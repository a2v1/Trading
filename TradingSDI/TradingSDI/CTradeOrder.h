//#include "stdafx.h"
#include <atldbcli.h>
class CTrade_orders
{

public:
	TCHAR m_Plugin_Status[31];
	TCHAR m_V_Login[31];
	TCHAR m_V_Order[31];
	TCHAR m_DT_SetupTime[31];
	TCHAR m_V_Symbol[31];
	TCHAR m_V_type[31];
	TCHAR m_D_initial_Volume[31];
	TCHAR m_D_order_price[31];
	TCHAR m_D_stop_loss[30];
	TCHAR m_V_commect[31];
	TCHAR m_order_modify_time[31];
	TCHAR m_V_Reason[31];
	TCHAR m_status_change_time[31];
	TCHAR m_V_state [30];
	

	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!
	
	DBSTATUS m_dwPlugin_StatusStatus;
	DBSTATUS m_dwV_LoginStatus;
	DBSTATUS m_dwV_OrderStatus;
	DBSTATUS m_dwDT_SetupTimeStatus;
	DBSTATUS m_dwV_SymbolStatus;
	DBSTATUS m_dwV_typeStatus;
	DBSTATUS m_dwD_initial_VolumeStatus;
	DBSTATUS m_dwD_order_priceStatus;
	DBSTATUS m_dwD_stop_lossStatus;
	DBSTATUS m_dwV_commectStatus;
	DBSTATUS m_dworder_modify_timeStatus;
	DBSTATUS m_dwV_ReasonStatus;
	DBSTATUS m_dwstatus_change_timeStatus;
	DBSTATUS m_dwV_stateStatus ;
	

	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!



	DBLENGTH m_dwPlugin_StatusLength;
	DBLENGTH m_dwV_LoginLength;
	DBLENGTH m_dwV_OrderLength;
	DBLENGTH m_dwDT_SetupTimeLength;
	DBLENGTH m_dwV_SymbolLength;
	DBLENGTH m_dwV_typeLength;
	DBLENGTH m_dwD_initial_VolumeLength;
	DBLENGTH m_dwD_order_priceLength;
	DBLENGTH m_dwD_stop_lossLength;
	DBLENGTH m_dwV_commectLength;
	DBLENGTH m_dworder_modify_timeLength;
	DBLENGTH m_dwV_ReasonLength;
	DBLENGTH m_dwstatus_change_timeLength;
	DBLENGTH m_dwV_stateLength;


	
	

	
// Column binding map
BEGIN_COLUMN_MAP(CTrade_orders)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_Plugin_Status, m_dwPlugin_StatusLength, m_dwPlugin_StatusStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_V_Login, m_dwV_LoginLength, m_dwV_LoginStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_V_Order, m_dwV_OrderLength, m_dwV_OrderStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_DT_SetupTime, m_dwDT_SetupTimeLength, m_dwDT_SetupTimeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5,  m_V_Symbol, m_dwV_SymbolLength, m_dwV_SymbolStatus)
		COLUMN_ENTRY_LENGTH_STATUS(6,  m_V_type, m_dwV_typeLength, m_dwV_typeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(7, m_D_initial_Volume, m_dwD_initial_VolumeLength, m_dwD_initial_VolumeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(8, m_D_order_price, m_dwD_order_priceLength, m_dwD_order_priceStatus)
		COLUMN_ENTRY_LENGTH_STATUS(9, m_D_stop_loss, m_dwD_stop_lossLength, m_dwD_stop_lossStatus)
		COLUMN_ENTRY_LENGTH_STATUS(10, m_V_commect, m_dwV_commectLength, m_dwV_commectStatus)
		COLUMN_ENTRY_LENGTH_STATUS(11, m_order_modify_time, m_dworder_modify_timeLength, m_dworder_modify_timeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(12, m_V_Reason, m_dwV_ReasonLength, m_dwV_ReasonStatus)
		COLUMN_ENTRY_LENGTH_STATUS(13, m_status_change_time, m_dwstatus_change_timeLength, m_dwstatus_change_timeStatus)		
		COLUMN_ENTRY_LENGTH_STATUS(14, m_V_state, m_dwV_stateLength, m_dwV_stateStatus)		
	END_COLUMN_MAP()
	
};