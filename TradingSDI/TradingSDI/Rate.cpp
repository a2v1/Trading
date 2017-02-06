
// TradingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "Rate.h"
#include "afxdialogex.h"
#include "Login.h"
#include "DealerSink.h"
#include "orderEntryForm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int Rate::tickSuscribeCheck=0;
double strbidDisplay=0;
double straskDisplay=0;
Rate::Rate(CWnd* pParent /*=NULL*/)
	: CDialogEx(Rate::IDD, pParent),
	m_bShowGripper(true),
      m_szMinimum(0, 0),
      m_hGripper(NULL)
{
	res    =MT_RET_OK_NONE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


CString strSymbol_r=L"";
CString strEx_r=L"";

Rate::Rate(CString strSymbol,CString strEx,CWnd* pParent /*=NULL*/)
	: CDialogEx(Rate::IDD, pParent),
	m_bShowGripper(true),
      m_szMinimum(0, 0),
      m_hGripper(NULL), m_event(NULL)
{
	res    =MT_RET_OK_NONE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	strSymbol_r=strSymbol;
	strEx_r=strEx;	
}



void Rate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RATE_LB_SCRIPNAME, m_lb_Symbol);
	DDX_Control(pDX, IDC_RATE_LB_EXCHANGE, m_lb_Ex);
	DDX_Control(pDX, IDC_RATE_LB_HEIGH, m_lb_Heigh);
	DDX_Control(pDX, IDC_RATE_LB_LOW, m_lb_Low);
	DDX_Control(pDX, IDC_BTN_RATE_BID, m_btn_bid);
	DDX_Control(pDX, IDC_BTN_RATE_ASK, m_btn_ask);
	DDX_Control(pDX, IDC_RATE_CMB_QTY, m_cmb_qty);	
	
}

BEGIN_MESSAGE_MAP(Rate, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()		
	ON_BN_CLICKED(IDC_BTN_RATE_BID, &Rate::OnBnClickedBtnRateBid)
	ON_WM_CLOSE()
END_MESSAGE_MAP()





// CTradingDlg message handlers
orderEntryForm* objentryform;
BOOL Rate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	
// use the initial dialog size as the default minimum
    if ((m_szMinimum.cx == 0) && (m_szMinimum.cy == 0))
    {
        CRect rcWindow;
        GetWindowRect(rcWindow);
        m_szMinimum = rcWindow.Size();
    }

    // keep the initial size of the client area as a baseline for moving/sizing controls
    CRect rcClient;
    GetClientRect(rcClient);
    m_szInitial = rcClient.Size();

    // create a gripper in the bottom-right corner
    if (m_bShowGripper && ((GetStyle() & WS_THICKFRAME) != 0))
    {
        SMovingChild s;
        s.m_rcInitial.SetRect(-GetSystemMetrics(SM_CXVSCROLL), -GetSystemMetrics(SM_CYHSCROLL), 0, 0);
        s.m_rcInitial.OffsetRect(rcClient.BottomRight());
        m_hGripper = CreateWindow(_T("Scrollbar"), _T("size"), WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP,
                                  s.m_rcInitial.left, s.m_rcInitial.top, s.m_rcInitial.Width(), s.m_rcInitial.Height(),
                                  m_hWnd, NULL, AfxGetInstanceHandle(), NULL);
        ASSERT(m_hGripper != NULL);
        if (m_hGripper != NULL)
        {
            s.m_hWnd = m_hGripper;
            s.m_dXMoveFrac = 1.0;
            s.m_dYMoveFrac = 1.0;
            s.m_dXSizeFrac = 0.0;
            s.m_dYSizeFrac = 0.0;
            m_MovingChildren.push_back(s);

            // put the gripper first in the z-order so it paints first and doesn't obscure other controls
            ::SetWindowPos(m_hGripper, HWND_TOP,0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
        }
    }
	m_lb_Symbol.SetWindowTextW(strSymbol_r);
	m_lb_Ex.SetWindowTextW(strEx_r);		

	
	objentryform=new orderEntryForm();
	objentryform->Create(IDD_ORDERENTRY, this);		
	/*if (tickSuscribeCheck==0)
	{*/
		DlgHelp::m_dealer->m_manager->TickSubscribe(this);  
	//}
	tickSuscribeCheck=tickSuscribeCheck+1;
	return TRUE; 
}

void Rate::set_tick_date()
{	
		MTTickShort    ticks;
		MTTickShort*   ticks_new    = new MTTickShort();
	   res=DlgHelp::m_dealer->m_manager->TickLast(strSymbol_r,ticks);
	   CString str_tick_bid=L"BID";
	   CString str_tick_ask=L"ASK";
	   CString str_tick_heigh=L"";
	   CString str_tick_low=L"";
	   str_tick_bid.Format(_T("%f"),ticks.bid );
	   str_tick_ask.Format(_T("%f"),ticks.ask );
	   m_btn_bid.SetWindowTextW(str_tick_bid);
	   m_btn_ask.SetWindowTextW(str_tick_ask);
}

void Rate::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}



void Rate::OnClose()
{	
	tickSuscribeCheck=tickSuscribeCheck-1;
	CDialog::OnCancel();
}



inline void Rate::OnTick(LPCWSTR symbol, const MTTickShort& tick)
{
	CString   strsymbol=L"";
	CString   str_sys_symbol=L"";
	m_lb_Symbol.GetWindowTextW(strsymbol);
	str_sys_symbol=symbol;
	
	if (str_sys_symbol==strsymbol)
	{
		CString strbid=L"BID";
		CString strask=L"ASK";
		strbid.Format(_T("BID \n\n %f"),tick.bid );
		strask.Format(_T("ASK \n\n %f"),tick.ask );
		m_btn_bid.SetWindowTextW(strbid);
		m_btn_ask.SetWindowTextW(strask);
		strbidDisplay=tick.ask ;
	}


	if (orderEntryForm::checkOrderForm==1)
	{		
		str_sys_symbol=symbol;
	
		if (str_sys_symbol==orderEntryForm::strSymbolcmb)
		{
			CString strbidask=L"BID";				
			strbidask.Format(_T("%f  /  %f"),tick.bid,tick.ask);
			objentryform->m_LbPrice.SetWindowTextW(strbidask);	
		}
	}


}








void Rate::OnBnClickedBtnRateBid()
{		
	CString strscmdvalue=L"";
	m_lb_Symbol.GetWindowTextW(strscmdvalue);	
	orderEntryForm::checkOrderForm=1;
	orderEntryForm::strSymbolcmb=strscmdvalue;
	objentryform->m_cmbSymbol.SetWindowTextW(strscmdvalue);
	m_cmb_qty.GetWindowTextW(strscmdvalue);	
	orderEntryForm::strqty=strscmdvalue;	
	objentryform->m_Volume.SetWindowTextW(strscmdvalue);

	//m_cmbSymbolType	
	objentryform->m_cmbSymbolType.SetWindowTextW(L"Pending Order");
	objentryform->m_cmbOrderType.SetWindowTextW(L"Buy Limit");
	CString strratedisplay=L"";
	strratedisplay.Format(_T("%f"),strbidDisplay);
	objentryform->m_Price.SetWindowTextW(strratedisplay);

	objentryform->MoveWindow( 200,100,400,450);
	objentryform->ShowWindow(SW_NORMAL);
	//objentryform->DoModal();
}


