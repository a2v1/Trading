// Symbol_Per_Define.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "Symbol_Per_Define.h"
#include "afxdialogex.h"
#include "per_define_Table.h"

// CSymbol_Per_Define dialog

IMPLEMENT_DYNAMIC(CSymbol_Per_Define, CDialogEx)

CSymbol_Per_Define::CSymbol_Per_Define(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSymbol_Per_Define::IDD, pParent)
{

}

CSymbol_Per_Define::~CSymbol_Per_Define()
{
}

void CSymbol_Per_Define::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSymbol_Per_Define, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSymbol_Per_Define::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSymbol_Per_Define::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSymbol_Per_Define message handlers


void CSymbol_Per_Define::OnBnClickedButton1()
{
	CDataSource connection;
    CSession session;
    HRESULT hr;
	CCommand<CNoAccessor, CNoRowset> cmd;

	_bstr_t valField1("");
	_bstr_t str_cmd("");
	 CString Symbol_group=L"";
	_bstr_t  b_symbol_group("");		 	
	CoInitialize(NULL);		
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CheckData;Data Source=64.251.7.161;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");			
	if(SUCCEEDED(hr))
	{
	  hr=session.Open(connection);							
	}
	  
	CString str_tmp_Delete=L"";
	str_tmp_Delete.Format(L"delete from Symbol_Per;");
	hr=cmd.Open(session,(LPCTSTR)str_tmp_Delete);	
	cmd.Close();


	 int noofrows=e_grid.GetNumberRows();
	 for (int f_count=0;f_count<noofrows-1;f_count++)
	 {
		CString strf=L"";
		Symbol_group=e_grid.QuickGetText(0,f_count);
				
		strf=e_grid.QuickGetText(1,f_count);
		
		if (strf!=L"")
		{
			CString str_tmp=L"";
			str_tmp.Format(L"insert into Symbol_Per([Symbol],per)values('%s','%s');",Symbol_group,strf);
			str_cmd=str_cmd+str_tmp;
		}
	}	

	hr=cmd.Open(session,(LPCTSTR)str_cmd);	  			

	AfxMessageBox(L"Group Margin has been updated");
	cmd.Close();
	session.Close();
	connection.Close();
}
void CSymbol_Per_Define::getdata()
{
	HRESULT hr;
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<Cper_define_Table> > artists1;	

	connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=Checkdata;Data Source=64.251.7.161;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	
	session.Open(connection);
	
		_bstr_t strCommand="";					
		strCommand="select * from Symbol_Per";		
		char* strCommand_char=(char*)strCommand;
		hr=artists1.Open(session,strCommand_char);				
		int rows_count=0;
		if(SUCCEEDED(hr))
		{
		while (artists1.MoveNext() == S_OK)
		{
			e_grid.QuickSetText(0,rows_count,artists1.m_Client); 

			CString str_per=L"";
			str_per.Format(L"%.2f",artists1.m_Per);
			e_grid.QuickSetText(1,rows_count,str_per);			
			rows_count=rows_count+1;
		}
		}
		artists1.Close();	
		session.Close();
		connection.Close();
}

BOOL CSymbol_Per_Define::OnInitDialog()
{
	CDialogEx::OnInitDialog();	
	e_grid.AttachGrid(this ,IDC_STATIC_GRID_Scrip_Per_Define);
	e_grid.SetNumberCols(2);
	e_grid.SetColWidth(0,150);
	e_grid.SetColWidth(1,50);	
	e_grid.QuickSetText(0,-1,L"Symbol");
	e_grid.QuickSetText(1,-1,L"Per");
	getdata();
	return TRUE;  
}


void CSymbol_Per_Define::OnBnClickedButton2()
{
	CDialogEx::OnCancel();
}
