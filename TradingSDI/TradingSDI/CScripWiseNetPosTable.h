#include <atldbcli.h>
class CScripWiseNetPosTable
{
public:
	TCHAR m_Symnol[31];
	double m_NetQty;
	double m_Average;
	double m_LastRate;
	double m_PL;
	
	DBSTATUS m_dwSymnolStatus;
	DBSTATUS m_dwNetQtyStatus;
	DBSTATUS m_dwAverageStatus;
	DBSTATUS m_dwLastRateStatus;
	DBSTATUS m_dwPLStatus;
	
	DBLENGTH m_dwSymnolLength;
	DBLENGTH m_dwNetQtyLength;
	DBLENGTH m_dwAverageLength;	
	DBLENGTH m_dwLastRateLength;
	DBLENGTH m_dwPLLength;
		

BEGIN_COLUMN_MAP(CScripWiseNetPosTable)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_Symnol, m_dwSymnolLength, m_dwSymnolStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_NetQty, m_dwNetQtyLength, m_dwNetQtyStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_Average, m_dwAverageLength, m_dwAverageStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_LastRate, m_dwLastRateLength, m_dwLastRateStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5,  m_PL, m_dwPLLength, m_dwPLStatus)		
	END_COLUMN_MAP()	
};