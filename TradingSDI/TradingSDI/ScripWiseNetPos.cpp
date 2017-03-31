#include "stdafx.h"
#include "resource.h"
#include "ScripWiseNetPos.h"
#include <afxdisp.h>
#include <time.h>
#include <locale.h>
#include "MainFrm.h"
#include "document.h"
#include <iostream>
#include "CScripWiseNetPosTable.h"
#include "Netpos_Get_Data.h"
using namespace std;
using namespace rapidjson;
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace rename("EOF", "EndOfFile")

#define WM_MY_THREAD_MESSAGE1				WM_APP+200
#define WM_MY_THREAD_MESSAGE_ROWSNO1		WM_APP+201
#define WM_MY_THREAD_MESSAGE_REFRESH1		WM_APP+202
#define GRID_ROWS_COUNT1					WM_APP+203
#define DELETE_ROW1	     					WM_APP+204
#define ROW_NO_FIND	     					WM_APP+205
#define GRID_SHORTING	     				WM_APP+206
#define GETCELLVAL	     				    WM_APP+207
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//CUIThread
BEGIN_MESSAGE_MAP(ScripWiseNetPos,CUGCtrl)	
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_MESSAGE(WM_MY_THREAD_MESSAGE1, OnThreadMessage)
	ON_MESSAGE(WM_MY_THREAD_MESSAGE_ROWSNO1, OnThreadMessage_RowsNo)		
	ON_MESSAGE(WM_MY_THREAD_MESSAGE_REFRESH1, GridRefresh)		
	ON_MESSAGE(GRID_ROWS_COUNT1, GridRowCount)		
	ON_MESSAGE(DELETE_ROW1, RowDelete)
	ON_MESSAGE(ROW_NO_FIND, rownofind)	
	ON_MESSAGE(GRID_SHORTING, gridshorting)		
	ON_MESSAGE(GETCELLVAL, getcellval)		

	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



CString ScripWiseNetPos::m_COL_VAL=L"";

int ScripWiseNetPos::g_ud=0;
int ScripWiseNetPos::g_c=0;
int ScripWiseNetPos::g_check=0;
CString ScripWiseNetPos::m_c_symbol=L"";
int ScripWiseNetPos::value_row_no=0;
int ScripWiseNetPos::filter_break=0;
int ScripWiseNetPos::insertFilterFlag=0;
int ScripWiseNetPos::check_First=0;
_variant_t ScripWiseNetPos::avarRecords;
int ScripWiseNetPos::lock_data=0;
int ScripWiseNetPos::intRows=0;
int ScripWiseNetPos::lock_data_fill=0;
int ScripWiseNetPos::Grid_Rows_Count=0;
int ScripWiseNetPos::data_display=0;
int ScripWiseNetPos::g_check_AND_BREAK=0;
int ScripWiseNetPos::row_count=0;

_bstr_t ScripWiseNetPos::strShort("  order by t1.login asc,t1.symbol asc");
_bstr_t ScripWiseNetPos::cellvalue("");
_bstr_t ScripWiseNetPos::strFilter(" ");
_variant_t ScripWiseNetPos::result;
long ScripWiseNetPos::rgIndices[2];
_bstr_t ScripWiseNetPos::bstr_currenttime("");

ScripWiseNetPos::scripwisenetpos_array ScripWiseNetPos::m_scripwisenetpos_Array;	
ScripWiseNetPos::scripwisenetpos_array ScripWiseNetPos::m_scripwisenetpos_Array_data;	
ScripWiseNetPos::scripwisenetpos_array ScripWiseNetPos::m_scripwisenetpos_grid_array;
CMutex ScripWiseNetPos::m_mutex_scripnetpos;


/////////////////////////////////////////////////////////////////////////////
//Standard MyCug construction/destruction
ScripWiseNetPos::ScripWiseNetPos()
{
	 t = CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S");
	 bstr_currenttime=t;
	UGXPThemes::UseThemes(false);
}

ScripWiseNetPos::~ScripWiseNetPos()
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

