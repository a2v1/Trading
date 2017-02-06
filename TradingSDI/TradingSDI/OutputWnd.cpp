#include "stdafx.h"
#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "Login.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar
//MyCug*  COutputWnd::m_wndOutputPos= new MyCug();

//MyCug*  COutputWnd::m_wndOutputDeal= new MyCug();
OrderGrid  COutputWnd::m_wndOutputOrder;
NetPosGrid COutputWnd::m_wndOutputPos;
Dealing COutputWnd::m_wndOutputDeal;
Duplicate_Order  COutputWnd::m_wndOutputDuplicate_Order;

GroupWise2NetPos COutputWnd::m_AnalysisGrid;
GroupWiseNetPos COutputWnd::m_GroupWiseNetPos;

COutputWnd::COutputWnd()
{
}

COutputWnd::~COutputWnd()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	//CRect rectDummy;
	//rectDummy.SetRectEmpty();		


	//// Create tabs window:
	//if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	//{
	//	TRACE0("Failed to create output tab window\n");
	//	return -1;      // fail to create
	//}

	//// Create output panes:
	//const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	//
	//COutputWnd::m_wndOutputOrder.CreateGrid(WS_CHILD|WS_VISIBLE,rectDummy, &m_wndTabs, 1);
	//COutputWnd::m_wndOutputPos.CreateGrid(WS_CHILD|WS_VISIBLE,rectDummy, &m_wndTabs, 2);
	//COutputWnd::m_wndOutputDeal.CreateGrid(WS_CHILD|WS_VISIBLE,rectDummy, &m_wndTabs, 3);
	//COutputWnd::m_wndOutputDuplicate_Order.CreateGrid(WS_CHILD|WS_VISIBLE,rectDummy, &m_wndTabs, 4);	
	//COutputWnd::m_AnalysisGrid.CreateGrid(WS_CHILD|WS_VISIBLE,rectDummy, &m_wndTabs, 4);
	//COutputWnd::m_GroupWiseNetPos.CreateGrid(WS_CHILD|WS_VISIBLE,rectDummy, &m_wndTabs, 5);
	////COutputWnd::m_GroupWiseNetPos;
	//
	//CString strTabName;
	//BOOL bNameValid;

	//// Attach list windows to tab:
	////bNameValid = strTabName.LoadString(IDS_BUILD_TAB);
	////ASSERT(bNameValid);
	////m_wndTabs.AddTab(m_wndOutputPos, strTabName, (UINT)0);
	//bNameValid = strTabName.LoadString(IDS_DEBUG_TAB);
	//ASSERT(bNameValid);
	//m_wndTabs.AddTab(&COutputWnd::m_wndOutputOrder, strTabName, (UINT)0);
	//m_wndTabs.AddTab(&COutputWnd::m_wndOutputPos, L"NetPosition", (UINT)1);
	//m_wndTabs.AddTab(&COutputWnd::m_wndOutputDeal, L"Dealing", (UINT)2);
	//m_wndTabs.AddTab(&COutputWnd::m_wndOutputDuplicate_Order, L"Comment Change", (UINT)3);
	////m_wndTabs.AddTab(&COutputWnd::m_wndOutput_alert, L"Alert", (UINT)4);
	//m_wndTabs.AddTab(&COutputWnd::m_AnalysisGrid, L"Group2wiseNetPos", (UINT)4);

	//m_wndTabs.AddTab(&COutputWnd::m_GroupWiseNetPos, L"GroupwiseNetPos", (UINT)5);
	
	//m_wndOutputDeal
	//bNameValid = strTabName.LoadString(IDS_FIND_TAB);
	//ASSERT(bNameValid);
	//m_wndTabs.AddTab(m_wndOutputDeal, strTabName, (UINT)2);		
	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	
	// Tab control should cover the whole client area:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	
}

void COutputWnd::AdjustHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);

		cxExtentMax = max(cxExtentMax, (int)dc.GetTextExtent(strItem).cx);
	}

	wndListBox.SetHorizontalExtent(cxExtentMax);
	dc.SelectObject(pOldFont);	
}


void COutputWnd::UpdateFonts()
{
	//m_wndOutputPos->SetFont(&afxGlobalData.fontRegular);
	//COutputWnd::m_wndOutputOrder.SetFont(&afxGlobalData.fontRegular);
	//m_wndOutputDeal->SetFont(&afxGlobalData.fontRegular);
}

/////////////////////////////////////////////////////////////////////////////
// COutputList1

COutputList::COutputList()
{
}

COutputList::~COutputList()
{
}

BEGIN_MESSAGE_MAP(COutputList, CListBox)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList message handlers

void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
}

void COutputList::OnEditCopy()
{
	MessageBox(_T("Copy output"));
}

void COutputList::OnEditClear()
{
	MessageBox(_T("Clear output"));
}

void COutputList::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}