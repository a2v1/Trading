// change_comment.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "change_comment.h"
#include "afxdialogex.h"
#include "grid_checktrade.h"
#include "Dealer.h"
#include "Login.h"
#include "GridTradeAndOrder.h"
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace rename("EOF", "EndOfFile")
// change_comment dialog

IMPLEMENT_DYNAMIC(change_comment, CDialogEx)

change_comment::change_comment(CWnd* pParent /*=NULL*/)
	: CDialogEx(change_comment::IDD, pParent)
{

}

change_comment::~change_comment()
{
}

void change_comment::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT16, m_time);
	DDX_Control(pDX, IDC_EDIT15, m_deal);
	DDX_Control(pDX, IDC_EDIT1, m_order);
	DDX_Control(pDX, IDC_EDIT14, m_symbol);	
	DDX_Control(pDX, IDC_EDIT9, m_type);
	DDX_Control(pDX, IDC_EDIT10, m_volume);
	DDX_Control(pDX, IDC_EDIT8, m_price);
	DDX_Control(pDX, IDC_EDIT6, m_comment);
	
}

BOOL change_comment::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_time.SetWindowTextW(Grid_CheckTrade::m_strtime);
	m_deal.SetWindowTextW(Grid_CheckTrade::m_strdeal);
	m_order.SetWindowTextW(Grid_CheckTrade::m_strorder);
	m_symbol.SetWindowTextW(Grid_CheckTrade::m_strsymbol);
	m_type.SetWindowTextW(Grid_CheckTrade::m_strtype);
	m_volume.SetWindowTextW(Grid_CheckTrade::m_strvolume);
	m_price.SetWindowTextW(Grid_CheckTrade::m_strprice);
	m_comment.SetWindowTextW(Grid_CheckTrade::m_strcomment);
	return true;
}


BEGIN_MESSAGE_MAP(change_comment, CDialogEx)
	//ON_EN_CHANGE(IDC_EDIT15, &change_comment::OnEnChangeEdit15)
	ON_BN_CLICKED(IDOK, &change_comment::OnBnClickedOk)
END_MESSAGE_MAP()


// change_comment message handlers




void change_comment::OnBnClickedOk()
{
	int comment_check=0;
	CString m_strnewcomment=L"";
	m_comment.GetWindowTextW(m_strnewcomment);
	CString login_1=GridTradeAndOrder::m_selected_login;
	CString login_2=L"";

	login_1=login_1.Mid(0,6);
	_bstr_t strlogin_o=login_1;
	_bstr_t strlogin_c_1=Grid_CheckTrade::m_strcomment;
	_bstr_t strlogin_c_2=m_strnewcomment;
	_bstr_t strlogin_1="" + strlogin_o + "-" + Grid_CheckTrade::m_strcomment + "";
	_bstr_t strlogin_2="" + strlogin_o + "-" + m_strnewcomment + "";
	
	comment_check=DlgHelp::m_dealer->Change_Comment(Grid_CheckTrade::m_strcomment,m_strnewcomment,Grid_CheckTrade::m_strdeal);	
	Sleep(1000);
	if (comment_check==1)
	{
		try
		{
			CoInitialize(NULL);
			HRESULT hr = S_OK;	
			_RecordsetPtr pRstAuthors = NULL;
		 hr = pRstAuthors.CreateInstance(__uuidof(Recordset)); 
		int check_data=0;
		_bstr_t jasonStr="";
		_variant_t  strUpdate_time="";
		_bstr_t r_time="";
		_bstr_t bstrConnect ="Provider=SQLOLEDB.1;SERVER=68.168.104.26;Database=Tradedatabase;uid=sa;pwd=ok@12345;";
		
		_bstr_t  InsertAndUpdate_Command="exec proc_data_delete_for_commentchange '" + strlogin_1 + "','" + strlogin_2 + "'; ";
		//CString MessageStr=InsertAndUpdate_Command;
		//AfxMessageBox(MessageStr);
		//_bstr_t  InsertAndUpdate_Command="exec proc_data_delete_for_commentchange '200011-25','200011-100'";
		 pRstAuthors->Open(InsertAndUpdate_Command,bstrConnect,  adOpenStatic,adLockReadOnly,adCmdText);  
		
		 AfxMessageBox(L"Data Has been Changed");
		}
		catch(_com_error & ce)
		{	   
			//AfxMessageBox(L"Netpos Insert"+ce.ErrorMessage());
			AfxMessageBox(ce.Description()+L"Comment Change");
		}
		
	}

}
