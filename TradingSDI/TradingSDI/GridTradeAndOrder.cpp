#include "stdafx.h"
#include "resource.h"
#include "GridTradeAndOrder.h"
#include <afxdisp.h>
#include <time.h>
#include <locale.h>
#include "MainFrm.h"
#include "document.h"
#include <iostream>
#include "CNetPosTable.h"
#include "Netpos_Get_Data.h"
#include "OverViewOrderGrid.h"
#include "Table_Position_Detail.h"
using namespace std;
using namespace rapidjson;
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace rename("EOF", "EndOfFile")

#define WM_MY_THREAD_MESSAGE1					WM_APP+200
#define WM_MY_THREAD_MESSAGE_ROWSNO1			WM_APP+201
#define WM_MY_THREAD_MESSAGE_REFRESH1			WM_APP+202
#define GRID_ROWS_COUNT1						WM_APP+203
#define DELETE_ROW1	     						WM_APP+204
#define DELETE_THREAD	     					WM_APP+205
#define ROW_NO_FIND	     						WM_APP+206
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//CUIThread
BEGIN_MESSAGE_MAP(GridTradeAndOrder,CUGCtrl)	
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_MESSAGE(WM_MY_THREAD_MESSAGE1, OnThreadMessage)
	ON_MESSAGE(WM_MY_THREAD_MESSAGE_ROWSNO1, OnThreadMessage_RowsNo)		
	ON_MESSAGE(WM_MY_THREAD_MESSAGE_REFRESH1, GridRefresh)		
	ON_MESSAGE(GRID_ROWS_COUNT1, GridRowCount)		
	ON_MESSAGE(DELETE_ROW1, RowDelete)		
	ON_MESSAGE(DELETE_THREAD,DeleteThred)
	ON_MESSAGE(ROW_NO_FIND,rownofind)	
END_MESSAGE_MAP()
//Structure variable
GridTradeAndOrder::st_gridAndOrder_Array GridTradeAndOrder::m_gridAndOrder_Array_Fill;
GridTradeAndOrder::st_gridAndOrder_Array GridTradeAndOrder::m_gridAndOrder_Grid_array;
GridTradeAndOrder::st_gridAndOrder_Array GridTradeAndOrder::m_gridAndOrder_Array;
CMutex GridTradeAndOrder::gridAndOrder_mutex;

GridTradeAndOrder::st_gridAndOrder GridTradeAndOrder::m_st_Dealing={};
//others
CString GridTradeAndOrder::m_c_symbol=L"";
int GridTradeAndOrder::value_row_no=0;
int GridTradeAndOrder::filter_break=0;
int GridTradeAndOrder::col_click=0;
int GridTradeAndOrder::a_d=0;

int GridTradeAndOrder::insertFilterFlag=0;
int GridTradeAndOrder::check_First=0;
int GridTradeAndOrder::thred_killed_ok=0;
_variant_t GridTradeAndOrder::avarRecords;
int GridTradeAndOrder::lock_data=0;
int GridTradeAndOrder::intRows=0;
int GridTradeAndOrder::lock_data_fill=0;
int GridTradeAndOrder::Grid_Rows_Count=0;
int GridTradeAndOrder::data_display=0;
int GridTradeAndOrder::grid_populate_check=0;
_bstr_t GridTradeAndOrder::m_selected_login="0";
_bstr_t GridTradeAndOrder::m_selected_Name="0";
_bstr_t GridTradeAndOrder::strShort("  order by t1.login asc,t1.symbol asc");
_bstr_t GridTradeAndOrder::cellvalue("");
_bstr_t GridTradeAndOrder::strFilter(" ");
_variant_t GridTradeAndOrder::result;
long GridTradeAndOrder::rgIndices[2];
_bstr_t GridTradeAndOrder::bstr_currenttime("");

//filter value global use
CString GridTradeAndOrder::col0_val=L"";
CString GridTradeAndOrder::col1_val=L"";
CString GridTradeAndOrder::col2_val=L"";
CString GridTradeAndOrder::col3_val=L"";
CString GridTradeAndOrder::col4_val=L"";
CString GridTradeAndOrder::col5_val=L"";
CString GridTradeAndOrder::col6_val=L"";
CString GridTradeAndOrder::col7_val=L"";
CString GridTradeAndOrder::col8_val=L"";
CString GridTradeAndOrder::col9_val=L"";
CString GridTradeAndOrder::col10_val=L"";
CString GridTradeAndOrder::col11_val=L"";
CString GridTradeAndOrder::col12_val=L"";
/////////////////////////////////////////////////////////////////////////////
//Standard MyCug construction/destruction

int GridTradeAndOrder::thread_check=0;
extern  CLogFile m_logfile_g;


GridTradeAndOrder::GridTradeAndOrder()
{
	GridTradeAndOrder::thread_check=0;
	//m_logfile_g.LogEvent(L"Start GridTradeAndOrder");	
	 t = CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S");
	 bstr_currenttime=t;
	 GridTradeAndOrder::grid_populate_check=0;
	UGXPThemes::UseThemes(false);
	//m_logfile_g.LogEvent(L"End GridTradeAndOrder");
}

GridTradeAndOrder::~GridTradeAndOrder()
{
	//m_logfile_g.LogEvent(L"Start GridTradeAndOrder");
	try
	{

    UGXPThemes::CleanUp();	
	GridTradeAndOrder::thread_check=1;
    DWORD exit_code= NULL;
	if (m_pThreads != NULL)
	{
	if(WaitForSingleObject(m_pThreads->m_hThread, INFINITE) != WAIT_OBJECT_0) 
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
	}
		catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"Thread UnInitiliaze");			
	}
	
//m_logfile_g.LogEvent(L"End GridTradeAndOrder");
   
}

