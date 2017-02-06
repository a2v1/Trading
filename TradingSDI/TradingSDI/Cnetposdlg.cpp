// Cnetposdlg.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "Cnetposdlg.h"
#include "afxdialogex.h"


// Cnetposdlg dialog

IMPLEMENT_DYNAMIC(Cnetposdlg, CDialogEx)

Cnetposdlg::Cnetposdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cnetposdlg::IDD, pParent)
{

}

Cnetposdlg::~Cnetposdlg()
{
}

void Cnetposdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IGQTY, m_igqty);
	DDX_Control(pDX, IDC_LOGIN, m_login);
	DDX_Control(pDX, IDC_GROUP, m_group);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date);	
	DDX_Control(pDX, IDC_IGMAIN, m_igmain);
	DDX_Control(pDX, IDC_IGCOMMENT, ig_comment);
}


BEGIN_MESSAGE_MAP(Cnetposdlg, CDialogEx)
	//ON_WM_ACTIVATE()
	ON_WM_PAINT()
	//ON_BN_CLICKED(IDC_IGQTY, &Cnetposdlg::OnBnClickedIgqty)
	ON_BN_CLICKED(IDC_IGCOMMENT, &Cnetposdlg::OnBnClickedIgcomment)
END_MESSAGE_MAP()


// Cnetposdlg message handlers


/*(void Cnetposdlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: Add your message handler code here
}*/


void Cnetposdlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CPen pen;
	CBrush brush;
	// TODO: Add your message handler code here
	pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	brush.CreateStockObject(DKGRAY_BRUSH);


	
	dc.SelectObject(&pen);
	dc.SelectObject(&brush);


	dc.Rectangle(0,0,1000,400);



	CDialog::OnPaint();	
		
		
}




BOOL Cnetposdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
//
//CRect rect;
//CWnd *pWnd = pDlg->GetDlgItem(YOUR_CONTROL_I);
//pWnd->GetWindowRect(&rect);
//pDlg->ScreenToClient(&rect); //optional step - see below
//
//	// EXCEPTION: OCX Property Pages should return FALSE
	return true;
}


void Cnetposdlg::OnBnClickedIgcomment()
{
	// TODO: Add your control notification handler code here
}
