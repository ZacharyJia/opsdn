#ifdef NSE_VSC_MAGIC_DEF
/* Note: codes between the #ifdef and #endif will not take effect. DO NOT add your codes here! */
#include "opnet.h"
#include "header_block.h"
#include "sv.h"
#endif


void create_listen_connection()
{
    FIN(create_listen_connection);
    // �˿ڱ���ΪС��1024�ı����˿ڣ������޷���ͬһ�˿��ϴ����������������ֶ˿��ѱ�ռ�õ����
    const int port = 998;

    // ��Ҫ����һ��tcp_app_handle�������������connection
    auto tcp_app_handle_tmp = tcp_intf_hndl_copy(tcp_app_handle);

    int conn_id = tcp_connection_with_source_open(&tcp_app_handle_tmp, 0, TCPC_PORT_UNSPEC,
        ip_address_create("192.168.10.2"), port, TCPC_COMMAND_OPEN_PASSIVE, 7);

    if(conn_id == TCPC_CONN_ID_UNSPEC || conn_id == TCPC_CONN_ID_INVALID)
    {
        printf("tcp connection open failed\n");
    }
    else {
        // �����ɹ��󽫶�Ӧ��tcp_app_handle��������
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
    // ����ǰ�Ѿ�ȷ��������pkptr�϶���openflow_msg��ʽ��
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
    //     // ����hello��
    //     tcp_data_send(tcp_app_handle_map[conn_id], create_hello_pkt(transaction_id));
    //     tcp_data_send(tcp_app_handle_map[conn_id], create_feature_req_pkt(transaction_id));
    //     break;

    // case OfpC_Features_Reply:
    //     // feature reply ������datapath id������Ҫ��
    //     break;
    
    // default:
    //     printf("�յ�����������Ϣ, ����: %d\n", pkt_type);
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
//     //��ʼ��DLL
//     //���汾��(���ֽ�)Ϊ2�����汾��Ϊ2������ 0x0202
//     WORD sockVersion = MAKEWORD(2, 2);
//     WSADATA wsaData;
//     // WSAStartup() ����ִ�гɹ��󣬻Ὣ�� ws2_32.dll �йص���Ϣд�� WSAData �ṹ�����
//     //(ֻ���עǰ������Ա����)
//     if (WSAStartup(sockVersion, &wsaData) != 0)
//         FOUT;

//     //�����׽��֣�socket() �������������׽��֣�ȷ���׽��ֵĸ�������
//     // IPv4 ��ַ���������ӵ����ݴ��䷽ʽ��TCP ����Э��
//     ryu_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

//     // ���������������,���������׽�����IP��ַ 101.76.220.219���˿� 3000 �󶨣�
//     sockaddr_in sockAddr;
//     memset(&sockAddr, 0, sizeof(sockAddr));
//     sockAddr.sin_family = PF_INET;

//     // 32λIP��ַ,s_addr ��һ������(unsigned long)����IP��ַ��һ���ַ�����
//     //������Ҫ inet_addr() ��������ת��
//     sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

//     // 16λ�Ķ˿ں�,�˿ں���Ҫ�� htons() ����ת��,0~1023 �Ķ˿�һ����ϵͳ������ض��ķ������
//     //������ 1024~65536 ֮�����˿ںš�
//     sockAddr.sin_port = htons(6633);

//     if (connect(ryu_sock, (SOCKADDR *)&sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
//     {
//         printf("����ʧ��\n");
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
//         // todo: �������û�����꣬����Ҫ��������
//     }
//     FOUT;
// }