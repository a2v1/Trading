#pragma once
#ifndef over_HEADER
#define over_HEADER
#include "afxwin.h"
#include "afxcmn.h"
#include "overview.h"
#include "afxwin.h"
#include "GridTradeAndOrder.h"
#include "OverViewOrderGrid.h"
#include "CTrade_Table.h"
#include "afxdtctl.h"
#include "Grid_CheckTrade.h"
#include  "tabControl.h"

// overview dialog

class overview : public CDialogEx
{
	DECLARE_DYNAMIC(overview)

public:

	

	overview(CWnd* pParent = NULL);   // standard constructor
	virtual ~overview();

// Dialog Data
	enum { IDD = IDD_TAB1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	void get_client_details();
	int checked_val;
	GridTradeAndOrder Tradegrid ;
	OverViewOrderGrid Ordergrid;
	CWinThread* m_pThreads;
    CWinThread* m_order_pThreads;

	static CDataSource connection;
	static CSession session;
	static CCommand<CAccessor<CTrade_Table>> artists1;
	static int chcekinitialize;

	LRESULT UpdateData(WPARAM, LPARAM);

	static CString total_trade;
	static CString last_trade_time;
	static CString trade_per;
	static CString balance;
	static CString profit;
	static CString Margin;

	afx_msg void OnBnClickedCheck1();
	CEdit m_accountnumber;
	CEdit m_accountname;
	CEdit m_masteraccount;
	CEdit m_history;
	CEdit m_nooftrade;
	CEdit m_lasttrade;
	CEdit m_percentageoftrade;
	CEdit m_txtProfit;
	CEdit m_txtBalance;
	CEdit m_txtMargin;
	CEdit m_txtGroup1;
	CEdit m_txtGroup2;
	CEdit m_txtGroup3;
	CEdit m_txtGroup4;
	CEdit m_txtCredit;
	CEdit m_txtName;
	CButton m_ignoreclient;
	CButton m_commentwise;

	afx_msg void OnIdclose();
	afx_msg void OnClose();	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
//	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedStaticFrgridTrade2();
};
#endif