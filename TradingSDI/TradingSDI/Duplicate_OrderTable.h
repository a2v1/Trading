#include <atldbcli.h>
#include "Grid_CheckTrade.h"
class Duplicate_OrderTable
{
public:
	TCHAR m_order[31];
	TCHAR m_deal[31];
	TCHAR m_login[31];
	TCHAR m_symbol[31];
	TCHAR m_volume[31];
	TCHAR m_price[31];
	
	DBSTATUS m_dworderStatus;
	DBSTATUS m_dwdealStatus;
	DBSTATUS m_dwloginStatus;
	DBSTATUS m_dwsymbolStatus;
	DBSTATUS m_dwvolumeStatus;
	DBSTATUS m_dwpriceStatus;
	
	DBLENGTH m_dworderLength;
	DBLENGTH m_dwdealLength;
	DBLENGTH m_dwloginLength;	
	DBLENGTH m_dwsymbolLength;
	DBLENGTH m_dwvolumeLength;
	DBLENGTH m_dwpriceLength;
		

BEGIN_COLUMN_MAP(Duplicate_OrderTable)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_order, m_dworderLength, m_dworderStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_deal, m_dwdealLength, m_dwdealStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_login, m_dwloginLength, m_dwloginStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_symbol, m_dwsymbolLength, m_dwsymbolStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5,  m_volume, m_dwvolumeLength, m_dwvolumeStatus)		
		COLUMN_ENTRY_LENGTH_STATUS(6,  m_price, m_dwpriceLength, m_dwpriceStatus)		
	END_COLUMN_MAP()	
};