#include "stdafx.h"
#include "resource.h"
#include "OrderGrid.h"
#include <afxdisp.h>
#include <time.h>
#include <locale.h>
#include "MainFrm.h"
#include "document.h"
#include <iostream>
#include "CTradeOrder.h"
#include "NetPosGrid.h"
#include "DataTradeFilter.h"
#include "Login.h"
#include "Client_Table.h"
#include "Order_Table.h"
using namespace std;
using namespace rapidjson;
#import "C:\Program Files\Common Files\System\ADO\msado15.dll"\
no_namespace rename("EOF", "EndOfFile")
#define WM_MY_THREAD_MESSAGE					WM_APP+100
#define WM_MY_THREAD_MESSAGE_ROWSNO				WM_APP+101
#define WM_MY_THREAD_MESSAGE_REFRESH			WM_APP+102
#define GRID_ROWS_COUNT							WM_APP+103
#define DELETE_ROW	     						WM_APP+104
#define DISPLAYDATA_NETPOSITON_FIRSTTIME		WM_APP+105
#define DISPLAYDATA_NETPOSITION_UPDATEANDINSERT	WM_APP+106
#define UPDATEGRID_BY_RATE						WM_APP+107
#define NETPOS_GRID_ROWS_COUNT					WM_APP+108
#define msg_getcellSymbol						WM_APP+109
#define msg_getcellNetqty						WM_APP+110
#define msg_getcellpl_volume					WM_APP+111
#define msg_getcellLogin						WM_APP+112
#define msg_getcell_netqty						WM_APP+113
#define msg_getcell_pl							WM_APP+114
#define msg_getcell_balan						WM_APP+115
#define msg_SetTextValue						WM_APP+116
#define msg_GetTextValue						WM_APP+117
#define msg_redraw_ALL							WM_APP+118
#define msg_sub_grid_rows_count					WM_APP+119
#define msg_getpl_cell							WM_APP+120
#define msg_gettemp_cell						WM_APP+121
#define msgGet_order_grid_rowcoun				WM_APP+122
#define msgGet_order_grid_text					WM_APP+123
#define msgOrderGrid_rowDelete					WM_APP+124
#define msgSet_order_grid_text					WM_APP+125
#define msgOrdergrid_cellFormat					WM_APP+126
#define msgSet_Norow_order_grid					WM_APP+127
#define msgOrderGrid_Redrawall					WM_APP+128
#define msgGet_Netpos_grid_text_thread1			WM_APP+129
#define msgGet_Netpos_grid_text_thread2			WM_APP+130
#define msgSetTextValue_2						WM_APP+131

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
BEGIN_MESSAGE_MAP(OrderGrid,CUGCtrl)	
	ON_WM_SIZE()
	ON_WM_TIMER()	

	ON_MESSAGE(msgOrderGrid_Redrawall,OrderGrid_Redrawall)
	ON_MESSAGE(msgSet_Norow_order_grid,Set_Norow_order_grid)
	ON_MESSAGE(msgOrdergrid_cellFormat,Ordergrid_cellFormat)
	ON_MESSAGE(msgSet_order_grid_text,Set_order_grid_text)
	ON_MESSAGE(msgOrderGrid_rowDelete,OrderGrid_rowDelete)
	ON_MESSAGE(msgGet_order_grid_text,Get_order_grid_text)
	ON_MESSAGE(msgGet_order_grid_rowcoun,Get_order_grid_rowcount)	
	ON_MESSAGE(WM_MY_THREAD_MESSAGE, OnThreadMessage)
	ON_MESSAGE(WM_MY_THREAD_MESSAGE_ROWSNO, OnThreadMessage_RowsNo)		
	ON_MESSAGE(WM_MY_THREAD_MESSAGE_REFRESH, GridRefresh)		
	ON_MESSAGE(GRID_ROWS_COUNT, GridRowCount)		
	ON_MESSAGE(DELETE_ROW, RowDelete)						
END_MESSAGE_MAP()

CString OrderGrid::str_orderGrid_settext;
CString OrderGrid::ordergrid_text=L"";
int OrderGrid::grid_rows_count=0;
int OrderGrid::filter_break=0;
int OrderGrid::insertFilterFlag=0;
int OrderGrid::check_First=0;
_variant_t OrderGrid::avarRecords;
int OrderGrid::lock_data=0;
int OrderGrid::intRows=0;
int OrderGrid::lock_data_fill=0;
int OrderGrid::Grid_Rows_Count=0;
_bstr_t OrderGrid::strShort(" DT_SetupTime desc");
_bstr_t OrderGrid::cellvalue("");
_bstr_t OrderGrid::strFilter(" and Plugin_Status not in ('OKAY','DEL') ");
_variant_t OrderGrid::result;
long OrderGrid::rgIndices[2];

CString OrderGrid::str_symbol_for_rate=L"";
double  OrderGrid::dbl_rate=0;
CSocket OrderGrid::m_Client;
OrderGrid::st_Order_UpdateArray OrderGrid::m_st_Order_UpdateArray;
OrderGrid::st_Order_Update OrderGrid::m_st_Order_Update={};
OrderGrid::st_Order_Update OrderGrid::m_cc_th={};
OrderGrid::St_Client_balanceArray OrderGrid::m_St_Client_balanceArray;

OrderGrid::m_client_Array OrderGrid::m_client_list;

OrderGrid::St_Client_balance OrderGrid::m_St_Client_balance={};
OrderGrid::St_Client OrderGrid::m_St_Client_1={};
OrderGrid::St_Client OrderGrid::m_St_Client_2={};
OrderGrid::St_Client OrderGrid::m_St_Client_3={};
OrderGrid::St_Client OrderGrid::m_St_Client_4={};
OrderGrid::St_Client OrderGrid::m_St_Client_5={};

CMutex OrderGrid::m_order_mutex;
int OrderGrid::col_click=0;
int OrderGrid::a_d=0;

OrderGrid::st_Order_UpdateArray OrderGrid::m_st_Order_GridArray;


CString OrderGrid::str_text_Update_Final_Balance=L"";

CString OrderGrid::str_orderGrid_gettext_2=L"";

CMutex OrderGrid::mutex_client_list;
CMutex OrderGrid::mutex_client_balance;

int OrderGrid::first_time_data_Received_YN=0;

HRESULT hrn;
CDataSource connection_update;
CSession session_update;	
CCommand<CNoAccessor, CNoRowset> cmd;
UINT update_data_PBNPS_Order(void*);

CLogFile m_logfile_g;


CString OrderGrid::col0_val=L"";
CString OrderGrid::col1_val=L"";
CString OrderGrid::col2_val=L"";
CString OrderGrid::col3_val=L"";
CString OrderGrid::col4_val=L"";
CString OrderGrid::col5_val=L"";
CString OrderGrid::col6_val=L"";
CString OrderGrid::col7_val=L"";
CString OrderGrid::col8_val=L"";
CString OrderGrid::col9_val=L"";
CString OrderGrid::col10_val=L"";
CString OrderGrid::col11_val=L"";
CString OrderGrid::col12_val=L"";
CString OrderGrid::col13_val=L"";
CString OrderGrid::col14_val=L"";
CString OrderGrid::col15_val=L"";



UINT RequestHandler(LPVOID pParam);

OrderGrid::OrderGrid()
{
	UGXPThemes::UseThemes(false);
}


BOOLEAN Check_value_In_list(CString login);


BOOLEAN Check_value_In_list(CString login)
{	
	//m_logfile_g.LogEvent(L"Check_value_In_list");
	boolean  return_value=false  ;
	OrderGrid::mutex_client_list.Lock();
	int client_total=OrderGrid::m_client_list.Total();
	OrderGrid::mutex_client_list.Unlock();
	for (int f=0;f<client_total;f++)
	{
		//CString client_from_list=L"";
		OrderGrid::mutex_client_list.Lock();
		OrderGrid::m_St_Client_1=OrderGrid::m_client_list[f];
		OrderGrid::mutex_client_list.Unlock();
		//client_from_list=OrderGrid::m_St_Client_1.Login;
		if (wcscmp(OrderGrid::m_St_Client_1.Login,login)==0)
		{
			return_value=true;
			return return_value;
		}
	}
	//m_logfile_g.LogEvent(L"END Check_value_In_list");
	return return_value;
}

OrderGrid::~OrderGrid()
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

	try
	{
	//delete m_pThread;
	UGXPThemes::CleanUp();

	DWORD exit_code= NULL;
	if (m_SocketThred != NULL)
	{
    GetExitCodeThread(m_SocketThred->m_hThread, &exit_code);
    if(exit_code == STILL_ACTIVE)
    {
        ::TerminateThread(m_SocketThred->m_hThread, 0);
        CloseHandle(m_SocketThred->m_hThread);
    }
    m_SocketThred->m_hThread = NULL;
    m_SocketThred = NULL;
	}
	}
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"Thread UnInitiliaze");			
	}
}





bool GetRowsOK(_RecordsetPtr pRstTemp,int intNumber, _variant_t& avarData) 
{
   // Store results of GetRows method in array.
   avarData = pRstTemp->GetRows(intNumber);

   // Return False only if fewer than the desired number of rows were returned, 
   // but not because the end of the Recordset was reached.
   long lUbound;
   HRESULT hr = SafeArrayGetUBound(avarData.parray, 2, &lUbound);   
   if (hr == 0) {
      if ((intNumber > lUbound + 1) && (!(pRstTemp->EndOfFile)))
         return false;
      else
         return true;   
	}
   else  
   {
      printf ("\nUnable to Get the Array's Upper Bound\n");
      return false;
	}
}

LRESULT OrderGrid::GridRefresh(WPARAM wParam, LPARAM lParam)
{
	RedrawAll();
	return 0;
}




LRESULT OrderGrid::GridRowCount(WPARAM wParam, LPARAM lParam)
{
	//RedrawAll();
	OrderGrid::Grid_Rows_Count=GetNumberRows();
	return 0;
}

LRESULT OrderGrid::RowDelete(WPARAM wParam, LPARAM lParam)
{
	int row= (int)wParam;
	for(int f=0;f<14;f++)
	{
		QuickSetText(f,row,L"");
	}
	//DeleteRow(row);
	return 0;
}



