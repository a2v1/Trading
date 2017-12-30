// UserCreate.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "UserCreate.h"
#include "afxdialogex.h"
#include "UserTable.h"

// UserCreate dialog

IMPLEMENT_DYNAMIC(UserCreate, CDialogEx)

	UserCreate::UserCreate(CWnd* pParent /*=NULL*/)
	: CDialogEx(UserCreate::IDD, pParent)
	, m_userID(_T(""))
	, m_pswd(_T(""))
	, m_ConfrimPswrd(_T(""))
{

}

UserCreate::~UserCreate()
{
}

void UserCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_userID);
	DDX_Text(pDX, IDC_PASSWORD, m_pswd);
	DDX_Text(pDX, IDC_CONFIRMPASSWRD, m_ConfrimPswrd);
}


BEGIN_MESSAGE_MAP(UserCreate, CDialogEx)
	ON_BN_CLICKED(ID_USERCREATE, &UserCreate::OnBnClickedUsercreate)
END_MESSAGE_MAP()


// UserCreate message handlers
BOOL UserCreate::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return true;
}

void UserCreate::OnBnClickedUsercreate()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_userID && m_pswd.IsEmpty() && m_ConfrimPswrd.IsEmpty())
	{
		return;
	}
	CDataSource connection;
	CSession session;
	HRESULT hr;
	CoInitialize(NULL);		
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=64.251.7.161;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");			
	if(SUCCEEDED(hr))
	{
		hr=session.Open(connection);							
	}


	if(m_pswd.Trim().Compare(m_ConfrimPswrd.Trim())==0)
	{
		CString Str_command=L"";
		Str_command.Format(L"EXEC PROC_InsertUserCreate '%s','%s'",m_userID,m_pswd);

		CCommand<CNoAccessor, CNoRowset>cmd;	
		if (SUCCEEDED(hr))
		{
			hr=cmd.Open(session,LPCTSTR(Str_command));							 			 		 				 	
		}
		cmd.Close();
		if (SUCCEEDED(hr))
		{
			AfxMessageBox(L"User has been created !!!",MB_ICONINFORMATION);	
		}
	}
	else
	{
		AfxMessageBox(L"Password Not matched!!!",MB_ICONWARNING);
	}
	session.Close();
	connection.Close();   

}
