# 开发笔记

## 坑记录
1. 还是需要sitl的，需要替换VS2010要用的sitl的dll文件。
2. （这是一个老问题，在这里也会出问题，所以一并转录过来。解决方案一致。）OP和ryu连的时候，使用内置的application demand作为测试流量。在发送packet-in消息时，会在ryu端出现错误的版本号的错误提示，把ryu卡崩溃，无法继续下去。  
问题原因及修改：经过检查发现，使用内置的application demand作为流量时，发送packet-in消息时，会在openflow_real_payload_support.ex.c文件中进行data包的序列化。序列化时，由于最高只翻译3层，因此只会翻译到UDP或者TCP包，data字段会作为payload放在最后。 但是内置流量的UDP/TCP包应应该是没有data的包的（只通过设置包的大小来实现流量模拟），这时这个包的序列化就只得到前42个字节（for UDP，14+20+8）。而openflow的包里相关字段的payload大小应该时42+数据大小，因此发出去的包的大小是小于该大小的。这时候ryu接收到对应的包，会认为tcp发生了segment，进而把后续包的内容作为了该包的缺失部分。这样就会产生严重的错位，后续包会解析到错误的数据，出现上述错误。
修改方案：在openflow_real_payload_support.ex.c中的openflow_real_payload_serialize_ofpc_packet_in函数里，当调用完sitl的翻译函数后，补充一个while循环，当发现当前已经翻译的字节数小于预期字节数时，就通过补0的方式，将序列化后的数据补充到实际大小。
```C
while (payload_handle_ptr->current_index < payload_handle_ptr->size) 
   {
       oms_sar_payload_uint8_serialize(payload_handle_ptr, (OpT_uInt8)0);
   }
```
3. 写控制器代码的时候，注意一点，OPNET的交换机不支持FLOOD_PORT，可以用ALL_PORT代替。**写控制器其他代码的时候也要注意，OP应该有挺多东西不支持的，所以要小心。**
4. 初始化的时候，要顺便把sitl也初始化了，可以参考代码。