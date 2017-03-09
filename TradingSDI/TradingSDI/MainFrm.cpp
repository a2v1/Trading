#include "stdafx.h"
#include "resource.h"
#include "define_margin.h"
#include "ClientCreate.h"
#include "TradingSDI.h"
#include "MainFrm.h"
#include "AddScrip.h"
#include "Dealer.h"
#include "Login.h"
#include "DealerSink.h"
#include "orderEntryForm.h"
#include "SymbolMapping.h"
#include "NetPosGrid.h"
#include "JournalSearch.h"
#include "Symbol_Table.h"
#include "symbol_grp.h"
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace rename("EOF", "EndOfFile")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define SAFE_DELETE(ptr) if (ptr) { delete ptr; ptr = NULL; }
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)
//used for dockablepane to reset it's pointer after close->destroy	
const UINT WM_RESETMEMBER = ::RegisterWindowMessage(_T("WM_RESETMEMBER"));
const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)	
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()	
	ON_REGISTERED_MESSAGE(WM_RESETMEMBER,OnResetMember)
	ON_COMMAND(ID_FILE_SYMBOLMAPPING, &CMainFrame::OnFileSymbolmapping)
	ON_COMMAND(ID_VIEW_SYMBOLADD, &CMainFrame::OnViewSymboladd)
	ON_WM_SIZE() 	
	ON_REGISTERED_MESSAGE(AFX_WM_ON_PRESS_CLOSE_BUTTON,OnClosePane)	
	ON_COMMAND(ID_VIEW_JOURNALSEARCH, &CMainFrame::OnViewJournalsearch)
	ON_COMMAND(ID_FILE_LTPUPDATE, &CMainFrame::OnFileLtpupdate)	
	ON_COMMAND(ID_SCRIPWISENETPOS, &CMainFrame::OnScripwisenetpos)
	ON_COMMAND(ID_LIVERATEVIEW, &CMainFrame::OnLiverateview)
	ON_COMMAND(ID_IGNORE0QQTY, &CMainFrame::OnIgnore0qqty)
	ON_COMMAND(ID_IGNOREMAIN, &CMainFrame::OnIgnoremain)
	ON_COMMAND(ID_IGNORECOMMENT, &CMainFrame::OnIgnorecomment)
	ON_COMMAND(ID_UPDATECOMMENT, &CMainFrame::OnUpdatecomment)
	ON_COMMAND(ID_ActivateOrder, &CMainFrame::OnActivateorder)
	ON_UPDATE_COMMAND_UI(ID_IGNORE0QQTY, &CMainFrame::OnUpdateIgnore0qqty)
	ON_UPDATE_COMMAND_UI(ID_IGNOREMAIN, &CMainFrame::OnUpdateIgnoremain)
	ON_UPDATE_COMMAND_UI(ID_IGNORECOMMENT, &CMainFrame::OnUpdateIgnorecomment)
	ON_UPDATE_COMMAND_UI(ID_TOTALVALUE, &CMainFrame::OnUpdateTotalvalue)
//	ON_COMMAND(ID_SYMBOLMAP, &CMainFrame::OnSymbolmap)
ON_COMMAND(ID_SYMBOLMAP, &CMainFrame::OnSymbolmap)
ON_COMMAND(ID_SYMBOLGROUPMAPPING, &CMainFrame::OnSymbolgroupmapping)
ON_COMMAND(ID_LTPUPDATE, &CMainFrame::OnLtpupdate)
ON_COMMAND(ID_DEFINESYMBOL, &CMainFrame::OnDefinesymbol)
ON_COMMAND(ID_CLIENTCREATE, &CMainFrame::OnClientcreate)
ON_UPDATE_COMMAND_UI(ID_DATETIME, &CMainFrame::OnUpdateDatetime)
ON_WM_MOVE()
END_MESSAGE_MAP()
static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};
// CMainFrame construction/destruction
COutputWnd CMainFrame::m_wndOutput;
CString CMainFrame::arrLogin[200] = {};
CString CMainFrame::arrLogin_Name[200] = {};
CString CMainFrame::arrScrip[290] = {};
CString CMainFrame::current_datetime=L"";

int CMainFrame::screen_height=0; 
int CMainFrame::screen_width=0;
int CMainFrame::menubar_height=0;
int CMainFrame::toolbar_height=0;

int CMainFrame::int_currenttime=0;

CMFCRibbonBar CMainFrame::m_wndRibbonBar;
CMFCToolBar CMainFrame::m_wndToolBar;
CMainFrame::SymbolArray CMainFrame::m_symbol_array;
CMainFrame::Symbol_Mapping CMainFrame::m_s_ms={};

CDealer* DlgHelp::m_dealer=new  CDealer();
int DlgHelp::login_checkYN=0;

_bstr_t CMainFrame::strServer=".\\sqlexpress";
_bstr_t CMainFrame::strPasssword="ok";
//_bstr_t CMainFrame::strServer=".";
//_bstr_t CMainFrame::strPasssword="ok@12345";
int CMainFrame::login_Check=0;
//IMTRequest DlgHelp::m_request ;
//IMTConfirm  DlgHelp::m_confirm;	
_bstr_t orderSkip ("''");




UINT check_comment_YN_d(CString login);
UINT check_comment_YN_d(CString login)
{
	int total_count=NetPosGrid::m_Client_Details_Array.Total();
	for (int f=0;f<total_count;f++)
	{
		NetPosGrid::m_Client_Details=NetPosGrid::m_Client_Details_Array[f];
		CString str_login=NetPosGrid::m_Client_Details.V_login;
		CString CommentYN=NetPosGrid::m_Client_Details.Comment_YN;
		CommentYN=CommentYN.Trim().MakeUpper();
		if(wcscmp(str_login,login)==0)
		{
			if (wcscmp(CommentYN,L"Y")==0)
			{
				return 1;
			}
		}
	}	
	return 0;
}


