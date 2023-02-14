#ifdef NSE_VSC_MAGIC_DEF
/* Note: codes between the #ifdef and #endif will not take effect. DO NOT add your codes here! */
#include "opnet.h"
#include "header_block.h"
#include "sv.h"
#endif

// get the ip address of this node, i.e., the controller's IP
IpT_Address get_host_ip_address() {
    FIN(getHostIpAddress);

    char address_str[20];
    
    IpT_Rte_Module_Data* module_ptr = ip_support_module_data_get(my_node_objid);
    Objid intf_info_objid_arr;
    op_ima_obj_attr_get (module_ptr->ip_parameters_objid, "Interface Information", &intf_info_objid_arr);
    
    Objid intf_info_objid = op_topo_child (intf_info_objid_arr, OPC_OBJTYPE_GENERIC, 0);
    op_ima_obj_attr_get_str(intf_info_objid, "Address", 20, address_str);

    FRET(ip_address_create(address_str));
}


// Create tcp listen on the given port
// It will be called every time after we accpet a incoming connection
void create_listen_connection()
{
    FIN(create_listen_connection);

    // The port must be less than 1024 because of limitions from OPNET.
    // I found that we cannot listen multiple times in the same port larger than 1024. It will report errors says the port is occupied.
    int port = 998;
    op_ima_obj_attr_get_int32(op_id_self(), "OpenFlowPort", &port);
    if (port >= 1024) {
        op_sim_end("The controller port cannot be greater than 1024 due to the TCP desgin of OPNET.",
                   "Please fill a port number less than 1024.",
                   "Do not forget to make changes on the SDN switches too.",
                   "Bye.");
    }

    // Make a copy of tcp_app_handle for processing subsequent incoming connections.
    auto tcp_app_handle_tmp = tcp_intf_hndl_copy(tcp_app_handle);

    // TODO: We need replace the IP will self ip address instead of a fixed string.
    int conn_id = tcp_connection_with_source_open(&tcp_app_handle_tmp, 0, TCPC_PORT_UNSPEC,
        get_host_ip_address(), port, TCPC_COMMAND_OPEN_PASSIVE, 7);

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
