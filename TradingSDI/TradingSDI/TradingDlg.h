
// TradingDlg.h : header file
//

#pragma once
#include "Dealer.h"

#include "Outputwnd.h"

// CTradingDlg dialog
class CTradingDlg : public CDialogEx 
{
// Construction
	
private:
	IMTRequest       *m_request;
	IMTConfirm       *m_confirm;
	CComboBox		 *cmb_login;
	
public:
	MyCug*	m_ctrl;
	CTradingDlg(CWnd* pParent = NULL);	// standard constructor	
	CTradingDlg(CString login,CString pwd);

// Dialog Data
	enum { IDD = IDD_TRADING_DIALOG };

	protected:
	COutputWnd        m_wndOutput;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void  add_LoginToCombobox();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButOrder();
	
};