void DlgHelp::add_LoginToCombobox()
{		
	IMTConGroup *group=m_dealer->m_manager->GroupCreate();
	IMTUser *user=m_dealer->m_manager->UserCreate();
	IMTConSymbol *symbols=m_dealer->m_manager->SymbolCreate();
	UINT Login_Index=0;
	UINT symbol_count=m_dealer->m_manager->SymbolTotal();    
		if (symbol_count!=0)
		{
			for(int f_count=0;f_count<symbol_count;f_count++)
			{
				if(m_dealer->m_manager->SymbolNext(f_count,symbols)==MT_RET_OK)
				{					
					CMainFrame::arrScrip[f_count]=symbols->Symbol();
				}
			}
		}
        for(UINT i=0;m_dealer->m_manager->GroupNext(i,group)==MT_RET_OK;i++)
          {		   
           UINT64 *logins=NULL;
           UINT    logins_total=0;
           if(m_dealer->m_manager->UserLogins(group->Group(),logins,logins_total)==MT_RET_OK)
             {
              if(logins && logins_total)
                for(UINT j=0;j<logins_total;j++)
                  {                  
					  UINT64 INTLOGIN=logins[j];					  
					  CString  pstrLogin=L"";
					  pstrLogin.Format( _T("%d"),INTLOGIN);
					  CString  pstrLogin_Name=L"";					  
					  CMainFrame::arrLogin[Login_Index]=pstrLogin;					  					  					  
					  if(m_dealer->m_manager->UserGet(INTLOGIN,user)==MT_RET_OK)
					  {
						  pstrLogin_Name=user->Name();
					  }
					  CMainFrame::arrLogin_Name[Login_Index]=pstrLogin_Name;
					  Login_Index=Login_Index+1;					  					  
                  }
              
              if(logins) { m_dealer->m_manager->Free(logins); logins=NULL; }
              logins_total=0;
             }
          }
        group->Release();
}





BOOL DlgHelp::OnInitDialog()
{

	//AfxMessageBox(L"OnInitDialog Start");
	CDialogEx::OnInitDialog();
	m_Password=(CEdit*)GetDlgItem(IDC_LOGIN_EDIT_PWD3);	
	m_Loginname=(CEdit*)GetDlgItem(IDC_LOGIN_EDIT_LOGIN3);
	//m_Server=(CEdit*)GetDlgItem(IDC_LOGIN_EDIT_SERVER3);
	//--- initialize dealer
   if(!m_dealer->Initialize(this))
     {
      EndDialog(IDCANCEL);
      return(FALSE);
     }
//--- create IMTRequest object
   m_request=m_dealer->RequestCreate();
   if(!m_request)
     {
      AfxMessageBox(L"Failed to create interface.");
      EndDialog(IDCANCEL);
      return(FALSE);
     }
//--- create IMTConfirm object
    m_confirm=m_dealer->ConfirmCreate();
    if(!m_confirm)
     {
      AfxMessageBox(L"Failed to create interface.");
      EndDialog(IDCANCEL);
      return(FALSE);
     }
//--	
   //AfxMessageBox(L"OnInitDialog End");
	return TRUE;  // return TRUE  unless you set the focus to a control
}


DlgHelp::DlgHelp() : CDialogEx(DlgHelp::IDD)
{
}



void DlgHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
void DlgHelp::OnIdok()
{
	// TODO: Add your command handler code here
}
void DlgHelp::OnIdcancel()
{
	// TODO: Add your command handler code here
}
BEGIN_MESSAGE_MAP(DlgHelp, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_LOGIN, &DlgHelp::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BTN_EXIT, &DlgHelp::OnBnClickedBtnExit)	
	ON_WM_CLOSE()	
	ON_COMMAND(IDOK, &DlgHelp::OnIdok)
	ON_COMMAND(IDCANCEL, &DlgHelp::OnIdcancel)
	
END_MESSAGE_MAP()

#define IDC_DIALOG_PANE 105
#define SAFE_DELETE(ptr) if (ptr) { delete ptr; ptr = NULL; }
CMainFrame::CMainFrame()
{		
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
}
CMainFrame::~CMainFrame()
{
	OrderGrid::m_Client.Close();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//CHECK bOX BY DEFAULT PROP
	m_enabled_ignore0=false ;
	m_enabled_comment =false;
	m_enabled_main=false;

	order_type[0]=L"Buy";
	order_type[1]=L"Sell";
	order_type[2]=L"Buy Limit";
	order_type[3]=L"Sell Limit";
	order_type[4]=L"Buy Stop";
	order_type[5]=L"Sell Stop";
	order_type[6]=L"Buy Stop Limit";
	order_type[7]=L"Sell Stop Limit";
	last_Nrow=0;	
	
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	

	CMainFrame::m_wndRibbonBar.Create(this);
	CMainFrame::m_wndRibbonBar.LoadFromResource(IDR_RIBBON1);
	

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	
	

	//if (!m_wndMenuBar.Create(this))
	//{
	//	TRACE0("Failed to create menubar\n");
	//	return -1;      // fail to create
	//}

	//m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// prevent the menu bar from taking the focus on activation
	//CMFCPopupMenu::SetForceMenuFocus(FALSE);

	// Allow user-defined toolbars operations:
	

	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("Failed to create toolbar\n");
	//	return -1;      // fail to create
	//}

	/*menubar_height=0;
	
	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);
*/
		
	//ribbon control
	pEditRibbon = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(ID_TOTALVALUE));	
	
	pEditDate_time = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_wndRibbonBar.FindByID(ID_DATETIME));

	
	//current date and time 
	CTime t = CTime::GetCurrentTime();
	CMainFrame::current_datetime = t.Format("%d:%m:%y %H:%M:%S");

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	
	// TODO: Delete these five lines if you don't want the toolbar and menubar to be dockable
	/*m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndToolBar);*/
	
	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	EnableLoadDockState(TRUE);
	// create docking windows
	if (!CreateDockingWindows())
	{
		TRACE0("Failed to create docking windows\n");
		return -1;
	}
	
	

	m_rateDocking.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_rateDocking);
		
	
	m_ScripNetPosDocking.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_ScripNetPosDocking);
	
	//m_ScripNetPosDocking
	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);

	EnableDocking(CBRS_ALIGN_ANY);

	
	 //Enable toolbar and docking window menu replacement
	//EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);
	//// enable menu personalization (most-recently used commands)
	//// TODO: define your own basic commands, ensuring that each pulldown menu has at least one basic command.
	//CList<UINT, UINT> lstBasicCommands;
	//lstBasicCommands.AddTail(ID_FILE_NEW);
	//lstBasicCommands.AddTail(ID_FILE_OPEN);
	//lstBasicCommands.AddTail(ID_FILE_SAVE);
	//lstBasicCommands.AddTail(ID_FILE_PRINT);
	//lstBasicCommands.AddTail(ID_APP_EXIT);
	//lstBasicCommands.AddTail(ID_EDIT_CUT);
	//lstBasicCommands.AddTail(ID_EDIT_PASTE);
	//lstBasicCommands.AddTail(ID_EDIT_UNDO);
	//lstBasicCommands.AddTail(ID_APP_ABOUT);
	//lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	//lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	//lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);	


	
