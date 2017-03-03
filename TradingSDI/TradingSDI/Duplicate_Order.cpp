#include "stdafx.h"
#include "resource.h"
#include "Duplicate_Order.h"
#include <afxdisp.h>
#include <time.h>
#include <locale.h>
#include "MainFrm.h"
#include "document.h"
#include <iostream>
#include "Duplicate_OrderTable.h"
#include "Netpos_Get_Data.h"
#include "Grid_CheckTrade.h"
#include "DataTradeFilter.h"
#include "Login.h"
using namespace std;
using namespace rapidjson;
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace rename("EOF", "EndOfFile")

#define WM_MY_THREAD_MESSAGE1				WM_APP+200
#define WM_MY_THREAD_MESSAGE_ROWSNO1			WM_APP+201
#define WM_MY_THREAD_MESSAGE_REFRESH1		WM_APP+202
#define GRID_ROWS_COUNT1						WM_APP+203
#define DELETE_ROW1	     					WM_APP+204
#define ROW_NO_FIND	     					WM_APP+206


#define CREATE_PUSH_BUTTON					WM_APP+205

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//CUIThread
BEGIN_MESSAGE_MAP(Duplicate_Order,CUGCtrl)	
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_MESSAGE(WM_MY_THREAD_MESSAGE1, OnThreadMessage)
	ON_MESSAGE(WM_MY_THREAD_MESSAGE_ROWSNO1, OnThreadMessage_RowsNo)		
	ON_MESSAGE(WM_MY_THREAD_MESSAGE_REFRESH1, GridRefresh)		
	ON_MESSAGE(GRID_ROWS_COUNT1, GridRowCount)		
	ON_MESSAGE(DELETE_ROW1, RowDelete)		
	ON_MESSAGE(CREATE_PUSH_BUTTON , CreatePushButton)	
	ON_MESSAGE(ROW_NO_FIND, rownofind)	
END_MESSAGE_MAP()
CString Duplicate_Order::m_c_symbol=L"";
int Duplicate_Order::value_row_no=0;
int Duplicate_Order::filter_break=0;
int Duplicate_Order::insertFilterFlag=0;
int Duplicate_Order::check_First=0;
_variant_t Duplicate_Order::avarRecords;
int Duplicate_Order::lock_data=0;
int Duplicate_Order::intRows=0;
int Duplicate_Order::lock_data_fill=0;
int Duplicate_Order::Grid_Rows_Count=0;
int Duplicate_Order::data_display=0;
int Duplicate_Order::thred_killed_ok=0;
_bstr_t Duplicate_Order::strShort("  order by t1.login asc,t1.symbol asc");

_bstr_t Duplicate_Order::strFilter(" ");
_variant_t Duplicate_Order::result;
long Duplicate_Order::rgIndices[2];
_bstr_t Duplicate_Order::bstr_currenttime("");


Duplicate_Order::Comment_ChangeArray Duplicate_Order::m_Comment_ChangeArray;
Duplicate_Order::st_Comment_Change Duplicate_Order::m_st_Comment_Change={};
/////////////////////////////////////////////////////////////////////////////
//Standard MyCug construction/destruction
Duplicate_Order::Duplicate_Order()
{
	 t = CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S");
	 bstr_currenttime=t;
	UGXPThemes::UseThemes(false);
}


LRESULT Duplicate_Order::CreatePushButton(WPARAM, LPARAM)
{
	CUGCell cell;
	int noofrows=GetNumberRows();
	GetCell(10,noofrows-1,&cell);

	if (cell.GetCellTypeEx()!= UGCT_BUTTONNOFOCUS)
	{
		InsertRow(noofrows);		
		GetCell(10,noofrows,&cell);		
		cell.SetCellType(m_nButtonIndex);
		cell.SetCellTypeEx(UGCT_BUTTONNOFOCUS);
		cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
		SetCell(10,noofrows,&cell);
		QuickSetText(10,noofrows,L"Select All");
	}
	else
	{
		QuickSetText(10,noofrows-1,L"Select All");
	}
	return 0;
}

