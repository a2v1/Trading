#pragma once


// COrderwiseJournal dialog
#include "Editable_Grid.h"
class COrderwiseJournal : public CDialogEx
{
	DECLARE_DYNAMIC(COrderwiseJournal)

public:
	COrderwiseJournal(CWnd* pParent = NULL);   // standard constructor
	virtual ~COrderwiseJournal();
	static CString odno;
// Dialog Data
	enum { IDD = IDD_ORDERWISE_JOURNAL };
	 static Editable_Grid e_grid;
	BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
