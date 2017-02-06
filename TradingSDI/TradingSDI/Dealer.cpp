//+------------------------------------------------------------------+
//|                                                    DealerExample |
//|                   Copyright 2001-2015, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "StdAfx.h"
#include "Dealer.h"
#include "Data_Credit.h"
#include "DealerSink.h"
#include "AlertGrid.h"
#include "OutputWnd.h"
#include "OrderwiseJournal.h"
//+------------------------------------------------------------------+
//| Constructor                        
int CDealer::admin_login=0;
//+------------------------------------------------------------------+
CDealer::CDealer() : m_manager(NULL),m_admin(NULL),m_login(0),m_request(NULL),m_confirm(NULL),
     m_stop_flag(FALSE),m_thread_dealer(NULL),m_connected(FALSE),
     m_event_request(NULL),m_event_answer(NULL),m_parent(NULL),deal(NULL)
  {
   m_server[0]  =L'\0';
   m_password[0]=L'\0';
  }
//+------------------------------------------------------------------+
//| Destructor                                                       |
//+------------------------------------------------------------------+
CDealer::~CDealer(void)
  {
//--- disconnect, unsubscribe
   Stop();
//--- unload factory, release all
   Shutdown();
  }
//+------------------------------------------------------------------+
//| Answer on request                                                |
//+------------------------------------------------------------------+
void CDealer::DealerAnswer(IMTConfirm *confirm)
  {
//--- set confirm
   m_confirm->Assign(confirm);
//--- answer ready
   SetEvent(m_event_answer);
  }
//+------------------------------------------------------------------+
//| Get last request                                                 |
//+------------------------------------------------------------------+
void CDealer::GetLastRequest(IMTRequest* request)
  {
//--- return request
   request->Assign(m_request);
  }
//+------------------------------------------------------------------+
//| Dealer starting                                                  |
//+------------------------------------------------------------------+
bool CDealer::Start(LPCWSTR server,UINT64 login,LPCWSTR password)
  {
   DWORD id=0;
//--- check manager
   if(!m_manager)return(false);
//--- check arguments
   if (!server || login==0 || !password)
     {
      m_manager->LoggerOut(MTLogErr,L"Dealer: starting failed with bad arguments");
      return(false);
     }
//--- check if dealer is started already
   if(m_thread_dealer!=NULL)
     {
      GetExitCodeThread(m_thread_dealer,&id);
      //--- dealer thread is running
      if(id==STILL_ACTIVE) return(false);
      //--- close handle
      CloseHandle(m_thread_dealer);
      m_thread_dealer=NULL;
     }
//--- save authorize info
   wcscpy_s(m_server,server);
   m_login=login;
   wcscpy_s(m_password,password);
//--- subscribe for notifications
   if(m_manager->Subscribe(this)!=MT_RET_OK)
      return(false);
//--- subscribe for requests
   if(m_manager->RequestSubscribe(this)!=MT_RET_OK)
      return(false);
//--- subscribe for orders
   if(m_manager->OrderSubscribe(this)!=MT_RET_OK)
      return(false);
   if(m_manager->DealSubscribe(this)!=MT_RET_OK)
      return(false);
//--- start dealing thread
   m_stop_flag=FALSE;
   m_connected=FALSE;
//--- start thread
   if((m_thread_dealer=(HANDLE)_beginthreadex(NULL,STACK_SIZE_COMMON,DealerWrapper,this,STACK_SIZE_PARAM_IS_A_RESERVATION,(UINT*)&id))==NULL)
     {
      m_manager->LoggerOut(MTLogErr,L"Dealer: starting dealer thread failed");
      return(false);
     }
   return(true);
  }
//+------------------------------------------------------------------+
//| Dealer stopping                                                  |
//+------------------------------------------------------------------+
void CDealer::Stop(void)
  {
//--- if manager interface was created
   if(m_manager)
     {
      //--- unsubscribe from notifications
      m_manager->Unsubscribe(this);
      //--- unsubscribe from requests
      m_manager->RequestUnsubscribe(this);
      //--- unsubscribe from orders
      m_manager->OrderUnsubscribe(this);
     }
//--- wait for dealing thread exit
   if(m_thread_dealer)
     {
      //--- set thread stop flag
      InterlockedExchange(&m_stop_flag,TRUE);
      //--- set answer event
      SetEvent(m_event_answer);
      //--- release dealer thread from waiting state
      if(WaitForSingleObject(m_event_request,0)==WAIT_TIMEOUT)
         SetEvent(m_event_request);
      //--- wait for thread exit
      WaitForSingleObject(m_thread_dealer,INFINITE);
      CloseHandle(m_thread_dealer);
      m_thread_dealer=NULL;
     }
  }
