#include "stdafx.h"
#include "resource.h"
#include "NetPosGrid.h"
#include <afxdisp.h>
#include <time.h>
#include <locale.h>
#include "MainFrm.h"
#include "document.h"
#include <iostream>
#include "CNetPosTable.h"
#include "Netpos_Get_Data.h"
#include "cnetposdlg.h"
#include <iostream>
#include <fstream>
#include "stringbuffer.h"
#include "prettywriter.h"
#include "writer.h"
#include "T_Pre_Post_outstanding.h"
#include <cstdio>
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
BEGIN_MESSAGE_MAP(NetPosGrid,CUGCtrl)	
	ON_WM_SIZE()
	ON_WM_TIMER()		
END_MESSAGE_MAP()
int NetPosGrid::netpos_lock=0;
int NetPosGrid::int_igrore_comment=0;
int NetPosGrid::int_ignoreQty=0;
CMutex NetPosGrid::mutex_Symbol_ltp;
CString NetPosGrid::m_c_login=L"";
CString NetPosGrid::m_c_symbol=L"";
CString NetPosGrid::m_COL_VAL=L"";
const char* NetPosGrid::strcol="";
CString NetPosGrid::m_total=L"";
int NetPosGrid::value_row_no=0;
int NetPosGrid::filter_break=0;
int NetPosGrid::insertFilterFlag=0;
int NetPosGrid::menu_item_cheked=0;
int NetPosGrid::check_First=0;
_variant_t NetPosGrid::avarRecords;
int NetPosGrid::lock_data=0;
int NetPosGrid::intRows=0;
int NetPosGrid::lock_data_fill=0;
int NetPosGrid::Grid_Rows_Count=0;
int NetPosGrid::data_display=0;
CString  NetPosGrid::Str_Total_Bal=L"";
_bstr_t NetPosGrid::strShort("  order by t1.login asc,t1.symbol asc");
_bstr_t NetPosGrid::cellvalue("");
_bstr_t NetPosGrid::strFilter(" ");
_variant_t NetPosGrid::result;
long NetPosGrid::rgIndices[2];
_bstr_t NetPosGrid::bstr_currenttime("");
_bstr_t NetPosGrid::ignore0ty("");
_bstr_t NetPosGrid::ignoremain("");
_bstr_t NetPosGrid::ignorecomment("");
COLORREF NetPosGrid::old_color;
COLORREF NetPosGrid::new_color=RGB(255,255,255);

NetPosGrid::st_Netposition NetPosGrid::m_st_Netposition={};
NetPosGrid::NetpositionArray NetPosGrid::m_NetpositionArray;
NetPosGrid::SymbolMultiplyer NetPosGrid::m_SymbolMultiplyer;
NetPosGrid::st_multiplyer NetPosGrid::m_st_multiplyer={};
NetPosGrid::Symbol_rate NetPosGrid::m_Symbol_rate={};
NetPosGrid::Symbol_rateArray NetPosGrid::m_Symbol_rateArray;

NetPosGrid::NetpositionArray NetPosGrid::m_client_lost;

NetPosGrid::st_Netposition NetPosGrid::m_st_Netposition_Ratecal={};

int NetPosGrid::netpos_grid_total=0;
CUGCell NetPosGrid::cellSymbol;
CUGCell NetPosGrid::cellRate;
CUGCell NetPosGrid::cellNetqty;
CUGCell NetPosGrid::cellpl;
CUGCell NetPosGrid::cellpl_volume;
CUGCell NetPosGrid::cellLogin;
CUGCell NetPosGrid::cell_pl;
CUGCell NetPosGrid::cell_netqty;
CUGCell NetPosGrid::cell_balan;


CMutex NetPosGrid::str_grid_mutex;


CMutex NetPosGrid::str_grid_filter;

int NetPosGrid::first_time_update=0;

CString NetPosGrid::text_for_update=L"";

CEdit	NetPosGrid::m_taxt_total;

CString NetPosGrid::get_Text_fromGrid=L"";

int NetPosGrid::sub_rows_count=0;
CUGCell NetPosGrid::pl_cell;
CUGCell NetPosGrid::Final_Balance_cell;;
CUGCell NetPosGrid::temp_Cell ;

CString NetPosGrid::strSettext2=L"";

NetPosGrid::Client_Details_Array NetPosGrid::m_Client_Details_Array;

NetPosGrid::Client_Details NetPosGrid::m_Client_Details={};

NetPosGrid::NetpositionArray NetPosGrid::m_NetpositionArray_For_Grid;
NetPosGrid::st_Netposition NetPosGrid::m_st_Netposition_For_Grid={};
NetPosGrid::Netposition_Ignore_comment_Array NetPosGrid::m_Netposition_Ignore_comment_Array;

NetPosGrid::Client_Balance_Array NetPosGrid::m_Client_Balance_Array;
double NetPosGrid::Pre_balance=0;	
int NetPosGrid::new_client=0;
int NetPosGrid::row_position=0;

CString NetPosGrid::col0_val=L"";
CString NetPosGrid::col1_val=L"";
CString NetPosGrid::col2_val=L"";
CString NetPosGrid::col3_val=L"";
CString NetPosGrid::col4_val=L"";
CString NetPosGrid::col5_val=L"";
CString NetPosGrid::col6_val=L"";
CString NetPosGrid::col7_val=L"";
CString NetPosGrid::col8_val=L"";
CString NetPosGrid::col9_val=L"";
CString NetPosGrid::col10_val=L"";
CString NetPosGrid::col11_val=L"";
CString NetPosGrid::col12_val=L"";
CString NetPosGrid::col13_val=L"";
CString NetPosGrid::col14_val=L"";
CString NetPosGrid::col15_val=L"";
CString NetPosGrid::col16_val=L"";
CString NetPosGrid::col17_val=L"";
CString NetPosGrid::col18_val=L"";
CString NetPosGrid::col19_val=L"";
CString NetPosGrid::col20_val=L"";

NetPosGrid::Symbol_in_m_Array NetPosGrid::m_Symbol_in_m_Array;
NetPosGrid::login_in_m_Array NetPosGrid::m_login_in_m_Array;

 NetPosGrid::NetpositionArray NetPosGrid::m_NetpositionArray_For_Grid_Final;

int NetPosGrid::col_click=0;
int NetPosGrid::a_d=0;

extern CLogFile m_logfile_g;
/////////////////////////////////////////////////////////////////////////////

double getColumnSum_in_st(int col_index);
double getColumnSum_in_st(int col_index)
{
	double return_val=0;
	CUGCell m_cell;
	int total_rows=NetPosGrid::m_NetpositionArray_For_Grid.Total();
	NetPosGrid::st_Netposition st={};
	for (int i=0;i<total_rows;i++)
	{
		st=NetPosGrid::m_NetpositionArray_For_Grid[i];
		LPTSTR endPtr1;			
		double d_val1=0;
		if (col_index==8)
		{
			d_val1=_tcstod(st.m_Floating_Profit,&endPtr1);
		}	
		if (col_index==5)
		{
			d_val1=_tcstod(st.m_netqty,&endPtr1);
		}		
		return_val=return_val+d_val1;
		
	}
	return return_val;
}

double getColumnSum_in_st_O(int col_index);
double getColumnSum_in_st_O(int col_index)
{
	double return_val=0;
	CUGCell m_cell;
	int total_rows=NetPosGrid::m_NetpositionArray_For_Grid.Total();
	NetPosGrid::st_Netposition st={};
	for (int i=0;i<total_rows;i++)
	{
		st=NetPosGrid::m_NetpositionArray_For_Grid[i];

		CString str_login=st.m_login;
		if (str_login.Find('-')<0)
		{
			LPTSTR endPtr1;			
			double d_val1=0;
			if (col_index==8)
			{
				d_val1=_tcstod(st.m_Floating_Profit,&endPtr1);
			}	
			if (col_index==5)
			{
				d_val1=_tcstod(st.m_netqty,&endPtr1);
			}		
			return_val=return_val+d_val1;
		}
	}
	return return_val;
}

//boolean  Check_numeric_col_filter(CString  filter_value,CString  real_value);

UINT Update_Netposition(LPVOID pParam);


NetPosGrid::NetPosGrid()
{
	 t = CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S");
	 bstr_currenttime=t;	 
	 UGXPThemes::UseThemes(false);	
}

NetPosGrid::~NetPosGrid()
{
	
	UGXPThemes::CleanUp();	
}

void NetPosGrid::OnSheetSetup(int sheetNumber)
{
	int	nRow = 0, nCol = 0;	
	CUGCell cell;
	SetGridDefault(&cell);
	EnableExcelBorders(TRUE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	//SetUserSizingMode( FALSE );
	SetDefFont(0);
	SetSH_Width(0);		
	SetNumberCols(21);
	QuickSetText(0,-1,L"Login");
	SetColWidth(0,100);
	QuickSetText(1,-1,L"Name");
	SetColWidth(1,120);
	QuickSetText(2,-1,L"Symbol");	
	SetColWidth(2,100);			
	QuickSetText(3,-1,L"Pre_NetQty");
	SetColWidth(3,100);			
	QuickSetText(4,-1,L"Diff_NetQty");
	SetColWidth(4,100);
	QuickSetText(5,-1,L"NetQty");	
	SetColWidth(5,100);
	QuickSetText(6,-1,L"Average");
	SetColWidth(6,100);
	QuickSetText(7,-1,L"LastRate");
	SetColWidth(7,100);			
	QuickSetText(8,-1,L"PL");
	SetColWidth(8,140);
	QuickSetText(9,-1,L"Balance");
	SetColWidth(9,140);			
	QuickSetText(10,-1,L"LastUpdate");
	SetColWidth(10,160);
	QuickSetText(11,-1,L"Group1");
	SetColWidth(11,160);
	QuickSetText(12,-1,L"Group2");
	SetColWidth(12,160);
	QuickSetText(13,-1,L"Group3");
	SetColWidth(13,160);
	QuickSetText(14,-1,L"Checked Status");
	SetColWidth(14,80);		
	QuickSetText(15,-1,L"Checked Time");
	SetColWidth(15,130);
	QuickSetText(16,-1,L"Alloted Limit");
	SetColWidth(16,100);		
	QuickSetText(17,-1,L"Remark2");
	SetColWidth(17,100);								
	QuickSetText(18,-1,L"Standing Avg rate");
	SetColWidth(18,100);		
	QuickSetText(19,-1,L"SQ Balance");
	SetColWidth(19,100);								
	QuickSetText(20,-1,L"pl_volume");
	SetColWidth(20,0);	

	// Header font
	for(int i = 0; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}	
	srand((unsigned)time(NULL));
	SetTimer(0, 100, NULL);
	
}
void NetPosGrid::OnGetCell(int col,long row,CUGCell *cell)
{
	//NetPosGrid::m_NetpositionArray_For_Grid_Final.Assign(NetPosGrid::m_NetpositionArray);
	
		//m_logfile_g.LogEvent(L"Start OnGetCell");
		st_Netposition mst_grid={};
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
			if (NetPosGrid::insertFilterFlag==1)
			{
				rows_no=row-1;				
				if (row==0)
				{
					return;
				}
			}
			if (col==0)
			{				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_login;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==1)
			{
				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_Name ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==2)
			{				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_symbol  ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==3)
			{				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_pre_qty ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==4)
			{				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_incre_qty ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==5)
			{				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_netqty  ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==6)
			{				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_avg_rate  ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==7)
			{				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_last_rate   ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==8)
			{
				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_Floating_Profit   ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==9)
			{
				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_Balance    ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==10)
			{
				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_last_update     ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==11)
			{
				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_Group1     ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==12)
			{
				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_Group2     ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==13)
			{
				//m_logfile_g.LogEvent(L"COL 13");
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_Group3    ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==14)
			{
				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_Checked_Status     ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==15)
			{
				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_Checked_Time      ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==16)
			{
				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_Alloted_Limit       ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==17)
			{
				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_Remark2       ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==18)
			{
				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_Standing_Avg_rate       ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==19)
			{
				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_Sq_Balance       ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==20)
			{
				
				mst_grid=NetPosGrid::m_NetpositionArray_For_Grid_Final[rows_no];
				CString tmp=mst_grid.m_pl_volume       ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
		}
		//m_logfile_g.LogEvent(L"END OnGetCell");	
	
		
}



void NetPosGrid::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	GridTradeAndOrder::m_selected_login="";
	GridTradeAndOrder::m_selected_Name="";
	CString login = QuickGetText(0,1);
	CString name = QuickGetText(1,row);

	try
	{
    if(login != L"")
	{
	GridTradeAndOrder::m_selected_login=QuickGetText(0,row);
	GridTradeAndOrder::m_selected_Name=QuickGetText(1,row);
	OverViewOrderGrid::thred_kill=0;			
	}
	}
	catch(exception ex)
	{
	   throw ex;
	}
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
	if(nParam == CELLTYPE_IS_EDITABLE || string == "CELLTYPE_IS_EDITABLE")
	{
		StartEdit();
	}	

	if(QuickGetText(0,row)!=NULL )
	{
		
		if (row==0)
		{
			if(NetPosGrid::insertFilterFlag==0)
			{	
				ADD_overview m_tab_dlg;
				m_tab_dlg.DoModal();//Setp 1
			}
		}
		else
		{
			ADD_overview m_tab_dlg;
			m_tab_dlg.DoModal();
		}
	}
}	
			 

