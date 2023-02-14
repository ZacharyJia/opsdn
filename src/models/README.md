# opsdn-models
[中文版](./README.zh.md)

This folder contains the models used in the OPNET.

## Structure
- `sdn_controller_agent.pr.m`：The controller agent process model, which is resides in the controller node. This model acts as a middle man between Openflow switches and the real Python controller.
- `sdn_controller_agent`: This folder contains the real code of the prcess model. I usually use this sturcture for better git support as opnet model is binary and hard to diff for git.
- `sdn_controller_ethernet_wkstn_adv.nd.m`: The controller agent node model in OPNET, every sdn scenario should haev at lease one controller node.
- `sdn_controller_send_req.ic.m`: An ICI packet format model for communication between modules. This ici is used for notify the controller process that data arrives from python.
- `controller_support.ex.cpp/.h`: A external support file for communicate with the dll-bridge.