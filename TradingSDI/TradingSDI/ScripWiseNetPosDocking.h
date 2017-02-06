
#pragma once
#include "ScripWiseNetPos.h"
#include "Dealing.h"

/////////////////
// COutputList window

class ScripWiseNetPosDocking : public CDockablePane
{
// COutputWnd ::m_wndOutputOrder
public:
	ScripWiseNetPosDocking();
	
	static ScripWiseNetPos m_wndOutputOrder;
	static int m_scripnetpos_x;
	static int m_scripnetpos_y;
	CComboBox* cbox;
//	void AdjustLayout();
	void UpdateFonts();

// Attributes
protected:
	CMFCTabCtrl	m_wndTabs;
protected:
	void FillBuildWindow();
	void FillDebugWindow();
	void FillFindWindow();

	void AdjustHorzScroll(CListBox& wndListBox);
	virtual void OnPressButtons(UINT nHit);
// Implementation
public:
	virtual ~ScripWiseNetPosDocking();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//virtual void OnSlide(BOOL bSlideOut);
	DECLARE_MESSAGE_MAP()
};