LRESULT OrderGrid::OnThreadMessage_RowsNo(WPARAM wParam, LPARAM lParam)
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
void OrderGrid::OnSheetSetup(int sheetNumber)
{
	m_nButtonIndex = AddCellType(&m_button);
	int	nRow = 0, nCol = 0;
	
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
	
	// Number
	SetNumberCols(16);
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
	QuickSetText(9,-1,L"Status");
	SetColWidth(9,100);			
	QuickSetText(10,-1,L"Select");
	SetColWidth(10,80);
	QuickSetText(11,-1,L"Type");
	SetColWidth(11,80);
	QuickSetText(12,-1,L"SubType");
	SetColWidth(12,80);
	QuickSetText(13,-1,L"Order#");
	SetColWidth(13,80);
	QuickSetText(14,-1,L"TradeHappenTime");
	SetColWidth(14,110);
	//CUGCell cell ;			 			
	/*GetColDefault( 10, &cell );			
	QuickSetCellType(10,-1,UGCT_CHECKBOX);	
	QuickSetCellTypeEx(10,-1,UGCT_CHECKBOXCHECKMARK);
	SetColDefault( 10, &cell );
	QuickSetLabelText(10,-1,L"Select")*/;




	//CUGCell cell ;			 			
	QuickSetText(15,-1,L"Our Comment");
	SetColWidth(15,100);				
			
	// Header font
	for(int i = 0; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}	

	

	CoInitialize(NULL );
	hrn=connection_update.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=TradeDataBase;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");	
	if(SUCCEEDED(hrn))
	{
		hrn=session_update.Open(connection_update);							
	}
	else
	{
		AfxMessageBox(L"connection.OpenFromInitializationString Failed");
	}

	//AfxBeginThread(RequestHandler, this);		
	//AfxBeginThread(Update_Final_Balance_ingrid, this);			

}

		

void OrderGrid::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	if(col>=11 && col<=15)
	{
		StartEdit();
	}
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
			 

void OrderGrid::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{		
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);

	OrderGrid::col_click=col;
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
	/*CUGCell cell ;			 			
	GetColDefault( 10, &cell );			
	QuickSetCellType(10,-1,UGCT_CHECKBOX);	
	QuickSetCellTypeEx(10,-1,UGCT_CHECKBOXCHECKMARK);
	SetColDefault( 10, &cell );
	QuickSetLabelText(10,-1,L"Select");
*/		 				
	RedrawAll();
}

