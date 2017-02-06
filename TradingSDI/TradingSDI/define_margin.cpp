// define_margin.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "define_margin.h"
#include "afxdialogex.h"
#include "TableGroup_Symbol.h"
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace rename("EOF", "EndOfFile")
// define_margin dialog

IMPLEMENT_DYNAMIC(define_margin, CDialogEx)

define_margin::define_margin(CWnd* pParent /*=NULL*/)
	: CDialogEx(define_margin::IDD, pParent)
{

}

define_margin::~define_margin()
{
}

void define_margin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(define_margin, CDialogEx)
	ON_BN_CLICKED(IDOK, &define_margin::OnBnClickedOk)
END_MESSAGE_MAP()


// define_margin message handlers

BOOL define_margin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	d_grid.AttachGrid(this ,IDC_STATIC_MARGIN);
	d_grid.SetColWidth(0,170);
	d_grid.SetColWidth(1,170);
	d_grid.QuickSetText(0,-1,L"SYMBOL");
	d_grid.QuickSetText(1,-1,L"MARGIN");


	getSymbolData();

	return TRUE;  // return TRUE unless you set the focus to a control

}


void define_margin::OnBnClickedOk()
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
	 //m_textcntrl.GetWindowText(Symbol_group);
	 _bstr_t  b_symbol_group=Symbol_group;
	int noofrows=d_grid.GetNumberRows();
	for (int f_count=0;f_count<noofrows-1;f_count++)
	{
		CString strf=L"";
		Symbol_group=d_grid.QuickGetText(0,f_count);
		b_symbol_group=Symbol_group;

		if (d_grid.QuickGetText(1,f_count)!=NULL )
		{
			valField1=d_grid.QuickGetText(1,f_count);
		}
		else
		{
			valField1="0";
		}
		strf=d_grid.QuickGetText(1,f_count);
		
		if (strf!=L"")
		{
			//select group_name,margin from Symbol_group_margin
			cmd=cmd+" delete  from Symbol_group_margin where Group_name='" + b_symbol_group + "'; insert into Symbol_group_margin(Group_name,margin) values('" + b_symbol_group + "','" + valField1 + "');";
		}
	}	
	
	
	pRstAuthors->Open(cmd,strCnn, adOpenStatic,adLockReadOnly,adCmdText);    			

	AfxMessageBox(L"Group Margin has been updated");
}


void define_margin::getSymbolData()
{
	HRESULT hr;
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<CSymbolGroup_Table> > artists1;	

	connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=TradeDataBase;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	
	session.Open(connection);
	
		_bstr_t strCommand="";	
		
		strCommand="select DISTINCT  Group_name,'0' as 'margin' from Symbol_Group  where Group_name not in (select Group_name from Symbol_group_margin) union all select group_name,margin from Symbol_group_margin";		
		char* strCommand_char=(char*)strCommand;
		hr=artists1.Open(session,strCommand_char);				
		int rows_count=0;
		if(SUCCEEDED(hr))
		{
		while (artists1.MoveNext() == S_OK)
		{
			d_grid.QuickSetText(0,rows_count,artists1.m_Symbol ); 
			d_grid.QuickSetText(1,rows_count,artists1.m_margin ); 
			rows_count=rows_count+1;
		}
		}
		artists1.Close();	
		session.Close();
		connection.Close();
}