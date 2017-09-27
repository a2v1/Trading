
// MainFrm.h : interface of the CMainFrame class
#pragma once
#include "OutputWnd.h"
#include "RateDocking.h"
#include "ScripWiseNetPosDocking.h"
#include "CustomDateTimePiker.h"
#include "LogFile.h"
#include "define_margin.h"
#include "ClientCreate.h"
#include "SymbolMapping.h"
#include "LTP_Dilog.h"
#include "symbol_grp.h"
class CMainFrame : public CFrameWndEx,public IMTManagerSink, public IMTRequestSink, public IMTOrderSink, public IMTDealerSink,public IMTDealSink ,public IMTTickSink 
{	
protected: // create from serialization only
	_variant_t avarRecords;
	DECLARE_DYNCREATE(CMainFrame)
	void  CMainFrame::GetOrders();
// Attributes
public:
	CString order_type[8];
   struct Symbol_Mapping
   {
	  
      wchar_t           symbol[64];              
	  wchar_t           Mapping_symbol[64];              
      
   };
   typedef TMTArray<Symbol_Mapping> SymbolArray;
   static SymbolArray m_symbol_array;

   static Symbol_Mapping m_s_ms;

   CMFCRibbonEdit* pEditRibbon;
   CMFCRibbonEdit* pEditDate_time;

	CLogFile m_logfile;

	static  COutputWnd m_wndOutput;
	static 	CString arrLogin[200];
	static 	CString arrLogin_Name[200];
	static	CString arrScrip[290];

	
	static _bstr_t   strServer;
	static _bstr_t  strPasssword;
	static	 int login_Check ;
	static   int screen_height; 
	static   int screen_width;
	static   int menubar_height;
	static   int toolbar_height;

	static int int_currenttime;

	  bool m_bShow;
      bool m_bVisible;
      NetPosGrid OBJ;


	CButton          m_check_IgnoreQty;
	CReBar           m_rebar;
	CReBar           m_wndReBar;
	CComboBox        m_comboBox;

	CButton			  m_Check0qty;
	CButton			  m_Ignoremain;
	CButton			  m_Ignorecomment;
	
	static CMFCRibbonBar  m_wndRibbonBar;
	static CString        current_datetime;

	//new Dlg calling
	CDateTimeEditCtrl     m_date;	
	

	CButton			  m_btn_Delete;
	CButton			  m_btn_Update_Comment;
	CButton			  m_btn_Activate_Order;
	bool              m_enabled_ignore0;
	bool              m_enabled_main;
	bool              m_enabled_comment;

	
public:
	int state; 	
	
// Overrides
public:
	CMainFrame();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	
	
	int m_index;
	static CMFCToolBar m_wndToolBar;
	int last_Nrow;
	virtual void UpdateComment();

	virtual BOOL OnShowPanes(BOOL bShow);
	
// Implementation
public:
	virtual ~CMainFrame();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	
#endif

protected:  // control bar embedded members
	CMFCMenuBar       m_wndMenuBar;
	
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;	
	RateDocking       m_rateDocking;
	ScripWiseNetPosDocking   m_ScripNetPosDocking;

	//data base initilization objects
	CDataSource connection;
	CSession session;
	HRESULT hr;
	//CFormView         m_formView;

	//LRESULT OnClosePane(WPARAM,LPARAM lp);
	
	virtual void  OnDealAdd(const IMTDeal*  deal);
	virtual void  OnDealDelete(const IMTDeal*  deal);
	virtual void  OnDealUpdate(const IMTDeal*  deal);
	virtual void  OnOrderAdd(const IMTOrder*  order);
	virtual void  OnOrderDelete(const IMTOrder*  order);
	virtual void  OnOrderUpdate(const IMTOrder*  order);
	virtual void  OnTick(LPCWSTR symbol, const MTTickShort& tick);

	BOOLEAN  Check_ltp_symbol(LPCWSTR symbol_ltp);
	CString  GetSymbolFrom_MappingSymbol(LPCWSTR symbol_ltp);
	
	void Activate_Order();
	//BOOL OnCmdMsg(UINT id,int code , void *pExtra,AFX_CMDHANDLERINFO* pHandler);
    
 void  CMainFrame::Getnetpos();
 void  CMainFrame::GetDeals();
 int CMainFrame::CreateRebar( void );

 BOOLEAN  Check_valid_Symbol(LPCWSTR symbol_ltp,LPCWSTR symbol);
LRESULT OnClosePane(WPARAM,LPARAM lp);

LRESULT OnResetMember(WPARAM wp,LPARAM);
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();	
	
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	afx_msg void OnFileSymbolmapping();
	afx_msg void OnViewSymboladd();
	afx_msg void OnViewJournalsearch();
	afx_msg void OnFileLtpupdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnScripwisenetpos();
	afx_msg void OnLiverateview();
	afx_msg void OnIgnore0qqty();
	afx_msg void OnIgnoremain();
	afx_msg void OnIgnorecomment();
	afx_msg void OnUpdatecomment();
	afx_msg void OnActivateorder();
	afx_msg void OnUpdateIgnore0qqty(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIgnoremain(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIgnorecomment(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTotalvalue(CCmdUI *pCmdUI);
//	afx_msg void OnSymbolmap();
	afx_msg void OnSymbolmap();
	afx_msg void OnSymbolgroupmapping();
	afx_msg void OnLtpupdate();
	afx_msg void OnDefinesymbol();
	afx_msg void OnClientcreate();
	afx_msg void OnUpdateDatetime(CCmdUI *pCmdUI);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnUsercreate();
	afx_msg void OnUserCreate();
	afx_msg void OnUserclientmapping();
	afx_msg void OnScripwisemodule();
};






