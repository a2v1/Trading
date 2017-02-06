// OrderwiseJournal.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "OrderwiseJournal.h"
#include "afxdialogex.h"
#include "Login.h"

// COrderwiseJournal dialog
Editable_Grid COrderwiseJournal::e_grid;
IMPLEMENT_DYNAMIC(COrderwiseJournal, CDialogEx)
CString COrderwiseJournal::odno=L"";
COrderwiseJournal::COrderwiseJournal(CWnd* pParent /*=NULL*/)
	: CDialogEx(COrderwiseJournal::IDD, pParent)
{

}

COrderwiseJournal::~COrderwiseJournal()
{
}

BOOL COrderwiseJournal::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	
	
	
	e_grid.AttachGrid(this ,IDC_STATIC);
	e_grid.SetColWidth(0,150);
	e_grid.SetColWidth(1,800);
	e_grid.QuickSetText(0,-1,L"TIME");
	e_grid.QuickSetText(1,-1,L"MESSAGE");

	if (COrderwiseJournal::odno.GetLength()>0)
	{	
		
		INT64       server_time      = DlgHelp::m_dealer->m_manager->TimeServer();
		INT64       to               = server_time;
		INT64       from               = server_time;
		//INT64       from             = server_time-(60*60*24*8);
		DlgHelp::m_dealer->getJournal_order(from,to,COrderwiseJournal::odno);
	
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}



void COrderwiseJournal::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COrderwiseJournal, CDialogEx)
END_MESSAGE_MAP()


// COrderwiseJournal message handlers
