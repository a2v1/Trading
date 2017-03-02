#include "stdafx.h"
#include "resource.h"
#include "Grid_CheckTrade.h"
#include <afxdisp.h>
#include <time.h>
#include <locale.h>
#include "MainFrm.h"
#include "document.h"
#include <iostream>
#include "CNetPosTable.h"
#include "Netpos_Get_Data.h"
#include "GridTradeAndOrder.h"
#include "DataTradeFilter.h"
#include "change_comment.h"
#include "Dealer.h"
using namespace std;
using namespace rapidjson;
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace rename("EOF", "EndOfFile")

#define WM_MY_THREAD_MESSAGE1				WM_APP+200
#define WM_MY_THREAD_MESSAGE_ROWSNO1		WM_APP+201
#define WM_MY_THREAD_MESSAGE_REFRESH1		WM_APP+202
#define GRID_ROWS_COUNT1					WM_APP+203
#define DELETE_ROW1	     					WM_APP+204
#define DELETE_THREAD	     				WM_APP+205

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(Grid_CheckTrade,CUGCtrl)	
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_MESSAGE(DELETE_THREAD,DeleteThred)
END_MESSAGE_MAP()

//Structure variable
Grid_CheckTrade::st_grid_check_array Grid_CheckTrade::m_st_grid_check_Array_Fill;
Grid_CheckTrade::st_grid_check_array Grid_CheckTrade::m_st_grid_check_Array;
Grid_CheckTrade::st_grid_check_array Grid_CheckTrade::m_st_grid_check_Grid_array;

Grid_CheckTrade::st_grid_check Grid_CheckTrade::m_st_grid_check={};


int Grid_CheckTrade::filter_break=0;
int Grid_CheckTrade::insertFilterFlag=0;
int Grid_CheckTrade::check_First=0;
_variant_t Grid_CheckTrade::avarRecords;
int Grid_CheckTrade::lock_data=0;
int Grid_CheckTrade::intRows=0;
int Grid_CheckTrade::lock_data_fill=0;
int Grid_CheckTrade::Grid_Rows_Count=0;
int Grid_CheckTrade::data_display=0;
int Grid_CheckTrade::thred_kill=0;
int Grid_CheckTrade::thred_killed_ok=0;
int Grid_CheckTrade::col_click=0;
int Grid_CheckTrade::a_d=0;

CString Grid_CheckTrade::m_strtime=L"";
CString Grid_CheckTrade::m_strdeal=L"";
CString Grid_CheckTrade::m_strorder=L"";
CString Grid_CheckTrade::m_strsymbol=L"";	
CString Grid_CheckTrade::m_strtype=L"";
CString Grid_CheckTrade::m_strvolume=L"";
CString Grid_CheckTrade::m_strprice=L"";
CString Grid_CheckTrade::m_strcomment=L"";

CString Grid_CheckTrade::col0_val=L"";
CString Grid_CheckTrade::col1_val=L"";
CString Grid_CheckTrade::col2_val=L"";
CString Grid_CheckTrade::col3_val=L"";
CString Grid_CheckTrade::col4_val=L"";
CString Grid_CheckTrade::col5_val=L"";
CString Grid_CheckTrade::col6_val=L"";
CString Grid_CheckTrade::col7_val=L"";
CString Grid_CheckTrade::col8_val=L"";
CString Grid_CheckTrade::col9_val=L"";
CString Grid_CheckTrade::col10_val=L"";
//_bstr_t Grid_CheckTrade::m_selected_login="0";
//_bstr_t Grid_CheckTrade::m_selected_Name="0";

_bstr_t Grid_CheckTrade::strShort("  order by t1.login asc,t1.symbol asc");
_bstr_t Grid_CheckTrade::cellvalue("");
_bstr_t Grid_CheckTrade::strFilter(" ");
_variant_t Grid_CheckTrade::result;
long Grid_CheckTrade::rgIndices[2];
_bstr_t Grid_CheckTrade::bstr_currenttime("");
COLORREF Grid_CheckTrade::rows_color_checked=RGB(255,0,0);
COLORREF Grid_CheckTrade::rows_color_unchecked=RGB(255,255,255);
/////////////////////////////////////////////////////////////////////////////
//Standard MyCug construction/destruction
Grid_CheckTrade::Grid_CheckTrade()
{
	 t = CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S");
	 bstr_currenttime=t;
	//UGXPThemes::UseThemes(false);

}

