#pragma once

#define API_REQUEST (WM_USER+1)
#define API_DISCONNECT 0xffff
class CManager :   public IMTDealSink 
  {	
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
   
   
  
   
   CWnd             *m_parent;         // parent dialog

public:	
	
	int check_order(UINT64 ono,int flg);
	void getJournal_order(UINT64 dFrom,UINT64 dTo,CString ordno);
	
	void getJournal(SYSTEMTIME dFrom,SYSTEMTIME dTo);
	
	
	IMTManagerAPI    *m_manager;        // Manager interface
	IMTAdminAPI		 *m_admin;
                     CManager();
                    ~CManager(void);
   //--- initialization 
   bool              Initialize(CWnd *parent);
   
   
   bool              Start(LPCWSTR server,UINT64 login,LPCWSTR password);
   void              Stop(void);
   //--- IMTManagerSink implementation
   
   int login(CString server,UINT64 login,CString password);

   
   void              Shutdown(void);

};

