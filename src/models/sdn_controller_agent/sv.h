#ifdef NSE_VSC_MAGIC_DEF
/* Note: codes between the #ifdef and #endif will not take effect. DO NOT add your codes here! */
/* state variables are listed here. DO NOT EDIT! */
#include "opnet.h"
#include "header_block.h"
#endif
Objid	 my_node_objid;

ApiT_Tcp_App_Handle	 tcp_app_handle;

std::map<int, ApiT_Tcp_App_Handle>	 tcp_app_handle_map;