Duplicate_Order::~Duplicate_Order()
{
	try
	{
	//delete m_pThread;
	UGXPThemes::CleanUp();

	DWORD exit_code= NULL;
	if (m_pThreads != NULL)
	{
    GetExitCodeThread(m_pThreads->m_hThread, &exit_code);
    if(exit_code == STILL_ACTIVE)
    {
        ::TerminateThread(m_pThreads->m_hThread, 0);
        CloseHandle(m_pThreads->m_hThread);
    }
    m_pThreads->m_hThread = NULL;
    m_pThreads = NULL;
	}
	}
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"Thread UnInitiliaze");			
	}

}

UINT update_data_Duplicate_Order(void*);
UINT update_data_Duplicate_Order(void *pParam)
{
	Duplicate_Order* pThis= (Duplicate_Order*)pParam;	
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<DataTradeFilter> > artists1;	
	HRESULT hr;
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=TradeDataBase;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	if(SUCCEEDED(hr))
	{
		session.Open(connection);
		while (true )
		{				
			_bstr_t strCommand="";		
			strCommand="select [time],[order],mt5_deals.deal,symbol,case when [action]=0 then 'Buy' else 'Sell' end as 'Type',volume/10000 as 'volume',price,comment,isnull(OurComment,'') as 'OurComment',[login] as 'Checked',isnull(change_YN,0) as 'Change_YN'  from mt5_deals left outer join Trade_Checked on Trade_Checked.deal=mt5_deals.deal left outer join comment_change on comment_change.deal=mt5_deals.deal where ISNULL(Change_YN,0)='1' order by slno asc";        
			char* strCommand_char=(char*)strCommand;
			hr=artists1.Open(session,strCommand_char);							 					 		 				 
			 int intRows=0;		 
			 double t_d_m_Pre_NetQty=0;
			 double t_d_m_Diff_NetQty=0;
			 double t_d_m_NetQty=0;
			 double t_d_m_PL=0;
			 double t_d_m_Balance=0;
			 if(SUCCEEDED(hr))
			 {
				 Duplicate_Order::m_Comment_ChangeArray.Clear();
				 while (artists1.MoveNext() == S_OK)
				 {																	  
					CMTStr::Copy(Duplicate_Order::m_st_Comment_Change.login,artists1.m_Checked);				 					
					CMTStr::Copy(Duplicate_Order::m_st_Comment_Change.time,artists1.m_time);				 										
					CMTStr::Copy(Duplicate_Order::m_st_Comment_Change.deal ,artists1.m_deal);				 										 
					CMTStr::Copy(Duplicate_Order::m_st_Comment_Change.order ,artists1.m_order);																
					CMTStr::Copy(Duplicate_Order::m_st_Comment_Change.symbol ,artists1.m_symbol);																										 
					CMTStr::Copy(Duplicate_Order::m_st_Comment_Change.action ,artists1.m_Type);											
					CMTStr::Copy(Duplicate_Order::m_st_Comment_Change.volume ,artists1.m_volume);								
					LPTSTR endPtr;
					double d_m_PL = _tcstod(artists1.m_price, &endPtr);												
					CString cstrpl;
					cstrpl.Format(_T("%.2f"),d_m_PL);	
					CMTStr::Copy(Duplicate_Order::m_st_Comment_Change.price ,cstrpl);											
					CMTStr::Copy(Duplicate_Order::m_st_Comment_Change.comment ,artists1.m_comment);											
					CMTStr::Copy(Duplicate_Order::m_st_Comment_Change.OurComment ,artists1.m_OurComment);	
					Duplicate_Order::m_Comment_ChangeArray.Add(&Duplicate_Order::m_st_Comment_Change);
				 }
				 artists1.Close();
				 pThis->SendMessage(WM_MY_THREAD_MESSAGE1, 0,0);
				 //pThis->PostMessage(WM_MY_THREAD_MESSAGE1, 0,0);
			 }
		 

			 Sleep(50);
		}
	}
    return 0;
}

