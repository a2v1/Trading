#include "stdafx.h"
#include "TradingSDI.h"
#include "overview.h"
#include "afxdialogex.h"
#include "LimitMappingScripwise.h"
#include "overviewordergrid.h"
#include "tabControl.h"
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace rename("EOF", "EndOfFile")
#define MY_THREAD_UPDATE				WM_APP+200

int overview::chcekinitialize=0;
CString overview::total_trade=L"";
CString overview::last_trade_time=L"";
CString overview::trade_per=L"";
CString overview::balance=L"";
CString overview::profit=L"";
CString overview::Margin=L"";
CDataSource overview::connection;
CSession overview::session;
CCommand<CAccessor<CTrade_Table> > overview::artists1;



extern HRESULT hrn;
extern CDataSource connection_update;
extern CSession session_update;	


// overview dialog

IMPLEMENT_DYNAMIC(overview, CDialogEx)

overview::overview(CWnd* pParent /*=NULL*/)
	: CDialogEx(overview::IDD, pParent)
{
	checked_val=0;
	OverViewOrderGrid::thred_kill=0;

}

overview::~overview()
{
	OverViewOrderGrid::thred_kill=1;

	try 
	{			
	
	DWORD exit_code= NULL;
	if (m_pThreads != NULL)
	{
	if(WaitForSingleObject(m_pThreads->m_hThread,INFINITE) == WAIT_OBJECT_0) 
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
	/* Tradegrid.~GridTradeAndOrder();
	 Ordergrid.~OverViewOrderGrid();*/

}
LRESULT overview::UpdateData(WPARAM wParam, LPARAM lParam)
{
	m_nooftrade.SetWindowTextW(total_trade);
	m_lasttrade.SetWindowTextW(last_trade_time);
	m_percentageoftrade.SetWindowTextW(trade_per);

	m_txtProfit.SetWindowTextW(profit);
	m_txtBalance.SetWindowTextW(balance);
	m_txtMargin.SetWindowTextW(Margin);
	
	return 0;
}


void overview::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, m_accountnumber);
	DDX_Control(pDX, IDC_EDIT2, m_accountname);
	DDX_Control(pDX, IDC_EDIT1, m_masteraccount);
	DDX_Control(pDX, IDC_EDIT4, m_history);
	DDX_Control(pDX, IDC_EDIT6, m_nooftrade);
	DDX_Control(pDX, IDC_EDIT5, m_lasttrade);
	DDX_Control(pDX, IDC_EDIT7, m_percentageoftrade);
	DDX_Control(pDX, IDC_EDIT15, m_txtProfit);
	DDX_Control(pDX, IDC_EDIT14, m_txtBalance);
	DDX_Control(pDX, IDC_EDIT13, m_txtMargin);
	DDX_Control(pDX, IDC_EDIT10, m_txtGroup1);
	DDX_Control(pDX, IDC_EDIT11, m_txtGroup2);
	DDX_Control(pDX, IDC_EDIT12, m_txtGroup3);
	DDX_Control(pDX, IDC_EDIT9, m_txtGroup4);
	DDX_Control(pDX, IDC_EDIT8, m_txtCredit);
	DDX_Control(pDX, IDC_CHECK1, m_ignoreclient);
	DDX_Control(pDX, IDC_CHECK2, m_commentwise);
}


BEGIN_MESSAGE_MAP(overview, CDialogEx)
	ON_MESSAGE(MY_THREAD_UPDATE,UpdateData)
	ON_BN_CLICKED(IDC_CHECK1, &overview::OnBnClickedCheck1)
	ON_COMMAND(IDCLOSE, &overview::OnIdclose)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &overview::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &overview::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &overview::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_CHECK2, &overview::OnBnClickedCheck2)
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_STATIC_FrGrid_Trade2, &overview::OnStnClickedStaticFrgridTrade2)
END_MESSAGE_MAP()

