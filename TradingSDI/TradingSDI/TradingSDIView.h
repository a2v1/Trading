
// TradingSDIView.h : interface of the CTradingSDIView class
//

#pragma once


class CTradingSDIView : public CTabView 
{
protected: // create from serialization only
	CTradingSDIView();
	DECLARE_DYNCREATE(CTradingSDIView)

// Attributes
public:
	CTradingSDIDoc* GetDocument() const;

// Operations
public  :
	
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnActivateView(CView* view);
	
	void onDestoyNetposThread();

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	

// Implementation
public:
	virtual ~CTradingSDIView();
#ifdef _DEBUG
	
#endif

protected:
	
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnAfxWmChangingActiveTab(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnFileSymbolgroupmapping();
//	afx_msg void OnFileDefinesymbolmargin();
//	afx_msg void OnFileCreateclient();
};

#ifndef _DEBUG  // debug version in TradingSDIView.cpp
inline CTradingSDIDoc* CTradingSDIView::GetDocument() const
   { return reinterpret_cast<CTradingSDIDoc*>(m_pDocument); }
#endif

