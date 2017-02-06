// ClientCreate.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "ClientCreate.h"
#include "afxdialogex.h"
#include "ClientHelpDlg.h"

// ClientCreate dialog

IMPLEMENT_DYNAMIC(ClientCreate, CDialogEx)

ClientCreate::ClientCreate(CWnd* pParent /*=NULL*/)
	: CDialogEx(ClientCreate::IDD, pParent)
	
{

}

ClientCreate::~ClientCreate()
{
}

void ClientCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_login);
	DDX_Control(pDX, IDC_EDIT2, m_name);
	DDX_Control(pDX, IDC_EDIT3, m_group1);
	DDX_Control(pDX, IDC_EDIT4, m_group2);
	DDX_Control(pDX, IDC_EDIT5, m_group3);
	DDX_Control(pDX, IDC_CHECK1, m_commnentYN);
	DDX_Control(pDX, IDC_CHECK2, m_ignoreYN);
	DDX_Control(pDX, IDC_EDIT6, m_creditclientf);
}


BEGIN_MESSAGE_MAP(ClientCreate, CDialogEx)
	ON_BN_CLICKED(IDSAVE, &ClientCreate::OnBnClickedSave)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT1, &ClientCreate::OnEnChangeEdit1)

	ON_BN_CLICKED(IDC_DELETEBTN, &ClientCreate::OnBnClickedDeletebtn)
	ON_EN_KILLFOCUS(IDC_EDIT1, &ClientCreate::OnEnKillfocusEdit1)
END_MESSAGE_MAP()


// ClientCreate message handlers


BOOL ClientCreate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//database initilization
		


    return true;
}


void ClientCreate::OnBnClickedSave()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();

	CDataSource connection;
	CSession session;
	HRESULT hr;
	CoInitialize(NULL);		
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CheckData;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");			
	if(SUCCEEDED(hr))
	{
		hr=session.Open(connection);							
	}


	CString strlogin,strName,strComment,strIgnore,strGroup1,strGroup2,strGroup3,strGroup4,strCreditClient ;

	m_login.GetWindowTextW(strlogin);
	m_name.GetWindowTextW(strName);
	if(m_commnentYN.GetCheck()==1)
	{
		strComment=L"Y";
	  
	}
	else{

		strComment=L"N";
	}

	if(m_ignoreYN.GetCheck()==1)
	{
		strIgnore=L"Y";
	  
	}
	else{

		strIgnore=L"N";
	}

	m_group1.GetWindowTextW(strGroup1);
	m_group2.GetWindowTextW(strGroup2);
	m_group3.GetWindowTextW(strGroup3);
    
	m_creditclientf.GetWindowTextW(strCreditClient);	
	double d_bal = _tstof((LPCTSTR)strCreditClient);
    strCreditClient.Format(_T("%.2f"),d_bal);

	if(strlogin!=L"")
	{
		CString Str_command=L"";
		Str_command.Format(L"PROC_InsertClient '%s','%s','%s','%s','%s','%s','%s','%s','%f'",strlogin,strName,strComment,strIgnore,strGroup1,strGroup2,strGroup3,strGroup4,strCreditClient);
	
	
		CCommand<CNoAccessor, CNoRowset>cmd;				
		hr=cmd.Open(session,LPCTSTR(Str_command));							 			 		 				 	
		cmd.Close();	
		session.Close();
		AfxMessageBox(L"Client has been created !!!");	
	}
	else{
	
	    AfxMessageBox(L"Fields are Empty!!!");	
	
	}

	// TODO: Add your control notification handler code here
}


void ClientCreate::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	
	CDialogEx::OnClose();
}


void ClientCreate::OnEnChangeEdit1()
{	
}


void ClientCreate::OnBnClickedDeletebtn()
{
	// TODO: Add your control notification handler code here
	ClientHelpDlg dlg;
	dlg.DoModal();
}


void ClientCreate::OnEnKillfocusEdit1()
{
	// TODO: Add your control notification handler code here
	CDataSource connection;
	CSession session;
	HRESULT hr;
	CoInitialize(NULL);		
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CheckData;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");			
	if(SUCCEEDED(hr))
	{
		hr=session.Open(connection);							
	}


	CString str_login=L"";

	
	m_login.GetWindowTextW(str_login);
	if(str_login.IsEmpty())
	{
		m_name.SetWindowTextW(L"");
		m_commnentYN.SetCheck(0);
		m_ignoreYN.SetCheck(0);
		m_group1.SetWindowTextW(L"");
		m_group2.SetWindowTextW(L"");
		m_group3.SetWindowTextW(L"");
		m_creditclientf.SetWindowTextW(L"");
	}
    else
	{

	CCommand<CAccessor<Client_Table> > table;	
	CString strcommand=L"";
	strcommand.Format(L"SELECT [V_login],[V_Name],[Comment_YN],[Ignore_YN],[client_group],[Client_Group1],[Client_Group2],[Client_Group4],[Client_Credit] FROM [Checkdata].[dbo].[Client] where [V_Login] ='%s'",str_login);
			 	
		
		hr=table.Open(session,(LPCTSTR)strcommand);							 			 		 				 	
	    CString str=L"";
		if(SUCCEEDED(hr))
		{
			while (table.MoveNext() == S_OK)
			{
				
				m_name.SetWindowTextW(table.V_Name);
				//comment YN
				if (_tcscmp(table.Comment_YN,_T("N"))==0  )
				{
				    m_commnentYN.SetCheck(0);
				}
				else
				{
					m_commnentYN.SetCheck(1);
				}
			
			   // Ignore YN
				if (_tcscmp(table.Ignore_YN,_T("N"))==0 )
				{
					m_ignoreYN.SetCheck(0);
				}
				else
				{
					m_ignoreYN.SetCheck(1);
				}
				m_group1.SetWindowTextW(table.client_group);
				m_group2.SetWindowTextW(table.Client_Group1);
				m_group3.SetWindowTextW(table.Client_Group2);
				str.Format(_T("%.2f",table.Client_Credit));
				m_creditclientf.SetWindowTextW(str);
			}
        }
		table.Close();
		session.Close();
	}
//AfxMessageBox(L"1");
}
