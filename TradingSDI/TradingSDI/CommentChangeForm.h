#pragma once



// CCommentChangeForm form view

class CCommentChangeForm : public CFormView
{
	DECLARE_DYNCREATE(CCommentChangeForm)

protected:
	CCommentChangeForm();           // protected constructor used by dynamic creation
	virtual ~CCommentChangeForm();

public:
	enum { IDD = IDD_COMMENTCHANGEFORM };
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


