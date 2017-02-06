#pragma once
#include "afxwin.h"


// change_comment dialog

class change_comment : public CDialogEx
{
	DECLARE_DYNAMIC(change_comment)

public:
	change_comment(CWnd* pParent = NULL);   // standard constructor
	virtual ~change_comment();
	BOOL OnInitDialog();
// Dialog Data
	enum { IDD = IDD_CHNGE_COMMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnEnChangeEdit15();
	CEdit m_time;
	CEdit m_deal;
	CEdit m_order;
	CEdit m_symbol;
	
	CEdit m_type;
	CEdit m_volume;
	CEdit m_price;
	CEdit m_comment;
	
	afx_msg void OnBnClickedOk();
};