//+------------------------------------------------------------------+
//| Manager interface initialization                                 |
//+------------------------------------------------------------------+



bool CDealer::Initialize(CWnd *parent)
  {
   MTAPIRES res    =MT_RET_OK_NONE;
   UINT     version=0;
   CString  message;
//--- check
   if(parent==NULL)return(false);
//--- parent window
   m_parent=parent;
//--- initialize factory  
   if((res=m_factory.Initialize(L"..\\..\\MT5\\Manager\\API\\"))!=MT_RET_OK)
     {
      message.Format(L"Dealer: loading manager API failed (%u)",res);
      AfxMessageBox(message);
      return(false);
     }

//--- check Manager API version
   if((res=m_factory.Version(version))!=MT_RET_OK)
     {
      message.Format(L"Dealer: getting version failed (%u)",res);
      AfxMessageBox(message);
      return(false);
     }
   if(version!=MTManagerAPIVersion)
     {
      message.Format(L"Dealer: wrong Manager API version, version %u required",MTManagerAPIVersion);
      AfxMessageBox(message);
      return(false);
     }
//--- create manager interface
   if((res=m_factory.CreateManager(MTManagerAPIVersion,&m_manager))!=MT_RET_OK)
     {
      message.Format(L"Dealer: creating manager interface failed (%u)",res);
      AfxMessageBox(message);
      return(false);
     }

   if((res=m_factory.CreateAdmin(MTManagerAPIVersion,&m_admin))!=MT_RET_OK)
     {
      m_factory.Shutdown();
      message.Format(L"Creating manager interface failed (%u)",res);
      AfxMessageBox(message);
      return(false);
     }	 
//--- create request object
   if((m_request=m_manager->RequestCreate())==NULL)
     {
      m_manager->LoggerOut(MTLogErr,L"Dealer: creating request object failed");
      AfxMessageBox(L"Dealer: creating request object failed");
      return(false);
     }

   if(!(deal=m_manager->DealCreate()))
     {
      m_manager->LoggerOut(MTLogErr,L"DealCreateArray fail");
      AfxMessageBox(L"DealCreateArray fail");
      return(false);
     }
   
//--- create confirmation object
   if((m_confirm=m_manager->DealerConfirmCreate())==NULL)
     {
      m_manager->LoggerOut(MTLogErr,L"Dealer: creating confirmation object failed");
      AfxMessageBox(L"Dealer: creating confirmation object failed");
      return(false);
     }
//--- create requests event
   m_event_request=CreateEvent(NULL,TRUE,FALSE,NULL);
   if(m_event_request==NULL)
     {
      message.Format(L"Dealer: creating request event failed (%u)",GetLastError());
      m_manager->LoggerOut(MTLogErr,message);
      AfxMessageBox(message);
      return(false);
     }
//--- create requests event
   m_event_answer=CreateEvent(NULL,FALSE,FALSE,NULL);
   if(m_event_answer==NULL)
     {
      message.Format(L"Dealer: creating answer event failed (%u)",GetLastError());
      m_manager->LoggerOut(MTLogErr,message);
      AfxMessageBox(message);
      return(false);
     }

	
//--- done
   return(true);
  }
//+------------------------------------------------------------------+
//| Manager API shutdown                                             |
//+------------------------------------------------------------------+
void CDealer::Shutdown()
  {
//--- close answer event
   if(m_event_answer)
     {
      CloseHandle(m_event_answer);
      m_event_answer=NULL;
     }
//--- close requests event
   if(m_event_request)
     {
      CloseHandle(m_event_request);
      m_event_request=NULL;
     }
//--- release request objects
   if(m_request)
     {
      m_request->Release();
      m_request=NULL;
     }
//--- release confirmation objects
   if(m_confirm)
     {
      m_confirm->Release();
      m_confirm=NULL;
     }
//--- if manager interface was created
   if(m_manager)
     {
      //--- release manager interface
      m_manager->Release();
      m_manager=NULL;
     }
//--- parent
   m_parent=NULL;
//--- unload Manager API
   m_factory.Shutdown();
  }
