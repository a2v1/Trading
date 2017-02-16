#include "stdafx.h"
#include "PosEntryAna.h"
#include "document.h"
#include <iostream>
#include "Position_Entry_Analysis.h"
#include "GridTradeAndOrder.h"
#include "tab3.h"
#include <fstream>
using namespace std;
using namespace rapidjson;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
int PosEntryAna::insertFilterFlag=0;

PosEntryAna::PosEntryAna(void)
{
	UGXPThemes::UseThemes(false);
}


PosEntryAna::~PosEntryAna(void)
{
	UGXPThemes::CleanUp();
}

void PosEntryAna::Getdata(_bstr_t m_login)
{
	
	m_logfile.LogEvent(L"Start PosEntry Ana Grid ");
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<CPosition_Entry_Analysis> > artists1;	
	HRESULT hr;
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	session.Open(connection);
	
	
	 SetNumberRows(0);
			
	_bstr_t strCommand="select Deal,[Login],Symbol,Time,EntryVolume,EntryPrice from Position_Entry_Analysis where [login]='" + m_login + "'";		  
	    char* strCommand_char=(char*)strCommand;
		hr=artists1.Open(session,strCommand_char);	

		int rownumber=0;
	    if(SUCCEEDED(hr))
		 {
			while (artists1.MoveNext() == S_OK)
			 {				 
				 InsertRow(rownumber);
				 QuickSetText(0,rownumber,artists1.m_deal);
				 QuickSetText(1,rownumber,artists1.m_login );
				 QuickSetText(2,rownumber,artists1.m_symbol);
				 QuickSetText(3,rownumber,artists1.m_time);
				 QuickSetText(4,rownumber,artists1.m_EntryVolume);
				
				CString str=L"";
				str.Format(L"%.4f",artists1.m_EntryPrice);
				QuickSetText(5,rownumber,str );
				rownumber=rownumber+1;
			 }
			  artists1.Close();
		 }   
	
	
	 RedrawAll();
	 m_logfile.LogEvent(L"END PosEntry Ana Grid");
	
}
void PosEntryAna::OnSetup()
{
	CUGCell cell;
	GetGridDefault(&cell);
	SetGridDefault(&cell);
	EnableExcelBorders(FALSE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetUserSizingMode( TRUE  );

	
	InitMenu();
	// Create and set default font
	AddFont(L"Arial", -12, FW_NORMAL);
	AddFont(L"Arial", -12, FW_BOLD);
	SetDefFont(0);

	


	CDC * pDC;
	
	int iHeight;
	int i, j;
	
	pDC = GetDC( );
	
	iHeight = -MulDiv( 8, GetDeviceCaps( pDC->m_hDC, LOGPIXELSY), 72 );
	m_font.CreateFont( iHeight, 0, 0, 0, 400, 0, 0, 0, 0, 0, 0, 0, 0, _T( "MS Sans Serif" ) );
	
	ReleaseDC( pDC );

	SetDefFont( &m_font );
		
	GetGridDefault( &cell );
	cell.SetAlignment( UG_ALIGNCENTER | UG_ALIGNVCENTER );
	SetGridDefault( &cell );

	SetNumberCols( 6);
	m_iArrowIndex = AddCellType( &m_sortArrow );

	SetCurrentCellMode( 2 );

	UseHints( TRUE );

	SetSH_Width( 0 );
	//SetUniformRowHeight( TRUE );
	
// Start timers
	srand( (unsigned)time( NULL ) );
	SetTimer(0, 100, NULL);
	SetTimer(1, 100, NULL);

	

	QuickSetCellType( 0, -1, m_iArrowIndex );
	SortBy( 0, UG_SORT_ASCENDING );

	m_iSortCol = 0;
	m_bSortedAscending = TRUE;
}
void PosEntryAna::OnSheetSetup(int sheetNumber)
{
	int	nRow = 0, nCol = 0;
	EnableExcelBorders(TRUE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetDefFont(0);
	SetSH_Width(0);	
	SetNumberCols(6);

	QuickSetText(0,-1,L"Deal");
	SetColWidth(0,100);

	QuickSetText(1,-1,L"Login");
	SetColWidth(1,120);

	QuickSetText(2,-1,L"Symbol");	
	SetColWidth(2,120);
			
	QuickSetText(3,-1,L"Time");
	SetColWidth(3,130);

	QuickSetText(4,-1,L"EntryVolume");
	SetColWidth(4,130);

	QuickSetText(5,-1,L"EntryPrice");
	SetColWidth(5,120);

	for(int i = 0; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}	
}

void PosEntryAna::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
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

	int row_no=GetNumberRows();
	 for(int f=0;f<row_no;f++)
	 {
		 CString val=QuickGetText(0,f);
		 if(wcscmp( val,L"")==0)
		{
			DeleteRow(f);
	    }
	 }
  RedrawAll();
}
int PosEntryAna::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
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
		  if(cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;

case 1:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 3:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 4:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 5:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;

default:
		if( CString(cell1->GetText()) == "")
			return 1;
		else if( CString(cell2->GetText()) == "")
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
int PosEntryAna::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{

	if(ID == UGCT_DROPLIST){
		return OnDropList(ID, col, row, msg, param);
	}
}

int PosEntryAna::OnDropList(long ID,int col,long row,long msg,long param)
{
if(PosEntryAna::insertFilterFlag==1 && row==0 )
	{
		CString  strval=L"";
		CUGCell cell;
		GetCell(col,row,&cell);
		strval=cell.GetText();
		
		if (strval!=L"")
		{
			gridFilter(col,GetNumberRows(),strval);
		}
		else
		{
			gridFilter(GetNumberCols(),GetNumberRows(),L"ALL");
		}
		
	}
	RedrawAll();
	return true;
}

void PosEntryAna::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();
	
	EnableMenu(TRUE);
	
	menu->AppendMenuW(MF_STRING|MF_UNCHECKED,2001,_T("Filter"));
}
void PosEntryAna::OnMenuCommand(int col,long row,int section,int item)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(section);
	CMenu* pMenu;
	pMenu = GetPopupMenu();

switch( item )
{
case 2001:
	       {
				filter();
				break;
		   }
}
RedrawAll();
}

