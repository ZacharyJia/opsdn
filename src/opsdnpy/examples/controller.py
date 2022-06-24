from opsdnpy.controller import Controller

from fattree_fw import FattreeForward
from topology_discover import TopologyDiscover


class MyController(Controller):
    def __init__(self):
        super(MyController, self).__init__()
        self.appManager.apps.append(TopologyDiscover())
        self.appManager.apps.append(FattreeForward(self.appManager))
