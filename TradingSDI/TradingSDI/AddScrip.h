#pragma once
#include <vector>
#include "Resource.h"
// CTradingDlg dialog
class AddScrip  : public CDialogEx
{
// Construction
public:
	AddScrip(CWnd* pParent = NULL);	// standard constructor
	static CString  strclient;

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_SCRIP};

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	void setLoginName();
	virtual BOOL OnInitDialog();	
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

	public:
    bool            m_bShowGripper;         // ignored if not WS_THICKFRAME
	CComboBox		 cmb_login;
	CComboBox		 cmb_Scrip;
	CEdit			edit_name;	
	//CMainFrame      *m_mainF;
	private:
    struct SMovingChild
    {
        HWND        m_hWnd;
        double      m_dXMoveFrac;
        double      m_dYMoveFrac;
        double      m_dXSizeFrac;
        double      m_dYSizeFrac;
        CRect       m_rcInitial;
    };
    typedef std::vector<SMovingChild>   MovingChildren;

    MovingChildren  m_MovingChildren;
    CSize           m_szInitial;
    CSize           m_szMinimum;
    HWND            m_hGripper;
	
public:
	
	afx_msg void OnBnClickedScripBtnLogin();
	afx_msg void OnCbnSelchangeScripCmbLogin();
	afx_msg void OnCbnEditchangeScripCmbLogin();
	
	afx_msg void OnBnClickedButton1();
	
};
