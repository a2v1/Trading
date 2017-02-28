#ifndef CSymbol_MapTable
#define CSymbol_MapTable
#include <atldbcli.h>
class Symbol_MapTable
{

public:
	TCHAR m_Symbol[31];
	TCHAR m_mapping_Symbol[31];
		
	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!
	
	DBSTATUS m_dwSymbolStatus;
	DBSTATUS m_mapping_SymbolStatus;
	

	DBLENGTH m_dwSymbolLength;
	DBLENGTH m_dwmapping_SymbolLength;
	
// Column binding map
BEGIN_COLUMN_MAP(Symbol_MapTable)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_Symbol , m_dwSymbolLength, m_dwSymbolStatus )
		COLUMN_ENTRY_LENGTH_STATUS(2, m_mapping_Symbol, m_dwmapping_SymbolLength, m_mapping_SymbolStatus)
			
	END_COLUMN_MAP()
	
};
#endif