int OrderGrid::OnCheckbox(long ID,int col,long row,long msg,long param)
{
	if(row==-1)
	{
		int rowscount=GetNumberRows();
		if (col==10)
		{
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
		
	}
	CString strchecked=L"";
	if (param==1)
	{
		QuickSetText(10,row ,L"1"); 
		strchecked=L"1";
	}
	else
	{
		QuickSetText(10,row ,L"0"); 
		strchecked=L"0";
	}

	if (col==10 && row !=-1)
	{		
		CString strord=QuickGetText(3,row);
		
		CString strComment_enter=QuickGetText(11,row);
				  

		_bstr_t b_strord=strord;
		_bstr_t b_strchecked=strchecked;
		_bstr_t b_strComment_enter=strComment_enter;


		
		CString strTYPE=L"";
		CString strsubtype=L"";
		CString strorderno_2=L"";
		CString strtrade_time=L"";

		strComment_enter=QuickGetText(15,row);
		strTYPE=QuickGetText(11,row);
		strsubtype=QuickGetText(12,row);
		strorderno_2=QuickGetText(13,row);
		strtrade_time=QuickGetText(14,row);
		
		
		_bstr_t b_strTYPE=strTYPE;
		_bstr_t b_strsubtype=strsubtype;
		_bstr_t b_strorderno_2=strorderno_2;
		_bstr_t b_strtrade_time=strtrade_time;


		_bstr_t strCommand="";
		//strCommand="Orderno_check_UPDATE '" + b_strord + "','" + b_strComment_enter + "','" + b_strchecked + "'";
		strCommand="Orderno_check_UPDATE '" + b_strord + "','" + b_strComment_enter + "','" + b_strchecked + "' , '" + b_strTYPE + "', '" + b_strsubtype + "', '" + b_strorderno_2 + "', '" + b_strtrade_time + "'";
		char* strCommand_char=(char*)strCommand;
		hrn=cmd.Open(session_update,strCommand_char);							 			 		 				 	
		cmd.Close();
	}

	return TRUE;
}
int OrderGrid::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{

	if(ID == UGCT_DROPLIST)
	{
		return OnDropList(ID, col, row, msg, param);
	}

	if(ID == UGCT_CHECKBOX)
	{
		return OnCheckbox(ID, col, row, msg, param);
	}

	if(ID == m_nButtonIndex)
	{
		return OnPushButton( ID, col, row, msg, param);
	}
}
int OrderGrid::OnDropList(long ID,int col,long row,long msg,long param)
{
	if (msg==103)
	{
		if(OrderGrid::insertFilterFlag==1 && row==0)
		{
			OrderGrid::filter_break=1;
			check_First==0;
			CString  strval=L"";
			CUGCell cell;
			GetCell(col,row,&cell);
			strval=cell.GetText();
			OrderGrid::strFilter="";		
		}
		if (col==11||col==12)
		{
					 
			CString strchecked=L"";
			strchecked=QuickGetText(10,row);
			

			CString strsubtype=L"";
			CString strorderno_2=L"";
			CString strtrade_time=L"";
			CString strord=QuickGetText(3,row);
			CString strTYPE=L"";
			CString strComment_enter=L"";
			if (col!=12)
			{
				strsubtype=QuickGetText(12,row);
			}
			if (col!=11)
			{
				strTYPE=QuickGetText(11,row);
			}
			strorderno_2=QuickGetText(13,row);
			strtrade_time=QuickGetText(14,row);



			_bstr_t b_strord=strord;
			_bstr_t b_strchecked=strchecked;
			

          	

			strComment_enter=QuickGetText(15,row);


		
			
			CUGCell cell;
			GetCell(col,row,&cell);
			if (col==11)
			{
				strTYPE=cell.GetText();
			}
			if (col==12)
			{
				strsubtype=cell.GetText();
			}


			_bstr_t b_strComment_enter=strComment_enter;
			_bstr_t b_strTYPE=strTYPE;
			_bstr_t b_strsubtype=strsubtype;
			_bstr_t b_strorderno_2=strorderno_2;
			_bstr_t b_strtrade_time=strtrade_time;


			_bstr_t strCommand="";
			//strCommand="Orderno_check_UPDATE '" + b_strord + "','" + b_strComment_enter + "','" + b_strchecked + "'";
			strCommand="Orderno_check_UPDATE '" + b_strord + "','" + b_strComment_enter + "','" + b_strchecked + "' , '" + b_strTYPE + "', '" + b_strsubtype + "', '" + b_strorderno_2 + "', '" + b_strtrade_time + "'";
			char* strCommand_char=(char*)strCommand;
			hrn=cmd.Open(session_update,strCommand_char);							 			 		 				 	
			cmd.Close();
		}




		if(OrderGrid::insertFilterFlag==1 && row==0 )
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
int OrderGrid::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	if(OrderGrid::insertFilterFlag==1 && row==0)
	{
		check_First==0;
		CString  strval=L"";	
		strval=string;
		OrderGrid::strFilter="";							  		
	}
	if (col==15 || col==11 || col==12 || col==13 || col==14)
		{

			CString strord=QuickGetText(3,row);
		
			

			CString strchecked=QuickGetText(10,row);


			CString strComment_enter=L"";
			CString strTYPE=L"";
			CString strsubtype=L"";
			CString strorderno_2=L"";
			CString strtrade_time=L"";

			if (col==15)
			{
				strComment_enter=string;
				strTYPE=QuickGetText(11,row);
				strsubtype=QuickGetText(12,row);
				strorderno_2=QuickGetText(13,row);
				strtrade_time=QuickGetText(14,row);
			}
			else if(col==11)
			{
				strComment_enter=QuickGetText(15,row);
				strTYPE=string;
				strsubtype=QuickGetText(12,row);
				strorderno_2=QuickGetText(13,row);
				strtrade_time=QuickGetText(14,row);
			}
			else if(col==12)
			{
				strComment_enter=QuickGetText(15,row);
				strTYPE=QuickGetText(11,row);
				strsubtype=string;
				strorderno_2=QuickGetText(13,row);
				strtrade_time=QuickGetText(14,row);
			}
			else if(col==13)
			{
				strComment_enter=QuickGetText(15,row);
				strTYPE=QuickGetText(11,row);
				strsubtype=QuickGetText(12,row);
				strorderno_2=string;
				strtrade_time=QuickGetText(14,row);
			}
			else if(col==14)
			{
				strComment_enter=QuickGetText(15,row);
				strTYPE=QuickGetText(11,row);
				strsubtype=QuickGetText(12,row);
				strorderno_2=QuickGetText(13,row);
				strtrade_time=string;
				if (strtrade_time.Trim().GetLength()>0)
				{

				}
			}



		






			_bstr_t b_strord=strord;
			_bstr_t b_strchecked=strchecked;
			
			_bstr_t b_strComment_enter=strComment_enter;

			_bstr_t b_strTYPE=strTYPE;
			_bstr_t b_strsubtype=strsubtype;
			_bstr_t b_strorderno_2=strorderno_2;
			_bstr_t b_strtrade_time=strtrade_time;


		
			_bstr_t strCommand="";
			strCommand="Orderno_check_UPDATE '" + b_strord + "','" + b_strComment_enter + "','" + b_strchecked + "' , '" + b_strTYPE + "', '" + b_strsubtype + "', '" + b_strorderno_2 + "', '" + b_strtrade_time + "'";
			char* strCommand_char=(char*)strCommand;
			hrn=cmd.Open(session_update,strCommand_char);							 			 		 				 	
			cmd.Close();
		}




		if(OrderGrid::insertFilterFlag==1 && row==0 )
		{
			
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
void OrderGrid::OnMenuCommand(int col,long row,int section,int item)
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
int OrderGrid::OnPushButton(long ID,int col,long row,long msg,long param)
{
	/*int rowscount=GetNumberRows();
	if (col==10)
	{
		for (int forcount=0;forcount<rowscount-1;forcount++)
		{
			QuickSetText(10,forcount,L"1"); 
		}
	}
	*/
	
	return TRUE;
}
int OrderGrid::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
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
void OrderGrid::OnTabSelected(int ID)
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

void OrderGrid::OnSize(UINT nType, int cx, int cy)
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



 void OrderGrid::OnGetCell(int col,long row,CUGCell *cell)
{
	OrderGrid::m_order_mutex.Lock(); 
	//m_logfile_g.LogEvent(L"Start OnGetCell");
		st_Order_Update mst_grid={};
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
			if (OrderGrid::insertFilterFlag==1)
			{
				rows_no=row-1;				
				if (row==0)
				{
					OrderGrid::m_order_mutex.Unlock();
					return;
				}
			}
			if (col==0)
			{				
				mst_grid=m_st_Order_GridArray[rows_no];				
				CString tmp=mst_grid.login  ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			if (col==1)
			{				
				mst_grid=m_st_Order_GridArray[rows_no];				
				CString tmp=mst_grid.time  ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==2)
			{
				
				mst_grid=m_st_Order_GridArray[rows_no];
				CString tmp=L""   ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==3)
			{				
				mst_grid=m_st_Order_GridArray[rows_no];				
				CString tmp=mst_grid.order    ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==4)
			{				
				mst_grid=m_st_Order_GridArray[rows_no];				
				CString tmp=mst_grid.symbol ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==5)
			{				
				mst_grid=m_st_Order_GridArray[rows_no];			
				CString tmp=mst_grid.action  ;	 			
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==6)
			{				
				mst_grid=m_st_Order_GridArray[rows_no];				
				CString tmp=mst_grid.volume   ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==7)
			{	
				mst_grid=m_st_Order_GridArray[rows_no];
				CString tmp=mst_grid.price;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==8)
			{				
				mst_grid=m_st_Order_GridArray[rows_no];
				CString tmp=mst_grid.comment ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==9)
			{	
				
				mst_grid=m_st_Order_GridArray[rows_no];
				CString tmp=mst_grid.OurComment  ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			
			else if (col==10)
			{	
				CUGCell MYcell;			 			
				GetColDefault( 10, &MYcell);			
				QuickSetCellType(10,rows_no,UGCT_CHECKBOX);	
				QuickSetCellTypeEx(10,rows_no,UGCT_CHECKBOXCHECKMARK);
				SetColDefault( 10, &MYcell);
				


				mst_grid=m_st_Order_GridArray[rows_no];
				CString tmp=mst_grid.Change_YN  ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==11)
			{	
				CUGCell MYcell;			 			
				GetColDefault( 11, &MYcell);			
				QuickSetCellType(11,rows_no,UGCT_DROPLIST);
				QuickSetCellTypeEx(11,rows_no,UGCT_DROPLISTHIDEBUTTON);
				QuickSetLabelText(11,rows_no,L"Type1\nType2\n");
				SetColDefault( 11, &MYcell);

				mst_grid=m_st_Order_GridArray[rows_no];
				CString tmp=mst_grid.TYPE  ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==12)
			{	
				
				CUGCell MYcell;			 			
				GetColDefault( 12, &MYcell);			
				QuickSetCellType(12,rows_no,UGCT_DROPLIST);
				QuickSetCellTypeEx(12,rows_no,UGCT_DROPLISTHIDEBUTTON);
				
				
				CUGCell getMyCell;			 			
				GetCell(11,row,&getMyCell);
				CString Cell11_text=getMyCell.GetText();



				Cell11_text=Cell11_text.MakeUpper();
				if (wcscmp(Cell11_text,L"TYPE1")==0)
				{
					QuickSetLabelText(12,rows_no,L"PBDU\nBPDS\nOL\n");
					SetColDefault( 12, &MYcell);
				}
				if (wcscmp(Cell11_text,L"TYPE2")==0)
				{
					QuickSetLabelText(12,rows_no,L"TDH\nSAT\n\OL\n");
					SetColDefault( 12, &MYcell);
				}

				mst_grid=m_st_Order_GridArray[rows_no];
				CString tmp=mst_grid.subtype;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==13)
			{	
				
				mst_grid=m_st_Order_GridArray[rows_no];
				CString tmp=mst_grid.orderno_2  ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==14)
			{	
				
				mst_grid=m_st_Order_GridArray[rows_no];
				CString tmp=mst_grid.trade_time  ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==15)
			{	
				
				mst_grid=m_st_Order_GridArray[rows_no];
				CString tmp=mst_grid.deal;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}			
		}
	OrderGrid::m_order_mutex.Unlock();
}



void OrderGrid::OnTimer(UINT nIDEvent)
{	
	// OrderGrid::m_st_Order_GridArray
	OrderGrid::m_order_mutex.Lock(); 
	int r_count=OrderGrid::m_st_Order_GridArray.Total();
	OrderGrid::m_order_mutex.Unlock();		
	int grid_total=GetNumberRows();
	
	if (OrderGrid::insertFilterFlag==1)
	{
			r_count=r_count+1;
	}		
	if (grid_total!=r_count)
	{			
		if (r_count>0)
		{
			SetNumberRows(r_count);					
		}
	}
	else
	{			
			RedrawAll();			
	}					
}



void OrderGrid::GetOrders()
 {
	//lock_data=true;	
	run_check=1;	

	
	//CreateThread();
	 /*OrderGrid *OG;
	 OG=new OrderGrid ();*/
	 HRESULT hr = S_OK;	
	run_check=0;  

 }
 void OrderGrid::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();	
	EnableMenu(TRUE);		
	AddMenuItem( 2001, _T( "Filter" ) );
	AddMenuItem( 2000, _T( "Find Dialog" ) );		
}

 int OrderGrid::OnMenuStart( int iCol, long lRow, int iSection )
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

 void OrderGrid::filter()
 {
	if (OrderGrid::insertFilterFlag==0)
	{
			addItemToCombobox();
			OrderGrid::insertFilterFlag=1;
			InsertRow(0);
			for (int col_count=0;col_count<16;col_count++)
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
		OrderGrid::insertFilterFlag=0;		
	}
	RedrawAll();
 }



BOOLEAN  OrderGrid::CheckvalueInArray(const CStringArray& arr,CString strval) 
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
 
void OrderGrid::addItemToCombobox()
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
	try
	{
	int rows=1;	
	CString str_val=L"";	
	for (int forcount=0;forcount<16;forcount++)
	{
		str[forcount]=L"ALL\n";		
	}
	OrderGrid::m_order_mutex.Lock();
	st_Order_UpdateArray m_array_filter;
	m_array_filter.Assign(OrderGrid::m_st_Order_UpdateArray);
	OrderGrid::m_order_mutex.Unlock();
	rows=m_array_filter.Total();
	for (int forcount=0;forcount<rows;forcount++)
	{
		st_Order_Update m_st_for_filter={};
		m_st_for_filter=m_array_filter[forcount];

		for (int clocount=0;clocount<16;clocount++)
		{									
				if (clocount==0)
				{
					str_val=m_st_for_filter.login ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr.Add(str_val);
					}
				}


				if (clocount==1)
				{
					str_val=m_st_for_filter.time ;
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
					
				}



				if (clocount==3)
				{
					str_val=m_st_for_filter.order ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr3,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr3.Add(str_val);
					}
				}

				if (clocount==4)
				{
					str_val=m_st_for_filter.symbol ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr4,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr4.Add(str_val);
					}
				}
				if (clocount==5)
				{
					str_val=m_st_for_filter.TYPE ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr5,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr5.Add(str_val);
					}
				}
				if (clocount==6)
				{
					str_val=m_st_for_filter.volume ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr6,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr6.Add(str_val);
					}
				}
				if (clocount==7)
				{
					str_val=m_st_for_filter.price ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr7,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr7.Add(str_val);
					}
				}
				if (clocount==8)
				{
					str_val=m_st_for_filter.comment ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr8,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr8.Add(str_val);
					}
				}
				if (clocount==9)
				{
					str_val=m_st_for_filter.OurComment ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr9,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr9.Add(str_val);
					}
				}
				if (clocount==10)
				{
					str_val=m_st_for_filter.Change_YN;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr10,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr10.Add(str_val);
					}
				}
				if (clocount==11)
				{
					str_val=m_st_for_filter.TYPE;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr11,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr11.Add(str_val);
					}
				}
				if (clocount==12)
				{
					str_val=m_st_for_filter.subtype;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr12,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr12.Add(str_val);
					}
				}
				if (clocount==13)
				{
					str_val=m_st_for_filter.orderno_2;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr13,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr13.Add(str_val);
					}
				}
				if (clocount==14)
				{
					str_val=m_st_for_filter.trade_time;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr14,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr14.Add(str_val);
					}
				}
				if (clocount==15)
				{
					str_val=m_st_for_filter.deal ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr15,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr15.Add(str_val);
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

UINT check_comment_YN(CString login);
UINT check_comment_YN(CString login)
{
	int total_count=NetPosGrid::m_Client_Details_Array.Total();
	for (int f=0;f<total_count;f++)
	{
		NetPosGrid::m_Client_Details=NetPosGrid::m_Client_Details_Array[f];
		CString str_login=NetPosGrid::m_Client_Details.V_login;
		CString CommentYN=NetPosGrid::m_Client_Details.Comment_YN;
		CommentYN=CommentYN.Trim().MakeUpper();
		if (wcscmp(CommentYN,L"Y")==0)
		{
			return 1;
		}
	}	
	return 0;
}

void get_login_balance_details(CString login);
void get_login_balance_details(CString login)
{
	int total_data=NetPosGrid::m_Client_Balance_Array.Total();
	int check_exist=0;
	int row_pos=-1;
	double bal=0;
	for (int i=0;i<total_data;i++)
	{
		NetPosGrid::Client_Balance m_Client_Balance={};
		m_Client_Balance=NetPosGrid::m_Client_Balance_Array[i];
		if(wcscmp(m_Client_Balance.V_login,login)==0)
		{
			row_pos=i;
			check_exist=1;
			bal=m_Client_Balance.Total_Balance;
			break;
		}
	}	
	NetPosGrid::new_client=check_exist;
	NetPosGrid::row_position=row_pos;
	NetPosGrid::Pre_balance=bal;
}


UINT RequestHandler(LPVOID pParam)
{			
	OrderGrid* pThis= (OrderGrid*)pParam;	
	try
	{			
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<Client_Table> > client;	
	HRESULT hr;
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	if(SUCCEEDED(hr))
	{
		hr=session.Open(connection);							
	}
	else
	{
		AfxMessageBox(L"connection.OpenFromInitializationString Failed");
	}
	_bstr_t strCommand="";		  
	strCommand ="SELECT  V_login, V_Name, Comment_YN, Ignore_YN, client_group, Client_Group1, Client_Group2, Client_Group4, Client_Credit from client";
	char* strCommand_char=(char*)strCommand;
	if(SUCCEEDED(hr))
	{
	hr=client.Open(session,strCommand_char);	
	}
	if(SUCCEEDED(hr))
	{
		int counter_count=0;
		while (client.MoveNext() == S_OK)
		{	
			CMTStr::Copy(NetPosGrid::m_Client_Details.V_login, client.V_login) ;
			CMTStr::Copy(NetPosGrid::m_Client_Details.V_Name, client.V_Name) ;
			CMTStr::Copy(NetPosGrid::m_Client_Details.Comment_YN,client.Comment_YN) ;
			CMTStr::Copy(NetPosGrid::m_Client_Details.Ignore_YN, client.Ignore_YN) ;
			CMTStr::Copy(NetPosGrid::m_Client_Details.client_group,client.client_group) ; 
			CMTStr::Copy(NetPosGrid::m_Client_Details.Client_Group1, client.Client_Group1);
			CMTStr::Copy(NetPosGrid::m_Client_Details.Client_Group2, client.Client_Group2);
			CMTStr::Copy(NetPosGrid::m_Client_Details.Client_Group4, client.Client_Group4);
			NetPosGrid::m_Client_Details.Client_Credit=client.Client_Credit;
			NetPosGrid::m_Client_Details_Array.Add(&NetPosGrid::m_Client_Details);			
		}		
	}
	else
	{
		AfxMessageBox(L"client.Open(session,strCommand_char) Failed");
	}
		//End of Getting Client Information Details
	client.Close();
	session.Close();
	OrderGrid::first_time_data_Received_YN=0;
	//CSocket m_Client;		
	if( AfxSocketInit() == FALSE)
	{ 
		AfxMessageBox(L"Failed to Initialize Sockets"); 
		return 0; 
	}
	if(OrderGrid::m_Client.Create()==FALSE)
	{
		AfxMessageBox(L"Failed to Create Socket");
		return 0;
	}
	
	if(OrderGrid::m_Client.Connect(L"68.168.104.26",5042)==FALSE)
	//if(OrderGrid::m_Client.Connect(L"192.168.43.203",5042)==FALSE)
	{

		AfxMessageBox(L"Failed to Connect");
		return 0;
	}	
	_bstr_t bstr="";
	USES_CONVERSION ;	
	rapidjson::Document d;	

	//while(true)
	//{
	//	//Sleep(50);
	//	_bstr_t b_car_val;
	//	char	cbuf[1000001];	
	//	for(int i=0;i<1000001;i++)
	//	cbuf[i] = '\0';		
	//	if(OrderGrid::m_Client.Receive(cbuf,1000000)>0)
	//	{				
	//		bstr=bstr+cbuf;
	//		CString cstr=bstr;
	//		int Charindex=cstr.Find('|');
	//		while  (Charindex>=0)
	//		{
	//			CString final_str=cstr.Mid(0,Charindex);
	//			cstr=cstr.Mid(Charindex+1,cstr.GetLength()-Charindex-1);
	//							
	//			bstr=cstr;
	//			Charindex=cstr.Find('|');
	//			char * strforjson;
	//			_bstr_t char_bstr;
	//			char_bstr=final_str;
	//			strforjson=(char*)char_bstr;
	//			if(!d.Parse<0>(strforjson).HasParseError())
	//			{
	//				const Value& Key=d["Key"];
	//				_bstr_t bstr_key=Key.GetString();
	//				CString str_key=bstr_key;
	//				const Value& rows = d["Rows"]; // Using a reference for consecutive access is handy and faster.
	//				assert(rows.IsArray());
	//				if (wcscmp(str_key,L"Netposition_FirstTime")==0)
	//				{
	//					NetPosGrid::mutex_Symbol_ltp.Lock();
	//					//m_logfile_g.LogEvent(L"Start Netposition_FirstTime");
	//					NetPosGrid::m_NetpositionArray.Clear();
	//					NetPosGrid::first_time_update=0;
	//				for (string::size_type  i = 0; i < rows.Size(); i++)
	//				{						
	//						//m_logfile_g.LogEvent(L"Start RequestHandler 1");
	//						_bstr_t  m_login=rows[i]["login"].GetString() ;
	//						CString m_str_login=m_login;
	//						
	//						CMTStr::Copy(OrderGrid::m_St_Client_4.Login,m_str_login); 

	//						if (Check_value_In_list(m_str_login)==false )
	//						{
	//							OrderGrid::mutex_client_list.Lock();
	//							OrderGrid::m_client_list.Add(&OrderGrid::m_St_Client_4);
	//							OrderGrid::mutex_client_list.Unlock();
	//						}
	//						_bstr_t  m_symbol=rows[i]["Symbol"].GetString() ;
	//						CString m_str_symbol=m_symbol;
	//						_bstr_t  m_netqty=rows[i]["netqty"].GetString() ;
	//						CString m_str_netqty=m_netqty;
	//						_bstr_t  m_avg_rate=rows[i]["avg_rate"].GetString() ;
	//						CString m_str_avg_rate=m_avg_rate;
	//						_bstr_t  m_last_update=rows[i]["last_update"].GetString() ;
	//						CString m_str_last_update=m_last_update;
	//						_bstr_t  m_pl_volume=rows[i]["pl_volume"].GetString() ;
	//						CString m_str_pl_volume=m_pl_volume;
	//						_bstr_t  m_Name=rows[i]["Name"].GetString() ;
	//						CString m_str_Name=m_Name;
	//						_bstr_t  m_Group1=rows[i]["Group1"].GetString() ;
	//						CString m_str_Group1=m_Group1;
	//						_bstr_t  m_Group2=rows[i]["Group2"].GetString() ;
	//						CString m_str_Group2=m_Group2;
	//						_bstr_t  m_Group3=rows[i]["Group3"].GetString() ;
	//						CString m_str_Group3=m_Group3;
	//						_bstr_t  m_Checked_Status=rows[i]["Checked_Status"].GetString() ;
	//						CString m_str_Checked_Status=m_Checked_Status;
	//						_bstr_t  m_Checked_Time=rows[i]["Checked_Time"].GetString() ;
	//						CString m_str_Checked_Time=m_Checked_Time;
	//						_bstr_t  m_Alloted_Limit=rows[i]["Alloted_Limit"].GetString() ;
	//						CString m_str_Alloted_Limit=m_Alloted_Limit;
	//						_bstr_t  m_Remark2=rows[i]["Remark2"].GetString() ;
	//						CString m_str_Remark2=m_Remark2;
	//						_bstr_t  m_Standing_Avg_rate=rows[i]["Standing_Avg_rate"].GetString() ;
	//						CString m_str_Standing_Avg_rate=m_Standing_Avg_rate;
	//						_bstr_t  m_Sq_Balance=rows[i]["Sq_Balance"].GetString();
	//						CString m_str_Sq_Balance=m_Sq_Balance;

	//						_bstr_t  m_Last_Rate=rows[i]["Last_Rate"].GetString();
	//						CString m_str_Last_Rate=m_Last_Rate;
	//						
	//						_bstr_t  m_Floating_Profit=rows[i]["Floating_Profit"].GetString();
	//						CString m_str_Floating_Profit=m_Floating_Profit;

	//						_bstr_t  m_Balance=rows[i]["Balance"].GetString();
	//						CString m_str_Balance=m_Balance;
	//						
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_login,m_str_login);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_symbol,m_str_symbol);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_pre_qty,m_str_netqty);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_netqty,m_str_netqty);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_avg_rate,m_str_avg_rate);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_last_update,m_str_last_update);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_pl_volume,m_str_pl_volume);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Name,m_str_Name);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Group1,m_str_Group1);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Group2,m_str_Group2);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Group3,m_str_Group3);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Checked_Status,m_str_Checked_Status);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Checked_Time,m_str_Checked_Time);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Alloted_Limit,m_str_Alloted_Limit);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Remark2,m_str_Remark2);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Standing_Avg_rate,m_str_Standing_Avg_rate);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Sq_Balance,m_str_Sq_Balance);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_last_rate ,m_str_Last_Rate);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Floating_Profit ,m_str_Floating_Profit);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Balance ,m_str_Balance);
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_new_qty,L"0");								
	//						CMTStr::Copy(NetPosGrid::m_st_Netposition.m_incre_qty,L"0");														
	//						NetPosGrid::m_NetpositionArray.Add(&NetPosGrid::m_st_Netposition);														
	//					}
	//					
	//					//pThis->SendMessage(DISPLAYDATA_NETPOSITON_FIRSTTIME, 1,1);	
	//					
	//					int rows_count=NetPosGrid::m_SymbolMultiplyer.Total();
	//					for(int f=0;f<rows_count;f++)
	//					{
	//						NetPosGrid::m_st_multiplyer=NetPosGrid::m_SymbolMultiplyer[f];								
	//						OrderGrid::str_symbol_for_rate=NetPosGrid::m_st_multiplyer.m_symbol;
	//						MTTickShort  tick;
	//						DlgHelp::m_dealer->m_manager->TickLast(OrderGrid::str_symbol_for_rate,tick);		
	//						OrderGrid::dbl_rate= tick.ask;	
	//						
	//						int rows_count=NetPosGrid::m_NetpositionArray.Total();

	//						for (int f=0;f<rows_count;f++)
	//						{
	//							NetPosGrid::m_st_Netposition_Ratecal=NetPosGrid::m_NetpositionArray[f];
	//							CString Str_get_symbol=NetPosGrid::m_st_Netposition_Ratecal.m_symbol;

	//							if (wcscmp(Str_get_symbol,OrderGrid::str_symbol_for_rate)==0)
	//							{
	//								LPTSTR endPtr1;								
	//								double netqty=_tcstod(NetPosGrid::m_st_Netposition_Ratecal.m_netqty, &endPtr1);
	//								endPtr1=L"";
	//								double plvolume=_tcstod(NetPosGrid::m_st_Netposition_Ratecal.m_pl_volume, &endPtr1);
	//								plvolume=plvolume;
	//								double value_with_last_rate=((OrderGrid::dbl_rate*-netqty));
	//								double pl=0;				 
	//								pl=(plvolume+value_with_last_rate)*COutputWnd::m_wndOutputPos.get_Multi(Str_get_symbol);
	//								pl=-pl;	

	//								CString str_rate=L"";
	//								str_rate.Format(L"%.2lf",OrderGrid::dbl_rate);					
	//								CMTStr::Copy(NetPosGrid::m_st_Netposition_Ratecal.m_last_rate,str_rate);

	//								CString str_pl=L"";
	//								str_pl.Format(L"%.2lf",pl);					
	//								CMTStr::Copy(NetPosGrid::m_st_Netposition_Ratecal.m_Floating_Profit,str_pl);
	//								NetPosGrid::m_NetpositionArray.Update(f,&NetPosGrid::m_st_Netposition_Ratecal);
	//							}
	//						}


	//					}
	//					//Calculating Total Balance	
	//					m_logfile_g.LogEvent(L"Start Netposition_FirstTime");
	//						int grid_row_count=NetPosGrid::m_NetpositionArray.Total();																														
	//					
	//						int f=0;
	//						if (NetPosGrid::insertFilterFlag==1)
	//						{
	//							f=1;
	//						}
	//																				
	//									
	//						for(f=0;f<grid_row_count;f++)
	//						{	
	//							double d_total_bal=0;	
	//							NetPosGrid::m_st_Netposition_Ratecal=NetPosGrid::m_NetpositionArray[f];
	//							CString Str_client_from_grid=L"";					
	//							Str_client_from_grid=NetPosGrid::m_st_Netposition_Ratecal.m_login ;													
	//							CString txt_pl=L"";
	//							txt_pl=NetPosGrid::m_st_Netposition_Ratecal.m_Floating_Profit ;						
	//							LPTSTR endPtr;
	//							double d_pl= _tcstod(txt_pl, &endPtr);	
	//							
	//							get_login_balance_details(Str_client_from_grid);
	//							d_total_bal=NetPosGrid::Pre_balance+d_pl;	
	//							NetPosGrid::Client_Balance m_Client_Balance={};
	//							m_Client_Balance.Total_Balance=d_total_bal;
	//							CMTStr::Copy(m_Client_Balance.V_login,Str_client_from_grid);
	//							if (NetPosGrid::row_position>=0)
	//							{
	//								NetPosGrid::m_Client_Balance_Array.Update(NetPosGrid::row_position,&m_Client_Balance);
	//							}
	//							else
	//							{
	//								NetPosGrid::m_Client_Balance_Array.Add(&m_Client_Balance);
	//							}
	//						}
	//							

	//						for(f=0;f<grid_row_count;f++)
	//						{					
	//							NetPosGrid::m_st_Netposition_Ratecal=NetPosGrid::m_NetpositionArray[f];
	//							CString Str_client_from_grid=L"";					
	//							Str_client_from_grid=NetPosGrid::m_st_Netposition_Ratecal.m_login ;
	//							
	//							get_login_balance_details(Str_client_from_grid);										
	//							CString str_pl=L"";
	//							str_pl.Format(L"%.0lf",NetPosGrid::Pre_balance);	
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition_Ratecal.m_Balance,str_pl);
	//							NetPosGrid::m_NetpositionArray.Update(f,&NetPosGrid::m_st_Netposition_Ratecal);														
	//						}							 			
	//																	
	//					//End of Updating New Data in structure
	//					NetPosGrid::first_time_update=1;

	//					if(OrderGrid::first_time_data_Received_YN==1)
	//					{
	//						COutputWnd::m_wndOutputPos.UpdatePre_Post_Position();
	//					}

	//					m_logfile_g.LogEvent(L"End Netposition_FirstTime");
	//					NetPosGrid::mutex_Symbol_ltp.Unlock();
	//				}
	//					if (wcscmp(str_key,L"TickData")==0)
	//					{
	//						int check=0;							
	//						for (string::size_type  i = 0; i < rows.Size(); i++)
	//						{
	//							 int check_new_row=0;								
	//							_bstr_t  m_symbol=rows[i]["Symbol"].GetString() ;
	//							CString m_str_symbol=m_symbol;								
	//							_bstr_t  m_Last_Rate=rows[i]["Last_Rate"].GetString();
	//							CString m_str_Last_Rate=m_Last_Rate;								
	//							LPTSTR endPtr;
	//							OrderGrid::dbl_rate= _tcstod(m_Last_Rate, &endPtr);		
	//							OrderGrid::str_symbol_for_rate=m_str_symbol;																
	//							try
	//							{			
	//								pThis->SendMessage(NETPOS_GRID_ROWS_COUNT, 1,1);//For Getting Rows Value and putting the rows value of netpos grid in (NetPosGrid::netpos_grid_total) variable		
	//								int f=0;
	//								if (NetPosGrid::insertFilterFlag==1)
	//								{
	//									f=1;
	//								}
	//								for(f;f<NetPosGrid::netpos_grid_total;f++)
	//								{						
	//									//For Getting cellvalue
	//									pThis->SendMessage(msg_getcellSymbol,2,f);
	//									pThis->SendMessage(msg_getcellNetqty,5,f);
	//									pThis->SendMessage(msg_getcellpl_volume,20,f);											
	//									pThis->SendMessage(msg_getcell_netqty,5,f);
	//									pThis->SendMessage(msg_getcell_pl,8,f);														
	//									CString strrate=L"";		
	//									CString strsymbol=NetPosGrid::cellSymbol.GetText();
	//									if (strsymbol.Trim().GetLength()>0)
	//									{
	//										strrate.Format(L"%.4lf",OrderGrid::dbl_rate);
	//										if (wcscmp(OrderGrid::str_symbol_for_rate,strsymbol)==0)
	//										{
	//											NetPosGrid::text_for_update=strrate;
	//											pThis->SendMessage(msg_SetTextValue,7,f);					
	//											double netqty=NetPosGrid::cellNetqty.GetNumber();
	//											double plvolume=NetPosGrid::cellpl_volume.GetNumber();
	//											plvolume=plvolume;
	//											double value_with_last_rate=((OrderGrid::dbl_rate*-netqty));
	//											double pl=0;				 
	//											pl=(plvolume+value_with_last_rate)*COutputWnd::m_wndOutputPos.get_Multi(OrderGrid::str_symbol_for_rate);
	//											pl=-pl;																	
	//											CString str_pl=L"";
	//											str_pl.Format(L"%.2lf",pl);
	//											NetPosGrid::text_for_update=str_pl;
	//											pThis->SendMessage(msg_SetTextValue,8,f);																		
	//										}
	//											
	//									}
	//							}
	//
	//							CString tempval=L"";
	//							double return_val=0;
	//							pThis->SendMessage(msg_sub_grid_rows_count,0,0);						
	//							int total_rows=NetPosGrid::sub_rows_count;
	//							for (int i=0;i<total_rows;i++)
	//							{		
	//								pThis->SendMessage(msg_GetTextValue,2,i);														
	//								CString txtTotal=NetPosGrid::get_Text_fromGrid;
	//								if (txtTotal!=L"Total")
	//								{
	//									pThis->SendMessage(msg_gettemp_cell,8,i);			
	//									double temp_double=NetPosGrid::temp_Cell.GetNumber();
	//									return_val=return_val+temp_double;
	//								}
	//							}
	//							tempval.Format(L"%.2f",return_val);

	//							NetPosGrid::m_taxt_total.SetWindowTextW(tempval);

	//							pThis->SendMessage(NETPOS_GRID_ROWS_COUNT, 1,1);//For Getting Rows Value and putting the rows value of netpos grid in (NetPosGrid::netpos_grid_total) variable
	//							int grd_row=NetPosGrid::netpos_grid_total-1;
	//								
	//												

	//							pThis->SendMessage(msg_GetTextValue,2,grd_row);
	//							CString strGridval=NetPosGrid::get_Text_fromGrid;
	//							if (strGridval==L"Total")
	//							{
	//									
	//								NetPosGrid::text_for_update=tempval;
	//								pThis->SendMessage(msg_SetTextValue,8,grd_row);
	//							}

	//							pThis->SendMessage(msg_redraw_ALL,0,0);
	//							}
	//							catch(_com_error & ce)
	//							{
	//								AfxMessageBox(ce.Description()+L"  update_rate_and_pl");	
	//							}

	//						}
	//					}
	//					if (wcscmp(str_key,L"Netposition_NewData")==0)
	//					{								
	//						NetPosGrid::mutex_Symbol_ltp.Lock();
	//						//m_logfile_g.LogEvent(L"Start Netposition_NewData");
	//						for (string::size_type  i = 0; i < rows.Size(); i++)
	//						{
	//							int check_new_row=0;
	//							_bstr_t  m_login=rows[i]["login"].GetString() ;
	//							CString m_str_login=m_login;
	//							CMTStr::Copy(OrderGrid::m_St_Client_5.Login,m_str_login);
	//							if (Check_value_In_list(m_str_login)==false )
	//							{
	//								OrderGrid::mutex_client_list.Lock();
	//								OrderGrid::m_client_list.Add(&OrderGrid::m_St_Client_5);
	//								OrderGrid::mutex_client_list.Unlock();
	//							}
	//							_bstr_t  m_symbol=rows[i]["Symbol"].GetString() ;
	//							CString m_str_symbol=m_symbol;
	//							_bstr_t  m_netqty=rows[i]["netqty"].GetString() ;
	//							CString m_str_netqty=m_netqty;
	//							_bstr_t  m_avg_rate=rows[i]["avg_rate"].GetString() ;
	//							CString m_str_avg_rate=m_avg_rate;
	//							_bstr_t  m_last_update=rows[i]["last_update"].GetString() ;
	//							CString m_str_last_update=m_last_update;
	//							_bstr_t  m_pl_volume=rows[i]["pl_volume"].GetString() ;
	//							CString m_str_pl_volume=m_pl_volume;
	//							_bstr_t  m_Name=rows[i]["Name"].GetString() ;
	//							CString m_str_Name=m_Name;
	//							_bstr_t  m_Group1=rows[i]["Group1"].GetString() ;
	//							CString m_str_Group1=m_Group1;
	//							_bstr_t  m_Group2=rows[i]["Group2"].GetString() ;
	//							CString m_str_Group2=m_Group2;
	//							_bstr_t  m_Group3=rows[i]["Group3"].GetString() ;
	//							CString m_str_Group3=m_Group3;
	//							_bstr_t  m_Checked_Status=rows[i]["Checked_Status"].GetString() ;
	//							CString m_str_Checked_Status=m_Checked_Status;
	//							_bstr_t  m_Checked_Time=rows[i]["Checked_Time"].GetString() ;
	//							CString m_str_Checked_Time=m_Checked_Time;
	//							_bstr_t  m_Alloted_Limit=rows[i]["Alloted_Limit"].GetString() ;
	//							CString m_str_Alloted_Limit=m_Alloted_Limit;
	//							_bstr_t  m_Remark2=rows[i]["Remark2"].GetString() ;
	//							CString m_str_Remark2=m_Remark2;
	//							_bstr_t  m_Standing_Avg_rate=rows[i]["Standing_Avg_rate"].GetString() ;
	//							CString m_str_Standing_Avg_rate=m_Standing_Avg_rate;
	//							_bstr_t  m_Sq_Balance=rows[i]["Sq_Balance"].GetString();
	//							CString m_str_Sq_Balance=m_Sq_Balance;
	//							_bstr_t  m_new_qty=rows[i]["new_qty"].GetString();
	//							CString  m_str_new_qty=m_new_qty;

	//							_bstr_t  m_Last_Rate=rows[i]["Last_Rate"].GetString();
	//							CString m_str_Last_Rate=m_Last_Rate;
	//						
	//							_bstr_t  m_Floating_Profit=rows[i]["Floating_Profit"].GetString();
	//							CString m_str_Floating_Profit=m_Floating_Profit;

	//							_bstr_t  m_Balance=rows[i]["Balance"].GetString();
	//							CString m_str_Balance=m_Balance;
	//							
	//							
	//							int total_rows_count=NetPosGrid::m_NetpositionArray.Total();
	//							int rows_position=0;
	//							for (int f=0;f<total_rows_count;f++)
	//							{
	//								NetPosGrid::m_st_Netposition=NetPosGrid::m_NetpositionArray[f];
	//								if (wcscmp(NetPosGrid::m_st_Netposition.m_login,m_str_login)==0 && wcscmp(NetPosGrid::m_st_Netposition.m_symbol,m_str_symbol)==0)
	//								{
	//									check_new_row=1;
	//									rows_position=f;
	//									break;
	//								}
	//							}

	//							
	//														
	//							LPTSTR endPtr;
	//							double o_netqty= _tcstod(NetPosGrid::m_st_Netposition.m_netqty, &endPtr);
	//							double n_newqty=_tcstod(m_str_netqty, &endPtr);

	//							double o_avgrate= _tcstod(NetPosGrid::m_st_Netposition.m_avg_rate, &endPtr);
	//							double n_avgrate=_tcstod(m_str_avg_rate, &endPtr);
	//							//For Ignore Duplicate data
	//							if (o_netqty!=n_newqty || o_avgrate!=n_avgrate)
	//							{
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_login,m_str_login);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_symbol,m_str_symbol);
	//							
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_netqty,m_str_netqty);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_avg_rate,m_str_avg_rate);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_last_update,m_str_last_update);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_pl_volume,m_str_pl_volume);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Name,m_str_Name);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Group1,m_str_Group1);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Group2,m_str_Group2);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Group3,m_str_Group3);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Checked_Status,m_str_Checked_Status);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Checked_Time,m_str_Checked_Time);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Alloted_Limit,m_str_Alloted_Limit);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Remark2,m_str_Remark2);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Standing_Avg_rate,m_str_Standing_Avg_rate);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Sq_Balance,m_str_Sq_Balance);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_new_qty,m_str_new_qty);
	//							INT64 incremental_qty=_wtoi64(NetPosGrid::m_st_Netposition.m_incre_qty)+_wtoi64(m_new_qty);
	//							CString str_incremental_qty=L"";
	//							str_incremental_qty.Format(L"%d",incremental_qty);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_incre_qty,str_incremental_qty);
	//							INT64 pre_net_qty=_wtoi64(m_str_netqty)-_wtoi64(m_new_qty);
	//							CString str_prenetqty=L"";
	//							str_prenetqty.Format(L"%d",pre_net_qty);
	//							//CMTStr::Copy(NetPosGrid::m_st_Netposition.m_pre_qty,str_prenetqty);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_last_rate ,m_str_Last_Rate);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Floating_Profit ,m_str_Floating_Profit);
	//							get_login_balance_details(m_str_login);
	//							double d_total_bal=0;								
	//							LPTSTR endPtr;
	//							double d_pl= _tcstod(m_str_Floating_Profit, &endPtr);
	//							d_total_bal=NetPosGrid::Pre_balance+d_pl;	
	//							NetPosGrid::Client_Balance m_Client_Balance={};
	//							m_Client_Balance.Total_Balance=d_total_bal;
	//							//CMTStr::Copy(m_Client_Balance.V_login,m_str_Floating_Profit);
	//							if (NetPosGrid::row_position>=0)
	//							{
	//								NetPosGrid::m_Client_Balance_Array.Update(NetPosGrid::row_position,&m_Client_Balance);
	//							}
	//							else
	//							{
	//								NetPosGrid::m_Client_Balance_Array.Add(&m_Client_Balance);
	//							}



	//							m_str_Balance.Format(L"%.0lf",d_total_bal);
	//							CMTStr::Copy(NetPosGrid::m_st_Netposition.m_Balance ,m_str_Balance);								
	//							if(check_new_row==1)
	//							{
	//								NetPosGrid::m_NetpositionArray.Update(rows_position,&NetPosGrid::m_st_Netposition);
	//								
	//							}
	//							else
	//							{
	//								rows_position=total_rows_count;
	//								NetPosGrid::m_NetpositionArray.Add(&NetPosGrid::m_st_Netposition);
	//							}	
	//							}
	//							//End of Ignore Duplicate Data																																						
	//						}									
	//						//m_logfile_g.LogEvent(L"End Netposition_NewData");
	//						
	//						NetPosGrid::mutex_Symbol_ltp.Unlock();							
	//					}
	//					if (wcscmp(str_key,L"Symbol_List")==0)
	//					{							
	//						NetPosGrid::m_SymbolMultiplyer.Clear();
	//						for (string::size_type  i = 0; i < rows.Size(); i++)
	//						{
	//							int check_new_row=0;								
	//							_bstr_t  m_symbol=rows[i]["symbol"].GetString() ;
	//							CString m_str_symbol=m_symbol;
	//							_bstr_t  m_multi=rows[i]["multi"].GetString() ;
	//							CString m_str_multi=m_multi;																						
	//															
	//							CMTStr::Copy(NetPosGrid::m_st_multiplyer.m_symbol ,m_symbol);								
	//							LPTSTR endPtr;
	//							NetPosGrid::m_st_multiplyer.m_multiplyer= _tcstod(m_multi , &endPtr);
	//							NetPosGrid::m_SymbolMultiplyer.Add(&NetPosGrid::m_st_multiplyer);
	//						}
	//						//m_logfile_g.LogEvent(L"Start RequestHandler 6");
	//					}
	//					
	//					if (wcscmp(str_key,L"Client_List")==0)
	//					{							
	//						NetPosGrid::m_Client_Details_Array.Clear();							
	//						for (string::size_type  i = 0; i < rows.Size(); i++)
	//						{
	//							int check_new_row=0;	
	//							_bstr_t  V_login=rows[i]["V_login"].GetString();
	//							_bstr_t  V_Name=rows[i]["V_Name"].GetString();
	//							_bstr_t  Comment_YN=rows[i]["Comment_YN"].GetString();
	//							_bstr_t  Ignore_YN=rows[i]["Ignore_YN"].GetString();
	//							_bstr_t  client_group=rows[i]["client_group"].GetString();
	//							_bstr_t  Client_Group1=rows[i]["Client_Group1"].GetString();
	//							_bstr_t  Client_Group2=rows[i]["Client_Group2"].GetString();
	//							_bstr_t  Client_Group4=rows[i]["Client_Group4"].GetString();
	//							_bstr_t   Client_Credit=rows[i]["Client_Credit"].GetString();

	//							CString   str_V_login=V_login;
	//							CString   str_V_Name=V_Name;
	//							CString   str_Comment_YN=Comment_YN;
	//							CString   str_Ignore_YN=Ignore_YN;
	//							CString   str_client_group=client_group;
	//							CString   str_Client_Group1=Client_Group1;
	//							CString   str_Client_Group2=Client_Group2;
	//							CString   str_Client_Group4=Client_Group4;
	//							CString   str_Client_Credit=Client_Credit;								

	//							CMTStr::Copy(NetPosGrid::m_Client_Details.V_login,str_V_login);
	//							CMTStr::Copy(NetPosGrid::m_Client_Details.V_Name,str_V_Name);
	//							CMTStr::Copy(NetPosGrid::m_Client_Details.Comment_YN,str_Comment_YN);
	//							CMTStr::Copy(NetPosGrid::m_Client_Details.Ignore_YN,str_Ignore_YN);
	//							CMTStr::Copy(NetPosGrid::m_Client_Details.client_group,str_client_group);
	//							CMTStr::Copy(NetPosGrid::m_Client_Details.Client_Group1,str_Client_Group1);
	//							CMTStr::Copy(NetPosGrid::m_Client_Details.Client_Group2,str_Client_Group2);
	//							CMTStr::Copy(NetPosGrid::m_Client_Details.Client_Group4,str_Client_Group4);
	//							LPTSTR endPtr;
	//							NetPosGrid::m_Client_Details.Client_Credit=_tcstod(Client_Credit , &endPtr);
	//							NetPosGrid::m_Client_Details_Array.Add(&NetPosGrid::m_Client_Details);
	//						}							
	//					}
	//					
	//				
	//			}
	//		}
	//		
	//	}
	//	int check_server_status=OrderGrid::m_Client.Send("",1);
	//	if (check_server_status==-1)
	//	{		
	//		OrderGrid::first_time_data_Received_YN=1;
	//		OrderGrid::m_Client.Close();
	//		if(OrderGrid::m_Client.Create()==FALSE)
	//		{
	//			AfxMessageBox(L"Failed to Create Socket");
	//			
	//		}	
	//		
	//		if(OrderGrid::m_Client.Connect(L"68.168.104.26",5042)==FALSE)
	//		{
	//			//AfxMessageBox(L"Failed to Connect");				
	//		}	
	//	}
	//}
	}
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description());
	}


	//m_logfile_g.LogEvent(L"End RequestHandler");
	return 0;
}


