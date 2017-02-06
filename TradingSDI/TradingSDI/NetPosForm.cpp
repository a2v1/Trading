// NetPosForm.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "NetPosForm.h"
#include "OutputWnd.h"


// CNetPosForm

IMPLEMENT_DYNCREATE(CNetPosForm, CFormView    )

CNetPosForm::CNetPosForm()
	: CFormView(CNetPosForm::IDD)
{

}

CNetPosForm::~CNetPosForm()
{
}

void CNetPosForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNetPosForm, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CNetPosForm diagnostics

#ifdef _DEBUG
void CNetPosForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CNetPosForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CNetPosForm message handlers


int CNetPosForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
		COutputWnd::m_wndOutputPos.CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,rect,this,IDD_NETPOSFORM);
		return 0;
}
