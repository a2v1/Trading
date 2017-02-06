// GroupWiseNetPosForm.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "GroupWiseNetPosForm.h"
#include "OutputWnd.h"


// CGroupWiseNetPosForm

IMPLEMENT_DYNCREATE(CGroupWiseNetPosForm, CFormView)

CGroupWiseNetPosForm::CGroupWiseNetPosForm()
	: CFormView(CGroupWiseNetPosForm::IDD)
{

}

CGroupWiseNetPosForm::~CGroupWiseNetPosForm()
{
}

void CGroupWiseNetPosForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGroupWiseNetPosForm, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CGroupWiseNetPosForm diagnostics

#ifdef _DEBUG
void CGroupWiseNetPosForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGroupWiseNetPosForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGroupWiseNetPosForm message handlers


int CGroupWiseNetPosForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
		COutputWnd::m_GroupWiseNetPos.CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,rect,this,1234);
		CenterWindow();
		return 0;
}
