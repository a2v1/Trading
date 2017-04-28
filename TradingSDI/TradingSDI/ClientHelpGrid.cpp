#include "stdafx.h"
#include "ClientHelpGrid.h"
#include "resource.h"

int ClientHelpGrid::m_selectedclient =0;
const COLORREF white_colr=RGB(255,255,255);
const COLORREF red_colr=RGB(255,0,0);
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

	COLORREF colr=NULL;
	int cols=0,xx;
	cols = GetNumberCols(); 
	CString m_clientcode=L"";

	if(row>=0)
	{
		for (xx = 0; xx < cols; xx++)
		{ 
			GetCell(xx,row, &cell);
			if (updn==1)
			{
				processed=1;
				colr=cell.GetBackColor();
				if(colr==red_colr)
				{
					cell.SetBackColor(white_colr);
				}
				else
				{
					cell.SetBackColor(red_colr);
				}
			}

			if(xx==0)
			{
				m_clientcode=cell.GetText();
				colr=cell.GetBackColor();
				if(!m_clientcode.IsEmpty())
				{
					if(colr==red_colr)
					{
						CString str=L"";

						str=m_clientcode;

						m_clientlist.AddTail(str);
					}
					else
					{
						CString str=L"";
						POSITION pos;
						pos = m_clientlist.GetHeadPosition();
						while (pos)
						{
							if ( m_clientlist.GetNext(pos)==m_clientcode)
								str = m_clientcode;
						}

						if (!str.IsEmpty())
						{
							m_clientlist.RemoveAt(m_clientlist.Find(str));
						}
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
	COLORREF colr=NULL;
	int col,ro,rows,cols;
	rows=GetNumberRows();
	cols=GetNumberCols();
	for(col=0;col<cols;col++)
	{
		for(ro=0;ro<rows;ro++)
		{
			GetCell(col,ro,&cell);
			colr=cell.GetBackColor();
			if(colr==RGB(255,0,0))
			{
				DeleteRow(ro);
			}
		}
	}
	RedrawAll();
}


void ClientHelpGrid::OnMenuCommand(int col,long row,int section,int item)
{
	CString Str_command=L"";

	//Process (show) the items in the list.
	for( POSITION pos = m_clientlist.GetHeadPosition(); pos != NULL; )
	{
		ClientHelpGrid::m_selectedclient=1;
		CString newstr=L"";
		CString m_login= m_clientlist.GetNext(pos);
		newstr.Format(L"delete FROM [CHECKDATA].[dbo].[Client] where [V_login]='%s';",m_login );
		Str_command=Str_command+newstr;
	}
	if (Str_command.GetLength()>0)
	{	
		CCommand<CNoAccessor, CNoRowset>cmd;			
		hr=cmd.Open(session,LPCTSTR(Str_command));							 			 		 				 	
		cmd.Close();	
	}

	CString str_msg=L"";
	if(ClientHelpGrid::m_selectedclient==1)
	{
		str_msg=L"Client has been Deleted!!";
	}
	else
	{
		str_msg=L"Please Select Client You Want To Delete!!";
	}
	ClientHelpGrid::m_selectedclient=0;


	if(!m_clientlist.IsEmpty())
	{
		m_clientlist.RemoveAll();
	}
	delete_row();
	AfxMessageBox(str_msg);
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

