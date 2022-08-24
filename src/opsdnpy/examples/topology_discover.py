# Copyright (C) 2011 Nippon Telegraph and Telephone Corporation.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
# implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# This file is modified from Ryu By Zachary

import json
import logging
import struct

import six
from ryu.lib.dpid import dpid_to_str, str_to_dpid
from ryu.lib.packet.ether_types import ETH_TYPE_LLDP, ETH_TYPE_CFM
import ryu.lib.packet.lldp as lldp

import opsdn

from opsdnpy.app import controller_app, set_ev_handler
from opsdnpy.op_timer import OpTimer

import ryu.ofproto.ofproto_v1_3_parser as ofp13
from ryu.ofproto import ofproto_v1_3 as ofproto
from ryu.lib.packet import packet
from ryu.lib.packet import ethernet

from exceptions import ControllerException
import networkx as nx

LLDP_SEND_PERIOD = 10


class LLDPPacket(object):
    # make a LLDP packet for link discovery.

    CHASSIS_ID_PREFIX = 'dpid:'
    CHASSIS_ID_PREFIX_LEN = len(CHASSIS_ID_PREFIX)
    CHASSIS_ID_FMT = CHASSIS_ID_PREFIX + '%s'

    PORT_ID_STR = '!I'  # uint32_t
    PORT_ID_SIZE = 4

    class LLDPUnknownFormat(ControllerException):
        message = '%(msg)s'

    @staticmethod
    def lldp_packet(dpid, port_no, dl_addr, ttl):
        pkt = packet.Packet()

        dst = lldp.LLDP_MAC_NEAREST_BRIDGE
        src = dl_addr
        ethertype = ETH_TYPE_LLDP
        eth_pkt = ethernet.ethernet(dst, src, ethertype)
        pkt.add_protocol(eth_pkt)

        tlv_chassis_id = lldp.ChassisID(
            subtype=lldp.ChassisID.SUB_LOCALLY_ASSIGNED,
            chassis_id=(LLDPPacket.CHASSIS_ID_FMT %
                        dpid_to_str(dpid)).encode('ascii'))

        tlv_port_id = lldp.PortID(subtype=lldp.PortID.SUB_PORT_COMPONENT,
                                  port_id=struct.pack(
                                      LLDPPacket.PORT_ID_STR,
                                      port_no))

        tlv_ttl = lldp.TTL(ttl=ttl)
        tlv_end = lldp.End()

        tlvs = (tlv_chassis_id, tlv_port_id, tlv_ttl, tlv_end)
        lldp_pkt = lldp.lldp(tlvs)
        pkt.add_protocol(lldp_pkt)

        pkt.serialize()
        return pkt.data

    @staticmethod
    def lldp_parse(data):
        pkt = packet.Packet(data)
        i = iter(pkt)
        eth_pkt = six.next(i)
        assert type(eth_pkt) == ethernet.ethernet

        lldp_pkt = six.next(i)
        if type(lldp_pkt) != lldp.lldp:
            raise LLDPPacket.LLDPUnknownFormat()

        tlv_chassis_id = lldp_pkt.tlvs[0]
        if tlv_chassis_id.subtype != lldp.ChassisID.SUB_LOCALLY_ASSIGNED:
            raise LLDPPacket.LLDPUnknownFormat(
                msg='unknown chassis id subtype %d' % tlv_chassis_id.subtype)
        chassis_id = tlv_chassis_id.chassis_id.decode('utf-8')
        if not chassis_id.startswith(LLDPPacket.CHASSIS_ID_PREFIX):
            raise LLDPPacket.LLDPUnknownFormat(
                msg='unknown chassis id format %s' % chassis_id)
        src_dpid = str_to_dpid(chassis_id[LLDPPacket.CHASSIS_ID_PREFIX_LEN:])

        tlv_port_id = lldp_pkt.tlvs[1]
        if tlv_port_id.subtype != lldp.PortID.SUB_PORT_COMPONENT:
            raise LLDPPacket.LLDPUnknownFormat(
                msg='unknown port id subtype %d' % tlv_port_id.subtype)
        port_id = tlv_port_id.port_id
        if len(port_id) != LLDPPacket.PORT_ID_SIZE:
            raise LLDPPacket.LLDPUnknownFormat(
                msg='unknown port id %d' % port_id)
        (src_port_no,) = struct.unpack(LLDPPacket.PORT_ID_STR, port_id)

        return src_dpid, src_port_no


