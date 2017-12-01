#pragma once
#include "Editable_Grid.h"

// CSymbol_Per_Define dialog

class CSymbol_Per_Define : public CDialogEx
{
	DECLARE_DYNAMIC(CSymbol_Per_Define)

public:
	CSymbol_Per_Define(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSymbol_Per_Define();

// Dialog Data
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void getdata();
	Editable_Grid e_grid;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
};
