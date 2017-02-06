#pragma once
#include "BalanceAnaGrid.h"
#include "afxwin.h"

// tab4 dialog

class tab4 : public CDialogEx
{
	DECLARE_DYNAMIC(tab4)

public:
	tab4(CWnd* pParent = NULL);   // standard constructor
	virtual ~tab4();

// Dialog Data
	enum { IDD = IDD_TAB4 };
public:
	BalanceAnaGrid  Balance_Grid;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_clientcombo;
	afx_msg void OnClose();	
	afx_msg void OnBnClickedOk();
};
