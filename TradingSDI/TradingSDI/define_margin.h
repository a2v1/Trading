#pragma once
#include "definemargin_grid.h"

// define_margin dialog

class define_margin : public CDialogEx
{
	DECLARE_DYNAMIC(define_margin)

public:
	define_margin(CWnd* pParent = NULL);   // standard constructor
	virtual ~define_margin();

// Dialog Data
	enum { IDD = IDD_DEFINE_MARGIN };
	definemargin_grid d_grid;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	void define_margin::getSymbolData();
	
};