LRESULT Duplicate_Order::rownofind(WPARAM wParam, LPARAM lParam)
{
	
	CString m_symbol=L"";
	
	for(int f=0;f<GetNumberRows();f++)
	{
		
		m_symbol=QuickGetText(4,f);
		if ( wcscmp(m_c_symbol,m_symbol)==0)
		{			
			value_row_no=f;
			return value_row_no;
		}
	}
	value_row_no=-1;

	if (value_row_no==-1)
	{
		for(int f=0;f<GetNumberRows();f++)
		{
			m_symbol=QuickGetText(4,f);
			if (wcscmp(m_symbol,L"")==0)
			{			
				value_row_no=f;
				return value_row_no;
			}
		}
	}

	return value_row_no;
}


LRESULT Duplicate_Order::GridRefresh(WPARAM wParam, LPARAM lParam)
{
	RedrawAll();
	return 0;
}
LRESULT Duplicate_Order::DeleteThred(WPARAM wParam, LPARAM lParam)
{
	DWORD exit_code= NULL;
	if (m_pThreads != NULL)
	{
    GetExitCodeThread(m_pThreads->m_hThread, &exit_code);
    if(exit_code == STILL_ACTIVE)
    {
        ::TerminateThread(m_pThreads->m_hThread, 0);
        CloseHandle(m_pThreads->m_hThread);
    }
    m_pThreads->m_hThread = NULL;
    m_pThreads = NULL;
	}

	Duplicate_Order::thred_killed_ok=0;	
	return 0;
}

boolean Duplicate_Order::CheckvalueInArray(CString dealno)
{
	int total_value =Duplicate_Order::m_Comment_ChangeArray.Total();
	for (int i=0;i<total_value;i++)
	{
		st_Comment_Change m_cc={};
		m_cc=Duplicate_Order::m_Comment_ChangeArray[i];
		CString dealin_array=m_cc.deal ;
		if (wcscmp(dealin_array,dealno)==0)
		{
			return true;
		}
	}
	return false;
}
LRESULT Duplicate_Order::OnThreadMessage(WPARAM wParam, LPARAM lParam)
{
	int grid_total_rows=GetNumberRows();
	int i=grid_total_rows-1;
	for (i;i>=0;i--)
	{
		CString Deal_in_Grid=QuickGetText(2,i);
		if (CheckvalueInArray(Deal_in_Grid)==false && Deal_in_Grid!="")
		{
			DeleteRow(i);
		}
	}
	int array_total=Duplicate_Order::m_Comment_ChangeArray.Total();
	for (int i=0;i<array_total;i++)
	{
		st_Comment_Change m_cc={};
		m_cc=Duplicate_Order::m_Comment_ChangeArray[i];
		CString array_deal=m_cc.deal;
		CString array_comment=m_cc.comment ;
		CString array_Ourcomment=m_cc.OurComment;

		CString array_time=m_cc.time;
		CString array_order=m_cc.order ;		
		CString array_symbol=m_cc.symbol;
		CString array_action=m_cc.action;
		CString array_volume=m_cc.volume;
		CString array_price=m_cc.price;				
		CString array_login=m_cc.login ;
		CString array_Change_YN=m_cc.Change_YN ;
		int grid_total=GetNumberRows();
		int check_new=1;
		for (int r=0;r<grid_total;r++)
		{
			CString grid_deal=QuickGetText(2,r);
			CString grid_comment=QuickGetText(8,r);
			CString grid_Ourcomment=QuickGetText(9,r);
			if (wcscmp(grid_deal,array_deal)==0)
			{
				check_new=0;
				if (wcscmp(array_comment,grid_comment)!=0 || wcscmp(array_Ourcomment,grid_Ourcomment)!=0)
				{
					QuickSetText(8,r,array_comment);
					QuickSetText(9,r,array_Ourcomment);
				}
			}
		}
		if (check_new==1 && short_click!=1)
		{	
			int r_no=GetNumberRows();			
			SetNumberRows(r_no+1);
			
			QuickSetText(0,r_no,array_login);
			QuickSetText(1,r_no,array_time);
			QuickSetText(2,r_no,array_deal);

			QuickSetText(3,r_no,array_order);
			QuickSetText(4,r_no,array_symbol);
			QuickSetText(5,r_no,array_action);

			QuickSetText(6,r_no,array_volume);
			QuickSetText(7,r_no,array_price);
			
			QuickSetText(8,r_no,array_comment);
			QuickSetText(9,r_no,array_Ourcomment);
			CUGCell cell ;
			GetColDefault( 10, &cell);			
			QuickSetCellType(10,r_no,UGCT_CHECKBOX);	
			QuickSetCellTypeEx(10,r_no,UGCT_CHECKBOXCHECKMARK);
			SetColDefault( 10, &cell );
			QuickSetText(10,r_no,L"0");
			//Opposite_Deal
			
		}
	}	
	
	RedrawAll();
	
	return 0;
}

