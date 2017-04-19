#include "stdafx.h"
#include "ClientHelpGrid.h"
#include "resource.h"

COLORREF ClientHelpGrid::my_Color=NULL;
BOOL ClientHelpGrid::m_click=FALSE;
//BOOL  ClientHelpGrid::m_checkvalue=false;  
ClientHelpGrid::ClientHelpGrid(void)
{
}


ClientHelpGrid::~ClientHelpGrid(void)
{
	//	delete	m_clientForm;
}

void ClientHelpGrid::OnSetup()
{
	SetNumberCols(9);
	//SetNumberRows(10);
	//data base connection specify
	CoInitialize(NULL);		
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");			
	if(SUCCEEDED(hr))
	{
		hr=session.Open(connection);							
	}


	m_iArrowIndex = AddCellType( &m_sortArrow );

	//	SetCurrentCellMode( 2 );
	SetMultiSelectMode(TRUE);
	UseHints( TRUE );

	SetSH_Width( 0 );

	QuickSetCellType( 0, -1, m_iArrowIndex );
	SortBy( 0, UG_SORT_ASCENDING );

	m_iSortCol = 0;
	m_bSortedAscending = TRUE;

	InitMenu();
	EnableMenu(TRUE);







}


/*void ClientHelpGrid::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
StartEdit();
}*/	

void ClientHelpGrid::OnLClicked(int col,long row,int updn, RECT *rect,POINT *point,int processed)
{ 


	int cols=0,xx;
	cols = GetNumberCols(); 
	CString m_clientcode=L"";

	if(row>=0)
	{
		for (xx = 0; xx < cols; xx++)
		{ 
			//processed=1;
			GetCell(xx,row, &cell);
			if (updn==1)
			{

				if(cell.GetBackColor()==RGB(255,0,0))
				{
					cell.SetBackColor(RGB(255,255,255));
				}
				else
				{
					cell.SetBackColor(RGB(255,0,0));
				}
			}
			ClientHelpGrid::my_Color= cell.GetBackColor();
			if(xx==0)
			{
				m_clientcode=cell.GetText();
				if(ClientHelpGrid::my_Color==RGB(255,0,0))
				{
					//m_clientlist.AddHead(m_clientcode);

					POSITION pos = m_list.GetHeadPosition();

					if (pos == NULL)
						m_list.AddTail(&m_clientcode);
					else
						m_list.InsertBefore(pos,&m_clientcode);



					//m_list.AddTail(&m_clientcode);
				}
				else
				{
					//POSITION position = m_list.GetHeadPosition();
					POSITION pos = m_list.Find(&m_clientcode);





					if(pos!=NULL)
					{
						POSITION temp = pos;
						m_list.GetNext(pos);
						CString* str=(CString*) m_list.GetAt(temp);
						m_list.RemoveAt(temp);
					}
				}
			}
			SetCell(xx,row,&cell);
		    RedrawCell(xx,row);
		}
	}
	RedrawAll(); 

} 



int ClientHelpGrid::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
{

	if( flags & UG_SORT_DESCENDING )
	{
		CUGCell *ptr = cell1;
		cell1 = cell2;
		cell2 = ptr;
	}
	int retVal = 0;

	switch ( m_iSortCol )
	{
	case 0:
		if( cell1->GetNumber() < cell2->GetNumber())
			retVal = -1;
		if( cell1->GetNumber() > cell2->GetNumber())
			retVal = 1;

		break;
	case 8:
		if( cell1->GetNumber() < cell2->GetNumber())
			retVal = -1;
		if( cell1->GetNumber() > cell2->GetNumber())
			retVal = 1;

		break;



	default:
		if( CString(cell1->GetText()) == "" )
			return 1;
		else if( CString(cell2->GetText()) == "" )
			return -1;

		switch( cell1->GetDataType() )
		{
		case UGCELLDATA_NUMBER:
		case UGCELLDATA_BOOL:
		case UGCELLDATA_CURRENCY:
			if( cell1->GetNumber() < cell2->GetNumber())
				retVal = -1;
			if( cell1->GetNumber() > cell2->GetNumber())
				retVal = 1;

			break;

		default:
			retVal = _tcscmp( cell1->GetText( ), cell2->GetText());
		}
	}

	return retVal;

}
void ClientHelpGrid::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();

	EnableMenu(TRUE);

	menu->AppendMenuW(MF_STRING,2001,_T("Delete"));

	SetMenu(menu);


}
void ClientHelpGrid::delete_row()
{
	int x,y,cols,rows;
	cols=GetNumberCols();
	rows=GetNumberRows();
	for(y=0;y<cols;y++)
	{
		for(x=0;x<rows;x++)
		{
			GetCell(y,x,&cell);
			if(cell.GetBackColor()==RGB(255,0,0))
			{
				DeleteRow(x);
			}
		}
	}

}


void ClientHelpGrid::OnMenuCommand(int col,long row,int section,int item)
{

	CString Str_command=L"";

	//Process (show) the items in the list.
	for( POSITION pos = m_list.GetHeadPosition(); pos != NULL; )
	{
		CString newstr=L"";
		CString* m_login= (CString*)m_list.GetAt(pos);

		newstr.Format(L"delete FROM [CHECKDATA].[dbo].[Client] where [V_login]='%s';",m_login );
		Str_command=Str_command+newstr;

	}
	if (Str_command.GetLength()>0)
	{	
		CCommand<CNoAccessor, CNoRowset>cmd;			
		hr=cmd.Open(session,LPCTSTR(Str_command));							 			 		 				 	
		cmd.Close();	
	}


	delete_row();
	AfxMessageBox(L"Client has been Deleted");
	RedrawAll();


}


void ClientHelpGrid::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{	
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);

	if( updn == 0)
		return;

	QuickSetCellType( m_iSortCol, -1, 0 );

	if( col == m_iSortCol )
	{
		if( m_bSortedAscending )
			m_bSortedAscending = FALSE;
		else
			m_bSortedAscending = TRUE;
	}
	else
	{
		m_iSortCol = col;
		m_bSortedAscending = TRUE;
	}

	if( m_bSortedAscending )
	{
		SortBy( col, UG_SORT_ASCENDING );
		QuickSetCellType( m_iSortCol, -1, m_iArrowIndex );
		QuickSetCellTypeEx( m_iSortCol, -1, UGCT_SORTARROWDOWN );

	}
	else
	{
		SortBy( col, UG_SORT_DESCENDING );
		QuickSetCellType( m_iSortCol, -1, m_iArrowIndex );
		QuickSetCellTypeEx( m_iSortCol, -1, UGCT_SORTARROWUP );

	}


	RedrawAll();
}

