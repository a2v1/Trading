#include "stdafx.h"
#include "RateDocking.h"
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
//MyCug*  RateDocking::m_wndOutputPos= new MyCug();

//MyCug*  RateDocking::m_wndOutputDeal= new MyCug();
RateGrid  RateDocking::m_wndOutputOrder;
 int RateDocking::m_rate_x=0;
 int RateDocking::m_rate_y=0;
RateDocking::RateDocking()
{
}

RateDocking::~RateDocking()
{
}

BEGIN_MESSAGE_MAP(RateDocking, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int RateDocking::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	RateDocking::m_wndOutputOrder.CreateGrid(WS_CHILD|WS_VISIBLE,rectDummy, &m_wndTabs, 1);
	

	//UpdateFonts();

	CString strTabName;
	BOOL bNameValid;

	// Attach list windows to tab:
	//bNameValid = strTabName.LoadString(IDS_BUILD_TAB);
	//ASSERT(bNameValid);
	//m_wndTabs.AddTab(m_wndOutputPos, strTabName, (UINT)0);
	bNameValid = strTabName.LoadString(IDS_DEBUG_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&RateDocking::m_wndOutputOrder, L"Rate", (UINT)0);
	
	//m_wndOutputDeal
	//bNameValid = strTabName.LoadString(IDS_FIND_TAB);
	//ASSERT(bNameValid);
	//m_wndTabs.AddTab(m_wndOutputDeal, strTabName, (UINT)2);		
	return 0;
}

void RateDocking::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	//RateDocking::m_rate_x=cx;
	//RateDocking::m_rate_y=cy;
	// Tab control should cover the whole client area:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	
	
//	CMainFrame::m_wndOutput.SetWindowPos(NULL,ScripWiseNetPosDocking::m_scripnetpos_x+5 , 30, CMainFrame::screen_width-cx-ScripWiseNetPosDocking::m_scripnetpos_x-5, cy+40,  SWP_NOACTIVATE | SWP_NOZORDER);	
	
	
}

void RateDocking::AdjustHorzScroll(CListBox& wndListBox)
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


void RateDocking::UpdateFonts()
{
	//m_wndOutputPos->SetFont(&afxGlobalData.fontRegular);
	RateDocking::m_wndOutputOrder.SetFont(&afxGlobalData.fontRegular);
	//m_wndOutputDeal->SetFont(&afxGlobalData.fontRegular);
}