LRESULT GridTradeAndOrder::DeleteThred(WPARAM wParam, LPARAM lParam)
{
	//m_logfile_g.LogEvent(L"Start DeleteThred");
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
	
	GridTradeAndOrder::thred_killed_ok=0;
	//m_logfile_g.LogEvent(L"End DeleteThred");
	return 0;
}

UINT update_data_Trade(void*);
UINT update_data_Trade(void *pParam)
{
	//m_logfile_g.LogEvent(L"Start update_data_Trade");
	
	GridTradeAndOrder* pThis= (GridTradeAndOrder*)pParam;	
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<CTable_Position_Detail> > artists1;
	HRESULT hr;
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	
     if(SUCCEEDED(hr))
     {
		hr=session.Open(connection);
		while (GridTradeAndOrder::thread_check==0)
		{				
            _bstr_t strCommand="";		
		     strCommand="select vt1.symbol,'' as 'order',vt3.lastTime,case when vt1.netqty>0 then 'BUY' when vt1.netqty<0 then 'SELL' else '' end  as 'TYPE',vt1.netqty as 'VOLUME',vt1.avgrate as 'Price',vt2.last_tick as 'CURRENT_RATE' ,case when vt1.netqty<0 then (isnull(vt2.last_tick,0)-vt1.avgrate)*vt1.netqty*vt1.contractSize when vt1.netqty>0 then (isnull(vt2.last_tick,0)-vt1.avgrate)*vt1.netqty*vt1.contractSize else 0  end as 'PL',vt3.[status],vt6.TotalTrade,vt7.Checked_time,vt8.limit,vt7.REMARK2  from  (select PositionAverageAccounting.Symbol,PositionAverageAccounting.multiplayer as 'contractSize',totalvolume/10000 as 'NetQty', WavgPrice as 'AVGRate' from PositionAverageAccounting where  PositionAverageAccounting.[login]='" + GridTradeAndOrder::m_selected_login + "' and totalvolume<>0   )vt1 left outer join (select t1.symbol,last_tick.last_tick from last_tick left outer join symbol_mapping as t1 on t1.mapping_Symbol=last_tick.symbol) vt2 on vt1.symbol=vt2.symbol left outer join (select t1.symbol,t1.LastTime,t1.Last_Deal,case when ([type]=0 or [type]=1) then 'MARKET' else 'LIMIT' end  as 'STATUS' from (select symbol,max([time]) 'LastTime',max([order])  as 'Last_Deal' from  Deal_Table_Accounting where Deal_Table_Accounting.[login]='" + GridTradeAndOrder::m_selected_login + "'   group by Deal_Table_Accounting.Symbol ) t1 left outer join mt5_orders_history on t1.last_deal=mt5_orders_history.[order])vt3 on vt1.symbol=vt3.symbol left outer join (select [symbol],cast(sum(case when col1=1 then col2 else 0 end) as varchar(20))+'/' +cast(sum(col2) as varchar(20)) as 'TotalTrade' from  (select [symbol],isnull(checked,0) as 'Col1',count (isnull(checked,0)) as 'Col2' from mt5_deals left outer join Trade_Checked on mt5_deals.Deal=Trade_Checked.Deal  LEFT  outer join client on client.V_login=cast(mt5_deals.[login]  as varchar(20))  where (cast(mt5_deals.[login] as varchar(50))='" + GridTradeAndOrder::m_selected_login + "' and comment='' and  isnull(Comment_YN,'N') ='Y')  or (cast(mt5_deals.[login] as varchar(50))='" + GridTradeAndOrder::m_selected_login + "' and isnull(Comment_YN,'N') <>'Y') group by [symbol],isnull(checked,0) )t1 group by [symbol])vt6 on vt6.symbol=vt1.symbol  left outer join (select * from Position_Check where [login]='" + GridTradeAndOrder::m_selected_login + "')vt7 on vt1.symbol=vt7.symbol left outer join ( select [login],symbol,cast(isnull(limit,0) as varchar(20))+'/'+cast(isnull(LimitSell,0) as varchar(20)) as limit from Limit_Mapping where [login]='" + GridTradeAndOrder::m_selected_login + "')vt8 on  vt1.symbol=vt8.symbol";
	    
			 if(SUCCEEDED(hr))
			 {
				 hr=artists1.Open(session,(LPCTSTR)strCommand);							 
			 }
			 		
			 if(SUCCEEDED(hr))
			 {
				 GridTradeAndOrder::m_gridAndOrder_Array_Fill.Clear();
				 //GridTradeAndOrder::st_gridAndOrder m_st_Dealing={};				 
				 while (artists1.MoveNext() == S_OK)
				 {									
                    LPTSTR endPtr;
				    double d_m_PL = _tcstod(artists1.m_Price, &endPtr);												
					CString cstrpl;
					cstrpl.Format(_T("%.2f"),d_m_PL);	

					CString cstr_Symbol=artists1.m_Symbol;
					CMTStr::Copy(GridTradeAndOrder::m_st_Dealing.Symbol ,cstr_Symbol);				 					
					CString cstr_Order=artists1.m_Order;
					CMTStr::Copy(GridTradeAndOrder::m_st_Dealing.Order ,cstr_Order);

					CString cstr_Time=artists1.m_Time;
					CMTStr::Copy(GridTradeAndOrder::m_st_Dealing.Time,cstr_Time ) ;

					CString cstr_Type=artists1.m_Type ;

					
					CMTStr::Copy(GridTradeAndOrder::m_st_Dealing.Type ,cstr_Type);		

					CString cstr_Volume=artists1.m_Volume ;
					CMTStr::Copy(GridTradeAndOrder::m_st_Dealing.Volume ,cstr_Volume);	

					
					CMTStr::Copy(GridTradeAndOrder::m_st_Dealing.Price,cstrpl) ;

					CString cstr_Current_Rate=artists1.m_Current_Rate ;
					CMTStr::Copy(GridTradeAndOrder::m_st_Dealing.Current_Rate ,cstr_Current_Rate);

					CString cstr_PL=artists1.m_PL ;
					CMTStr::Copy(GridTradeAndOrder::m_st_Dealing.PL  ,cstr_PL);


					CString cstr_Status=artists1.m_Status ;
					CMTStr::Copy(GridTradeAndOrder::m_st_Dealing.Status,cstr_Status);


					CString cstr_Trade_Checked=artists1.m_Trade_Checked ;
					CMTStr::Copy(GridTradeAndOrder::m_st_Dealing.Trade_Checked,cstr_Trade_Checked);


					CString cstr_Checked_Time=artists1.m_Checked_Time ;
					CMTStr::Copy(GridTradeAndOrder::m_st_Dealing.Checked_Time,cstr_Checked_Time);


					CString cstr_Limit=artists1.m_Limit;
					CMTStr::Copy(GridTradeAndOrder::m_st_Dealing.Limit,cstr_Limit);


					CString cstr_Remark2=artists1.m_Remark2;
					CMTStr::Copy(GridTradeAndOrder::m_st_Dealing.Remark2,cstr_Remark2);
					

					GridTradeAndOrder::m_gridAndOrder_Array_Fill.Add(&GridTradeAndOrder::m_st_Dealing);
				 }
				 artists1.Close();				    									 			 				 
			 }


			 GridTradeAndOrder::gridAndOrder_mutex.Lock();	


			 //COLUMN VALUES FILTERATION
			  int val_type=0;	
				 val_type=0;
				 if (GridTradeAndOrder::insertFilterFlag==1 )
				 {
					 GridTradeAndOrder::m_gridAndOrder_Grid_array.Clear();
					 int noof_rowsInStruc=GridTradeAndOrder::m_gridAndOrder_Array_Fill.Total();
					for(int fcount=0;fcount<noof_rowsInStruc;fcount++)
					{
						GridTradeAndOrder::st_gridAndOrder m_st_Netposition={};
						m_st_Netposition=GridTradeAndOrder::m_gridAndOrder_Array_Fill[fcount];
						int flag=0;				
						CString col_row_val[13];		
						col_row_val[0]=m_st_Netposition.Symbol;
						if (GridTradeAndOrder::col0_val.Trim().GetLength()>0)
						{
							col_row_val[0]=col_row_val[0].Mid(0,GridTradeAndOrder::col0_val.Trim().GetLength());
						}
						col_row_val[1]=m_st_Netposition.Order;
						if (GridTradeAndOrder::col1_val.Trim().GetLength()>0)
						{
							col_row_val[1]=col_row_val[1].Mid(0,GridTradeAndOrder::col1_val.Trim().GetLength());
							col_row_val[1]=col_row_val[1].Mid(0,10);
						}
						col_row_val[2]=m_st_Netposition.Time ;
						if (GridTradeAndOrder::col2_val.Trim().GetLength()>0)
						{
							col_row_val[2]=col_row_val[2].Mid(0,GridTradeAndOrder::col2_val.Trim().GetLength());
						}
						
						col_row_val[3]=m_st_Netposition.Type ;
						if (GridTradeAndOrder::col3_val.Trim().GetLength()>0)
						{
							col_row_val[3]=col_row_val[3].Mid(0,GridTradeAndOrder::col3_val.Trim().GetLength());
						}

						col_row_val[4]=m_st_Netposition.Volume;
						if (GridTradeAndOrder::col4_val.Trim().GetLength()>0)
						{
							col_row_val[4]=col_row_val[4].Mid(0,GridTradeAndOrder::col4_val.Trim().GetLength());
						}

						col_row_val[5]=m_st_Netposition.Price;;
						boolean bool_col5=Check_numeric_col_filter(GridTradeAndOrder::col5_val,col_row_val[5]);

						col_row_val[6]=m_st_Netposition.Current_Rate;;
						boolean bool_col6=Check_numeric_col_filter(GridTradeAndOrder::col6_val,col_row_val[6]);

						col_row_val[7]=m_st_Netposition.PL;
						boolean bool_col7=Check_numeric_col_filter(GridTradeAndOrder::col7_val,col_row_val[7]);

						col_row_val[8]=m_st_Netposition.Status;
						if (GridTradeAndOrder::col8_val.Trim().GetLength()>0)
						{
							col_row_val[8]=col_row_val[8].Mid(0,GridTradeAndOrder::col8_val.Trim().GetLength());
						}

						col_row_val[9]=m_st_Netposition.Trade_Checked ;
						if (GridTradeAndOrder::col9_val.Trim().GetLength()>0)
						{
							col_row_val[9]=col_row_val[9].Mid(0,GridTradeAndOrder::col9_val.Trim().GetLength());
						}

						col_row_val[10]=m_st_Netposition.Checked_Time ;
						if (GridTradeAndOrder::col10_val.Trim().GetLength()>0)
						{
							col_row_val[10]=col_row_val[10].Mid(0,GridTradeAndOrder::col10_val.Trim().GetLength());
						}
						col_row_val[11]=m_st_Netposition.Limit ;
						if (GridTradeAndOrder::col11_val.Trim().GetLength()>0)
						{
							col_row_val[11]=col_row_val[11].Mid(0,GridTradeAndOrder::col11_val.Trim().GetLength());
						}
						col_row_val[12]=m_st_Netposition.Remark2;
						if (GridTradeAndOrder::col12_val.Trim().GetLength()>0)
						{
							col_row_val[12]=col_row_val[12].Mid(0,GridTradeAndOrder::col12_val.Trim().GetLength());
						}

						if((GridTradeAndOrder::col0_val.Trim()==col_row_val[0].Trim() || GridTradeAndOrder::col0_val.Trim()==L"ALL"||GridTradeAndOrder::col0_val.Trim()==L"") && (GridTradeAndOrder::col1_val.Trim()==col_row_val[1].Trim() || GridTradeAndOrder::col1_val.Trim()==L"ALL"||GridTradeAndOrder::col1_val.Trim()==L"") && (GridTradeAndOrder::col2_val.Trim()==col_row_val[2].Trim() || GridTradeAndOrder::col2_val.Trim()==L"ALL"||GridTradeAndOrder::col2_val.Trim()==L"")  && (GridTradeAndOrder::col3_val.Trim()==col_row_val[3].Trim() || GridTradeAndOrder::col3_val.Trim()==L"ALL"||GridTradeAndOrder::col3_val.Trim()==L"") && (GridTradeAndOrder::col4_val.Trim()==col_row_val[4].Trim() || GridTradeAndOrder::col4_val.Trim()==L"ALL"||GridTradeAndOrder::col4_val.Trim()==L"")   && (bool_col5==true || GridTradeAndOrder::col5_val.Trim()==L"ALL"||GridTradeAndOrder::col5_val.Trim()==L"")   && (bool_col6==true || GridTradeAndOrder::col6_val.Trim()==L"ALL"||GridTradeAndOrder::col6_val.Trim()==L"")   && (bool_col7==true || GridTradeAndOrder::col7_val.Trim()==L"ALL"||GridTradeAndOrder::col7_val.Trim()==L"")   && (GridTradeAndOrder::col8_val.Trim()==col_row_val[8].Trim() || GridTradeAndOrder::col8_val.Trim()==L"ALL"||GridTradeAndOrder::col8_val.Trim()==L"") && (GridTradeAndOrder::col9_val.Trim()==col_row_val[9].Trim() || GridTradeAndOrder::col9_val.Trim()==L"ALL"||GridTradeAndOrder::col9_val.Trim()==L"") &&(GridTradeAndOrder::col10_val==col_row_val[10] || GridTradeAndOrder::col10_val==L"ALL"||GridTradeAndOrder::col10_val==L"")&&(GridTradeAndOrder::col11_val==col_row_val[11] || GridTradeAndOrder::col11_val==L"ALL"||GridTradeAndOrder::col11_val==L"")&&(GridTradeAndOrder::col12_val==col_row_val[12] || GridTradeAndOrder::col12_val==L"ALL"||GridTradeAndOrder::col12_val==L""))
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Add(&m_st_Netposition);
						}
					}
				 }
				 else
				 {
					 GridTradeAndOrder::m_gridAndOrder_Grid_array.Assign(GridTradeAndOrder::m_gridAndOrder_Array_Fill);
				 }



//SORTING Colums values
	int t_rows=GridTradeAndOrder::m_gridAndOrder_Grid_array.Total();
	GridTradeAndOrder::st_gridAndOrder first_st={};
	GridTradeAndOrder::st_gridAndOrder next_st={};
	GridTradeAndOrder::st_gridAndOrder swap_st={};
	val_type=0;
	if (GridTradeAndOrder::col_click==4 || GridTradeAndOrder::col_click==5||GridTradeAndOrder::col_click==7 || GridTradeAndOrder::col_click==6)
	{
		val_type=1;
	}
	for (int i=0;i<t_rows;i++)
	{
		first_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
		for (int j=i+1;j<t_rows;j++)
		{
			next_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[j];
			if (GridTradeAndOrder::a_d==0)
			{
				if (val_type==0)
				{
					if (GridTradeAndOrder::col_click==0)
					{
						if (wcscmp(first_st.Symbol   ,next_st.Symbol)>0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Symbol ,swap_st.Symbol  );							
						}
					}
					if (GridTradeAndOrder::col_click==1)
					{
						if (wcscmp(first_st.Order   ,next_st.Order   )>0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Order   ,swap_st.Order  );							
						}
					}
					
					if (GridTradeAndOrder::col_click==2)
					{
						if (wcscmp(first_st.Time  ,next_st.Time  )>0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Time  ,swap_st.Time );							
						}
					}
					if (GridTradeAndOrder::col_click==3)
					{
						if (wcscmp(first_st.Type   ,next_st.Type   )>0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Type ,swap_st.Type  );							
						}
					}
					
					if (GridTradeAndOrder::col_click==8)
					{
						if (wcscmp(first_st.Status   ,next_st.Status   )>0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Status ,swap_st.Status  );							
						}
					}


					if (GridTradeAndOrder::col_click==9)
					{
						if (wcscmp(first_st.Trade_Checked   ,next_st.Trade_Checked  )>0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Trade_Checked ,swap_st.Trade_Checked );							
						}
					}
					
					if (GridTradeAndOrder::col_click==10)
					{
						if (wcscmp(first_st.Checked_Time  ,next_st.Checked_Time  )>0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Checked_Time,swap_st.Checked_Time );							
						}
					}
					if (GridTradeAndOrder::col_click==11)
					{
						if (wcscmp(first_st.Limit  ,next_st.Limit  )>0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Limit  ,swap_st.Limit );							
						}
					}


					if (GridTradeAndOrder::col_click==12)
					{
						if (wcscmp(first_st.Remark2   ,next_st.Remark2  )>0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Remark2   ,swap_st.Remark2 );							
						}
					}

				}	
				else
				{
					if (GridTradeAndOrder::col_click==4)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.Volume, &endPtr1);
						double val2=_tcstod(next_st.Volume, &endPtr1);
						if (val1>val2)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Volume  ,swap_st.Volume  );							
						}
					}
					if (GridTradeAndOrder::col_click==5)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.Price, &endPtr1);
						double val2=_tcstod(next_st.Price, &endPtr1);
						if (val1>val2)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Price ,swap_st.Price);							
						}
					}
					if (GridTradeAndOrder::col_click==6)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.Current_Rate, &endPtr1);
						double val2=_tcstod(next_st.Current_Rate, &endPtr1);
						if (val1>val2)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Current_Rate  ,swap_st.Current_Rate);							
						}

					}
					if (GridTradeAndOrder::col_click==7)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.PL, &endPtr1);
						double val2=_tcstod(next_st.PL, &endPtr1);
						if (val1>val2)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.PL ,swap_st.PL  );							
						}
					}
					
				}
			 }
			else
			{
				if (val_type==0)
				{

					if (GridTradeAndOrder::col_click==0)
					{
						if (wcscmp(first_st.Symbol   ,next_st.Symbol)<0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Symbol ,swap_st.Symbol  );							
						}
					}
					if (GridTradeAndOrder::col_click==1)
					{
						if (wcscmp(first_st.Order   ,next_st.Order)<0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Order   ,swap_st.Order  );							
						}
					}
					
					if (GridTradeAndOrder::col_click==2)
					{
						if (wcscmp(first_st.Time  ,next_st.Time  )<0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Time  ,swap_st.Time );							
						}
					}
					if (GridTradeAndOrder::col_click==3)
					{
						if (wcscmp(first_st.Type   ,next_st.Type )<0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Type ,swap_st.Type  );							
						}
					}
					
					if (GridTradeAndOrder::col_click==8)
					{
						if (wcscmp(first_st.Status   ,next_st.Status)<0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Status ,swap_st.Status  );							
						}
					}


					if (GridTradeAndOrder::col_click==9)
					{
						if (wcscmp(first_st.Trade_Checked   ,next_st.Trade_Checked  )<0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Trade_Checked ,swap_st.Trade_Checked );							
						}
					}
					
					if (GridTradeAndOrder::col_click==10)
					{
						if (wcscmp(first_st.Checked_Time  ,next_st.Checked_Time  )<0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Checked_Time,swap_st.Checked_Time );							
						}
					}
					if (GridTradeAndOrder::col_click==11)
					{
						if (wcscmp(first_st.Limit  ,next_st.Limit  )<0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Limit  ,swap_st.Limit );							
						}
					}


					if (GridTradeAndOrder::col_click==12)
					{
						if (wcscmp(first_st.Remark2   ,next_st.Remark2  )<0)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Remark2   ,swap_st.Remark2 );							
						}
					}

				}	
				else
				{
					if (GridTradeAndOrder::col_click==4)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.Volume, &endPtr1);
						double val2=_tcstod(next_st.Volume, &endPtr1);
						if (val1<val2)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Volume  ,swap_st.Volume  );							
						}
					}
					if (GridTradeAndOrder::col_click==5)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.Price, &endPtr1);
						double val2=_tcstod(next_st.Price, &endPtr1);
						if (val1<val2)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Price ,swap_st.Price);							
						}
					}
					if (GridTradeAndOrder::col_click==6)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.Current_Rate, &endPtr1);
						double val2=_tcstod(next_st.Current_Rate, &endPtr1);
						if (val1<val2)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.Current_Rate  ,swap_st.Current_Rate);							
						}

					}
					if (GridTradeAndOrder::col_click==7)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.PL, &endPtr1);
						double val2=_tcstod(next_st.PL, &endPtr1);
						if (val1<val2)
						{
							GridTradeAndOrder::m_gridAndOrder_Grid_array.Shift(j,i-j);
							swap_st=GridTradeAndOrder::m_gridAndOrder_Grid_array[i];
							CMTStr::Copy(first_st.PL ,swap_st.PL  );							
						}
					}
					
				}
				
			}
		}
	}


	        GridTradeAndOrder::gridAndOrder_mutex.Unlock();	
			}
		Sleep(10);
	  }

    session.Close();
	connection.Close();
	//m_logfile_g.LogEvent(L"End update_data_Trade");
    return 0;
}



