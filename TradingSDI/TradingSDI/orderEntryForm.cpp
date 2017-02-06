
// TradingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "orderEntryForm.h"
#include "MainFrm.h"
#include "Login.h"
#include "DealerSink.h"
#define MT5_TIMEOUT_CONNECT   30000
#define MT5_TIMEOUT_DEALER    10000

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int orderEntryForm::checkOrderForm=0;
CString orderEntryForm::strqty=L"";
CString orderEntryForm::strSymbolcmb=L"";

IMTManagerAPI* orderEntryForm::manager     =NULL;
CMTManagerAPIFactory orderEntryForm::factory;

   IMTRequest *m_request;
   IMTRequest *m_result ;
   IMTConfirm *m_confirm;   
   UINT        id=0;
   CDealer sink;   
   MTAPISTR              strapi;
   CString strStatus[36]={L"Request is on the way.",L"Request accepted.",L"Request processed.",L"Requote in response to the request.",L"Prices in response to the request.",L"Request rejected",L"Request canceled",L"An order placed as a result of the request",L"Request fulfilled",L"Request partially fulfilled",L"Common error of request",L"Request timed out",L"Invalid request",L"Invalid volume",L"Invalid price",L"Wrong stop levels or price",L"Trade is disabled",L"Market is closed",L"Not enough money",L"Price has changed",L"No price",L"Invalid order expiration",L"Order has been changed",L"Too many trade requests",L"Request does not contain changes",L"Autotrading disabled on the server",L"Autotrading disabled on the client side",L"Request blocked by the dealer",L"Modification failed due to order or position being close to market",L"Fill mode is not supported",L"No connection",L"Allowed only for real accounts",L"Reached the limit on the number of orders",L"Reached the volume limit",L"Invalid or prohibited order type",L"Position is already closed. For example, this error appears when attempting to modify the stop levels of an already closed position"};
orderEntryForm::orderEntryForm()
{
	
}

void orderEntryForm::OnClose()
{	
	orderEntryForm::checkOrderForm=0;	
	CDialog::OnCancel();
}
void orderEntryForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cmbSymbol);
	DDX_Control(pDX, IDC_COMBO2, m_cmbSymbolType);
	DDX_Control(pDX, IDC_COMBO3, m_cmbOrderType);
	DDX_Control(pDX, IDC_EDIT1, m_Volume);
	DDX_Control(pDX, IDC_EDIT2, m_Price);
	DDX_Control(pDX, IDC_STATIC_PRICE, m_LbPrice);
	DDX_Control(pDX, IDC_STATIC_PRICE2, m_LbStatus);	
	DDX_Control(pDX, IDC_BUTTON1, m_BtnPlace);	

	
}

BEGIN_MESSAGE_MAP(orderEntryForm, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()		
	
	ON_BN_CLICKED(IDC_BUTTON1, &orderEntryForm::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &orderEntryForm::OnCbnSelchangeCombo3)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO1, &orderEntryForm::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()




inline bool orderEntryForm::Initialize(IMTRequest *request, IMTConfirm *confirm)
  {   
   m_event  =CreateEvent(NULL,FALSE,FALSE,NULL);
   return(request && m_event && confirm);
  }
//+------------------------------------------------------------------+
//| Waiting for result                                               |
//+------------------------------------------------------------------+
inline MTAPIRES orderEntryForm::Wait(DWORD timeout)
  {
   res=MT_RET_ERR_DATA;
//--- wait for result
   if(m_event)
     {
      if(WaitForSingleObject(m_event,timeout)==WAIT_OBJECT_0)
	    {
         res=m_request->ResultRetcode();
	    }
      else
	    {
         res=MT_RET_REQUEST_TIMEOUT;
	    }
     }
//--- done
   return(res);
  }
//+------------------------------------------------------------------+
//| Result notification in form of IMTRequest                        |
//+------------------------------------------------------------------+
inline void orderEntryForm::OnDealerAnswer(const IMTRequest* request)
  {
   if(m_request) m_request->Assign(request);
   if(m_event)   SetEvent(m_event);
  }
//+------------------------------------------------------------------+
//| Result notification in form of IMTConfirm                        |
//+------------------------------------------------------------------+
inline void orderEntryForm::OnDealerResult(const IMTConfirm*  confirm)
  {
	  if(m_confirm) m_confirm->Assign(confirm); 
  }

BOOL orderEntryForm::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	for (int f_count=0;f_count<200;f_count++)
	{
		/*if (CMainFrame::arrLogin[f_count]!=L"")
		{
			m_cmbSymbol.AddString(CMainFrame::arrLogin[f_count]);
		}*/
		if (CMainFrame::arrScrip[f_count]!=L"")
		{
			m_cmbSymbol.AddString(CMainFrame::arrScrip[f_count]);
		}
	}
	m_cmbSymbolType.AddString(L"Market Order");
	m_cmbSymbolType.AddString(L"Pending Order");
	m_cmbOrderType.AddString(L"Buy Limit");
	m_cmbOrderType.AddString(L"Sell Limit");
	m_cmbOrderType.AddString(L"Buy Stop");
	m_cmbOrderType.AddString(L"Sell Stop");
	m_cmbOrderType.AddString(L"Buy Stop Limit");
	m_cmbOrderType.AddString(L"Sell Stop Limit");	
	res =MT_RET_OK_NONE;
	//DlgHelp::m_dealer->m_manager->TickSubscribe(this);
	return TRUE; 
}