UINT update_data_ScripWiseNetpos(void*);
UINT update_data_ScripWiseNetpos(void *pParam)
{
	HRESULT hr;
	ScripWiseNetPos* pThis= (ScripWiseNetPos*)pParam;	
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<CScripWiseNetPosTable> > artists1;	
	connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");	
	session.Open(connection);
	while (true)
	{	
		 
		_bstr_t strCommand="";		
		strCommand="ScripWiseNetpos";
        char* strCommand_char=(char*)strCommand;
		hr=artists1.Open(session,strCommand_char);							
		if(SUCCEEDED(hr))
		{
			
			ScripWiseNetPos::m_scripwisenetpos_Array_data.Clear();
			double total_balance=0,total_netQty=0,total_AvgaRate=0,total_Lastrate=0;

			while (artists1.MoveNext() == S_OK)
			{				
				ScripWiseNetPos::st_scripwisenetpos m_st_scripwisenetpos={};	
				CMTStr::Copy(m_st_scripwisenetpos.m_Symnol,artists1.m_Symnol);
				m_st_scripwisenetpos.m_NetQty= artists1.m_NetQty;
				m_st_scripwisenetpos.m_Average =artists1.m_Average ;
				m_st_scripwisenetpos.m_LastRate =artists1.m_LastRate ;
				m_st_scripwisenetpos.m_PL =artists1.m_PL;
				total_netQty=total_netQty+m_st_scripwisenetpos.m_NetQty;
				total_AvgaRate=total_AvgaRate+m_st_scripwisenetpos.m_Average;
				total_Lastrate=total_Lastrate+m_st_scripwisenetpos.m_LastRate;
				total_balance=total_balance+m_st_scripwisenetpos.m_PL;
				ScripWiseNetPos::m_scripwisenetpos_Array_data.Add(&m_st_scripwisenetpos);
			}
			artists1.Close();
			ScripWiseNetPos::st_scripwisenetpos m_st_scripwisenetpos={};	
			CMTStr::Copy(m_st_scripwisenetpos.m_Symnol,L"Total");

			m_st_scripwisenetpos.m_NetQty= total_netQty;
			//m_st_scripwisenetpos.m_Average =total_AvgaRate;
			//m_st_scripwisenetpos.m_LastRate =total_Lastrate;


			m_st_scripwisenetpos.m_PL =total_balance;			
			ScripWiseNetPos::m_scripwisenetpos_Array_data.Add(&m_st_scripwisenetpos);

			ScripWiseNetPos::m_mutex_scripnetpos.Lock();
			ScripWiseNetPos::m_scripwisenetpos_Array.Assign(ScripWiseNetPos::m_scripwisenetpos_Array_data);
			ScripWiseNetPos::m_mutex_scripnetpos.Unlock();
		}	
		Sleep(30);
	}		
    return 0;
}



LRESULT ScripWiseNetPos::GridRefresh(WPARAM wParam, LPARAM lParam)
{
	
	RedrawAll();
	
	return 0;
}

