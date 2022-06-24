import logging

from opsdnpy.app_manager import AppManager
from opsdnpy.basic_app import BasicApp
from opsdnpy.data_path import Datapath


class Controller:
    def __init__(self):
        self.logger = logging.getLogger('Controller')

        logging.basicConfig(level=logging.DEBUG)
        self.datapaths = dict()
        self.appManager = AppManager()
        self.appManager.apps.append(BasicApp())
        # self.appManager.apps.append(SimpleSwitch13())
        # self.appManager.apps.append(TopologyDiscover())
        # self.appManager.apps.append(FattreeForward(self.appManager))

    def handle_dp_pkt(self, conn_id, buf, len):
        self.logger.debug('handle_dp_pkt')
        if conn_id not in self.datapaths:
            self.datapaths[conn_id] = Datapath(self.appManager, conn_id)

        self.datapaths[conn_id].handle_pkt(buf)
        return 'heiheihei'
