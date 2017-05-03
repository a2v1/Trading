
#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "TradingSDI.h"
#endif
#include "TradingSDIDoc.h"
#include "TradingSDIView.h"
#include "resource.h"
#include "symbol_grp.h"
#include "define_margin.h"
#include "ClientCreate.h"
#include "OrderForm.h"
#include "NetPosForm.h"
#include "NetPosGrid.h"
#include "CommentChangeForm.h"
#include "DealingForm.h"
#include "Group2WiseNetPosForm.h"
#include "GroupWiseNetPosForm.h"
#include "AuditForm.h"
#include "OutputWnd.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CTradingSDIView, CTabView)
	
BEGIN_MESSAGE_MAP(CTradingSDIView, CTabView)
	// Standard printing commands
	ON_WM_CREATE()	
	ON_REGISTERED_MESSAGE(AFX_WM_CHANGE_ACTIVE_TAB, &CTradingSDIView::OnAfxWmChangingActiveTab)
END_MESSAGE_MAP()
CTradingSDIView::CTradingSDIView()
{
	// TODO: add construction code here
	
}
CTradingSDIView::~CTradingSDIView()
{
}
BOOL CTradingSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CTabView::PreCreateWindow(cs);
}

// CTradingSDIView drawing

void CTradingSDIView::OnDraw(CDC* pDC)
{
	
	/*const CString str("Hello");
    pDC->TextOut(0, 0, str);	 */

}

int CTradingSDIView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;
	    CMFCTabCtrl m_tab;
		CRect m_rect;
		m_rect.SetRectEmpty();
		m_tab.DestroyWindow();
		m_tab.Create(CMFCTabCtrl::STYLE_3D_VS2005,m_rect,this,1,CMFCTabCtrl::LOCATION_TOP);
		m_tab.EnableTabSwap(false);
		
		

		AddView(RUNTIME_CLASS(COrderForm),_T("Order"),0);
		AddView(RUNTIME_CLASS(CNetPosForm),_T("NetPosition"),1);
		AddView(RUNTIME_CLASS(CCommentChangeForm),_T("CommentChange"),2);
		AddView(RUNTIME_CLASS(CDealingForm),_T("Dealing"),3);
		AddView(RUNTIME_CLASS(CGroup2WiseNetPosForm),_T("Group2WiseNetPos"),4);
		AddView(RUNTIME_CLASS(CGroupWiseNetPosForm),_T("GroupWiseNetPos"),5);
		AddView(RUNTIME_CLASS(CAuditForm),_T("Audit"),6);


		//SetActiveView(1);
		//AfxMessageBox(L"CTradingSDIView::OnCreate");
	return 0;
}

// CTradingSDIView diagnostics
LRESULT CTradingSDIView::OnAfxWmChangingActiveTab(WPARAM wParam, LPARAM lParam)
{
	CMFCTabCtrl* pTab = (CMFCTabCtrl*)lParam;
	
	CWnd *pWnd = pTab->GetActiveWnd();

	int i=pTab->GetActiveTab();

	if(i==0)
	{
	 NetPosGrid::Data_Update=0;
	 onDestoyNetposThread();
	}
	else if(i==1)
	{
		NetPosGrid::Data_Update=1;
		COutputWnd::m_wndOutputPos.Thread_start_st_netpos_update();	
	}

	else if(i==2)
	{
		 NetPosGrid::Data_Update=0;
		 onDestoyNetposThread();
	}
	else if(i==3)
	{
		 NetPosGrid::Data_Update=0;
		 onDestoyNetposThread();
	}
	else if(i==4)
	{
		NetPosGrid::Data_Update=0;
		onDestoyNetposThread();
	}
	else if(i==5)
	{
		NetPosGrid::Data_Update=0;
		onDestoyNetposThread();
	}
	else if(i==6)
	{
		NetPosGrid::Data_Update=0;
		onDestoyNetposThread();
	}
	return 0;
}


void CTradingSDIView::OnActivateView(CView* view)
{
	
	
}


void CTradingSDIView::onDestoyNetposThread()
{
	try 
	{				
		DWORD exit_code= NULL;
		if (COutputWnd::m_wndOutputPos.m_pThreads != NULL)
		{
			if(WaitForSingleObject(COutputWnd::m_wndOutputPos.m_pThreads->m_hThread,INFINITE) == WAIT_OBJECT_0) 
			{
				GetExitCodeThread(COutputWnd::m_wndOutputPos.m_pThreads->m_hThread, &exit_code);
				if(exit_code == STILL_ACTIVE)
				{
					::TerminateThread(COutputWnd::m_wndOutputPos.m_pThreads->m_hThread, 0);
					CloseHandle(COutputWnd::m_wndOutputPos.m_pThreads->m_hThread);
				}
				//COutputWnd::m_wndOutputPos.m_pThreads->m_hThread = NULL;
				COutputWnd::m_wndOutputPos.m_pThreads = NULL;
			}
		}
	}
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"Thread UnInitiliaze");			
	}
}

#ifdef _DEBUG



CTradingSDIDoc* CTradingSDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTradingSDIDoc)));
	//AfxMessageBox(L"CTradingSDIView::GetDocument()");
	return (CTradingSDIDoc*)m_pDocument;
}


#endif 