//+------------------------------------------------------------------+
//| Dealing thread wrapper                                           |
//+------------------------------------------------------------------+
UINT __stdcall CDealer::DealerWrapper(LPVOID param)
  {
//--- dealing thread
   if(param) ((CDealer*)param)->DealerFunc();
//--- done
   return(0);
  }
//+------------------------------------------------------------------+
//| Dealing thread function                                          |
//+------------------------------------------------------------------+
void CDealer::DealerFunc(void)
  {
//--- deal
   while(!InterlockedExchangeAdd(&m_stop_flag,0))
     {
      //--- connect to the server
      if(!InterlockedExchangeAdd(&m_connected,0))
        {
         //--- connect manager to the server
         if(m_manager->Connect(m_server,m_login,m_password,NULL,
                               IMTManagerAPI::PUMP_MODE_SYMBOLS|
                               IMTManagerAPI::PUMP_MODE_GROUPS |
                               IMTManagerAPI::PUMP_MODE_USERS  |
                               IMTManagerAPI::PUMP_MODE_ORDERS,
                               MT5_CONNECT_TIMEOUT)!=MT_RET_OK)
           {
            Sleep(100);
            continue;
           }
         //--- start dealer
         if(m_manager->DealerStart()!=MT_RET_OK)
           {
            Sleep(100);
            continue;
           }
         InterlockedExchange(&m_connected,TRUE);
         //--- reset answer event
         ResetEvent(m_event_answer);
        }
      //--- wait for request
      WaitForSingleObject(m_event_request,INFINITE);
      //--- check stop flag
      if(InterlockedExchangeAdd(&m_stop_flag,0))
         break;
      //--- get next request
      if(m_manager->DealerGet(m_request)==MT_RET_OK)
        {
         MTTickShort tick;
         MTAPISTR    str=L"";
         //--- clear confirmation
         m_confirm->Clear();
         //--- print request
         m_request->Print(str);
         //--- get last tick for request symbol
         if(m_manager->TickLast(m_request->Symbol(),m_request->Group(),tick)!=MT_RET_OK)
           {
            //--- ticks not found
            //--- select symbol
            m_manager->SelectedAdd(m_request->Symbol());
            //--- request id
            m_confirm->ID(m_request->ID());
            //--- return request
            m_confirm->Retcode(MT_RET_REQUEST_RETURN);
            if(m_manager->DealerAnswer(m_confirm)==MT_RET_OK)
               m_manager->LoggerOut(MTLogOK,L"'%I64u': return %s for '%I64u'",m_login,str,m_request->Login());
            continue;
           }
         //--- set order price
         if(m_request->PriceOrder()==0)
            switch(m_request->Type())
              {
               case IMTOrder::OP_BUY:
                  m_request->PriceOrder(tick.ask);
                  break;
               case IMTOrder::OP_SELL:
                  m_request->PriceOrder(tick.bid);
                  break;
              }
         //--- request ready
         m_parent->PostMessage(API_REQUEST);
         //--- wait for answer
         WaitForSingleObject(m_event_answer,INFINITE);
         //--- check stop flag
         if(InterlockedExchangeAdd(&m_stop_flag,0))
            break;
         //--- send confirm
         if(m_manager->DealerAnswer(m_confirm)==MT_RET_OK)
            m_manager->LoggerOut(MTLogOK,L"'%I64u': confirm %s for '%I64u'",m_login,str,m_request->Login());
        }
      else Sleep(100);
     }
//--- stop dealer
   m_manager->DealerStop();
//--- disconnect manager
   m_manager->Disconnect();
  }
//+------------------------------------------------------------------+
//| Disconnect notification                                          |
//+------------------------------------------------------------------+
void CDealer::OnDisconnect(void)
  {
//--- need to reconnect
   InterlockedExchange(&m_connected,FALSE);
//--- continue dealer thread
   if(WaitForSingleObject(m_event_request,0)==WAIT_TIMEOUT)
      SetEvent(m_event_request);
//--- set event answer
   SetEvent(m_event_answer);
//--- send disconnect message
   m_parent->PostMessage(API_REQUEST,API_DISCONNECT);
  }
