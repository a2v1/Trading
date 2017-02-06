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

IMPLEMENT_DYNCREATE(CAuditForm, CFormView)

CAuditForm::CAuditForm()
	: CFormView(CAuditForm::IDD)
{
  
}

CAuditForm::~CAuditForm()
{
	
}

void CAuditForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CAuditForm, CFormView)
	ON_WM_CREATE()
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
		CRect rect1,rect2,rect3,rect4;
		rect1.CopyRect(rect);
		
		rect1.bottom=rect1.bottom-450;               
	   if (!m_passedbymngrGrid.CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,rect1,this,IDC_STATICPASSED))
	   {
			     
				TRACE0("Failed to create PassedBYGrid\n");
				return -1; 
       }	

	   rect2.CopyRect(rect);
	   rect2.top=rect1.bottom;
	   rect2.bottom=rect2.bottom-300;
	   if (!m_npbpstype1grid.CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,rect2,this,IDC_STATICNPBPSTYPE1))
	   {
				TRACE0("Failed to create CodeChangedGrid\n");
				return -1; 
       }

       rect3.CopyRect(rect);
	   rect3.top=rect2.bottom;
	   rect3.bottom=rect3.bottom-150;
	   if (!m_npbpstype2grid.CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,rect3,this,IDC_STATICNPBPSTYPE2))
	   {
				TRACE0("Failed to create Type1 Grid\n");
				return -1; // fail to create
       }

	   rect4.CopyRect(rect);
	   rect4.top=rect3.bottom;
	   rect4.bottom=rect4.bottom;
	   if (!m_CodeChangGrid.CreateGrid(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,rect4,this,IDC_STATICODECHANGED))
	   {
				TRACE0("Failed to create Type2 Grid\n");
				return -1; // fail to create
       }


	   return 0;
}
