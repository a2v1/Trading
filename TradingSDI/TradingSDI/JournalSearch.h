#pragma once


// CJournalSearch dialog

class CJournalSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CJournalSearch)

public:
	CJournalSearch(CWnd* pParent = NULL);   // standard constructor
	virtual ~CJournalSearch();

	CDateTimeCtrl m_datefrom;
	CDateTimeCtrl m_dateto;
	CButton m_btnsearch; 
	virtual BOOL OnInitDialog();
// Dialog Data
	enum { IDD = IDD_DIALOG_FOR_JOURNAL_SEARCH };

protected:
	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