//if (!m_Check0qty.Create(L"Igonore 0 Qty",WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX,CRect(0,0,105,20), &m_wndToolBar, ID_FILE_NEW_FRAME))
//{
//		TRACE0("Failed to create checkbox\n");
//		return -1; // fail to create
//}
//m_Check0qty.EnableWindow(1);
//
//
//if (!m_Ignoremain.Create(L"Ignore Main",WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX,CRect(110,0,210,20), &m_wndToolBar, ID_1))
//{
//		TRACE0("Failed to create checkbox\n");
//		return -1; // fail to create
//}
//m_Ignoremain.EnableWindow(1);
//
//if (!m_Ignorecomment.Create(L"Ignore Comment",WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX,CRect(210,0,340,20), &m_wndToolBar, ID_2))
//{
//		TRACE0("Failed to create checkbox\n");
//		return -1; // fail to create
//}
//m_Ignorecomment.EnableWindow(1);
//
//
CRect RECT;
RECT=pEditDate_time->GetRect();

RECT.bottom  =RECT.bottom +2;


//if (!m_date.Create(WS_CHILD|WS_VISIBLE,CRect(400,100,580,125), &m_wndRibbonBar, 701))
	if (!m_date.Create(WS_CHILD|WS_VISIBLE,RECT, &m_wndRibbonBar, 701))
	{
			TRACE0("Failed to create DateTimePicker\n");
			return -1; // fail to create
	}
	m_date.EnableWindow(1);
	m_date.SetFormat(L"dd-MM-yyyy HH:mm:ss");

//if (!m_btn_Delete.Create(L"Data Delete",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,CRect(510,0,615,22), &m_wndToolBar, ID_4))
//{
//		TRACE0("Failed to create checkbox\n");
//		return -1; // fail to create
//}
//m_btn_Delete.EnableWindow(0);
//
//if (!m_btn_Update_Comment.Create(L"Update Comment",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,CRect(625,0,750,22), &m_wndToolBar, ID_5))
//{
//		TRACE0("Failed to create checkbox\n");
//		return -1; // fail to create
//}
//m_btn_Update_Comment.EnableWindow(0);
//
//
//if (!m_btn_Activate_Order.Create(L"Activate Order",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,CRect(760,0,875,22), &m_wndToolBar, ID_6))
//{
//		TRACE0("Failed to create checkbox\n");
//		return -1; // fail to create
//}
//m_btn_Activate_Order.EnableWindow(0);
//
//
//if (!NetPosGrid::m_taxt_total.Create(WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,CRect(885,0,1010,18), &m_wndToolBar, ID_7))
//{
//		TRACE0("Failed to create checkbox\n");
//		return -1; // fail to create
//}
//m_taxt_total.EnableWindow(0);

//m_taxt_total

	DlgHelp dlg;

	dlg.DoModal();
	if (DlgHelp::login_checkYN==0)
	{
		//CDialog::OnCancel();
		ASSERT(AfxGetMainWnd() != NULL);    
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	
	}

	MTAPIRES res    =MT_RET_OK_NONE;

	res=DlgHelp::m_dealer->m_manager->OrderSubscribe(this);	
	res=DlgHelp::m_dealer->m_manager->DealSubscribe(this);
	
	GetDeals();

	//Loading symbol list in Array
		CDataSource connection;
		CSession session;
		HRESULT hr;
		CoInitialize(NULL);		
		hr=connection.OpenFromInitializationString(L"Provider=SQLOLEDB.1;Password=ok@12345;Persist Security Info=True;User ID=sa;Initial Catalog=tradedatabase;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=ABHISHEK-P;Use Encryption for Data=False;Tag with column collation when possible=False");			
		if(SUCCEEDED(hr))
		{
			hr=session.Open(connection);							
		}		
		CCommand<CAccessor<CSymbol_Table> > table;				 	
		char* strCommand_char="select Symbol,Mapping_Symbol from symbol_mapping";
		if(SUCCEEDED(hr))
		{
			hr=table.Open(session,strCommand_char);							 			 		 				 	
		}
		if(SUCCEEDED(hr))
		{
			while (table.MoveNext() == S_OK)
			{									
				Symbol_Mapping m_dt={};			
				CMTStr::Copy(m_dt.symbol,table.m_Symbol ) ;
				CMTStr::Copy(m_dt.Mapping_symbol,table.m_Mapping_Symbol);
				CString  Ltp_Symbol=L"";
				Ltp_Symbol=table.m_Mapping_Symbol;	
				DlgHelp::m_dealer->m_manager->SelectedAdd(Ltp_Symbol);
				m_symbol_array.Add(&m_dt);
			}		
		}			
		table.Close();
	//End of Loading symbol list in Array
	
	//DlgHelp::m_dealer->m_manager->TickSubscribe(this);
	
	

	int count=COutputWnd::m_wndOutputPos.m_SymbolMultiplyer.Total();

	for(int f=0;f<count;f++)
	{
		COutputWnd::m_wndOutputPos.m_st_multiplyer=COutputWnd::m_wndOutputPos.m_SymbolMultiplyer[f];
		DlgHelp::m_dealer->m_manager->SelectedAdd(COutputWnd::m_wndOutputPos.m_st_multiplyer.m_symbol);
	}
	
		
	res=DlgHelp::m_dealer->m_manager->TickSubscribe(this);

	state=1;
	
	login_Check=1;



	//dilog called in this class
    m_ClientDlg.Create(IDD_DIALOG1, this);
    m_Symbolmapiingdlg.Create(IDD_Mapping_Symbol, this);
	m_SymbolDlg.Create(IDD_SYMBOL_GRP, this);
	m_DefineMarginDlg.Create(IDD_DEFINE_MARGIN, this);
	m_ltp_dilog.Create(IDD_DIALOG_LTP, this);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}



BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;
	// Create output window
	CString strOutputWnd;
	

	CMainFrame::screen_height=GetSystemMetrics(SM_CYSCREEN);
	CMainFrame::screen_width =GetSystemMetrics(SM_CXSCREEN);	
	
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	//if (!m_wndOutput.Create(strOutputWnd, this, CRect(0,0,0,0), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |CBRS_ORIENT_HORZ| CBRS_FLOAT_MULTI))
	//{
	//	TRACE0("Failed to create Output window\n");
	//	return FALSE; // failed to create
	//}

	 	
	CString strScripWiseNetPosWnd;
	bNameValid = strScripWiseNetPosWnd.LoadString(IDS_SCRIPNETPOS_WND);
	ASSERT(bNameValid);
	if (!m_ScripNetPosDocking.Create(strScripWiseNetPosWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_SCRIPWISENETPOSWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT  | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Properties window\n");
		return FALSE; // failed to create
	}
	
	//	m_ScripNetPosDocking.SetAutoHideMode(true, CBRS_ALIGN_LEFT);

	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_rateDocking.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Properties window\n");
		return FALSE; // failed to create
	}

	//m_rateDocking.SetAutoHideMode(true, CBRS_ALIGN_RIGHT);
	
	


	//m_ScripNetPosDocking
	SetDockingWindowIcons(theApp.m_bHiColorIcons);

	

	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	//m_rateDocking
	//m_wndOutput.SetIcon(hOutputBarIcon, FALSE);
	m_rateDocking.SetIcon(hOutputBarIcon, FALSE);
	m_ScripNetPosDocking.SetIcon(hOutputBarIcon, FALSE);
	
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}
void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		CMainFrame::m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		CMainFrame::m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		CMainFrame::m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		CMainFrame::m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		CMainFrame::m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		CMainFrame::m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		CMainFrame::m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		CMainFrame::m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	

	//m_wndOutput.UpdateFonts();
	m_rateDocking.UpdateFonts();
	m_ScripNetPosDocking.UpdateFonts();
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// base class does the real work

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}	


	// TODO: Add your control notification handler code here
	
	return TRUE;
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
	//m_wndOutput.UpdateFonts();
	m_rateDocking.UpdateFonts();
	m_ScripNetPosDocking.UpdateFonts();
}

LRESULT CMainFrame::OnResetMember(WPARAM wp,LPARAM)
{
	return (LRESULT)TRUE;
}




void DlgHelp::OnBnClickedBtnLogin()
{

	//TODO: Add your control notification handler code here
   CString login;
   CString password;
   CString server;
   
//---   
   m_Loginname->GetWindowText(login);   

   server=L"64.150.180.239:1950";
   //server=L"72.55.168.204:1950";

   m_Password->GetWindowText(password);    
   //m_Server->GetWindowText(server);    
//--- dealer starting
   

    
	//if( m_dealer->m_manager->Connect(server,_wtoi64(login),password,L"",IMTManagerAPI::PUMP_MODE_FULL,INFINITE))
 //    {
 //     AfxMessageBox(L"Login fail");
 //     return;	  
 //    }
	////res=admin->Connect(server,login,password,L"",0,MT5_CONNECT_TIMEOUT);
	//if( m_dealer->m_admin->Connect(server,_wtoi64(login),password,L"",0,INFINITE))
 //    {
 //     //AfxMessageBox(L"Login fail");
 //     //return;	  
	//	 CMainFrame::admin_login=0;
 //    }
	//else
	//{
	//	CMainFrame::admin_login=1;
	//}
   int login_check=0;
   login_check=m_dealer->login(server,login,password);
   if (login_check==0)
   {
	   return;
   }
	//--- loading manager API
   if((orderEntryForm::factory.Initialize(L""))!=MT_RET_OK)
     {
      wprintf_s(L"Loading manager API failed ");
     
     }
//--- creating manager interface
   if((orderEntryForm::factory.CreateManager(MTManagerAPIVersion,&orderEntryForm::manager))!=MT_RET_OK)
     {
      wprintf_s(L"Creating manager interface failed ");
      
     }	

	/*if( orderEntryForm::manager->Connect(server,_wtoi64(login),password,L"",IMTManagerAPI::PUMP_MODE_FULL,INFINITE))
     {
      AfxMessageBox(L"Login fail");
      return;	  
     }*/

	//m_dealer->m_manager=orderEntryForm::manager;
	DlgHelp::login_checkYN=1;
	CDialog::OnCancel();
	add_LoginToCombobox();
	
	COutputWnd::m_wndOutputOrder.ThreadStart();
	COutputWnd::m_wndOutputPos.Thread_start_st_netpos_update();	
	//Thread_start_ServerSocket
	// TODO: Add your control notification handler code here
}


void DlgHelp::OnBnClickedBtnExit()
{	
   /*CDealerSink* sink;
   sink=new  CDealerSink();*/
   

	CDialog::OnCancel();
	ASSERT(AfxGetMainWnd() != NULL);    
	AfxGetMainWnd()->PostMessage(WM_CLOSE);
	
}

void DlgHelp::OnClose()
{	
	
	CDialog::OnCancel();
	ASSERT(AfxGetMainWnd() != NULL);    
	AfxGetMainWnd()->PostMessage(WM_CLOSE);
	CWnd::OnClose();
}
void  CMainFrame::OnDealDelete(const IMTDeal*  deal )
{
	Getnetpos();
}
void  CMainFrame::OnDealUpdate(const IMTDeal*  deal )
{
	Getnetpos();
}

