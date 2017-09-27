#include "stdafx.h"
#include "HelpUserCleintGrid.h"


HelpUserCleintGrid::HelpUserCleintGrid(void)
{
}


HelpUserCleintGrid::~HelpUserCleintGrid(void)
{
}

void HelpUserCleintGrid::OnSetup()
{
	SetNumberCols(2);

	QuickSetText(0,-1,L"User LoginID");
	SetColWidth(0,120);

	QuickSetText(1,-1,L"Cleint ID");
	SetColWidth(1,120);

	m_iArrowIndex = AddCellType( &m_sortArrow );
	SetMultiSelectMode(TRUE);
	UseHints( TRUE );

	SetSH_Width( 0 );

	QuickSetCellType( 0, -1, m_iArrowIndex );
	SortBy( 0, UG_SORT_ASCENDING );

	m_iSortCol = 0;
	m_bSortedAscending = TRUE;

	//Display Data
	DisplayData();

}


void HelpUserCleintGrid::DisplayData()
{

	CoInitialize(NULL);
	CCommand<CAccessor<UserClient_Table> > artists1;	
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=64.251.7.161;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	if(SUCCEEDED(hr))
	{
	 hr=session.Open(connection);							
	}
	
	if(SUCCEEDED(hr))
	{
	    CString Str_command=L"";
		Str_command.Format(L"select v_Login_userid, v_cleintid from User_CleintMap");
		hr=artists1.Open(session,(LPCTSTR)Str_command);
		int rows_count=0;
		if(SUCCEEDED(hr))
		{
			while(hr=artists1.MoveNext() == S_OK)
			{
				InsertRow(rows_count);
				QuickSetText(0,rows_count,artists1.V_LoginUserID); 
			    QuickSetText(1,rows_count,artists1.V_ClientID ); 
				rows_count=rows_count+1;
			}
		
		}	
		RedrawAll();
		artists1.Close();
	}
	session.Close();
	connection.Close();
 	CoUninitialize();

}
