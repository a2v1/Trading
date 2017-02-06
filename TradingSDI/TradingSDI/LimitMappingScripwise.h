#pragma once
#include "Editable_Grid.h"

// LimitMappingScripwise dialog

class LimitMappingScripwise : public CDialogEx
{
	DECLARE_DYNAMIC(LimitMappingScripwise)

public:
	LimitMappingScripwise(CWnd* pParent = NULL);   // standard constructor
	virtual ~LimitMappingScripwise();
	void getSymbolData();
	Editable_Grid e_grid;
	virtual BOOL OnInitDialog();	


	 
    CSize           m_szInitial;
    CSize           m_szMinimum;
    HWND            m_hGripper;
// Dialog Data
	enum { IDD = IDD_DIALOG_LIMITmAPPING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnBnClickedBtnOk();
};
