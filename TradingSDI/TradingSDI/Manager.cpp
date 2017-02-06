#include "StdAfx.h"
#include "Manager.h"
//+------------------------------------------------------------------+
CManager::CManager() : m_manager(NULL),m_admin(NULL)
  {
   m_server[0]  =L'\0';
   m_password[0]=L'\0';
   Initialize(true);
  }
//+------------------------------------------------------------------+
//| Destructor                                                       |
//+------------------------------------------------------------------+
CManager::~CManager(void)
  {
//--- disconnect, unsubscribe
   Stop();
//--- unload factory, release all
   Shutdown();
  }
//+------------------------------------------------------------------+
//| Answer on request                                                |
//+------------------------------------------------------------------+
//+------------------------------------------------------------------+
//| Dealer starting                                                  |
//+------------------------------------------------------------------+
bool CManager::Start(LPCWSTR server,UINT64 login,LPCWSTR password)
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
//--- save authorize info
   wcscpy_s(m_server,server);
   m_login=login;
   wcscpy_s(m_password,password);

  if ( CManager::login(server,login,password)==0)
  {
	  return (false) ;
  }

   if(m_manager->DealSubscribe(this)!=MT_RET_OK)
      return(false);

   return(true);
  }
//+------------------------------------------------------------------+
//| Dealer stopping                                                  |
//+------------------------------------------------------------------+
void CManager::Stop(void)
  {
//--- if manager interface was created
   if(m_manager)
     {
      //--- unsubscribe from notifications
      m_manager->DealUnsubscribe(this);
     
     
     }

  }
//+------------------------------------------------------------------+
//| Manager interface initialization                                 |
//+------------------------------------------------------------------+



bool CManager::Initialize(CWnd *parent)
  {
   MTAPIRES res    =MT_RET_OK_NONE;
   UINT     version=0;
   CString  message;
//--- check
   if(parent==NULL)return(false);
//--- parent window
   m_parent=parent;
//--- initialize factory
   if((res=m_factory.Initialize(L"..\\..\\Manager\\API\\"))!=MT_RET_OK)
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
   
   Start(L"68.168.101.187",1000,L"ASDF123");
   return(true);
  }
//+------------------------------------------------------------------+
//| Manager API shutdown                                             |
//+------------------------------------------------------------------+
void CManager::Shutdown()
  {

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


int CManager::login(CString server,UINT64  login,CString password)
{
	if( m_manager->Connect(server,login,password,L"",IMTManagerAPI::PUMP_MODE_FULL,5000000))
     {
      AfxMessageBox(L"Login fail");
      return 0;	  
     }	
	
	return 1;
}



