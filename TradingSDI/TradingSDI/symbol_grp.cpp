// symbol_grp.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "symbol_grp.h"
#include "afxdialogex.h"
#include "resource.h"
#include"symbol_map.h"
#include "help_search.h"
#include "TableGroup_Symbol.h"
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace rename("EOF", "EndOfFile")

IMPLEMENT_DYNAMIC(symbol_grp, CDialogEx)

symbol_grp::symbol_grp(CWnd* pParent /*=NULL*/)
	: CDialogEx(symbol_grp::IDD, pParent)
{

}

symbol_grp::~symbol_grp()
{
}

void symbol_grp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_textcntrl);
}


BEGIN_MESSAGE_MAP(symbol_grp, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &symbol_grp::OnBnClickedButton1)	
	ON_BN_CLICKED(IDOK, &symbol_grp::OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_EDIT1, &symbol_grp::OnEnKillfocusEdit1)
END_MESSAGE_MAP()


// symbol_grp message handlers


BOOL symbol_grp::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	symbol_map.AttachGrid(this ,IDC_STATIC_GRID);
	symbol_map.SetColWidth(0,340);	
	symbol_map.QuickSetText(0,-1,L"SYMBOL");

	//getSymbolData();

	return TRUE;  // return TRUE unless you set the focus to a control	
}


void symbol_grp::OnBnClickedButton1()
{
	help_search dlg;
	dlg.DoModal();	
}
void symbol_grp::OnBnClickedOk()
{
	_bstr_t valField1("");
		_bstr_t valField2("");		
		_bstr_t valField3("");
		_bstr_t cmd("");
		CString  strsqlcommand;				 	
		HRESULT hr = S_OK;		 
		CoInitialize(NULL);
          // Define string variables.		 
		_bstr_t strCnn("Provider=SQLOLEDB;SERVER=68.168.104.26;Database=tradedatabase;uid=sa;pwd=ok@12345;");		 
        _RecordsetPtr pRstAuthors = NULL;
 
      // Call Create instance to instantiate the Record set
      hr = pRstAuthors.CreateInstance(__uuidof(Recordset)); 
      if(FAILED(hr))
      {           
      }		
	  
	  
	 CString Symbol_group=L"";
	// GetDlgItemText(IDC_EDIT1,Symbol_group);
	 m_textcntrl.GetWindowText(Symbol_group);
	 _bstr_t  b_symbol_group=Symbol_group;
	int noofrows=symbol_map.GetNumberRows();
	for (int f_count=0;f_count<noofrows-1;f_count++)
	{
		CString strf=L"";
		valField1=symbol_map.QuickGetText(0,f_count);
		strf=symbol_map.QuickGetText(0,f_count);
		
		if (strf!=L"")
		{
			cmd=cmd+" insert into Symbol_Group(Group_name,Symbol) values('" + b_symbol_group + "','" + valField1 + "');";
		}
	}	
	cmd=" delete  from Symbol_Group where Group_name='" + b_symbol_group + "';"+cmd;
	
	pRstAuthors->Open(cmd,strCnn, adOpenStatic,adLockReadOnly,adCmdText);    			

	AfxMessageBox(L"Symbol Group  has been updated");
	//CDialogEx::OnOK();
}

void symbol_grp::getSymbolData(_bstr_t group_symbol)
{
	HRESULT hr;
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<CSymbolGroup_Table> > artists1;	

	connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=TradeDataBase;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	
	session.Open(connection);
	
		_bstr_t strCommand="";	
		
		strCommand="select symbol,'0' as 'margin' from Symbol_Group where Group_name='" + group_symbol + "'";		
		char* strCommand_char=(char*)strCommand;
		hr=artists1.Open(session,strCommand_char);				
		int rows_count=0;
		if(SUCCEEDED(hr))
		{
		while (artists1.MoveNext() == S_OK)
		{
			symbol_map.QuickSetText(0,rows_count,artists1.m_Symbol ); 
			rows_count=rows_count+1;
		}
		}
		artists1.Close();	
		session.Close();
		connection.Close();
}

void symbol_grp::OnEnKillfocusEdit1()
{
	CString tvalue=L"";
	 m_textcntrl.GetWindowText(tvalue);
	 _bstr_t bstrval=tvalue;
	getSymbolData(bstrval);
}
