#pragma once



// CGroupWiseNetPosForm form view

class CGroupWiseNetPosForm : public CFormView
{
	DECLARE_DYNCREATE(CGroupWiseNetPosForm)

protected:
	CGroupWiseNetPosForm();           // protected constructor used by dynamic creation
	virtual ~CGroupWiseNetPosForm();

public:
	enum { IDD = IDD_GROUPWISENETPOS };
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