LRESULT GridTradeAndOrder::GridRefresh(WPARAM wParam, LPARAM lParam)
{
	RedrawAll();
	return 0;
}

LRESULT GridTradeAndOrder::rownofind(WPARAM wParam, LPARAM lParam)
{
//m_logfile_g.LogEvent(L"Start rownofind");
CString m_symbol=L"";
if(OverViewOrderGrid::thred_kill==0)
  {
	for(int f=0;f<GetNumberRows();f++)
	{
		
		m_symbol=QuickGetText(0,f);
		if ( wcscmp(m_c_symbol,m_symbol)==0)
		{			
			value_row_no=f;
			return value_row_no;
		}
	}
	value_row_no=0;

	if (value_row_no==0)
	{
		for(int f=0;f<GetNumberRows();f++)
		{
			m_symbol=QuickGetText(0,f);
			if (wcscmp(m_symbol,L"")==0)
			{			
				value_row_no=f;
				return value_row_no;
			}
		}
	}

 }
//m_logfile_g.LogEvent(L"End rownofind");
  return value_row_no;
}



LRESULT GridTradeAndOrder::OnThreadMessage(WPARAM wParam, LPARAM lParam)
{
	//m_logfile_g.LogEvent(L"Start GridTradeOrder Onthreaad msg");
	HRESULT hr = S_OK;	
	int col= (int)wParam;
	int row= (int)lParam;
	
	if (GridTradeAndOrder::insertFilterFlag==0)
	{
		
		QuickSetText(col,row,GridTradeAndOrder::cellvalue);	
		/*if (GridTradeAndOrder::grid_populate_check==0)
		{*/
			CUGCell cell ;	
			/*GetColDefault( 12, &cell );			
			if (cell.GetCellType()!=UGCT_CHECKBOX )
			{
				QuickSetCellType(12,row,UGCT_CHECKBOX);	
				QuickSetCellTypeEx(12,row,UGCT_CHECKBOXCHECKMARK);
				SetColDefault( 12, &cell );
			}*/

			
			GetCell(11,0,&cell);
			if (cell.GetParam()!=CELLTYPE_IS_EDITABLE)
			{
				cell.SetParam(CELLTYPE_IS_EDITABLE);
			}
			GetCell(12,0,&cell);
			if (cell.GetParam()!=CELLTYPE_IS_EDITABLE)
			{
				cell.SetParam(CELLTYPE_IS_EDITABLE);
			}
		//}
	}
	else
	{
		QuickSetText(col,row+1,GridTradeAndOrder::cellvalue);	
			
		//RedrawCell(col,row+1);
	}
	//m_logfile_g.LogEvent(L"End GridTradeOrder Onthreaad msg");
	return 0;
	
}

