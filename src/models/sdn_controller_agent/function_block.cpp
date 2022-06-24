#ifdef NSE_VSC_MAGIC_DEF
/* Note: codes between the #ifdef and #endif will not take effect. DO NOT add your codes here! */
#include "opnet.h"
#include "header_block.h"
#include "sv.h"
#endif


void create_listen_connection()
{
    FIN(create_listen_connection);
    // 端口必须为小于1024的保留端口，否则无法在同一端口上创建多个监听，会出现端口已被占用的情况
    const int port = 998;

    // 需要复制一个tcp_app_handle用来处理后续的connection
    auto tcp_app_handle_tmp = tcp_intf_hndl_copy(tcp_app_handle);

    int conn_id = tcp_connection_with_source_open(&tcp_app_handle_tmp, 0, TCPC_PORT_UNSPEC,
        ip_address_create("192.168.10.2"), port, TCPC_COMMAND_OPEN_PASSIVE, 7);

    if(conn_id == TCPC_CONN_ID_UNSPEC || conn_id == TCPC_CONN_ID_INVALID)
    {
        printf("tcp connection open failed\n");
    }
    else {
        // 创建成功后将对应的tcp_app_handle保存下来
        tcp_app_handle_map[conn_id] = tcp_app_handle_tmp;
    }
    FOUT;
}

Packet* create_feature_req_pkt(int transaction_id) 
{
    Packet* featureReqPkptr = op_pk_create_fmt("openflow_msg");
    op_pk_nfd_set_int32(featureReqPkptr, "version", OPENFLOW_VERSION);
    op_pk_nfd_set_int32(featureReqPkptr, "type", OfpC_Features_Request);
    op_pk_nfd_set_int32(featureReqPkptr, "length", 8);
    op_pk_nfd_set_int32(featureReqPkptr, "transaction id", transaction_id);
    return featureReqPkptr;
}

Packet* create_hello_pkt(int transaction_id)
{
    Packet* helloPkptr = op_pk_create_fmt("openflow_msg");
    op_pk_nfd_set_int32(helloPkptr, "version", OPENFLOW_VERSION);
    op_pk_nfd_set_int32(helloPkptr, "type", OfpC_Hello);
    op_pk_nfd_set_int32(helloPkptr, "length", 8);
    op_pk_nfd_set_int32(helloPkptr, "transaction id", transaction_id);
    return helloPkptr;
}

void handle_openflow_packet(int conn_id, Packet* pkptr) 
{
    FIN(handle_openflow_packet(conn_id, pkptr));
    // 调用前已经确保，来的pkptr肯定是openflow_msg格式的
    char* pkt_buf;
    OpT_Packet_Size pkt_size;
    openflow_tcp_sar_serialization_callback(pkptr, &pkt_buf, &pkt_size);
    controller_support_handle_pkt(conn_id, pkt_buf, pkt_size);


    // int pkt_type;
    // int transaction_id;
    // op_pk_nfd_get_int32(pkptr, "type", &pkt_type);
    // op_pk_nfd_get_int32(pkptr, "transaction id", &transaction_id);
    // switch (pkt_type)
    // {
    // case OfpC_Hello:
    //     // 处理hello包
    //     tcp_data_send(tcp_app_handle_map[conn_id], create_hello_pkt(transaction_id));
    //     tcp_data_send(tcp_app_handle_map[conn_id], create_feature_req_pkt(transaction_id));
    //     break;

    // case OfpC_Features_Reply:
    //     // feature reply 当中有datapath id，所以要先
    //     break;
    
    // default:
    //     printf("收到了其他的消息, 类型: %d\n", pkt_type);
    //     break;
    // }


    // char* pkt_buf;
    // OpT_Packet_Size pkt_size;
    // openflow_tcp_sar_serialization_callback(pkptr, &pkt_buf, &pkt_size);
    
    // for (int i = 0; i < pkt_size; i++)
    // {
    //     printf("%x ", pkt_buf[i]);
    // }
    // printf("\n");
    // ryu_send(pkt_buf, pkt_size);
    FOUT;
}

// void create_ryu_connection()
// {
//     FIN(create_ryu_connection);
//     //初始化DLL
//     //主版本号(低字节)为2，副版本号为2，返回 0x0202
//     WORD sockVersion = MAKEWORD(2, 2);
//     WSADATA wsaData;
//     // WSAStartup() 函数执行成功后，会将与 ws2_32.dll 有关的信息写入 WSAData 结构体变量
//     //(只需关注前两个成员即可)
//     if (WSAStartup(sockVersion, &wsaData) != 0)
//         FOUT;

//     //创建套接字，socket() 函数用来创建套接字，确定套接字的各种属性
//     // IPv4 地址、面向连接的数据传输方式、TCP 传输协议
//     ryu_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

//     // 向服务器发起请求,将创建的套接字与IP地址 101.76.220.219、端口 3000 绑定：
//     sockaddr_in sockAddr;
//     memset(&sockAddr, 0, sizeof(sockAddr));
//     sockAddr.sin_family = PF_INET;

//     // 32位IP地址,s_addr 是一个整数(unsigned long)，而IP地址是一个字符串，
//     //所以需要 inet_addr() 函数进行转换
//     sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

//     // 16位的端口号,端口号需要用 htons() 函数转换,0~1023 的端口一般由系统分配给特定的服务程序，
//     //尽量在 1024~65536 之间分配端口号。
//     sockAddr.sin_port = htons(6633);

//     if (connect(ryu_sock, (SOCKADDR *)&sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
//     {
//         printf("连接失败\n");
//         ryu_sock = -1;
//     }

//     FOUT;
// }


// void ryu_send(char* buf, int len)
// {
//     FIN(ryu_send);
//     printf("Send data to ryu [%d]\n", len);
//     int ret = send(ryu_sock, buf, len, 0);
//     FOUT;
// }

// void ryu_recv()
// {
//     FIN(ryu_recv);
//     printf("recv data from ryu ");
//     char buf[2048];
//     int ret = recv(ryu_sock, buf, 2048, 0);
//     if (ret == SOCKET_ERROR) {
//         int err = WSAGetLastError();
//     }
//     else {
//         printf("[%d]\n", ret);
//         OpT_Packet_Size converted = 0;
//         Packet* pkptr = openflow_tcp_sar_deserialization_callback(buf, ret, &converted);
//         if (pkptr)
//         {
//             tcp_data_send(tcp_app_handle, pkptr);
//         }
//         // todo: 如果数据没处理完，还需要继续处理
//     }
//     FOUT;
// }