int OrderGrid::OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow)
{
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newcol);
	UNREFERENCED_PARAMETER(newrow);
	return TRUE;
}

void OrderGrid::ThreadStart()
{
	m_SocketThred=AfxBeginThread(RequestHandler, this);		
}
void OrderGrid::OnSetup()
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
	SetUniformRowHeight( TRUE );	
	// Start timers
	srand( (unsigned)time( NULL ) );
	SetTimer(0, 20, NULL);
	//SetTimer(1, 100, NULL);

	/*if( AfxSocketInit() == FALSE)
	{ 
		AfxMessageBox(L"Failed to Initialize Sockets"); 
		return; 
	}

	if(m_Client.Create()==FALSE)
	{
		MessageBox(L"Failed to Create Socket");
		return;

	}
	if(m_Client.Connect(L"69.64.74.136",5041)==FALSE)
	{
		MessageBox(L"Failed to Connect");
		return;

	}
*/

	QuickSetCellType( 0, -1, m_iArrowIndex );
	SortBy( 0, UG_SORT_ASCENDING );

	m_iSortCol = 0;
	m_bSortedAscending = TRUE;



	m_pThreads=AfxBeginThread(update_data_PBNPS_Order, this);		
	

	
	

		//m_pThread = new CUIThread();
		//m_pThread->m_bAutoDelete = FALSE;	// Disable auto deletion of thread object upon thread termination.
		//m_pThread->SetParent(this);		
		//m_pThread->CreateThread();
		run_check=0;		
}