Grid_CheckTrade::~Grid_CheckTrade()
{
	
	
}
boolean Check_numeric_col_filter1(CString  filter_value,CString  real_value);
boolean  Check_numeric_col_filter1(CString  filter_value,CString  real_value)
{
		boolean bool_col=false;		
		double temp_double=0;
		LPTSTR endPtr;
		temp_double= _tcstod(real_value, &endPtr);	
		filter_value=filter_value.Trim();
		if (filter_value.GetLength()>2)
		{
			if (filter_value.Mid(0,2)==L">=")
			{
				CString o_real_val=filter_value.Mid(2,filter_value.GetLength()-2);
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(o_real_val, &endPtr1);	
				if (temp_double>=db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}
			if (filter_value.Mid(0,2)==L"<=")
			{
				CString o_real_val=filter_value.Mid(2,filter_value.GetLength()-2);
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(o_real_val, &endPtr1);	
				if (temp_double<=db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}

			if (filter_value.Mid(0,1)==L"<")
			{
				CString o_real_val=filter_value.Mid(1,filter_value.GetLength()-1);
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(o_real_val, &endPtr1);	
				if (temp_double<db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}
			if (filter_value.Mid(0,1)==L">")
			{
				CString o_real_val=filter_value.Mid(1,filter_value.GetLength()-1);
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(o_real_val, &endPtr1);	
				if (temp_double>db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}	

			
			if (filter_value.Mid(0,1)!=L">" &&  filter_value.Mid(0,1)!=L"<")
			{
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(filter_value, &endPtr1);	
				if (temp_double==db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}

		}
		else
		{

			if (filter_value.Mid(0,1)==L"<")
			{
				CString o_real_val=filter_value.Mid(1,filter_value.GetLength()-1);
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(o_real_val, &endPtr1);	
				if (temp_double<db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}
			if (filter_value.Mid(0,1)==L">")
			{
				CString o_real_val=filter_value.Mid(1,filter_value.GetLength()-1);
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(o_real_val, &endPtr1);	
				if (temp_double>db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}	

			if (filter_value.Mid(0,1)!=L">" &&  filter_value.Mid(0,1)!=L"<")
			{
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(filter_value, &endPtr1);	
				if (temp_double==db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}
		}
		return bool_col;
}
LRESULT Grid_CheckTrade::DeleteThred(WPARAM wParam, LPARAM lParam)
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

	Grid_CheckTrade::thred_killed_ok=0;	
	return 0;
}

double Grid_CheckTrade::getColumnSum_in_struct(int col_index,int flag)
{

	double return_val=0;
	CUGCell m_cell;
	int total_rows=Grid_CheckTrade::m_st_grid_check_Array_Fill.Total();
	Grid_CheckTrade::st_grid_check st={};
	for (int i=0;i<total_rows;i++)
	{
		
        st=Grid_CheckTrade::m_st_grid_check_Array_Fill[i];
		LPTSTR endPtr1;			
		double d_val1=0;
		if (col_index==6)
		{
			d_val1=_tcstod(st.m_volume,&endPtr1);
			if (flag==0)
			{				
				if (wcscmp(st.m_Type,L"Buy")==0)
				{
					return_val=return_val+d_val1;
				}
			}
			else
			{				
				if ((wcscmp(st.m_Type,L"Sell")==0))
				{
					return_val=return_val+d_val1;
				}
			}

		}	
	}
	return return_val;
}

/////////////////////////////////////////////////////////////////////////////
//	OnSheetSetup	
//		This notification is called for each additional sheet that the grid
//		might contain, here you can customize each sheet in the grid.
//	Params:
//		sheetNumber - idndex of current sheet
//	Return:
//		<none>
void Grid_CheckTrade::OnSheetSetup(int sheetNumber)
{
	
	int	nRow = 0, nCol = 0;
	EnableExcelBorders(TRUE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetDefFont(0);
	SetSH_Width(0);	
	SetVScrollMode(1);
	
	// Number
			SetNumberCols(11);
			QuickSetText(0,-1,L"Comment");
			SetColWidth(0,80);
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
			
			QuickSetText(9,-1,L"OurComment");
			SetColWidth(9,120);						

			QuickSetText(10,-1,L"Tally");
			SetColWidth(10,50);						
			
	// Header font
	for(int i = 1; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}	

}

		

void Grid_CheckTrade::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();
	CString string;
	if(cell.GetLabelText() != NULL)
		string = cell.GetLabelText();

	if(processed)
	{
		if(cell.GetCellType() == m_nSpinIndex)
			return ;
	}

	if(nParam == CELLTYPE_IS_EDITABLE || string == "CELLTYPE_IS_EDITABLE" || col==9)
	{
		StartEdit();
	}
}	
			 

void Grid_CheckTrade::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{	
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);
	
	Grid_CheckTrade::col_click=col;
	if( updn == 0)
		return;
	if (col_click!=col)
	{
		a_d=0;
	}
	else
	{
		if (a_d==0)
		{
			a_d=1;
		}
		else
		{
			a_d=0;
		}
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


	Col_sorting();
	

	RedrawAll();
	
}
int Grid_CheckTrade::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{

	if(ID == UGCT_DROPLIST){
		return OnDropList(ID, col, row, msg, param);
	}
	if(ID == UGCT_CHECKBOX){
		return OnCheckbox(ID, col, row, msg, param);
	}
	return 0;
}
void Grid_CheckTrade::gridFilter(int colno,int rows_count,CString col_value)
{
	CString getColvalue=L"";
	
	for(int fcount=rows_count-2;fcount>0;fcount--)
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
			     	//AfxMessageBox(L"Hide Row");
				}
				else
				{
					SetRowHeight(fcount, 0);	
				}
			}
			if (fcar==L"<")
			{
				if(getColvalue<comp_value )
				{
				    SetRowHeight(fcount, 20);
					//AfxMessageBox(L"Hide Row");
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
			//AfxMessageBox(L"Hide Row");
		}
		else
		{
			SetRowHeight(fcount, 0);
		}
		}
	}
	
	 
		 double totbuyqty=0;
		 double totsellqty=0;
		 double buyqty=0;
		 double sellqty=0;
	for(int fcount=0;fcount<rows_count-1;fcount++)
	{
		buyqty=0;
		sellqty=0;
		CString strType=QuickGetText(5,fcount);
		CString strQty=QuickGetText(6,fcount);
		
		int row_height=0;
		
		row_height=GetRowHeight(fcount);

		LPTSTR endPtr;
		if (row_height!=0)
		{
			if (strType=="Buy" )
			{
				buyqty  = _tcstod(strQty, &endPtr);												
				totbuyqty= totbuyqty+buyqty;
			}
			if (strType=="Sell")
			{
				sellqty  = _tcstod(strQty, &endPtr);	
				totsellqty =totsellqty+sellqty;
			}
		}
	  }
	
			CString cstrpl;
			cstrpl.Format(_T("%.2f"),totbuyqty );	

			QuickSetText(1,rows_count-1,L"Total");
			QuickSetText(2,rows_count-1,L"");
			QuickSetText(3,rows_count-1,L"");
			QuickSetText(4,rows_count-1,L"Buy Qty:-");
			QuickSetText(5,rows_count-1,cstrpl);
			QuickSetText(6,rows_count-1,L"Sell Qty:-");
			cstrpl.Format(_T("%.2f"),totsellqty  );	
			QuickSetText(7,rows_count-1,cstrpl);



}
int Grid_CheckTrade::OnDropList(long ID,int col,long row,long msg,long param)
{
	
	if (msg==103)
	{
		if(Grid_CheckTrade::insertFilterFlag==1 && row==0)
		{
			Grid_CheckTrade::filter_break=1;
			check_First==0;
			CString  strval=L"";
			CUGCell cell;
			GetCell(col,row,&cell);
			strval=cell.GetText();
			Grid_CheckTrade::strFilter="";		
		}

		

		if(Grid_CheckTrade::insertFilterFlag==1 && row==0 )
		{
			
			CString  strval=L"";
			CUGCell cell;
			GetCell(col,row,&cell);
			strval=cell.GetText();	
			if(col==0)
			{
				if (strval!=L"")
				{
					col0_val=strval;					
				}
				else
				{
					col0_val=L"ALL";					
				}
			}


			if(col==1)
			{
				if (strval!=L"")
				{
					col1_val=strval;					
				}
				else
				{
					col1_val=L"ALL";					
				}
			}

			if(col==2)
			{
				if (strval!=L"")
				{
					col2_val=strval;					
				}
				else
				{
					col2_val=L"ALL";					
				}
			}

			if(col==3)
			{
				if (strval!=L"")
				{
					col3_val=strval;					
				}
				else
				{
					col3_val=L"ALL";					
				}
			}

			if(col==4)
			{
				if (strval!=L"")
				{
					col4_val=strval;					
				}
				else
				{
					col4_val=L"ALL";					
				}
			}

			if(col==5)
			{
				if (strval!=L"")
				{
					col5_val=strval;					
				}
				else
				{
					col5_val=L"ALL";					
				}
			}

			if(col==6)
			{
				if (strval!=L"")
				{
					col6_val=strval;					
				}
				else
				{
					col6_val=L"ALL";					
				}
			}

			if(col==7)
			{
				if (strval!=L"")
				{
					col7_val=strval;					
				}
				else
				{
					col7_val=L"ALL";					
				}
			}

			if(col==8)
			{
				if (strval!=L"")
				{
					col8_val=strval;					
				}
				else
				{
					col8_val=L"ALL";					
				}
			}

			if(col==9)
			{
				if (strval!=L"")
				{
					col9_val=strval;					
				}
				else
				{
					col9_val=L"ALL";					
				}
			}

			if(col==10)
			{
				if (strval!=L"")
				{
					col10_val=strval;					
				}
				else
				{
					col10_val=L"ALL";					
				}
			}

		}

		ColValue_filter();
	/*if(Grid_CheckTrade::insertFilterFlag==1 && row==0)
	{
		Grid_CheckTrade::filter_break=1;
		check_First==0;
		CString  strval=L"";
		CUGCell cell;
		GetCell(col,row,&cell);
		strval=cell.GetText();
		Grid_CheckTrade::strFilter="";
		if (strval!=L"")
		{
			gridFilter(col,GetNumberRows(),strval);
		}
	 }*/
	  RedrawAll();
     }
    return true;
}
_bstr_t Grid_CheckTrade::get_string(CString  MainStr,CString SepStr)
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



int Grid_CheckTrade::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	if(Grid_CheckTrade::insertFilterFlag==1 && row==0)
	{
		QuickSetText(col,row,string);
		//RedrawRow(row);
		CString cstr1=L"";
		CString cstr2=L"";
		CString cstr3=L"";
		CString cstr4=L"";
		CString cstr5=L"";
		CString cstr6=L"";
		CString cstr7=L"";
		CString cstr8=L"";
		CString cstr9=L"";
		CString cstr10=L"";
		CString cstr11=L"";
		CString cstr12=L"";
		CString cstr13=L"";
		CString cstr14=L"";

		_bstr_t strcol1="";
		_bstr_t strcol2="";
		_bstr_t strcol3="";
		_bstr_t strcol4="";
		_bstr_t strcol5="";
		_bstr_t strcol6="";
		_bstr_t strcol7="";
		_bstr_t strcol8="";
		_bstr_t strcol9="";
		_bstr_t strcol10="";
		_bstr_t strcol11="";
		_bstr_t strcol12="";
		_bstr_t strcol13="";
		_bstr_t strcol14="";
		Grid_CheckTrade::strFilter="";
		check_First==0;
		CString  strval=L"";
	
		strval=string;
		
		Grid_CheckTrade::filter_break=1;
		_bstr_t b_strval(strval);

			cstr1=QuickGetText(0,0);
			if (cstr1!=L"" && cstr1!=L"ALL")
			{
				//get_string(QuickGetText(0,0),L",")
				strcol1=" and t1.Login in " + get_string(QuickGetText(0,0),L",") + "";
			}
			cstr2=QuickGetText(1,0);
			if (cstr2!=L"" && cstr2!=L"ALL")
			{
				strcol2=" and t1.Name='" + (_bstr_t)QuickGetText(1,0) +"'";
			}
			cstr3=QuickGetText(2,0);
			if (cstr3!=L"" && cstr3!=L"ALL")
			{
				strcol3=" and t1.Symbol in " + get_string(QuickGetText(2,0),L",") + "";
			}
			cstr4=QuickGetText(3,0);
			if (cstr4!=L"" && cstr4!=L"ALL")
			{
				strcol4=" and t1.Pre_netqty='" + (_bstr_t)QuickGetText(3,0) +"'";
			}
			cstr5=QuickGetText(4,0);
			if (cstr5!=L"" && cstr5!=L"ALL")
			{
				strcol5=" and t1.Diff_netqty='" + (_bstr_t)QuickGetText(4,0) +"'";
			}
			cstr6=QuickGetText(5,0);
			if (cstr6!=L"" && cstr6!=L"ALL")
			{
				cstr6=cstr6.Trim();
				CString fcar=cstr6.Mid(0,1);
				if(fcar==L">"||fcar==L"<")
				{
					strcol6=" and t1.netqty " + (_bstr_t)QuickGetText(5,0) +" ";
				}
				else 
				{
					strcol6=" and t1.netqty='" + (_bstr_t)QuickGetText(5,0) +"'";
				}

				
			}
			cstr7=QuickGetText(6,0);
			if (cstr7!=L"" && cstr7!=L"ALL")
			{
				strcol7=" and t1.Average='" + (_bstr_t)QuickGetText(6,0) +"'";
			}
			cstr8=QuickGetText(7,0);
			if (cstr8!=L"" && cstr8!=L"ALL")
			{
				strcol8=" and t1.Lastrate='" + (_bstr_t)QuickGetText(7,0) +"'";			
			}
			cstr9=QuickGetText(8,0);
			if (cstr9!=L"" && cstr9!=L"ALL")
			{
				strcol9=" and t1.pl='" + (_bstr_t)QuickGetText(8,0) +"'";			
			}
			cstr10=QuickGetText(9,0);
			if (cstr10!=L"" && cstr10!=L"ALL")
			{
				strcol10=" and t1.Balance='" + (_bstr_t)QuickGetText(9,0) +"'";			
			}
			cstr11=QuickGetText(10,0);
			if (cstr11!=L"" && cstr11!=L"ALL")
			{
				strcol11=" and t1.LastUpdate='" + (_bstr_t)QuickGetText(10,0) +"'";			
			}

			cstr12=QuickGetText(11,0);
			if (cstr12!=L"" && cstr12!=L"ALL")
			{
				strcol12=" and isnull(t1.Client_Group,'')='" + (_bstr_t)QuickGetText(11,0) +"'";			
			}

			cstr13=QuickGetText(12,0);
			if (cstr13!=L"" && cstr13!=L"ALL")
			{
				strcol13=" and isnull(t1.Client_Group1,'')='" + (_bstr_t)QuickGetText(12,0) +"'";			
			}

			cstr14=QuickGetText(13,0);
			if (cstr14!=L"" && cstr14!=L"ALL")
			{
				strcol14=" and isnull(t1.Client_Group2,'')='" + (_bstr_t)QuickGetText(13,0) +"'";			
			}
		
		Grid_CheckTrade::strFilter=strcol1+strcol2+strcol3+strcol4+strcol5+strcol6+strcol7+strcol8+strcol9+strcol10+strcol11+strcol12+strcol13+strcol14;
	}
	Grid_CheckTrade::filter_break=0;
	Grid_CheckTrade::data_display=1;
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
void Grid_CheckTrade::OnMenuCommand(int col,long row,int section,int item)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(section);

		 


	// init. local variables
	CMenu* pMenu;
	pMenu = GetPopupMenu();
	CUGCell cell;
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
			int getno_col=GetNumberCols();
			int getrow_no=GetNumberRows();

			CUGCell cell;



			CColorDialog clrdlg(cell.GetBackColor());
            if (clrdlg.DoModal()==IDOK)
			{
				Grid_CheckTrade::rows_color_checked=clrdlg.GetColor();				
				int intcolor=Grid_CheckTrade::rows_color_checked;
				_bstr_t strcolor=(_bstr_t)intcolor;
				CString strvalue=strcolor;				
				CStdioFile	myFile;
				if ( myFile.Open( _T("Color_Checked.txt"), CFile::modeCreate | CFile::modeReadWrite ) )
				{					
					myFile.WriteString(strvalue);
					myFile.Flush();
					//myFile.Seek( 0, CFile::begin );
					//nActual = myFile.Read( szBuffer, sizeof( szBuffer ) ); 
				}


				for(int r_count=0;r_count<getrow_no;r_count++)
				{
					CString checked_val=QuickGetText(9,r_count);
					if (_tcscmp(checked_val,_T("0"))!=0 )
					{
						for(int f_count=0;f_count<getno_col;f_count++)
						{
						 	GetCell(f_count ,r_count,&cell);
							int nCellTypeIndex = cell.GetCellType();
							int nParam = cell.GetParam();				
							cell.SetBackColor(Grid_CheckTrade::rows_color_checked);
							SetCell(f_count,r_count ,&cell);
							RedrawCell(f_count,r_count);
						}
					}
				}
			}
			break;
		}

			case 2003:
		{
			int getno_col=GetNumberCols();
			int getrow_no=GetNumberRows();
						
			CUGCell cell;
			CColorDialog clrdlg(cell.GetBackColor());
			if (clrdlg.DoModal()==IDOK)
			{
				Grid_CheckTrade::rows_color_unchecked=clrdlg.GetColor();
				int intcolor=Grid_CheckTrade::rows_color_unchecked;
				_bstr_t strcolor=(_bstr_t)intcolor;
				CString strvalue=strcolor;				
				CStdioFile	myFile;
				if ( myFile.Open( _T("Color_UnChecked.txt"), CFile::modeCreate | CFile::modeReadWrite ) )
				{					
					myFile.WriteString(strvalue);
					myFile.Flush();
					//myFile.Seek( 0, CFile::begin );
					//nActual = myFile.Read( szBuffer, sizeof( szBuffer ) ); 
				}
				for(int r_count=0;r_count<getrow_no;r_count++)
				{
					CString checked_val=QuickGetText(9,r_count);
					if (_tcscmp(checked_val,_T("1"))!=0 )
					{
						for(int f_count=0;f_count<getno_col;f_count++)
						{
							GetCell(f_count ,r_count,&cell);
							int nCellTypeIndex = cell.GetCellType();
							int nParam = cell.GetParam();				
							cell.SetBackColor(Grid_CheckTrade::rows_color_unchecked);
							SetCell(f_count,r_count ,&cell);
							RedrawCell(f_count,r_count);
						}
					}
				}

			}
			break;
		}
			case 2004:
				{
					if (CDealer::admin_login==0)
					{
						return;
					}
					change_comment dlg_chngecmnt;					
					dlg_chngecmnt.DoModal();
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
int Grid_CheckTrade::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
{
 if( flags & UG_SORT_DESCENDING )
	{
		CUGCell *ptr = cell1;
		cell1 = cell2;
		cell2 = ptr;
	}


	COleDateTime date1, date2;

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
void Grid_CheckTrade::OnTabSelected(int ID)
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

void Grid_CheckTrade::OnSize(UINT nType, int cx, int cy)
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







void Grid_CheckTrade::OnTimer(UINT nIDEvent)
{		
}





 void Grid_CheckTrade::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();
	
	EnableMenu(TRUE);
	
	
	AddMenuItem( 2001, _T( "Filter" ) );
	AddMenuItem( 2000, _T( "Find Dialog" ) );
	AddMenuItem(2002,_T("Checked Trade color"));
	AddMenuItem(2003,_T("UnChecked Trade color"));
	//AddMenuItem(2004,_T("Change Comment"));
	
}

 int Grid_CheckTrade::OnMenuStart( int iCol, long lRow, int iSection )
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

 void Grid_CheckTrade::filter()
 {
	 CMenu *pMnenu;
	 pMnenu= GetPopupMenu();
	if (Grid_CheckTrade::insertFilterFlag==0)
	{
			addItemToCombobox();
			Grid_CheckTrade::insertFilterFlag=1;
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
			pMnenu->CheckMenuItem(2001,MF_CHECKED);
	}
	else
	{
		
		DeleteRow(0);
		Grid_CheckTrade::insertFilterFlag=0;
		int r_count=Grid_CheckTrade::m_st_grid_check_Array_Fill.Total();
		int grid_total=GetNumberRows();
		if (Grid_CheckTrade::insertFilterFlag==1)
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
		pMnenu->CheckMenuItem(2001,MF_UNCHECKED);
	}
	RedrawAll();
 }



BOOLEAN  Grid_CheckTrade::CheckvalueInArray(const CStringArray& arr,CString strval) 
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
 
void Grid_CheckTrade::addItemToCombobox()
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
	
	st_grid_check_array m_array_filter;
	m_array_filter.Assign(Grid_CheckTrade::m_st_grid_check_Array_Fill);
	
	rows=m_array_filter.Total();
	for (int forcount=0;forcount<rows;forcount++)
	{
		st_grid_check m_st_for_filter={};
		m_st_for_filter=m_array_filter[forcount];

		for (int clocount=0;clocount<16;clocount++)
		{									
				if (clocount==0)
				{
					str_val=m_st_for_filter.m_CommentYN ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr.Add(str_val);
					}
				}


				if (clocount==1)
				{
					str_val=m_st_for_filter.m_time ;
					if (str_val.GetLength()>10)
					{
						str_val=str_val.Mid(0,10);
					}
					if (CheckvalueInArray(arr1,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr1.Add(str_val);
					}
				}


				if (clocount==2)
				{
					str_val=m_st_for_filter.m_deal ;
					if (str_val.GetLength()>10)
					{
						str_val=str_val.Mid(0,10);
					}
					if (CheckvalueInArray(arr2,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr2.Add(str_val);
					}
					
				}



				if (clocount==3)
				{
					str_val=m_st_for_filter.m_order ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr3,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr3.Add(str_val);
					}
				}

				if (clocount==4)
				{
					str_val=m_st_for_filter.m_symbol ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr4,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr4.Add(str_val);
					}
				}
				if (clocount==5)
				{
					str_val=m_st_for_filter.m_Type ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr5,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr5.Add(str_val);
					}
				}
				if (clocount==6)
				{
					str_val=m_st_for_filter.m_volume ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr6,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr6.Add(str_val);
					}
				}
				if (clocount==7)
				{
					str_val=m_st_for_filter.m_price;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr7,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr7.Add(str_val);
					}
				}
				if (clocount==8)
				{
					str_val=m_st_for_filter.m_comment ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr8,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr8.Add(str_val);
					}
				}
				if (clocount==9)
				{
					str_val=m_st_for_filter.m_OurComment ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr9,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr9.Add(str_val);
					}
				}
				if (clocount==10)
				{
					str_val=m_st_for_filter.m_Checked;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr10,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr10.Add(str_val);
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
 








void Grid_CheckTrade::OnSetup()
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

    CUGCell cell;
	GetGridDefault(&cell);
	SetGridDefault(&cell);
	EnableExcelBorders(FALSE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetUserSizingMode( TRUE  );
	SetVScrollMode(1);
	
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

void Grid_CheckTrade::getData(CString FilterType,CString Datefrom,CString DateTo)
{
	try
	{

	CString strval=L"";
	CStdioFile	myFile;
	if ( myFile.Open( _T("Color_UnChecked.txt"), CFile::modeRead ) )
	{								
		myFile.Seek( 0, CFile::begin );		
		myFile.ReadString(strval);
		myFile.Close();		
		int intcolor = _ttoi(strval);
		if(intcolor!=0)
		{
			Grid_CheckTrade::rows_color_unchecked=intcolor;
		}
	}

	if ( myFile.Open( _T("Color_Checked.txt"), CFile::modeRead ) )
	{								
		myFile.Seek( 0, CFile::begin );		
		myFile.ReadString(strval);
		myFile.Close();		
		int intcolor = _ttoi(strval);
		if(intcolor!=0)
		{
			Grid_CheckTrade::rows_color_checked=intcolor;
		}
	}

	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<DataTradeFilter> > artists1;

	connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=TradeDataBase;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	
	session.Open(connection);
		_bstr_t strCommand="";				
		_bstr_t strfilter="";				
		if (FilterType!=L"")
		{
			if (FilterType==L"All history")
			{
				strfilter="";
			}
			if (FilterType==L"From Monday")
			{
				strfilter=" and [Time]>=convert(varchar(11),(getdate()-datepart(dw,getdate())+2),111)";
			}
			if (FilterType==L"Today")
			{
				strfilter=" and [Time]>=convert(varchar(11),getdate(),111)";
			}
			if (FilterType==L"Yesterday")
			{
				strfilter=" and [Time]>=convert(varchar(11),getdate()-1,111)";
			}
		}
		else
		{
			_bstr_t df=Datefrom ;
			_bstr_t dt=DateTo;
			strfilter=" and [Time]>='" + df + "' and [Time]<='" + dt + "'";
		}		
		_bstr_t strMainCode="";
		_bstr_t strComment="";
		CString sel_login=GridTradeAndOrder::m_selected_login;
		int catpos=sel_login.Find('-');
		CString sel_comment=sel_login.Mid(7,sel_login.GetLength()-7);
		sel_login=sel_login.Mid(0,6);
		strMainCode=sel_login;
		strComment=sel_comment;

		HRESULT hr;
		char* strCommand_char;
		if(catpos>=0)
		{
			strCommand="select [time],[order],mt5_deals.deal,symbol,case when [action]=0 then 'Buy' else 'Sell' end as 'Type',volume/10000 as 'volume',price,comment,isnull(OurComment,'') as 'OurComment',isnull(checked,'0') as 'Checked',isnull(change_YN,0) as 'Change_YN'  from mt5_deals left outer join Trade_Checked on Trade_Checked.deal=mt5_deals.deal left outer join comment_change on comment_change.deal=mt5_deals.deal where [login]='" + strMainCode + "' AND [action] IN (0,1) AND  isnull(comment,'')='" + strComment + "'   " + strfilter + "    order by [deal] desc";		
		}
		else
		{
			strCommand="select [time],[order],mt5_deals.deal,symbol,case when [action]=0 then 'Buy' else 'Sell' end as 'Type',volume/10000 as 'volume',price,comment,isnull(OurComment,'') as 'OurComment',isnull(checked,'0') as 'Checked',isnull(change_YN,0) as 'Change_YN'  from mt5_deals left outer join Trade_Checked on Trade_Checked.deal=mt5_deals.deal left outer join comment_change on comment_change.deal=mt5_deals.deal where [login]='" + strMainCode + "'  AND [action] IN (0,1)  " + strfilter + "    order by [deal] desc";		
		}
		strCommand_char=(char*)strCommand;
		hr=artists1.Open(session,strCommand_char);				
			 				 
		 
		 double t_d_m_Pre_NetQty=0;
		 double t_d_m_Diff_NetQty=0;
		 double t_d_m_NetQty=0;
		 double t_d_m_PL=0;
		 double t_d_m_Balance=0;

		 double buyqty=0;
		 double sellqty=0;
		 double totbuyqty=0;
		 double totsellqty=0;

		
		if(SUCCEEDED(hr))
		{
		 Grid_CheckTrade::m_st_grid_check_Array_Fill.Clear();
		 while (artists1.MoveNext() == S_OK)
		 {
			 buyqty=0;
			 sellqty=0;
			 
			LPTSTR endPtr;
			double d_m_PL = _tcstod(artists1.m_price, &endPtr);												
			CString cstrpl;
			cstrpl.Format(_T("%.2f"),d_m_PL);	


		    Grid_CheckTrade::st_grid_check m_st={};
			
			CMTStr::Copy(m_st.m_CommentYN ,artists1.m_CommentYN);
			CMTStr::Copy(m_st.m_time,artists1.m_time);
			CMTStr::Copy(m_st.m_deal ,artists1.m_deal);
			CMTStr::Copy(m_st.m_order ,artists1.m_order);
			CMTStr::Copy(m_st.m_symbol,artists1.m_symbol);
			CMTStr::Copy(m_st.m_Type,artists1.m_Type);
			CMTStr::Copy(m_st.m_volume,artists1.m_volume);
		
            CMTStr::Copy(m_st.m_price,cstrpl);
			CMTStr::Copy(m_st.m_comment,artists1.m_comment);
			CMTStr::Copy(m_st.m_OurComment,artists1.m_OurComment);
			CMTStr::Copy(m_st.m_Checked,artists1.m_Checked);
			Grid_CheckTrade::m_st_grid_check_Array_Fill.Add(&m_st);
		  }
		 }
	

		//End of Updating Data In New Structure
		Grid_CheckTrade::st_grid_check N_st={};
		CMTStr::Copy(N_st.m_CommentYN ,L"Total:-");

		 CString s1 = L"";        
		 int trade_count=Grid_CheckTrade::m_st_grid_check_Array_Fill.Total();
		 s1.Format(L"Count:-%d",trade_count);

		 CString s2 = L"";   

		 double netQty=getColumnSum_in_struct(6,0)-getColumnSum_in_struct(6,1);
		 s2.Format(L"Net:-%.2f",netQty);


		CMTStr::Copy(N_st.m_time ,s1);


		CMTStr::Copy(N_st.m_OurComment ,s2);
        CMTStr::Copy(N_st.m_symbol ,L"Buy Qty:-");
		CMTStr::Copy(N_st.m_volume ,L"Sell Qty:-");

	    CString temp_buy_total=L"";
	    temp_buy_total.Format(L"%.2f",getColumnSum_in_struct(6,0));
		CMTStr::Copy(N_st.m_Type,temp_buy_total);

		CString temp_sell_total=L"";
	    temp_sell_total.Format(L"%.2f",getColumnSum_in_struct(6,1));
		CMTStr::Copy(N_st.m_price,temp_sell_total);

	
		Grid_CheckTrade::m_st_grid_check_Array_Fill.Add(&N_st);
		

		//ASSINGNING MAIN ARRAY TO OTHER 
		Grid_CheckTrade::m_st_grid_check_Grid_array.Assign(Grid_CheckTrade::m_st_grid_check_Array_Fill);

		int r_count=Grid_CheckTrade::m_st_grid_check_Grid_array.Total();
		int grid_total=GetNumberRows();
		if (Grid_CheckTrade::insertFilterFlag==1)
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

		//checkbox in grid 
		int row=0;
		CUGCell cell;
	
        for(row;row<r_count-1;row++)
	    {
			GetColDefault( 10, &cell );			
			QuickSetCellType(10,row,UGCT_CHECKBOX);	
			QuickSetCellTypeEx(10,row,UGCT_CHECKBOXCHECKMARK);
			SetColDefault( 10, &cell );
			QuickSetCellType(0,row,UGCT_CHECKBOX);	
			QuickSetCellTypeEx(0,row,UGCT_CHECKBOXCHECKMARK);
	    }
		GetCell(9,0,&cell);
		cell.SetParam(CELLTYPE_IS_EDITABLE);

		//checkbox initialization in grid rows
		if (_tcscmp(artists1.m_Checked,_T("0"))!=0 )
			{
				for (int fcount=0;fcount<=10;fcount++)
				{
					CUGCell cell;
					GetCell(fcount,row,&cell);
					int nCellTypeIndex = cell.GetCellType();
					int nParam = cell.GetParam();					
					cell.SetBackColor(Grid_CheckTrade::rows_color_checked);
					SetCell(fcount,row ,&cell);
				}
			}
			else
			{
				for (int fcount=0;fcount<=10;fcount++)
				{
					CUGCell cell;
					GetCell(fcount,row,&cell);
					int nCellTypeIndex = cell.GetCellType();
					int nParam = cell.GetParam();					
					cell.SetBackColor(Grid_CheckTrade::rows_color_unchecked);
					SetCell(fcount,row ,&cell);
				}
			}

        

         artists1.Close();	
		 session.Close();
		 connection.Close();
		 RedrawAll();		 
	}
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description());			
	}
}