LRESULT Duplicate_Order::GridRowCount(WPARAM wParam, LPARAM lParam)
{
	//RedrawAll();
	Duplicate_Order::Grid_Rows_Count=GetNumberRows();
	return 0;
}

LRESULT Duplicate_Order::RowDelete(WPARAM wParam, LPARAM lParam)
{
	int row= (int)wParam;
	for(int f=0;f<10;f++)
	{
		QuickSetText(f,row,L"");
	}
	//DeleteRow(row);
	return 0;
}
LRESULT Duplicate_Order::OnThreadMessage_RowsNo(WPARAM wParam, LPARAM lParam)
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
		 CUGCell cell ;			 			
		GetColDefault( 10, &cell );			
		QuickSetCellType(10,val,UGCT_CHECKBOX);	
		QuickSetCellTypeEx(10,val,UGCT_CHECKBOXCHECKMARK);
		SetColDefault( 10, &cell );
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

void Duplicate_Order::OnSheetSetup(int sheetNumber)
{
	int	nRow = 0, nCol = 0;
	// ****************************************************************
	// ** Set up columns
	// ****************************************************************
	CUGCell cell;

	//COutputWnd::m_wndOutputOrder.GetGridDefault(&cell);
	//cell.SetBackColor(MY_COLOR_BACK);
	//cell.SetTextColor(MY_COLOR_TEXT);
	//SetGridDefault(&cell);
	EnableExcelBorders(TRUE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	
	SetVScrollMode(UG_SORT_DESCENDING);
	SetDefFont(0);
	SetSH_Width(0);
	
	// Number
			SetNumberCols(12);
			QuickSetText(0,-1,L"Login");
			SetColWidth(0,100);
			QuickSetText(1,-1,L"Time");
			SetColWidth(1,100);
			QuickSetText(2,-1,L"Deal");
			SetColWidth(2,100);
			

			QuickSetText(3,-1,L"Order");	
			SetColWidth(3,100);
			
			QuickSetText(4,-1,L"Symbol");
			SetColWidth(4,100);
			
			QuickSetText(5,-1,L"Type");
			SetColWidth(5,100);
			QuickSetText(6,-1,L"Volume");	
			SetColWidth(6,100);
			QuickSetText(7,-1,L"Price");
			SetColWidth(7,100);
			QuickSetText(8,-1,L"Comment");
			SetColWidth(8,100);
			QuickSetText(9,-1,L"CommentTo");
			SetColWidth(9,100);			
			//QuickSetText(10,-1,L"Select");
			//SetColWidth(10,80);

			//CUGCell cell ;			 			
			GetColDefault( 10, &cell );			
			QuickSetCellType(10,-1,UGCT_CHECKBOX);	
			QuickSetCellTypeEx(10,-1,UGCT_CHECKBOXCHECKMARK);
			SetColDefault( 10, &cell );
			QuickSetLabelText(10,-1,L"Select");

			QuickSetText(11,-1,L"Opposite_Deal");
			SetColWidth(11,100);			
			//Opposite_Deal
			
	// Header font			
	for(int i = 0; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}	
		
	RedrawAll();
}




int Duplicate_Order::OnCheckbox(long ID,int col,long row,long msg,long param)
{
	if(row==-1)
	{
		int rowscount=GetNumberRows();
		if (param==1)
		{
			for (int forcount=0;forcount<rowscount;forcount++)
			{
				QuickSetText(10,forcount,L"1"); 
			}
		}
		if (param==0)
		{
			for (int forcount=0;forcount<rowscount;forcount++)
			{
				QuickSetText(10,forcount,L"0"); 
			}
		}
	}

	return TRUE;
}



void Duplicate_Order::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);

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

	if(nParam == CELLTYPE_IS_EDITABLE || string == "CELLTYPE_IS_EDITABLE"||col==9||col==11)
	{
		StartEdit();
		//Duplicate_Order::filter_break=1;
	}
}	
			 