inline void orderEntryForm::OnTick(LPCWSTR symbol, const MTTickShort& tick)
{
	CString   strsymbol=L"";
	CString   str_sys_symbol=L"";
	m_cmbSymbol.GetWindowTextW(strsymbol);
	str_sys_symbol=symbol;
	
	if (str_sys_symbol==strsymbol)
	{
		CString strbidask=L"BID";				
		strbidask.Format(_T("%f  /  %f"),tick.bid,tick.ask);
		m_LbPrice.SetWindowTextW(strbidask);	
	}
}

void orderEntryForm::OnBnClickedButton1()
{
	
	
   
   //IMTAdminAPI          *admin       =NULL;
   UINT                  version     =0;
   MTAPIRES              res         =MT_RET_OK_NONE;
   wchar_t               server[256] =L"";
   UINT64                login       =0;
   wchar_t               password[64]=L"";
   wchar_t               tmp[256]    =L"";
   UINT                  api_ver     = MTManagerAPIVersion;
   MTAPISTR              strapi;

//--- create request
   IMTRequest *request=manager->RequestCreate();
   IMTRequest *result =manager->RequestCreate();
   IMTConfirm *confirm=manager->DealerConfirmCreate();
   CDealerSink sink;
   UINT        id=0;
//---
   m_LbStatus.SetWindowTextW(L"");
   //manager->TickSubscribe(&sink);
//---
   if(request && result && confirm && sink.Initialize(result,confirm))
   {
	   //--- buy 1.00 EURUSD
	   request->Clear();
	   UINT64 int64Login=_wcstoui64(AddScrip::strclient,NULL,10);	   
	   request->Login(int64Login);
	   UINT intaction=0;
		short cIndex;		
		CString temp;
		cIndex=m_cmbSymbol.GetCurSel();	
		if (cIndex>=0)
		{
			m_cmbSymbol.GetLBText(cIndex,temp);
		}
		else
		{
			m_cmbSymbol.GetWindowTextW(temp);
		}

		request->Symbol(temp);

		cIndex=m_cmbSymbolType.GetCurSel();	
		if (cIndex>=0)
		{
			m_cmbSymbolType.GetLBText(cIndex,temp);
		}
		else
		{
			m_cmbSymbolType.GetWindowTextW(temp);
		}
	   int intrequest=0;
	   /*if (temp==L"Market Order")
	   {
		   intrequest=1;
	   }
	   if (temp==L"Pending Order")
	   {
		   intrequest=5;
	   }*/
		//request->Action(intrequest);
		request->Action(IMTRequest::TA_DEALER_POS_EXECUTE);	   
		//   request->Action(IMTRequest::TA_DEALER_ORD_PENDING);
	   


	   cIndex=m_cmbOrderType.GetCurSel();
	   if (cIndex>=0)
		{
			m_cmbOrderType.GetLBText(cIndex,temp);
	   }
	   else
	   {
		   m_cmbOrderType.GetWindowTextW(temp);
	   }

	   intrequest=0;
	   if (temp==L"Buy Limit")
	   {
		   intrequest=2;
	   }
	   if (temp==L"Sell Limit")
	   {
		   intrequest=3;
	   }
	   if (temp==L"Buy Stop")
	   {
		   intrequest=4;
	   }
	   if (temp==L"Sell Stop")
	   {
		   intrequest=5;
	   }
	   if (temp==L"Buy Stop Limit")
	   {
		   intrequest=6;
	   }
	   if (temp==L"Sell Stop Limit")
	   {
		   intrequest=7;
	   }
	   //request->Type(IMTOrder::OP_BUY_STOP_LIMIT );
	   request->Type(intrequest);
	   CString strVolume=L"";
	    m_Volume.GetWindowTextW(strVolume);
	   double  dbVolume=_wcstoui64(strVolume,NULL,10);	   
	   request->Volume(SMTMath::VolumeToInt(dbVolume));
	   
	   CString strPrice=L"";
	    m_Price.GetWindowTextW(strPrice);
	   double  dbPrice=_wcstoui64(strPrice,NULL,10);	   
	   request->PriceOrder(dbPrice);

	   res=manager->DealerSend(request,&sink,id);
	   if(res==MT_RET_OK)
	     {
		   res=sink.Wait(MT5_TIMEOUT_DEALER);
	     }
	   if(res==MT_RET_REQUEST_DONE)
	     {
			 m_LbStatus.SetWindowTextW(L"Order Done ");		   
	     }
	   else
	   {
		   
			m_LbStatus.SetWindowTextW(strStatus[res-10001]);		   
		   
	   }

	   request=NULL ;
	   result =NULL;
       confirm=NULL;

   }
//--- waiting for ESC press   
//--- 
   //manager->Disconnect();
   //manager->Release(); manager=NULL;
//---   

}


void orderEntryForm::OnCbnSelchangeCombo3()
{	
	
}


void orderEntryForm::OnCbnSelchangeCombo1()
{
	CString strscmdvalue=L"";
	m_cmbSymbolType.GetWindowTextW(strscmdvalue);
	orderEntryForm::strSymbolcmb=strscmdvalue;
}
