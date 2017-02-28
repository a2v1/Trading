#pragma once
#include <vector>
#include "Resource.h"
#include "Editable_Grid.h"
#include "SymbolMappingTable.h"
#include <atldbcli.h>
// CTradingDlg dialog
class SymbolMapping  : public CDialogEx
{
// Construction
public:
	SymbolMapping(CWnd* pParent = NULL);	// standard constructor
	

// Dialog Data
	enum { IDD = IDD_Mapping_Symbol};

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CDataSource connection;
    CSession session;
    HRESULT hr;

// Implementation
protected:
	HICON m_hIcon;
	Editable_Grid e_grid;
	// Generated message map functions
	void setLoginName();
	virtual BOOL OnInitDialog();	
	void getSymbolData();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

	public:
    bool            m_bShowGripper;         // ignored if not WS_THICKFRAME	
	
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
	
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnClose();
};
