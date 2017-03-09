#pragma once
#include "symbol_map.h"
#include "afxwin.h"
#include "TableGroup_Symbol.h"
// symbol_grp dialog

class symbol_grp : public CDialogEx
{
	DECLARE_DYNAMIC(symbol_grp)


public:
	symbol_grp(CWnd* pParent = NULL);   // standard constructor
	virtual ~symbol_grp();
	Symbol_Map symbol_map;
// Dialog Data
	enum { IDD = IDD_SYMBOL_GRP };

	//data base connection
	CDataSource connection;
    CSession session;
    HRESULT hr;
	CCommand<CNoAccessor, CNoRowset> cmd;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	void getSymbolData(_bstr_t group_symbol);
	afx_msg void OnBnClickedOk();
	CEdit m_textcntrl;
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnClose();
};