void PosEntryAna::filter()
{
	 CMenu *pMnenu;
	pMnenu= GetPopupMenu();

	if ( PosEntryAna::insertFilterFlag==0)
	{
			addItemToCombobox();
			PosEntryAna::insertFilterFlag=1;
			InsertRow(0);
			for (int col_count=0;col_count<6;col_count++)
			{
				CUGCell cell;
				int row=0;
				int col=col_count;
				cell.ClearAll();
				cell.SetCellType(UGCT_DROPLIST);
				cell.SetCellTypeEx(UGCT_DROPLISTHIDEBUTTON);
				cell.SetParam(CELLTYPE_IS_EDITABLE);
				QuickSetRange(col,row,col,row,&cell);
				QuickSetLabelText(col,row,str[col_count]);
			}
			pMnenu->CheckMenuItem(2001,MF_CHECKED);

	}
	else
	{
		
		DeleteRow(0);
		PosEntryAna::insertFilterFlag=0;
		pMnenu->CheckMenuItem(2001,MF_UNCHECKED);
	}
	RedrawAll();
 }

BOOLEAN  PosEntryAna::CheckvalueInArray(const CStringArray& arr,CString strval) 
{
	try
	{
	int arrcount=arr.GetCount();
    for (int forcount=0;forcount<arrcount;forcount++)
	{
		if (arr[forcount]==strval)
		{
			return true;
		}
                                                                                                                                                                                                                                                                                        	}
    return false  ;
	}
	catch(_com_error & ce)
			{
				AfxMessageBox(ce.Description()+L"CheckvalueInArray");			
			} 
}
 
void PosEntryAna::addItemToCombobox()
{
	CStringArray arr;
	CStringArray arr1;
	CStringArray arr2;
	CStringArray arr3;
	CStringArray arr4;
	CStringArray arr5;
	CStringArray arr6;
	
	try
	{
	int rows=1;
	rows=GetNumberRows();
	
	CString str_val=L"";
	
	for (int forcount=0;forcount<6;forcount++)
	{
		str[forcount]=L"ALL\n";		
	}
	for (int forcount=0;forcount<rows;forcount++)
	{
		for (int clocount=0;clocount<6;clocount++)
		{
			str_val=QuickGetText(clocount,forcount);
			str_val=str_val.Trim();
			
			if (str_val!=L"")
			{
				if (clocount==0)
				{
					if (CheckvalueInArray(arr,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr.Add(str_val);
					}
				}


				if (clocount==1)
				{
					if (CheckvalueInArray(arr1,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr1.Add(str_val);
					}
				}


				if (clocount==2)
				{
					if (CheckvalueInArray(arr2,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr2.Add(str_val);
					}
				}



				if (clocount==3)
				{
					if (CheckvalueInArray(arr3,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr3.Add(str_val);
					}
				}

				if (clocount==4)
				{
					if (CheckvalueInArray(arr4,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr4.Add(str_val);
					}
				}
				if (clocount==5)
				{
					if (CheckvalueInArray(arr5,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr5.Add(str_val);
					}
				}
				if (clocount==6)
				{
					if (CheckvalueInArray(arr6,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr6.Add(str_val);
					}
				}
			}

		}												
	}
	}
	catch(_com_error & ce)
			{
				AfxMessageBox(ce.Description()+L"addItemToCombobox");			
			} 
}

void PosEntryAna::gridFilter(int colno,int rows_count,CString col_value)
{
	
	CString getColvalue=L"";
	CString col_filter_val[7];
	
	for(int c=0;c<7;c++)
	{
		col_filter_val[c]=QuickGetText(c,0);
	}
	for(int fcount=rows_count-1;fcount>0;fcount--)
	{
		int flag=0;		
		
		CString col_row_val[7];
		for(int c=0;c<7;c++)
		{
			col_row_val[c]=QuickGetText(c,fcount);
		}
	  if((col_filter_val[0]==col_row_val[0] || col_filter_val[0]==L"ALL"||col_filter_val[0]==L"") && (col_filter_val[1]==col_row_val[1] || col_filter_val[1]==L"ALL"||col_filter_val[1]==L"") && (col_filter_val[2]==col_row_val[2] || col_filter_val[2]==L"ALL"||col_filter_val[2]==L"")  && (col_filter_val[3]==col_row_val[3] || col_filter_val[3]==L"ALL"||col_filter_val[3]==L"")  && (col_filter_val[4]==col_row_val[4] || col_filter_val[4]==L"ALL"||col_filter_val[4]==L"")   && (col_filter_val[5]==col_row_val[5] || col_filter_val[5]==L"ALL"||col_filter_val[5]==L"")&&(col_filter_val[6]==col_row_val[6] || col_filter_val[6]==L"ALL"||col_filter_val[6]==L""))
	   {			
			CString checkblakval=QuickGetText(0,fcount);
			checkblakval=checkblakval.Trim();
			if(checkblakval.Trim().GetLength()>0)
			{
				flag=1;
			}			
		}
		else
		{			
			flag=0;			
		}
		
	    if (flag==1)
		{
			SetRowHeight(fcount, 20);
		}
		else
		{   
			 SetRowHeight(fcount, 0);
		}
	 }
	
}
