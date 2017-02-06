#pragma once



// CGroup2WiseNetPosForm form view

class CGroup2WiseNetPosForm : public CFormView
{
	DECLARE_DYNCREATE(CGroup2WiseNetPosForm)

protected:
	CGroup2WiseNetPosForm();           // protected constructor used by dynamic creation
	virtual ~CGroup2WiseNetPosForm();

public:
	enum { IDD = IDD_GROUP2WISENETPOSFORM };
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


