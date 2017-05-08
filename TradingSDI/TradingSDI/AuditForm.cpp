// AuditForm.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "AuditForm.h"
#define IDC_STATICODECHANGED 10008
#define IDC_STATICNPBPSTYPE1 10009
#define IDC_STATICNPBPSTYPE2 10010
#define IDC_STATICPASSED     10011
// CAuditForm

CPassedBYMngr CAuditForm::m_passbygrid;

IMPLEMENT_DYNCREATE(CAuditForm, CFormView)

	CAuditForm::CAuditForm()
	: CFormView(CAuditForm::IDD)
{
	try
	{
		m_GridID[0] =IDC_STATICPASSED;
		m_GridID[1] =IDC_STATICNPBPSTYPE1;
		m_GridID[2] =IDC_STATICNPBPSTYPE2;
		m_GridID[3] =IDC_STATICODECHANGED;

		m_Grid[0] = new CPassedBYMngr();
		m_Grid[1] = new CNPBPSType1Grid();
		m_Grid[2] = new CNPBPSType2Grid();
		m_Grid[3] = new CCodesChanged();
	}
	catch(CMemoryException e)
	{
		AfxMessageBox(L"CAudit Form Constructor Initialization");
		throw;
	}

	m_nPageCount = 4;
	m_tabCurrent=0;
}

CAuditForm::~CAuditForm()
{
	for(int nCount=0; nCount <m_nPageCount ; nCount++)
	{
		delete m_Grid[nCount];
	}

}

void CAuditForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TABAUDIT, m_tab);
}

BEGIN_MESSAGE_MAP(CAuditForm, CFormView)
	ON_WM_CREATE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABAUDIT, &CAuditForm::OnTcnSelchangeTabaudit)
	ON_NOTIFY(TCN_FOCUSCHANGE, IDC_TABAUDIT, &CAuditForm::OnTcnFocusChangeTabaudit)
END_MESSAGE_MAP()


// CAuditForm diagnostics

#ifdef _DEBUG
void CAuditForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAuditForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAuditForm message handlers


int CAuditForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect desktop;
	GetParentFrame()->GetWindowRect(desktop);
	desktop.right =desktop.right-4;
	desktop.bottom=desktop.bottom-182;
	MoveWindow(&desktop,TRUE);


	CRect 	rect;
	GetClientRect(&rect);
	CRect rect1;
	rect1.CopyRect(rect);


	if (!m_tab.Create(WS_CHILD|WS_VISIBLE,rect1,this,IDC_TABAUDIT))
	{

		TRACE0("Failed to create Tabs in Audit Form\n");
		return -1; 
	}

	m_tab.InsertItem(1,L"PassByManager");
	m_tab.InsertItem(2,L"NBPS");
	m_tab.InsertItem(3,L"OKAY");
	m_tab.InsertItem(4,L"CodeChanged");

	InitForm();

	return 0;
}

void CAuditForm::InitForm()
{

	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;

	GetClientRect(&tabRect);
	m_tab.GetItemRect(0, &itemRect);

	nX=itemRect.left;
	nY=itemRect.bottom+1;
	nXc=tabRect.right-itemRect.left-1;
	nYc=tabRect.bottom;

	for(int nCount=0; nCount <m_nPageCount; nCount++)
	{

		if (!m_Grid[nCount]->CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,CRect(nX,nY,nXc,nYc),&m_tab,m_GridID[nCount]))
		{

			TRACE0("Failed to create AuditGrids\n");
			return ; 
		}
	}

	//Default Tab Show
	m_Grid[0]->ShowWindow(SW_SHOW);
	for(int nCount=1; nCount <m_nPageCount ; nCount++)
	{
		m_Grid[nCount]->ShowWindow(SW_HIDE);
	}

}
void CAuditForm::OnTcnSelchangeTabaudit(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if(m_tabCurrent != m_tab.GetCurSel()){
		m_Grid[m_tabCurrent]->ShowWindow(SW_HIDE);
		m_tabCurrent=m_tab.GetCurSel();
		m_Grid[m_tabCurrent]->ShowWindow(SW_SHOW);
		m_Grid[m_tabCurrent]->SetFocus();
	}

	if (DlgHelp::login_checkYN==1)
	{
		//destroying thread and start thread on tab change
		if(m_tabCurrent==0)
		{
			m_nbpsgrid2.thread_destoy();
			m_nbpsgrid1.thread_destoy();
			m_codechangegrid.thread_destoy();
			CAuditForm::m_passbygrid.data_ThreadStart();

		}
		else if(m_tabCurrent==1)
		{
			m_nbpsgrid2.thread_destoy();
			m_codechangegrid.thread_destoy();
			CAuditForm::m_passbygrid.thread_destoy();
			m_nbpsgrid1.data_ThreadStart();
		}
		else if(m_tabCurrent==2)
		{
			CAuditForm::m_passbygrid.thread_destoy();
			m_nbpsgrid1.thread_destoy();
			m_codechangegrid.thread_destoy();
			m_nbpsgrid2.data_ThreadStart();

		}
		else if(m_tabCurrent==3)
		{
			m_nbpsgrid2.thread_destoy();
			CAuditForm::m_passbygrid.thread_destoy();
			m_nbpsgrid1.thread_destoy();
			m_codechangegrid.data_ThreadStart();

		}
	}
	*pResult = 0;
}


void CAuditForm::OnTcnFocusChangeTabaudit(NMHDR *pNMHDR, LRESULT *pResult)
{

	if(m_tabCurrent != m_tab.GetCurFocus()){
		m_Grid[m_tabCurrent]->ShowWindow(SW_HIDE);
		m_tabCurrent=m_tab.GetCurFocus();
		m_Grid[m_tabCurrent]->ShowWindow(SW_SHOW);
		m_Grid[m_tabCurrent]->SetFocus();
	}

	*pResult = 0;
}