void  CMainFrame::OnOrderAdd(const IMTOrder*  order)
{
	if (order->Type()!=0 && order->Type()!=1)
	{
		Dealing::dealing_mutex.Lock();	
		Dealing::st_Dealing m_st_dealing={};
		CString cstr_log_time=L"";
		CTime t = CTime::GetCurrentTime();
		cstr_log_time = t.Format("%Y.%m.%d %H:%M:%S");	
		wcscpy(m_st_dealing.LOG_TIME ,cstr_log_time);
		m_st_dealing.Time=order->TimeSetup();
		CString m_comment=order->Comment();		
		CString m_login=L"";
		m_login.Format(L"%d",order->Login());
		if (m_comment.Trim()!=L"")
		{
			if(check_comment_YN_d(m_login)==1)
			{
				m_login=m_login+"-"+m_comment;
			}
		}	
		wcscpy(m_st_dealing.Login,m_login);	

		m_st_dealing.Order=order->Order();	
		wcscpy(m_st_dealing.Symbol,order->Symbol());		
		wcscpy(m_st_dealing.Type,L"");
		double d_volume=order->VolumeInitial();
		m_st_dealing.Volume=d_volume/10000;
		m_st_dealing.Price=order->PriceOrder();	
		wcscpy(m_st_dealing.Order_type,order_type[order->Type()]);

		wcscpy(m_st_dealing.Entrytype,L"ORDER");
		wcscpy(m_st_dealing.Comment,order->Comment());	
		wcscpy(m_st_dealing.Current_Status,order->ExternalID());	
		Dealing::m_st_Dealing_Array.Add(&m_st_dealing);
		//Dealing::m_st_Dealing_Array.Shift(Dealing::m_st_Dealing_Array.Total()-1,0);	
		
		Dealing::dealing_mutex.Unlock();	
	}
}
 void  CMainFrame::OnOrderDelete(const IMTOrder*  order)
{
	if (order->Type()!=0 && order->Type()!=1)
	{
		Dealing::dealing_mutex.Lock();	
		Dealing::st_Dealing m_st_dealing={};

		CString cstr_log_time=L"";
		CTime t = CTime::GetCurrentTime();
		cstr_log_time = t.Format("%Y.%m.%d %H:%M:%S");	
		wcscpy(m_st_dealing.LOG_TIME ,cstr_log_time);

		m_st_dealing.Time=order->TimeSetup();

		CString m_comment=order->Comment();
		CString m_login=L"";
		m_login.Format(L"%d",order->Login());
		if (m_comment.Trim()!=L"")
		{
			if(check_comment_YN_d(m_login)==1)
			{
				m_login=m_login+"-"+m_comment;
			}
		}	
		wcscpy(m_st_dealing.Login,m_login);	

		m_st_dealing.Order=order->Order();	
		wcscpy(m_st_dealing.Symbol,order->Symbol());

		
		wcscpy(m_st_dealing.Type,L"");

		double d_volume=order->VolumeInitial();
		m_st_dealing.Volume=d_volume/10000;
		m_st_dealing.Price=order->PriceOrder();	

		wcscpy(m_st_dealing.Order_type,order_type[order->Type()]);

		wcscpy(m_st_dealing.Entrytype,L"ORDER");
		wcscpy(m_st_dealing.Comment,order->Comment());	
		wcscpy(m_st_dealing.Current_Status,order->ExternalID());	
		wcscpy(m_st_dealing.Current_Status,L"DELETED");	 
		Dealing::m_st_Dealing_Array.Add(&m_st_dealing);
		//Dealing::m_st_Dealing_Array.Shift(Dealing::m_st_Dealing_Array.Total()-1,0);	
		Dealing::dealing_mutex.Unlock();	
	}
}
 void  CMainFrame::OnOrderUpdate(const IMTOrder*  order)
{
	
	if (order->Type()!=0 && order->Type()!=1)
	{
		Dealing::st_Dealing m_st_dealing={};
		int total_count=Dealing::m_st_Dealing_Array.Total();
		for (int i=total_count-1;i>=0;i--)
		{
			m_st_dealing=Dealing::m_st_Dealing_Array[i];
			CString en_type=m_st_dealing.Entrytype;
			if (m_st_dealing.Order==order->Order() && en_type==L"ORDER")
			{
				break;
			}
		}
		if ( wcscmp(m_st_dealing.Comment,order->Comment())!=0 || wcscmp(m_st_dealing.Symbol ,order->Symbol())!=0  || m_st_dealing.Price!=order->PriceOrder() || m_st_dealing.Volume!=order->VolumeInitial()/10000|| wcscmp(m_st_dealing.Current_Status,order->ExternalID())!=0)
		{
		Dealing::dealing_mutex.Lock();	
		

		CString cstr_log_time=L"";
		CTime t = CTime::GetCurrentTime();
		cstr_log_time = t.Format("%Y.%m.%d %H:%M:%S");	
		wcscpy(m_st_dealing.LOG_TIME ,cstr_log_time);


		m_st_dealing.Time=order->TimeSetup();



		CString m_comment=order->Comment();
		CString m_login=L"";
		m_login.Format(L"%d",order->Login());
		if (m_comment.Trim()!=L"")
		{
			if(check_comment_YN_d(m_login)==1)
			{
				m_login=m_login+"-"+m_comment;
			}
		}	
		wcscpy(m_st_dealing.Login,m_login);	

		m_st_dealing.Order=order->Order();	
		wcscpy(m_st_dealing.Symbol,order->Symbol());

		
		wcscpy(m_st_dealing.Type,L"");

		double d_volume=order->VolumeInitial();
		m_st_dealing.Volume=d_volume/10000;
		m_st_dealing.Price=order->PriceOrder();	

		m_st_dealing.Deal=0;

		wcscpy(m_st_dealing.Order_type,order_type[order->Type()]);

		wcscpy(m_st_dealing.Entrytype,L"ORDER");
		wcscpy(m_st_dealing.Comment,order->Comment());	
		wcscpy(m_st_dealing.Current_Status,order->ExternalID());	
		Dealing::m_st_Dealing_Array.Add(&m_st_dealing);
		//Dealing::m_st_Dealing_Array.Shift(Dealing::m_st_Dealing_Array.Total()-1,0);	
		Dealing::dealing_mutex.Unlock();	
		}
	}
}


 void  CMainFrame::Getnetpos()
 {	 
	 
 }



  void  CMainFrame::GetDeals()
 {	 
	
 }
  
void  CMainFrame::GetOrders()
 {	 		 
		
 }



