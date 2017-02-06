#pragma once


#include "Dealing.h"
// CDealingForm form view

class CDealingForm : public CFormView
{
	DECLARE_DYNCREATE(CDealingForm)

protected:
	CDealingForm();           // protected constructor used by dynamic creation
	virtual ~CDealingForm();

public:
	
	enum { IDD = IDD_DEALINGFORM };
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
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


