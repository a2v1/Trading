#pragma once
#include "stdafx.h"
#include "TradingSDI.h"
#include "MainFrm.h"
#include "AddScrip.h"
#include "Dealer.h"
#include "OrderForm.h"

class DlgHelp : public CDialogEx
{
	public:
		DlgHelp();	

// Dialog Data
		enum { IDD = IDD_Login_Form};
	
		

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);
		virtual void add_LoginToCombobox();
		BOOL OnInitDialog();
		//BOOL PreTranslateMessage(MSG* pMsg);// DDX/DDV support


		CEdit*            m_Password;
		CEdit*            m_Loginname;   
		//CEdit*            m_Server;  
		CButton*          m_Logout;
		CButton*          m_Login;   
		HICON             m_hIcon;

	//data base initilization objects
	CDataSource connection;
	CSession session;
	HRESULT hr;
  
   //CMainFrame		mainF;
// Implementation
protected:
	afx_msg void OnClose();	
	DECLARE_MESSAGE_MAP()	
	afx_msg void OnIdok();
	afx_msg void OnIdcancel();
	
public:
		//static IMTRequest       *m_request;
		//static IMTConfirm       *m_confirm;
		//static CDealer           m_dealer;
		IMTConfirm       *m_confirm;
		IMTRequest       *m_request;
		static CDealer           *m_dealer;
		static int login_checkYN ;
		

	afx_msg void OnBnClickedBtnLogin();
	afx_msg void OnBnClickedBtnExit();
	
};