LRESULT GridTradeAndOrder::GridRowCount(WPARAM wParam, LPARAM lParam)
{
	//RedrawAll();
	GridTradeAndOrder::Grid_Rows_Count=GetNumberRows();
	return 0;
}

LRESULT GridTradeAndOrder::RowDelete(WPARAM wParam, LPARAM lParam)
{
	//m_logfile_g.LogEvent(L"Start RowDelete");
	int row= (int)wParam;
	for(int f=0;f<13;f++)
	{
		QuickSetText(f,row,L"");
	}
	//m_logfile_g.LogEvent(L"End RowDelete");
	//DeleteRow(row);
	return 0;
}



LRESULT GridTradeAndOrder::OnThreadMessage_RowsNo(WPARAM wParam, LPARAM lParam)
{
	//m_logfile_g.LogEvent(L"Start OnThreadMessage_RowsNo");
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
		//m_logfile_g.LogEvent(L"End OnThreadMessage_RowsNo");
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
void GridTradeAndOrder::OnSheetSetup(int sheetNumber)
{
	//m_logfile_g.LogEvent(L"Start OnSheetSetup");
	int	nRow = 0, nCol = 0;
	// ****************************************************************
	// ** Set up columns
	// ****************************************************************
	CUGCell cell;

	GetGridDefault(&cell);
	//cell.SetBackColor(MY_COLOR_BACK);
	//cell.SetTextColor(MY_COLOR_TEXT);
	SetGridDefault(&cell);
	EnableExcelBorders(TRUE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetDefFont(0);
	SetSH_Width(0);
	
	// Number
			SetNumberCols(13);
			QuickSetText(0,-1,L"Symbol");
			SetColWidth(0,100);
			QuickSetText(1,-1,L"Order");
			SetColWidth(1,50);
			QuickSetText(2,-1,L"Time");	
			SetColWidth(2,140);
			
			QuickSetText(3,-1,L"Type");
			SetColWidth(3,60);
			
			QuickSetText(4,-1,L"Volume");
			SetColWidth(4,40);
			QuickSetText(5,-1,L"Price");	
			SetColWidth(5,60);
			QuickSetText(6,-1,L"LTP Price");
			SetColWidth(6,60);
			QuickSetText(7,-1,L"P&L");
			SetColWidth(7,70);
			
			QuickSetText(8,-1,L"Status");
			SetColWidth(8,60);		

			QuickSetText(9,-1,L"Checked Status");
			SetColWidth(9,80);		

			QuickSetText(10,-1,L"Checked Time");
			SetColWidth(10,130);

			QuickSetText(11,-1,L"Alloted Limit");
			SetColWidth(11,100);		

			QuickSetText(12,-1,L"Remark2");
			SetColWidth(12,100);		
			
	// Header font
	for(int i = 0; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}
//m_logfile_g.LogEvent(L"End OnSheetSetup");
}

		

void GridTradeAndOrder::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	//m_logfile_g.LogEvent(L"Start OnDClicked");
	

	//CDialog mySettings( IDD_TAB_DATA );
   //INT_PTR returnCode = -1;
   //returnCode = mySettings.DoModal();

   
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

	if(nParam == CELLTYPE_IS_EDITABLE || string == "CELLTYPE_IS_EDITABLE"||col==11||col==12)
	{
		StartEdit();
	}
	//m_logfile_g.LogEvent(L"End OnDClicked");
}	
			 

void GridTradeAndOrder::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{
	//m_logfile_g.LogEvent(L"Start OnTH_LClicked");
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);

    GridTradeAndOrder::col_click=col;
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
	
	RedrawAll();
	
//m_logfile_g.LogEvent(L"End OnTH_LClicked");
}
int GridTradeAndOrder::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{

	if(ID == UGCT_DROPLIST){
		return OnDropList(ID, col, row, msg, param);
	}
}
int GridTradeAndOrder::OnDropList(long ID,int col,long row,long msg,long param)
{
	
	//m_logfile_g.LogEvent(L"Start OnDropList");
	if (msg==103)
	{
		if(GridTradeAndOrder::insertFilterFlag==1 && row==0)
		{
			GridTradeAndOrder::filter_break=1;
			check_First==0;
			CString  strval=L"";
			CUGCell cell;
			GetCell(col,row,&cell);
			strval=cell.GetText();
			GridTradeAndOrder::strFilter="";

		}

		if(GridTradeAndOrder::insertFilterFlag==1 && row==0 )
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

	  }
	 RedrawAll();
	}
	//m_logfile_g.LogEvent(L"End OnDropList");
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

