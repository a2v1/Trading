
// TradingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SymbolMapping.h"
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" \
	no_namespace rename("EOF", "EndOfFile")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

SymbolMapping::SymbolMapping(CWnd* pParent /*=NULL*/)
	: CDialogEx(SymbolMapping::IDD, pParent),
	m_bShowGripper(true),
	m_szMinimum(0, 0),
	m_hGripper(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void SymbolMapping::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);	
	//CListCtrl m_list;
	//DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(SymbolMapping, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_WM_CLOSE()	
	ON_BN_CLICKED(IDC_BUTTON1, &SymbolMapping::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &SymbolMapping::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTradingDlg message handlers

BOOL SymbolMapping::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//SETTING THE POSITION OF DILOG
	CRect rect;
	GetClientRect(&rect);
	MoveWindow( rect.left+10,rect.top+115,rect.Width()+5,rect.Height());


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
	if (m_bShowGripper && ((GetStyle() & WS_THICKFRAME) != 0))
	{
		SMovingChild s;
		s.m_rcInitial.SetRect(-GetSystemMetrics(SM_CXVSCROLL), -GetSystemMetrics(SM_CYHSCROLL), 0, 0);
		s.m_rcInitial.OffsetRect(rcClient.BottomRight());
		m_hGripper = CreateWindow(_T("Scrollbar"), _T("size"), WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP,
			s.m_rcInitial.left, s.m_rcInitial.top, s.m_rcInitial.Width(), s.m_rcInitial.Height(),
			m_hWnd, NULL, AfxGetInstanceHandle(), NULL);
		ASSERT(m_hGripper != NULL);
		if (m_hGripper != NULL)
		{
			s.m_hWnd = m_hGripper;
			s.m_dXMoveFrac = 1.0;
			s.m_dYMoveFrac = 1.0;
			s.m_dXSizeFrac = 0.0;
			s.m_dYSizeFrac = 0.0;
			m_MovingChildren.push_back(s);

			// put the gripper first in the z-order so it paints first and doesn't obscure other controls
			::SetWindowPos(m_hGripper, HWND_TOP,0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
		}
	}


	CRect rectDummy;
	rectDummy.SetRectEmpty();



	e_grid.AttachGrid(this ,IDC_STATIC);
	e_grid.SetColWidth(0,150);
	e_grid.SetColWidth(1,150);
	e_grid.QuickSetText(0,-1,L"SYMBOL");
	e_grid.QuickSetText(1,-1,L"MAPPING SYMBOL");


	//data base initialization
	CoInitialize(NULL);		
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=TradeDataBase;Data Source=64.251.7.161;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");			
	if(SUCCEEDED(hr))
	{
		hr=session.Open(connection);							
	}


	//display data on grid
	getSymbolData();

	return TRUE;  // return TRUE  unless you set the focus to a control
}



void SymbolMapping::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
void SymbolMapping::OnBnClickedButton1()
{
	_bstr_t valField1("");
	_bstr_t valField2("");
	_bstr_t buff_cmd(""); 	
	//HRESULT hr = S_OK;		 
	//CoInitialize(NULL);
	//        // Define string variables.		 
	//_bstr_t strCnn("Provider=SQLOLEDB;SERVER=64.251.7.161;Database=tradedatabase;uid=sa;pwd=ok@12345;");
	// //_bstr_t strCnn("Provider=SQLOLEDB;SERVER=.;Database=CHECKDATA;uid=sa;pwd=ok;");
	//      _RecordsetPtr pRstAuthors = NULL;

	//    // Call Create instance to instantiate the Record set
	//    hr = pRstAuthors.CreateInstance(__uuidof(Recordset)); 
	//    if(FAILED(hr))
	//    {           
	//    }		

	if(FAILED(hr))
	{
		return;
	}
	int noofrows=e_grid.GetNumberRows();
	for (int f_count=0;f_count<noofrows-1;f_count++)
	{
		valField1=e_grid.QuickGetText(0,f_count);
		valField2=e_grid.QuickGetText(1,f_count);

		if(!SysStringLen(valField1)==0)
		{
			buff_cmd=buff_cmd+"insert into symbol_mapping values('" + valField1 + "','" + valField2 + "')";
		}
	}	


	buff_cmd=" delete from symbol_mapping   delete from last_tick  "+buff_cmd;
	//pRstAuthors->Open(cmd,strCnn, adOpenStatic,adLockReadOnly,adCmdText); 
	hr=cmd.Open(session,(LPCTSTR)buff_cmd);

	AfxMessageBox(L"Symbol has been updated");

	cmd.Close();
	session.Close();
	connection.Close();
}


void SymbolMapping::OnBnClickedButton2()
{

	session.Close();
	connection.Close();
	CDialog::OnCancel();
}


void SymbolMapping::getSymbolData()
{
	//by oledb
	CString str_command=L"";
	CCommand<CAccessor<Symbol_MapTable> > table;				 	
	str_command="select symbol,mapping_symbol from symbol_mapping";
	hr=table.Open(session,(LPCTSTR)str_command);							 			 		 				 

	if(SUCCEEDED(hr))
	{
		int row_number =0;
		while (table.MoveNext() == S_OK)
		{	

			e_grid.QuickSetText(0,row_number,table.m_Symbol);
			e_grid.QuickSetText(1,row_number,table.m_mapping_Symbol);
			row_number++;
		}		
	}			
	e_grid.RedrawAll();
	table.Close();
}

void SymbolMapping::OnClose()
{
	session.Close();
	connection.Close();
	CDialogEx::OnClose();
}