UINT update_data_PBNPS_Order(void *pParam)
{
	OrderGrid* pThis= (OrderGrid*)pParam;	
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<COrder_Table> > artists1;	
	HRESULT hr;
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=TradeDataBase;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	if(SUCCEEDED(hr))
	{
		session.Open(connection);
		while (true )
		{				
			_bstr_t strCommand="";		
			strCommand="Proc_Order";        
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
				 OrderGrid::m_st_Order_UpdateArray.Clear();
				 while (artists1.MoveNext() == S_OK)
				 {																	  
					CMTStr::Copy(OrderGrid::m_st_Order_Update.login,artists1.m_Checked);				 					
					CMTStr::Copy(OrderGrid::m_st_Order_Update.time,artists1.m_time);				 										
					CMTStr::Copy(OrderGrid::m_st_Order_Update.deal ,artists1.m_deal);				 										 
					CMTStr::Copy(OrderGrid::m_st_Order_Update.order ,artists1.m_order);																
					CMTStr::Copy(OrderGrid::m_st_Order_Update.symbol ,artists1.m_symbol);																										 
					CMTStr::Copy(OrderGrid::m_st_Order_Update.action ,artists1.m_Type);											
					CMTStr::Copy(OrderGrid::m_st_Order_Update.volume ,artists1.m_volume);								
					LPTSTR endPtr;
					double d_m_PL = _tcstod(artists1.m_price, &endPtr);												
					CString cstrpl;
					cstrpl.Format(_T("%.2f"),d_m_PL);	
					CMTStr::Copy(OrderGrid::m_st_Order_Update.price ,cstrpl);											
					CMTStr::Copy(OrderGrid::m_st_Order_Update.comment ,artists1.m_comment);											
					CMTStr::Copy(OrderGrid::m_st_Order_Update.OurComment ,artists1.m_OurComment);	
					CMTStr::Copy(OrderGrid::m_st_Order_Update.Change_YN  ,artists1.m_CommentYN);

					CMTStr::Copy(OrderGrid::m_st_Order_Update.TYPE ,artists1.m_TYPE);											
					CMTStr::Copy(OrderGrid::m_st_Order_Update.subtype ,artists1.m_subtype);											
					CMTStr::Copy(OrderGrid::m_st_Order_Update.orderno_2 ,artists1.m_orderno_2);	
					CMTStr::Copy(OrderGrid::m_st_Order_Update.trade_time  ,artists1.m_trade_time);
					OrderGrid::m_st_Order_UpdateArray.Add(&OrderGrid::m_st_Order_Update);
				 }
				 artists1.Close();


				 OrderGrid::m_order_mutex.Lock();

				 int val_type=0;	
				 val_type=0;
				 if (OrderGrid::insertFilterFlag==1 )
				 {
					OrderGrid::m_st_Order_GridArray.Clear();
					int noof_rowsInStruc=OrderGrid::m_st_Order_UpdateArray.Total();
					for(int fcount=0;fcount<noof_rowsInStruc;fcount++)
					{
						OrderGrid::st_Order_Update m_st_Netposition={};
						m_st_Netposition=OrderGrid::m_st_Order_UpdateArray[fcount];
						int flag=0;				
						CString col_row_val[16];		
						col_row_val[0]=m_st_Netposition.login ;
						if (OrderGrid::col0_val.Trim().GetLength()>0)
						{
							col_row_val[0]=col_row_val[0].Mid(0,OrderGrid::col0_val.Trim().GetLength());
						}
						col_row_val[1]=m_st_Netposition.time ;
						if (OrderGrid::col1_val.Trim().GetLength()>0)
						{
							col_row_val[1]=col_row_val[1].Mid(0,OrderGrid::col1_val.Trim().GetLength());
							col_row_val[1]=col_row_val[1].Mid(0,10);
						}
						col_row_val[2]=L"" ;
						if (OrderGrid::col2_val.Trim().GetLength()>0)
						{
							col_row_val[2]=col_row_val[2].Mid(0,OrderGrid::col2_val.Trim().GetLength());
						}
						
						col_row_val[3]=m_st_Netposition.order ;
						if (OrderGrid::col3_val.Trim().GetLength()>0)
						{
							col_row_val[3]=col_row_val[3].Mid(0,OrderGrid::col3_val.Trim().GetLength());
						}

						col_row_val[4]=m_st_Netposition.symbol;
						if (OrderGrid::col4_val.Trim().GetLength()>0)
						{
							col_row_val[4]=col_row_val[4].Mid(0,OrderGrid::col4_val.Trim().GetLength());
						}

						col_row_val[5]=m_st_Netposition.action ;
						if (OrderGrid::col5_val.Trim().GetLength()>0)
						{
							col_row_val[5]=col_row_val[5].Mid(0,OrderGrid::col5_val.Trim().GetLength());
						}

						col_row_val[6]=m_st_Netposition.volume;
						boolean bool_col6=Check_numeric_col_filter(OrderGrid::col6_val,col_row_val[6]);

						col_row_val[7]=m_st_Netposition.price  ;
						boolean bool_col7=Check_numeric_col_filter(OrderGrid::col7_val,col_row_val[7]);

						col_row_val[8]=m_st_Netposition.comment ;
						if (OrderGrid::col8_val.Trim().GetLength()>0)
						{
							col_row_val[8]=col_row_val[8].Mid(0,OrderGrid::col8_val.Trim().GetLength());
						}

						col_row_val[9]=m_st_Netposition.OurComment  ;
						if (OrderGrid::col9_val.Trim().GetLength()>0)
						{
							col_row_val[9]=col_row_val[9].Mid(0,OrderGrid::col9_val.Trim().GetLength());
						}

						col_row_val[10]=m_st_Netposition.Change_YN  ;
						if (OrderGrid::col10_val.Trim().GetLength()>0)
						{
							col_row_val[10]=col_row_val[10].Mid(0,OrderGrid::col10_val.Trim().GetLength());
						}
						col_row_val[11]=m_st_Netposition.TYPE  ;
						if (OrderGrid::col11_val.Trim().GetLength()>0)
						{
							col_row_val[11]=col_row_val[11].Mid(0,OrderGrid::col11_val.Trim().GetLength());
						}
						col_row_val[12]=m_st_Netposition.subtype  ;
						if (OrderGrid::col12_val.Trim().GetLength()>0)
						{
							col_row_val[12]=col_row_val[12].Mid(0,OrderGrid::col12_val.Trim().GetLength());
						}
						col_row_val[13]=m_st_Netposition.orderno_2  ;
						if (OrderGrid::col13_val.Trim().GetLength()>0)
						{
							col_row_val[13]=col_row_val[13].Mid(0,OrderGrid::col13_val.Trim().GetLength());
						}
						col_row_val[14]=m_st_Netposition.trade_time ;
						if (OrderGrid::col14_val.Trim().GetLength()>0)
						{
							col_row_val[14]=col_row_val[14].Mid(0,OrderGrid::col14_val.Trim().GetLength());
						}
						OrderGrid::col15_val=m_st_Netposition.deal ;
						if (OrderGrid::col15_val.Trim().GetLength()>0)
						{
							col_row_val[15]=col_row_val[15].Mid(0,OrderGrid::col15_val.Trim().GetLength());
						}


						if((OrderGrid::col0_val.Trim()==col_row_val[0].Trim() || OrderGrid::col0_val.Trim()==L"ALL"||OrderGrid::col0_val.Trim()==L"") && (OrderGrid::col1_val.Trim()==col_row_val[1].Trim() || OrderGrid::col1_val.Trim()==L"ALL"||OrderGrid::col1_val.Trim()==L"") && (OrderGrid::col2_val.Trim()==col_row_val[2].Trim() || OrderGrid::col2_val.Trim()==L"ALL"||OrderGrid::col2_val.Trim()==L"")  && (OrderGrid::col3_val.Trim()==col_row_val[3].Trim() || OrderGrid::col3_val.Trim()==L"ALL"||OrderGrid::col3_val.Trim()==L"") && (OrderGrid::col4_val.Trim()==col_row_val[4].Trim() || OrderGrid::col4_val.Trim()==L"ALL"||OrderGrid::col4_val.Trim()==L"")   && (OrderGrid::col5_val.Trim()==col_row_val[5].Trim() || OrderGrid::col5_val.Trim()==L"ALL"||OrderGrid::col5_val.Trim()==L"")   && (bool_col6==true || OrderGrid::col6_val.Trim()==L"ALL"||OrderGrid::col6_val.Trim()==L"")   && (bool_col7==true || OrderGrid::col7_val.Trim()==L"ALL"||OrderGrid::col7_val.Trim()==L"")   && (OrderGrid::col8_val.Trim()==col_row_val[8].Trim() || OrderGrid::col8_val.Trim()==L"ALL"||OrderGrid::col8_val.Trim()==L"") && (OrderGrid::col9_val.Trim()==col_row_val[9].Trim() || OrderGrid::col9_val.Trim()==L"ALL"||OrderGrid::col9_val.Trim()==L"") &&(OrderGrid::col10_val==col_row_val[10] || OrderGrid::col10_val==L"ALL"||OrderGrid::col10_val==L"")&&(OrderGrid::col11_val==col_row_val[11] || OrderGrid::col11_val==L"ALL"||OrderGrid::col11_val==L"")&&(OrderGrid::col12_val==col_row_val[12] || OrderGrid::col12_val==L"ALL"||OrderGrid::col12_val==L"") &&(OrderGrid::col13_val==col_row_val[13] || OrderGrid::col13_val==L"ALL"||OrderGrid::col13_val==L"")&&(OrderGrid::col14_val==col_row_val[14] || OrderGrid::col14_val==L"ALL"||OrderGrid::col14_val==L"")&&(OrderGrid::col15_val==col_row_val[15] || OrderGrid::col15_val==L"ALL"||OrderGrid::col15_val==L""))
						{
							OrderGrid::m_st_Order_GridArray.Add(&m_st_Netposition);
						}
					}
				 }
				 else
				 {
					  OrderGrid::m_st_Order_GridArray.Assign(OrderGrid::m_st_Order_UpdateArray);
				 }









	int t_rows=OrderGrid::m_st_Order_GridArray.Total();
	OrderGrid::st_Order_Update first_st={};
	OrderGrid::st_Order_Update next_st={};
	OrderGrid::st_Order_Update swap_st={};
	val_type=0;
	if (OrderGrid::col_click==7 || OrderGrid::col_click==6)
	{
		val_type=1;
	}
	for (int i=0;i<t_rows;i++)
	{
		first_st=OrderGrid::m_st_Order_GridArray[i];
		for (int j=i+1;j<t_rows;j++)
		{
			next_st=OrderGrid::m_st_Order_GridArray[j];
			if (OrderGrid::a_d==0)
			{
				if (val_type==0)
				{
					if (OrderGrid::col_click==0)
					{
						if (wcscmp(first_st.login   ,next_st.login   )>0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.login ,swap_st.login  );							
						}
					}
					if (OrderGrid::col_click==1)
					{
						if (wcscmp(first_st.time   ,next_st.time   )>0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.time   ,swap_st.time  );							
						}
					}
					
					if (OrderGrid::col_click==3)
					{
						if (wcscmp(first_st.order  ,next_st.order  )>0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.order  ,swap_st.order );							
						}
					}
					if (OrderGrid::col_click==4)
					{
						if (wcscmp(first_st.symbol   ,next_st.symbol   )>0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.symbol ,swap_st.symbol  );							
						}
					}
					
					if (OrderGrid::col_click==5)
					{
						if (wcscmp(first_st.action   ,next_st.action   )>0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.action ,swap_st.action  );							
						}
					}


					if (OrderGrid::col_click==8)
					{
						if (wcscmp(first_st.comment   ,next_st.comment  )>0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.comment ,swap_st.comment );							
						}
					}






					if (OrderGrid::col_click==9)
					{
						if (wcscmp(first_st.OurComment  ,next_st.OurComment  )>0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.OurComment,swap_st.OurComment );							
						}
					}
					if (OrderGrid::col_click==10)
					{
						if (wcscmp(first_st.Change_YN  ,next_st.Change_YN  )>0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.Change_YN  ,swap_st.Change_YN );							
						}
					}


					if (OrderGrid::col_click==15)
					{
						if (wcscmp(first_st.deal   ,next_st.deal  )>0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.deal   ,swap_st.deal );							
						}
					}

				}	
				else
				{
					if (OrderGrid::col_click==6)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.volume, &endPtr1);
						double val2=_tcstod(next_st.volume, &endPtr1);
						if (val1>val2)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.volume  ,swap_st.volume  );							
						}
					}
					if (OrderGrid::col_click==7)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.price, &endPtr1);
						double val2=_tcstod(next_st.price, &endPtr1);
						if (val1>val2)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.price ,swap_st.price  );							
						}
					}
					
				}
				}
			else
			{
				if (val_type==0)
				{

					if (OrderGrid::col_click==0)
					{
						if (wcscmp(first_st.login   ,next_st.login   )<0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.login ,swap_st.login  );							
						}
					}
					if (OrderGrid::col_click==1)
					{
						if (wcscmp(first_st.time   ,next_st.time   )<0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.time   ,swap_st.time  );							
						}
					}
					
					if (OrderGrid::col_click==3)
					{
						if (wcscmp(first_st.order  ,next_st.order  )<0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.order  ,swap_st.order );							
						}
					}
					if (OrderGrid::col_click==4)
					{
						if (wcscmp(first_st.symbol   ,next_st.symbol   )<0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.symbol ,swap_st.symbol  );							
						}
					}
					if (OrderGrid::col_click==5)
					{
						if (wcscmp(first_st.action   ,next_st.action   )<0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.action ,swap_st.action  );							
						}
					}
					if (OrderGrid::col_click==7)
					{
						if (wcscmp(first_st.Change_YN  ,next_st.Change_YN  )<0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.Change_YN  ,swap_st.Change_YN );							
						}
					}

					if (OrderGrid::col_click==8)
					{
						if (wcscmp(first_st.comment   ,next_st.comment  )<0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.comment ,swap_st.comment );							
						}
					}

					if (OrderGrid::col_click==9)
					{
						if (wcscmp(first_st.OurComment  ,next_st.OurComment  )<0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.OurComment,swap_st.OurComment );							
						}
					}

					if (OrderGrid::col_click==15)
					{
						if (wcscmp(first_st.deal   ,next_st.deal  )>0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.deal   ,swap_st.deal );							
						}
					}

					if (OrderGrid::col_click==10)
					{
						if (wcscmp(first_st.Change_YN  ,next_st.Change_YN  )<0)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.Change_YN  ,swap_st.Change_YN );							
						}
					}
				}

				else
				{
					if (OrderGrid::col_click==6)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.volume, &endPtr1);
						double val2=_tcstod(next_st.volume, &endPtr1);
						if (val1<val2)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.volume  ,swap_st.volume  );							
						}
					}
					if (OrderGrid::col_click==7)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.price, &endPtr1);
						double val2=_tcstod(next_st.price, &endPtr1);
						if (val1<val2)
						{
							OrderGrid::m_st_Order_GridArray.Shift(j,i-j);
							swap_st=OrderGrid::m_st_Order_GridArray[i];
							CMTStr::Copy(first_st.price ,swap_st.price  );							
						}
					}
					
				}
				
					
				}
			}
		}

	OrderGrid::m_order_mutex.Unlock();

			 }		 
			 Sleep(10);			 
		}
	}
    return 0;
}
boolean OrderGrid::CheckvalueInArray(CString orderno)
{
	int total_value =OrderGrid::m_st_Order_UpdateArray.Total();
	for (int i=0;i<total_value;i++)
	{
		st_Order_Update m_cc={};
		m_cc=OrderGrid::m_st_Order_UpdateArray[i];
		CString dealin_array=m_cc.order  ;
		if (wcscmp(dealin_array,orderno)==0)
		{
			return true;
		}
	}
	return false;
}



