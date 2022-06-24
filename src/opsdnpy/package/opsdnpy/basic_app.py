import logging

import ryu.ofproto.ofproto_v1_3_parser as ofp13

import opsdn

from opsdnpy.app import controller_app, set_ev_handler
from opsdnpy.op_timer import OpTimer


@controller_app
class BasicApp:
    def __init__(self):
        self.logger = logging.getLogger('BasicApp')

    def repeat_run(self, user_data):
        self.logger.info('[%lf] Repeat running......%d', opsdn.sim_time(), user_data)
        OpTimer().set_op_timer(opsdn.sim_time() + 30, self.repeat_run, user_data + 1)

    @set_ev_handler(ofp13.OFPHello)
    def handle_hello(self, dp, msg):
        self.logger.info('%lf: handleHello is called!!', opsdn.sim_time())
        dp.send_msg(ofp13.OFPHello(dp))
        dp.send_msg(ofp13.OFPFeaturesRequest(dp))

    @set_ev_handler(ofp13.OFPSwitchFeatures)
    def handle_switch_features(self, dp, msg):
        dp.id = msg.datapath_id

    @set_ev_handler(ofp13.OFPEchoRequest)
    def handle_echo_request(self, dp, msg):
        dp.send_msg(ofp13.OFPEchoReply(dp, data=msg.data))

