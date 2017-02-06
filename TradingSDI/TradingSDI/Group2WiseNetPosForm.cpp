// Group2WiseNetPosForm.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "Group2WiseNetPosForm.h"
#include "OutputWnd.h"


// CGroup2WiseNetPosForm

IMPLEMENT_DYNCREATE(CGroup2WiseNetPosForm, CFormView)

CGroup2WiseNetPosForm::CGroup2WiseNetPosForm()
	: CFormView(CGroup2WiseNetPosForm::IDD)
{

}

CGroup2WiseNetPosForm::~CGroup2WiseNetPosForm()
{
}

void CGroup2WiseNetPosForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGroup2WiseNetPosForm, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CGroup2WiseNetPosForm diagnostics

#ifdef _DEBUG
void CGroup2WiseNetPosForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGroup2WiseNetPosForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGroup2WiseNetPosForm message handlers


int CGroup2WiseNetPosForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
		COutputWnd::m_AnalysisGrid.CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,rect,this,1234);
		CenterWindow();

		return 0;
}