BOOLEAN  CMainFrame::Check_ltp_symbol(LPCWSTR symbol_ltp)
{
	int m_count=m_symbol_array.Total();
	for (int f=0;f<m_count;f++)
	{
		Symbol_Mapping m_ms={};
		m_ms=m_symbol_array[f];
		if(wcscmp(m_ms.Mapping_symbol,symbol_ltp)==0)
		{
			return true ;
		}
	}
	return false;
}

CString  CMainFrame::GetSymbolFrom_MappingSymbol(LPCWSTR symbol_ltp)
{
	CString Return_String=L"";
	int m_count=m_symbol_array.Total();
	for (int f=0;f<m_count;f++)
	{
		Symbol_Mapping m_ms={};
		m_ms=m_symbol_array[f];
		if(wcscmp(m_ms.Mapping_symbol,symbol_ltp)==0)
		{
			Return_String=m_ms.symbol;
			return Return_String;
		}
	}
	return Return_String;
}


BOOLEAN  CMainFrame::Check_valid_Symbol(LPCWSTR symbol_ltp,LPCWSTR symbol)
{	
	int m_count=m_symbol_array.Total();
	for (int f=0;f<m_count;f++)
	{
		Symbol_Mapping m_ms={};
		m_ms=m_symbol_array[f];
		if(wcscmp(m_ms.Mapping_symbol,symbol_ltp)==0 && wcscmp(m_ms.symbol,symbol)==0)
		{			
			return true ;
		}
	}
	return false ;
}

inline void CMainFrame::OnTick(LPCWSTR symbol, const MTTickShort& tick)
{
	if (NetPosGrid::first_time_update==1 )
	{
		if (Check_ltp_symbol(symbol)==true)	
		{		
			//NetPosGrid::mutex_Symbol_ltp.Lock();
			OrderGrid::str_symbol_for_rate=symbol;		
			OrderGrid::dbl_rate=tick.bid;		
			//NetPosGrid::mutex_Symbol_ltp.Unlock();			
		}
	}
}



void CMainFrame::OnFileSymbolmapping()
{
		// TODO: Add your command handler code here
		SymbolMapping* dlg = new SymbolMapping();
	
		dlg->Create(IDD_Mapping_Symbol, this);
		//dlg->SetWindowPos(NULL, 0,Pos,0,0, SWP_NOZORDER | SWP_NOMOVE | SWP_SHOWWINDOW);
		CRect rect;
		GetClientRect(&rect);
		dlg->MoveWindow( 1,48,500,700);
		dlg->ShowWindow(SW_NORMAL);
	}
void  CMainFrame::OnDealAdd(const IMTDeal*  deal)
{
	Dealing::dealing_mutex.Lock();
	Dealing::st_Dealing m_st_dealing={};
	CString cstr_log_time=L"";
	CTime t = CTime::GetCurrentTime();
	cstr_log_time = t.Format("%Y.%m.%d %H:%M:%S");	
	wcscpy(m_st_dealing.LOG_TIME ,cstr_log_time);	
	m_st_dealing.Time=deal->Time();
	CString m_comment=deal->Comment();
	CString m_login=L"";
	m_login.Format(L"%d",deal->Login());
	if (m_comment.Trim()!=L"")
	{	
		if(check_comment_YN_d(m_login)==1)
		{
			m_login=m_login+"-"+m_comment;
		}
	}	
	wcscpy(m_st_dealing.Login,m_login);
	m_st_dealing.Deal=deal->Deal();
	m_st_dealing.Order=deal->Order();
	
	wcscpy(m_st_dealing.Symbol,deal->Symbol());
	CString m_type=L"";
	if (deal->Action()==0)
	{
		m_type=L"BUY";
	}
	else if (deal->Action()==1)
	{
		m_type=L"SELL";
	}
	else
	{
		m_type=L"";
	}	
	wcscpy(m_st_dealing.Type,m_type);
	double d_volume=deal->Volume();
	m_st_dealing.Volume=d_volume/10000;
	m_st_dealing.Price=deal->Price();
	wcscpy(m_st_dealing.Comment,deal->Comment());	
	wcscpy(m_st_dealing.Current_Status,deal->ExternalID());	
	wcscpy(m_st_dealing.Entrytype,L"DEAL");
	Dealing::m_st_Dealing_Array.Add(&m_st_dealing);
	//Dealing::m_st_Dealing_Array.Shift(Dealing::m_st_Dealing_Array.Total()-1,0);	
	Dealing::dealing_mutex.Unlock();	
}

void CMainFrame::OnViewSymboladd()
{
	// TODO: Add your command handler code here
	AddScrip* dlg = new AddScrip();
	
	dlg->Create(IDD_DIALOG_ADD_SCRIP, this);
	dlg->SetWindowPos(NULL, 0,0,0,0, SWP_NOZORDER | SWP_NOMOVE | SWP_SHOWWINDOW);
	CRect rect;
	GetClientRect(&rect);
	dlg->MoveWindow( 1,48,rect.Width(),40);
	dlg->ShowWindow(SW_NORMAL);
}

int CMainFrame::CreateRebar( void )
{    
    return 0;
}

LRESULT CMainFrame::OnClosePane(WPARAM,LPARAM lp)
{		
    CBasePane* pane = (CBasePane*)lp;
    int id = pane->GetDlgCtrlID();    
	int cx,cy;
	cx=0;
	cy=0 ;
	if (id==102)
	{
		ScripWiseNetPosDocking::m_scripnetpos_x=cx;
		cy=ScripWiseNetPosDocking::m_scripnetpos_y;
		int i=0;		
		//CMainFrame::m_wndOutput.SetWindowPos(NULL,cx+5 , 30, CMainFrame::screen_width-cx-RateDocking::m_rate_x-5, cy+40,  SWP_NOACTIVATE | SWP_NOZORDER);	
	}
	if (id==150)
	{
		cx=0;
		RateDocking::m_rate_x=cx;
		cy=RateDocking::m_rate_y;
		int i=0;		
		//CMainFrame::m_wndOutput.SetWindowPos(NULL,cx+5 , 30, CMainFrame::screen_width-cx-RateDocking::m_rate_x-5, cy+40,  SWP_NOACTIVATE | SWP_NOZORDER);	
	}
	
 return (LRESULT)FALSE ;
}