LRESULT OrderGrid::OnThreadMessage(WPARAM wParam, LPARAM lParam)
{	
	int grid_total_rows=GetNumberRows();
	int i=grid_total_rows-1;
	for (i;i>=0;i--)
	{
		CString Deal_in_Grid=QuickGetText(3,i);
		if (CheckvalueInArray(Deal_in_Grid)==false && Deal_in_Grid!="")
		{
			DeleteRow(i);

		}
	}
	int array_total=OrderGrid::m_st_Order_UpdateArray.Total();
	for (int i=0;i<array_total;i++)
	{
		st_Order_Update m_cc={};
		m_cc=OrderGrid::m_st_Order_UpdateArray[i];
		CString array_deal=m_cc.deal  ;
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
			CString grid_order=QuickGetText(3,r);
			CString grid_comment=QuickGetText(8,r);
			CString grid_price=QuickGetText(7,r);
			if (wcscmp(grid_order,array_order)==0)
			{
				check_new=0;
				if (wcscmp(array_comment,grid_comment)!=0 || wcscmp(array_price,grid_price)!=0)
				{
					QuickSetText(8,r,array_comment);
					QuickSetText(9,r,array_Ourcomment);
					CUGCell cell ;
					GetColDefault( 10, &cell);			
					QuickSetCellType(10,r,UGCT_CHECKBOX);	
					QuickSetCellTypeEx(10,r,UGCT_CHECKBOXCHECKMARK);
					SetColDefault( 10, &cell );
					QuickSetText(10,r,array_Change_YN);
					QuickSetText(11,r,array_deal);
				}
			}
		}
		if (check_new==1 )
		{	
			int r_no=GetNumberRows();			
			SetNumberRows(r_no+1);			
			QuickSetText(0,r_no,array_login);
			QuickSetText(1,r_no,array_time);
			QuickSetText(2,r_no,L"");			
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
			QuickSetText(10,r_no,array_Change_YN);
			QuickSetText(11,r_no,array_deal);					
		}
	}		
	RedrawAll();	
	return 0;
}



