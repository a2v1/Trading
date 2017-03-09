#include <atldbcli.h>
class CPassedBYMngrTable
{
public:
	TCHAR m_Section[50];
	TCHAR m_login[50];
	double m_Order;
	TCHAR m_Order_In_Time[50];
	INT64 m_Deal;
	TCHAR m_Symbol[50];
	TCHAR m_Type1[50];
	double m_Volume;
	double m_Price;
	TCHAR m_Comment[50];
	TCHAR m_Status[50];
	TCHAR m_Type[50];
	TCHAR m_SubType[50];
	TCHAR m_PassedTime[50];


	DBSTATUS  m_Section_s;
	DBSTATUS m_login_s;
	DBSTATUS m_Order_s;
	DBSTATUS m_Order_In_Time_s;
	DBSTATUS m_Deal_s;
	DBSTATUS m_Symbol_s;
	DBSTATUS m_Type1_s;
	DBSTATUS m_Volume_s;
	DBSTATUS m_Price_s;
	DBSTATUS m_Comment_s;
	DBSTATUS m_Status_s;
	DBSTATUS m_Type_s;
	DBSTATUS m_SubType_s;
	DBSTATUS m_PassedTime_s;
		
	DBLENGTH m_Section_l;
	DBLENGTH m_login_l;
	DBLENGTH m_Order_l;
	DBLENGTH m_Order_In_Time_l;
	DBLENGTH m_Deal_l;
	DBLENGTH m_Symbol_l;
	DBLENGTH m_Type1_l;
	DBLENGTH m_Volume_l;
	DBLENGTH m_Price_l;
	DBLENGTH m_Comment_l;
	DBLENGTH m_Status_l;
	DBLENGTH m_Type_l;
	DBLENGTH m_SubType_l;
	DBLENGTH m_PassedTime_l;

BEGIN_COLUMN_MAP(CPassedBYMngrTable)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_Section,m_Section_l , m_Section_s)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_login, m_login_l, m_login_s)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_Order, m_Order_l, m_Order_s)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_Order_In_Time, m_Order_In_Time_l, m_Order_In_Time_s)
		COLUMN_ENTRY_LENGTH_STATUS(5, m_Deal, m_Deal_l, m_Deal_s)
		COLUMN_ENTRY_LENGTH_STATUS(6, m_Symbol, m_Symbol_l, m_Symbol_s)
		COLUMN_ENTRY_LENGTH_STATUS(7, m_Type1, m_Type1_l, m_Type1_s)
		COLUMN_ENTRY_LENGTH_STATUS(8, m_Volume, m_Volume_l, m_Volume_s)
		COLUMN_ENTRY_LENGTH_STATUS(9, m_Price, m_Price_l, m_Price_s)
		COLUMN_ENTRY_LENGTH_STATUS(10,  m_Comment, m_Comment_l, m_Comment_s)
		COLUMN_ENTRY_LENGTH_STATUS(11,  m_Status,m_Status_l , m_Status_s)
		COLUMN_ENTRY_LENGTH_STATUS(12, m_Type, m_Type_l, m_Type_s)
		COLUMN_ENTRY_LENGTH_STATUS(13,  m_SubType, m_SubType_l, m_SubType_s)
		COLUMN_ENTRY_LENGTH_STATUS(14,  m_PassedTime, m_PassedTime_l, m_PassedTime_s)
	END_COLUMN_MAP()	
};