#pragma once

#include "PassedBYMngr.h"
#include "CodesChanged.h"
#include "NPBPSType1Grid.h"
#include "NPBPSType2Grid.h"
#include "afxwin.h"

// CAuditForm form view

class CAuditForm : public CFormView
{
	DECLARE_DYNCREATE(CAuditForm)

protected:
	CAuditForm();           // protected constructor used by dynamic creation
	virtual ~CAuditForm();
	  CPassedBYMngr m_passedbymngrGrid;
	  CCodesChanged m_CodeChangGrid;
	  CNPBPSType1Grid m_npbpstype1grid;
	  CNPBPSType2Grid m_npbpstype2grid;



public:
	enum { IDD = IDD_AUDITFORM };

	
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
	CStatic m_staticpassedbymngr;
	CStatic m_StaticNpbpsType1;
	CStatic m_StaticNPBPStype2;
	CStatic m_StaticCodeChanged;
};