void Grid_CheckTrade::OnGetCell(int col,long row,CUGCell *cell)
{		
		//m_logfile_g.LogEvent(L"Start OnGetCell");
	    Grid_CheckTrade::st_grid_check mst_grid={};

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
			if (Grid_CheckTrade::insertFilterFlag==1)
			{
				rows_no=row-1;				
				if (row==0)
				{
					return;
				}
			}
			if (col==0)
			{		
				mst_grid=Grid_CheckTrade::m_st_grid_check_Grid_array[rows_no];
				CString tmp=mst_grid.m_CommentYN;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}

			else if (col==1)
			{

				mst_grid=Grid_CheckTrade::m_st_grid_check_Grid_array[rows_no];				
				CString tmp=mst_grid.m_time;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==2)
			{		
				mst_grid=Grid_CheckTrade::m_st_grid_check_Grid_array[rows_no];
				CString tmp=mst_grid.m_deal ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
				
			}
			else if (col==3)
			{	
				mst_grid=Grid_CheckTrade::m_st_grid_check_Grid_array[rows_no];
				CString tmp=mst_grid.m_order ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==4)
			{				
				mst_grid=Grid_CheckTrade::m_st_grid_check_Grid_array[rows_no];
				CString tmp=mst_grid.m_symbol ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==5)
			{				
				mst_grid=Grid_CheckTrade::m_st_grid_check_Grid_array[rows_no];
				CString tmp=mst_grid.m_Type  ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==6)
			{	
				mst_grid=Grid_CheckTrade::m_st_grid_check_Grid_array[rows_no];
				CString tmp=mst_grid.m_volume  ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==7)
			{				
				mst_grid=Grid_CheckTrade::m_st_grid_check_Grid_array[rows_no];
				CString tmp=mst_grid.m_price ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				
			    }
			}

			else if (col==8)
			{	
				
				mst_grid=Grid_CheckTrade::m_st_grid_check_Grid_array[rows_no];
				CString tmp=mst_grid.m_comment;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==9)
			{	
				
				mst_grid=Grid_CheckTrade::m_st_grid_check_Grid_array[rows_no];
				CString tmp=mst_grid.m_OurComment;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==10)
			{	
				mst_grid=Grid_CheckTrade::m_st_grid_check_Grid_array[rows_no];
				CString tmp=mst_grid.m_Checked;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
					
			}
		 }

}



