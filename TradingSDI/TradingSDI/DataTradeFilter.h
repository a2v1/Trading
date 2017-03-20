//#include "stdafx.h"
#include <atldbcli.h>
class DataTradeFilter
{

public:
	TCHAR m_time[31];
	TCHAR m_order[31];
	TCHAR m_deal[31];
	TCHAR m_symbol[31];
	TCHAR m_Type[31];
	TCHAR m_volume[31];
	TCHAR m_price[31];
	TCHAR m_comment[31];
	TCHAR m_OurComment[30];
	TCHAR m_Checked[31];
	TCHAR m_CommentYN[31];
	TCHAR m_Opp_Deal[31];
	
	
	
	DBSTATUS m_time_status;
	DBSTATUS m_order_status;
	DBSTATUS m_deal_status;
	DBSTATUS m_symbol_status;
	DBSTATUS m_Type_status;
	DBSTATUS m_volume_status;
	DBSTATUS m_price_status;
	DBSTATUS m_comment_status;
	DBSTATUS m_OurComment_status;
	DBSTATUS m_Checked_status;
	DBSTATUS m_CommentYN_status;
	DBSTATUS m_Opp_Deal_status;
	
	
	DBLENGTH m_time_Length;
	DBLENGTH m_order_Length;
	DBLENGTH m_deal_Length;
	DBLENGTH m_symbol_Length;
	DBLENGTH m_Type_Length;
	DBLENGTH m_volume_Length;
	DBLENGTH m_price_Length;
	DBLENGTH m_comment_Length;
	DBLENGTH m_OurComment_Length;
	DBLENGTH m_Checked_Length;
	DBLENGTH m_CommentYN_Length;
	DBLENGTH m_Opp_Deal_Length;			

// Column binding map
BEGIN_COLUMN_MAP(DataTradeFilter)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_time, m_time_Length, m_time_status)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_order, m_order_Length, m_order_status)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_deal, m_deal_Length, m_deal_status)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_symbol, m_symbol_Length, m_symbol_status)
		COLUMN_ENTRY_LENGTH_STATUS(5,  m_Type, m_Type_Length, m_Type_status)
		COLUMN_ENTRY_LENGTH_STATUS(6,  m_volume, m_volume_Length, m_volume_status)
		COLUMN_ENTRY_LENGTH_STATUS(7, m_price, m_price_Length, m_price_status)
		COLUMN_ENTRY_LENGTH_STATUS(8, m_comment, m_comment_Length, m_comment_status)
		COLUMN_ENTRY_LENGTH_STATUS(9, m_OurComment, m_OurComment_Length, m_OurComment_status)
		COLUMN_ENTRY_LENGTH_STATUS(10, m_Checked, m_Checked_Length, m_Checked_status)		
		COLUMN_ENTRY_LENGTH_STATUS(11, m_CommentYN, m_CommentYN_Length, m_CommentYN_status )		
		COLUMN_ENTRY_LENGTH_STATUS(12, m_Opp_Deal, m_Opp_Deal_Length, m_Opp_Deal_status)		
	END_COLUMN_MAP()
	
};