// overview message handlers
void overview::get_client_details()
{
	CoInitialize(NULL);	
	CCommand<CAccessor<CTrade_Table> > artists1;				
	_bstr_t strCommand="";	
	CString sel_login=GridTradeAndOrder::m_selected_login;
	sel_login=sel_login.Mid(0,6);
	_bstr_t strcode=sel_login;
	HRESULT hr;


	CDataSource connection;
	CSession session;
	

	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	if(SUCCEEDED(hr))
	{
	hr=session.Open(connection);
	}


	strCommand="select isnull(Comment_YN,'N') as 'Comment_YN',isnull(Ignore_YN,'N') as 'Ignore_YN',isnull(Client_group,'') as 'Client_group',isnull(Client_Group1,'') as 'Client_Group1',isnull(Client_Group2,'') as 'Client_Group2',isnull(Client_Group4,'') as 'v',isnull(Client_Credit,'0') as 'ba','' as  'TYPE','' as  'volume' ,'' AS 'cHECKtRADE'from client where v_login='" + GridTradeAndOrder::m_selected_login + "' ";		
	char* strCommand_char=(char*)strCommand;
	if(SUCCEEDED(hr))
	{
		hr=artists1.Open(session,strCommand_char);	
	}
	if(SUCCEEDED(hr))
	{
	while (artists1.MoveNext() == S_OK)
	{		
		if (_tcscmp(artists1.m_Symbol,_T("N"))==0 )
		{
			m_ignoreclient.SetCheck(0);
		}
		else
		{
			m_ignoreclient.SetCheck(1);
		}
		if (_tcscmp(artists1.m_Order,_T("N"))==0 )
		{
			m_commentwise.SetCheck(0);
		}
		else
		{
			m_commentwise.SetCheck(1);
		}						
		m_txtGroup1.SetWindowTextW(artists1.m_Time);
		m_txtGroup2.SetWindowTextW(artists1.m_Type);
		m_txtGroup3.SetWindowTextW(artists1.m_Volume);	
		m_txtGroup4.SetWindowTextW(artists1.m_Price);		
		m_txtCredit.SetWindowTextW(artists1.m_Current_Rate) ;
	}

    }
	artists1.Close();	
	
	
}