int Grid_CheckTrade::OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow)
{	
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newcol);
	UNREFERENCED_PARAMETER(newrow);
	return TRUE;
}



			 
void Grid_CheckTrade::OnKeyDown(UINT *vcKey,BOOL processed)
{
	
		processed=false;
	
	
	//StartEdit();
}

int Grid_CheckTrade::OnCheckbox(long ID,int col,long row,long msg,long param)
{
	for (int fcount=0;fcount<=9;fcount++)
	{
	CUGCell cell;
	GetCell(fcount,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();

	if(param == 1)
	{
		
			//cell.SetTextColor(RGB(255,0,0));
		cell.SetBackColor(Grid_CheckTrade::rows_color_checked);
	}
	else
		{
			
			//cell.SetTextColor(RGB(0,0,0));
			cell.SetBackColor(Grid_CheckTrade::rows_color_unchecked );
		}
		SetCell(fcount,row ,&cell);
		RedrawCell(fcount,row);
	
	}
	
	return TRUE;
}


void Grid_CheckTrade::OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	Grid_CheckTrade::m_strtime=QuickGetText(1,row);
	Grid_CheckTrade::m_strdeal=QuickGetText(2,row);
	Grid_CheckTrade::m_strorder=QuickGetText(3,row);
	Grid_CheckTrade::m_strsymbol=QuickGetText(4,row);
	Grid_CheckTrade::m_strtype=QuickGetText(5,row);
	Grid_CheckTrade::m_strvolume=QuickGetText(6,row);
	Grid_CheckTrade::m_strprice=QuickGetText(7,row);
	Grid_CheckTrade::m_strcomment=QuickGetText(8,row);
}

