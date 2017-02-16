// LTP_Dilog.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "LTP_Dilog.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include <afxdisp.h>
#include "LTPupdate.h"
#include "Login.h"
// LTP_Dilog dialog

#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace rename("EOF", "EndOfFile")
IMPLEMENT_DYNAMIC(LTP_Dilog, CDialogEx)

LTP_Dilog::LTP_Dilog(CWnd* pParent /*=NULL*/)
	: CDialogEx(LTP_Dilog::IDD, pParent)
{

}

LTP_Dilog::~LTP_Dilog()
{
}

void LTP_Dilog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LTP_Dilog, CDialogEx)
	ON_STN_CLICKED(IDC_STATIC_LTP, &LTP_Dilog::OnStnClickedStaticLtp)
	
	ON_BN_CLICKED(IDOK, &LTP_Dilog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &LTP_Dilog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &LTP_Dilog::OnBnClickedButton4)
END_MESSAGE_MAP()
// LTP_Dilog message handlers


BOOL LTP_Dilog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ltp_grid.AttachGrid(this ,IDC_STATIC_LTP);


	ltp_grid.SetColWidth(0,80);
	ltp_grid.SetColWidth(1,112);
	ltp_grid.SetColWidth(2,117);
	ltp_grid.QuickSetText(0,-1,L"SYMBOL");
	ltp_grid.QuickSetText(1,-1,L"MAPPING SYMBOL");
	ltp_grid.QuickSetText(2,-1,L"LAST TICK");

	ltp_grid.GetData();

     return TRUE;
	// EXCEPTION: OCX Property Pages should return FALSE
}


void LTP_Dilog::OnStnClickedStaticLtp()
{
	// TODO: Add your control notification handler code here
}






void LTP_Dilog::OnBnClickedOk()
{
	
		_bstr_t valField1("");
		_bstr_t valField2("");
		_bstr_t valField3("");
		_bstr_t cmd("");
		CString  strsqlcommand;				 	
		HRESULT hr = S_OK;		 
			 
		CoInitialize(NULL);
          // Define string variables.		 
		_bstr_t strCnn("Provider=SQLOLEDB;SERVER=68.168.104.26;Database=tradedatabase;uid=sa;pwd=ok@12345;");
		
        _RecordsetPtr pRstAuthors = NULL;
 
      // Call Create instance to instantiate the Record set
      hr = pRstAuthors.CreateInstance(__uuidof(Recordset)); 
	 
	int noofrows=ltp_grid.GetNumberRows();
	for (int f_count=0;f_count<noofrows;f_count++)
	{
		CString strf=ltp_grid.QuickGetText(1,f_count);
		valField2=ltp_grid.QuickGetText(1,f_count);
		valField3=ltp_grid.QuickGetText(2,f_count);

		if (strf.Trim().GetLength()>0)
		{
			cmd=cmd+" delete from last_tick where symbol='" + valField2 + "';  insert into LAST_TICK(symbol,last_tick) values('" + valField2 + "','" + valField3 + "') ;";
		}
	}		
	pRstAuthors->Open(cmd,strCnn, adOpenStatic,adLockReadOnly,adCmdText);    			

	AfxMessageBox(L"LTP has been updated");
	
}


void LTP_Dilog::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	int noofrows=ltp_grid.GetNumberRows();
	for (int f_count=0;f_count<noofrows;f_count++)
	{
		CString strf=ltp_grid.QuickGetText(0,f_count);
		strf=strf.Trim();
		MTTickShort  tick;
		DlgHelp::m_dealer->m_manager->TickLast(strf,tick);
		CString strtlasttick=L"";
		strtlasttick.Format(L"%.4f",tick.ask );
		ltp_grid.QuickSetText (2,f_count,strtlasttick);
		
	}
	ltp_grid.RedrawAll();
}


void LTP_Dilog::OnBnClickedButton4()
{
	if(CDealer::admin_login!=1)
	{
		AfxMessageBox(L"You Are not a valid user");
		return ;
	}


	int noofrows=ltp_grid.GetNumberRows();
	for (int f_count=0;f_count<noofrows;f_count++)
	{
		CString strf=ltp_grid.QuickGetText(0,f_count);
		CString str_closingrate=ltp_grid.QuickGetText(2,f_count);

		strf=strf.Trim();
		MTTickShort  tick;
		
		DlgHelp::m_dealer->m_manager->TickLast(strf,tick);
		tick.datetime=0;

		LPTSTR endPtr1;										
		double Closing_rate=_tcstod(str_closingrate ,&endPtr1);
		tick.ask=Closing_rate;
		tick.bid=Closing_rate;
		tick.last=Closing_rate;

		MTTickShort  newtick[1]={};
		newtick[0]=tick;
		
		MTAPIRES res;
		res=DlgHelp::m_dealer->m_admin->TickAdd(strf,newtick,1);
	}
	AfxMessageBox(L"Closing Rate has been updated");
}
