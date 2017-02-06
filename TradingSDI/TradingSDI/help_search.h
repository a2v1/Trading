#pragma once
#include "helpserach_grid.h"

// help_search dialog

class help_search : public CDialogEx
{
	DECLARE_DYNAMIC(help_search)

public:
	help_search(CWnd* pParent = NULL);   // standard constructor
	virtual ~help_search();

// Dialog Data
	enum { IDD = IDD_HELP_SEARCH };
	helpserach_grid help_grid;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
