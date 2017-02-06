#include "stdafx.h"
#include "resource.h"
#include "AlertGrid.h"
#include "document.h"
#include <iostream>
#include "Login.h"
#include "OrderwiseJournal.h"

using namespace std;
using namespace rapidjson;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
BEGIN_MESSAGE_MAP(AlertGrid,CUGCtrl)	
	ON_WM_SIZE()
	ON_WM_TIMER()		
END_MESSAGE_MAP()
int AlertGrid::insertFilterFlag=0;
int AlertGrid::shorting=0;
AlertGrid::AlertGrid()
{
	UGXPThemes::UseThemes(false);
}
AlertGrid::~AlertGrid()
{	
	UGXPThemes::CleanUp();
}
LRESULT AlertGrid::GridRefresh(WPARAM wParam, LPARAM lParam)
{
	RedrawAll();
	return 0;
}
LRESULT AlertGrid::OnThreadMessage(WPARAM wParam, LPARAM lParam)
{
	HRESULT hr = S_OK;	
	int col= (int)wParam;
	int row= (int)lParam;
	
	
	return 0;
}

LRESULT AlertGrid::GridRowCount(WPARAM wParam, LPARAM lParam)
{	
	
	return 0;
}

LRESULT AlertGrid::RowDelete(WPARAM wParam, LPARAM lParam)
{
	int row= (int)wParam;
	for(int f=0;f<14;f++)
	{
		QuickSetText(f,row,L"");
	}	
	return 0;
}
LRESULT AlertGrid::OnThreadMessage_RowsNo(WPARAM wParam, LPARAM lParam)
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


void AlertGrid::OnSheetSetup(int sheetNumber)
{
	int	nRow = 0, nCol = 0;
	CUGCell cell;
	//COutputWnd::m_wndOutputOrder.GetGridDefault(&cell);
	SetGridDefault(&cell);
	EnableExcelBorders(TRUE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetDefFont(0);
	SetSH_Width(0);	
	SetNumberCols(9);

	QuickSetText(0,-1,L"PLUGIN STATUS");
	SetColWidth(0,130);

	QuickSetText(1,-1,L"LOGIN");
	SetColWidth(1,100);

	QuickSetText(2,-1,L"TIME");	
	SetColWidth(2,100);
			
	QuickSetText(3,-1,L"ORDER NO");
	SetColWidth(3,130);

	QuickSetText(4,-1,L"ORDER TYPE");
	SetColWidth(4,130);

	QuickSetText(5,-1,L"SYMBOL");
	SetColWidth(5,100);

	QuickSetText(6,-1,L"QTY");
	SetColWidth(6,160);

	QuickSetText(7,-1,L"RATE");	
	SetColWidth(7,100);
			
	QuickSetText(8,-1,L"COMMENT");
	SetColWidth(8,130);

	for(int i = 0; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}	
}

		

void AlertGrid::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();
	CString string;
	if(cell.GetLabelText() != NULL)
		string = cell.GetLabelText();
	
	if(nParam == CELLTYPE_IS_EDITABLE || string == "CELLTYPE_IS_EDITABLE"){
		StartEdit();
	}

	CString strordno=QuickGetText(3,row);
	if (strordno.GetLength()>0)
	{
		COrderwiseJournal::odno=strordno;
		COrderwiseJournal* dlg = new COrderwiseJournal();			
		dlg->DoModal();
	}
}	
			 

