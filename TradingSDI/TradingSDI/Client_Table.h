//#include "stdafx.h"
#ifndef Client_Table_HEADER
#define Client_Table_HEADER
#include <atldbcli.h>
class Client_Table
{

public:
	TCHAR   V_login[64];
	TCHAR   V_Name[200];
	TCHAR   Comment_YN[64];
	TCHAR   Ignore_YN[64];
	TCHAR   client_group[64];
	TCHAR   Client_Group1[64];
	TCHAR   Client_Group2[64];
	TCHAR   Client_Group4[64];
	double   Client_Credit;
		
	
	
	DBSTATUS	s_V_login;
	DBSTATUS	s_V_Name;
	DBSTATUS	s_Comment_YN;
	DBSTATUS	s_Ignore_YN;
	DBSTATUS	s_client_group;
	DBSTATUS	s_Client_Group1;
	DBSTATUS	s_Client_Group2;
	DBSTATUS	s_Client_Group4;
	DBSTATUS	s_Client_Credit;		


	DBLENGTH 	l_V_login;
	DBLENGTH	l_V_Name;
	DBLENGTH	l_Comment_YN;
	DBLENGTH	l_Ignore_YN;
	DBLENGTH	l_client_group;
	DBLENGTH	l_Client_Group1;
	DBLENGTH	l_Client_Group2;
	DBLENGTH	l_Client_Group4;
	DBLENGTH	l_Client_Credit;
	

	
	

	
// Column binding map
BEGIN_COLUMN_MAP(Client_Table)
	COLUMN_ENTRY_LENGTH_STATUS(1,V_login,s_Client_Credit,l_V_login);
	COLUMN_ENTRY_LENGTH_STATUS(2,V_Name,s_Client_Credit,l_V_Name);
	COLUMN_ENTRY_LENGTH_STATUS(3,Comment_YN,s_Client_Credit,l_Comment_YN);
	COLUMN_ENTRY_LENGTH_STATUS(4,Ignore_YN,s_Client_Credit,l_Ignore_YN);
	COLUMN_ENTRY_LENGTH_STATUS(5,client_group,s_Client_Credit,l_client_group);
	COLUMN_ENTRY_LENGTH_STATUS(6,Client_Group1,s_Client_Credit,l_Client_Group1);
	COLUMN_ENTRY_LENGTH_STATUS(7,Client_Group2,s_Client_Credit,l_Client_Group2);
	COLUMN_ENTRY_LENGTH_STATUS(8,Client_Group4,s_Client_Credit,l_Client_Group4);
	COLUMN_ENTRY_LENGTH_STATUS(9,Client_Credit,s_Client_Credit,l_Client_Credit);							
END_COLUMN_MAP()
	
};
#endif