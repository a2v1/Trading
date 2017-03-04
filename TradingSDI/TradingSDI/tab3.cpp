// tab3.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "tab3.h"
#include "afxdialogex.h"
#include "PosEntryAna.h"
#include "MainFrm.h"
#include "GridTradeAndOrder.h"
// tab3 dialog

IMPLEMENT_DYNAMIC(tab3, CDialogEx)

tab3::tab3(CWnd* pParent /*=NULL*/)
	: CDialogEx(tab3::IDD, pParent)
{

}

tab3::~tab3()
{
}

void tab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ClientCode);
}


BEGIN_MESSAGE_MAP(tab3, CDialogEx)
	ON_BN_CLICKED(IDOK, &tab3::OnBnClickedOk)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// tab3 message handlers
void tab3::OnClose()
{
	
	CDialog::OnClose();
}


BOOL tab3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	posEntryGrid.AttachGrid(this,IDC_STATIC_POSENTRYGRID);
	for (int f_count=0;f_count<200;f_count++)
	{
		if (CMainFrame::arrLogin[f_count]!=L"")
		{
			m_ClientCode.AddString(CMainFrame::arrLogin[f_count]);
		}
	}

	return TRUE;  
}


void tab3::OnBnClickedOk()
{
	int item_no=m_ClientCode.GetCurSel();
	CString list_code=L"";

    if (item_no!=-1)
    {
		 m_ClientCode.GetLBText(item_no,list_code);
	}
	 
	posEntryGrid.Getdata((LPCTSTR)list_code);
    posEntryGrid.RedrawAll(); 
}