void Grid_CheckTrade::Col_sorting()
{
 	//m_logfile_g.LogEvent(L"Start Update_Netposition Step_5");	
	int t_rows=Grid_CheckTrade::m_st_grid_check_Grid_array.Total();
	t_rows=t_rows-1;
	Grid_CheckTrade::st_grid_check first_st={};
	Grid_CheckTrade::st_grid_check swap_st={};
	Grid_CheckTrade::st_grid_check next_st={};
	

	int val_type=0;
	if (Grid_CheckTrade::col_click==1||Grid_CheckTrade::col_click==3 ||Grid_CheckTrade::col_click==4 ||Grid_CheckTrade::col_click==5 ||Grid_CheckTrade::col_click==8||Grid_CheckTrade::col_click==9)
	{
		val_type=0;
	}
	else
	{
		val_type=1;
	}
	for (int i=0;i<t_rows;i++)
	{
		first_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
		for (int j=i+1;j<t_rows;j++)
		{
			next_st=Grid_CheckTrade::m_st_grid_check_Grid_array[j];
			if (Grid_CheckTrade::a_d==0)
			{
				if (val_type==0)
				{
					if (Grid_CheckTrade::col_click==1)
					{
						if (wcscmp(first_st.m_time,next_st.m_time)>0)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_time,swap_st.m_time);

							
						}
					}
					
					if (Grid_CheckTrade::col_click==3)
					{
						if (wcscmp(first_st.m_order ,next_st.m_order)>0)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_order,swap_st.m_order);

							
						}
					}


					if (Grid_CheckTrade::col_click==4)
					{
						if (wcscmp(first_st.m_symbol  ,next_st.m_symbol)>0)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_symbol,swap_st.m_symbol);

							
						}
					}

					if (Grid_CheckTrade::col_click==5)
					{
						if (wcscmp(first_st.m_Type  ,next_st.m_Type)>0)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_Type,swap_st.m_Type);

							
						}
					}

					

					if (Grid_CheckTrade::col_click==8)
					{
						if (wcscmp(first_st.m_comment   ,next_st.m_comment)>0)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_comment,swap_st.m_comment);

							
						}
					}

					if (Grid_CheckTrade::col_click==9)
					{
						if (wcscmp(first_st.m_OurComment,next_st.m_OurComment)>0)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_OurComment,swap_st.m_OurComment);
						}
					}


				
				}
				else if (val_type==1)
				{
					if (Grid_CheckTrade::col_click==7)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_price ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_price,&endPtr2);						
						if (d_val1>d_val2)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_price,swap_st.m_price);							
						}
					}
					if (Grid_CheckTrade::col_click==6)
					{
						LPTSTR endPtr1;										
						int d_val1=_tcstod(first_st.m_volume ,&endPtr1);
						LPTSTR endPtr2;										
						int d_val2=_tcstod(next_st.m_volume,&endPtr2);						
						if (d_val1>d_val2)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_volume,swap_st.m_volume);

							
						}
					}
					if (Grid_CheckTrade::col_click==2)
					{
						LPTSTR endPtr1;										
						int d_val1=_tcstod(first_st.m_deal ,&endPtr1);
						LPTSTR endPtr2;										
						int d_val2=_tcstod(next_st.m_deal,&endPtr2);						
						if (d_val1>d_val2)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_deal,swap_st.m_deal);
						}
					}

				}
			}


			else if(Grid_CheckTrade::a_d==1)
			{
              	if (val_type==0)
				{
					if (Grid_CheckTrade::col_click==1)
					{
						if (wcscmp(first_st.m_time,next_st.m_time)<0)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_time,swap_st.m_time);

							
						}
					}
					if (Grid_CheckTrade::col_click==2)
					{
						if (wcscmp(first_st.m_deal,next_st.m_deal)<0)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_deal,swap_st.m_deal);
						}
					}
					if (Grid_CheckTrade::col_click==3)
					{
						if (wcscmp(first_st.m_order ,next_st.m_order)<0)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_order,swap_st.m_order);

							
						}
					}


					if (Grid_CheckTrade::col_click==4)
					{
						if (wcscmp(first_st.m_symbol  ,next_st.m_symbol)<0)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_symbol,swap_st.m_symbol);

							
						}
					}

					if (Grid_CheckTrade::col_click==5)
					{
						if (wcscmp(first_st.m_Type  ,next_st.m_Type)<0)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_Type,swap_st.m_Type);

							
						}
					}
					if (Grid_CheckTrade::col_click==8)
					{
						if (wcscmp(first_st.m_comment   ,next_st.m_comment)<0)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_comment,swap_st.m_comment);

							
						}
					}

					if (Grid_CheckTrade::col_click==9)
					{
						if (wcscmp(first_st.m_OurComment,next_st.m_OurComment)<0)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_OurComment,swap_st.m_OurComment);
						}
					}


				
				}
				else if (val_type==1)
				{
					if (Grid_CheckTrade::col_click==7)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_price ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_price,&endPtr2);						
						if (d_val1<d_val2)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_price,swap_st.m_price);							
						}
					}
					if (Grid_CheckTrade::col_click==6)
					{
						LPTSTR endPtr1;										
						int d_val1=_tcstod(first_st.m_volume ,&endPtr1);
						LPTSTR endPtr2;										
						int d_val2=_tcstod(next_st.m_volume,&endPtr2);						
						if (d_val1<d_val2)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_volume,swap_st.m_volume);

							
						}
					}
					if (Grid_CheckTrade::col_click==2)
					{
						LPTSTR endPtr1;										
						int d_val1=_tcstod(first_st.m_deal ,&endPtr1);
						LPTSTR endPtr2;										
						int d_val2=_tcstod(next_st.m_deal,&endPtr2);						
						if (d_val1<d_val2)
						{
							Grid_CheckTrade::m_st_grid_check_Grid_array.Shift(j,i-j);
							swap_st=Grid_CheckTrade::m_st_grid_check_Grid_array[i];
							CMTStr::Copy(first_st.m_deal,swap_st.m_deal);
						}
					}

				}				
	
			}
			
		}
		
	}
	    int r_count=Grid_CheckTrade::m_st_grid_check_Grid_array.Total();

		int grid_total=GetNumberRows();
		if (Grid_CheckTrade::insertFilterFlag==1)
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

