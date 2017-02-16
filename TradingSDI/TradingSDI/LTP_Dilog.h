#pragma once
#include "LTPupdate.h"

// LTP_Dilog dialog

class LTP_Dilog : public CDialogEx
{
	DECLARE_DYNAMIC(LTP_Dilog)

public:
	LTP_Dilog(CWnd* pParent = NULL);   // standard constructor
	virtual ~LTP_Dilog();
	LTPupdate ltp_grid;
	
// Dialog Data
	enum { IDD = IDD_DIALOG_LTP };
	
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedStaticLtp();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
};
