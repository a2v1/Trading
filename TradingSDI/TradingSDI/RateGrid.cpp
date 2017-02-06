#include "stdafx.h"
#include "resource.h"
#include "RateGrid.h"
#include <afxdisp.h>
#include <time.h>
#include <locale.h>
#include "MainFrm.h"
#include "document.h"
#include <iostream>
#include "CNetPosTable.h"
#include "Login.h"
using namespace std;
using namespace rapidjson;
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace rename("EOF", "EndOfFile")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//CUIThread
BEGIN_MESSAGE_MAP(RateGrid,CUGCtrl)	
	ON_WM_SIZE()
	ON_WM_TIMER()	
END_MESSAGE_MAP()
int RateGrid::filter_break=0;
int RateGrid::insertFilterFlag=0;
int RateGrid::check_First=0;
_variant_t RateGrid::avarRecords;
int RateGrid::lock_data=0;
int RateGrid::intRows=0;
int RateGrid::lock_data_fill=0;
int RateGrid::Grid_Rows_Count=0;
_bstr_t RateGrid::strShort(" DT_SetupTime desc");
_bstr_t RateGrid::cellvalue("");
_bstr_t RateGrid::strFilter(" and Plugin_Status not in ('OKAY','DEL') ");
_variant_t RateGrid::result;
long RateGrid::rgIndices[2];

/////////////////////////////////////////////////////////////////////////////
//Standard MyCug construction/destruction
RateGrid::RateGrid()
{
	UGXPThemes::UseThemes(false);
}

RateGrid::~RateGrid()
{
	//delete m_pThread;
	UGXPThemes::CleanUp();
}




LRESULT RateGrid::GridRefresh(WPARAM wParam, LPARAM lParam)
{
	RedrawAll();
	return 0;
}



LRESULT RateGrid::OnThreadMessage(WPARAM wParam, LPARAM lParam)
{
	HRESULT hr = S_OK;	
	int col= (int)wParam;
	int row= (int)lParam;
	
	if (RateGrid::insertFilterFlag==0)
	{
		
		QuickSetText(col,row,RateGrid::cellvalue);	
		
		//RedrawCell(col,row);
	}
	else
	{
		QuickSetText(col,row+1,RateGrid::cellvalue);	
			
		//RedrawCell(col,row+1);
	}
	return 0;
}

LRESULT RateGrid::GridRowCount(WPARAM wParam, LPARAM lParam)
{
	//RedrawAll();
	RateGrid::Grid_Rows_Count=GetNumberRows();
	return 0;
}

LRESULT RateGrid::RowDelete(WPARAM wParam, LPARAM lParam)
{
	int row= (int)wParam;
	for(int f=0;f<14;f++)
	{
		QuickSetText(f,row,L"");
	}
	//DeleteRow(row);
	return 0;
}



LRESULT RateGrid::OnThreadMessage_RowsNo(WPARAM wParam, LPARAM lParam)
{
	int val= (int)wParam;
	int flag= (int)lParam;
	if(flag==0)
	{
		SetNumberRows(val);
	}
	if(flag==1)
	{
		InsertRow(val);
	}
		return 0;
}







/////////////////////////////////////////////////////////////////////////////
//	OnSheetSetup	
//		This notification is called for each additional sheet that the grid
//		might contain, here you can customize each sheet in the grid.
//	Params:
//		sheetNumber - idndex of current sheet
//	Return:
//		<none>
void RateGrid::OnSheetSetup(int sheetNumber)
{
	int	nRow = 0, nCol = 0;
	// ****************************************************************
	// ** Set up columns
	// ****************************************************************
	CUGCell cell;

	//COutputWnd::m_wndOutputOrder.GetGridDefault(&cell);
	//cell.SetBackColor(MY_COLOR_BACK);
	//cell.SetTextColor(MY_COLOR_TEXT);
	SetGridDefault(&cell);
	EnableExcelBorders(TRUE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetDefFont(0);
	SetSH_Width(0);
	//DlgHelp::m_dealer->m_manager->DealSubscribe(this);
	// Number
			SetNumberCols(3);

			QuickSetText(0,-1,L"SYMBOL");
			SetColWidth(0,130);

			QuickSetText(1,-1,L"LTP");
			SetColWidth(1,70);

			QuickSetText(2,-1,L"TIME");	
			SetColWidth(2,130);
			
			
			

			
	// Header font
	for(int i = 0; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}	
}

		

void RateGrid::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();
	CString string;
	if(cell.GetLabelText() != NULL)
		string = cell.GetLabelText();

	if(processed){
		if(cell.GetCellType() == m_nSpinIndex)
			return ;
	}

	if(nParam == CELLTYPE_IS_EDITABLE || string == "CELLTYPE_IS_EDITABLE"){
		StartEdit();
	}
}	
			 

