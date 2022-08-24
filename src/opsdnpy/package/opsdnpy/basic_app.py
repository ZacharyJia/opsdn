import logging

import ryu.ofproto.ofproto_v1_3_parser as ofp13

import opsdn

from opsdnpy.app import controller_app, set_ev_handler
from opsdnpy.op_timer import OpTimer

# A basic controller app for handling basic openflow interaction.

@controller_app
class BasicApp:
    def __init__(self):
        self.logger = logging.getLogger('BasicApp')

    @set_ev_handler(ofp13.OFPHello)
    def handle_hello(self, dp, msg):
        self.logger.debug('%lf: handle_hello is called!!', opsdn.sim_time())
        # Reply a Hello and FeatureRequest packe to the datapath.
        dp.send_msg(ofp13.OFPHello(dp))
        dp.send_msg(ofp13.OFPFeaturesRequest(dp))

    @set_ev_handler(ofp13.OFPSwitchFeatures)
    def handle_switch_features(self, dp, msg):
        # Record the datapath id cause the datapath id is sent in feature reply at the first time.
        dp.id = msg.datapath_id

    @set_ev_handler(ofp13.OFPEchoRequest)
    def handle_echo_request(self, dp, msg):
        dp.send_msg(ofp13.OFPEchoReply(dp, data=msg.data))