_bstr_t GridTradeAndOrder::get_string(CString  MainStr,CString SepStr)
{
	//m_logfile_g.LogEvent(L"Start get_string");
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


	//m_logfile_g.LogEvent(L"End  get_string");
	return b_strreturn;

}



int GridTradeAndOrder::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	//m_logfile_g.LogEvent(L"Start  OnEditFinish");
	if(GridTradeAndOrder::insertFilterFlag==1 && row==0)
	{
		GridTradeAndOrder::filter_break=1;
		check_First==0;
		CString  strval=L"";
		CUGCell cell;
		GetCell(col,row,&cell);
		strval=cell.GetText();
		GridTradeAndOrder::strFilter="";
		if (strval!=L"")
		{
			gridFilter(col,GetNumberRows(),strval);
		}
	}
	RedrawAll();

	//m_logfile_g.LogEvent(L"End  OnEditFinish");
	return true;
	
}



void GridTradeAndOrder::OnMenuCommand(int col,long row,int section,int item)
{
	//m_logfile_g.LogEvent(L"Start  OnMenuCommand");
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

	//m_logfile_g.LogEvent(L"End  OnMenuCommand");
}




int GridTradeAndOrder::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
{
	//m_logfile_g.LogEvent(L"Start  OnSortEvaluate");
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
	//m_logfile_g.LogEvent(L"End  OnSortEvaluate");
	return retVal;
}

