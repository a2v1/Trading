#include <atldbcli.h>
class CodeChangedTable
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
	TCHAR m_Opposite_Deal[50];
	TCHAR m_Deal_Time[50];
	TCHAR m_Symbol1[50];
	TCHAR m_Type2[50];
	double m_Volume1;
	double m_Price1;
	TCHAR m_Status1[50];


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
    DBSTATUS m_Opposite_Deal_s;
	DBSTATUS m_Deal_Time_s;
	DBSTATUS m_Symbol1_s;
	DBSTATUS m_Type2_s;
	DBSTATUS m_Volume1_s;
	DBSTATUS m_Price1_s;
	DBSTATUS m_Status1_s;

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
    DBLENGTH m_Opposite_Deal_l;
	DBLENGTH m_Deal_Time_l;
	DBLENGTH m_Symbol1_l;
	DBLENGTH m_Type2_l;
	DBLENGTH m_Volume1_l;
	DBLENGTH m_Price1_l;
	DBLENGTH m_Status1_l;

BEGIN_COLUMN_MAP(CodeChangedTable)
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
        COLUMN_ENTRY_LENGTH_STATUS(12, m_Opposite_Deal, m_Opposite_Deal_l, m_Opposite_Deal_s)
		COLUMN_ENTRY_LENGTH_STATUS(13,  m_Deal_Time, m_Deal_Time_l, m_Deal_Time_s)
		COLUMN_ENTRY_LENGTH_STATUS(14, m_Symbol1, m_Symbol1_l, m_Symbol1_s)
		COLUMN_ENTRY_LENGTH_STATUS(15,  m_Type2, m_Type2_l, m_Type2_s)
		COLUMN_ENTRY_LENGTH_STATUS(16, m_Volume1, m_Volume1_l, m_Volume1_s)
		COLUMN_ENTRY_LENGTH_STATUS(17,  m_Price1, m_Price1_l, m_Price1_s)
		COLUMN_ENTRY_LENGTH_STATUS(18,  m_Status1, m_Status1_l, m_Status1_s)
	END_COLUMN_MAP()	
};