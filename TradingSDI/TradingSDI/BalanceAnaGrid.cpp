#include "stdafx.h"
#include "BalanceAnaGrid.h"
#include "document.h"
#include <iostream>
#include "BalanceTableAnalysis.h"
#include "GridTradeAndOrder.h"
using namespace std;
using namespace rapidjson;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
int BalanceAnaGrid::insertFilterFlag=0;

//Structure variable
BalanceAnaGrid::st_grid_balanalysis_array BalanceAnaGrid::m_st_grid_anlysis_Array_Fill;
BalanceAnaGrid::st_grid_balanalysis_array BalanceAnaGrid::m_st_grid_anlysis_Grid_array;

BalanceAnaGrid::st_grid_balanalysis BalanceAnaGrid::m_st_grid_anlysis={};

int BalanceAnaGrid::m_selectedclient =0;
BalanceAnaGrid::BalanceAnaGrid(void)
{
	UGXPThemes::UseThemes(false);
}


BalanceAnaGrid::~BalanceAnaGrid(void)
{
	UGXPThemes::CleanUp();
}

void BalanceAnaGrid::GetData(_bstr_t m_login)
{
	logfile.LogEvent(L"Start Balance Grid ");
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<CBalanceTableAnalysis> > artists1;	
	HRESULT hr;
	
	
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	hr=session.Open(connection);

	  _bstr_t strCommand ="";
	  strCommand="select [Login],Deal,[Time],[Order],Symbol,EntryAction,EntryVolume,EntryPrice,ExitDeal,ExitTime,ExitOrder,ExitAction,ExitVolume,ExitPrice,ProfitPoint_L,ProfitPoint_P,Multiplayer,Balance,potentialprofitpoint,PotentialLosspoint,DurationTime,high,low from BalanceTableAnalysis where [login]='" + m_login + "'";
		
	  hr=artists1.Open(session,(LPCTSTR)strCommand);	

		 if(SUCCEEDED(hr))
		 {
			
			 BalanceAnaGrid::m_st_grid_anlysis_Array_Fill.Clear();
			 while (artists1.MoveNext() == S_OK)
			 {

				BalanceAnaGrid::m_selectedclient=1;
				LPTSTR endPtr;
				CString price=L"";
				CString exit_price=L"";
				CString ProfitPoint_L=L"";
				CString ProfitPoint_P=L"";
				CString Multiplayer=L"";
				CString Balance=L"";
				CString potentialprofitpoint=L"";
				CString PotentialLosspoint=L"";
				CString DurationTime=L"";
				CString high=L"";
				CString low=L"";

				double d_price = _tcstod(artists1.m_EntryPrice, &endPtr);												
				price.Format(_T("%.2f"),d_price);	

				double d_exit_price = _tcstod(artists1.m_ExitPrice, &endPtr);												
				exit_price.Format(_T("%.2f"),d_price);

				double d_ProfitPoint_L = _tcstod(artists1.m_ProfitPoint_L, &endPtr);												
				ProfitPoint_L.Format(_T("%.2f"),d_price);

				double d_ProfitPoint_P = _tcstod(artists1.m_ProfitPoint_P, &endPtr);												
				ProfitPoint_P.Format(_T("%.2f"),d_price);

				double d_Multiplayer = _tcstod(artists1.m_Multiplayer, &endPtr);												
				Multiplayer.Format(_T("%.2f"),d_price);

				double d_Balance = _tcstod(artists1.m_Balance, &endPtr);												
				Balance.Format(_T("%.2f"),d_price);

				double d_potentialprofitpoint = _tcstod(artists1.m_potentialprofitpoint, &endPtr);												
				potentialprofitpoint.Format(_T("%.2f"),d_price);

				double d_PotentialLosspoint = _tcstod(artists1.m_PotentialLosspoint, &endPtr);												
				PotentialLosspoint.Format(_T("%.2f"),d_price);

				double d_DurationTime = _tcstod(artists1.m_DurationTime, &endPtr);												
				DurationTime.Format(_T("%.2f"),d_price);

				double d_high = _tcstod(artists1.m_high, &endPtr);												
				high.Format(_T("%.2f"),d_price);

				double d_low = _tcstod(artists1.m_low, &endPtr);												
				low.Format(_T("%.2f"),d_price);
				
				BalanceAnaGrid::st_grid_balanalysis m_st={};
			
				CMTStr::Copy(m_st.m_login ,artists1.m_Login);
				CMTStr::Copy(m_st.m_deal,artists1.m_deal);
				CMTStr::Copy(m_st.m_time ,artists1.m_Time);
				CMTStr::Copy(m_st.m_Order ,artists1.m_Order);
				CMTStr::Copy(m_st.m_symbol,artists1.m_Symbol);
				CMTStr::Copy(m_st.m_EntryAction,artists1.m_EntryAction);


				CMTStr::Copy(m_st.m_EntryVolume ,artists1.m_EntryVolume);
				CMTStr::Copy(m_st.m_Entryprice,price);
				CMTStr::Copy(m_st.m_ExitDeal ,artists1.m_ExitDeal);
				CMTStr::Copy(m_st.m_ExitTime ,artists1.m_ExitTime);
				CMTStr::Copy(m_st.m_ExitOrder,artists1.m_ExitOrder);
				CMTStr::Copy(m_st.m_ExitAction,artists1.m_ExitAction);

				
				CMTStr::Copy(m_st.m_ExitVolume ,artists1.m_ExitVolume);
				CMTStr::Copy(m_st.m_ExitPrice,exit_price);
				CMTStr::Copy(m_st.m_ProfitPoint_L ,ProfitPoint_L);
				CMTStr::Copy(m_st.m_ProfitPoint_P ,ProfitPoint_P);
				CMTStr::Copy(m_st.m_Multiplayer,Multiplayer);
				CMTStr::Copy(m_st.m_Balance,Balance);


				CMTStr::Copy(m_st.m_potentialprofitpoint ,potentialprofitpoint);
				CMTStr::Copy(m_st.m_DurationTime,PotentialLosspoint);
				CMTStr::Copy(m_st.m_high ,high);
				CMTStr::Copy(m_st.m_low ,low);

				BalanceAnaGrid::m_st_grid_anlysis_Array_Fill.Add(&m_st);
			 }
         }   

		  if(BalanceAnaGrid::m_selectedclient==0)
		  {
		      
		    AfxMessageBox(L"Data Not Found");
		  }
		  BalanceAnaGrid::m_selectedclient=0;

		  //ASSINGNING into main array
		  BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Assign(BalanceAnaGrid::m_st_grid_anlysis_Array_Fill);

	    //adding rows set rows
		RefreshGrid();


    artists1.Close();   
	session.Close();
	connection.Close();
	RedrawAll();
	logfile.LogEvent(L"END Balance Grid ");
}