LRESULT ScripWiseNetPos::gridshorting(WPARAM wParam, LPARAM lParam)
{
	int updn=int(wParam);
	int col=int(lParam);

		

	if( updn == 0)
	{
		return 0;
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


	 int ro_no=GetNumberRows();	
	 for(int f=0;f<ro_no;f++)
	 {
		 CString cval=QuickGetText(0,f);
		if(wcscmp( cval,L"TOTAL")==0)
		{
			DeleteRow(f);
			f=f-1;
		}
	 }

	 RedrawAll();
	 return 0;
}


LRESULT ScripWiseNetPos::rownofind(WPARAM wParam, LPARAM lParam)
{
	
CString m_symbol=L"";

for(int f=0;f<GetNumberRows();f++)
	{
		
		m_symbol=QuickGetText(0,f);
		if(wcscmp(m_c_symbol,m_symbol)==0)
		{			
			value_row_no=f;
		    return value_row_no;
		}
	}

   value_row_no=-1;
   if (value_row_no==-1)
	{
		for(int K=0;K<GetNumberRows();K++)
		{
			m_symbol=QuickGetText(0,K);
			if (wcscmp(m_symbol,L"")==0)
			{			
				value_row_no=K;
				return value_row_no;
			}
			
		}
	}
	
	 
	return value_row_no;
}


LRESULT ScripWiseNetPos::OnThreadMessage(WPARAM wParam, LPARAM lParam)
{
	
	HRESULT hr = S_OK;	
	int col= (int)wParam;
	int row= (int)lParam;
	
	if (ScripWiseNetPos::insertFilterFlag==0)
	{
		
		QuickSetText(col,row,ScripWiseNetPos::cellvalue);	
		
		//RedrawCell(col,row);
	}
	else
	{
		QuickSetText(col,row+1,ScripWiseNetPos::cellvalue);	
			
		//RedrawCell(col,row+1);
	}
	
	return 0;
}



LRESULT ScripWiseNetPos::getcellval(WPARAM wParam, LPARAM lParam)
{
	m_COL_VAL=QuickGetText(int(wParam),(lParam));
	return 0;
}
LRESULT ScripWiseNetPos::GridRowCount(WPARAM wParam, LPARAM lParam)
{
	//RedrawAll();
	
	ScripWiseNetPos::Grid_Rows_Count=GetNumberRows();
	
	return 0;
}

LRESULT ScripWiseNetPos::RowDelete(WPARAM wParam, LPARAM lParam)
{
	int row= (int)wParam;
	for(int f=0;f<5;f++)
	{
		QuickSetText(f,row,L"");
	}
	
	return 0;
}



LRESULT ScripWiseNetPos::OnThreadMessage_RowsNo(WPARAM wParam, LPARAM lParam)
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

void ScripWiseNetPos::OnSheetSetup(int sheetNumber)
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
	SetVScrollMode(UG_SORT_DESCENDING);
	SetDefFont(0);
	SetSH_Width(0);
	
	// Number
			SetNumberCols(5);
			//SetNumberRows(18);
			QuickSetText(0,-1,L"Symbol");
			SetColWidth(0,110);
			QuickSetText(1,-1,L"NetQty");
			SetColWidth(1,70);
			QuickSetText(2,-1,L"Average");	
			SetColWidth(2,70);
			
			QuickSetText(3,-1,L"LastRate");
			SetColWidth(3,70);
			
			QuickSetText(4,-1,L"PL");
			SetColWidth(4,90);
			

			
	// Header font
	for(int i = 0; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}	
}

		

void ScripWiseNetPos::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
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

	if(nParam == CELLTYPE_IS_EDITABLE || string == "CELLTYPE_IS_EDITABLE")
	{
		StartEdit();
	}
}	
			 

void ScripWiseNetPos::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{	
	ScripWiseNetPos::g_ud=updn;
	ScripWiseNetPos::g_c=col;
	ScripWiseNetPos::g_check=1;
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);
	gridshorting(updn,col);
	
}

