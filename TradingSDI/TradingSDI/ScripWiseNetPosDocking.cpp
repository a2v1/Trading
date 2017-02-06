#include "stdafx.h"
#include "ScripWiseNetPosDocking.h"
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
//MyCug*  ScripWiseNetPosDocking::m_wndOutputPos= new MyCug();

//MyCug*  ScripWiseNetPosDocking::m_wndOutputDeal= new MyCug();
ScripWiseNetPos ScripWiseNetPosDocking::m_wndOutputOrder;
int ScripWiseNetPosDocking::m_scripnetpos_x=0;
int ScripWiseNetPosDocking::m_scripnetpos_y=0;
ScripWiseNetPosDocking::ScripWiseNetPosDocking()
{
}

ScripWiseNetPosDocking::~ScripWiseNetPosDocking()
{
}

BEGIN_MESSAGE_MAP(ScripWiseNetPosDocking, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//AFX_HTCLOSE() 
	//AFX_HTMAXBUTTON()
END_MESSAGE_MAP()

int ScripWiseNetPosDocking::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create tabs window:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}

	// Create output panes:
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	//m_wndOutputPos->CreateGrid(WS_CHILD|WS_VISIBLE,rectDummy, &m_wndTabs, 2);			
	ScripWiseNetPosDocking::m_wndOutputOrder.CreateGrid(WS_CHILD|WS_VISIBLE,rectDummy, &m_wndTabs, 1);
	

	//UpdateFonts();

	CString strTabName;
	BOOL bNameValid;

	// Attach list windows to tab:
	//bNameValid = strTabName.LoadString(IDS_BUILD_TAB);
	//ASSERT(bNameValid);
	//m_wndTabs.AddTab(m_wndOutputPos, strTabName, (UINT)0);
	bNameValid = strTabName.LoadString(IDS_DEBUG_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&ScripWiseNetPosDocking::m_wndOutputOrder, L"ScripWiseNetPos", (UINT)0);
	
	//m_wndOutputDeal
	//bNameValid = strTabName.LoadString(IDS_FIND_TAB);
	//ASSERT(bNameValid);
	//m_wndTabs.AddTab(m_wndOutputDeal, strTabName, (UINT)2);		
	return 0;
}

void ScripWiseNetPosDocking::OnPressButtons(UINT nHit)
{
	if(nHit==1)
	{
		AfxMessageBox(L"1");
	}
	if(nHit==0)
	{
		AfxMessageBox(L"0");
	}
}
void ScripWiseNetPosDocking::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);	
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	
	AdjustLayout();
	
}


//void ScripWiseNetPosDocking::AdjustLayout()
//{
//	if (GetSafeHwnd() == NULL)
//	{
//		return;
//	}
//
//	CRect rectClient;
//	GetClientRect(rectClient);
//
//	//int cyTlb = CMainFrame::m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;
//
//	// CMainFrame::m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
//	//m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
//}


void ScripWiseNetPosDocking::AdjustHorzScroll(CListBox& wndListBox)
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


void ScripWiseNetPosDocking::UpdateFonts()
{
	//m_wndOutputPos->SetFont(&afxGlobalData.fontRegular);
	ScripWiseNetPosDocking::m_wndOutputOrder.SetFont(&afxGlobalData.fontRegular);
	//m_wndOutputDeal->SetFont(&afxGlobalData.fontRegular);
}