UINT update_Label(void*);
UINT update_Label(void *pParam)
{
	overview* pThis= (overview*)pParam;	
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<CTrade_Table> > artists1;	

	connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	
	session.Open(connection);
	HRESULT hr;
	while (OverViewOrderGrid::thred_kill==0 )
	{	
		
		Sleep(100);
		_bstr_t strCommand="";	
		CString sel_login=GridTradeAndOrder::m_selected_login;
		sel_login=sel_login.Mid(0,6);
		_bstr_t strcode=sel_login;
		strCommand="select sum(volume/10000),max([time]),(cast(sum(volume/10000) as float)/cast((select sum(volume/10000) from Deal_Table_Accounting where [action]in (0,1) and [login]='" + strcode + "' ) as float))*100 ,'' as  'TYPE','' as  'volume', '' as Price,'' as Current_rate,''  as 'PL',''   as 'Status',''   as 'TradeStatus' from Deal_Table_Accounting where [action]in (0,1)  and [login]='" + GridTradeAndOrder::m_selected_login + "' ";
		
		char* strCommand_char=(char*)strCommand;
		hr=artists1.Open(session,strCommand_char);	
		if(SUCCEEDED(hr))
		{
		while (artists1.MoveNext() == S_OK)
		{
			overview::total_trade=artists1.m_Symbol ;
			overview::last_trade_time=artists1.m_Order ;
			overview::trade_per=artists1.m_Time ;
		}
		}
		artists1.Close();
		overview::balance=L"0";
		strCommand="select isnull(sum(Balance),0),'' as 'v','' as 'ba','' as  'TYPE','' as  'volume', '' as Price,'' as Current_rate,''  as 'PL',''   as 'Status',''   as 'TradeStatus' from BalanceTableAccounting where  [login]='" + GridTradeAndOrder::m_selected_login + "' ";		
		strCommand_char=(char*)strCommand;
		hr=artists1.Open(session,strCommand_char);				
		if(SUCCEEDED(hr))
		{
		while (artists1.MoveNext() == S_OK)
		{
			LPTSTR endPtr;
			double d_m_PL = _tcstod(artists1.m_Symbol, &endPtr);												
			CString cstrpl;
			cstrpl.Format(_T("%.0f"),d_m_PL);															
			overview::balance=cstrpl;									
		}
		}
		artists1.Close();


		overview::profit=L"0";
		strCommand="select isnull(sum(PL),0),'' as 'v','' as 'ba','' as  'TYPE','' as  'volume', '' as Price,'' as Current_rate,''  as 'PL',''   as 'Status',''   as 'TradeStatus'  from (SELECT vt1.symbol,'' as 'order',vt3.lastTime,'' as 'TYPE',vt1.netqty as 'VOLUME',vt1.avgrate as 'Price',vt2.last_tick as 'CURRENT_RATE' ,case when vt1.netqty<0 then (isnull(vt2.last_tick,0)-vt1.avgrate)*vt1.netqty*vt1.Multiplayer when vt1.netqty>0 then (isnull(vt2.last_tick,0)-vt1.avgrate)*vt1.netqty*vt1.Multiplayer else 0  end as 'PL',vt3.[status] from  (select PositionAverageAccounting.Symbol,PositionAverageAccounting.multiplayer,totalvolume/10000 as 'NetQty', wavgprice as 'AVGRate' from PositionAverageAccounting where  PositionAverageAccounting.[login]='" + GridTradeAndOrder::m_selected_login + "'  and totalvolume<>0    )vt1 left outer join (select t1.symbol,last_tick.last_tick from tradedatabase.dbo.last_tick left outer join tradedatabase.dbo.symbol_mapping as t1 on t1.mapping_Symbol=tradedatabase.dbo.last_tick.symbol) vt2 on vt1.symbol=vt2.symbol left outer join (select t1.symbol,t1.LastTime,t1.Last_Deal,case when ([type]=0 or [type]=1) then 'MARKET' else 'LIMIT' end  as 'STATUS' from (select symbol,max([time]) 'LastTime',max([order])  as 'Last_Deal' from  Deal_Table_Accounting where  Deal_Table_Accounting.[login]='" + GridTradeAndOrder::m_selected_login + "'   group by Deal_Table_Accounting.Symbol ) t1 left outer join tradedatabase.dbo.mt5_orders_history on t1.last_deal=tradedatabase.dbo.mt5_orders_history.[order])vt3 on vt1.symbol=vt3.symbol) vt6";
		strCommand_char=(char*)strCommand;
		hr=artists1.Open(session,strCommand_char);				
		if(SUCCEEDED(hr))
		{
		while (artists1.MoveNext() == S_OK)
		{
			LPTSTR endPtr;
			double d_m_PL = _tcstod(artists1.m_Symbol, &endPtr);												
			CString cstrpl;
			cstrpl.Format(_T("%.0f"),d_m_PL);															
			overview::profit=cstrpl;			
		}
		}
		artists1.Close();
								
		double v1 = _tstof((LPCTSTR)overview::balance);
		double v2 = _tstof((LPCTSTR)overview::profit);
		double v1v2= v1+v2;
		
		overview::Margin.Format(_T("%.0f"), v1v2);
		if (OverViewOrderGrid::thred_kill!=1)
		{
			pThis->SendMessage(MY_THREAD_UPDATE, 1,1);			 		 		
		}
	 }
	 return 0;
	}




void overview::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here

}


void overview::OnBnClickedButton1()
{
	LimitMappingScripwise dlg;
	dlg.DoModal();
}


