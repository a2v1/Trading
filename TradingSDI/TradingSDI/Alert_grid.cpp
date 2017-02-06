#include "stdafx.h"
#include "Alert_grid.h"
#include "OutputWnd.h"


BEGIN_MESSAGE_MAP(Alert_grid,CUGCtrl)	


END_MESSAGE_MAP()

Alert_grid::Alert_grid(void)
{
}


Alert_grid::~Alert_grid(void)
{
}


void Alert_grid::OnSetup()
{

int	nRow = 0, nCol = 0;
	// ****************************************************************
	// ** Set up columns
	// ****************************************************************
	CUGCell cell;

	COutputWnd::m_alertgrid.GetGridDefault(&cell);
	//cell.SetBackColor(MY_COLOR_BACK);
	//cell.SetTextColor(MY_COLOR_TEXT);
	SetGridDefault(&cell);
	EnableExcelBorders(TRUE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetDefFont(0);
	SetSH_Width(0);
	
	// Number
	        
	  		SetNumberCols(15);
			QuickSetText(0,-1,L"Status");
			SetColWidth(0,60);
			QuickSetText(1,-1,L"Login");
			SetColWidth(1,65);
			QuickSetText(2,-1,L"OrderNo");	
			SetColWidth(2,65);
			
			QuickSetText(3,-1,L"OrderTime");
			SetColWidth(3,160);
			
			QuickSetText(4,-1,L"Symbol");
			SetColWidth(4,80);
			QuickSetText(5,-1,L"OrderType");	
			SetColWidth(5,80);
			QuickSetText(6,-1,L"Qty");
			SetColWidth(6,50);
			QuickSetText(7,-1,L"PRICE");
			SetColWidth(7,60);
			
			QuickSetText(8,-1,L"StopLoss");
			SetColWidth(8,40);
			QuickSetText(9,-1,L"Comment");
			SetColWidth(9,40);
			SetColWidth(10,160);
			QuickSetText(10,-1,L"Order Modify Time");
			QuickSetText(11,-1,L"Reason");
			SetColWidth(11,50);
			SetColWidth(12,160);
			QuickSetText(12,-1,L"Status Change Time");
			QuickSetText(13,-1,L"State");
			SetColWidth(13,30);
			QuickSetText(14,-1,L"Remark");
			SetColWidth(14,160);
			

			
	//// Header font
	//for(int i = 0; i < GetNumberCols(); i++)
	//{
	//	QuickSetFont(i, -1, 1);
	//}	


}

BOOL Alert_grid::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	

	return CUGCtrl::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
