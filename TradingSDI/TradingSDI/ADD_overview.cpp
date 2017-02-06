#include "stdafx.h"
#include "TradingSDI.h"
#include "ADD_overview.h"
#include "afxdialogex.h"
#include "tabControl.h"
IMPLEMENT_DYNAMIC(ADD_overview, CDialogEx)
ADD_overview::ADD_overview(CWnd* pParent /*=NULL*/)
    : CDialogEx(ADD_overview::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_bInit = false;
    /*p1=NULL;
    p2=NULL;
    p3=NULL;
    p4=NULL;*/
}
ADD_overview::~ADD_overview()
{

}
 
void ADD_overview::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB1, m_ctrlTAB);
}
 
BEGIN_MESSAGE_MAP(ADD_overview, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
//  ON_WM_MOVE()
     
    ON_WM_CLOSE()
    ON_WM_DESTROY()
    //ON_WM_SHOWWINDOW()
    ON_NOTIFY(NM_CLICK, IDC_TAB1, &ADD_overview::OnNMClickTab1)
     
END_MESSAGE_MAP()
BOOL ADD_overview::OnInitDialog()
{
    CDialogEx::OnInitDialog();
 
    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
 
 
    // TODO: Add extra initialization here
    m_ctrlTAB.InitDialogs();
 
    m_ctrlTAB.InsertItem(0,L"OverView");
    m_ctrlTAB.InsertItem(1,L"TradeCheck");
    m_ctrlTAB.InsertItem(2,L"TradeWiseAnalysis");
    m_ctrlTAB.InsertItem(3,L"StandingPosition");
     
    return TRUE;  // return TRUE  unless you set the focus to a control
}
 
 
void ADD_overview::OnPaint() 
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
 
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR ADD_overview::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}
 
 
 
void ADD_overview::OnClose()
{
    // TODO: Add your message handler code here and/or call default 
  
    m_ctrlTAB.OnClose();
    CDialogEx::OnClose();
}
 
 
BOOL ADD_overview::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
 
 
    return CDialogEx::PreTranslateMessage(pMsg);
}
 
 
void ADD_overview::OnDestroy()
{
	/*p1->OnClose();
    p2->OnClose();
    p3->OnClose();
	p4->OnClose(); 
	delete(p1);
	delete(p2);
    delete(p3);
    delete(p4);*/
    CDialogEx::OnDestroy();
}
 
 
void ADD_overview::OnNMClickTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    //p1->ShowWindow(SW_SHOW);
    *pResult = 0;
}