/////////////////////////////////////////////////////////////////////////////
//	OnTabSelected
//		Called when the user selects one of the tabs on the bottom of the screen
//	Params:
//		ID	- id of selected tab
//	Return:
//		<none>
void GridTradeAndOrder::OnTabSelected(int ID)
{
	//m_logfile_g.LogEvent(L"Start  OnTabSelected");
	SetSheetNumber(ID);
	PostMessage(WM_SIZE, 0, 0L);
	//m_logfile_g.LogEvent(L"End  OnTabSelected");
}



void GridTradeAndOrder::OnSize(UINT nType, int cx, int cy)
{
	
	
}







void GridTradeAndOrder::OnTimer(UINT nIDEvent)
{	
	GridTradeAndOrder::gridAndOrder_mutex.Lock();

	
	int r_count=GridTradeAndOrder::m_gridAndOrder_Grid_array.Total();
	
	int grid_total=GetNumberRows();
	if (GridTradeAndOrder::insertFilterFlag==1)
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

	GridTradeAndOrder::gridAndOrder_mutex.Unlock();
}





 void GridTradeAndOrder::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();
	
	EnableMenu(TRUE);
	
	
	AddMenuItem( 2001, _T( "Filter" ) );
	AddMenuItem( 2000, _T( "Find Dialog" ) );
	
	
}

 int GridTradeAndOrder::OnMenuStart( int iCol, long lRow, int iSection )
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

 void GridTradeAndOrder::filter()
 {
	 //m_logfile_g.LogEvent(L"Start  filter");
	if (GridTradeAndOrder::insertFilterFlag==0)
	{
			addItemToCombobox();
			GridTradeAndOrder::insertFilterFlag=1;
			InsertRow(0);
			for (int col_count=0;col_count<13;col_count++)
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
		GridTradeAndOrder::insertFilterFlag=0;
		GridTradeAndOrder::strFilter=" ";

		GridTradeAndOrder::col0_val=L"";
		GridTradeAndOrder::col1_val=L"";
		GridTradeAndOrder::col2_val=L"";
		GridTradeAndOrder::col3_val=L"";
		GridTradeAndOrder::col4_val=L"";
		GridTradeAndOrder::col5_val=L"";
		GridTradeAndOrder::col6_val=L"";
		GridTradeAndOrder::col7_val=L"";
		GridTradeAndOrder::col8_val=L"";
		GridTradeAndOrder::col9_val=L"";
		GridTradeAndOrder::col10_val=L"";
		GridTradeAndOrder::col11_val=L"";
		GridTradeAndOrder::col12_val=L"";
	}
	RedrawAll();

	//m_logfile_g.LogEvent(L"End  filter");
 }



