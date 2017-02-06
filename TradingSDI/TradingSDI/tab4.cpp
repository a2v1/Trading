// tab4.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "tab4.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "GridTradeAndOrder.h"

// tab4 dialog

IMPLEMENT_DYNAMIC(tab4, CDialogEx)

tab4::tab4(CWnd* pParent /*=NULL*/)
	: CDialogEx(tab4::IDD, pParent)
{

}

tab4::~tab4()
{
}

void tab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_clientcombo);
}


BEGIN_MESSAGE_MAP(tab4, CDialogEx)
	ON_BN_CLICKED(IDOK, &tab4::OnBnClickedOk)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// tab4 message handlers

void tab4::OnClose()
{
	
	CDialog::OnClose();
}

BOOL tab4::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Balance_Grid.AttachGrid(this,IDC_STATIC_BALANCE_TABLE);
	Balance_Grid.GetData(GridTradeAndOrder::m_selected_login);

	for (int f_count=0;f_count<200;f_count++)
	{
		if (CMainFrame::arrLogin[f_count]!=L"")
		{
			m_clientcombo.AddString(CMainFrame::arrLogin[f_count]);
		}
	}

	return TRUE; 
}


void tab4::OnBnClickedOk()
{
	int item_no=m_clientcombo.GetCurSel();

	if (item_no!=-1)
    {
		m_clientcombo.GetLBText(item_no,(LPTSTR)GridTradeAndOrder::m_selected_login);
	}
	 
	Balance_Grid.GetData(GridTradeAndOrder::m_selected_login);
	Balance_Grid.RedrawAll();
}
