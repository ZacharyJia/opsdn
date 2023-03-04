/* Process model C++ form file: sdn_controller_agent.pr.cpp */
/* Portions of this file copyright 2017 by Riverbed Technology. All rights reserved. */


/*
 =========================== NOTE ==========================
 This file is automatically generated from sdn_controller_agent.pr.m
 during a process model compilation.

 Do NOT manually edit this file.
 Manual edits will be lost during the next compilation.
 =========================== NOTE ==========================
*/



/* This variable carries the header into the object file */
const char sdn_controller_agent_pr_cpp [] = "MIL_3_Tfile_Hdr_ 1860 30A op_runsim_opt 7 62A5D1DE 62A5D1DE 1 Zachary-1080 lab_user 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 4e52 0                                                                                                                                                                                                                                                                                                                                                                                              ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

#include "sdn_controller_agent/header_block.h"

/* End of Header Block */

#if !defined (VOSD_NO_FIN)
#undef	BIN
#undef	BOUT
#define	BIN		FIN_LOCAL_FIELD(_op_last_line_passed) = __LINE__ - _op_block_origin;
#define	BOUT	BIN
#define	BINIT	FIN_LOCAL_FIELD(_op_last_line_passed) = 0; _op_block_origin = __LINE__;
#else
#define	BINIT
#endif /* #if !defined (VOSD_NO_FIN) */



/* State variable definitions */
class sdn_controller_agent_state
	{
	private:
		/* Internal state tracking for FSM */
		FSM_SYS_STATE

	public:
		sdn_controller_agent_state (void);

		/* Destructor contains Termination Block */
		~sdn_controller_agent_state (void);

		/* State Variables */
		Objid	                  		my_node_objid                                   ;
		ApiT_Tcp_App_Handle	    		tcp_app_handle                                  ;
		std::map<int, ApiT_Tcp_App_Handle>			tcp_app_handle_map                              ;

		/* FSM code */
		void sdn_controller_agent (OP_SIM_CONTEXT_ARG_OPT);
		/* Diagnostic Block */
		void _op_sdn_controller_agent_diag (OP_SIM_CONTEXT_ARG_OPT);

#if defined (VOSD_NEW_BAD_ALLOC)
		void * operator new (size_t) throw (VOSD_BAD_ALLOC);
#else
		void * operator new (size_t);
#endif
		void operator delete (void *);

		/* Memory management */
		static VosT_Obtype obtype;
	};

VosT_Obtype sdn_controller_agent_state::obtype = (VosT_Obtype)OPC_NIL;

