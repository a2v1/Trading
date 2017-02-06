#include <atldbcli.h>
class CSymbol_Table
{
public:
	
	TCHAR m_Symbol[64];
	TCHAR m_Mapping_Symbol[200];
	

	
	DBSTATUS        m_Symbol_Status;
	DBSTATUS        m_Mapping_Symbol_Status;
	
	


	DBLENGTH        m_Symbol_Length;
	DBLENGTH        m_Mapping_Symbol_Length;
	
// Column binding map
BEGIN_COLUMN_MAP(CSymbol_Table)		
		COLUMN_ENTRY_LENGTH_STATUS(1,m_Symbol,m_Symbol_Length,m_Symbol_Status); 
		COLUMN_ENTRY_LENGTH_STATUS(2,m_Mapping_Symbol,m_Mapping_Symbol_Length,m_Mapping_Symbol_Status);
		
	END_COLUMN_MAP()
	
};