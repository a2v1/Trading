// OrderForm.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "OrderForm.h"
#include "OutputWnd.h"


// COrderForm
ScripWiseNetPos COrderForm::m_GridScripWise;

IMPLEMENT_DYNCREATE(COrderForm, CFormView)

COrderForm::COrderForm()
	: CFormView(COrderForm::IDD)
{

}

COrderForm::~COrderForm()
{
}

void COrderForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COrderForm, CFormView)
	ON_WM_CREATE()	
END_MESSAGE_MAP()


// COrderForm diagnostics

#ifdef _DEBUG
void COrderForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void COrderForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// COrderForm message handlers


int COrderForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;	


		CRect desktop;

		GetParentFrame()->GetWindowRect(desktop);
		desktop.right =desktop.right-4;
		desktop.bottom=desktop.bottom-75;

		MoveWindow(&desktop,TRUE);		

		CRect 	rect;
		GetClientRect(&rect);
		COutputWnd::m_wndOutputOrder.CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,rect,this,IDD_ORDERFORM);

		return 0;
}




void COrderForm::OnInitialUpdate()
{
	 CFormView::OnInitialUpdate();	
	
}