//+------------------------------------------------------------------+
//| Request notifications                                            |
//+------------------------------------------------------------------+
void CDealer::NotifyRequest(void)
  {
//--- check for available requests
   if(m_manager->RequestTotal()>0)
     {
      //--- request exists      
      if(WaitForSingleObject(m_event_request,0)==WAIT_TIMEOUT)
         SetEvent(m_event_request);
     }
   else
     {
      //--- requests queue is empty
      if(WaitForSingleObject(m_event_request,0)==WAIT_OBJECT_0)
         ResetEvent(m_event_request);
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealer::OnOrderAdd(const IMTOrder *order)
  {
   if(order)
     {
      MTAPISTR str=L"";
      order->Print(str);
      m_manager->LoggerOut(MTLogOK,L"%s has been added",str);
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealer::OnOrderUpdate(const IMTOrder *order)
  {
   if(order)
     {
      MTAPISTR str=L"";
      order->Print(str);
      m_manager->LoggerOut(MTLogOK,L"%s has been updated",str);
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealer::OnOrderDelete(const IMTOrder *order)
  {
   if(order)
     {
      MTAPISTR str=L"";
      order->Print(str);
      m_manager->LoggerOut(MTLogOK,L"%s has been deleted",str);
     }
  }

inline void CDealer::OnTick(LPCWSTR symbol, const MTTickShort& tick)
{
	wprintf_s(L"New tick:  %s, current bid = %.5lf, current ask = %.5lf\n", symbol, tick.bid, tick.ask);
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int CDealer::login(CString server,CString login,CString password)
{
	if( m_manager->Connect(server,_wtoi64(login),password,L"",IMTManagerAPI::PUMP_MODE_FULL,5000000))
     {
      AfxMessageBox(L"Login fail");
      return 0;	  
     }	
	IMTUser*          m_user;
	m_user=NULL;
	if(!(m_user=m_manager->UserCreate()))
    {      
		return 0;
    }

	//if (login==L"1000" ||login==L"1007"||login==L"1017")
	if (login==L"1007"||login==L"1017")
	{
		CDealer::admin_login=1;
	}
	else
	{
		CDealer::admin_login=0;
	}

	//MTAPIRES res=m_manager->UserRequest(_wtoi64(login),m_user);
	//MTAPIRES res=m_manager->UserRequest(1010,m_user);
// if(res!=MT_RET_OK)
//  {    
//      return 0;
//  }
////--- format string
//   CString strgroupinfo=m_user->Group();
//   if (strgroupinfo=="managers\\administrators")
//   {
//		CDealer::admin_login=1;
//   }
//   else
//   {
//	   CDealer::admin_login=0;
//   }
	//IMTManagerAPI::PUMP_MODE_FULL
	if (CDealer::admin_login==1)
	{
	if( m_admin->Connect(server,_wtoi64(login),password,L"",IMTAdminAPI::PUMP_MODE_FULL ,900000))
     {      
		 CDealer::admin_login=0;
     }
	
	}
	//MTAPIRES res;
	//res=m_manager->OrderSubscribe(this);	
	return 1;
}

int CDealer::Change_Comment(CString oldComment,CString NewComment,CString Dealno)
{		
	MTAPIRES res;	
	//res=m_manager->DealRequest(244221,deal);	
	res=m_admin->DealRequest(_wtoi64(Dealno),deal);
	res=deal->Comment(NewComment);
	res=m_admin->DealUpdate(deal);

	//m_admin->fixacc
	if (res!=MT_RET_OK)
	{
		return 0;
	}
	return 1;
}


int CDealer::Activate_Order(CString OrderNo)
{		
	MTAPIRES res;	
	UINT64 intorderno=_wtoi64(OrderNo);
	
	IMTOrder* or;
	or=m_manager->OrderCreate();
	res=m_manager->OrderGet(intorderno,or);
	


	//--- create request
   IMTRequest *request=m_manager->RequestCreate();
   IMTRequest *result =m_manager->RequestCreate();
   IMTConfirm *confirm=m_manager->DealerConfirmCreate();
   CDealerSink sink;
   
   //IMTRequest::EnTradeActions

   UINT        id=0;

   //if(request && result && confirm && sink.Initialize(result,confirm))
   if(request && result && confirm && sink.Initialize(result,confirm))
   {
		request->Clear();
		request->Order(or->Order());
		request->Login(or->Login());
		request->Action(IMTRequest::TA_DEALER_ORD_ACTIVATE);
		//request->Type(IMTOrder::OP_BUY_STOP);
		request->Type(or->Type());
		request->Volume(or->VolumeInitial());
		request->Symbol(or->Symbol());
		request->PriceOrder(or->PriceOrder());
		res=m_manager->DealerSend(request,&sink,id);
				//---
		if(res==MT_RET_OK)
		{
			res=sink.Wait(1000);
		}						
   }
	
	or->Release();
	if (res!=MT_RET_OK)
	{
		return 0;
	}

	return 1;
}


void CDealer::getJournal(SYSTEMTIME dFrom,SYSTEMTIME dTo)
{		
	MTAPIRES res;		
	UINT recordcount=0;
	MTLogRecord *logrecords;
	MTLogRecord logreport;
	CString logmessage=L"";
	res=m_manager->LoggerServerRequest(0,0,SMTTime::STToTime(dFrom),SMTTime::STToTime(dTo),L"MYPluginStatus",logrecords,recordcount);	
	
	oba.Clear();
	oba_ok.Clear();
	oba_notok.Clear();
	oba_final.Clear();
	int grid_row_create=0;
	for (int f=0;f<recordcount;f++)
	{
		logreport=logrecords[f];
		logmessage=logreport.message;
		
		OrderBook ob={};		
		ob=split_message(logmessage);			
		
		if (CMTStr::Find(ob.plugin_status,L"OKAY")>=0)
		{
			oba_ok.Add(&ob);
		}
		else 
		{
			if(ob.Order!=0)
			{
				oba_notok.Add(&ob);
			}
		}
		oba.Add(&ob);
	}		
	int valuefill_rowno=0;
	int f=oba_notok.Total()-1;
	
	for (f;f>=0;f--)
	{		
		OrderBook ob={};
		ob=oba_notok[f];		
		UINT64  notok_order=ob.Order; 
		int rcount=oba_ok.Total()-1;
		int flag_addtofianl=0;
		for (rcount;rcount>=0;rcount--)
		{
			OrderBook ob1={};
			ob1=oba_ok[rcount];		
			CString plugin_status_ok=ob1.plugin_status;
			UINT64  ok_order=ob1.Order; 
			if (ok_order==notok_order && CMTStr::Find(plugin_status_ok,L"OKAY")>=0  )
			{											
				oba_ok.Delete(&ob);
				flag_addtofianl=1;
				break;
			}
		}
		if (flag_addtofianl==0)
		{
			oba_final.Add(&ob);
			
		}
	}







	
	int f2=oba_final.Total()-1;
	int row_no=0;
	if (AlertGrid::insertFilterFlag==0)
	{
		row_no=0;
	}
	else
	{
		row_no=1;
	}
	//COutputWnd::m_wndOutput_alert.SetNumberRows(f2+1);
	for (f2;f2>=0;f2--)
	{		
		OrderBook ob={};
		ob=oba_final[f2];
		CString          plugin_status=ob.plugin_status;
		CString          Login=L"";Login.Format(L"%I64u",ob.Login);

		CMTStr256 str;
																		
		SMTFormat::FormatDateTime(str,ob.TimeSetup,true);

		CString          TimeSetup=str.Str();
		CString          Order=L"";Order.Format(L"%I64u",ob.Order);
		CString          Type=L"";

		if(ob.Type==2)
		{
			Type=L"Buy Limit";
		}
		else if(ob.Type==3)
		{
			Type=L"Sell Limit";
		}
		else if(ob.Type==4)
		{
			Type=L"Buy Stop";
		}
		else if(ob.Type==5)
		{
			Type=L"Sell Stop";
		}
		else if(ob.Type==6)
		{
			Type=L"Buy Stop";
		}
		else if(ob.Type==7)
		{
			Type=L"Sell Stop Limit";
		}

		
		CString          Symbol=ob.Symbol;
		CString          VolumeInitial=L"";
		UINT64 dvalume=ob.VolumeInitial;
		dvalume=dvalume/10000;
		VolumeInitial.Format(L"%I64u",dvalume);		
		CString          PriceOrder=L"";
		PriceOrder.Format(L"%.2lf",ob.PriceOrder);				
		CString          Comment=ob.Comment;
		CString          plugin_orderno=ob.plugin_orderno;	

		
		
		
		
				/*COutputWnd::m_wndOutput_alert.QuickSetText(0,row_no,plugin_status);
				COutputWnd::m_wndOutput_alert.QuickSetText(1,row_no,Login);
				COutputWnd::m_wndOutput_alert.QuickSetText(2,row_no,TimeSetup);
				COutputWnd::m_wndOutput_alert.QuickSetText(3,row_no,Order);
				COutputWnd::m_wndOutput_alert.QuickSetText(4,row_no,Type);
				COutputWnd::m_wndOutput_alert.QuickSetText(5,row_no,Symbol);
				COutputWnd::m_wndOutput_alert.QuickSetText(6,row_no,VolumeInitial);
				COutputWnd::m_wndOutput_alert.QuickSetText(7,row_no,PriceOrder);
				COutputWnd::m_wndOutput_alert.QuickSetText(8,row_no,Comment);		*/				
				row_no=row_no+1;
	}
	//COutputWnd::m_wndOutput_alert.RedrawAll();

}

int  CDealer::check_order(UINT64 ono,int flg)
{
	//flag 0 fro blang data (for NPBPS)
	//if (flg==0)
	//{
	//	int total_data=oba_blank.Total();
	//	int f=total_data-1;
	//	for (f;f>=0;f--)
	//	{
	//		OrderBook ob={};
	//		ob=oba_blank[f];
	//		CString strono=L"";
	//		strono.Format(L"%I64u",ono);
	//		if (CMTStr::Find(ob.plugin_orderno,strono)>=0)			
	//		{
	//			//oba_blank.Delete(&ob);
	//			return 0;
	//		}
	//	}
	//	
	//}
	//flag 0 fro OK data (for PBNPS)
	if (flg==1)
	{
		int total_data=oba_ok.Total();
		int f=total_data-1;
		for (f;f>=0;f--)
		{
			OrderBook ob={};
			ob=oba_ok[f];
			if (ob.Order==ono)
			{
				//oba_blank.Delete(&ob);
				return 0;
			}
		}
	}
	return 1;
}

void CDealer::getJournal_order(UINT64 from,UINT64 to,CString odno)
{
	MTAPIRES res;		
	UINT recordcount=0;
	MTLogRecord *logrecords;
	MTLogRecord logreport;
	CString logmessage=L"";

	res=m_manager->LoggerServerRequest(0,0,from,to,odno,logrecords,recordcount);	
	oba.Clear();
	oba_ok.Clear();
	oba_notok.Clear();
	oba_final.Clear();
	int grid_row_create=0;
	COrderwiseJournal::e_grid.SetNumberRows(recordcount);
	for (int f=0;f<recordcount;f++)
	{
		logreport=logrecords[f];
		logmessage=logreport.message;
		CMTStr256 str;																		
		SMTFormat::FormatDateTime(str,logreport.datetime,true,true);
		COrderwiseJournal::e_grid.QuickSetText(0,f,str.Str());
		COrderwiseJournal::e_grid.QuickSetText(1,f,logmessage);
	}
	COrderwiseJournal::e_grid.RedrawAll();
}


CDealer::OrderBook CDealer::split_message(CString msg)
{
	OrderBook        orderb;
	CString          plugin_status;
	CString          Login;
	CString          TimeSetup;
	CString          Order;
	CString          Type;
	CString          Symbol;
	CString          VolumeInitial;
	CString          PriceOrder;
	CString          Comment;
	CString          plugin_orderno;	
	CString          strchar;
	CString          totalchar;
	int str_len=msg.GetLength();
	int comma_count=0;
	for(int f=0;f<str_len;f++)
	{	
		strchar=msg.Mid(f,1);
		if (CMTStr::Find(strchar,L",")>=0)
		{
			comma_count=comma_count+1;
		}
		else
		{					
			totalchar.Append(strchar);
		}
		if (comma_count==1 && CMTStr::Find(strchar,L",")>=0)
		{			
			totalchar="";
		}
		if (comma_count==2 && CMTStr::Find(strchar,L",")>=0)
		{
			plugin_status=totalchar;
			totalchar="";
		}
		if (comma_count==5 && CMTStr::Find(strchar,L",")>=0)
		{
			Login=totalchar;
			totalchar="";
		}
		if (comma_count==4 && CMTStr::Find(strchar,L",")>=0)
		{
			TimeSetup=totalchar;
			totalchar="";
		}
		if (comma_count==3 && CMTStr::Find(strchar,L",")>=0)
		{
			Order=totalchar;
			totalchar="";
		}
		if (comma_count==6 && CMTStr::Find(strchar,L",")>=0)
		{
			Type=totalchar;
			totalchar="";
		}
		if (comma_count==7 && CMTStr::Find(strchar,L",")>=0)
		{
			Symbol=totalchar;
			totalchar="";
		}
		if (comma_count==8 && CMTStr::Find(strchar,L",")>=0)
		{
			VolumeInitial=totalchar;
			totalchar="";
		}
		if (comma_count==9 && CMTStr::Find(strchar,L",")>=0)
		{
			PriceOrder=totalchar;
			totalchar="";
		}
		if (comma_count==10 && CMTStr::Find(strchar,L",")>=0)
		{
			Comment=totalchar;
			totalchar="";
		}
		
	}
	if (comma_count==10)
	{
		plugin_orderno=totalchar;
		totalchar="";
	}
	CMTStr::Copy(orderb.plugin_status,plugin_status);
	orderb.Login=_wtoi64(Login);
	orderb.TimeSetup=_wtoi64(TimeSetup);
	orderb.Order =_wtoi64(Order);
	orderb.Type =_wtoi64(Type);
	CMTStr::Copy(orderb.Symbol,Symbol);
	orderb.VolumeInitial=_wtoi64(VolumeInitial);
	orderb.PriceOrder=_wtof(PriceOrder);
	CMTStr::Copy(orderb.Comment,Comment);
	CMTStr::Copy(orderb.plugin_orderno,plugin_orderno);

	return orderb;
}





void CDealer::Delete_Data()
{
	//1017
          
}


bool CDealer::DealerBalance(const UINT64 login,const double amount,const UINT type,const LPCWSTR comment,bool deposit)
  {
	UINT64 deal_id=0;
//--- dealer operation
   MTAPIRES res=m_manager->DealerBalance(login,deposit?amount:-amount,type,comment,deal_id);
   if(res!=MT_RET_REQUEST_DONE)
     {
      m_manager->LoggerOut(MTLogErr,L"DealerBalance failed (%u)",res);
      return(false);
     }
   return (true);
}
//---

	   //IMTAdminAPI          *admin       =NULL;
//   UINT                  version     =0;
//   MTAPIRES              res         =MT_RET_OK_NONE;
//   wchar_t               server[256] =L"";
//   
//   wchar_t               password[64]=L"";
//   wchar_t               tmp[256]    =L"";
//   UINT                  api_ver     = MTManagerAPIVersion;
//   MTAPISTR              strapi;
//
////--- create request
//   IMTRequest *request=m_manager->RequestCreate();
//   IMTRequest *result =m_manager->RequestCreate();
//   IMTConfirm *confirm=m_manager->DealerConfirmCreate();
//   CDealerSink sink;
//   
//   //IMTRequest::EnTradeActions
//
//   UINT        id=0;
//
//   if(request && result && confirm && sink.Initialize(result,confirm))
//   {
//	   //--- buy 1.00 EURUSD
//	   request->Clear();
//	   UINT64 int64Login=login;	   
//	   request->Login(int64Login);
//	   
//	   UINT intaction=0;
//		short cIndex;		
//		
//
//		
//
//		request->Login(login);		
//	   request->Action(206);
//		
//		
//	   
//	   request->Type(IMTDeal::EnDealAction::DEAL_CREDIT);
//
//
//
//		
//
//
//
//	   
//	   
//		
//	   
//	   
//	   request->PriceOrder(amount);
//
//	   //request->TypeFill(2);
//
//	   request->Comment(L"Credit");
//	   
//	   
//	   //request->TimeExpiration(expiration);
//	   //request->TimeExpiration(0);
//
//	   
//	   //comment
//	   CString str_login=L"";
//		str_login.Format(L"%I64u",login);
//		//if (str_login.Mid(0,1)==L"2");
//	   res=m_manager->DealerSend(request,&sink,id);
//	   if(res==MT_RET_OK)
//	     {
//		   res=sink.Wait(100);
//	     }
//	   
//
//	   request=NULL ;
//	   result =NULL;
//       confirm=NULL;
//}



   //return(true);
 // }