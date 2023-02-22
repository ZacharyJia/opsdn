# opsdn-models
[English Version](./README.md)

opsdn的模型相关部分。

## 目录结构
- `sdn_controller_agent.pr.m`：控制器代理的进程模型，会被放到控制器代理节点当中。该模型实际上扮演了一个中间人的角色，在OpelFlow交换机和Python控制器之间上传下达。
- `sdn_controller_agent`: 该目录包含了上述进程模型的实际代码。我通常采用这种结构来组织进程模型的代码，因为OPNET对git的支持太差了，二进制模型没法直接做diff。
- `sdn_controller_ethernet_wkstn_adv.nd.m`: 控制器代理的节点模型。相当于仿真网络当中的控制器，所有交换机都连它。
- `sdn_controller_send_req.ic.m`: 用来进行进程间通信的ICI格式模型。这个ici是用来通知控制器有来自于Python的数据到达了。
- `controller_support.ex.cpp/.h`: 一个外部支持文件，用来跟dll-bridge进行通信的。