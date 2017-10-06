//#include "stdafx.h"
#ifndef UserClient_Table_HEADER
#define UserClient_Table_HEADER
#include <atldbcli.h>
class UserClient_Table
{

public:
	TCHAR   V_LoginUserID[31];
	TCHAR   V_ClientID[31];
	
		
	DBSTATUS	V_S_LoginUserID;
	DBSTATUS	V_S_ClientID;
	
	DBLENGTH 	l_V_LoginUserID;
	DBLENGTH	l_V_ClientID;
	
	
// Column binding map
BEGIN_COLUMN_MAP(UserClient_Table)
	COLUMN_ENTRY_LENGTH_STATUS(1,V_LoginUserID,l_V_LoginUserID,V_S_LoginUserID);
	COLUMN_ENTRY_LENGTH_STATUS(2,V_ClientID,l_V_ClientID,V_S_ClientID);	
END_COLUMN_MAP()
	
};
#endif