#pragma once

#include "OrderGrid.h"

// COrderForm form view

class COrderForm : public CFormView
{
	DECLARE_DYNCREATE(COrderForm)

protected:
	COrderForm();           // protected constructor used by dynamic creation
	virtual ~COrderForm();

public:
	//OrderGrid m_ordergrid;
	enum { IDD = IDD_ORDERFORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);	
	virtual void OnInitialUpdate();
};


