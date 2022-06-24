import random
import logging

from ryu.ofproto import ofproto_parser, ofproto_v1_3, ofproto_protocol

import opsdn


class Datapath(ofproto_protocol.ProtocolDesc):
    def __init__(self, appManager, conn_id):
        super(Datapath, self).__init__()

        self.logger = logging.getLogger('Datapath')

        self.appManager = appManager
        self.conn_id = conn_id

        self.unreplied_echo_requests = []

        self.xid = random.randint(0, self.ofproto.MAX_XID)
        self.id = None  # datapath_id is unknown yet
        self._ports = None
        self.set_version(ofproto_v1_3.OFP_VERSION)
        # self.flow_format = ofproto_v1_3.NXFF_OPENFLOW10

    def handle_pkt(self, buf):
        self.logger.debug('handle_pkt')
        (version, msg_type, msg_len, xid) = ofproto_parser.header(buf)
        if len(buf) < msg_len:
            self.logger.error('packet buf len is less than the length field')
            return
        msg = ofproto_parser.msg(self, version, msg_type, msg_len, xid, buf[:msg_len])
        if msg:
            self.logger.info('received packet: ' + str(msg))
            self.dispatchHandler(msg)

    def dispatchHandler(self, msg):
        apps = self.appManager.get_applications()
        for app in apps:
            app.dispatch(self, msg.__class__.__name__, msg)

    def set_xid(self, msg):
        self.xid += 1
        self.xid &= self.ofproto.MAX_XID
        msg.set_xid(self.xid)
        return self.xid

    def send_msg(self, msg):
        assert isinstance(msg, self.ofproto_parser.MsgBase)
        if msg.xid is None:
            self.set_xid(msg)
        msg.serialize()
        self.logger.debug('send_msg %s', msg)
        return opsdn.send_to_dp(self.conn_id, msg.buf, len(msg.buf))