void RateGrid::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
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

//		((CFindAndSortDemo*)GetParent())->Trace( _T( "Sorted column %d ascending" ), iCol );
	}
	else
	{
		SortBy( col, UG_SORT_DESCENDING );
		QuickSetCellType( m_iSortCol, -1, m_iArrowIndex );
		QuickSetCellTypeEx( m_iSortCol, -1, UGCT_SORTARROWUP );
//		Trace( _T( "Sorted column %d descending" ), iCol );
	}
	
	RedrawAll();
	
}
int RateGrid::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{

	if(ID == UGCT_DROPLIST){
		return OnDropList(ID, col, row, msg, param);
	}
}
int RateGrid::OnDropList(long ID,int col,long row,long msg,long param)
{
	if (msg==103)
	{
		if(RateGrid::insertFilterFlag==1 && row==0)
	{
		RateGrid::filter_break=1;
		check_First==0;
		CString  strval=L"";
		CUGCell cell;
		GetCell(col,row,&cell);
		strval=cell.GetText();
		RateGrid::strFilter="";
		if (strval!=L"")
		{
			gridFilter(col,GetNumberRows(),strval);
		}
	}
	}
	return true;
}


/////////////////////////////////////////////////////////////////////////////
//	OnEditFinish
//		This notification is sent when the edit is being finised
//	Params:
//		col, row	- coordinates of the edit cell
//		edit		- pointer to the edit control
//		string		- actual string that user typed in
//		cancelFlag	- indicates if the edit is being cancelled
//	Return:
//		TRUE - to allow the edit it proceede
//		FALSE - to force the user back to editing of that same cell
int RateGrid::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	if(RateGrid::insertFilterFlag==1 && row==0)
	{
		RateGrid::filter_break=1;
		check_First==0;
		CString  strval=L"";
		CUGCell cell;
		QuickSetText(col,row,string );
		GetCell(col,row,&cell);
		strval=cell.GetText();
		RateGrid::strFilter="";
		if (strval!=L"")
		{
			gridFilter(col,GetNumberRows(),strval);
		}
	}
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
//	OnMenuCommand
//		This notification is called when the user has selected a menu item
//		in the pop-up menu.
//	Params:
//		col, row - the cell coordinates of where the menu originated from
//		setcion - identify for which portion of the gird the menu is for.
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//		item - ID of the menu item selected
//	Return:
//		<none>
void RateGrid::OnMenuCommand(int col,long row,int section,int item)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(section);
	// init. local variables
	CMenu* pMenu;
	pMenu = GetPopupMenu();
	
	switch( item )
	{
		
		case 2000:
		{
			FindDialog();
//			Trace( _T( "Displayed the grid's Find Dialog." ) );
			break;
		}
		case 2001:
		{
			filter();
//			Trace( _T( "Displayed the grid's Replace Dialog." ) );
			break;
		}
		
	}
}




/////////////////////////////////////////////////////////////////////////////
//	OnSortEvaluate
//		Sent as a result of the 'SortBy' call, this is called for each cell
//		comparison and allows for customization of the sorting routines.
//		We provide following code as example of what could be done here,
//		you migh have to modify it to give your application customized sorting.
//	Params:
//		cell1, cell2	- pointers to cells that are compared
//		flags			- identifies sort direction
//	Return:
//		value less than zero to identify that the cell1 comes before cell2
//		value equal to zero to identify that the cell1 and cell2 are equal
//		value greater than zero to identify that the cell1 comes after cell2


/////////////////////////////////////////////////////////////////////////////
//	OnTabSelected
//		Called when the user selects one of the tabs on the bottom of the screen
//	Params:
//		ID	- id of selected tab
//	Return:
//		<none>
void RateGrid::OnTabSelected(int ID)
{
	SetSheetNumber(ID);
	PostMessage(WM_SIZE, 0, 0L);
}

/////////////////////////////////////////////////////////////////////////////
//	OnAdjustComponentSizes
//		Called when the grid components are baing arranged.
//	Params:
//		grid, topHdg, sideHdg, cnrBtn, vScroll, hScroll, 
//		tabs	- sizes and location of each of the grid components
//	Return:
//		<none>