void overview::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	HRESULT hr_update;
	CDataSource connection_update;
	CSession session_update;	
	CCommand<CNoAccessor, CNoRowset> cmd_update;

	CoInitialize(NULL );
	hr_update=connection_update.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");	
	if(SUCCEEDED(hr_update))
	{
		hr_update=session_update.Open(connection_update);							
	}
	else
	{
		AfxMessageBox(L"connection.OpenFromInitializationString Failed");
	}


	 int check_data=0;
	 _bstr_t jasonStr="";
	 _variant_t  strUpdate_time="";
	 _bstr_t r_time="";	 

	 int rows_no=Tradegrid.GetNumberRows();
	 _bstr_t  InsertAndUpdate_Command=" ";
	 _bstr_t  str_deal=" ";
	 _bstr_t  str_out_comment=" ";
	 _bstr_t  str_checked=" ";
	 _bstr_t  str_new=" ";
	 _bstr_t str_symbol="";
	 _bstr_t str_Limit="";


	 _bstr_t  str_checked_Time=" ";
	 _bstr_t  str_Remark1=" ";
	 _bstr_t str_Remark2="";
	 _bstr_t str_Limit2="";
	 _bstr_t str_NewLimit="";
	 int check_flag=0;
	 for (int forcount=0;forcount<rows_no;forcount++)
	 {		 		 		 
		str_symbol=Tradegrid.QuickGetText(0,forcount);		 		
		str_checked_Time=Tradegrid.QuickGetText(10,forcount);		 
		str_Remark1=Tradegrid.QuickGetText(11,forcount);		 
		str_Remark2=Tradegrid.QuickGetText(12,forcount);		 
		if (Tradegrid.QuickGetText(11,forcount)!=NULL )
		{
			str_Limit =Tradegrid.QuickGetText(11,forcount);		 
			CString str1=str_Limit;
			CString strchar=L"";
			_bstr_t bstrchar="";
			str_Limit2="";
			str_NewLimit="";
			check_flag=0;
			int strlen=str1.GetLength();
			for (int forcount=0;forcount<strlen;forcount++)
			{
				strchar=str1.Mid(forcount,1);
				bstrchar=strchar;
				if (strchar!="/")
				{
					if (check_flag==0)
					{
						str_NewLimit=str_NewLimit+bstrchar;
					}
					else
					{
						str_Limit2=str_Limit2+bstrchar;
					}
				}
				else
				{
					check_flag=1;
				}
			}
		}
		else
		{
			str_Limit="0";
			str_Limit2="0";
		}
		if(Tradegrid.QuickGetText(0,forcount)!=NULL )
		{
			str_new= " exec Proc_Position_Check_1 '" + GridTradeAndOrder::m_selected_login + "','" + str_symbol + "','" + str_checked_Time  + "','" + str_Remark1  + "','" + str_Remark2 + "'; ";
		 InsertAndUpdate_Command=str_new +InsertAndUpdate_Command ;
		}
		if (Tradegrid.QuickGetText(11,forcount)!=NULL )
		{
		 str_new= " exec Update_Limit '" + GridTradeAndOrder::m_selected_login + "','" + str_symbol + "','" + str_NewLimit + "','" + str_Limit2 + "'; ";
		 InsertAndUpdate_Command=str_new +InsertAndUpdate_Command ;
		}
		 
		 
	 }
	 char* strCommand_char=(char*)InsertAndUpdate_Command;
	 hr_update=cmd_update.Open(session_update,strCommand_char);							 			 		 				 	
	 cmd_update.Close();
	 session_update.Close();
	 
	 CoUninitialize();
}


BOOL overview::OnInitDialog()
{
	CDialogEx::OnInitDialog();	
	CString strcode=GridTradeAndOrder::m_selected_login;
	CString strname=GridTradeAndOrder::m_selected_Name;
	CString Codeandname=L"";
	Codeandname.Format(L"                                                   %s:-%s",strcode,strname);
	SetWindowTextW(Codeandname);
	//
 // // TODO: Add extra initialization h
	/*CRect rectDummy;
	RECT  rect={100,100,100,100};*/
	//
  	 Tradegrid.AttachGrid(this,IDC_STATIC_FrGrid_Trade2);
	 Ordergrid.AttachGrid(this,IDC_STATIC_FrGrid_Order2);
	

	get_client_details();

	CString sel_login=GridTradeAndOrder::m_selected_login;
	m_accountnumber.SetWindowTextW(GridTradeAndOrder::m_selected_login);
	m_accountname.SetWindowTextW(GridTradeAndOrder::m_selected_Name);
	m_masteraccount.SetWindowTextW(sel_login.Mid(0,6));
	m_pThreads=AfxBeginThread(update_Label, this);		
	m_pThreads->m_bAutoDelete=false;

	return TRUE;  // return TRUE unless you set the focus to a control

	
}
void overview::OnIdclose()
{
	
	OverViewOrderGrid::thred_kill=1;
	
	
}