void Duplicate_Order::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{		
	short_click=1;
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);

	if( updn == 0)
	{
		short_click=0;
		return;
	}
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
	
	CUGCell cell ;			 			
	GetColDefault( 10, &cell );			
	QuickSetCellType(10,-1,UGCT_CHECKBOX);	
	QuickSetCellTypeEx(10,-1,UGCT_CHECKBOXCHECKMARK);
	SetColDefault( 10, &cell );
	QuickSetLabelText(10,-1,L"Select");
	RedrawAll();
	short_click=0;
}
int Duplicate_Order::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{

	if(ID == UGCT_DROPLIST)
	{
		return OnDropList(ID, col, row, msg, param);
	}

	if(ID == UGCT_CHECKBOX){
		return OnCheckbox(ID, col, row, msg, param);
	}

	if(ID == m_nButtonIndex)
	{
		return OnPushButton( ID, col, row, msg, param);
	}
}
int Duplicate_Order::OnDropList(long ID,int col,long row,long msg,long param)
{
	if (msg==103)
	{
		if(Duplicate_Order::insertFilterFlag==1 && row==0)
	{
		Duplicate_Order::filter_break=1;
		check_First==0;
		CString  strval=L"";
		CUGCell cell;
		GetCell(col,row,&cell);
		strval=cell.GetText();
		Duplicate_Order::strFilter="";
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

_bstr_t Duplicate_Order::get_string(CString  MainStr,CString SepStr)
{
	int str_len=MainStr.GetLength();
	CString strcode=L"";	
	_bstr_t b_strreturn="";
	_bstr_t b_strCode="";
	_bstr_t b_strChar="";
	_bstr_t bstrcomp="";
	for(int forcount=0;forcount<str_len;forcount++)
	{
		CString strchar=MainStr.Mid(forcount,1);
		if (strchar!=SepStr)
		{
			b_strChar=strchar;
			b_strCode=b_strCode+b_strChar;
		}
		else
		{
			if(b_strreturn!=bstrcomp)
			{
				b_strreturn=b_strreturn+","+"'"+b_strCode+"'";
			}
			else
			{
				b_strreturn="'"+b_strCode+"'";
			}
			b_strCode="";
		}
	}
	
	if (b_strreturn!=bstrcomp)
	{
		b_strreturn=b_strreturn+","+"'"+b_strCode+"'";
	}
	else
	{
		b_strreturn="'" +b_strCode +"'";
	}

	b_strreturn="("+b_strreturn+")";
	return b_strreturn;

}



int Duplicate_Order::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{

	
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
void Duplicate_Order::OnMenuCommand(int col,long row,int section,int item)
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





int Duplicate_Order::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
{
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
	int retVal = 0;

	BYTE color1, color2;

	switch ( m_iSortCol )
	{
case 1:
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

/////////////////////////////////////////////////////////////////////////////
//	OnTabSelected
//		Called when the user selects one of the tabs on the bottom of the screen
//	Params:
//		ID	- id of selected tab
//	Return:
//		<none>
void Duplicate_Order::OnTabSelected(int ID)
{
	SetSheetNumber(ID);
	PostMessage(WM_SIZE, 0, 0L);
}



void Duplicate_Order::OnSize(UINT nType, int cx, int cy)
{
	
}

void Duplicate_Order::OnTimer(UINT nIDEvent)
{		
}


 void Duplicate_Order::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();
	
	EnableMenu(TRUE);
	
	
	AddMenuItem( 2001, _T( "Filter" ) );
	AddMenuItem( 2000, _T( "Find Dialog" ) );
	
	
}

 int Duplicate_Order::OnMenuStart( int iCol, long lRow, int iSection )
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

 void Duplicate_Order::filter()
 {
	if (Duplicate_Order::insertFilterFlag==0)
	{
			addItemToCombobox();
			Duplicate_Order::insertFilterFlag=1;
			InsertRow(0);
			for (int col_count=0;col_count<10;col_count++)
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
		Duplicate_Order::insertFilterFlag=0;
		Duplicate_Order::strFilter=" ";
	}
	RedrawAll();
 }



BOOLEAN  Duplicate_Order::CheckvalueInArray(const CStringArray& arr,CString strval) 
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
 
void Duplicate_Order::addItemToCombobox()
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
	
	try
	{
	int rows=1;
	rows=GetNumberRows();
	
	CString str_val=L"";
	
	for (int forcount=0;forcount<10;forcount++)
	{
		str[forcount]=L"ALL\n";		
	}
	for (int forcount=0;forcount<rows;forcount++)
	{
		for (int clocount=0;clocount<10;clocount++)
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

			}

		}												
	}
	}
	catch(_com_error & ce)
			{
				AfxMessageBox(ce.Description()+L"addItemToCombobox");			
			} 
}
 





int Duplicate_Order::OnPushButton(long ID,int col,long row,long msg,long param)
{
	int rowscount=GetNumberRows();
	for (int forcount=0;forcount<rowscount-1;forcount++)
	{
		QuickSetText(10,forcount,L"1"); 
	}
	
	return TRUE;
}


void Duplicate_Order::OnSetup()
{
	// Set up the Tab controls
	short_click=0;
	m_nButtonIndex = AddCellType(&m_button);
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

	int	nIndex = 0;
	CUGCell cell;
	GetGridDefault(&cell);
	SetGridDefault(&cell);
	EnableExcelBorders(FALSE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
//	SetUniformRowHeight(false);
	
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

	SetNumberCols(11);
	

	m_iArrowIndex = AddCellType( &m_sortArrow );

	SetCurrentCellMode( 2 );

	UseHints( TRUE );

	SetSH_Width( 0 );
 // Start timers
//	srand( (unsigned)time( NULL ) );
	SetTimer(0, 100, NULL);
	SetTimer(1, 100, NULL);

	
	QuickSetCellType( 0, -1, m_iArrowIndex );
	SortBy( 0, UG_SORT_ASCENDING );

	m_iSortCol = 0;
	m_bSortedAscending = TRUE;
	m_pThreads=AfxBeginThread(update_data_Duplicate_Order, this);		   	
		run_check=0;		
}

void Duplicate_Order::gridFilter(int colno,int rows_count,CString col_value)
{
	
	CString getColvalue=L"";
	
for(int fcount=rows_count;fcount>-1;fcount--)

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
					SetRowHeight(fcount, 20);
				}
				else
				{
					SetColWidth(fcount, 0);
				}
			}
			if (fcar==L"<")
			{
				if(getColvalue<comp_value )
				{
				    SetRowHeight(fcount, 20);
				}
				else
				{
					SetRowHeight(fcount, 0);
				}
			}
		}

		else
		{

		if(getColvalue==col_value || col_value==L"ALL")
		{
			
			SetRowHeight(fcount, 20);
		}
		else
		{
			SetRowHeight(fcount, 0);
		}
		}
	 }
	//SetRowHeight(0, 20);
	      
	
}

