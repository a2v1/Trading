#include <atldbcli.h>
class CScripWiseNetPosTable
{
public:
	TCHAR m_Symnol[31];
	double m_NetQty;
	double m_Average;
	double m_LastRate;
	double m_PL;
	double m_remQTY;
	double m_remPL;
	
	DBSTATUS m_dwSymnolStatus;
	DBSTATUS m_dwNetQtyStatus;
	DBSTATUS m_dwAverageStatus;
	DBSTATUS m_dwLastRateStatus;
	DBSTATUS m_dwPLStatus;
	DBSTATUS m_remQTYStatus;
	DBSTATUS m_remPLStatus;
	
	DBLENGTH m_dwSymnolLength;
	DBLENGTH m_dwNetQtyLength;
	DBLENGTH m_dwAverageLength;	
	DBLENGTH m_dwLastRateLength;
	DBLENGTH m_dwPLLength;
	DBLENGTH m_remQTYLength;
	DBLENGTH m_remPLLength;
		

BEGIN_COLUMN_MAP(CScripWiseNetPosTable)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_Symnol, m_dwSymnolLength, m_dwSymnolStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_NetQty, m_dwNetQtyLength, m_dwNetQtyStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_Average, m_dwAverageLength, m_dwAverageStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_LastRate, m_dwLastRateLength, m_dwLastRateStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5,  m_PL, m_dwPLLength, m_dwPLStatus)		

		COLUMN_ENTRY_LENGTH_STATUS(6,  m_remQTY, m_remQTYLength, m_remQTYStatus)		
		COLUMN_ENTRY_LENGTH_STATUS(7,  m_remPL, m_remPLLength, m_remPLStatus)		
	END_COLUMN_MAP()	
};