void AlertGrid::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{	
	if (row==-1 && updn==1)
	{
		AlertGrid::shorting=0;
		
		
	}

	if ( AlertGrid::insertFilterFlag==1)
	{
		DeleteRow(0);		
		AlertGrid::insertFilterFlag=0;
	}

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
int AlertGrid::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{

	if(ID == UGCT_DROPLIST){
		return OnDropList(ID, col, row, msg, param);
	}
}
int AlertGrid::OnDropList(long ID,int col,long row,long msg,long param)
{
	if (msg==103)
	{
	if(AlertGrid::insertFilterFlag==1 && row==0)
	{
		//AlertGrid::filter_break=1;
		//check_First==0;
		CString  strval=L"";
		CUGCell cell;
		GetCell(col,row,&cell);
		strval=cell.GetText();
		//AlertGrid::strFilter="";
		if (strval!=L"")
		{
			gridFilter(col,GetNumberRows(),strval);
		}
	}
	RedrawAll();
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
int AlertGrid::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	if(AlertGrid::insertFilterFlag==1 && row==0)
	{
		//AlertGrid::filter_break=1;
		
		CString  strval=L"";
		CUGCell cell;
		QuickSetText(col,row,string );
		GetCell(col,row,&cell);
		strval=cell.GetText();
		
		
	  gridFilter(col,GetNumberRows(),strval);
		
		RedrawAll();
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
void AlertGrid::OnMenuCommand(int col,long row,int section,int item)
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
		case 2002:
		{
		    
	
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
void AlertGrid::OnTabSelected(int ID)
{
	//SetSheetNumber(ID);
	//PostMessage(WM_SIZE, 0, 0L);
}

/////////////////////////////////////////////////////////////////////////////
//	OnAdjustComponentSizes
//		Called when the grid components are baing arranged.
//	Params:
//		grid, topHdg, sideHdg, cnrBtn, vScroll, hScroll, 
//		tabs	- sizes and location of each of the grid components
//	Return:
//		<none>

void AlertGrid::OnSize(UINT nType, int cx, int cy)
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
void AlertGrid::OnTimer(UINT nIDEvent)
{		
}
 void AlertGrid::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();
	
	EnableMenu(TRUE);
	
	
	AddMenuItem( 2001, _T( "Filter" ) );
	AddMenuItem( 2000, _T( "Find Dialog" ) );
	
	
}

 int AlertGrid::OnMenuStart( int iCol, long lRow, int iSection )
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

 


 void AlertGrid::filter()
 {
	if (AlertGrid::insertFilterFlag==0)
	{
			addItemToCombobox();
			AlertGrid::insertFilterFlag=1;
			InsertRow(0);
			for (int col_count=0;col_count<9;col_count++)
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
			RedrawAll();
	}
	else
	{
		
		DeleteRow(0);
		AlertGrid::insertFilterFlag=0;
		gridFilter(1,GetNumberRows(),L"ALL");
	}
	RedrawAll();
 }



BOOLEAN  AlertGrid::CheckvalueInArray(const CStringArray& arr,CString strval) 
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
 
void AlertGrid::addItemToCombobox()
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
	
	try
	{
	int rows=1;
	rows=GetNumberRows();
	
	CString str_val=L"";
	
	for (int forcount=0;forcount<8;forcount++)
	{
		str[forcount]=L"ALL\n";
		
	}
	for (int forcount=0;forcount<rows;forcount++)
	{
		for (int clocount=0;clocount<8;clocount++)
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
				

				}

			}

		}												
	}
	
	catch(_com_error & ce)
			{
				AfxMessageBox(ce.Description()+L"addItemToCombobox");			
			} 
}

void AlertGrid::OnSetup()
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

	SetNumberCols( 14 );
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

void AlertGrid::gridFilter(int colno,int rows_count,CString col_value)
{
	CString getColvalue=L"";
	CString col_filter_val[9];
	for(int c=0;c<9;c++)
	{
		col_filter_val[c]=QuickGetText(c,0);
	}
	for(int fcount=rows_count-1;fcount>0;fcount--)
	{
		int flag=0;		
		
		CString col_row_val[9];
		for(int c=0;c<9;c++)
		{
			col_row_val[c]=QuickGetText(c,fcount);
		}
		if((col_filter_val[0]==col_row_val[0] || col_filter_val[0]==L"ALL"||col_filter_val[0]==L"") && (col_filter_val[1]==col_row_val[1] || col_filter_val[1]==L"ALL"||col_filter_val[1]==L"") && (col_filter_val[2]==col_row_val[2] || col_filter_val[2]==L"ALL"||col_filter_val[2]==L"")  && (col_filter_val[3]==col_row_val[3] || col_filter_val[3]==L"ALL"||col_filter_val[3]==L"")  && (col_filter_val[4]==col_row_val[4] || col_filter_val[4]==L"ALL"||col_filter_val[4]==L"")   && (col_filter_val[5]==col_row_val[5] || col_filter_val[5]==L"ALL"||col_filter_val[5]==L"")   && (col_filter_val[6]==col_row_val[6] || col_filter_val[6]==L"ALL"||col_filter_val[6]==L"")   && (col_filter_val[7]==col_row_val[7] || col_filter_val[7]==L"ALL"||col_filter_val[7]==L"")   && (col_filter_val[8]==col_row_val[8] || col_filter_val[8]==L"ALL"||col_filter_val[8]==L"") )
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


int AlertGrid::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
{
		int retVal = 0;			
		
		if( flags & UG_SORT_DESCENDING )
		{
			CUGCell *ptr = cell1;
			cell1 = cell2;
			cell2 = ptr;
		}

		COLORREF cr1 = cell1->GetBackColor();
		COLORREF cr2 = cell2->GetBackColor();
		COleDateTime date1, date2;
		CString str1, str2;
		int iLen1, iLen2;
		

		BYTE color1, color2;

		switch ( m_iSortCol )
		{
	
	
		case 2:
			date1.ParseDateTime( cell1->GetText(), VAR_DATEVALUEONLY );
			date2.ParseDateTime( cell2->GetText(), VAR_DATEVALUEONLY );

			// If a date is invalid, move it to the bottom, by always making it >
			// ( the valid code is 0 )
			if (date1.GetStatus())
				return 1;
			if (date2.GetStatus())
				return -1;
		
			if( date1 < date2 )
				retVal = -1;
			if( date1 > date2 )
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