void NetPosGrid::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);	
	UNREFERENCED_PARAMETER(processed);
	NetPosGrid::col_click=col;
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
	
	CString strcolval1=L"";
	CString strcolval2=L"";
	CString strcolval3=L"";
	CString strcolval4=L"";
	CString strcolval5=L"";
	CString strcolval6=L"";
	CString strcolval7=L"";
	CString strcolval8=L"";
	CString strcolval9=L"";
	CString strcolval10=L"";
	CString strcolval11=L"";
	CString strcolval12=L"";
	CString strcolval13=L"";
	CString strcolval14=L"";
	CString strcolval15=L"";
	CString strcolval16=L"";
	CString strcolval17=L"";
	CString strcolval18=L"";
	int rows_total=GetNumberRows();
	if (NetPosGrid::insertFilterFlag==1)
	{
		if (rows_total==2)
		{
			return;
		}
	}
	else
	{
		if (rows_total==1)
		{
			return;
		}
	}
	CUGDataSource* cd;
	cd=GetDataSource(0);
	//cd->DeleteRow(GetNumberRows()-1);
	
	DeleteRow(rows_total-1);
	
	
	if (NetPosGrid::insertFilterFlag==1)
	{
		
		//cd->DeleteRow(0);
		strcolval1=QuickGetText(0,0);
		strcolval2=QuickGetText(1,0);
		strcolval3=QuickGetText(2,0);
		strcolval4=QuickGetText(3,0);
		strcolval5=QuickGetText(4,0);
		strcolval6=QuickGetText(5,0);
		strcolval7=QuickGetText(6,0);
		strcolval8=QuickGetText(7,0);
		strcolval9=QuickGetText(8,0);
		strcolval10=QuickGetText(9,0);
		strcolval11=QuickGetText(10,0);
		strcolval12=QuickGetText(11,0);
		strcolval13=QuickGetText(12,0);
		strcolval14=QuickGetText(13,0);
		strcolval15=QuickGetText(14,0);
		strcolval16=QuickGetText(15,0);
		strcolval17=QuickGetText(16,0);
		strcolval18=QuickGetText(17,0);
		DeleteRow(0);
		
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
		

	}
	else
	{
		SortBy( col, UG_SORT_DESCENDING );
		QuickSetCellType( m_iSortCol, -1, m_iArrowIndex );
		QuickSetCellTypeEx( m_iSortCol, -1, UGCT_SORTARROWUP );
		

	}	

	
	if (NetPosGrid::insertFilterFlag==1)
	{
		InsertRow(0);
		
		addItemToCombobox();						
		for (int col_count=0;col_count<18;col_count++)
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



			QuickSetText(0,0,strcolval1);
			QuickSetText(1,0,strcolval2);
			QuickSetText(2,0,strcolval3);
			QuickSetText(3,0,strcolval4);
			QuickSetText(4,0,strcolval5);
			QuickSetText(5,0,strcolval6);
			QuickSetText(6,0,strcolval7);
			QuickSetText(7,0,strcolval8);
			QuickSetText(8,0,strcolval9);
			QuickSetText(9,0,strcolval10);
			QuickSetText(10,0,strcolval11);
			QuickSetText(11,0,strcolval12);
			QuickSetText(12,0,strcolval13);
			QuickSetText(13,0,strcolval14);
			QuickSetText(14,0,strcolval15);
			QuickSetText(15,0,strcolval16);
			QuickSetText(16,0,strcolval17);
			QuickSetText(17,0,strcolval18);
		}
	}

	

	int CHECKNO=GetNumberRows();
	InsertRow(CHECKNO-1);			
	int col_no=GetNumberCols();
	for (int c1=0;c1<col_no;c1++)
	{
		CString strtemp=QuickGetText(c1,CHECKNO);
		QuickSetText(c1,CHECKNO-1,strtemp);
		QuickSetText(c1,CHECKNO,L"");
	}
	QuickSetText(2,GetNumberRows()-1,L"Total");
	CString tempval=L"";
	tempval.Format(L"%.2f",getColumnSum(8));
	QuickSetText(8,GetNumberRows()-1,tempval);
	RedrawAll();


}
int NetPosGrid::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{
	if(ID == UGCT_DROPLIST)
	{
		return OnDropList(ID, col, row, msg, param);
	}
}
int NetPosGrid::OnDropList(long ID,int col,long row,long msg,long param)
{	
	if (msg==103)
	{		
		if(NetPosGrid::insertFilterFlag==1 && row==0 )
		{
			NetPosGrid::filter_break=1;
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

			if(col==11)
			{
				if (strval!=L"")
				{
					col11_val=strval;					
				}
				else
				{
					col11_val=L"ALL";					
				}
			}

			if(col==12)
			{
				if (strval!=L"")
				{
					col12_val=strval;					
				}
				else
				{
					col12_val=L"ALL";					
				}
			}

			if(col==13)
			{
				if (strval!=L"")
				{
					col13_val=strval;					
				}
				else
				{
					col13_val=L"ALL";					
				}
			}

			if(col==14)
			{
				if (strval!=L"")
				{
					col14_val=strval;					
				}
				else
				{
					col14_val=L"ALL";					
				}
			}

			if(col==15)
			{
				if (strval!=L"")
				{
					col15_val=strval;					
				}
				else
				{
					col15_val=L"ALL";					
				}
			}

			if(col==16)
			{
				if (strval!=L"")
				{
					col16_val=strval;					
				}
				else
				{
					col16_val=L"ALL";					
				}
			}

			if(col==17)
			{
				if (strval!=L"")
				{
					col17_val=strval;					
				}
				else
				{
					col17_val=L"ALL";					
				}
			}

			if(col==18)
			{
				if (strval!=L"")
				{
					col18_val=strval;					
				}
				else
				{
					col18_val=L"ALL";					
				}
			}

			if(col==19)
			{
				if (strval!=L"")
				{
					col19_val=strval;					
				}
				else
				{
					col19_val=L"ALL";					
				}
			}

			if(col==20)
			{
				if (strval!=L"")
				{
					col20_val=strval;					
				}
				else
				{
					col20_val=L"ALL";					
				}
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

_bstr_t NetPosGrid::get_string(CString  MainStr,CString SepStr)
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



int NetPosGrid::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	if(NetPosGrid::insertFilterFlag==1 && row==0)
	{
		NetPosGrid::filter_break=1;
		
		CString  strval=L"";
		CUGCell cell;
		QuickSetText(col,row,string );
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

		if(col==11)
		{
			if (strval!=L"")
			{
				col11_val=strval;					
			}
			else
			{
				col11_val=L"ALL";					
			}
		}

		if(col==12)
		{
			if (strval!=L"")
			{
				col12_val=strval;					
			}
			else
			{
				col12_val=L"ALL";					
			}
		}

		if(col==13)
		{
			if (strval!=L"")
			{
				col13_val=strval;					
			}
			else
			{
				col13_val=L"ALL";					
			}
		}

		if(col==14)
		{
			if (strval!=L"")
			{
				col14_val=strval;					
			}
			else
			{
				col14_val=L"ALL";					
			}
		}

		if(col==15)
		{
			if (strval!=L"")
			{
				col15_val=strval;					
			}
			else
			{
				col15_val=L"ALL";					
			}
		}

		if(col==16)
		{
			if (strval!=L"")
			{
				col16_val=strval;					
			}
			else
			{
				col16_val=L"ALL";					
			}
		}

		if(col==17)
		{
			if (strval!=L"")
			{
				col17_val=strval;					
			}
			else
			{
				col17_val=L"ALL";					
			}
		}

		if(col==18)
		{
			if (strval!=L"")
			{
				col18_val=strval;					
			}
			else
			{
				col18_val=L"ALL";					
			}
		}

		if(col==19)
		{
			if (strval!=L"")
			{
				col19_val=strval;					
			}
			else
			{
				col19_val=L"ALL";					
			}
		}

		if(col==20)
		{
			if (strval!=L"")
			{
				col20_val=strval;					
			}
			else
			{
				col20_val=L"ALL";					
			}
		}
	    
	}
	return TRUE;
}
void NetPosGrid::OnMenuCommand(int col,long row,int section,int item)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(section);
	// init. local variables
	
	CMenu* pMenu;
	pMenu = GetPopupMenu();

	CMenu* submenu=pMenu->GetSubMenu(1);

switch( item )
{
case 2001:
	       {
					filter();
					break;
		   }
		  
case 1000:
		   {
			   if(submenu->GetMenuState(1000,MF_CHECKED))
			   {
			   
				   SetColWidth(0,0);
				  
				   submenu->CheckMenuItem(1000,MF_UNCHECKED);
			   }
			   else 
			   {
				   SetColWidth(0,120);
				   submenu->CheckMenuItem(1000,MF_CHECKED);
				  
			   }
                break;
		   }
case 1001:
		   {

		      
			   if(submenu->GetMenuState(1001,MF_CHECKED))
			   {
			   
				   SetColWidth(1,0);
				  
				  submenu->CheckMenuItem(1001,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(1,120);
				   submenu->CheckMenuItem(1001,MF_CHECKED);
			   }

			   break;

		   }
 case 1002:
		   {

		      
			   if(submenu->GetMenuState(1002,MF_CHECKED))
			   {
			   
				   SetColWidth(2,0);
				  
				   submenu->CheckMenuItem(1002,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(2,120);
				   submenu->CheckMenuItem(1002,MF_CHECKED);

			   }

			   break;

		   }
 case 1003:
		   {

		      
			   if(submenu->GetMenuState(1003,MF_CHECKED))
			   {
			   
				   SetColWidth(3,0);
				   submenu->CheckMenuItem(1003,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(3,120);
				   submenu->CheckMenuItem(1003,MF_CHECKED);
			   }

			   break;

		   }
 case 1004:
		   {

		      
			   if(submenu->GetMenuState(1004,MF_CHECKED))
			   {
			   
				   SetColWidth(4,0);
				  
				   submenu->CheckMenuItem(1004,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(4,120);
				   submenu->CheckMenuItem(1004,MF_CHECKED);
			   }

			   break;

		   }
 case 1005:
		   {

		      
			   if(submenu->GetMenuState(1005,MF_CHECKED))
			   {
			   
				   SetColWidth(5,0);
				  
				    submenu->CheckMenuItem(1005,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(5,120);
				   submenu->CheckMenuItem(1005,MF_CHECKED);
			   
			   }

			   break;

		   }
 case 1006:
		   {

		      
			   if(submenu->GetMenuState(1006,MF_CHECKED))
			   {
			   
				   SetColWidth(6,0);
				  
				  submenu->CheckMenuItem(1006,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(6,120);
				   submenu->CheckMenuItem(1006,MF_CHECKED);
			   }
			   break;
		   }
 case 1007:
		   {		      
			   if(submenu->GetMenuState(1007,MF_CHECKED))
			   {
			   
				   SetColWidth(7,0);
				  
				  submenu->CheckMenuItem(1007,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(7,120);
				   submenu->CheckMenuItem(1007,MF_CHECKED);
			   }

			   break;

		   }
 case 1008:
		   {

		      
			   if(submenu->GetMenuState(1008,MF_CHECKED))
			   {
			   
				   SetColWidth(8,0);
				  
				   submenu->CheckMenuItem(1008,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(8,120);
				   submenu->CheckMenuItem(1008,MF_CHECKED);
			   }

			   break;

		   }
 case 1009:
		   {

		      
			   if(submenu->GetMenuState(1009,MF_CHECKED))
			   {
			   
				   SetColWidth(9,0);
				  
				 submenu->CheckMenuItem(1009,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(9,120);
				   submenu->CheckMenuItem(1009,MF_CHECKED);
			   }

			   break;

		   }
 case 1010:
		   {

		      
			   if(submenu->GetMenuState(1010,MF_CHECKED))
			   {
			   
				   SetColWidth(10,0);
				  
				  submenu->CheckMenuItem(1010,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(10,120);
				   submenu->CheckMenuItem(1010,MF_CHECKED);
			   }

			   break;

		   }
 case 1011:
		   {

		      
			   if(submenu->GetMenuState(1011,MF_CHECKED))
			   {
			   
				   SetColWidth(11,0);
				  
				  submenu->CheckMenuItem(1011,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(11,120);
				   submenu->CheckMenuItem(1011,MF_CHECKED);
			   }

			   break;

		   }
 case 1012:
		   {

		      
			   if(submenu->GetMenuState(1012,MF_CHECKED))
			   {
			   
				   SetColWidth(12,0);
				  
				   submenu->CheckMenuItem(1012,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(12,120);
				   submenu->CheckMenuItem(1012,MF_CHECKED);
			   }

			   break;

		   }
 case 1013:
		   {

		      
			   if(submenu->GetMenuState(1013,MF_CHECKED))
			   {
			   
				   SetColWidth(13,0);
				  
				submenu->CheckMenuItem(1013,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(13,120);
				   submenu->CheckMenuItem(1013,MF_CHECKED);
			   }

			   break;

		   }
case 1014:
		   {

		      
			   if(submenu->GetMenuState(1014,MF_CHECKED))
			   {
			   
				   SetColWidth(14,0);
				  
				  submenu->CheckMenuItem(1014,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(14,120);
				   submenu->CheckMenuItem(1014,MF_CHECKED);
			   }

			   break;

		   }
case 1015:
		   {

		      
			   if(submenu->GetMenuState(1015,MF_CHECKED))
			   {
			   
				   SetColWidth(15,0);
				   submenu->CheckMenuItem(1015,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(15,120);
				   submenu->CheckMenuItem(1015,MF_CHECKED);
			   }

			   break;

		   }
case 1016:
		   {

		      
			   if(submenu->GetMenuState(1016,MF_CHECKED))
			   {
			   
				   SetColWidth(16,0);
				   submenu->CheckMenuItem(1016,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(16,120);
				   submenu->CheckMenuItem(1016,MF_CHECKED);
			   }

			   break;

		   }
case 1017:
		   {

		      
			   if(submenu->GetMenuState(1017,MF_CHECKED))
			   {
			   
				   SetColWidth(17,0);
				   submenu->CheckMenuItem(1017,MF_UNCHECKED);
			   }
			   else
			   {
				   SetColWidth(17,120);
				   submenu->CheckMenuItem(1017,MF_CHECKED);
			   }

			   break;
            }

	 }

    RedrawAll();
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
int NetPosGrid::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
{
	int retVal = 0;
	try
	{
	if( flags & UG_SORT_DESCENDING )
	{
		CUGCell *ptr = cell1;
		cell1 = cell2;
		cell2 = ptr;
	}

COleDateTime date1, date2;
switch ( m_iSortCol )
	{
case 0:
    
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

case 15:
		
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
	
	 }
	 catch(_com_error & ce)
			{
				AfxMessageBox(ce.Description()+L"   OnSortEvaluate");			
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
void NetPosGrid::OnTabSelected(int ID)
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

void NetPosGrid::OnSize(UINT nType, int cx, int cy)
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

void NetPosGrid::OnTimer(UINT nIDEvent)
{	
	
		//m_logfile_g.LogEvent(L"Start OnTimer");
		NetPosGrid::str_grid_mutex.Lock();
		int r_count=NetPosGrid::m_NetpositionArray_For_Grid_Final.Total();
		int grid_total=GetNumberRows();
		if (NetPosGrid::insertFilterFlag==1)
		{
				r_count=r_count+1;
		}		
		if (grid_total!=r_count)
		{			
			COutputWnd::m_wndOutputPos.SetNumberRows(r_count);		
			//RedrawAll();
		}
		else
		{			
				RedrawAll();			
		}
		  
		
	
		NetPosGrid::str_grid_mutex.Unlock();
		//m_logfile_g.LogEvent(L"End OnTimer");
	
}





void NetPosGrid::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();
	
	EnableMenu(TRUE);
	
	menu->AppendMenuW(MF_STRING|MF_UNCHECKED,2001,_T("Filter"));
	
	
	submenu.CreatePopupMenu();
	
		
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1000, _T("Login"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1001, _T("Name"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1002, _T("Symbol"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1003, _T("Pre_NetQty"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1004, _T("Diff_NetQty"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1005, _T("NetQty"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1006, _T("Average"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1007, _T("LastRate"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1008, _T("PL"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1009, _T("Balance"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1010, _T("LastUpdate"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1011, _T("Branch"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1012, _T("SubBranch"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1013, _T("Group3"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1014, _T("Checked Status"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1015, _T("Checked Time"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1016, _T("Alloted Limit"));
	submenu.AppendMenu(MF_STRING|MF_CHECKED, 1017, _T("Remark2"));

	
	menu->AppendMenu(MF_POPUP, (UINT)submenu.Detach(), _T("Columns Setting"));
	SetMenu(menu);
	// LPCSTR menuname="Columns Setting";
	             


	int menu_count =GetMenuItemCount(submenu);

	for(int i =0; i <menu_count;i++)
	{
		int id=GetMenuItemID(submenu,i);		
		submenu.EnableMenuItem(id,TRUE);
	}			
}

 int NetPosGrid::OnMenuStart( int iCol, long lRow, int iSection )
{
	
	UNREFERENCED_PARAMETER(iCol);
	UNREFERENCED_PARAMETER(lRow);

	if( iSection == UG_GRID )
	{
		return TRUE;
	}
	else
		return FALSE;
}

void NetPosGrid::filter()
{
	try
	{
	 CMenu *pMnenu;
	pMnenu= GetPopupMenu();

	if (NetPosGrid::insertFilterFlag==0)
	{
			addItemToCombobox();
			NetPosGrid::insertFilterFlag=1;
			InsertRow(0);
			for (int col_count=0;col_count<18;col_count++)
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
		NetPosGrid::insertFilterFlag=0;
		NetPosGrid::strFilter=" ";
		NetPosGrid::col0_val=L"";
		NetPosGrid::col1_val=L"";
		NetPosGrid::col2_val=L"";
		NetPosGrid::col3_val=L"";
		NetPosGrid::col4_val=L"";
		NetPosGrid::col5_val=L"";
		NetPosGrid::col6_val=L"";
		NetPosGrid::col7_val=L"";
		NetPosGrid::col8_val=L"";
		NetPosGrid::col9_val=L"";
		NetPosGrid::col10_val=L"";
		NetPosGrid::col11_val=L"";
		NetPosGrid::col12_val=L"";
		NetPosGrid::col13_val=L"";
		NetPosGrid::col14_val=L"";
		NetPosGrid::col15_val=L"";
		NetPosGrid::col16_val=L"";
		NetPosGrid::col17_val=L"";
		NetPosGrid::col18_val=L"";
		NetPosGrid::col19_val=L"";
		NetPosGrid::col20_val=L"";
		pMnenu->CheckMenuItem(2001,MF_UNCHECKED);
	}
	RedrawAll();
	}
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"   filter");			
	} 
 }

BOOLEAN  NetPosGrid::CheckvalueInArray(const CStringArray& arr,CString strval) 
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
 
void NetPosGrid::colShorting( int index)
{
	m_str_array.Clear();
	CString cstr=str[index];
	int str_len=cstr.GetLength();

	CString split_str=L"";
	for (int f=0;f<str_len;f++)
	{		
		if (cstr.Mid(f,1)!=L"\n")
		{
			split_str=split_str+cstr.Mid(f,1);
		}
		else
		{
			if (split_str.Trim().GetLength()>0 && split_str.Trim()!="ALL")
			{
				st_shorting m_st_shorting={};
				CMTStr::Copy(m_st_shorting.m_symbol,split_str);
				m_str_array.Add(&m_st_shorting);
			}
			split_str=L"";
		}
	}	
	int arr_count=m_str_array.Total();
	st_shorting  first_st={};
	st_shorting  next_st={};
	st_shorting  swap_st={};
	for (int f=0;f<arr_count;f++)
	{
		
		first_st=m_str_array[f] ;
		for (int j=f+1;j<arr_count;j++)
		{			
			next_st=m_str_array[j];			
			if (wcscmp(first_st.m_symbol,next_st.m_symbol)>0)
			{
				m_str_array.Shift(j,f-j);
				swap_st=m_str_array[f];
				first_st=swap_st;							
			}
		}
	}
	st_shorting st_str={};
	CString final_str=L"";
	for (int f=0;f<arr_count;f++)
	{
		st_str=m_str_array[f];
		CString temp_str=st_str.m_symbol ;
		final_str=final_str+L"\n"+temp_str;
	}
	str[index]=L"ALL"+final_str;
}
void NetPosGrid::addItemToCombobox()
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
	NetPosGrid::str_grid_filter.Lock();
	try
	{
		int rows=1;
		rows=m_NetpositionArray.Total();	
		CString str_val=L"";	
		for (int forcount=0;forcount<18;forcount++)
		{
			str[forcount]=L"ALL\n";		
		}
		for (int forcount=0;forcount<rows;forcount++)
		{
			st_Netposition m_st_Netposition={};
			m_st_Netposition=m_NetpositionArray[forcount];
			for (int clocount=0;clocount<18;clocount++)
			{											
					if (clocount==0)
					{
						str_val=m_st_Netposition.m_login;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr,str_val)==false && str_val!=L"")
						{
							str[0]=str[0]+str_val+L"\n";										
							arr.Add(str_val);							
						}
					}


					if (clocount==1)
					{
						str_val=m_st_Netposition.m_Name;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr1,str_val)==false  && str_val!=L"")
						{
							str[1]=str[1]+str_val+L"\n";										
							arr1.Add(str_val);
						}
					}


					if (clocount==2)
					{
						str_val=m_st_Netposition.m_symbol;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr2,str_val)==false  && str_val!=L"")
						{
							str[2]=str[2]+str_val+L"\n";										
							arr2.Add(str_val);
						}
					}



					if (clocount==3)
					{
						str_val=m_st_Netposition.m_pre_qty ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr3,str_val)==false  && str_val!=L"")
						{
							str[3]=str[3]+str_val+L"\n";										
							arr3.Add(str_val);
						}
					}

					if (clocount==4)
					{
						str_val=m_st_Netposition.m_incre_qty;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr4,str_val)==false  && str_val!=L"")
						{
							str[4]=str[4]+str_val+L"\n";										
							arr4.Add(str_val);
						}
					}
					if (clocount==5)
					{
						str_val=m_st_Netposition.m_netqty ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr5,str_val)==false  && str_val!=L"")
						{
							str[5]=str[5]+str_val+L"\n";										
							arr5.Add(str_val);
						}
					}
					if (clocount==6)
					{
						str_val=m_st_Netposition.m_avg_rate ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr6,str_val)==false  && str_val!=L"")
						{
							str[6]=str[6]+str_val+L"\n";										
							arr6.Add(str_val);
						}
					}
					if (clocount==7)
					{
						str_val=m_st_Netposition.m_last_rate ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr7,str_val)==false  && str_val!=L"")
						{
							str[7]=str[7]+str_val+L"\n";										
							arr7.Add(str_val);
						}
					}
					if (clocount==8)
					{
						str_val=m_st_Netposition.m_Floating_Profit ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr8,str_val)==false  && str_val!=L"")
						{
							str[8]=str[8]+str_val+L"\n";										
							arr8.Add(str_val);
						}
					}
					if (clocount==9)
					{
						str_val=m_st_Netposition.m_Balance ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr9,str_val)==false  && str_val!=L"")
						{
							str[9]=str[9]+str_val+L"\n";										
							arr9.Add(str_val);
						}
					}
					if (clocount==10)
					{
						str_val=m_st_Netposition.m_last_update ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr10,str_val)==false  && str_val!=L"")
						{
							str[10]=str[10]+str_val+L"\n";										
							arr10.Add(str_val);
						}
					}
					if (clocount==11)
					{
						str_val=m_st_Netposition.m_Group1 ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr11,str_val)==false  && str_val!=L"")
						{
							str[11]=str[11]+str_val+L"\n";										
							arr11.Add(str_val);
						}
					}
					if (clocount==12)
					{
						str_val=m_st_Netposition.m_Group2 ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr12,str_val)==false  && str_val!=L"")
						{
							str[12]=str[12]+str_val+L"\n";										
							arr12.Add(str_val);
						}
					}
					if (clocount==13)
					{
						str_val=m_st_Netposition.m_Group3 ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr13,str_val)==false  && str_val!=L"")
						{
							str[13]=str[13]+str_val+L"\n";										
							arr13.Add(str_val);
						}
					}
					if (clocount==14)
					{
						str_val=m_st_Netposition.m_Checked_Status;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr14,str_val)==false  && str_val!=L"")
						{
							str[14]=str[14]+str_val+L"\n";										
							arr14.Add(str_val);
						}
					}
					if (clocount==15)
					{
						str_val=m_st_Netposition.m_Checked_Time;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr15,str_val)==false  && str_val!=L"")
						{
							str[15]=str[15]+str_val+L"\n";										
							arr15.Add(str_val);
						}
					}
					if (clocount==16)
					{
						str_val=m_st_Netposition.m_Alloted_Limit;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr16,str_val)==false  && str_val!=L"")
						{
							str[16]=str[16]+str_val+L"\n";										
							arr16.Add(str_val);
						}
					}
					if (clocount==17)
					{
						str_val=m_st_Netposition.m_Remark2;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr17,str_val)==false  && str_val!=L"")
						{
							str[17]=str[17]+str_val+L"\n";										
							arr17.Add(str_val);
						}
					}								
			}												
		}
		for(int f=0;f<18;f++)
		{
			colShorting(f);
		}
		
	}
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"addItemToCombobox");			
	} 
	NetPosGrid::str_grid_filter.Unlock();
}
 

