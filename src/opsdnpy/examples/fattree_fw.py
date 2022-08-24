import logging
import random

from networkx import NetworkXNoPath
from ryu.lib.dpid import dpid_to_str
from ryu.lib.packet import ethernet, ether_types
from ryu.ofproto import ofproto_v1_3_parser as ofp13
import networkx as nx

from opsdnpy.app import controller_app, set_ev_handler


@controller_app
class FattreeForward:
    def __init__(self, appManager):
        self.logger = logging.getLogger('FattreeForward')
        self.appManager = appManager
        for app in self.appManager.apps:
            if hasattr(app, 'G'):
                self.G = app.G
                break

        self.datapaths = dict()

    @set_ev_handler(ofp13.OFPSwitchFeatures)
    def switch_features_handler(self, dp, msg):
        self.datapaths[dpid_to_str(dp.id)] = dp

    @set_ev_handler(ofp13.OFPPacketIn)
    def packet_in_handler(self, dp, msg):
        eth, pkt_type, pkt_data = ethernet.ethernet.parser(msg.data)
        self.logger.info('self.G = ' + str(self.G))
        if eth.ethertype == ether_types.ETH_TYPE_IP:
            # We only forward IP packet here.
            self.logger.info('IP packet from %s to %s', eth.src, eth.dst)
            try:
                paths = [p for p in nx.all_shortest_paths(self.G, dpid_to_str(dp.id), eth.dst)]
                # self.logger.info('candidate paths: %s', str(paths))
                path = random.choice(paths)
                self.logger.info('path: %s', str(path))

                for i in range(1, len(path)):
                    src, dst = path[i - 1], path[i]

                    if src not in self.datapaths:
                        return

                    edge = self.G.edges[src, dst]
                    self.logger.info('edge: %s', str(edge))
                    src_port = edge['src_port']
                    dst_port = edge['dst_port']
                    out_port = -1
                    if src_port.startswith(src):
                        out_port = src_port.replace(src + ':', '')
                    elif dst_port.startswith(src):
                        out_port = dst_port.replace(src + ':', '')
                    self.logger.info('out_port: %s', out_port)

                    if int(out_port) != -1:
                        match = ofp13.OFPMatch(eth_src=eth.src, eth_dst=eth.dst)
                        actions = [ofp13.OFPActionOutput(int(out_port))]
                        self.add_flow(self.datapaths[src], 100, match, actions)


            except NetworkXNoPath:
                pass

    @staticmethod
    def add_flow(datapath, priority, match, actions, buffer_id=None):
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
