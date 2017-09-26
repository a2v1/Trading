// HelpUserCleintDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "HelpUserCleintDlg.h"
#include "afxdialogex.h"


// HelpUserCleintDlg dialog

IMPLEMENT_DYNAMIC(HelpUserCleintDlg, CDialogEx)

HelpUserCleintDlg::HelpUserCleintDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(HelpUserCleintDlg::IDD, pParent)
{

}

HelpUserCleintDlg::~HelpUserCleintDlg()
{
}

void HelpUserCleintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HelpUserCleintDlg, CDialogEx)
END_MESSAGE_MAP()


// HelpUserCleintDlg message handlers


BOOL HelpUserCleintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_HelpGrid.AttachGrid(this,IDC_STATIC_GRID);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
