// JournalSearch.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "JournalSearch.h"
#include "afxdialogex.h"
#include "Login.h"

// CJournalSearch dialog

IMPLEMENT_DYNAMIC(CJournalSearch, CDialogEx)

CJournalSearch::CJournalSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJournalSearch::IDD, pParent)
{

}

CJournalSearch::~CJournalSearch()
{
}

void CJournalSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_datefrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dateto);	
	DDX_Control(pDX,IDC_BUTTON1,m_btnsearch);
}


BEGIN_MESSAGE_MAP(CJournalSearch, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON1, &CJournalSearch::OnBnClickedButton1)
END_MESSAGE_MAP()

BOOL CJournalSearch::OnInitDialog()
{
	CDialog::OnInitDialog();	
	m_datefrom.SetFormat(L"dd-MM-yyyy");
	m_dateto.SetFormat(L"dd-MM-yyyy");
	return true;
}

BOOL CJournalSearch::OnEraseBkgnd(CDC* pDC)
{
    CRect rect;
    GetClientRect(&rect);
    CBrush myBrush(RGB(255, 255, 255));    // dialog background color
    CBrush *pOld = pDC->SelectObject(&myBrush);
    BOOL bRes  = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
    pDC->SelectObject(pOld);    // restore old brush
    return bRes;                       // CDialog::OnEraseBkgnd(pDC);
}

void CJournalSearch::OnBnClickedButton1()
{
	m_btnsearch.EnableWindow(false);
	SYSTEMTIME dfrom,dto;
	m_datefrom.GetTime(&dfrom);
	m_dateto.GetTime(&dto);	
	DlgHelp::m_dealer->getJournal(dfrom,dto);
	m_btnsearch.EnableWindow(true);
}
