#pragma once
# include "Resource.h"

// OrderGridFilter dialog

class OrderGridFilter : public CDialogEx
{
	DECLARE_DYNAMIC(OrderGridFilter)

public:
	void addItemToCombobox();
	BOOLEAN  CheckvalueInArray(CString* arr,CString strval) ;
	CComboBox*		 cmb_status;
	CComboBox*		 cmb_client;
	CComboBox*		 cmb_order;
	CComboBox*		 cmb_date;
	CComboBox*		 cmb_symbol;
	CComboBox*		 cmb_ordertype;
	CComboBox*		 cmb_qty;
	CComboBox*		 cmb_rate;
	CComboBox*		 cmb_comment;
	OrderGridFilter(CWnd* pParent = NULL);   // standard constructor
	virtual ~OrderGridFilter();
	
	
	enum { IDD = IDD_DIALOG_FILTER };

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();	
	DECLARE_MESSAGE_MAP()
};
