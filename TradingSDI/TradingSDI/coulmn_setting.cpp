// coulmn_setting.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "coulmn_setting.h"
#include "afxdialogex.h"


// coulmn_setting dialog

IMPLEMENT_DYNAMIC(coulmn_setting, CDialogEx)

coulmn_setting::coulmn_setting(CWnd* pParent /*=NULL*/)
	: CDialogEx(coulmn_setting::IDD, pParent)
{

}

coulmn_setting::~coulmn_setting()
{
}

void coulmn_setting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(coulmn_setting, CDialogEx)
END_MESSAGE_MAP()


// coulmn_setting message handlers


BOOL coulmn_setting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	grid.AttachGrid(this ,IDC_STATIC_COLUMN_GRID);
	
	grid.QuickSetText(1,-1,L"Show Nd Hide Column ");
	grid.SetColWidth(1,130);

	grid.QuickSetText(0,-1,L"Column Name");
	grid.SetColWidth(0,120);

	return TRUE;  // return TRUE unless you set the focus to a control

}