int Duplicate_Order::OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow)
{	
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newcol);
	UNREFERENCED_PARAMETER(newrow);
	return TRUE;
}
void Duplicate_Order::change_comment_dealwise(CString login,CString dealno,CString newcomment,CString precomment)
{
	
	int comment_check=0;
	CString m_strnewcomment=L"";
	m_strnewcomment=newcomment;
	CString login_1=login;
	CString login_2=L"";

	login_1=login_1.Mid(0,6);
	_bstr_t strlogin_o=login_1;
	_bstr_t strlogin_c_1=precomment;
	_bstr_t strlogin_c_2=m_strnewcomment;
	_bstr_t strlogin_1="";
	if (precomment.Trim()!=L"")
	{
		strlogin_1="" + strlogin_o + "-" + precomment + "";
	}
	else
	{
		strlogin_1=strlogin_o ;
	}
	_bstr_t strlogin_2="";
	if (newcomment.Trim()!=L"")
	{
		strlogin_2="" + strlogin_o + "-" + m_strnewcomment + "";
	}
	else
	{
		strlogin_2=strlogin_o ;
	}
	
	comment_check=DlgHelp::m_dealer->Change_Comment(precomment,m_strnewcomment,dealno);	
	Sleep(100);
	if (comment_check==1)
	{
		try
		{
			CoInitialize(NULL);
			HRESULT hr = S_OK;	
			_RecordsetPtr pRstAuthors = NULL;
		 hr = pRstAuthors.CreateInstance(__uuidof(Recordset)); 
		int check_data=0;
		_bstr_t jasonStr="";
		_variant_t  strUpdate_time="";
		_bstr_t r_time="";
		_bstr_t bstrConnect ="Provider=SQLOLEDB.1;SERVER=68.168.104.26;Database=Tradedatabase;uid=sa;pwd=ok@12345;";
		
		_bstr_t  InsertAndUpdate_Command="exec proc_data_delete_for_commentchange '" + strlogin_1 + "','" + strlogin_2 + "'; ";
		
		 pRstAuthors->Open(InsertAndUpdate_Command,bstrConnect,  adOpenStatic,adLockReadOnly,adCmdText);  				
		}
		catch(_com_error & ce)
		{	   
			//AfxMessageBox(L"Netpos Insert"+ce.ErrorMessage());
			AfxMessageBox(ce.Description()+L"Comment Change");
		}
		
	}
}


