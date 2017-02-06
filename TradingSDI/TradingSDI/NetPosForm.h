#pragma once



// CNetPosForm form view

class CNetPosForm : public CFormView
{
	DECLARE_DYNCREATE(CNetPosForm)

protected:
	CNetPosForm();           // protected constructor used by dynamic creation
	virtual ~CNetPosForm();

public:
	enum { IDD = IDD_NETPOSFORM };
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
};


