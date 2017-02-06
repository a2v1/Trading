
// TradingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AddScrip.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "Rate.h"
#include "orderEntryForm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CString  AddScrip::strclient=L"";
AddScrip::AddScrip(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddScrip::IDD, pParent),
	m_bShowGripper(true),
      m_szMinimum(0, 0),
      m_hGripper(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void AddScrip::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCRIP_CMB_LOGIN, cmb_login);
	DDX_Control(pDX, IDC_SCRIP_EDIT_LOGIN, edit_name);
	DDX_Control(pDX, IDC_SCRIP_CMB_SYMBOL, cmb_Scrip);
	
	

}

BEGIN_MESSAGE_MAP(AddScrip, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	
	ON_BN_CLICKED(IDC_SCRIP_BTN_LOGIN, &AddScrip::OnBnClickedScripBtnLogin)
	ON_CBN_SELCHANGE(IDC_SCRIP_CMB_LOGIN, &AddScrip::OnCbnSelchangeScripCmbLogin)
	ON_CBN_EDITCHANGE(IDC_SCRIP_CMB_LOGIN, &AddScrip::OnCbnEditchangeScripCmbLogin)
	ON_CBN_SELENDOK(IDC_SCRIP_CMB_LOGIN, &AddScrip::OnCbnEditchangeScripCmbLogin)	
	ON_BN_CLICKED(IDC_BUTTON1, &AddScrip::OnBnClickedButton1)	
	
END_MESSAGE_MAP()


// CTradingDlg message handlers

BOOL AddScrip::OnInitDialog()
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

	
	
	
	for (int f_count=0;f_count<200;f_count++)
	{
		if (CMainFrame::arrLogin[f_count]!=L"")
		{
			cmb_login.AddString(CMainFrame::arrLogin[f_count]);
		}
		if (CMainFrame::arrScrip[f_count]!=L"")
		{
			cmb_Scrip.AddString(CMainFrame::arrScrip[f_count]);
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}



void AddScrip::OnPaint()
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






int Pos_x=0;
int Pos_y=90;
int Panal=0;

void AddScrip::OnBnClickedScripBtnLogin()
{
	
	// TODO: Add your control notification handler code here
	CString strSymbol=L"";
	cmb_Scrip.GetWindowTextW(strSymbol);
	CString strEx=L"MCX";
	Rate* dlg = new Rate(strSymbol,strEx);
	CDialog* dlgRate;
	dlgRate=(CDialog*)GetDlgItem(IDD_DIALOG_RATE);	
	dlg->Create(IDD_DIALOG_RATE, this);
	//dlg->SetWindowPos(NULL, 0,Pos,0,0, SWP_NOZORDER | SWP_NOMOVE | SWP_SHOWWINDOW);
	dlg->MoveWindow( Pos_x,Pos_y,300,250);
	dlg->ShowWindow(SW_NORMAL);
	 Pos_x=Pos_x+310;
	 Panal=Panal+1;
	 if (Panal==4)
	 {
		 Panal=0;
		 Pos_y =Pos_y+255;
		 Pos_x=10;
	 }
}


int arrayItemIndex(CString arr[200],CString item)
{
	for (int for_count=0;for_count<200;for_count++)
	{
		if (item==arr[for_count])
		{
			return for_count;
		}
	}
	return 199;
}

void AddScrip::setLoginName()
{
	edit_name.SetWindowTextW(L"");
	short cIndex;
	strclient=L"";
	CString fontName;
	cIndex=cmb_login.GetCurSel();
	if (cIndex>=0)
	{
	
	cmb_login.GetLBText(cIndex,fontName);  
	strclient=fontName;
	CString Loginname=CMainFrame::arrLogin_Name[arrayItemIndex(CMainFrame::arrLogin,fontName)];	
	edit_name.SetWindowTextW(Loginname);
	}
	else
	{		
			cmb_login.GetWindowTextW(fontName) ;
			CString Loginname=CMainFrame::arrLogin_Name[arrayItemIndex(CMainFrame::arrLogin,fontName)];	
			edit_name.SetWindowTextW(Loginname);		
			strclient=fontName;
	}

	//cmb_login
}
void AddScrip::OnCbnSelchangeScripCmbLogin()
{
	setLoginName();
}





void AddScrip::OnCbnEditchangeScripCmbLogin()
{
	// TODO: Add your control notification handler code here
	setLoginName();
}




void AddScrip::OnBnClickedButton1()
{
	/*orderEntryForm* objentryform=new orderEntryForm();
	objentryform->Create(IDD_ORDERENTRY, this);		
	objentryform->MoveWindow( 500,200,300,250);
	objentryform->ShowWindow(SW_NORMAL);*/

}