LRESULT OrderGrid::Get_order_grid_rowcount(WPARAM wParam, LPARAM lParam)
{
	
	OrderGrid::grid_rows_count=GetNumberRows();
	return 0;
}


LRESULT OrderGrid::Get_order_grid_text(WPARAM wParam, LPARAM lParam)
{
	
	int col_no=int(wParam);
	int row_no=int(lParam);
	OrderGrid::ordergrid_text=QuickGetText(col_no,row_no);
	return 0;
}



LRESULT OrderGrid::OrderGrid_rowDelete(WPARAM wParam, LPARAM lParam)
{	
	int col_no=int(wParam);
	int row_no=int(lParam);
	DeleteRow(row_no);
	return 0;
}
LRESULT OrderGrid::Set_order_grid_text(WPARAM wParam, LPARAM lParam)
{
	
	int col_no=int(wParam);
	int row_no=int(lParam);
	QuickSetText(col_no,row_no,OrderGrid::str_orderGrid_settext);
	return 0;
}
LRESULT OrderGrid::Ordergrid_cellFormat(WPARAM wParam, LPARAM lParam)
{
	int col_no=int(wParam);
	int row_no=int(lParam);
	CUGCell cell ;
	GetColDefault( col_no, &cell);			
	QuickSetCellType(col_no,row_no,UGCT_CHECKBOX);	
	QuickSetCellTypeEx(col_no,row_no,UGCT_CHECKBOXCHECKMARK);
	SetColDefault( col_no, &cell );
	QuickSetText(col_no,row_no,OrderGrid::str_orderGrid_settext);
	return 0;
	
}

