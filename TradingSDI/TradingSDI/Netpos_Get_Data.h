//#include "stdafx.h"
#include <atldbcli.h>
class Netpos_Get_Data
{

public:
	TCHAR m_Login[31];
	TCHAR m_Name[50];
	TCHAR m_Symbol[31];
	TCHAR m_Pre_NetQty[31];
	TCHAR m_Diff_NetQty[31];
	TCHAR m_NetQty[31];
	TCHAR m_Average[31];
	TCHAR m_LastRate[31];
	TCHAR m_PL[30];
	TCHAR m_Type [31];
	TCHAR m_Balance[31];
	TCHAR m_LastUpdate[31];		
	TCHAR m_Client_Group[31];		
	TCHAR m_Client_Group1[31];		
	TCHAR m_Client_Group2[31];		

	TCHAR m_TotalTrade[20];
	TCHAR m_Checked_Time[20];
	TCHAR m_Remark1[50];
	TCHAR m_Remark2[50];

	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!
	
	DBSTATUS m_dwLoginStatus;
	DBSTATUS m_dwNameStatus;
	DBSTATUS m_dwSymbolStatus;
	DBSTATUS m_dwPre_NetQtyStatus;
	DBSTATUS m_dwDiff_NetQtyStatus;
	DBSTATUS m_dwNetQtyStatus;
	DBSTATUS m_dwAverageStatus;
	DBSTATUS m_dwLastRateStatus;
	DBSTATUS m_dwPLStatus;
	DBSTATUS m_dwTypeStatus;
	DBSTATUS m_dwBalanceStatus;
	DBSTATUS m_dwLastUpdateStatus;	
	DBSTATUS m_dwClient_GroupStatus;	
	DBSTATUS m_dwClient_Group1Status;	
	DBSTATUS m_dwClient_GroupS2tatus;	
	

	DBSTATUS m_TotalTradeStatus;
	DBSTATUS m_Checked_TimeStatus;
	DBSTATUS m_Remark1Status;
	DBSTATUS m_Remark2Status;

	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!



	DBLENGTH m_dwLoginLength;
	DBLENGTH m_dwNameLength;
	DBLENGTH m_dwSymbolLength;	
	DBLENGTH m_dwPre_NetQtyLength;
	DBLENGTH m_dwDiff_NetQtyLength;
	DBLENGTH m_dwNetQtyLength;
	DBLENGTH m_dwAverageLength;
	DBLENGTH m_dwLastRateLength;
	DBLENGTH m_dwPLLength;
	DBLENGTH m_dwTypeLength;
	DBLENGTH m_dwBalanceLength;
	DBLENGTH m_dwLastUpdateLength;

	DBLENGTH m_dwClient_GroupLength;
	DBLENGTH m_dwClient_Group1Length;
	DBLENGTH m_dwClient_GroupL2ength;
	
	DBLENGTH m_TotalTradeLength;
	DBLENGTH m_Checked_TimeLength;
	DBLENGTH m_Remark1Length;
	DBLENGTH m_Remark2Length;

	
	

	
// Column binding map
BEGIN_COLUMN_MAP(Netpos_Get_Data)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_Login, m_dwLoginLength, m_dwLoginStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_Name, m_dwNameLength, m_dwNameStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_Symbol, m_dwSymbolLength, m_dwSymbolStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_Pre_NetQty, m_dwPre_NetQtyLength, m_dwPre_NetQtyStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5,  m_Diff_NetQty, m_dwDiff_NetQtyLength, m_dwDiff_NetQtyStatus)
		COLUMN_ENTRY_LENGTH_STATUS(6,  m_NetQty, m_dwNetQtyLength, m_dwNetQtyStatus)
		COLUMN_ENTRY_LENGTH_STATUS(7,  m_Average, m_dwAverageLength, m_dwAverageStatus)
		COLUMN_ENTRY_LENGTH_STATUS(8,  m_LastRate, m_dwLastRateLength, m_dwLastRateStatus)
		COLUMN_ENTRY_LENGTH_STATUS(9,  m_PL, m_dwPLLength, m_dwPLStatus)
		COLUMN_ENTRY_LENGTH_STATUS(10,  m_Type, m_dwTypeLength, m_dwTypeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(11,  m_Balance, m_dwBalanceLength, m_dwBalanceStatus)
		COLUMN_ENTRY_LENGTH_STATUS(12,  m_LastUpdate, m_dwLastUpdateLength, m_dwLastUpdateStatus)		
		COLUMN_ENTRY_LENGTH_STATUS(13,  m_Client_Group, m_dwClient_GroupLength, m_dwClient_GroupStatus)
		COLUMN_ENTRY_LENGTH_STATUS(14,  m_Client_Group1, m_dwClient_Group1Length, m_dwClient_Group1Status)		
		COLUMN_ENTRY_LENGTH_STATUS(15,  m_Client_Group2, m_dwClient_GroupL2ength, m_dwClient_GroupS2tatus)


		COLUMN_ENTRY_LENGTH_STATUS(16,  m_TotalTrade, m_TotalTradeLength, m_TotalTradeStatus)		
		COLUMN_ENTRY_LENGTH_STATUS(17,  m_Checked_Time, m_Checked_TimeLength, m_Checked_TimeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(18,  m_Remark1, m_Remark1Length, m_Remark1Status)		
		COLUMN_ENTRY_LENGTH_STATUS(19,  m_Remark2, m_Remark2Length, m_Remark2Status)
	END_COLUMN_MAP()
	
};