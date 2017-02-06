// rate.h : header file
//

#pragma once
#include <vector>

// CTradingDlg dialog
class Rate  : public CDialogEx,public IMTDealerSink, public IMTTickSink
{
// Construction
private:
	 HANDLE            m_event;
public:
	static int tickSuscribeCheck;
	Rate(CWnd* pParent = NULL);	// standard constructor
	Rate(CString strSymbol,CString strEx,CWnd* pParent = NULL);	
	virtual void      OnTick(LPCWSTR symbol, const MTTickShort& tick);

// Dialog Data
	enum { IDD = IDD_DIALOG_RATE};

	protected:
		CStatic m_lb_Symbol;
		CStatic m_lb_Ex;
		CStatic m_lb_Heigh;
		CStatic m_lb_Low;
		CButton m_btn_bid;
		CButton m_btn_ask;
		CComboBox m_cmb_qty;
		MTAPIRES res;

afx_msg void OnClose();
		
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();	
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

	public:
    bool            m_bShowGripper;         // ignored if not WS_THICKFRAME

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
	
	
	void set_tick_date();	
	
	afx_msg void OnBnClickedBtnRateBid();
};
