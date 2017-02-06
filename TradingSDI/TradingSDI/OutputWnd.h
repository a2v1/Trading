#pragma once
//#include "MyCug.h"
//#include "OrderGrid.h"
#include "NetPosGrid.h"
#include "Dealing.h"
#include "Duplicate_Order.h"
#include "AlertGrid.h"
#include "AnalysisGrid.h"
#include "GroupWisePosition.h"

/////////////////
// COutputList window

class COutputList : public CListBox
{
// Construction
public:
	COutputList();

// Implementation
public:
	virtual ~COutputList();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};

class COutputWnd : public CDockablePane,public IMTManagerSink, public IMTRequestSink, public IMTOrderSink, public IMTDealerSink 
{
// COutputWnd ::m_wndOutputOrder
public:
	COutputWnd();
	//static MyCug* m_wndOutputPos;	
	//static MyCug* m_wndOutputDeal;

	static OrderGrid m_wndOutputOrder;

	static GroupWise2NetPos m_AnalysisGrid;

	static NetPosGrid m_wndOutputPos;

	static Dealing m_wndOutputDeal;

	static Duplicate_Order  m_wndOutputDuplicate_Order;

	static GroupWiseNetPos m_GroupWiseNetPos;

	//static AlertGrid m_wndOutput_alert;

	/*static LTPupdate  m_wndOutputLTPupdate;*/
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
	virtual ~COutputWnd();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};

