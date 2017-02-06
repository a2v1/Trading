#pragma once
#include "PosEntryAna.h"
#include "afxwin.h"

// tab3 dialog

class tab3 : public CDialogEx
{
	DECLARE_DYNAMIC(tab3)

public:
	tab3(CWnd* pParent = NULL);   // standard constructor
	virtual ~tab3();

// Dialog Data
	enum { IDD = IDD_TAB3 };
	static int m_selectedclient;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	PosEntryAna posEntryGrid;
public:
	afx_msg void OnClose();	
	virtual BOOL OnInitDialog();
	CComboBox m_ClientCode;
	afx_msg void OnBnClickedOk();
};
