// DealingForm.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "DealingForm.h"
#include <atltypes.h>
//#include "bpctrlanchormap.h"
#include "OutputWnd.h"

// CDealingForm

IMPLEMENT_DYNCREATE(CDealingForm, CFormView)

CDealingForm::CDealingForm()
	: CFormView(CDealingForm::IDD)
{

}

CDealingForm::~CDealingForm()
{
}

void CDealingForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDealingForm, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDealingForm diagnostics

#ifdef _DEBUG
void CDealingForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDealingForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

int CDealingForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	COutputWnd::m_wndOutputDeal.CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,rect,this,1234);
	CenterWindow();
	return 0;
}


void CDealingForm::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);	              
}
