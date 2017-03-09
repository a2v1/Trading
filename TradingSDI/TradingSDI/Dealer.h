//+------------------------------------------------------------------+
//|                                                    DealerExample |
//|                   Copyright 2001-2015, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//--- user message
#define API_REQUEST (WM_USER+1)
#define API_DISCONNECT 0xffff
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CDealer : public IMTManagerSink, public IMTRequestSink, public IMTOrderSink, public IMTDealerSink, public IMTTickSink,public IMTDealSink 
  {

	struct OrderBook
   {	  
		wchar_t           plugin_status[64];
		UINT64            Login;
		UINT64            TimeSetup;
		UINT64            Order;
		UINT              Type;
		wchar_t           Symbol[64];
		UINT64            VolumeInitial;
		double            PriceOrder;
		wchar_t           Comment[64];
		wchar_t           plugin_orderno[64];
   };
	
	//typedef CArray<OrderBook> OrderBook;
	typedef TMTArray<OrderBook> OrderBookArray;
	OrderBookArray oba;
	OrderBookArray oba_ok;
	OrderBookArray oba_notok;
	OrderBookArray oba_final;
	
   enum              constants
     {
      MT5_CONNECT_TIMEOUT=30000,       // connect timeout in milliseconds
      STACK_SIZE_COMMON  =1024*1024,   // stack size for dealing thread in bytes
     };
private:
   CMTManagerAPIFactory m_factory;     // Manager API factory   
   MTAPISTR          m_server;         // server address
   
   UINT64            m_login;          // dealer login
   MTAPISTR          m_password;       // dealer password
   IMTRequest       *m_request;        // request interface
   IMTConfirm       *m_confirm;        // confirmation interface
   volatile LONG     m_stop_flag;      // dealing stop flag
   HANDLE            m_thread_dealer;  // dealing thread
   volatile LONG     m_connected;      // connected flag
   HANDLE            m_event_request;  // request notifications event
   HANDLE            m_event_answer;   // answer notifications event
   HANDLE            m_event;
   CWnd             *m_parent;         // parent dialog

public:	
	
	int check_order(UINT64 ono,int flg);
	OrderBook split_message(CString msg);
	void CDealer::getJournal(SYSTEMTIME dFrom,SYSTEMTIME dTo);
	IMTDeal* deal;		
	static int admin_login;
	static CString admin_login_name;
 IMTManagerAPI    *m_manager;        // Manager interface
 IMTAdminAPI  *m_admin;
                     CDealer();
                    ~CDealer(void);
   //--- initialization 
   bool              Initialize(CWnd *parent);
   int Change_Comment(CString oldComment,CString NewComment,CString Dealno);
   bool DealerBalance(const UINT64 login,const double amount,const UINT type,const LPCWSTR comment,bool deposit);
   //--- answer
   void              DealerAnswer(IMTConfirm *confirm);
   void              GetLastRequest(IMTRequest* request);
   IMTRequest*       RequestCreate(){ if(m_manager==NULL)return(NULL); return(m_manager->RequestCreate()); }
   IMTConfirm*       ConfirmCreate(){ if(m_manager==NULL)return(NULL); return(m_manager->DealerConfirmCreate()); }
   //--- starting and stopping
   bool              Start(LPCWSTR server,UINT64 login,LPCWSTR password);
   void              Stop(void);
   //--- IMTManagerSink implementation
   virtual void      OnDisconnect(void);
   //--- IMTRequestSink implementation
   virtual void      OnRequestAdd(const IMTRequest*)    { NotifyRequest(); }
   virtual void      OnRequestUpdate(const IMTRequest*) { NotifyRequest(); }
   virtual void      OnRequestDelete(const IMTRequest*) { NotifyRequest(); }
   virtual void      OnRequestSync(void)                { NotifyRequest(); }

   int login(CString server,CString login,CString password);

   void Delete_Data(); 

   void getJournal_order(UINT64 from,UINT64 to,CString odno);
   
   int Activate_Order(CString OrderNo);
   //virtual void      OnDealerAnswer(const IMTRequest* result);
   //virtual void      OnDealerResult(const IMTConfirm* confirm);
   virtual void      OnTick(LPCWSTR symbol, const MTTickShort& tick);

   //--- IMTOrderSink implementation
   virtual void      OnOrderAdd(const IMTOrder*    order);
   virtual void      OnOrderUpdate(const IMTOrder* order);
   virtual void      OnOrderDelete(const IMTOrder* order);
   
    //--- shutdown
   void              Shutdown(void);

private:
  
   //--- dealing thread
   static UINT __stdcall DealerWrapper(LPVOID param);
   void              DealerFunc(void);
   //--- requests notification
   void              NotifyRequest(void);
  };
//+------------------------------------------------------------------+