int ScripWiseNetPos::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{

	if(ID == UGCT_DROPLIST){
		return OnDropList(ID, col, row, msg, param);
	}
	return 0;
}
int ScripWiseNetPos::OnDropList(long ID,int col,long row,long msg,long param)
{
	if (msg==103)
	{
	if(ScripWiseNetPos::insertFilterFlag==1 && row==0)
	{
		ScripWiseNetPos::filter_break=1;
		check_First==0;
		CString  strval=L"";
		CUGCell cell;
		GetCell(col,row,&cell);
		strval=cell.GetText();
		ScripWiseNetPos::strFilter="";
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

_bstr_t ScripWiseNetPos::get_string(CString  MainStr,CString SepStr)
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



int ScripWiseNetPos::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
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
void ScripWiseNetPos::OnMenuCommand(int col,long row,int section,int item)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(section);
	// init. local variables
	CMenu* pMenu;
	pMenu = GetPopupMenu();
	
	switch( item )
	{
		/*case 2000:
			{
			 filter();
			 break;
			
			}*/
		case 2001:
		{
			FindDialog();
//			Trace( _T( "Displayed the grid's Find Dialog." ) );
			break;

		}
	}
}
//   




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
int ScripWiseNetPos::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
{ 

	ScripWiseNetPos::row_count=ScripWiseNetPos::row_count+1;

	if( flags & UG_SORT_DESCENDING )
	{
		CUGCell *ptr = cell1;
		cell1 = cell2;
		cell2 = ptr;
	}

	
	
	CString str1, str2;
	
	int retVal = 0;
	switch(m_iSortCol)
	{
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
     case 4:
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
	switch( cell1->GetDataType()  )
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
void ScripWiseNetPos::OnTabSelected(int ID)
{
	SetSheetNumber(ID);
	PostMessage(WM_SIZE, 0, 0L);
}



void ScripWiseNetPos::OnSize(UINT nType, int cx, int cy)
{
	
}

void ScripWiseNetPos::OnTimer(UINT nIDEvent)
{	
	m_mutex_scripnetpos.Lock();
	m_scripwisenetpos_grid_array.Assign(m_scripwisenetpos_Array);
	m_mutex_scripnetpos.Unlock();
	int r_count=m_scripwisenetpos_grid_array.Total();
	Dealing::dealing_mutex.Unlock();		
	int grid_total=GetNumberRows();
	if (grid_total!=r_count)
	{			
		SetNumberRows(r_count);					
	}
	else
	{			
			RedrawAll();			
	}				
}


void ScripWiseNetPos::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();
	
	EnableMenu(TRUE);
	
	
	/*AddMenuItem( 2000, _T( "Filter" ) );*/
	AddMenuItem( 2001, _T( "Find Dialog" ) );
		
	submenu.CreatePopupMenu();
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1000, _T("Symbol"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1001, _T("NetQty"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1002, _T("Average"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1003, _T("LastRate"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1004, _T("PL"));
	
	//menu->AppendMenu(MF_POPUP, (UINT)submenu.Detach(), _T("Columns Setting"));
	SetMenu(menu);
	
}

 int ScripWiseNetPos::OnMenuStart( int iCol, long lRow, int iSection )
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

 void ScripWiseNetPos::filter()
 {
	if (ScripWiseNetPos::insertFilterFlag==0)
	{
			addItemToCombobox();
			ScripWiseNetPos::insertFilterFlag=1;
			InsertRow(0);
			for (int col_count=0;col_count<5;col_count++)
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
		ScripWiseNetPos::insertFilterFlag=0;
		ScripWiseNetPos::strFilter=" ";
	}
	RedrawAll();
 }



BOOLEAN  ScripWiseNetPos::CheckvalueInArray(const CStringArray& arr,CString strval) 
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
 
void ScripWiseNetPos::addItemToCombobox()
{
	CStringArray arr;
	CStringArray arr1;
	CStringArray arr2;
	CStringArray arr3;
	CStringArray arr4;
	CStringArray arr5;
	
	
	
	try
	{
	int rows=1;
	rows=GetNumberRows();
	
	CString str_val=L"";
	
	for (int forcount=0;forcount<5;forcount++)
	{
		str[forcount]=L"ALL\n";		
	}
	for (int forcount=0;forcount<rows;forcount++)
	{
		for (int clocount=0;clocount<5;clocount++)
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
			
				
			}

		}												
	}
	}
	catch(_com_error & ce)
			{
				AfxMessageBox(ce.Description()+L"addItemToCombobox");			
			} 
}
 

void ScripWiseNetPos::gridFilter(int colno,int rows_count,CString col_value)
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
}
void ScripWiseNetPos::OnSetup()
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

	SetNumberCols(5);
	

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
	m_pThreads=AfxBeginThread(update_data_ScripWiseNetpos, this);		   	
		run_check=0;		

}




void ScripWiseNetPos::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//m_pThreads->ResumeThread();
	//CUGCtrl::OnLButtonUp(nFlags, point);
}





void ScripWiseNetPos::OnGetCell(int col,long row,CUGCell *cell)
{
		//m_logfile_g.LogEvent(L"Start OnGetCell");
		st_scripwisenetpos mst_grid={};
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
			
			if (col==0)
			{				
				mst_grid=m_scripwisenetpos_grid_array[rows_no];				
				CString tmp=L"";				
				tmp=mst_grid.m_Symnol;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			if (col==1)
			{				
				mst_grid=m_scripwisenetpos_grid_array[rows_no];				
				CString tmp=L"";
				double netqty=mst_grid.m_NetQty;
				tmp.Format(L"%.2f",netqty);
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==2)
			{
				
				mst_grid=m_scripwisenetpos_grid_array[rows_no];				
				CString tmp=L"";
				double netqty=mst_grid.m_Average ;
				tmp.Format(L"%.2f",netqty);
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==3)
			{				
				mst_grid=m_scripwisenetpos_grid_array[rows_no];				
				CString tmp=L"";
				double netqty=mst_grid.m_LastRate ;
				tmp.Format(L"%.2f",netqty);
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==4)
			{				
				mst_grid=m_scripwisenetpos_grid_array[rows_no];				
				CString tmp=L"";
				double netqty=mst_grid.m_PL ;
				tmp.Format(L"%.2f",netqty);
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
		}
}