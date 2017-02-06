
#pragma once
//#include "MyCug.h"
//#include "OrderGrid.h"
#include "RateGrid.h"
#include "Dealing.h"

/////////////////
// COutputList window

class RateDocking : public CDockablePane
{
// COutputWnd ::m_wndOutputOrder
public:
	RateDocking();
	
	static RateGrid m_wndOutputOrder;

	static int m_rate_x;
	static int m_rate_y;

	CComboBox* cbox;

	void UpdateFonts();

// Attributes
protected:
	CMFCTabCtrl	m_wndTabs;

	/*COutputList m_wndOutputBuild;
	COutputList m_wndOutputDebug;
	COutputList m_wndOutputFind;*/

	

	//CEdit m_wndOutputBuild;
	
	

protected:
	void FillBuildWindow();
	void FillDebugWindow();
	void FillFindWindow();

	void AdjustHorzScroll(CListBox& wndListBox);
// Implementation
public:
	virtual ~RateDocking();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};

