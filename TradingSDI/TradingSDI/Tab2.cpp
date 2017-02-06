// Tab2.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "Tab2.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(Tab2, CDialogEx)



extern HRESULT hrn;
extern CDataSource connection_update;
extern CSession session_update;	
extern CCommand<CNoAccessor, CNoRowset> cmd;

Tab2::Tab2(CWnd* pParent /*=NULL*/)
	: CDialogEx(Tab2::IDD, pParent)
{
	
}

Tab2::~Tab2()
{
}

void Tab2::OnClose()
{
	
	CDialog::OnClose();
}


void Tab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_datefrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dateto);
	DDX_Control(pDX, IDC_COMBO1, m_daycombo);
	DDX_Control(pDX, IDC_BUTTON1, m_export);
}


BEGIN_MESSAGE_MAP(Tab2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &Tab2::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &Tab2::OnBnClickedOk)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// Tab2 message handlers


void Tab2::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CString datefrom;
	CString dateto;
	CString combovalue;
	CTime dfrom,dto;
	int itemno=m_daycombo.GetCurSel();
	if (itemno!=-1)
	{
		m_daycombo.GetLBText(itemno,combovalue);
	}
	else
	{
		m_datefrom.GetTime(dfrom);
		m_dateto.GetTime(dto);
		dto=dto+(24 * 60 * 60);
		datefrom=dfrom.Format ("%m-%d-%Y");
		dateto=dto.Format ("%m-%d-%Y");
	}
	gridtradecheck.getData(combovalue,datefrom,dateto);	
}


void Tab2::OnBnClickedOk()
{
    
	 int check_data=0;
	 _bstr_t jasonStr="";
	 _variant_t  strUpdate_time="";
	 _bstr_t r_time="";
	 	

	 int rows_no=gridtradecheck.GetNumberRows();
	 _bstr_t  InsertAndUpdate_Command=" ";
	 _bstr_t  str_deal=" ";
	 _bstr_t  str_out_comment=" ";
	 _bstr_t  str_checked=" ";
	 _bstr_t  str_new=" ";
	 _bstr_t str_symbol="";
	 _bstr_t commentYN="";

	 for (int forcount=0;forcount<rows_no;forcount++)
	 {
		 commentYN=gridtradecheck.QuickGetText(0,forcount);
		 str_deal=gridtradecheck.QuickGetText(2,forcount);
		 str_out_comment=gridtradecheck.QuickGetText(9,forcount);
		 str_checked=gridtradecheck.QuickGetText(10,forcount);		 
		 str_symbol=gridtradecheck.QuickGetText(4,forcount);		 
		 str_new= " exec update_trade_Status '" + str_deal + "','" + str_checked + "','" + str_out_comment + "'; ";
		 InsertAndUpdate_Command=str_new +InsertAndUpdate_Command ;

		 str_new= " exec Proc_Position_Check '" + GridTradeAndOrder::m_selected_login + "','" + str_symbol + "'; ";
		 InsertAndUpdate_Command=str_new +InsertAndUpdate_Command ;


		 str_new= " exec update_CommentChangeYN '" + str_deal + "','" + commentYN + "'; ";
		 InsertAndUpdate_Command=str_new +InsertAndUpdate_Command ;
		 
		 
	 }	
		char* strCommand_char=(char*)InsertAndUpdate_Command;
		hrn=cmd.Open(session_update,strCommand_char);							 			 		 				 	
		cmd.Close();
	 AfxMessageBox(L"Data Updated");
	 
	

	
}
	
		
	
	



BOOL Tab2::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	gridtradecheck.AttachGrid(this,IDC_STATIC_FrGrid_Trade_history2);
		
	return TRUE;  // return TRUE unless you set the focus to a control

}