BOOL CMainFrame::OnShowPanes(BOOL bShow)
{
	//AfxMessageBox(L"Hello");
	return false;
}

void CMainFrame::Activate_Order()
{
	
	COutputWnd::m_wndOutputOrder.Selected_ActivateOrder();
	
}
void CMainFrame::UpdateComment()
{
	//Duplicate_Order m_d_order;
	COutputWnd::m_wndOutputDuplicate_Order.Selected_commentChange();
}

void CMainFrame::OnViewJournalsearch()
{	
	CJournalSearch* dlg = new CJournalSearch();
	
	dlg->Create(IDD_DIALOG_FOR_JOURNAL_SEARCH, this);
	dlg->SetWindowPos(NULL, 0,0,0,0, SWP_NOZORDER | SWP_NOMOVE | SWP_SHOWWINDOW);
	CRect rect;
	GetClientRect(&rect);
	dlg->MoveWindow( rect.left+470,rect.bottom-75 ,330,40);		
	dlg->ShowWindow(SW_NORMAL);
}


void CMainFrame::OnFileLtpupdate()
{
	
	
    RecalcLayout();
}


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	int x=(int)pMsg->wParam;

if(pMsg->message==WM_SYSKEYDOWN || pMsg->message==WM_KEYDOWN )
{
		BOOL bCtrl=::GetKeyState(VK_CONTROL)&0x8000;
        BOOL bShift=::GetKeyState(VK_SHIFT)&0x8000;
        BOOL bAlt=::GetKeyState(VK_MENU)&0x8000;

switch (x)
		{
          case 77:
			  if(bCtrl )
	                   {
						   if (m_Ignoremain.GetState()==BST_UNCHECKED)
						   {
							    m_Ignoremain.SetCheck(BST_CHECKED);
						        NetPosGrid::ignoremain=" and isnull(type,'')<>'O'";
	                            NetPosGrid::ignorecomment="";
	                         	m_Ignorecomment.SetCheck(0);
	
						    	m_Ignoremain.EnableWindow(TRUE);
						   }
						   else if(m_Ignoremain.GetState()==BST_CHECKED)
						   {
						
							   m_Ignoremain.SetCheck(BST_UNCHECKED);
                                 NetPosGrid::ignoremain="";  
						    	m_Ignoremain.EnableWindow(TRUE);
						   }
						   return TRUE; 
						   OBJ.RedrawAll();
			            }
			         
	                  RedrawWindow();
					  break;

          case 90:
	             if(bCtrl)
	                  {
						  if (m_Check0qty.GetState()==BST_UNCHECKED)
						   {
							   m_Check0qty.SetCheck(BST_CHECKED);
		                       NetPosGrid::ignore0ty=" and t1.NetQty<>0"; 
							    m_Check0qty.EnableWindow(TRUE);

						   }
						   else if(m_Check0qty.GetState()==BST_CHECKED)
						   {
							    m_Check0qty.SetCheck(BST_UNCHECKED);
						        NetPosGrid::ignore0ty="";
							    m_Check0qty.EnableWindow(TRUE);

						   }
		                  return TRUE;
						  OBJ.RedrawAll();
	                  }
				       
				      RedrawWindow();
					  break;
		  case 67:
			    if(bCtrl)
				      {
				          if (m_Ignorecomment.GetState()==BST_UNCHECKED)
						   {   
							   m_Ignorecomment.SetCheck(BST_CHECKED);
							   NetPosGrid::ignoremain="";
		                       NetPosGrid::ignorecomment=" and isnull(type,'')<>'D'";
		                       m_Ignoremain.SetCheck(0);
							    m_Ignorecomment.EnableWindow(TRUE);

						   }
						   else if(m_Ignorecomment.GetState()==BST_CHECKED)
						   {    
							     m_Ignorecomment.SetCheck(BST_UNCHECKED);
							    NetPosGrid::ignorecomment="";
								 m_Ignorecomment.EnableWindow(TRUE);
						   }
		                  return TRUE;
						   OBJ.RedrawAll();
				        }
				         
				         RedrawWindow();
						 break;
		  case 82:
			  if(bCtrl)
			         {
					
					     /* if(!m_bShow && !m_bVisible)
		                      {
								 m_bShow = TRUE;
		                         m_bVisible	= TRUE;
		                         Invalidate();
								 m_rateDocking.ShowPane(TRUE,FALSE,TRUE);
								 m_rateDocking.DockToRecentPos();
					             UpdateWindow();

								 }
						  else 
			     			  {
								  m_bShow = FALSE;
		                          m_bVisible = FALSE;
		                          Invalidate();
								  m_rateDocking.ShowPane(FALSE,FALSE,FALSE);
		                          UpdateWindow();
						     }*/
						
				     }
			         RedrawWindow();
			         break;
           case 66:
			   if(bCtrl)
			         {
					        if(!m_bShow && !m_bVisible)
		                        {
				                
	                        	 m_bShow = TRUE;
		                         m_bVisible	= TRUE;
		                         Invalidate();
								 m_ScripNetPosDocking.ShowPane(TRUE,FALSE,TRUE);
								  m_ScripNetPosDocking.DockToRecentPos();
							     UpdateWindow();

								 }
						    else 
			     			   {
								  m_bShow		= FALSE;
		                          m_bVisible	= FALSE;
		                          Invalidate();
								  m_ScripNetPosDocking.ShowPane(FALSE,FALSE,FALSE);
		                          UpdateWindow();
						       }
				     }
			         RedrawWindow();
			         break;
  		                   default:
			                  break;
		           }
           
       }
 
            
	return __super::PreTranslateMessage(pMsg);
}


void CMainFrame::OnScripwisenetpos()
{
	BOOL show_hide= this->m_ScripNetPosDocking.IsVisible();
	m_ScripNetPosDocking.ShowPane(!show_hide,FALSE,!show_hide);	
}


void CMainFrame::OnLiverateview()
{
	BOOL show_hide= this->m_rateDocking.IsVisible();
	m_rateDocking.ShowPane(!show_hide,FALSE,!show_hide);
}


void CMainFrame::OnUpdateIgnore0qqty(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
    pCmdUI->Enable();
	pCmdUI->SetCheck( m_enabled_ignore0 ? 1 :  0 );
}


