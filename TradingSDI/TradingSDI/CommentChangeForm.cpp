// CommentChangeForm.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "CommentChangeForm.h"
#include "OutputWnd.h"

// CCommentChangeForm

IMPLEMENT_DYNCREATE(CCommentChangeForm, CFormView)

CCommentChangeForm::CCommentChangeForm()
	: CFormView(CCommentChangeForm::IDD)
{

}

CCommentChangeForm::~CCommentChangeForm()
{
}

void CCommentChangeForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCommentChangeForm, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CCommentChangeForm diagnostics

#ifdef _DEBUG
void CCommentChangeForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCommentChangeForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCommentChangeForm message handlers


int CCommentChangeForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
		COutputWnd::m_wndOutputDuplicate_Order.CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,rect,this,IDD_ORDERFORM);
		return 0;
}
