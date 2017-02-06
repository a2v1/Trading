
// TradingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Trading.h"
#include "TradingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
Login::Login(CWnd* pParent /*=NULL*/)
	: CDialogEx(Login::IDD, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Login, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()		
	ON_BN_CLICKED(IDC_BTN_LOGIN, &Login::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BTN_EXIT, &Login::OnBnClickedBtnExit)
END_MESSAGE_MAP()


// CTradingDlg message handlers

BOOL Login::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Password=(CEdit*)GetDlgItem(IDC_LOGIN_EDIT_PWD);	
	m_Loginname=(CEdit*)GetDlgItem(IDC_LOGIN_EDIT_LOGIN);



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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}



void Login::OnPaint()
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







void Login::OnBnClickedBtnLogin()
{
	 //TODO: Add your control notification handler code here
	CString login;
   CString password;
   CString server;
//---
   server=L"69.64.74.136";
   m_Loginname->GetWindowText(login);   
   m_Password->GetWindowText(password);    
//--- dealer starting
   /*if(!m_dealer.Start(server,_wtoi64(login),password))
     {
      AfxMessageBox(L"Login fail");
      return;
     }*/

    if( m_dealer.m_manager->Connect(server,_wtoi64(login),password,L"",0xffffffff,INFINITE))
     {
      AfxMessageBox(L"Login fail");
      return;
	  
     }
           





	
	CTradingDlg* dlg = new CTradingDlg(login,password);
	
	CDialog::OnCancel();
	dlg->DoModal();
	
	 
   
}


void Login::OnBnClickedBtnExit()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}




