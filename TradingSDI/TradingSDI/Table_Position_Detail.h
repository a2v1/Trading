//#include "stdafx.h"
#ifndef TABLE_POSITION_DETAIL_HEADER
#define TABLE_POSITION_DETAIL_HEADER
#include <atldbcli.h>
class CTable_Position_Detail
{

public:
	TCHAR m_Symbol[31];
	TCHAR m_Order[31];
	TCHAR m_Time[31];
	TCHAR m_Type[31];
	TCHAR m_Volume[31];
	TCHAR m_Price[31];
	TCHAR m_Current_Rate[31];
	TCHAR m_PL[31];
	TCHAR m_Status[30];
	TCHAR m_Trade_Checked[30];
	TCHAR m_Checked_Time[30];
	TCHAR m_Limit[30];
	TCHAR m_Remark2[100];
		
	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!
	
	DBSTATUS m_dwSymbolStatus;
	DBSTATUS m_dwOrderStatus;
	DBSTATUS m_dwTimeStatus;
	DBSTATUS m_dwTypeStatus;
	DBSTATUS m_dwVolumeStatus;
	DBSTATUS m_dwPriceStatus;
	DBSTATUS m_dwCurrent_RateStatus;
	DBSTATUS m_dwPLStatus;
	DBSTATUS m_dwStatusStatus;
	DBSTATUS m_dwTrade_CheckedStatus;
	DBSTATUS m_dwChecked_TimeStatus;
	DBSTATUS m_dwLimitStatus;
	DBSTATUS m_dwRemark2Status;
	
	

	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!



	DBLENGTH m_dwSymbolLength;
	DBLENGTH m_dwOrderLength;
	DBLENGTH m_dwTimeLength;
	DBLENGTH m_dwTypeLength;
	DBLENGTH m_dwVolumeLength;
	DBLENGTH m_dwPriceLength;
	DBLENGTH m_dwCurrent_RateLength;
	DBLENGTH m_dwPLLength;
	DBLENGTH m_dwStatusLength;
	DBLENGTH m_dwTrade_CheckedLength;
	DBLENGTH m_dwChecked_TimeLength;
	DBLENGTH m_dwLimitLength;
	DBLENGTH m_dwRemark2Length;
	

	
	

	
// Column binding map
BEGIN_COLUMN_MAP(CTable_Position_Detail)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_Symbol , m_dwSymbolLength, m_dwSymbolStatus )
		COLUMN_ENTRY_LENGTH_STATUS(2, m_Order, m_dwOrderLength, m_dwOrderStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_Time, m_dwTimeLength, m_dwTimeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_Type, m_dwTypeLength, m_dwTypeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5,  m_Volume, m_dwVolumeLength, m_dwVolumeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(6,  m_Price, m_dwPriceLength, m_dwPriceStatus)
		COLUMN_ENTRY_LENGTH_STATUS(7, m_Current_Rate, m_dwCurrent_RateLength, m_dwCurrent_RateStatus)
		COLUMN_ENTRY_LENGTH_STATUS(8, m_PL, m_dwPLLength, m_dwPLStatus)
		COLUMN_ENTRY_LENGTH_STATUS(9, m_Status, m_dwStatusLength, m_dwStatusStatus)		
		COLUMN_ENTRY_LENGTH_STATUS(10, m_Trade_Checked, m_dwTrade_CheckedLength, m_dwTrade_CheckedStatus)
		COLUMN_ENTRY_LENGTH_STATUS(11, m_Checked_Time , m_dwChecked_TimeLength , m_dwChecked_TimeStatus )		
		COLUMN_ENTRY_LENGTH_STATUS(12, m_Limit , m_dwLimitLength, m_dwLimitStatus)		
		COLUMN_ENTRY_LENGTH_STATUS(13, m_Remark2 , m_dwRemark2Length, m_dwRemark2Status)		
	END_COLUMN_MAP()
	
};
#endif