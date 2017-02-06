//#include "stdafx.h"
#ifndef CTrade_HEADER
#define CTrade_HEADER
#include <atldbcli.h>
class CCredit_Table
{

public:
	TCHAR m_Credit[31];
	DBSTATUS m_dwCreditStatus;
	DBLENGTH m_dwCreditLength;	
// Column binding map
BEGIN_COLUMN_MAP(CCredit_Table)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_Credit , m_dwCreditLength, m_dwCreditStatus )		
	END_COLUMN_MAP()
	
};
#endif