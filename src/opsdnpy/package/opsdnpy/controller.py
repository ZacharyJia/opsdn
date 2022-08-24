import logging

from opsdnpy.app_manager import AppManager
from opsdnpy.basic_app import BasicApp
from opsdnpy.data_path import Datapath

# This is the base class of OPSDN controllers.
# Here we load BasicApp to the controller for handling basic openflow interactions.
# And we provide a `handle_dp_pkt` function for dispatch packets to corresponding datapaths.
class Controller:
    def __init__(self):
        self.logger = logging.getLogger('Controller')

        self.datapaths = dict()
        self.appManager = AppManager()
        self.appManager.apps.append(BasicApp())

    def handle_dp_pkt(self, conn_id, buf, len):
        if conn_id not in self.datapaths:
            self.datapaths[conn_id] = Datapath(self.appManager, conn_id)

        self.datapaths[conn_id].handle_pkt(buf)
        return ''
