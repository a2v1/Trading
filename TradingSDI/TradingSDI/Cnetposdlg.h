#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// Cnetposdlg dialog

class Cnetposdlg : public CDialogEx
{
	DECLARE_DYNAMIC(Cnetposdlg)

public:
	Cnetposdlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~Cnetposdlg();

// Dialog Data
	enum { IDD = IDD_NETPOS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_igqty;//ignore quantity
	CEdit m_login;
	CEdit m_group;
	CDateTimeCtrl m_date;
	//CEdit m_net;
	CButton m_igmain;//ignore main
	CButton ig_comment;
	Cnetposdlg *pDlg;
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedIgqty();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedIgcomment();
};