BOOLEAN  GridTradeAndOrder::CheckvalueInArray(const CStringArray& arr,CString strval) 
{
	//m_logfile_g.LogEvent(L"Start  CheckvalueInArray");
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
	//m_logfile_g.LogEvent(L"End  CheckvalueInArray");
    return false  ;
	}
	catch(_com_error & ce)
			{
				AfxMessageBox(ce.Description()+L"CheckvalueInArray");			
			} 
}
 
void GridTradeAndOrder::addItemToCombobox()
{
	//m_logfile_g.LogEvent(L"Start  CheckvalueInArray");
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
	try
	{
	int rows=1;
	
	
	CString str_val=L"";
	
	for (int forcount=0;forcount<12;forcount++)
	{
		str[forcount]=L"ALL\n";		
	}
	GridTradeAndOrder::gridAndOrder_mutex.Lock();	
	st_gridAndOrder_Array m_array_filter;
	m_array_filter.Assign(GridTradeAndOrder::m_gridAndOrder_Array_Fill);
	GridTradeAndOrder::gridAndOrder_mutex.Unlock();	

	rows=m_array_filter.Total();

	for (int forcount=0;forcount<rows;forcount++)
	{

		st_gridAndOrder m_st_for_filter={};
		m_st_for_filter=m_array_filter[forcount];


		for (int clocount=0;clocount<12;clocount++)
		{

			  if (clocount==0)
				{
					str_val=m_st_for_filter.Symbol;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr.Add(str_val);
					}
				}


				if (clocount==1)
				{
					str_val=m_st_for_filter.Order;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr1,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr1.Add(str_val);
					}
				}


				if (clocount==2)
				{
					str_val=m_st_for_filter.Time ;
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
					str_val=m_st_for_filter.Type;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr3,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr3.Add(str_val);
					}
				}

				if (clocount==4)
				{
					str_val=m_st_for_filter.Volume;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr4,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr4.Add(str_val);
					}
				}
				if (clocount==5)
				{
					str_val=m_st_for_filter.Price;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr5,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr5.Add(str_val);
					}
				}
				if (clocount==6)
				{
					str_val=m_st_for_filter.Current_Rate;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr6,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr6.Add(str_val);
					}
				}
				if (clocount==7)
				{
					
					str_val=m_st_for_filter.PL;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr7,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr7.Add(str_val);
					}
				}
				if (clocount==8)
				{
					str_val=m_st_for_filter.Status;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr8,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr8.Add(str_val);
					}
				}
				if (clocount==9)
				{
					str_val=m_st_for_filter.Trade_Checked;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr9,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr9.Add(str_val);
					}
				}
				if (clocount==10)
				{
					str_val=m_st_for_filter.Checked_Time;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr10,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr10.Add(str_val);
					}
				}
				if (clocount==11)
				{
					str_val=m_st_for_filter.Limit;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr11,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr11.Add(str_val);
					}
				}
				if (clocount==12)
				{
					str_val=m_st_for_filter.Remark2;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr12,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr12.Add(str_val);
					}
				}
				
			

		}												
	}
	}
	catch(_com_error & ce)
			{
				AfxMessageBox(ce.Description()+L"addItemToCombobox");			

	} 

	//m_logfile_g.LogEvent(L"End  CheckvalueInArray");
}
 