void Duplicate_Order::Selected_commentChange()
{
	
	/*OrderGrid::m_Client.Send("Hello",5);*/
	if(CDealer::admin_login!=1)
	{
		AfxMessageBox(L"You Are not a valid user");
		return ;
	}

	char * Final_Str="";	

	char* data_for_send;
	Duplicate_Order::filter_break=1;
	int rows_count=GetNumberRows();
	CString login=L"";
	CString deal=L"";
	CString comment_o=L"";
	CString comment_n=L"";
	CString ocomment_o=L"";
	CString ocomment_n=L"";
	CoInitialize(NULL);
	_RecordsetPtr pRstAuthors = NULL;
	 HRESULT hr = S_OK;
	 hr = pRstAuthors.CreateInstance(__uuidof(Recordset)); 
	_bstr_t bstrConnect ="Provider=SQLOLEDB.1;SERVER=68.168.104.26;Database=TRADEDATABASE;uid=sa;pwd=ok@12345;";		
	_bstr_t str_new="";
	_bstr_t InsertAndUpdate_Command="";
	_bstr_t  bstr_final_comment=""; 
	bstr_final_comment="Comment_Change~";
	for (int fcount=0;fcount<rows_count;fcount++)
	{
		login=QuickGetText(0,fcount);
		deal=QuickGetText(2,fcount);
		comment_o=QuickGetText(8,fcount);
		ocomment_o=comment_o;
		if (comment_o.Find('-')>=0)
		{
			comment_o=comment_o.Mid(0,comment_o.Find('-'));
		}
		comment_n=QuickGetText(9,fcount);
		ocomment_n=comment_n;
		if (comment_n.Find('-')>=0)
		{
			comment_n=comment_n.Mid(0,comment_n.Find('-'));
		}
		
		CString check_value=QuickGetText(10,fcount);
		_bstr_t strdeal=deal;
		
		if (login!=L"" && check_value==L"1"  && comment_n.Trim().GetLength()>0) 
		{
			change_comment_dealwise(login,deal,ocomment_n,ocomment_o);
			st_Change_Comment_List m_st_Change_Comment_List={};
			CMTStr::Copy(m_st_Change_Comment_List.Deal,deal);
			CMTStr::Copy(m_st_Change_Comment_List.Login,login);
			CMTStr::Copy(m_st_Change_Comment_List.Old_Comment,comment_o);
			CMTStr::Copy(m_st_Change_Comment_List.New_Comment,comment_n);
			char *struct_data;
			//memcpy(struct_data,&m_st_Change_Comment_List,sizeof(st_Change_Comment_List));*/
			_bstr_t bstr_login=login+"-"+comment_o+"|"+login+"-"+comment_n+"|"+login+"-"+ocomment_o+"|"+login+"-"+ocomment_n;
			
			bstr_final_comment=bstr_final_comment+bstr_login+"|";
		

			 str_new= " exec update_CommentChangeYN '" + strdeal + "','0'; ";
			 InsertAndUpdate_Command=str_new +InsertAndUpdate_Command ;
		}
	}	
	Final_Str=bstr_final_comment;
	int check_data_send=0;
	if(check_data_send=OrderGrid::m_Client.Send(Final_Str,strlen(Final_Str))>1)
	{

	}
	else
	{
	
			 if(WSAGetLastError()!=WSAEWOULDBLOCK) 
			 { 				
				shutdown(OrderGrid::m_Client,2);
				closesocket(OrderGrid::m_Client);									
			 }		
			 
			 CSocket m_Client;
			if( AfxSocketInit() == FALSE)
			{ 
				AfxMessageBox(L"Failed to Initialize Sockets"); 
				return ; 
			}
			if(m_Client.Create()==FALSE)
			{
				AfxMessageBox(L"Failed to Create Socket");
				return ;
			}
			if(m_Client.Connect(L"68.168.104.26",5042)==FALSE)
			{
				AfxMessageBox(L"Failed to Connect");		
				return;
			}	
		    m_Client.Send(Final_Str,strlen(Final_Str));
			m_Client.Close();
			shutdown(m_Client,2);
			closesocket(m_Client);

	}
	Final_Str=NULL ;
	CString str_command_check=InsertAndUpdate_Command;
	if (str_command_check.Trim().GetLength()>0)
	{
		pRstAuthors->Open(InsertAndUpdate_Command,bstrConnect,  adOpenStatic,adLockReadOnly,adCmdText);  	 
	}
	Duplicate_Order::filter_break=0;
	AfxMessageBox(L"Data has been  SuccessFully updated");
}







BOOL Duplicate_Order::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	int x=(int)pMsg->wParam;

	if(pMsg->message==WM_KEYDOWN )
	{

	if(x==70 && GetKeyState( VK_CONTROL) < 0)
		{
		    filter();
            return TRUE;
		}
	}
   return CUGCtrl::PreTranslateMessage(pMsg);
}
