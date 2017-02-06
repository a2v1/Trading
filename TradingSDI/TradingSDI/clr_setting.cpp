// clr_setting.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "clr_setting.h"
#include "afxdialogex.h"
#include "dealing.h"
#include "ugctrl.h"


// clr_setting dialog

IMPLEMENT_DYNAMIC(clr_setting, CDialogEx)

clr_setting::clr_setting(CWnd* pParent /*=NULL*/)
	: CDialogEx(clr_setting::IDD, pParent)
{


}

clr_setting::~clr_setting()
{
}

void clr_setting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CLR, m_combo);
	DDX_Control(pDX, IDC_BUTTON_CLR, btn_color);
	
}


BEGIN_MESSAGE_MAP(clr_setting, CDialogEx)
	
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_CLR, &clr_setting::OnBnClickedButtonClr)
	ON_CBN_SELCHANGE(IDC_COMBO_CLR, &clr_setting::OnCbnSelchangeComboClr)
END_MESSAGE_MAP()


// clr_setting message handlers






void clr_setting::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	/*CPen pen;
	CBrush brush;
	// TODO: Add your message handler code here
	pen.CreatePen(PS_SOLID,1,RGB(255,255,255));
	brush.CreateStockObject(WHITE_BRUSH);


	
	dc.SelectObject(&pen);
	dc.SelectObject(&brush);


	dc.Rectangle(0,0,1000,400);*/



	CDialog::OnPaint();	
		
}


void clr_setting::OnBnClickedButtonClr()
{
	// TODO: Add your control notification handler code here
	


	CColorDialog dlgclr;
	if(dlgclr.DoModal()==IDOK);
	{
		
		if( m_combo.GetCurSel() == 0 )
		{                			
		}
	

	}

}




void clr_setting::OnCbnSelchangeComboClr()
{
	

/*CString str1, str2,str3;

int n;
for (int i = 0; i < m_combo.GetCount(); i++)
{
	n = m_combo.GetLBTextLen(i);
	m_combo.GetLBText(i, str1.GetBuffer(n));
   str1.ReleaseBuffer();
  
   str2.Format(_T("item %d: %s\r\n"), i, str1.GetBuffer(0));
   str3.Format(_T("item %d: %s\r\n"), i, str2.GetBuffer(1));

  
}*/


}


BOOL clr_setting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_combo.AddString(_T("ORDER CANCELED"));
	m_combo.AddString(_T("ORDER PLACED"));
	m_combo.AddString(_T("Trade Done"));
				//m_combo.AddString(_T("ORDER CANCEL"));

	return TRUE;  // return TRUE unless you set the focus to a control
	
}

