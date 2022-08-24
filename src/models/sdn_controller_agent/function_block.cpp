#ifdef NSE_VSC_MAGIC_DEF
/* Note: codes between the #ifdef and #endif will not take effect. DO NOT add your codes here! */
#include "opnet.h"
#include "header_block.h"
#include "sv.h"
#endif

// Create tcp listen on the given port
// It will be called every time after we accpet a incoming connection
void create_listen_connection()
{
    FIN(create_listen_connection);

    // The port must be less than 1024 because of limitions from OPNET.
    // I found that we cannot listen multiple times in the same port larger than 1024. It will report errors says the port is occupied.
    // TODO: we need to move it to the model attribute so that users can customize it. But we need warning them it must be less than 1024.
    const int port = 998;

    // Make a copy of tcp_app_handle for processing subsequent incoming connections.
    auto tcp_app_handle_tmp = tcp_intf_hndl_copy(tcp_app_handle);

    // TODO: We need replace the IP will self ip address instead of a fixed string.
    int conn_id = tcp_connection_with_source_open(&tcp_app_handle_tmp, 0, TCPC_PORT_UNSPEC,
        ip_address_create("192.168.10.2"), port, TCPC_COMMAND_OPEN_PASSIVE, 7);

    if(conn_id == TCPC_CONN_ID_UNSPEC || conn_id == TCPC_CONN_ID_INVALID)
    {
        printf("tcp connection open failed\n");
    }
    else {
        tcp_app_handle_map[conn_id] = tcp_app_handle_tmp;
    }
    FOUT;
}

// we have received a openflow packet from the switches, so we need to serialize it and send it to the controller in python environment.
void handle_openflow_packet(int conn_id, Packet* pkptr) 
{
    FIN(handle_openflow_packet(conn_id, pkptr));
    // It is ensured that the pkptr is in the format of openflow_msg
    char* pkt_buf;
    OpT_Packet_Size pkt_size;
    openflow_tcp_sar_serialization_callback(pkptr, &pkt_buf, &pkt_size);
    controller_support_handle_pkt(conn_id, pkt_buf, pkt_size);

    FOUT;
}