void overview::OnClose()
{
	OverViewOrderGrid::thred_kill=1;
	
	CDialog::OnClose();
}



void overview::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	
		_bstr_t valField1("");
		_bstr_t valField2("");
		_bstr_t cmd("");
		CString  strsqlcommand;				 	
		
		HRESULT hr_update;
		CDataSource connection_update;
		CSession session_update;	
		CCommand<CNoAccessor, CNoRowset> cmd_update;
		
		CoInitialize(NULL );
		hr_update=connection_update.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");	
		if(SUCCEEDED(hr_update))
		{
			hr_update=session_update.Open(connection_update);							
		}
		else
		{
			AfxMessageBox(L"connection.OpenFromInitializationString Failed");
		}


		
	  _bstr_t check1="";
	  _bstr_t check2="";
	  _bstr_t group1="";
	  _bstr_t group2="";
	  _bstr_t group3="";
	  _bstr_t group4="";
	  _bstr_t credit ="";

	  _bstr_t b_name ="";

	  CString str_group1;
	  CString str_group2;
	  CString str_group3;
	  CString str_group4;
	  CString str_credit;

	  CString str_name=L"";

	 
	if(m_ignoreclient.GetCheck()==0)
	{
		check1="N";
	}
	else
	{
		check1="Y";
	}
	 if(m_commentwise.GetCheck()==0)
	{
		check2="N";
	}
	else
	{
		check2="Y";
	}	 		
	 						
	 m_txtGroup1.GetWindowTextW(str_group1);
	 m_txtGroup2.GetWindowTextW(str_group2);
	 m_txtGroup3.GetWindowTextW(str_group3);			
	 m_txtGroup4.GetWindowTextW(str_group4);			
	 m_txtCredit.GetWindowTextW(str_credit);			
	 m_accountname.GetWindowTextW(str_name);			
	 if (str_credit.Trim()==L"")
	 {
		 str_credit=L"0";
	 }
	 group1=str_group1;
	 group2=str_group2;
	 group3=str_group3;
	 group4=str_group4;
	 credit=str_credit;
	 b_name=str_name;
	 
	cmd=" update client set    v_name='" + b_name + "', Comment_YN='" + check1 + "',Ignore_YN='" + check2 + "',client_group='" + group1 + "',Client_Group1='" + group2 + "',Client_Group2='" + group3 + "',Client_Group4='" + group4 + "',Client_Credit='" +  credit + "' where v_login='" + GridTradeAndOrder::m_selected_login + "'";
	
	 char* strCommand_char=(char*)cmd;
	 hr_update=cmd_update.Open(session_update,strCommand_char);							 			 		 				 	
	 
	 cmd_update.Close();
	 session_update.Close();
	 CoUninitialize();
	AfxMessageBox(L"Data Updated");

}


void overview::OnBnClickedCheck2()
{
	// TODO: Add your control notification handler code here
}


void overview::OnTimer(UINT_PTR nIDEvent)
{
	
	/*double v1 = _tstof((LPCTSTR)overview::balance);
	double v2 = _tstof((LPCTSTR)overview::profit);
	double v1v2= v1+v2;
	overview::Margin.Format(_T("%.0f"), v1v2);

	if (OverViewOrderGrid::thred_kill!=1)
	{
		m_nooftrade.SetWindowTextW(total_trade);
		m_lasttrade.SetWindowTextW(last_trade_time);
		m_percentageoftrade.SetWindowTextW(trade_per);

		m_txtProfit.SetWindowTextW(profit);
		m_txtBalance.SetWindowTextW(balance);
		m_txtMargin.SetWindowTextW(overview::Margin);
	}*/

	CDialogEx::OnTimer(nIDEvent);
}


void overview::OnStnClickedStaticFrgridTrade2()
{
	// TODO: Add your control notification handler code here
}
