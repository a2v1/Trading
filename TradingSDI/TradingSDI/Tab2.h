
#ifndef Tab2_HEADER
#define Tab2_HEADER
#include "GridTradeAndOrder.h"
#include "OverViewOrderGrid.h"
#include "CTrade_Table.h"
#include "afxdtctl.h"
#include "Grid_CheckTrade.h"
#include "Tab2.h"
#include "TABCONTROL.H"
#include "afxwin.h"
#include "overview.h"

// Tab2 dialog

class Tab2 : public CDialogEx
{
	DECLARE_DYNAMIC(Tab2)

public:
	Tab2(CWnd* pParent = NULL);   // standard constructor
	virtual ~Tab2();

// Dialog Data
	enum { IDD = IDD_TAB2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	Grid_CheckTrade gridtradecheck;
	CWinThread* m_pThreads;

	CWinThread* m_order_pThreads;
	afx_msg void OnClose();	
	CDateTimeCtrl m_datefrom;
	CDateTimeCtrl m_dateto;
	afx_msg void OnBnClickedButton2();
	CComboBox m_daycombo;
	CButton m_export;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
#endif