#define my_node_objid           		op_sv_ptr->my_node_objid
#define tcp_app_handle          		op_sv_ptr->tcp_app_handle
#define tcp_app_handle_map      		op_sv_ptr->tcp_app_handle_map

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	sdn_controller_agent_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((sdn_controller_agent_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


/* Function Block */

#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ + 2};
#endif

#include "sdn_controller_agent/function_block.cpp"


/* End of Function Block */

/* Undefine optional tracing in FIN/FOUT/FRET */
/* The FSM has its own tracing code and the other */
/* functions should not have any tracing.		  */
#undef FIN_TRACING
#define FIN_TRACING

#undef FOUTRET_TRACING
#define FOUTRET_TRACING

/* Undefine shortcuts to state variables because the */
/* following functions are part of the state class */
#undef my_node_objid
#undef tcp_app_handle
#undef tcp_app_handle_map

/* Access from C kernel using C linkage */
extern "C"
{
	VosT_Obtype _op_sdn_controller_agent_init (int * init_block_ptr);
	VosT_Address _op_sdn_controller_agent_alloc (VosT_Obtype, int);
	void sdn_controller_agent (OP_SIM_CONTEXT_ARG_OPT)
		{
		((sdn_controller_agent_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr))->sdn_controller_agent (OP_SIM_CONTEXT_PTR_OPT);
		}

	void _op_sdn_controller_agent_svar (void *, const char *, void **);

	void _op_sdn_controller_agent_diag (OP_SIM_CONTEXT_ARG_OPT)
		{
		((sdn_controller_agent_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr))->_op_sdn_controller_agent_diag (OP_SIM_CONTEXT_PTR_OPT);
		}

	void _op_sdn_controller_agent_terminate (OP_SIM_CONTEXT_ARG_OPT)
		{
		/* The destructor is the Termination Block */
		delete (sdn_controller_agent_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr);
		}


} /* end of 'extern "C"' */




/* Process model interrupt handling procedure */


void
sdn_controller_agent_state::sdn_controller_agent (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (sdn_controller_agent_state::sdn_controller_agent ());
	try
		{
		/* Temporary Variables */
		#include "sdn_controller_agent/tv.h"
		/* End of Temporary Variables */


		FSM_ENTER_NO_VARS ("sdn_controller_agent")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_UNFORCED_NOLABEL (0, "init", "sdn_controller_agent [init enter execs]")
				FSM_PROFILE_SECTION_IN ("sdn_controller_agent [init enter execs]", state0_enter_exec)
				{
#include "sdn_controller_agent/state_init_enter.cpp"
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (1,"sdn_controller_agent")


			/** state (init) exit executives **/
			FSM_STATE_EXIT_UNFORCED (0, "init", "sdn_controller_agent [init exit execs]")
				FSM_PROFILE_SECTION_IN ("sdn_controller_agent [init exit execs]", state0_exit_exec)
				{
#include "sdn_controller_agent/state_init_exit.cpp"
				}
				FSM_PROFILE_SECTION_OUT (state0_exit_exec)


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (2, state2_enter_exec, ;, "default", "", "init", "listen", "tr_20", "sdn_controller_agent [init -> listen : default / ]")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "idle", state1_enter_exec, "sdn_controller_agent [idle enter execs]")
				FSM_PROFILE_SECTION_IN ("sdn_controller_agent [idle enter execs]", state1_enter_exec)
				{
#include "sdn_controller_agent/state_idle_enter.cpp"
				}
				FSM_PROFILE_SECTION_OUT (state1_enter_exec)

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"sdn_controller_agent")


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "idle", "sdn_controller_agent [idle exit execs]")
				FSM_PROFILE_SECTION_IN ("sdn_controller_agent [idle exit execs]", state1_exit_exec)
				{
#include "sdn_controller_agent/state_idle_exit.cpp"
				}
				FSM_PROFILE_SECTION_OUT (state1_exit_exec)


			/** state (idle) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "idle", "idle", "tr_1", "sdn_controller_agent [idle -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (listen) enter executives **/
			FSM_STATE_ENTER_UNFORCED (2, "listen", state2_enter_exec, "sdn_controller_agent [listen enter execs]")
				FSM_PROFILE_SECTION_IN ("sdn_controller_agent [listen enter execs]", state2_enter_exec)
				{
#include "sdn_controller_agent/state_listen_enter.cpp"
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (5,"sdn_controller_agent")


			/** state (listen) exit executives **/
			FSM_STATE_EXIT_UNFORCED (2, "listen", "sdn_controller_agent [listen exit execs]")
				FSM_PROFILE_SECTION_IN ("sdn_controller_agent [listen exit execs]", state2_exit_exec)
				{
#include "sdn_controller_agent/state_listen_exit.cpp"
				}
				FSM_PROFILE_SECTION_OUT (state2_exit_exec)


			/** state (listen) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "listen", "idle", "tr_21", "sdn_controller_agent [listen -> idle : default / ]")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"sdn_controller_agent")
		}
	catch (...)
		{
		Vos_Error_Print (VOSC_ERROR_ABORT,
			(const char *)VOSC_NIL,
			"Unhandled C++ exception in process model (sdn_controller_agent)",
			(const char *)VOSC_NIL, (const char *)VOSC_NIL);
		}
	}




void
sdn_controller_agent_state::_op_sdn_controller_agent_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
#if defined (OPD_ALLOW_ODB)
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = __LINE__+1;
#endif

	FIN_MT (sdn_controller_agent_state::_op_sdn_controller_agent_diag ())

	try
		{

		/* Diagnostic Block */

		BINIT
#include "sdn_controller_agent/diag_block.cpp"

		/* End of Diagnostic Block */

		}
	catch (...)
		{
		Vos_Error_Print (VOSC_ERROR_ABORT,
			(const char *)VOSC_NIL,
			"Unhandled C++ exception in process model (sdn_controller_agent)",
			"In Diagnostic Block",
			(const char *)VOSC_NIL);
		}

	FOUT
#endif /* OPD_ALLOW_ODB */
	}

void
sdn_controller_agent_state::operator delete (void* ptr)
	{
	FIN (sdn_controller_agent_state::operator delete (ptr));
	Vos_Poolmem_Dealloc (ptr);
	FOUT
	}

sdn_controller_agent_state::~sdn_controller_agent_state (void)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = __LINE__;
#endif

	FIN (sdn_controller_agent_state::~sdn_controller_agent_state ())

	try
		{

		/* Termination Block */

		BINIT
#include "sdn_controller_agent/term_block.c"

		/* End of Termination Block */

		}
	catch (...)
		{
		Vos_Error_Print (VOSC_ERROR_ABORT,
			(const char *)VOSC_NIL,
			"Unhandled C++ exception in process model (sdn_controller_agent)",
			"In Termination Block",
			(const char *)VOSC_NIL);
		}

	FOUT
	}