void CMainFrame::OnIgnore0qqty()
{	// TODO: Add your command handler code here
	m_enabled_ignore0 = !m_enabled_ignore0;


    if(m_enabled_ignore0==1)
	{
		NetPosGrid::int_ignoreQty=1;
	}
	if(m_enabled_ignore0==0)
	{
		NetPosGrid::int_ignoreQty=0;
	}
 
	Invalidate();
}

void CMainFrame::OnUpdateIgnoremain(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
    pCmdUI->SetCheck( m_enabled_main ? 1 :  0 );
	
}


void CMainFrame::OnIgnoremain()
{
	// TODO: Add your command handler code here
	m_enabled_main =!m_enabled_main;
	m_enabled_comment=false;
	if(m_enabled_main==1)
	{
		NetPosGrid::ignoremain=" and isnull(type,'')<>'O'";
		NetPosGrid::ignorecomment="";
	}
	if(m_enabled_main==0)
	{
		NetPosGrid::ignoremain="";
	}
  
   Invalidate();
}

void CMainFrame::OnUpdateIgnorecomment(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
    pCmdUI->SetCheck( m_enabled_comment ? 1 :  0);

}

void CMainFrame::OnIgnorecomment()
{
	// TODO: Add your command handler code here

	m_enabled_comment=!m_enabled_comment;
	m_enabled_main=false;
	if(m_enabled_comment==1)
	{
		NetPosGrid::mutex_Symbol_ltp.Lock();
		NetPosGrid::m_login_in_m_Array.Clear();
		NetPosGrid::m_Symbol_in_m_Array.Clear();
		NetPosGrid::int_igrore_comment=1;
		int noof_rowsInStruc=NetPosGrid::m_client_lost.Total();
		NetPosGrid::st_Netposition st_net={};
		for(int i=0;i<noof_rowsInStruc;i++)
		{
			st_net=NetPosGrid::m_client_lost[i];
			CString str_login=st_net.m_login;
			if (str_login.Find('-')>0)
			{
				str_login=str_login.Mid(0,str_login.Find('-'));			
			}
			//For checking login is allreay exist or not
			int  login_count=NetPosGrid::m_login_in_m_Array.Total();
			int check_for_duplicate=0;
			for (int f=0;f<login_count;f++)
			{
				NetPosGrid::login_in_m m_st_login_c={};
				m_st_login_c=NetPosGrid::m_login_in_m_Array[f];
				if (wcscmp(m_st_login_c.V_login,str_login)==0)
				{
					check_for_duplicate=1;
					break;
				}
			}
			//End of Checking
			if (check_for_duplicate==0)
			{
				NetPosGrid::login_in_m m_st_login={};
				CMTStr::Copy(m_st_login.V_login,str_login);				
				NetPosGrid::m_login_in_m_Array.Add(&m_st_login);
			}


			CString str_symbol=st_net.m_symbol ;
			
			//For checking login is allreay exist or not
			int  symbol_count=NetPosGrid::m_Symbol_in_m_Array.Total();
			int check_for_duplicate_symbol=0;
			for (int f=0;f<login_count;f++)
			{
				NetPosGrid::Symbol_in_m  m_st_symbol_c={};
				m_st_symbol_c=NetPosGrid::m_Symbol_in_m_Array[f];
				if (wcscmp(m_st_symbol_c.V_symbol ,str_symbol)==0)
				{
					check_for_duplicate_symbol=1;
					break;
				}
			}
			//End of Checking
			if (check_for_duplicate_symbol==0)
			{
				NetPosGrid::Symbol_in_m  m_st_symbol={};
				CMTStr::Copy(m_st_symbol.V_symbol,str_symbol);				
				NetPosGrid::m_Symbol_in_m_Array.Add(&m_st_symbol);
			}
		}
		NetPosGrid::mutex_Symbol_ltp.Unlock();
	}
	if(m_enabled_comment==0)
	{
		NetPosGrid::int_igrore_comment=0;
	}

	Invalidate();
}


void CMainFrame::OnUpdatecomment()
{
	// TODO: Add your command handler code here
	COutputWnd::m_wndOutputDuplicate_Order.Selected_commentChange();
}


void CMainFrame::OnActivateorder()
{
	// TODO: Add your command handler code here
	COutputWnd::m_wndOutputOrder.Selected_ActivateOrder();
}

void CMainFrame::OnUpdateTotalvalue(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();	
	NetPosGrid::str_grid_mutex.Lock();
	pEditRibbon->SetEditText(NetPosGrid::Str_Total_Bal);
	NetPosGrid::str_grid_mutex.Unlock();
	
}


void CMainFrame::OnSymbolmap()
{
    CRect rect;
	GetClientRect(&rect);
	m_Symbolmapiingdlg.MoveWindow( 1,48,440,650);
	m_Symbolmapiingdlg.ShowWindow(SW_NORMAL);
	

}



void CMainFrame::OnSymbolgroupmapping()
{
	CRect rect;
	GetClientRect(&rect);
	m_SymbolDlg.MoveWindow( 1,48,430,600);
	m_SymbolDlg.ShowWindow(SW_NORMAL);
		
}


void CMainFrame::OnLtpupdate()
{
	CRect rect;
	GetClientRect(&rect);
	m_ltp_dilog.MoveWindow( 1,48,380,500);
	m_ltp_dilog.ShowWindow(SW_NORMAL);
}


void CMainFrame::OnDefinesymbol()
{

	CRect rect;
	GetClientRect(&rect);
	m_DefineMarginDlg.MoveWindow( 1,48,400,538);
	m_DefineMarginDlg.ShowWindow(SW_NORMAL);
	
}


void CMainFrame::OnClientcreate()
{

	CRect rect;
	GetClientRect(&rect);
	m_ClientDlg.MoveWindow( 30,100,450,350);
	m_ClientDlg.ShowWindow(SW_NORMAL);
}


void CMainFrame::OnUpdateDatetime(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(0);				
	//pEditDate_time->SetEditText(CMainFrame::current_datetime);
}


void CMainFrame::OnMove(int x, int y)
{
	__super::OnMove(x, y);


	
}
