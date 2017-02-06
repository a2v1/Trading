#pragma once
#include "afxwin.h"
#include "dealing.h"
#include "ugctrl.h"

// clr_setting dialog

class clr_setting : public CDialogEx
{
	DECLARE_DYNAMIC(clr_setting)

public:
	clr_setting(CWnd* pParent = NULL);   // standard constructor
	virtual ~clr_setting();

// Dialog Data
	enum { IDD = IDD_DLG_CLR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	DECLARE_MESSAGE_MAP()
public:
	

	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonClr();
	afx_msg void OnCbnSelchangeComboClr();
	virtual BOOL OnInitDialog();
	CComboBox m_combo;
	CMFCButton btn_color;
};