void NetPosGrid::OnSetup()
{
	try
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

		SetNumberCols( 17 );
		//SetNumberRows( 50 );

		m_iArrowIndex = AddCellType( &m_sortArrow );

		SetCurrentCellMode( 2 );

		UseHints( TRUE );

		SetSH_Width( 0 );


		QuickSetCellType( 0, -1, m_iArrowIndex );
		SortBy( 0, UG_SORT_ASCENDING );

		m_iSortCol = 0;
		m_bSortedAscending = TRUE;					
		run_check=0;	

		//database initilization
		CoInitialize(NULL);		
		hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");	
		if(SUCCEEDED(hr))
		{
		 hr=session.Open(connection);							
		}

	}
	 catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"   writeData");			
	} 
}
void NetPosGrid::Thread_start_st_netpos_update()
{
	AfxBeginThread(Update_Netposition, this);		
}
boolean  Check_numeric_col_filter(CString  filter_value,CString  real_value)
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
void NetPosGrid::gridFilter(int colno,int rows_count,CString col_value)
{
	NetPosGrid::str_grid_filter.Lock();
	try
	{
	CString getColvalue=L"";
	CString col_filter_val[18];	
	for(int c=0;c<18;c++)
	{
		col_filter_val[c]=QuickGetText(c,0);
	}
	int noof_filterdata_count=0;	
	int noof_rowsInStruc=m_NetpositionArray.Total();	
	for(int fcount=0;fcount<noof_rowsInStruc;fcount++)
	{
		st_Netposition m_st_Netposition={};
		m_st_Netposition=m_NetpositionArray[fcount];
		
		int flag=0;		
		
		CString col_row_val[18];
		
		col_row_val[0]=m_st_Netposition.m_login;
		if (col_filter_val[0].Trim().GetLength()>0)
		{
			col_row_val[0]=col_row_val[0].Mid(0,col_filter_val[0].Trim().GetLength());
		}
		col_row_val[1]=m_st_Netposition.m_Name ;
		if (col_filter_val[1].Trim().GetLength()>0)
		{
			col_row_val[1]=col_row_val[1].Mid(0,col_filter_val[1].Trim().GetLength());
		}
		col_row_val[2]=m_st_Netposition.m_symbol ;
		if (col_filter_val[2].Trim().GetLength()>0)
		{
			col_row_val[2]=col_row_val[2].Mid(0,col_filter_val[2].Trim().GetLength());
		}

		col_row_val[3]=m_st_Netposition.m_pre_qty ;		
		boolean bool_col3=Check_numeric_col_filter(col_filter_val[3],col_row_val[3]);				

		col_row_val[4]=m_st_Netposition.m_incre_qty;
		boolean bool_col4=Check_numeric_col_filter(col_filter_val[4],col_row_val[4]);

		col_row_val[5]=m_st_Netposition.m_netqty ;
		boolean bool_col5=Check_numeric_col_filter(col_filter_val[5],col_row_val[5]);

		col_row_val[6]=m_st_Netposition.m_avg_rate ;
		boolean bool_col6=Check_numeric_col_filter(col_filter_val[6],col_row_val[6]);

		col_row_val[7]=m_st_Netposition.m_last_rate ;
		boolean bool_col7=Check_numeric_col_filter(col_filter_val[7],col_row_val[7]);

		col_row_val[8]=m_st_Netposition.m_Floating_Profit ;
		boolean bool_col8=Check_numeric_col_filter(col_filter_val[8],col_row_val[8]);

		col_row_val[9]=m_st_Netposition.m_Balance ;
		boolean bool_col9=Check_numeric_col_filter(col_filter_val[9],col_row_val[9]);

		col_row_val[10]=m_st_Netposition.m_last_update ;
		if (col_filter_val[10].Trim().GetLength()>0)
		{
			col_row_val[10]=col_row_val[10].Mid(0,col_filter_val[10].Trim().GetLength());
		}
		col_row_val[11]=m_st_Netposition.m_Group1 ;
		if (col_filter_val[11].Trim().GetLength()>0)
		{
			col_row_val[11]=col_row_val[11].Mid(0,col_filter_val[11].Trim().GetLength());
		}
		col_row_val[12]=m_st_Netposition.m_Group2 ;
		if (col_filter_val[12].Trim().GetLength()>0)
		{
			col_row_val[12]=col_row_val[12].Mid(0,col_filter_val[12].Trim().GetLength());
		}
		col_row_val[13]=m_st_Netposition.m_Group3 ;
		if (col_filter_val[13].Trim().GetLength()>0)
		{
			col_row_val[13]=col_row_val[13].Mid(0,col_filter_val[13].Trim().GetLength());
		}
		col_row_val[14]=m_st_Netposition.m_Checked_Status;
		if (col_filter_val[14].Trim().GetLength()>0)
		{
			col_row_val[14]=col_row_val[14].Mid(0,col_filter_val[14].Trim().GetLength());
		}
		col_row_val[15]=m_st_Netposition.m_Checked_Time;
		if (col_filter_val[15].Trim().GetLength()>0)
		{
			col_row_val[15]=col_row_val[15].Mid(0,col_filter_val[15].Trim().GetLength());
		}
		col_row_val[16]=m_st_Netposition.m_Alloted_Limit;
		if (col_filter_val[16].Trim().GetLength()>0)
		{
			col_row_val[16]=col_row_val[16].Mid(0,col_filter_val[16].Trim().GetLength());
		}
		col_row_val[17]=m_st_Netposition.m_Remark2;
		if (col_filter_val[17].Trim().GetLength()>0)
		{
			col_row_val[17]=col_row_val[17].Mid(0,col_filter_val[17].Trim().GetLength());
		}

		
		if((col_filter_val[0].Trim()==col_row_val[0].Trim() || col_filter_val[0].Trim()==L"ALL"||col_filter_val[0].Trim()==L"") && (col_filter_val[1].Trim()==col_row_val[1].Trim() || col_filter_val[1].Trim()==L"ALL"||col_filter_val[1].Trim()==L"") && (col_filter_val[2].Trim()==col_row_val[2].Trim() || col_filter_val[2].Trim()==L"ALL"||col_filter_val[2].Trim()==L"")  && (bool_col3==true  || col_filter_val[3].Trim()==L"ALL"||col_filter_val[3].Trim()==L"")  && (bool_col4==true  ||  col_filter_val[4].Trim()==L"ALL"||col_filter_val[4].Trim()==L"")   && (bool_col5==true || col_filter_val[5].Trim()==L"ALL"||col_filter_val[5].Trim()==L"")   && (bool_col6==true || col_filter_val[6].Trim()==L"ALL"||col_filter_val[6].Trim()==L"")   && (bool_col7==true || col_filter_val[7].Trim()==L"ALL"||col_filter_val[7].Trim()==L"")   && (bool_col8==true || col_filter_val[8].Trim()==L"ALL"||col_filter_val[8].Trim()==L"") && (bool_col9==true || col_filter_val[9]==L"ALL"||col_filter_val[9]==L"") &&(col_filter_val[10]==col_row_val[10] || col_filter_val[10]==L"ALL"||col_filter_val[10]==L"")&&(col_filter_val[11]==col_row_val[11] || col_filter_val[11]==L"ALL"||col_filter_val[11]==L"")&&(col_filter_val[12]==col_row_val[12] || col_filter_val[12]==L"ALL"||col_filter_val[12]==L"") &&(col_filter_val[13]==col_row_val[13] || col_filter_val[13]==L"ALL"||col_filter_val[13]==L"")&&(col_filter_val[14]==col_row_val[14] || col_filter_val[14]==L"ALL"||col_filter_val[14]==L"")&&(col_filter_val[15]==col_row_val[15] || col_filter_val[15]==L"ALL"||col_filter_val[15]==L"")&&(col_filter_val[16]==col_row_val[16] || col_filter_val[16]==L"ALL"||col_filter_val[16]==L"")&&(col_filter_val[17]==col_row_val[17] || col_filter_val[17]==L"ALL"||col_filter_val[17]==L""))
		{						
				noof_filterdata_count=noof_filterdata_count+1;						
		}
		
	 }
	 } 	 
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"   Grid Filter");			
	} 

	NetPosGrid::str_grid_filter.Unlock();
}

