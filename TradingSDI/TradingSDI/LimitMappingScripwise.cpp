#include "stdafx.h"
#include "TradingSDI.h"
#include "LimitMappingScripwise.h"
#include "afxdialogex.h"
#include "GridTradeAndOrder.h"
#include "CTrade_Table.h"
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
no_namespace rename("EOF", "EndOfFile")

IMPLEMENT_DYNAMIC(LimitMappingScripwise, CDialogEx)
LimitMappingScripwise::LimitMappingScripwise(CWnd* pParent /*=NULL*/)
	: CDialogEx(LimitMappingScripwise::IDD, pParent)
{

}
LimitMappingScripwise::~LimitMappingScripwise()
{
}
void LimitMappingScripwise::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BOOL LimitMappingScripwise::OnInitDialog()
{
	CDialogEx::OnInitDialog();		
// use the initial dialog size as the default minimum
    if ((m_szMinimum.cx == 0) && (m_szMinimum.cy == 0))
    {
        CRect rcWindow;
        GetWindowRect(rcWindow);
        m_szMinimum = rcWindow.Size();
    }
    // keep the initial size of the client area as a baseline for moving/sizing controls
    CRect rcClient;
    GetClientRect(rcClient);
    m_szInitial = rcClient.Size();
    // create a gripper in the bottom-right corner    	
	CRect rectDummy;
	rectDummy.SetRectEmpty();	
	e_grid.AttachGrid(this ,IDC_STATIC_GRID_LIMTMAPPING);
	e_grid.SetNumberCols(3);
	e_grid.SetColWidth(0,150);
	e_grid.SetColWidth(1,50);
	e_grid.SetColWidth(2,50);
	e_grid.QuickSetText(0,-1,L"SYMBOL");
	e_grid.QuickSetText(1,-1,L"LimitBuy");
	e_grid.QuickSetText(2,-1,L"LimitSell");

	getSymbolData();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
BEGIN_MESSAGE_MAP(LimitMappingScripwise, CDialogEx)
	ON_BN_CLICKED(ID_BTN_CANCEL, &LimitMappingScripwise::OnBnClickedBtnCancel)
	ON_BN_CLICKED(ID_BTN_OK, &LimitMappingScripwise::OnBnClickedBtnOk)
END_MESSAGE_MAP()
void LimitMappingScripwise::getSymbolData()
{
	HRESULT hr;
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<CTrade_Table> > artists1;	

	connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=TradeDataBase;Data Source=64.251.7.161;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	
	session.Open(connection);
	
		_bstr_t strCommand="";	
		CString sel_login=GridTradeAndOrder::m_selected_login;
		sel_login=sel_login.Mid(0,6);
		_bstr_t strcode=sel_login;
		//select distinct symbol,0 as 'Limit','' as 'Client_group','' as 'Client_Group1','' as 'Client_Group2','' as 'v','' as 'ba','' as  'TYPE','' as  'volume' ,'' AS 'cHECKtRADE' from mt5_deals  where [Action] in (0,1)	 and symbol not in (select Symbol from Limit_Mapping where [login]='" + GridTradeAndOrder::m_selected_login + "' )union select Symbol,Limit from Limit_Mapping where [login]='" + GridTradeAndOrder::m_selected_login + "' "
		strCommand="select distinct symbol,0 as 'LimitBuy',0 as 'Client_group','' as 'Client_Group1','' as 'Client_Group2','' as 'v','' as 'ba','' as  'TYPE','' as  'volume' ,'' AS 'cHECKtRADE' from mt5_deals  where [Action] in (0,1)	 and symbol not in (select Symbol from Limit_Mapping where [login]='" + GridTradeAndOrder::m_selected_login + "' )union select Symbol,Limit,LimitSell as 'Client_group','' as 'Client_Group1','' as 'Client_Group2','' as 'v','' as 'ba','' as  'TYPE','' as  'volume' ,'' AS 'cHECKtRADE' from Limit_Mapping where [login]='" + GridTradeAndOrder::m_selected_login + "' ";		
		char* strCommand_char=(char*)strCommand;
		hr=artists1.Open(session,strCommand_char);				
		int rows_count=0;
		if(SUCCEEDED(hr))
		{
		while (artists1.MoveNext() == S_OK)
		{
			e_grid.QuickSetText(0,rows_count,artists1.m_Symbol ); 
			e_grid.QuickSetText(1,rows_count,artists1.m_Order);
			e_grid.QuickSetText(2,rows_count,artists1. m_Time);
			rows_count=rows_count+1;
		}
		}
		artists1.Close();	
		session.Close();
		connection.Close();
}
void LimitMappingScripwise::OnBnClickedBtnCancel()
{
	CDialog::OnCancel();
}
void LimitMappingScripwise::OnBnClickedBtnOk()
{
		_bstr_t valField1("");
		_bstr_t valField2("");		
		_bstr_t valField3("");
		_bstr_t cmd("");
		CString  strsqlcommand;				 	
		HRESULT hr = S_OK;		 
		CoInitialize(NULL);
          // Define string variables.		 
		_bstr_t strCnn("Provider=SQLOLEDB;SERVER=64.251.7.161;Database=tradedatabase;uid=sa;pwd=ok@12345;");		 
        _RecordsetPtr pRstAuthors = NULL;
 
      // Call Create instance to instantiate the Record set
      hr = pRstAuthors.CreateInstance(__uuidof(Recordset)); 
      if(FAILED(hr))
      {           
      }		
	 
	int noofrows=e_grid.GetNumberRows();
	for (int f_count=0;f_count<noofrows-1;f_count++)
	{
		CString strf=L"";
		valField1=e_grid.QuickGetText(0,f_count);
		strf=e_grid.QuickGetText(0,f_count);
		valField2=e_grid.QuickGetText(1,f_count);
		if (e_grid.QuickGetText(2,f_count)!=NULL )
		{
			valField3=e_grid.QuickGetText(2,f_count);
		}
		else
		{
			valField3="0";
		}
		if (strf!=L"")
		{
			cmd=cmd+"  delete  from Limit_Mapping where [login]='" + GridTradeAndOrder::m_selected_login + "' and symbol='" + valField1 + "'   insert into Limit_Mapping([login],symbol,limit,LimitSell) values('" + GridTradeAndOrder::m_selected_login + "','" + valField1 + "','" + valField2 + "','" + valField3 + "')";
		}
	}	
	
	pRstAuthors->Open(cmd,strCnn, adOpenStatic,adLockReadOnly,adCmdText);    			

	AfxMessageBox(L"Limit has been updated");
}
