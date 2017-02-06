// ClientHelpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "ClientHelpDlg.h"
#include "afxdialogex.h"


// ClientHelpDlg dialog

IMPLEMENT_DYNAMIC(ClientHelpDlg, CDialogEx)

ClientHelpDlg::ClientHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ClientHelpDlg::IDD, pParent)
{

}

ClientHelpDlg::~ClientHelpDlg()
{
}

void ClientHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ClientHelpDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDITSEARCH, &ClientHelpDlg::OnEnChangeEditsearch)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &ClientHelpDlg::OnBnClickedOk)
	
END_MESSAGE_MAP()


// ClientHelpDlg message handlers


void ClientHelpDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	


}


BOOL ClientHelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//database initialization
		
		CoInitialize(NULL);		
		hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CheckData;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");			
		if(SUCCEEDED(hr))
		{
			hr=session.Open(connection);							
		}

	SetWindowPos(this,40, 60, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	

	client_grid .AttachGrid(this ,IDC_STATICGRID);
	client_grid.SetColWidth(0,75);
	client_grid.SetColWidth(1,75);
	client_grid.SetColWidth(2,80);
	client_grid.SetColWidth(3,82);
	client_grid.SetColWidth(4,92);
	client_grid.SetColWidth(5,93);
	client_grid.SetColWidth(6,93);
	client_grid.SetColWidth(7,93);
	client_grid.SetColWidth(8,92);

	client_grid.QuickSetText(0,-1,L"LOGIN");
	client_grid.QuickSetText(1,-1,L"NAME");
	client_grid.QuickSetText(2,-1,L"COMMENTYN");
	client_grid.QuickSetText(3,-1,L"IGNOREYN");
	client_grid.QuickSetText(4,-1,L"CLIENTGROUP1");
	client_grid.QuickSetText(5,-1,L"CLIENTGROUP2");
	client_grid.QuickSetText(6,-1,L"CLIENTGROUP3");
	client_grid.QuickSetText(7,-1,L"CLIENTGROUP4");
	client_grid.QuickSetText(8,-1,L"CREDITCLIENT");
	
	getdata();
	return TRUE;  // return TRUE unless you set the focus to a control

}	


void ClientHelpDlg::getdata()
{
	CCommand<CAccessor<Client_Table> > table;				 	
		char* strCommand_char="SELECT  [V_login],[V_Name],[Comment_YN],[Ignore_YN],[client_group],[Client_Group1],[Client_Group2],[Client_Group4],[Client_Credit]FROM [CheckData].[dbo].[Client]";
		hr=table.Open(session,strCommand_char);							 			 		 				 	
	    CString strBuffer=L""; 

		if(SUCCEEDED(hr))
		{
			int row_number =0;
			while (table.MoveNext() == S_OK)
			{	
				client_grid.InsertRow(row_number);
				client_grid.QuickSetText(0,row_number,table.V_login);
				client_grid.QuickSetText(1,row_number,table.V_Name);
				client_grid.QuickSetText(2,row_number,table.Comment_YN);
				client_grid.QuickSetText(3,row_number,table.Ignore_YN);
				client_grid.QuickSetText(4,row_number,table.client_group);
				client_grid.QuickSetText(5,row_number,table.Client_Group1);
				client_grid.QuickSetText(6,row_number,table.Client_Group2);
				client_grid.QuickSetText(7,row_number,table.Client_Group4);
			    strBuffer.Format( _T("%.2f"), table.Client_Credit );
				client_grid.QuickSetText(8,row_number,strBuffer);
				row_number=row_number+1;
			}		
		}			
		client_grid.RedrawAll();
		table.Close();

}
void ClientHelpDlg::OnEnChangeEditsearch()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the 
        client_grid.SetNumberRows(0);
	
		//e_grid.GetDataSource
		CString edit_val;
		CCommand<CAccessor<Client_Table> > table;	
		CString  str_command=L"";
		GetDlgItemText(IDC_EDITSEARCH,edit_val);

		str_command.Format(L"SELECT  [V_login],[V_Name],[Comment_YN],[Ignore_YN],[client_group],[Client_Group1],[Client_Group2],[Client_Group4],[Client_Credit] FROM [CheckData].[dbo].[Client] where [V_Name] like '%s%s'",edit_val,L"%");
		_bstr_t bstr_command=str_command;
		char* strCommand_char=bstr_command;
		hr=table.Open(session,strCommand_char);	
		CString strBuffer=L"";
    	if(SUCCEEDED(hr))
		{
			int row_number =0;
			while (table.MoveNext() == S_OK)
			{	
				client_grid.InsertRow(row_number);
				client_grid.QuickSetText(0,row_number,table.V_login);
				client_grid.QuickSetText(1,row_number,table.V_Name);
				client_grid.QuickSetText(2,row_number,table.Comment_YN);
				client_grid.QuickSetText(3,row_number,table.Ignore_YN);
				client_grid.QuickSetText(4,row_number,table.client_group);
				client_grid.QuickSetText(5,row_number,table.Client_Group1);
				client_grid.QuickSetText(6,row_number,table.Client_Group2);
				client_grid.QuickSetText(7,row_number,table.Client_Group4);
				strBuffer.Format( _T("%.2f"), table.Client_Credit );
				client_grid.QuickSetText(8,row_number,strBuffer);	
				row_number=row_number+1;
				
			}		
		}	
		client_grid.RedrawAll();
		table.Close();
}

void ClientHelpDlg::OnClose()
{
	session.Close();
	connection.Close();
	CDialogEx::OnClose();
}