void GridTradeAndOrder::OnSetup()
{
	//m_logfile_g.LogEvent(L"Start  OnSetup()");
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
	
	 // Start timers
	//srand( (unsigned)time( NULL ) );
	SetTimer(0, 100, NULL);
	SetTimer(1, 100, NULL);

	

	QuickSetCellType( 0, -1, m_iArrowIndex );
	SortBy( 0, UG_SORT_ASCENDING );

	m_iSortCol = 0;
	m_bSortedAscending = TRUE;



	m_pThreads=AfxBeginThread(update_data_Trade, this);	
	m_pThreads->m_bAutoDelete=false;
	//m_SocketThred=AfxBeginThread(update_data_Order, this);		

	run_check=0;		
	//m_logfile_g.LogEvent(L"End  OnSetup()");
}

void GridTradeAndOrder::gridFilter(int colno,int rows_count,CString col_value)
{
	//m_logfile_g.LogEvent(L"Start gridFilter");
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
	//m_logfile_g.LogEvent(L"End gridFilter");
}

int GridTradeAndOrder::OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow)
{
	//m_logfile_g.LogEvent(L"Start OnCanViewMove");
	UNREFERENCED_PARAMETER(oldcol);
	UNREFERENCED_PARAMETER(oldrow);
	UNREFERENCED_PARAMETER(newcol);
	UNREFERENCED_PARAMETER(newrow);
	//m_logfile_g.LogEvent(L"End  OnCanViewMove");
	return TRUE;
}

void GridTradeAndOrder::OnGetCell(int col,long row,CUGCell *cell)
{		
		//m_logfile_g.LogEvent(L"Start OnGetCell");
	    st_gridAndOrder mst_grid={};
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
			if (GridTradeAndOrder::insertFilterFlag==1)
			{
				rows_no=row-1;				
				if (row==0)
				{
					return;
				}
			}
			if (col==0)
			{				
				mst_grid=GridTradeAndOrder::m_gridAndOrder_Grid_array[rows_no];				
				CString tmp=mst_grid.Symbol ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==1)
			{
				
				mst_grid=GridTradeAndOrder::m_gridAndOrder_Grid_array[rows_no];
				CString tmp=mst_grid.Order ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==2)
			{				
				mst_grid=GridTradeAndOrder::m_gridAndOrder_Grid_array[rows_no];
				UINT64 m_time=_wtoi( mst_grid.Time);
				CString tmp=L"";
				CMTStr256 str_time;
				SMTFormat::FormatDateTime(str_time,m_time,true,true);
				tmp=str_time.Str();
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==3)
			{			
				mst_grid=GridTradeAndOrder::m_gridAndOrder_Grid_array[rows_no];
				CString tmp=mst_grid.Type ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==4)
			{				
				mst_grid=GridTradeAndOrder::m_gridAndOrder_Grid_array[rows_no];
				CString tmp=mst_grid.Volume ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==5)
			{				
				mst_grid=GridTradeAndOrder::m_gridAndOrder_Grid_array[rows_no];
				CString tmp=mst_grid.Price;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==6)
			{	
				mst_grid=GridTradeAndOrder::m_gridAndOrder_Grid_array[rows_no];
				CString tmp=mst_grid.Current_Rate  ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==7)
			{				
				mst_grid=GridTradeAndOrder::m_gridAndOrder_Grid_array[rows_no];
				CString tmp=mst_grid.PL  ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				
			    }
			}
			else if (col==8)
			{	
				
				mst_grid=GridTradeAndOrder::m_gridAndOrder_Grid_array[rows_no];
				CString tmp=mst_grid.Status;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==9)
			{	
				
				mst_grid=GridTradeAndOrder::m_gridAndOrder_Grid_array[rows_no];
				CString tmp=mst_grid.Trade_Checked;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==10)
			{	
				
				mst_grid=GridTradeAndOrder::m_gridAndOrder_Grid_array[rows_no];
				CString tmp=mst_grid.Checked_Time;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==11)
			{	
				
				mst_grid=GridTradeAndOrder::m_gridAndOrder_Grid_array[rows_no];
				CString tmp=mst_grid.Limit;
															
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==12)
			{	
				mst_grid=GridTradeAndOrder::m_gridAndOrder_Grid_array[rows_no];
				CString tmp=mst_grid.Remark2;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
		    }
	   }
	   
}