int NetPosGrid::OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newcol);
	UNREFERENCED_PARAMETER(newrow);
	return TRUE;
}

void NetPosGrid::writeData()
{	
	try
	{
    CMenu* pMenu;
	pMenu = GetPopupMenu();

   CMenu* submenu = pMenu->GetSubMenu(1);


  rapidjson::Document d;	
  streampos size;
  char* allNewData = '\0';
  int flag;
  

 fstream file(_T("D:\\RapidJasonExample\\RapidJason\\RapidJason\\Item_Checked.txt"), ios::in|ios::ate);

 if(file)
  {

	 size = file.tellg();
	 int k=size;
	 k=k+1;
	 allNewData = new char [k];
	 for(int f=0;f<k;f++)
	 allNewData[f] = '\0';
     file.seekg (0, ios::beg);
	 file.read (allNewData, size);
	 file.flush();
  }
  
	 colarr.Clear(); 
	 if(!d.Parse<0>(allNewData).HasParseError())
    	 {
			 Value& rows = d["Netpos"]; 
			 assert(rows.IsArray());
             d.SetObject();
			 rapidjson::Value myArray(rapidjson::kArrayType);
			 rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
			 rapidjson::StringBuffer strbuf;
               
			 for (string::size_type  i = 0; i < rows.Size(); i++)
			 {
				    const char* strcol1;
					const char* strcol2;
					colsett cs={};
					strcol1 =rows[i]["ColName"].GetString();
					strcol2 =rows[i]["Visible"].GetString();
					  
					  /* strcol2="false";*/
					    colarr.Add(&cs);						 				 				 
				        const char* strcol;
					   int cols= GetNumberCols();
			         
				     for (int c=0;c<cols;c++)
					   {
						  if(CMTStr::Find( CA2T(strcol1),QuickGetText(c,-1))>=0)
						  {
                                
							  int Count=   submenu->GetMenuItemCount();
						     for(int i=0;i<=Count;i++)
							  {
								 int ID= submenu->GetMenuItemID(i);
							// int state= submenu->GetMenuState(ID,MF_CHECKED && MF_UNCHECKED)
								 if(  CMTStr::Find(CA2T(strcol2),L"True")>=0)
							      {
							   
									
									SetColWidth(c,120);
								    NetPosGrid::strcol= "True";
								  }
							      else if(submenu->GetMenuState(ID,MF_UNCHECKED))
								  { 
									
									SetColWidth(c,0);
									NetPosGrid::strcol= "False";
								  }
							   }
							}
						    RedrawCol(c);
					      }
					   
					   
			
				  char buff[1024];
				  rapidjson::Value vMemberName  (rapidjson:: kObjectType);
			      vMemberName.SetString(buff, strlen(buff), allocator);  
				
                  vMemberName.SetObject();
				  
                  vMemberName.AddMember("ColName",strcol1, allocator);				
				  vMemberName.AddMember("Visible",NetPosGrid::strcol,allocator);							
				  myArray.PushBack(vMemberName, allocator);
				
			  
			     }
			   
			    d.RemoveMember("Netpos");
			    d.AddMember("Netpos", myArray, allocator);			
			    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
			    d.Accept(writer);
				const char *jsonString = strbuf.GetString();
		        ofstream outputfile;
				outputfile.open("Item_Checked.txt", ios::out);   
				if (outputfile.is_open())
				{
					outputfile<<jsonString<<endl;
				    outputfile.close();
				}

		}
	 }
	 catch(_com_error & ce)
			{
				AfxMessageBox(ce.Description()+L"   writeData");			
			} 
		
}
//void NetPosGrid::update_rate_and_pl(CString symbol,double rate)
//{	
//	try
//	{
//	//m_logfile.LogEvent(L"Start NetPosGrid::update_rate_and_pl");
//	int row_no=GetNumberRows();
//	int f=0;
//	if (NetPosGrid::insertFilterFlag==1)
//	{
//		f=1;
//	}
//	for(f;f<row_no;f++)
//	{		
//		CUGCell cellSymbol, cellRate, cellNetqty, cellpl,cellpl_volume,cellLogin;
//		COutputWnd::m_wndOutputPos.GetCell(2, f, &cellSymbol);
//
//		COutputWnd::m_wndOutputPos.GetCell(5, f, &cellNetqty);
//		COutputWnd::m_wndOutputPos.GetCell(20, f, &cellpl_volume);
//		COutputWnd::m_wndOutputPos.GetCell(0, f, &cellLogin);
//		
//		CString strrate=L"";
//		
//		CString strsymbol=cellSymbol.GetText();
//		if (strsymbol.Trim().GetLength()>0)
//		{
//			strrate.Format(L"%.4lf",rate);
//			if (wcscmp(symbol,strsymbol)==0)
//			{
//				QuickSetText(7,f,strrate);										
//				double netqty=cellNetqty.GetNumber();
//				double plvolume=cellpl_volume.GetNumber();
//				plvolume=plvolume;
//				double value_with_last_rate=((rate*-netqty));
//				double pl=0;
//				pl=(plvolume+value_with_last_rate)*get_Multi(symbol);
//				pl=-pl;				
//				//pl=pl/10000;
//				CString str_pl=L"";
//				str_pl.Format(L"%.2lf",pl);
//				QuickSetText(8,f,str_pl);				
//				double finalbal=getBalance(cellLogin.GetText());								
//				//RedrawRow(f);
//			}
//			else
//			{
//				CUGCell cell_pl,cell_netqty,cell_balan;
//				GetCell(5,f,&cell_netqty);
//				GetCell(8,f,&cell_pl);
//				GetCell(19,f,&cell_balan);
//				double m_d_pl=cell_pl.GetNumber();
//				double m_d_netqty=cell_pl.GetNumber();
//				if (m_d_pl==0 && m_d_netqty==0)
//				{
//					CUGCell balance_cell;
//					GetCell(19,f,&balance_cell);
//					double pl=cell_balan.GetNumber();
//
//					CString str_pl=L"";
//					str_pl.Format(L"%.2lf",pl);
//					QuickSetText(8,f,str_pl);				
//				}
//			}
//		}
//	}
//	
//	CString tempval=L"";
//	tempval.Format(L"%.2f",getColumnSum(8));
//	NetPosGrid::m_taxt_total.SetWindowTextW(tempval);
//	int grd_row=GetNumberRows()-1;
//	CString strGridval=QuickGetText(2,grd_row);
//	if (strGridval==L"Total")
//	{
//		QuickSetText(8,grd_row,tempval);
//	}
//
//	RedrawAll();
//	}
//	catch(_com_error & ce)
//	{
//		AfxMessageBox(ce.Description()+L"  update_rate_and_pl");			
//	} 
//	//m_logfile.LogEvent(L"End NetPosGrid::update_rate_and_pl");
//}





