

#if !defined(AFX_DATETIMEEDITCTRL_H__737F6EBA_CC75_11D6_8634_0000B48746CF__INCLUDED_)
#define AFX_DATETIMEEDITCTRL_H__737F6EBA_CC75_11D6_8634_0000B48746CF__INCLUDED_


class CDateTimeEditCtrl : public CDateTimeCtrl
{
  DECLARE_DYNAMIC(CDateTimeEditCtrl)
  
// Construction
public:
	CDateTimeEditCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateTimeEditCtrl)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	 void WINAPI DoDateTimeChange(LPNMDATETIMECHANGE lpChange);
	 void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags);
	 void OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags);
	
	//}}AFX_VIRTUAL

// Implementation
public:
  
  
  virtual ~CDateTimeEditCtrl();

  

  

	// Generated message map functions
protected:
  
	
	
	DECLARE_MESSAGE_MAP()
};


#endif // !defined(AFX_DATETIMEEDITCTRL_H__737F6EBA_CC75_11D6_8634_0000B48746CF__INCLUDED_)
