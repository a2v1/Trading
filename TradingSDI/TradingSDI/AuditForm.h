#pragma once

#include "PassedBYMngr.h"
#include "CodesChanged.h"
#include "NPBPSType1Grid.h"
#include "NPBPSType2Grid.h"
#include "afxwin.h"
#include "afxcmn.h"

// CAuditForm form view

class CAuditForm : public CFormView
{
	DECLARE_DYNCREATE(CAuditForm)

protected:
	CAuditForm();           // protected constructor used by dynamic creation
	virtual ~CAuditForm();
	  
	 //Array to hold the list of Grid tab pages for CTabCtrl
    int m_GridID[4];
    //Grid Array Variable to hold the Grid
	CUGCtrl *m_Grid[4];
    int m_tabCurrent;
    int m_nPageCount;

  static CPassedBYMngr m_passbygrid;
	CNPBPSType1Grid m_nbpsgrid1;
	CNPBPSType2Grid m_nbpsgrid2;
	CCodesChanged m_codechangegrid;


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
	CTabCtrl m_tab;
	afx_msg void OnTcnSelchangeTabaudit(NMHDR *pNMHDR, LRESULT *pResult);
	void InitForm();
	afx_msg void OnTcnFocusChangeTabaudit(NMHDR *pNMHDR, LRESULT *pResult);
};


