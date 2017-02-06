#pragma once
#include "ClientHelpGrid.h"
#include "Client_Table.h"

// ClientHelpDlg dialog

class ClientHelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ClientHelpDlg)

public:
	ClientHelpDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ClientHelpDlg();

	ClientHelpGrid client_grid;
	CDataSource connection;
    CSession session;
    HRESULT hr;
// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void getdata();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditsearch();
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
};
