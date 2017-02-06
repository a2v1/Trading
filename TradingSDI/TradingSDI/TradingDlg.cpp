
// TradingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Trading.h"
#include "TradingDlg.h"
#include "afxdialogex.h"
#include "Rate.h"
#include "Login.h"
#include <string.h>
#include <iostream>
#include <iomanip>
#include <sstream>




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About
int Pos_x=10;
int Pos_y=80;
int Panal=0;
CString Login_user=L"";
CString pwd_user=L"";

CDealer  m_dealer;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_TRADING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}



void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTradingDlg dialog



CTradingDlg::CTradingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTradingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CTradingDlg::CTradingDlg(CString login,CString   pwd): CDialogEx(CTradingDlg::IDD)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Login_user=login;
	pwd_user=pwd;
}

void CTradingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTradingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_BN_CLICKED(IDC_BUT_ORDER, &CTradingDlg::OnBnClickedButOrder)
END_MESSAGE_MAP()


// CTradingDlg message handlers

BOOL CTradingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ShowWindow(SW_MAXIMIZE);



	cmb_login=(CComboBox*)GetDlgItem(IDC_CMB_ACCOUNT);

	//--- initialize dealer
   if(!m_dealer.Initialize(this))
     {
      EndDialog(IDCANCEL);
      return(FALSE);
     }
//--- create IMTRequest object
   m_request=m_dealer.RequestCreate();
   if(!m_request)
     {
      AfxMessageBox(L"Failed to create interface.");
      EndDialog(IDCANCEL);
      return(FALSE);
     }
//--- create IMTConfirm object
   m_confirm=m_dealer.ConfirmCreate();
   if(!m_confirm)
     {
      AfxMessageBox(L"Failed to create interface.");
      EndDialog(IDCANCEL);
      return(FALSE);
     }
//---
   if( m_dealer.m_manager->Connect(L"69.64.74.136",_wtoi64(Login_user),pwd_user,L"",0xffffffff,INFINITE))
     {
      //AfxMessageBox(L"Login fail");
      return TRUE ;	  
     }











	//Creating Panel
  
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndOutput);
	//Updating Panel












	add_LoginToCombobox();
	m_ctrl=new MyCug(L"Hello");
	m_ctrl->AttachGrid(this, IDC_Grid_Position);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTradingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTradingDlg::OnPaint()
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





void CTradingDlg::OnBnClickedButOrder()
{
	
	// TODO: Add your control notification handler code here
	Rate* dlg = new Rate();
	CDialog* dlgRate;
	dlgRate=(CDialog*)GetDlgItem(IDD_DIALOG_RATEPANAL);	
	dlg->Create(IDD_DIALOG_RATEPANAL, this);
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

 void CTradingDlg::add_LoginToCombobox()
{	
	
	IMTConGroup *group=m_dealer.m_manager->GroupCreate();
        for(UINT i=0;m_dealer.m_manager->GroupNext(i,group)==MT_RET_OK;i++)
          {
           UINT64 *logins=NULL;
           UINT    logins_total=0;
           if(m_dealer.m_manager->UserLogins(group->Group(),logins,logins_total)==MT_RET_OK)
             {
              if(logins && logins_total)
                for(UINT j=0;j<logins_total;j++)
                  {
                   IMTPositionArray *positions=m_dealer.m_manager->PositionCreateArray();
                   
                   if(m_dealer.m_manager->PositionGet(logins[j],positions)==MT_RET_OK)
                         wprintf_s(L"%I64u - %u position(s)\n",logins[j],positions->Total());
                   else  wprintf_s(L"%I64u - failed request position(s)\n",logins[j]);
                   
                   positions->Release();
					  UINT64 INTLOGIN=logins[j];
					  
					  CString  pstrLogin=L"";
					  pstrLogin.Format( _T("%d"),INTLOGIN);
					  
					  cmb_login->AddString(pstrLogin);
					  
                  }
              //--- чистим
              if(logins) { m_dealer.m_manager->Free(logins); logins=NULL; }
              logins_total=0;
             }
          }
        group->Release();
}
//
 
 