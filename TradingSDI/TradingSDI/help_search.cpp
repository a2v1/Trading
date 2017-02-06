// help_search.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "help_search.h"
#include "afxdialogex.h"
#include "helpserach_grid.h"

// help_search dialog

IMPLEMENT_DYNAMIC(help_search, CDialogEx)

help_search::help_search(CWnd* pParent /*=NULL*/)
	: CDialogEx(help_search::IDD, pParent)
{

}

help_search::~help_search()
{
}

void help_search::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(help_search, CDialogEx)
END_MESSAGE_MAP()


// help_search message handlers


BOOL help_search::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	help_grid.AttachGrid(this ,IDC_STATIC_HELP);
	help_grid.SetColWidth(0,140);
	help_grid.SetColWidth(1,140);
	
	
	help_grid.QuickSetText(0,-1,L"SYMBOL");
	help_grid.QuickSetText(1,-1,L"MARGIN");
	
		


	return TRUE;  // return TRUE unless you set the focus to a control

}
