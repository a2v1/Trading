#pragma once

#include "HelpUserCleintGrid.h"
// HelpUserCleintDlg dialog

class HelpUserCleintDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HelpUserCleintDlg)

public:
	HelpUserCleintDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~HelpUserCleintDlg();

// Dialog Data
	enum { IDD = IDD_HELPUSERCLEINT };

	HelpUserCleintGrid m_HelpGrid;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