#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

void *
sdn_controller_agent_state::operator new (size_t)
#if defined (VOSD_NEW_BAD_ALLOC)
		throw (VOSD_BAD_ALLOC)
#endif
	{
	void * new_ptr;

	FIN_MT (sdn_controller_agent_state::operator new ());

	new_ptr = Vos_Alloc_Object (sdn_controller_agent_state::obtype);
#if defined (VOSD_NEW_BAD_ALLOC)
	if (new_ptr == VOSC_NIL) throw VOSD_BAD_ALLOC();
#endif
	FRET (new_ptr)
	}

/* State constructor initializes FSM handling */
/* by setting the initial state to the first */
/* block of code to enter. */

sdn_controller_agent_state::sdn_controller_agent_state (void) :
		_op_current_block (0)
	{
#if defined (OPD_ALLOW_ODB)
		_op_current_state = "sdn_controller_agent [init enter execs]";
#endif
	}

VosT_Obtype
_op_sdn_controller_agent_init (int * init_block_ptr)
	{
	FIN_MT (_op_sdn_controller_agent_init (init_block_ptr))

	sdn_controller_agent_state::obtype = Vos_Define_Object_Prstate ("proc state vars (sdn_controller_agent)",
		sizeof (sdn_controller_agent_state));
	*init_block_ptr = 0;

	FRET (sdn_controller_agent_state::obtype)
	}

VosT_Address
_op_sdn_controller_agent_alloc (VosT_Obtype, int)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	sdn_controller_agent_state * ptr;
	FIN_MT (_op_sdn_controller_agent_alloc ())

	/* New instance will have FSM handling initialized */
#if defined (VOSD_NEW_BAD_ALLOC)
	try {
		ptr = new sdn_controller_agent_state;
	} catch (const VOSD_BAD_ALLOC &) {
		ptr = VOSC_NIL;
	}
#else
	ptr = new sdn_controller_agent_state;
#endif
	FRET ((VosT_Address)ptr)
	}



void
_op_sdn_controller_agent_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	sdn_controller_agent_state		*prs_ptr;

	FIN_MT (_op_sdn_controller_agent_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (sdn_controller_agent_state *)gen_ptr;

	if (strcmp ("my_node_objid" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->my_node_objid);
		FOUT
		}
	if (strcmp ("tcp_app_handle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->tcp_app_handle);
		FOUT
		}
	if (strcmp ("tcp_app_handle_map" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->tcp_app_handle_map);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}
