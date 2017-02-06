//#include "stdafx.h"
#include <atldbcli.h>
class CT_Pre_Post_outstanding
{

public:
	TCHAR m_login[31];
	TCHAR m_symbol[31];
	double m_preval;
	double m_postval;

	
	DBSTATUS m_dwloginStatus;
	DBSTATUS m_dwsymbolStatus;
	DBSTATUS m_dwprevalStatus;
	DBSTATUS m_dwpostvalStatus;	

	DBLENGTH m_dwloginLength;
	DBLENGTH m_dwsymbolLength;
	DBLENGTH m_dwprevalLength;
	DBLENGTH m_dwpostvalLength;
	
// Column binding map
BEGIN_COLUMN_MAP(CT_Pre_Post_outstanding)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_login, m_dwloginLength, m_dwloginStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_symbol, m_dwsymbolLength, m_dwsymbolStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_preval, m_dwprevalLength, m_dwprevalStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_postval, m_dwpostvalLength, m_dwpostvalStatus)	
END_COLUMN_MAP()
	
};