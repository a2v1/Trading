#pragma once
#include"columnsetting_grid.h"

// coulmn_setting dialog

class coulmn_setting : public CDialogEx
{
	DECLARE_DYNAMIC(coulmn_setting)

public:
	coulmn_setting(CWnd* pParent = NULL);   // standard constructor
	virtual ~coulmn_setting();

	//grid
	Columnsetting_grid grid;
// Dialog Data
	enum { IDD = IDD_DIALOG_COLUMN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
};