void BalanceAnaGrid::RefreshGrid()
{
	int r_count=BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Total();

		int grid_total=GetNumberRows();
		if (BalanceAnaGrid::insertFilterFlag==1)
		{
			r_count=r_count+1;
		}		
		if (grid_total!=r_count)
		{			
			SetNumberRows(r_count);		
		}
		else
		{			
			RedrawAll();			
		}

}
void BalanceAnaGrid::OnSetup()
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

	SetNumberCols( 24);
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

int BalanceAnaGrid::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{

	if(ID == UGCT_DROPLIST){
		return OnDropList(ID, col, row, msg, param);
	}
}

int BalanceAnaGrid::OnDropList(long ID,int col,long row,long msg,long param)
{
if(BalanceAnaGrid::insertFilterFlag==1 && row==0 )
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
	


void BalanceAnaGrid::OnSheetSetup(int sheetNumber)
{
	int	nRow = 0, nCol = 0;
	EnableExcelBorders(TRUE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetDefFont(0);
	SetSH_Width(0);	
	SetNumberCols(23);

	QuickSetText(0,-1,L"Login");
	SetColWidth(0,100);

	QuickSetText(1,-1,L"Deal");
	SetColWidth(1,100);

	QuickSetText(2,-1,L"Time");	
	SetColWidth(2,120);
			
	QuickSetText(3,-1,L"Order");
	SetColWidth(3,120);

	QuickSetText(4,-1,L"Symbol");
	SetColWidth(4,100);

	QuickSetText(5,-1,L"EntryAction");
	SetColWidth(5,100);
	QuickSetText(6,-1,L"EntryVolume");
	SetColWidth(6,100);

	QuickSetText(7,-1,L"EntryPrice");
	SetColWidth(7,100);

	QuickSetText(8,-1,L"ExitDeal");	
	SetColWidth(8,100);
			
	QuickSetText(9,-1,L"ExitTime");
	SetColWidth(9,120);

	QuickSetText(10,-1,L"ExitOrder");
	SetColWidth(10,110);

	QuickSetText(11,-1,L"ExitAction");
	SetColWidth(11,120);
	QuickSetText(12,-1,L"ExitVolume");
	SetColWidth(12,100);

	QuickSetText(13,-1,L"ExitPrice");
	SetColWidth(13,120);

	QuickSetText(14,-1,L"ProfitPoint_L");	
	SetColWidth(14,120);
			
	QuickSetText(15,-1,L"ProfitPoint_P");
	SetColWidth(15,120);

	QuickSetText(16,-1,L"Multiplayer");
	SetColWidth(16,130);

	QuickSetText(17,-1,L"Balance");
	SetColWidth(17,120);
	QuickSetText(18,-1,L"PotentialProfitPoint");	
	SetColWidth(18,120);
			
	QuickSetText(19,-1,L"PotentialLossPoint");
	SetColWidth(19,130);

	QuickSetText(20,-1,L"TimeDuration");
	SetColWidth(20,130);

	QuickSetText(21,-1,L"High");
	SetColWidth(21,120);
    QuickSetText(22,-1,L"Low");
	SetColWidth(22,120);



	for(int i = 0; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}	
}

void BalanceAnaGrid::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
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
int BalanceAnaGrid::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
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

case 1:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 2:
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

case 5:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 6:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 7:
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
case 9:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 10:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 12:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 11:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;

case 13:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 14:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 16:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 17:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 18:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 19:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 20:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 21:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 22:
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
void BalanceAnaGrid::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();
	
	EnableMenu(TRUE);
	
	menu->AppendMenuW(MF_STRING|MF_UNCHECKED,2001,_T("Filter"));
}
void BalanceAnaGrid::OnMenuCommand(int col,long row,int section,int item)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(section);
	// init. local variables
	
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

void BalanceAnaGrid::filter()
{
	 CMenu *pMnenu;
	pMnenu= GetPopupMenu();

	if ( BalanceAnaGrid::insertFilterFlag==0)
	{
			addItemToCombobox();
			BalanceAnaGrid::insertFilterFlag=1;
			InsertRow(0);
			for (int col_count=0;col_count<23;col_count++)
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
		BalanceAnaGrid::insertFilterFlag=0;
		pMnenu->CheckMenuItem(2001,MF_UNCHECKED);
	}
	RedrawAll();
 }

BOOLEAN  BalanceAnaGrid::CheckvalueInArray(const CStringArray& arr,CString strval) 
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
 
void BalanceAnaGrid::addItemToCombobox()
{
	CStringArray arr;
	CStringArray arr1;
	CStringArray arr2;
	CStringArray arr3;
	CStringArray arr4;
	CStringArray arr5;
	CStringArray arr6;
	CStringArray arr7;
	CStringArray arr8;
	CStringArray arr9;
	CStringArray arr10;
	CStringArray arr11;
	CStringArray arr12;
	CStringArray arr13;
	CStringArray arr14;
	CStringArray arr15;
	CStringArray arr16;
	CStringArray arr17;
	CStringArray arr18;
	CStringArray arr19;
	CStringArray arr20;
	CStringArray arr21;
	CStringArray arr22;

	try
	{
	int rows=1;
	rows=GetNumberRows();
	
	CString str_val=L"";
	
	for (int forcount=0;forcount<24;forcount++)
	{
		str[forcount]=L"ALL\n";		
	}
	for (int forcount=0;forcount<rows;forcount++)
	{
		for (int clocount=0;clocount<24;clocount++)
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
				if (clocount==7)
				{
					if (CheckvalueInArray(arr7,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr7.Add(str_val);
					}
				}
				if (clocount==8)
				{
					if (CheckvalueInArray(arr8,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr8.Add(str_val);
					}
				}
				if (clocount==9)
				{
					if (CheckvalueInArray(arr9,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr9.Add(str_val);
					}
				}
				if (clocount==10)
				{
					if (CheckvalueInArray(arr10,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr10.Add(str_val);
					}
				}
				if (clocount==11)
				{
					if (CheckvalueInArray(arr11,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr11.Add(str_val);
					}
				}
				if (clocount==12)
				{
					if (CheckvalueInArray(arr12,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr12.Add(str_val);
					}
				}
				if (clocount==13)
				{
					if (CheckvalueInArray(arr13,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr13.Add(str_val);
					}
				}
				if (clocount==14)
				{
					if (CheckvalueInArray(arr14,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr14.Add(str_val);
					}
				}
				if (clocount==15)
				{
					if (CheckvalueInArray(arr15,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr15.Add(str_val);
					}
				}
				if (clocount==16)
				{
					if (CheckvalueInArray(arr16,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr16.Add(str_val);
					}
				}
				if (clocount==17)
				{
					if (CheckvalueInArray(arr17,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr17.Add(str_val);
					}
				}
				if (clocount==18)
				{
					if (CheckvalueInArray(arr18,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr18.Add(str_val);
					}
				}
				if (clocount==19)
				{
					if (CheckvalueInArray(arr19,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr19.Add(str_val);
					}
				}
				if (clocount==20)
				{
					if (CheckvalueInArray(arr20,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr20.Add(str_val);
					}
				}
				if (clocount==21)
				{
					if (CheckvalueInArray(arr21,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr21.Add(str_val);
					}
				}
				if (clocount==22)
				{
					if (CheckvalueInArray(arr22,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr22.Add(str_val);
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

void BalanceAnaGrid::gridFilter(int colno,int rows_count,CString col_value)
{
	
	CString getColvalue=L"";
	CString col_filter_val[23];
	
	for(int c=0;c<23;c++)
	{
		col_filter_val[c]=QuickGetText(c,0);
	}
	for(int fcount=rows_count-1;fcount>0;fcount--)
	{
		int flag=0;		
		
		CString col_row_val[23];
		for(int c=0;c<23;c++)
		{
			col_row_val[c]=QuickGetText(c,fcount);
		}
		if((col_filter_val[0]==col_row_val[0] || col_filter_val[0]==L"ALL"||col_filter_val[0]==L"") && (col_filter_val[1]==col_row_val[1] || col_filter_val[1]==L"ALL"||col_filter_val[1]==L"") && (col_filter_val[2]==col_row_val[2] || col_filter_val[2]==L"ALL"||col_filter_val[2]==L"")  && (col_filter_val[3]==col_row_val[3] || col_filter_val[3]==L"ALL"||col_filter_val[3]==L"")  && (col_filter_val[4]==col_row_val[4] || col_filter_val[4]==L"ALL"||col_filter_val[4]==L"")   && (col_filter_val[5]==col_row_val[5] || col_filter_val[5]==L"ALL"||col_filter_val[5]==L"")   && (col_filter_val[6]==col_row_val[6] || col_filter_val[6]==L"ALL"||col_filter_val[6]==L"")   && (col_filter_val[7]==col_row_val[7] || col_filter_val[7]==L"ALL"||col_filter_val[7]==L"")   && (col_filter_val[8]==col_row_val[8] || col_filter_val[8]==L"ALL"||col_filter_val[8]==L"") && (col_filter_val[9]==col_row_val[9] || col_filter_val[9]==L"ALL"||col_filter_val[9]==L"") &&(col_filter_val[10]==col_row_val[10] || col_filter_val[10]==L"ALL"||col_filter_val[10]==L"")&&(col_filter_val[11]==col_row_val[11] || col_filter_val[11]==L"ALL"||col_filter_val[11]==L"")&&(col_filter_val[12]==col_row_val[12] || col_filter_val[12]==L"ALL"||col_filter_val[12]==L"") &&(col_filter_val[13]==col_row_val[13] || col_filter_val[13]==L"ALL"||col_filter_val[13]==L"")&&(col_filter_val[14]==col_row_val[14] || col_filter_val[14]==L"ALL"||col_filter_val[14]==L"")&&(col_filter_val[15]==col_row_val[15] || col_filter_val[15]==L"ALL"||col_filter_val[15]==L"")&&(col_filter_val[16]==col_row_val[16] || col_filter_val[16]==L"ALL"||col_filter_val[16]==L"")&&(col_filter_val[17]==col_row_val[17] || col_filter_val[17]==L"ALL"||col_filter_val[17]==L"")&&(col_filter_val[18]==col_row_val[18] || col_filter_val[18]==L"ALL"||col_filter_val[18]==L"")&&(col_filter_val[19]==col_row_val[19] || col_filter_val[19]==L"ALL"||col_filter_val[19]==L"")&&(col_filter_val[20]==col_row_val[20] || col_filter_val[20]==L"ALL"||col_filter_val[20]==L"")&&(col_filter_val[21]==col_row_val[21] || col_filter_val[21]==L"ALL"||col_filter_val[21]==L"")&&(col_filter_val[22]==col_row_val[22] || col_filter_val[22]==L"ALL"||col_filter_val[22]==L""))
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

void BalanceAnaGrid::OnGetCell(int col,long row,CUGCell *cell)
{		
		//m_logfile_g.LogEvent(L"Start OnGetCell");
	    BalanceAnaGrid::st_grid_balanalysis mst_grid={};

        int rows_no=0;
		rows_no=row;		
		UNREFERENCED_PARAMETER(col);
		UNREFERENCED_PARAMETER(row);
		UNREFERENCED_PARAMETER(*cell);		
		if ( col >= 0 && row == -1 )
		{	
		}
		else if ( row >= 0 && col == -1 )
		{	
		}
		else if ( col >= 0 && row >= 0 )
		{
			if (BalanceAnaGrid::insertFilterFlag==1)
			{
				rows_no=row-1;				
				if (row==0)
				{
					return;
				}
			}
			if (col==0)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_login;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}

			else if (col==1)
			{

				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];				
				CString tmp=mst_grid.m_deal;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==2)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_time ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
				
			}
			else if (col==3)
			{	
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_Order ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}


			else if (col==4)
			{	
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_symbol ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==5)
			{				
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_EntryAction;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==6)
			{				
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_EntryVolume  ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}


			//////////////////////////////
			else if (col==7)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_Entryprice;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}

			else if (col==8)
			{

				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];				
				CString tmp=mst_grid.m_ExitDeal;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==9)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_ExitTime ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
				
			}
			else if (col==10)
			{	
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_ExitOrder ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==11)
			{				
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_ExitAction;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==12)
			{				
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_ExitVolume  ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}

			////////////////////////////////////
			else if (col==13)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_ExitPrice;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}

			else if (col==14)
			{

				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];				
				CString tmp=mst_grid.m_ProfitPoint_L;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==15)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_ProfitPoint_P ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
				
			}
			else if (col==16)
			{	
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_Multiplayer ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==17)
			{				
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_Balance;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==18)
			{				
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_potentialprofitpoint  ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			////////////////////////////////
			else if (col==19)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_PotentialLosspoint;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}

			else if (col==20)
			{

				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];				
				CString tmp=mst_grid.m_DurationTime;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==21)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_high ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
				
			}
			else if (col==22)
			{	
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_low ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
		}
}