class Port:
    DEFAULT_TTL = 120

    def __init__(self, dp, port_no, hw_addr):
        self.datapath = dp
        self.port_no = port_no
        self.hw_addr = hw_addr
        self.lldp_data = LLDPPacket.lldp_packet(
            self.datapath.id, self.port_no, self.hw_addr, self.DEFAULT_TTL
        )
        self.is_sw2sw = False


@controller_app
class TopologyDiscover:

    def __init__(self):
        self.logger = logging.getLogger('TopologyDiscover')
        self.timer = OpTimer()
        self.ports = dict()

        self.G = nx.Graph()

        self.timer.set_op_timer(opsdn.sim_time() + LLDP_SEND_PERIOD, self.send_lldp_msg, None)

    @staticmethod
    def get_port_key(dpid, port):
        return dpid_to_str(dpid) + ':' + str(port)

    @set_ev_handler(ofp13.OFPSwitchFeatures)
    def switch_features_handler(self, dp, msg):
        self.logger.info('switch_features_handler...............................')
        datapath = dp
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser

        # Install LLDP flow entry
        self.install_lldp_flow(datapath)

        self.install_default_packet_in_flow(datapath)

        self.G.add_node(dpid_to_str(dp.id), type='switch')

        req = ofp13.OFPPortDescStatsRequest(datapath, 0)
        datapath.send_msg(req)

    @set_ev_handler(ofp13.OFPPortDescStatsReply)
    def port_desc_handler(self, dp, msg):
        for p in msg.body:
            port_key = self.get_port_key(dp.id, p.port_no)
            if port_key not in self.ports and p.name != b'P00':  # 跳过P00端口，那个是跟控制器通信用的
                self.ports[port_key] = Port(dp, p.port_no, p.hw_addr)

    @set_ev_handler(ofp13.OFPPortStatus)
    def port_status_handler(self, dp, msg):
        ofpport = msg.desc
        port_key = self.get_port_key(dp.id, ofpport.port_no)
        if port_key not in self.ports:
            self.ports[port_key] = Port(dp, ofpport.port_no, ofpport.hw_addr)

    def add_flow(self, datapath, priority, match, actions, buffer_id=None):
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser

        inst = [parser.OFPInstructionActions(ofproto.OFPIT_APPLY_ACTIONS,
                                             actions)]
        if buffer_id:
            mod = parser.OFPFlowMod(datapath=datapath, buffer_id=buffer_id,
                                    priority=priority, match=match,
                                    instructions=inst)
        else:
            mod = parser.OFPFlowMod(datapath=datapath, priority=priority,
                                    match=match, instructions=inst)
        datapath.send_msg(mod)

    @set_ev_handler(ofp13.OFPPacketIn)
    def lldp_packet_in_handler(self, dp, msg):
        # If you hit this you might want to increase
        # the "miss_send_length" of your switch
        if msg.msg_len < msg.total_len:
            self.logger.debug("packet truncated: only %s of %s bytes",
                              msg.msg_len, msg.total_len)
        datapath = dp
        ofproto = datapath.ofproto
        parser = datapath.ofproto_parser

        try:
            src_dpid, src_port_no = LLDPPacket.lldp_parse(msg.data)
        except LLDPPacket.LLDPUnknownFormat:
            # This handler can receive all the packets which can be
            # not-LLDP packet. Ignore it silently
            return

        dst_dpid = msg.datapath.id
        dst_port_no = msg.match['in_port']

        self.logger.info('detect link: %d:%d <---> %d:%d',
                         src_dpid, src_port_no, dst_dpid, dst_port_no)

        src_port_key = self.get_port_key(src_dpid, src_port_no)
        dst_port_key = self.get_port_key(dst_dpid, dst_port_no)
        if src_port_key not in self.ports or dst_port_key not in self.ports:
            return
        self.ports[src_port_key].is_sw2sw = True
        self.ports[dst_port_key].is_sw2sw = True
        self.G.add_edge(
            dpid_to_str(src_dpid),
            dpid_to_str(dst_dpid),
            src_port=src_port_key,
            dst_port=dst_port_key
        )

        self.write_graph_to_json()
        # nx.write_gexf(self.G, 'E:\\source\\cython-op-demo\\python\\topo.gexf')

    @set_ev_handler(ofp13.OFPPacketIn)
    def handle_ether_packet(self, dp, msg):
        eth, pkt_type, pkt_data = ethernet.ethernet.parser(msg.data)

        # ignore lldp and cfm packets
        if eth.ethertype in (ETH_TYPE_LLDP, ETH_TYPE_CFM):
            return

        self.logger.info('handle_ether_packet called!!!!!!!!!!!')

        dpid = dp.id
        port_no = msg.match['in_port']
        port_key = self.get_port_key(dpid, port_no)

        if port_key not in self.ports:
            return
        if self.ports[port_key].is_sw2sw:
            return

        host_mac = eth.src
        self.G.add_node(str(host_mac), type='server')

        self.G.add_edge(
            dpid_to_str(dpid),
            str(host_mac),
            src_port=port_key,
            dst_port='host:0'
        )

        self.write_graph_to_json()

    @staticmethod
    def install_default_packet_in_flow(dp):
        match = ofp13.OFPMatch()
        actions = [ofp13.OFPActionOutput(ofproto.OFPP_CONTROLLER,
                                         ofproto.OFPCML_NO_BUFFER
                                         )]
        inst = [ofp13.OFPInstructionActions(
            ofproto.OFPIT_APPLY_ACTIONS, actions)]
        mod = ofp13.OFPFlowMod(datapath=dp, match=match,
                               instructions=inst,
                               priority=0)
        dp.send_msg(mod)

    @staticmethod
    def install_lldp_flow(dp):
        match = ofp13.OFPMatch(
            eth_type=ETH_TYPE_LLDP,
            eth_dst=lldp.LLDP_MAC_NEAREST_BRIDGE)
        # OFPCML_NO_BUFFER is set so that the LLDP is not
        # buffered on switch
        parser = ofp13
        actions = [parser.OFPActionOutput(ofproto.OFPP_CONTROLLER,
                                          ofproto.OFPCML_NO_BUFFER
                                          )]
        inst = [parser.OFPInstructionActions(
            ofproto.OFPIT_APPLY_ACTIONS, actions)]
        mod = parser.OFPFlowMod(datapath=dp, match=match,
                                idle_timeout=0, hard_timeout=0,
                                instructions=inst,
                                priority=0xFFFF)
        dp.send_msg(mod)

    def send_lldp_msg(self, userdata):
        for port_key in self.ports:
            port = self.ports[port_key]
            dp = port.datapath
            actions = [dp.ofproto_parser.OFPActionOutput(port.port_no)]
            out = dp.ofproto_parser.OFPPacketOut(
                datapath=dp, in_port=dp.ofproto.OFPP_CONTROLLER,
                buffer_id=dp.ofproto.OFP_NO_BUFFER, actions=actions,
                data=port.lldp_data)

            dp.send_msg(out)
            # self.logger.info('[MyController]: port: %s', port)
        self.timer.set_op_timer(opsdn.sim_time() + LLDP_SEND_PERIOD, self.send_lldp_msg, None)

    def write_graph_to_json(self):
        data = nx.node_link_data(self.G)
        data['edges'] = data['links']
        # del data['links']
        # del data['graph']
        # del data['directed']
        # del data['multigraph']
        with open('topo.json', 'w') as f:
            json.dump(data, f)
