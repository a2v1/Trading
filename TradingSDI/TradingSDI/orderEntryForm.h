#pragma once
#include "stdafx.h"
class orderEntryForm : public CDialogEx,public IMTDealerSink//, public IMTTickSink
{
	public:
		orderEntryForm();	

// Dialog Data
		enum {IDD = IDD_ORDERENTRY};
	 bool              Initialize(IMTRequest *request, IMTConfirm *confirm);
   MTAPIRES          Wait(DWORD timeout);   
   virtual void      OnDealerAnswer(const IMTRequest* result);
   virtual void      OnDealerResult(const IMTConfirm* confirm);
	
	

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);	
		virtual void      OnTick(LPCWSTR symbol, const MTTickShort& tick);
		BOOL OnInitDialog();		
		MTAPIRES  res ;
		
		
  
protected:
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()	
	HANDLE            m_event;
	
public:
		CStatic m_LbPrice;
		CStatic m_LbStatus;
		CComboBox m_cmbSymbol;
		CEdit m_Volume;

		CComboBox m_cmbSymbolType;
		CComboBox m_cmbOrderType;
		
		CEdit m_Price;		
		CButton m_BtnPlace;	


	static 	IMTManagerAPI  *manager;
	static 	CMTManagerAPIFactory  factory;
			
		static int checkOrderForm;
		static CString   strqty;
		static CString strSymbolcmb;
		afx_msg void OnBnClickedButton1();
		afx_msg void OnCbnSelchangeCombo3();
		afx_msg void OnCbnSelchangeCombo1();
};