void Grid_CheckTrade::ColValue_filter()
{

	    int val_type=0;	
		val_type=0;
		if (Grid_CheckTrade::insertFilterFlag==1 )
		{
		Grid_CheckTrade::m_st_grid_check_Grid_array.Clear();
		int noof_rowsInStruc=Grid_CheckTrade::m_st_grid_check_Array_Fill.Total();
		for(int fcount=0;fcount<noof_rowsInStruc;fcount++)
		{
			Grid_CheckTrade::st_grid_check m_st_Netposition={};
			m_st_Netposition=Grid_CheckTrade::m_st_grid_check_Array_Fill[fcount];
			int flag=0;				
			CString col_row_val[11];		
			col_row_val[0]=m_st_Netposition.m_CommentYN ;
			if (Grid_CheckTrade::col0_val.Trim().GetLength()>0)
			{
				col_row_val[0]=col_row_val[0].Mid(0,Grid_CheckTrade::col0_val.Trim().GetLength());
			}
			col_row_val[1]=m_st_Netposition.m_time ;
			if (Grid_CheckTrade::col1_val.Trim().GetLength()>0)
			{
				col_row_val[1]=col_row_val[1].Mid(0,Grid_CheckTrade::col1_val.Trim().GetLength());
				col_row_val[1]=col_row_val[1].Mid(0,10);
			}
			col_row_val[2]=m_st_Netposition.m_deal;
			if (Grid_CheckTrade::col2_val.Trim().GetLength()>0)
			{
				col_row_val[2]=col_row_val[2].Mid(0,Grid_CheckTrade::col2_val.Trim().GetLength());
			}
						
			col_row_val[3]=m_st_Netposition.m_order ;
			if (Grid_CheckTrade::col3_val.Trim().GetLength()>0)
			{
				col_row_val[3]=col_row_val[3].Mid(0,Grid_CheckTrade::col3_val.Trim().GetLength());
			}

			col_row_val[4]=m_st_Netposition.m_symbol;
			if (Grid_CheckTrade::col4_val.Trim().GetLength()>0)
			{
				col_row_val[4]=col_row_val[4].Mid(0,Grid_CheckTrade::col4_val.Trim().GetLength());
			}

			col_row_val[5]=m_st_Netposition.m_Type ;
			if (Grid_CheckTrade::col5_val.Trim().GetLength()>0)
			{
				col_row_val[5]=col_row_val[5].Mid(0,Grid_CheckTrade::col5_val.Trim().GetLength());
			}

			col_row_val[6]=m_st_Netposition.m_volume;
			boolean bool_col6=Check_numeric_col_filter1(Grid_CheckTrade::col6_val,col_row_val[6]);

			col_row_val[7]=m_st_Netposition.m_price  ;
			boolean bool_col7=Check_numeric_col_filter1(Grid_CheckTrade::col7_val,col_row_val[7]);

			col_row_val[8]=m_st_Netposition.m_comment ;
			if (Grid_CheckTrade::col8_val.Trim().GetLength()>0)
			{
				col_row_val[8]=col_row_val[8].Mid(0,Grid_CheckTrade::col8_val.Trim().GetLength());
			}

			col_row_val[9]=m_st_Netposition.m_OurComment  ;
			if (Grid_CheckTrade::col9_val.Trim().GetLength()>0)
			{
				col_row_val[9]=col_row_val[9].Mid(0,Grid_CheckTrade::col9_val.Trim().GetLength());
			}

			col_row_val[10]=m_st_Netposition.m_Checked;
			if (Grid_CheckTrade::col10_val.Trim().GetLength()>0)
			{
				col_row_val[10]=col_row_val[10].Mid(0,Grid_CheckTrade::col10_val.Trim().GetLength());
			}
			
			if((Grid_CheckTrade::col0_val.Trim()==col_row_val[0].Trim() || Grid_CheckTrade::col0_val.Trim()==L"ALL"||Grid_CheckTrade::col0_val.Trim()==L"") && (Grid_CheckTrade::col1_val.Trim()==col_row_val[1].Trim() || Grid_CheckTrade::col1_val.Trim()==L"ALL"||Grid_CheckTrade::col1_val.Trim()==L"") && (Grid_CheckTrade::col2_val.Trim()==col_row_val[2].Trim() || Grid_CheckTrade::col2_val.Trim()==L"ALL"||Grid_CheckTrade::col2_val.Trim()==L"")  && (Grid_CheckTrade::col3_val.Trim()==col_row_val[3].Trim() || Grid_CheckTrade::col3_val.Trim()==L"ALL"||Grid_CheckTrade::col3_val.Trim()==L"") && (Grid_CheckTrade::col4_val.Trim()==col_row_val[4].Trim() || Grid_CheckTrade::col4_val.Trim()==L"ALL"||Grid_CheckTrade::col4_val.Trim()==L"")   && (Grid_CheckTrade::col5_val.Trim()==col_row_val[5].Trim() || Grid_CheckTrade::col5_val.Trim()==L"ALL"||Grid_CheckTrade::col5_val.Trim()==L"")   && (bool_col6==true || Grid_CheckTrade::col6_val.Trim()==L"ALL"||Grid_CheckTrade::col6_val.Trim()==L"")   && (bool_col7==true || Grid_CheckTrade::col7_val.Trim()==L"ALL"||Grid_CheckTrade::col7_val.Trim()==L"")   && (Grid_CheckTrade::col8_val.Trim()==col_row_val[8].Trim() || Grid_CheckTrade::col8_val.Trim()==L"ALL"||Grid_CheckTrade::col8_val.Trim()==L"") && (Grid_CheckTrade::col9_val.Trim()==col_row_val[9].Trim() || Grid_CheckTrade::col9_val.Trim()==L"ALL"||Grid_CheckTrade::col9_val.Trim()==L"") &&(Grid_CheckTrade::col10_val==col_row_val[10] || Grid_CheckTrade::col10_val==L"ALL"||Grid_CheckTrade::col10_val==L""))
			{
				Grid_CheckTrade::m_st_grid_check_Grid_array.Add(&m_st_Netposition);
			}
		}
		}
		else
		{
			Grid_CheckTrade::m_st_grid_check_Grid_array.Assign(Grid_CheckTrade::m_st_grid_check_Array_Fill);
		}

		

	    int r_count=Grid_CheckTrade::m_st_grid_check_Grid_array.Total();

		int grid_total=GetNumberRows();
		if (Grid_CheckTrade::insertFilterFlag==1)
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