void RateGrid::OnSize(UINT nType, int cx, int cy)
{
	/*EnableUpdate(FALSE);

	RECT rect;
	GetClientRect(&rect);

	SetTabWidth(max(rect.right/3, 75));
	SetSH_Width(0);
	SetColWidth(0, 175);
	for(int y = 1;y < 14; y++)
	{
		SetColWidth(y, (rect.right-175)/6);
	}

	EnableUpdate(TRUE);


	CUGCtrl::OnSize(nType,cx,cy);*/
}
void RateGrid::OnTimer(UINT nIDEvent)
{		
}
 void RateGrid::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();
	
	EnableMenu(TRUE);
	
	
	AddMenuItem( 2001, _T( "Filter" ) );
	AddMenuItem( 2000, _T( "Find Dialog" ) );
	
	
}

 int RateGrid::OnMenuStart( int iCol, long lRow, int iSection )
{
	UNREFERENCED_PARAMETER(iCol);
	UNREFERENCED_PARAMETER(lRow);

	if( iSection == UG_GRID )
	{
//		Trace( _T( "Displayed the grid's internal pop-up menu." ) );	
		return TRUE;
	}
	else
		return FALSE;
}

 void RateGrid::filter()
 {
	if (RateGrid::insertFilterFlag==0)
	{
			addItemToCombobox();
			RateGrid::insertFilterFlag=1;
			InsertRow(0);
			for (int col_count=0;col_count<3;col_count++)
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
	}
	else
	{
		
		DeleteRow(0);
		RateGrid::insertFilterFlag=0;
		gridFilter(1,GetNumberRows(),L"ALL");
	}
	RedrawAll();
 }



BOOLEAN  RateGrid::CheckvalueInArray(const CStringArray& arr,CString strval) 
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
 
void RateGrid::addItemToCombobox()
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
	try
	{
	int rows=1;
	rows=GetNumberRows();
	
	CString str_val=L"";
	
	for (int forcount=0;forcount<3;forcount++)
	{
		str[forcount]=L"ALL\n";
		
	}
	for (int forcount=0;forcount<rows;forcount++)
	{
		for (int clocount=0;clocount<3;clocount++)
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


				
				
				
				
				

			}

		}												
	}
	}
	catch(_com_error & ce)
			{
				AfxMessageBox(ce.Description()+L"addItemToCombobox");			
			} 
}

void RateGrid::OnSetup()
{
	// Set up the Tab controls
	c1_click=0;
	c2_click=0;
	c3_click=0;
	c4_click=0;
	c5_click=0;
	c6_click=0;
	c7_click=0;
	c8_click=0;
	c9_click=0;
	c10_click=0;
	c11_click=0;
	c12_click=0;
	c13_click=0;
	c14_click=0;
	int	nIndex = 0;
	CUGCell cell;
	GetGridDefault(&cell);
	SetGridDefault(&cell);
	EnableExcelBorders(FALSE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetUserSizingMode( TRUE );

	
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

	SetNumberCols( 14 );
	//SetNumberRows( 50 );

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



	
		run_check=0;		
}

void RateGrid::gridFilter(int colno,int rows_count,CString col_value)
{
	CString getColvalue=L"";
	
	for(int fcount=rows_count-1;fcount>0;fcount--)
	{
		getColvalue=QuickGetText(colno,fcount);


		col_value=col_value.Trim();
		CString fcar=col_value.Mid(0,1);
		CString comp_value=col_value.Mid(1,col_value.GetLength()-1);
		if(fcar==L">"||fcar==L"<")
		{
			if (fcar==L">")
			{
				if(getColvalue>comp_value )
				{
					SetColWidth(2, 75);
					SetRowHeight(fcount, 20);
					SetSH_Width(0);
					SetTH_Height(20);
			
					//AfxMessageBox(L"Hide Row");
				}
				else
				{
					SetColWidth(2, 75);
					SetRowHeight(fcount, 0);
					SetSH_Width(0);
					SetTH_Height(20);
					//AfxMessageBox(L"UN Hide Row");
				}
			}
			if (fcar==L"<")
			{
				if(getColvalue<comp_value )
				{
					SetColWidth(2, 75);
					SetRowHeight(fcount, 20);
					SetSH_Width(0);
					SetTH_Height(20);
			
					//AfxMessageBox(L"Hide Row");
				}
				else
				{
					SetColWidth(2, 75);
					SetRowHeight(fcount, 0);
					SetSH_Width(0);
					SetTH_Height(20);
					//AfxMessageBox(L"UN Hide Row");
				}
			}
		}

		else
		{

		if(getColvalue==col_value || col_value==L"ALL")
		{
			SetColWidth(2, 75);
			SetRowHeight(fcount, 20);
			SetSH_Width(0);
			SetTH_Height(20);
			
			//AfxMessageBox(L"Hide Row");
		}
		else
		{
			SetColWidth(2, 75);
			SetRowHeight(fcount, 0);
			SetSH_Width(0);
			SetTH_Height(20);
			//AfxMessageBox(L"UN Hide Row");
		}
		}
	}
	
}


int RateGrid::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
{
	if( flags & UG_SORT_DESCENDING )
	{
		CUGCell *ptr = cell1;
		cell1 = cell2;
		cell2 = ptr;
	}


	COleDateTime date1, date2;
	
	int retVal = 0;



	switch ( m_iSortCol )
	{
	case 1:
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

