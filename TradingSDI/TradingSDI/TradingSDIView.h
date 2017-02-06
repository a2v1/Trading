
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
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
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