//void NetPosGrid::update_rate_and_pl_byindex(CString symbol,double rate,int index)
//{		
//	try
//	{
//		//m_logfile.LogEvent(L"Start update_rate_and_pl_byindex");
//			
//		CUGCell cellSymbol, cellRate, cellNetqty, cellpl,cellpl_volume,cellLogin;
//		COutputWnd::m_wndOutputPos.GetCell(2, index, &cellSymbol);
//
//		COutputWnd::m_wndOutputPos.GetCell(5, index, &cellNetqty);
//		COutputWnd::m_wndOutputPos.GetCell(20, index, &cellpl_volume);
//		COutputWnd::m_wndOutputPos.GetCell(0, index, &cellLogin);
//		
//		CString strrate=L"";
//		
//		CString strsymbol=cellSymbol.GetText();
//		if (strsymbol.Trim().GetLength()>0)
//		{
//			strrate.Format(L"%.4lf",rate);
//			if (wcscmp(symbol,strsymbol)==0)
//			{
//				QuickSetText(7,index,strrate);										
//				double netqty=cellNetqty.GetNumber();
//				double plvolume=cellpl_volume.GetNumber();
//				plvolume=plvolume;
//				double value_with_last_rate=((rate*-netqty));
//				double pl=0;
//				pl=(plvolume+value_with_last_rate)*get_Multi(symbol);
//				pl=-pl;				
//				//pl=pl/10000;
//				CString str_pl=L"";
//				str_pl.Format(L"%.2lf",pl);
//				QuickSetText(8,index,str_pl);				
//				double finalbal=getBalance(cellLogin.GetText());								
//				//RedrawRow(f);
//			}
//			else
//			{
//				CUGCell cell_pl,cell_netqty,cell_balan;
//				GetCell(5,index,&cell_netqty);
//				GetCell(8,index,&cell_pl);
//				GetCell(19,index,&cell_balan);
//				double m_d_pl=cell_pl.GetNumber();
//				double m_d_netqty=cell_pl.GetNumber();
//				if (m_d_pl==0 && m_d_netqty==0)
//				{
//					CUGCell balance_cell;
//					GetCell(19,index,&balance_cell);
//					double pl=cell_balan.GetNumber();
//
//					CString str_pl=L"";
//					str_pl.Format(L"%.2lf",pl);
//					QuickSetText(8,index,str_pl);				
//				}
//			}
//		}
//	
//	}
//	catch(_com_error & ce)
//			{
//				AfxMessageBox(ce.Description()+L"   update_rate_and_pl_byindex");			
//			} 
//	//m_logfile.LogEvent(L"END update_rate_and_pl_byindex");
//}
//



double NetPosGrid::get_Multi(CString symbol)
{
	double return_val=0;
	try
	{	
		int row_no=m_SymbolMultiplyer.Total();
		for(int f=0;f<row_no;f++)
		{
			m_st_multiplyer=m_SymbolMultiplyer[f];		
			if (wcscmp(symbol,m_st_multiplyer.m_symbol)==0)
			{
				return_val=m_st_multiplyer.m_multiplyer ;
				break;
			}
		}
	}
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"   getBalance");			
	} 
	return return_val;
}

double NetPosGrid::getBalance(CString strlogin)
{
	double return_value=0;
		
	int rows_count=GetNumberRows();
	int i=0;
	if (NetPosGrid::insertFilterFlag==1)
	{
		i=1;
	}

	for (i;i<rows_count;i++)
	{
		CUGCell pl_login;
		COutputWnd::m_wndOutputPos.GetCell(0, i, &pl_login);
		CString str_login=L"";

		str_login=pl_login.GetText();
		if (wcscmp(str_login,strlogin)==0)
		{
			CUGCell pl_cell;
			COutputWnd::m_wndOutputPos.GetCell(8, i, &pl_cell);
			double newval=pl_cell.GetNumber();
			return_value=return_value+newval;
		}
	}


	CUGCell Final_Balance_cell;
	COutputWnd::m_wndOutputPos.GetCell(9, 0, &Final_Balance_cell);
	CString final_bal=L"";
	final_bal.Format(L"%.2lf",return_value);
	Final_Balance_cell.SetText(final_bal);

	rows_count=GetNumberRows();
	i=0;
	if (NetPosGrid::insertFilterFlag==1)
	{
		i=1;
	}
	for (i;i<rows_count;i++)
	{
		CUGCell pl_login;
		COutputWnd::m_wndOutputPos.GetCell(0, i, &pl_login);
		CString str_getvalue=L"";
		str_getvalue=pl_login.GetText();
		if (wcscmp(str_getvalue,strlogin)==0)
		{
			COutputWnd::m_wndOutputPos.SetCell(9,i,&Final_Balance_cell);		
			
		}
	}
	
	
	return return_value;
}




double NetPosGrid::getColumnSum(int col_index)
{
	double return_val=0;
	CUGCell m_cell;
	int total_rows=GetNumberRows();
	for (int i=0;i<total_rows;i++)
	{
		CString txtTotal=QuickGetText(2,i);
		if (txtTotal!=L"Total")
		{
			GetCell(col_index,i,&m_cell);
			double temp_double=m_cell.GetNumber();
			return_val=return_val+temp_double;
		}
	}
	return return_val;
}


	

void NetPosGrid::UpdatePre_Post_Position()
{
	
	CCommand<CAccessor<CT_Pre_Post_outstanding> > artists1;		
	if(SUCCEEDED(hr))
	{
		session.Open(connection);
		_bstr_t strCommand="";		
		strCommand=" get_position '" + NetPosGrid::bstr_currenttime + "'";        
		char* strCommand_char=(char*)strCommand;
		hr=artists1.Open(session,strCommand_char);							 					 		 				 
		int intRows=0;		 
		double t_d_m_Pre_NetQty=0;
		double t_d_m_Post_NetQty=0;
		CString strlogin=L"";
		CString strsymbol=L"";
		
		if(SUCCEEDED(hr))
		{	
			NetPosGrid::mutex_Symbol_ltp.Lock();
			while (artists1.MoveNext() == S_OK)
			{		
				t_d_m_Pre_NetQty=artists1.m_preval ;
				t_d_m_Post_NetQty=artists1.m_postval;
				strlogin=artists1.m_login;
				strsymbol=artists1.m_symbol;																				
				CString strt_d_m_Pre_NetQty=L"";
				strt_d_m_Pre_NetQty.Format(_T("%.0f"),t_d_m_Pre_NetQty);
				CString strt_d_m_Post_NetQty=L"";
				strt_d_m_Post_NetQty.Format(_T("%.0f"),t_d_m_Post_NetQty);


				int rows_count=NetPosGrid::m_NetpositionArray.Total();
				for(int f=0;f<rows_count;f++)
				{
					NetPosGrid::st_Netposition m_st_Netposition={};
					m_st_Netposition=NetPosGrid::m_NetpositionArray[f];
					CString str_Grid_Login=m_st_Netposition.m_login;
					CString str_Grid_Symbol=m_st_Netposition.m_symbol;
					CMTStr::Copy(m_st_Netposition.m_pre_qty,strt_d_m_Pre_NetQty);
					if (wcscmp(str_Grid_Login,strlogin)==0 && wcscmp(str_Grid_Symbol,strsymbol)==0)
					{					
						CMTStr::Copy(m_st_Netposition.m_incre_qty,strt_d_m_Post_NetQty);
						NetPosGrid::m_NetpositionArray.Update(f,&m_st_Netposition);
					}
					
				}
			}
			NetPosGrid::mutex_Symbol_ltp.Unlock();
			//RedrawAll();
			artists1.Close();	
			session.Close();
		}		 					
	}
}


//NetPosGrid::m_NetpositionArray
//Calculate Pl In Array by LTP