LRESULT OrderGrid::Set_Norow_order_grid(WPARAM wParam, LPARAM lParam)
{
	
	int col_no=int(wParam);
	int row_no=int(lParam);
	SetNumberRows(row_no);
	return 0;
}

LRESULT OrderGrid::OrderGrid_Redrawall(WPARAM wParam, LPARAM lParam)
{
	RedrawAll();
	return 0;
}

void OrderGrid::Selected_ActivateOrder()
{
	if(CDealer::admin_login!=1)
	{
		AfxMessageBox(L"You Are not a valid user");
		return ;
	}	
	int rows_count=GetNumberRows();
	
	CString order=L"";
	
	for (int fcount=0;fcount<rows_count;fcount++)
	{		
		order=QuickGetText(3,fcount);	
		CString check_value=QuickGetText(10,fcount);
		
		if (check_value==L"1" ) 
		{
			int status_check=0;
			status_check=DlgHelp::m_dealer->Activate_Order(order);	
			/*if (status_check==1)
			{*/
				_bstr_t strCommand="";
				_bstr_t bstrorder=order;
				strCommand="exec Proc_order_Passed_By_Manager '" + bstrorder + "'";
				char* strCommand_char=(char*)strCommand;
				hrn=cmd.Open(session_update,strCommand_char);							 			 		 				 	
			//}
			cmd.Close();

		}
	}		
	AfxMessageBox(L"Data has been  SuccessFully updated");
}