CString Get_Ltp_Symbol(CString StrSymbol);
CString Get_Ltp_Symbol(CString StrSymbol)
{
	CString str_sym=L"";
	int m_count=CMainFrame::m_symbol_array.Total() ;
	for (int f=0;f<m_count;f++)
	{
		CMainFrame::Symbol_Mapping m_ms={};
		m_ms=CMainFrame::m_symbol_array[f];
		if(wcscmp(m_ms.symbol ,StrSymbol)==0 )
		{	
			str_sym=m_ms.Mapping_symbol ;
			return str_sym ;
		}
	}
	return str_sym;
}
void get_login_balance_details(CString login);
UINT Update_Netposition(LPVOID pParam)
{

	CCommand<CAccessor<Netposition_table> > artists1;		
	CoInitialize(NULL);	
	CDataSource connection;
	CSession session;
	HRESULT hr;
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");	
	if(SUCCEEDED(hr))
	{
			 hr=session.Open(connection);
	}
	while (true)
	{			
		
		//database initilization
	   /*try
	   {*/
	    //m_logfile.LogEvent(L"Start update_rate_and_pl_byindex");
		//CMainFrame::int_currenttime
		NetPosGrid::str_grid_filter.Lock();
		NetPosGrid::m_NetpositionArray.Clear();
		if(SUCCEEDED(hr))
		{			 
			CString strCommand=L"";		
			strCommand.Format(L"exec NetPosClientWise '%d';",CMainFrame::int_currenttime); 			 
		     hr=artists1.Open(session,(LPCTSTR)strCommand);
            
			 if(SUCCEEDED(hr))
		     {				 
			      while (hr=artists1.MoveNext() == S_OK)
				  {		
					    CString strpre_netQty=L""; 
					    CString strDiff_netQty=L""; 
					    CString str_NetQty=L""; 
					    CString str_Average=L""; 
					    CString str_LastRate=L""; 
					    CString str_PL=L""; 
					    CString str_balance=L""; 
					    CString str_lastupdate=L""; 
						CString str_checked_time=L""; 
					    CString str_Alloted_Limit=L""; 
					    CString str_Standing_Avg_rate=L""; 
					    CString str_SQ_Balance=L""; 
						CString str_pl_volume=L""; 

					    NetPosGrid::st_Netposition mst={};
						CMTStr::Copy(mst.m_login,artists1.m_login);
						CMTStr::Copy(mst.m_Name,artists1.m_name);
						CMTStr::Copy(mst.m_symbol,artists1.m_symbol);

						/*if (wcscmp(artists1.m_symbol,L"GCJ71KG")==0)
						{
							int k=0;
						}*/

						//strpre_netQty.Format( _T("%.2f"), artists1.m_Pre_NetQty);
						CString str_m_Pre_NetQty=artists1.m_Pre_NetQty;
						if (str_m_Pre_NetQty.Find('.')>0)
						{
							double  dbPre_NetQty=_wtof(artists1.m_Pre_NetQty);
							str_m_Pre_NetQty.Format( _T("%.2f"), dbPre_NetQty);
							CMTStr::Copy(mst.m_pre_qty,str_m_Pre_NetQty);
						}
						else
						{
							CMTStr::Copy(mst.m_pre_qty,artists1.m_Pre_NetQty);
						}
						//strDiff_netQty.Format( _T("%.2f"), artists1.m_Diff_NetQty);


						str_m_Pre_NetQty=artists1.m_Diff_NetQty;
						if (str_m_Pre_NetQty.Find('.')>0)
						{
							double  dbPre_NetQty=_wtof(artists1.m_Diff_NetQty);
							str_m_Pre_NetQty.Format( _T("%.2f"), dbPre_NetQty);
							CMTStr::Copy(mst.m_incre_qty,str_m_Pre_NetQty);
						}
						else
						{
							CMTStr::Copy(mst.m_incre_qty,artists1.m_Diff_NetQty);
						}
						
						//str_NetQty.Format( _T("%.2f"), artists1.m_NetQty);


						str_m_Pre_NetQty=artists1.m_NetQty;
						if (str_m_Pre_NetQty.Find('.')>0)
						{
							double  dbPre_NetQty=_wtof(artists1.m_NetQty);
							str_m_Pre_NetQty.Format( _T("%.2f"), dbPre_NetQty);
							CMTStr::Copy(mst.m_netqty,str_m_Pre_NetQty);
						}
						else
						{
							CMTStr::Copy(mst.m_netqty,artists1.m_NetQty);
						}
			

						//str_Average.Format( _T("%.2f"), artists1.m_Average);
						CMTStr::Copy(mst.m_avg_rate ,artists1.m_Average) ;
						//str_LastRate.Format( _T("%.2f"), artists1.m_LastRate);
						CMTStr::Copy(mst.m_last_rate ,artists1.m_LastRate);
						//str_PL.Format( _T("%.2f"), artists1.m_PL);
						CMTStr::Copy(mst.m_Floating_Profit ,artists1.m_PL) ;
						//str_balance.Format( _T("%.2f"), artists1.m_balance);
						CMTStr::Copy(mst.m_Balance ,artists1.m_balance) ;

						//str_lastupdate.Format( _T("%d"), artists1.m_lastupdate);
						CMTStr::Copy(mst.m_last_update ,artists1.m_lastupdate);

						CMTStr::Copy(mst.m_Group1 ,artists1.m_Group1) ;
						CMTStr::Copy(mst.m_Group2 ,artists1.m_Group2) ;
						CMTStr::Copy(mst.m_Group3 ,artists1.m_Group3) ;
						CMTStr::Copy(mst.m_Checked_Status ,artists1.m_Checked_Status) ;						
						CMTStr::Copy(mst.m_Checked_Time ,artists1.m_checked_time);
					   // str_Alloted_Limit.Format( _T("%.2f"), artists1.m_Alloted_Limit);

						CMTStr::Copy(mst.m_Alloted_Limit ,artists1.m_Alloted_Limit);
						CMTStr::Copy(mst.m_Remark2 ,artists1.m_Remark2) ;

						//str_Standing_Avg_rate.Format( _T("%.2f"), artists1.m_Standing_Avg_rate);
						CMTStr::Copy(mst.m_Standing_Avg_rate ,artists1.m_Standing_Avg_rate);
						//str_SQ_Balance.Format( _T("%.2f"), artists1.m_SQ_Balance);
						CMTStr::Copy(mst.m_Sq_Balance , artists1.m_SQ_Balance);
						//str_pl_volume.Format( _T("%.2f"), artists1.m_pl_volume);
						CMTStr::Copy(mst.m_pl_volume ,artists1.m_pl_volume);
						NetPosGrid::m_NetpositionArray.Add(&mst);				
				  }

	   
			  }
			 artists1.Close();
		
		}
		else
		{
			session.Close();
			connection.Close();
			CoUninitialize();
			CoInitialize(NULL);	
			hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");	
			if(SUCCEEDED(hr))
			{
					 hr=session.Open(connection);
			}
		}
		
		NetPosGrid::str_grid_filter.Unlock();
		NetPosGrid::mutex_Symbol_ltp.Lock();
		NetPosGrid::m_client_lost.Assign(NetPosGrid::m_NetpositionArray);
		NetPosGrid::mutex_Symbol_ltp.Unlock();


			if (NetPosGrid::int_igrore_comment==0)
			{
			NetPosGrid::m_NetpositionArray_For_Grid.Clear();
			int noof_rowsInStruc=NetPosGrid::m_NetpositionArray.Total();	
			//m_logfile_g.LogEvent(L"Start Update_Netposition Step_3");	
			for(int fcount=0;fcount<noof_rowsInStruc;fcount++)
			{
				NetPosGrid::st_Netposition m_st_Netposition={};
				m_st_Netposition=NetPosGrid::m_NetpositionArray[fcount];
				int flag=0;				
				CString col_row_val[21];		
				col_row_val[0]=m_st_Netposition.m_login;
				if (NetPosGrid::col0_val.Trim().GetLength()>0)
				{
					col_row_val[0]=col_row_val[0].Mid(0,NetPosGrid::col0_val.Trim().GetLength());
				}
				col_row_val[1]=m_st_Netposition.m_Name ;
				if (NetPosGrid::col1_val.Trim().GetLength()>0)
				{
					col_row_val[1]=col_row_val[1].Mid(0,NetPosGrid::col1_val.Trim().GetLength());
				}
				col_row_val[2]=m_st_Netposition.m_symbol ;
				if (NetPosGrid::col2_val.Trim().GetLength()>0)
				{
					col_row_val[2]=col_row_val[2].Mid(0,NetPosGrid::col2_val.Trim().GetLength());
				}

				col_row_val[3]=m_st_Netposition.m_pre_qty ;		
				boolean bool_col3=Check_numeric_col_filter(NetPosGrid::col3_val,col_row_val[3]);				

				col_row_val[4]=m_st_Netposition.m_incre_qty;
				boolean bool_col4=Check_numeric_col_filter(NetPosGrid::col4_val,col_row_val[4]);

				col_row_val[5]=m_st_Netposition.m_netqty ;
				boolean bool_col5=Check_numeric_col_filter(NetPosGrid::col5_val,col_row_val[5]);

				col_row_val[6]=m_st_Netposition.m_avg_rate ;
				boolean bool_col6=Check_numeric_col_filter(NetPosGrid::col6_val,col_row_val[6]);

				col_row_val[7]=m_st_Netposition.m_last_rate ;
				boolean bool_col7=Check_numeric_col_filter(NetPosGrid::col7_val,col_row_val[7]);

				col_row_val[8]=m_st_Netposition.m_Floating_Profit ;
				boolean bool_col8=Check_numeric_col_filter(NetPosGrid::col8_val,col_row_val[8]);

				col_row_val[9]=m_st_Netposition.m_Balance ;
				boolean bool_col9=Check_numeric_col_filter(NetPosGrid::col9_val,col_row_val[9]);

				col_row_val[10]=m_st_Netposition.m_last_update ;
				if (NetPosGrid::col10_val.Trim().GetLength()>0)
				{
					col_row_val[10]=col_row_val[10].Mid(0,NetPosGrid::col10_val.Trim().GetLength());
				}
				col_row_val[11]=m_st_Netposition.m_Group1 ;
				if (NetPosGrid::col11_val.Trim().GetLength()>0)
				{
					col_row_val[11]=col_row_val[11].Mid(0,NetPosGrid::col11_val.Trim().GetLength());
				}
				col_row_val[12]=m_st_Netposition.m_Group2 ;
				if (NetPosGrid::col12_val.Trim().GetLength()>0)
				{
					col_row_val[12]=col_row_val[12].Mid(0,NetPosGrid::col12_val.Trim().GetLength());
				}
				col_row_val[13]=m_st_Netposition.m_Group3 ;
				if (NetPosGrid::col13_val.Trim().GetLength()>0)
				{
					col_row_val[13]=col_row_val[13].Mid(0,NetPosGrid::col13_val.Trim().GetLength());
				}
				col_row_val[14]=m_st_Netposition.m_Checked_Status;
				if (NetPosGrid::col14_val.Trim().GetLength()>0)
				{
					col_row_val[14]=col_row_val[14].Mid(0,NetPosGrid::col14_val.Trim().GetLength());
				}
				NetPosGrid::col15_val=m_st_Netposition.m_Checked_Time;
				if (NetPosGrid::col15_val.Trim().GetLength()>0)
				{
					col_row_val[15]=col_row_val[15].Mid(0,NetPosGrid::col15_val.Trim().GetLength());
				}
				col_row_val[16]=m_st_Netposition.m_Alloted_Limit;
				if (NetPosGrid::col16_val.Trim().GetLength()>0)
				{
					col_row_val[16]=col_row_val[16].Mid(0,NetPosGrid::col16_val.Trim().GetLength());
				}
				col_row_val[17]=m_st_Netposition.m_Remark2;
				if (NetPosGrid::col17_val.Trim().GetLength()>0)
				{
					col_row_val[17]=col_row_val[17].Mid(0,NetPosGrid::col17_val.Trim().GetLength());
				}

				col_row_val[18]=m_st_Netposition.m_Standing_Avg_rate;
				if (NetPosGrid::col18_val.Trim().GetLength()>0)
				{
					col_row_val[18]=col_row_val[18].Mid(0,NetPosGrid::col18_val.Trim().GetLength());
				}

				col_row_val[19]=m_st_Netposition.m_Sq_Balance;
				if (NetPosGrid::col19_val.Trim().GetLength()>0)
				{
					col_row_val[19]=col_row_val[19].Mid(0,NetPosGrid::col19_val.Trim().GetLength());
				}

				col_row_val[20]=m_st_Netposition.m_pl_volume;
				if (NetPosGrid::col20_val.Trim().GetLength()>0)
				{
					col_row_val[20]=col_row_val[20].Mid(0,NetPosGrid::col20_val.Trim().GetLength());
				}
		
				if((NetPosGrid::col0_val.Trim()==col_row_val[0].Trim() || NetPosGrid::col0_val.Trim()==L"ALL"||NetPosGrid::col0_val.Trim()==L"") && (NetPosGrid::col1_val.Trim()==col_row_val[1].Trim() || NetPosGrid::col1_val.Trim()==L"ALL"||NetPosGrid::col1_val.Trim()==L"") && (NetPosGrid::col2_val.Trim()==col_row_val[2].Trim() || NetPosGrid::col2_val.Trim()==L"ALL"||NetPosGrid::col2_val.Trim()==L"")  && (bool_col3==true  || NetPosGrid::col3_val.Trim()==L"ALL"||NetPosGrid::col3_val.Trim()==L"")  && (bool_col4==true  ||  NetPosGrid::col4_val.Trim()==L"ALL"||NetPosGrid::col4_val.Trim()==L"")   && (bool_col5==true || NetPosGrid::col5_val.Trim()==L"ALL"||NetPosGrid::col5_val.Trim()==L"")   && (bool_col6==true || NetPosGrid::col6_val.Trim()==L"ALL"||NetPosGrid::col6_val.Trim()==L"")   && (bool_col7==true || NetPosGrid::col7_val.Trim()==L"ALL"||NetPosGrid::col7_val.Trim()==L"")   && (bool_col8==true || NetPosGrid::col8_val.Trim()==L"ALL"||NetPosGrid::col8_val.Trim()==L"") && (bool_col9==true || NetPosGrid::col9_val==L"ALL"||NetPosGrid::col9_val==L"") &&(NetPosGrid::col10_val==col_row_val[10] || NetPosGrid::col10_val==L"ALL"||NetPosGrid::col10_val==L"")&&(NetPosGrid::col11_val==col_row_val[11] || NetPosGrid::col11_val==L"ALL"||NetPosGrid::col11_val==L"")&&(NetPosGrid::col12_val==col_row_val[12] || NetPosGrid::col12_val==L"ALL"||NetPosGrid::col12_val==L"") &&(NetPosGrid::col13_val==col_row_val[13] || NetPosGrid::col13_val==L"ALL"||NetPosGrid::col13_val==L"")&&(NetPosGrid::col14_val==col_row_val[14] || NetPosGrid::col14_val==L"ALL"||NetPosGrid::col14_val==L"")&&(NetPosGrid::col15_val==col_row_val[15] || NetPosGrid::col15_val==L"ALL"||NetPosGrid::col15_val==L"")&&(NetPosGrid::col16_val==col_row_val[16] || NetPosGrid::col16_val==L"ALL"||NetPosGrid::col16_val==L"")&&(NetPosGrid::col17_val==col_row_val[17] || NetPosGrid::col17_val==L"ALL"||NetPosGrid::col17_val==L"")&&(NetPosGrid::col18_val==col_row_val[17] || NetPosGrid::col18_val==L"ALL"||NetPosGrid::col18_val==L"")&&(NetPosGrid::col19_val==col_row_val[17] || NetPosGrid::col19_val==L"ALL"||NetPosGrid::col19_val==L"")&&(NetPosGrid::col20_val==col_row_val[17] || NetPosGrid::col20_val==L"ALL"||NetPosGrid::col20_val==L""))
				{						
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_login,m_st_Netposition.m_login);				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Name ,m_st_Netposition.m_Name) ;
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_symbol ,m_st_Netposition.m_symbol );				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_pre_qty ,m_st_Netposition.m_pre_qty) ;						
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_incre_qty ,m_st_Netposition.m_incre_qty);				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_netqty ,m_st_Netposition.m_netqty) ;				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_avg_rate ,m_st_Netposition.m_avg_rate );				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_last_rate ,m_st_Netposition.m_last_rate );				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Floating_Profit ,m_st_Netposition.m_Floating_Profit );				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Balance ,m_st_Netposition.m_Balance) ;				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_last_update ,m_st_Netposition.m_last_update) ;
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Group1 ,m_st_Netposition.m_Group1) ;
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Group2 ,m_st_Netposition.m_Group2 );
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Group3 ,m_st_Netposition.m_Group3 );
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Checked_Status ,m_st_Netposition.m_Checked_Status);
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Checked_Time ,m_st_Netposition.m_Checked_Time);
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Alloted_Limit ,m_st_Netposition.m_Alloted_Limit);
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Remark2 ,m_st_Netposition.m_Remark2);				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Standing_Avg_rate ,m_st_Netposition.m_Standing_Avg_rate);				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Sq_Balance ,m_st_Netposition.m_Sq_Balance);				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_pl_volume ,m_st_Netposition.m_pl_volume);	
					if (NetPosGrid::int_ignoreQty==1)
					{
						CString str_netqty=m_st_Netposition.m_netqty;
						if (wcscmp(str_netqty,L"0")!=0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Add(&NetPosGrid::m_st_Netposition_For_Grid);
						}						
					}
					else
					{
						NetPosGrid::m_NetpositionArray_For_Grid.Add(&NetPosGrid::m_st_Netposition_For_Grid);
					}
				}
		
			 }	
			 //m_logfile_g.LogEvent(L"Start Update_Netposition Step_4");	
			 }

			if (NetPosGrid::int_igrore_comment==1)
			{
				NetPosGrid::mutex_Symbol_ltp.Unlock();
				//st_Netposition_Ignore_comment
				NetPosGrid::m_Netposition_Ignore_comment_Array.Clear();

				NetPosGrid::mutex_Symbol_ltp.Lock();
				int client_total=NetPosGrid::m_login_in_m_Array.Total() ;
				int symbol_total=NetPosGrid::m_Symbol_in_m_Array.Total();
				NetPosGrid::mutex_Symbol_ltp.Unlock();
				for (int c=0;c<client_total;c++)
				{
					NetPosGrid::login_in_m m_login_in_m={};
					m_login_in_m=NetPosGrid::m_login_in_m_Array[c];
					CString str_login_m=m_login_in_m.V_login;					
					for (int s=0;s<symbol_total;s++)
					{
						NetPosGrid::Symbol_in_m m_symbol_in_m={};
						m_symbol_in_m=NetPosGrid::m_Symbol_in_m_Array[s];
						CString str_symbol=m_symbol_in_m.V_symbol ;
						NetPosGrid::mutex_Symbol_ltp.Lock();
						int net_pos_total=NetPosGrid::m_NetpositionArray.Total();	

						double m_d_pre_qty=0;
						double m_d_incre_qty=0;
						double m_d_netqty=0;
						double m_d_avg_rate=0;
						double m_d_Floating_Profit=0;
						double m_d_Balance=0;

						double m_p_pre_qty=0;
						double m_p_incre_qty=0;
						double m_p_netqty=0;
						double m_p_avg_rate=0;
						double m_p_Floating_Profit=0;
						double m_p_Balance=0;
						double m_d_last_rate=0;

						for(int n=0;n<net_pos_total;n++)
						{
							NetPosGrid::st_Netposition m_st_np={};
							m_st_np=NetPosGrid::m_NetpositionArray[n];
							CString str_login=m_st_np.m_login;
							if (str_login.Find('-')>0)
							{
								str_login=str_login.Mid(0,str_login.Find('-'));
							}
							if (wcscmp(str_login_m,str_login)==0 && wcscmp(str_symbol,m_st_np.m_symbol)==0)
							{
								LPTSTR endPtr1;																
								m_d_pre_qty=_tcstod(m_st_np.m_pre_qty, &endPtr1);						
								m_d_pre_qty=m_d_pre_qty+m_p_pre_qty;
								m_p_pre_qty=m_d_pre_qty;
								
								m_d_incre_qty=_tcstod(m_st_np.m_incre_qty, &endPtr1);						
								m_d_incre_qty=m_d_incre_qty+m_p_incre_qty;
								m_p_incre_qty=m_d_incre_qty;

								m_d_netqty=_tcstod(m_st_np.m_netqty , &endPtr1);				
								
								double net_total_qty=1;
								if ((m_d_netqty+m_p_netqty)!=0)
								{
									net_total_qty=m_d_netqty+m_p_netqty;
								}
								m_d_avg_rate=_tcstod(m_st_np.m_avg_rate , &endPtr1); 															
								m_d_avg_rate=(((m_p_avg_rate*m_p_netqty)+(m_d_netqty*m_d_avg_rate))/net_total_qty);
								m_d_avg_rate=abs(m_d_avg_rate);
								m_p_avg_rate=m_d_avg_rate;
								
								m_d_netqty=m_d_netqty+m_p_netqty;
								m_p_netqty=m_d_netqty;
								
								m_d_Floating_Profit=_tcstod(m_st_np.m_Floating_Profit , &endPtr1);				
								m_d_Floating_Profit=m_d_Floating_Profit+m_p_Floating_Profit;
								m_p_Floating_Profit=m_d_Floating_Profit;

								m_d_Balance=_tcstod(m_st_np.m_Balance, &endPtr1);				
								m_d_Balance=m_d_Balance+m_p_Balance;
								m_p_Balance=m_d_Balance;


								m_d_last_rate=_tcstod(m_st_np.m_last_rate, &endPtr1);				
							}
						}
						NetPosGrid::mutex_Symbol_ltp.Unlock();
						NetPosGrid::st_Netposition_Ignore_comment m_st_comment={};
						CMTStr::Copy(m_st_comment.m_login,str_login_m);
						CString str_name=L"";
						CString str_group1=L"";
						CString str_group2=L"";
						CString str_group3=L"";
						CString str_group4=L"";

						CString m_pre_qty_str=L"";
						m_pre_qty_str.Format(L"%.0f",m_d_pre_qty);
						CString m_incre_qty_str=L"";
						m_incre_qty_str.Format(L"%.0f",m_d_incre_qty);
						CString m_netqty_str=L"";
						m_netqty_str.Format(L"%.0f",m_d_netqty);
						CString m_avg_rate_str=L"";
						m_avg_rate_str.Format(L"%.0f",m_d_avg_rate);
						CString m_last_rate_str=L"";
						m_last_rate_str.Format(L"%.0f",m_d_last_rate);
						CString m_Floating_Profit_str=L"";
						m_Floating_Profit_str.Format(L"%.0f",m_d_Floating_Profit);
						CString m_Balance_str=L"";
						m_Balance_str.Format(L"%.0f",m_d_Balance);

						//Getting group and name of login
						int client_total=NetPosGrid::m_Client_Details_Array.Total();
						for (int cl=0;cl<client_total;cl++)
						{
							NetPosGrid::Client_Details m_cl={};
							m_cl=NetPosGrid::m_Client_Details_Array[cl];
							if (wcscmp(m_cl.V_login,str_login_m)==0)
							{
								str_name=m_cl.V_Name;
								str_group1=m_cl.client_group ;
								str_group2=m_cl.Client_Group1;
								str_group3=m_cl.Client_Group2;
								str_group4=m_cl.Client_Group4;
							}
						}
						//End of getting name and group of Login							
						if (m_d_Balance!=0 || m_d_netqty!=0)
						{
							CMTStr::Copy(m_st_comment.m_Name ,str_name);
							CMTStr::Copy(m_st_comment.m_symbol ,str_symbol);				
							CMTStr::Copy(m_st_comment.m_pre_qty ,m_pre_qty_str) ;						
							CMTStr::Copy(m_st_comment.m_incre_qty ,m_incre_qty_str);				
							CMTStr::Copy(m_st_comment.m_netqty ,m_netqty_str) ;				
							CMTStr::Copy(m_st_comment.m_avg_rate ,m_avg_rate_str );				
							CMTStr::Copy(m_st_comment.m_last_rate ,m_last_rate_str );				
							CMTStr::Copy(m_st_comment.m_Floating_Profit ,m_Floating_Profit_str );				
							CMTStr::Copy(m_st_comment.m_Balance ,m_Balance_str) ;				
							CMTStr::Copy(m_st_comment.m_last_update ,L"") ;
							CMTStr::Copy(m_st_comment.m_Group1 ,str_group1) ;
							CMTStr::Copy(m_st_comment.m_Group2 ,str_group2);
							CMTStr::Copy(m_st_comment.m_Group3 ,str_group3);
							CMTStr::Copy(m_st_comment.m_Checked_Status ,L"");
							CMTStr::Copy(m_st_comment.m_Checked_Time ,L"");
							CMTStr::Copy(m_st_comment.m_Alloted_Limit ,L"");
							CMTStr::Copy(m_st_comment.m_Remark2 ,L"");				
							CMTStr::Copy(m_st_comment.m_Standing_Avg_rate ,L"");				
							CMTStr::Copy(m_st_comment.m_Sq_Balance ,L"");				
							CMTStr::Copy(m_st_comment.m_pl_volume ,L"");
						
							NetPosGrid::m_Netposition_Ignore_comment_Array.Add(&m_st_comment);
						}
					}
				}





			NetPosGrid::m_NetpositionArray_For_Grid.Clear();
			int noof_rowsInStruc=NetPosGrid::m_Netposition_Ignore_comment_Array.Total();	
			for(int fcount=0;fcount<noof_rowsInStruc;fcount++)
			{
				NetPosGrid::st_Netposition_Ignore_comment m_st_Netposition={};
				m_st_Netposition=NetPosGrid::m_Netposition_Ignore_comment_Array[fcount];
				int flag=0;				
				CString col_row_val[21];		
				col_row_val[0]=m_st_Netposition.m_login;
				if (NetPosGrid::col0_val.Trim().GetLength()>0)
				{
					col_row_val[0]=col_row_val[0].Mid(0,NetPosGrid::col0_val.Trim().GetLength());
				}
				col_row_val[1]=m_st_Netposition.m_Name ;
				if (NetPosGrid::col1_val.Trim().GetLength()>0)
				{
					col_row_val[1]=col_row_val[1].Mid(0,NetPosGrid::col1_val.Trim().GetLength());
				}
				col_row_val[2]=m_st_Netposition.m_symbol ;
				if (NetPosGrid::col2_val.Trim().GetLength()>0)
				{
					col_row_val[2]=col_row_val[2].Mid(0,NetPosGrid::col2_val.Trim().GetLength());
				}

				col_row_val[3]=m_st_Netposition.m_pre_qty ;		
				boolean bool_col3=Check_numeric_col_filter(NetPosGrid::col3_val,col_row_val[3]);				

				col_row_val[4]=m_st_Netposition.m_incre_qty;
				boolean bool_col4=Check_numeric_col_filter(NetPosGrid::col4_val,col_row_val[4]);

				col_row_val[5]=m_st_Netposition.m_netqty ;
				boolean bool_col5=Check_numeric_col_filter(NetPosGrid::col5_val,col_row_val[5]);

				col_row_val[6]=m_st_Netposition.m_avg_rate ;
				boolean bool_col6=Check_numeric_col_filter(NetPosGrid::col6_val,col_row_val[6]);

				col_row_val[7]=m_st_Netposition.m_last_rate ;
				boolean bool_col7=Check_numeric_col_filter(NetPosGrid::col7_val,col_row_val[7]);

				col_row_val[8]=m_st_Netposition.m_Floating_Profit ;
				boolean bool_col8=Check_numeric_col_filter(NetPosGrid::col8_val,col_row_val[8]);

				col_row_val[9]=m_st_Netposition.m_Balance ;
				boolean bool_col9=Check_numeric_col_filter(NetPosGrid::col9_val,col_row_val[9]);

				col_row_val[10]=m_st_Netposition.m_last_update ;
				if (NetPosGrid::col10_val.Trim().GetLength()>0)
				{
					col_row_val[10]=col_row_val[10].Mid(0,NetPosGrid::col10_val.Trim().GetLength());
				}
				col_row_val[11]=m_st_Netposition.m_Group1 ;
				if (NetPosGrid::col11_val.Trim().GetLength()>0)
				{
					col_row_val[11]=col_row_val[11].Mid(0,NetPosGrid::col11_val.Trim().GetLength());
				}
				col_row_val[12]=m_st_Netposition.m_Group2 ;
				if (NetPosGrid::col12_val.Trim().GetLength()>0)
				{
					col_row_val[12]=col_row_val[12].Mid(0,NetPosGrid::col12_val.Trim().GetLength());
				}
				col_row_val[13]=m_st_Netposition.m_Group3 ;
				if (NetPosGrid::col13_val.Trim().GetLength()>0)
				{
					col_row_val[13]=col_row_val[13].Mid(0,NetPosGrid::col13_val.Trim().GetLength());
				}
				col_row_val[14]=m_st_Netposition.m_Checked_Status;
				if (NetPosGrid::col14_val.Trim().GetLength()>0)
				{
					col_row_val[14]=col_row_val[14].Mid(0,NetPosGrid::col14_val.Trim().GetLength());
				}
				NetPosGrid::col15_val=m_st_Netposition.m_Checked_Time;
				if (NetPosGrid::col15_val.Trim().GetLength()>0)
				{
					col_row_val[15]=col_row_val[15].Mid(0,NetPosGrid::col15_val.Trim().GetLength());
				}
				col_row_val[16]=m_st_Netposition.m_Alloted_Limit;
				if (NetPosGrid::col16_val.Trim().GetLength()>0)
				{
					col_row_val[16]=col_row_val[16].Mid(0,NetPosGrid::col16_val.Trim().GetLength());
				}
				col_row_val[17]=m_st_Netposition.m_Remark2;
				if (NetPosGrid::col17_val.Trim().GetLength()>0)
				{
					col_row_val[17]=col_row_val[17].Mid(0,NetPosGrid::col17_val.Trim().GetLength());
				}

				col_row_val[18]=m_st_Netposition.m_Standing_Avg_rate;
				if (NetPosGrid::col18_val.Trim().GetLength()>0)
				{
					col_row_val[18]=col_row_val[18].Mid(0,NetPosGrid::col18_val.Trim().GetLength());
				}

				col_row_val[19]=m_st_Netposition.m_Sq_Balance;
				if (NetPosGrid::col19_val.Trim().GetLength()>0)
				{
					col_row_val[19]=col_row_val[19].Mid(0,NetPosGrid::col19_val.Trim().GetLength());
				}

				col_row_val[20]=m_st_Netposition.m_pl_volume;
				if (NetPosGrid::col20_val.Trim().GetLength()>0)
				{
					col_row_val[20]=col_row_val[20].Mid(0,NetPosGrid::col20_val.Trim().GetLength());
				}
		
				if((NetPosGrid::col0_val.Trim()==col_row_val[0].Trim() || NetPosGrid::col0_val.Trim()==L"ALL"||NetPosGrid::col0_val.Trim()==L"") && (NetPosGrid::col1_val.Trim()==col_row_val[1].Trim() || NetPosGrid::col1_val.Trim()==L"ALL"||NetPosGrid::col1_val.Trim()==L"") && (NetPosGrid::col2_val.Trim()==col_row_val[2].Trim() || NetPosGrid::col2_val.Trim()==L"ALL"||NetPosGrid::col2_val.Trim()==L"")  && (bool_col3==true  || NetPosGrid::col3_val.Trim()==L"ALL"||NetPosGrid::col3_val.Trim()==L"")  && (bool_col4==true  ||  NetPosGrid::col4_val.Trim()==L"ALL"||NetPosGrid::col4_val.Trim()==L"")   && (bool_col5==true || NetPosGrid::col5_val.Trim()==L"ALL"||NetPosGrid::col5_val.Trim()==L"")   && (bool_col6==true || NetPosGrid::col6_val.Trim()==L"ALL"||NetPosGrid::col6_val.Trim()==L"")   && (bool_col7==true || NetPosGrid::col7_val.Trim()==L"ALL"||NetPosGrid::col7_val.Trim()==L"")   && (bool_col8==true || NetPosGrid::col8_val.Trim()==L"ALL"||NetPosGrid::col8_val.Trim()==L"") && (bool_col9==true || NetPosGrid::col9_val==L"ALL"||NetPosGrid::col9_val==L"") &&(NetPosGrid::col10_val==col_row_val[10] || NetPosGrid::col10_val==L"ALL"||NetPosGrid::col10_val==L"")&&(NetPosGrid::col11_val==col_row_val[11] || NetPosGrid::col11_val==L"ALL"||NetPosGrid::col11_val==L"")&&(NetPosGrid::col12_val==col_row_val[12] || NetPosGrid::col12_val==L"ALL"||NetPosGrid::col12_val==L"") &&(NetPosGrid::col13_val==col_row_val[13] || NetPosGrid::col13_val==L"ALL"||NetPosGrid::col13_val==L"")&&(NetPosGrid::col14_val==col_row_val[14] || NetPosGrid::col14_val==L"ALL"||NetPosGrid::col14_val==L"")&&(NetPosGrid::col15_val==col_row_val[15] || NetPosGrid::col15_val==L"ALL"||NetPosGrid::col15_val==L"")&&(NetPosGrid::col16_val==col_row_val[16] || NetPosGrid::col16_val==L"ALL"||NetPosGrid::col16_val==L"")&&(NetPosGrid::col17_val==col_row_val[17] || NetPosGrid::col17_val==L"ALL"||NetPosGrid::col17_val==L"")&&(NetPosGrid::col18_val==col_row_val[17] || NetPosGrid::col18_val==L"ALL"||NetPosGrid::col18_val==L"")&&(NetPosGrid::col19_val==col_row_val[17] || NetPosGrid::col19_val==L"ALL"||NetPosGrid::col19_val==L"")&&(NetPosGrid::col20_val==col_row_val[17] || NetPosGrid::col20_val==L"ALL"||NetPosGrid::col20_val==L""))
				{						
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_login,m_st_Netposition.m_login);				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Name ,m_st_Netposition.m_Name) ;
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_symbol ,m_st_Netposition.m_symbol );				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_pre_qty ,m_st_Netposition.m_pre_qty) ;						
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_incre_qty ,m_st_Netposition.m_incre_qty);				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_netqty ,m_st_Netposition.m_netqty) ;				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_avg_rate ,m_st_Netposition.m_avg_rate );				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_last_rate ,m_st_Netposition.m_last_rate );				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Floating_Profit ,m_st_Netposition.m_Floating_Profit );				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Balance ,m_st_Netposition.m_Balance) ;				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_last_update ,m_st_Netposition.m_last_update) ;
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Group1 ,m_st_Netposition.m_Group1) ;
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Group2 ,m_st_Netposition.m_Group2 );
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Group3 ,m_st_Netposition.m_Group3 );
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Checked_Status ,m_st_Netposition.m_Checked_Status);
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Checked_Time ,m_st_Netposition.m_Checked_Time);
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Alloted_Limit ,m_st_Netposition.m_Alloted_Limit);
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Remark2 ,m_st_Netposition.m_Remark2);				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Standing_Avg_rate ,m_st_Netposition.m_Standing_Avg_rate);				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_Sq_Balance ,m_st_Netposition.m_Sq_Balance);				
					CMTStr::Copy(NetPosGrid::m_st_Netposition_For_Grid.m_pl_volume ,m_st_Netposition.m_pl_volume);	
					if (NetPosGrid::int_ignoreQty==1)
					{
						CString str_netqty=m_st_Netposition.m_netqty;
						if (wcscmp(str_netqty,L"0")!=0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Add(&NetPosGrid::m_st_Netposition_For_Grid);
						}						
					}
					else
					{
						NetPosGrid::m_NetpositionArray_For_Grid.Add(&NetPosGrid::m_st_Netposition_For_Grid);
					}
				}
		
			 }	
			 }

	//m_logfile_g.LogEvent(L"Start Update_Netposition Step_5");	
	int t_rows=NetPosGrid::m_NetpositionArray_For_Grid.Total();
	NetPosGrid::st_Netposition first_st={};
	NetPosGrid::st_Netposition swap_st={};
	NetPosGrid::st_Netposition next_st={};
	

	int val_type=0;
	if (NetPosGrid::col_click==0||NetPosGrid::col_click==1||NetPosGrid::col_click==2 ||NetPosGrid::col_click==10 ||NetPosGrid::col_click==11 ||NetPosGrid::col_click==12 ||NetPosGrid::col_click==13 ||NetPosGrid::col_click==17)
	{
		val_type=0;
	}
	else
	{
		val_type=1;
	}
	for (int i=0;i<t_rows;i++)
	{
		first_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
		for (int j=i+1;j<t_rows;j++)
		{
			next_st=NetPosGrid::m_NetpositionArray_For_Grid[j];
			if (NetPosGrid::a_d==0)
			{
				if (val_type==0)
				{
					if (NetPosGrid::col_click==0)
					{
						if (wcscmp(first_st.m_login,next_st.m_login)>0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_login,swap_st.m_login);

							
						}
					}
					if (NetPosGrid::col_click==1)
					{
						if (wcscmp(first_st.m_Name,next_st.m_Name)>0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Name,swap_st.m_Name);

							
						}
					}
					if (NetPosGrid::col_click==2)
					{
						if (wcscmp(first_st.m_symbol ,next_st.m_symbol)>0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_symbol,swap_st.m_symbol);

							
						}
					}


					if (NetPosGrid::col_click==11)
					{
						if (wcscmp(first_st.m_Group1  ,next_st.m_Group1)>0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Group1,swap_st.m_Group1);

							
						}
					}

					if (NetPosGrid::col_click==12)
					{
						if (wcscmp(first_st.m_Group2  ,next_st.m_Group2)>0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Group2,swap_st.m_Group2);

							
						}
					}

					if (NetPosGrid::col_click==13)
					{
						if (wcscmp(first_st.m_Group3  ,next_st.m_Group3)>0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Group3,swap_st.m_Group3);

							
						}
					}

					if (NetPosGrid::col_click==10)
					{
						if (wcscmp(first_st.m_last_update   ,next_st.m_last_update)>0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_last_update,swap_st.m_last_update);

							
						}
					}

					if (NetPosGrid::col_click==17)
					{
						if (wcscmp(first_st.m_Remark2,next_st.m_Remark2)>0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Remark2,swap_st.m_Remark2);

							
						}
					}


					if (NetPosGrid::col_click==14)
					{
						if (wcscmp(first_st.m_Checked_Status,next_st.m_Checked_Status)>0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Checked_Status,swap_st.m_Checked_Status);

							
						}
					}


					if (NetPosGrid::col_click==15)
					{
						if (wcscmp(first_st.m_Checked_Time,next_st.m_Checked_Time)>0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Checked_Time,swap_st.m_Checked_Time);

							
						}
					}


				}
				else if (val_type==1)
				{
					if (NetPosGrid::col_click==3)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_pre_qty ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_pre_qty,&endPtr2);						
						if (d_val1>d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_pre_qty,swap_st.m_pre_qty);							
						}
					}

					if (NetPosGrid::col_click==4)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_new_qty  ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_new_qty,&endPtr2);						
						if (d_val1>d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_new_qty,swap_st.m_new_qty);							
						}
					}
					if (NetPosGrid::col_click==5)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_netqty   ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_netqty,&endPtr2);						
						if (d_val1>d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_netqty,swap_st.m_netqty);							
						}
					}
					if (NetPosGrid::col_click==6)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_avg_rate    ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_avg_rate,&endPtr2);						
						if (d_val1>d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_avg_rate,swap_st.m_avg_rate);							
						}
					}
					if (NetPosGrid::col_click==7)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_last_rate     ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_last_rate ,&endPtr2);						
						if (d_val1>d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_last_rate ,swap_st.m_last_rate );							
						}
					}


					if (NetPosGrid::col_click==8)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_Floating_Profit     ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_Floating_Profit ,&endPtr2);						
						if (d_val1>d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Floating_Profit ,swap_st.m_Floating_Profit );							
						}
					}

					if (NetPosGrid::col_click==9)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_Balance     ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_Balance ,&endPtr2);						
						if (d_val1>d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Balance,swap_st.m_Balance );							
						}
					}

					if (NetPosGrid::col_click==16)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_Alloted_Limit     ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_Alloted_Limit ,&endPtr2);						
						if (d_val1>d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Alloted_Limit,swap_st.m_Alloted_Limit );							
						}
					}

					if (NetPosGrid::col_click==18)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_Standing_Avg_rate     ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_Standing_Avg_rate ,&endPtr2);						
						if (d_val1>d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Standing_Avg_rate,swap_st.m_Standing_Avg_rate );							
						}
					}

					if (NetPosGrid::col_click==19)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_Sq_Balance   ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_Sq_Balance,&endPtr2);						
						if (d_val1>d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Sq_Balance,swap_st.m_Sq_Balance);							
						}
					}

					if (NetPosGrid::col_click==20)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_pl_volume,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_pl_volume,&endPtr2);						
						if (d_val1>d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_pl_volume,swap_st.m_pl_volume);							
						}
					}


				}
			}
			else if(NetPosGrid::a_d==1)
			{
				if (val_type==0)
				{
					if (NetPosGrid::col_click==0)
					{
						if (wcscmp(first_st.m_login,next_st.m_login)<0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_login,swap_st.m_login);
						}
					}
					if (NetPosGrid::col_click==1)
					{
						if (wcscmp(first_st.m_Name,next_st.m_Name)<0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Name,swap_st.m_Name);

							
						}
					}
					if (NetPosGrid::col_click==2)
					{
						if (wcscmp(first_st.m_symbol ,next_st.m_symbol)<0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_symbol,swap_st.m_symbol);

							
						}
					}


					if (NetPosGrid::col_click==11)
					{
						if (wcscmp(first_st.m_Group1  ,next_st.m_Group1)<0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Group1,swap_st.m_Group1);

							
						}
					}

					if (NetPosGrid::col_click==12)
					{
						if (wcscmp(first_st.m_Group2  ,next_st.m_Group2)<0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Group2,swap_st.m_Group2);

							
						}
					}

					if (NetPosGrid::col_click==13)
					{
						if (wcscmp(first_st.m_Group3  ,next_st.m_Group3)<0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Group3,swap_st.m_Group3);

							
						}
					}



					if (NetPosGrid::col_click==10)
					{
						if (wcscmp(first_st.m_last_update   ,next_st.m_last_update)<0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_last_update,swap_st.m_last_update);

							
						}
					}

					if (NetPosGrid::col_click==17)
					{
						if (wcscmp(first_st.m_Remark2,next_st.m_Remark2)<0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Remark2,swap_st.m_Remark2);

							
						}
					}



					if (NetPosGrid::col_click==14)
					{
						if (wcscmp(first_st.m_Checked_Status,next_st.m_Checked_Status)<0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Checked_Status,swap_st.m_Checked_Status);

							
						}
					}


					if (NetPosGrid::col_click==15)
					{
						if (wcscmp(first_st.m_Checked_Time,next_st.m_Checked_Time)<0)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Checked_Time,swap_st.m_Checked_Time);

							
						}
					}


				}
				else if (val_type==1)
				{
					if (NetPosGrid::col_click==3)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_pre_qty ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_pre_qty,&endPtr2);						
						if (d_val1<d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_pre_qty,swap_st.m_pre_qty);							
						}
					}

					if (NetPosGrid::col_click==4)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_new_qty  ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_new_qty,&endPtr2);						
						if (d_val1<d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_new_qty,swap_st.m_new_qty);							
						}
					}
					if (NetPosGrid::col_click==5)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_netqty   ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_netqty,&endPtr2);						
						if (d_val1<d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_netqty,swap_st.m_netqty);							
						}
					}
					if (NetPosGrid::col_click==6)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_avg_rate    ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_avg_rate,&endPtr2);						
						if (d_val1<d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_avg_rate,swap_st.m_avg_rate);							
						}
					}
					if (NetPosGrid::col_click==7)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_last_rate     ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_last_rate ,&endPtr2);						
						if (d_val1<d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_last_rate ,swap_st.m_last_rate );							
						}
					}


					if (NetPosGrid::col_click==8)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_Floating_Profit     ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_Floating_Profit ,&endPtr2);						
						if (d_val1<d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Floating_Profit ,swap_st.m_Floating_Profit );							
						}
					}

					if (NetPosGrid::col_click==9)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_Balance     ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_Balance ,&endPtr2);						
						if (d_val1<d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Balance,swap_st.m_Balance );							
						}
					}

					if (NetPosGrid::col_click==16)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_Alloted_Limit     ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_Alloted_Limit ,&endPtr2);						
						if (d_val1<d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Alloted_Limit,swap_st.m_Alloted_Limit );							
						}
					}

					if (NetPosGrid::col_click==18)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_Standing_Avg_rate     ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_Standing_Avg_rate ,&endPtr2);						
						if (d_val1<d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Standing_Avg_rate,swap_st.m_Standing_Avg_rate );							
						}
					}

					if (NetPosGrid::col_click==19)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_Sq_Balance   ,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_Sq_Balance,&endPtr2);						
						if (d_val1<d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_Sq_Balance,swap_st.m_Sq_Balance);							
						}
					}

					if (NetPosGrid::col_click==20)
					{
						LPTSTR endPtr1;										
						double d_val1=_tcstod(first_st.m_pl_volume,&endPtr1);
						LPTSTR endPtr2;										
						double d_val2=_tcstod(next_st.m_pl_volume,&endPtr2);						
						if (d_val1<d_val2)
						{
							NetPosGrid::m_NetpositionArray_For_Grid.Shift(j,i-j);
							swap_st=NetPosGrid::m_NetpositionArray_For_Grid[i];
							CMTStr::Copy(first_st.m_pl_volume,swap_st.m_pl_volume);							
						}
					}


    			}
			}
			
		}
		
	}
	//m_logfile_g.LogEvent(L"Start Update_Netposition Step_6");	
	//End of Updating Data In New Structure
	NetPosGrid::st_Netposition N_st={};
	CMTStr::Copy(N_st.m_login ,L"Total:-");
	CString tempval=L"";
	tempval.Format(L"%.2f",getColumnSum_in_st_O(8));
	CMTStr::Copy(N_st.m_Floating_Profit,tempval);
	CString str_balance=tempval;
	
	tempval.Format(L"%.2f",getColumnSum_in_st_O(5));
	CMTStr::Copy(N_st.m_netqty,tempval);
	NetPosGrid::m_NetpositionArray_For_Grid.Add(&N_st);		

	NetPosGrid::str_grid_mutex.Lock();
	NetPosGrid::m_NetpositionArray_For_Grid_Final.Assign(NetPosGrid::m_NetpositionArray_For_Grid);
	NetPosGrid::Str_Total_Bal=str_balance;
	
	
	NetPosGrid::str_grid_mutex.Unlock();
}


	return 0;
}

	

