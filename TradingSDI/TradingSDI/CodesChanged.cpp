#include "stdafx.h"
#include "CodesChanged.h"
#include "resource.h"
#include <afxdisp.h>
#include <time.h>
#include <locale.h>
#include "MainFrm.h"
#include "document.h"
#include <iostream>
#include "Login.h"
#include "CodeChangedTable.h"

using namespace std;
using namespace rapidjson;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CCodesChanged,CUGCtrl)	
	ON_WM_SIZE()
	ON_WM_TIMER()		
END_MESSAGE_MAP()

int CCodesChanged::insertFilterFlag=0;
CCodesChanged::st_Dealing_Array CCodesChanged::m_st_Dealing_Array;	
CCodesChanged::st_Dealing_Array CCodesChanged::m_st_Dealing_Grid_array;
CMutex CCodesChanged::dealing_mutex;

CString CCodesChanged::col0_val=L"";
CString CCodesChanged::col1_val=L"";
CString CCodesChanged::col2_val=L"";
CString CCodesChanged::col3_val=L"";
CString CCodesChanged::col4_val=L"";
CString CCodesChanged::col5_val=L"";
CString CCodesChanged::col6_val=L"";
CString CCodesChanged::col7_val=L"";
CString CCodesChanged::col8_val=L"";
CString CCodesChanged::col9_val=L"";
CString CCodesChanged::col10_val=L"";
CString CCodesChanged::col11_val=L"";
CString CCodesChanged::col12_val=L"";
CString CCodesChanged::col13_val=L"";
CString CCodesChanged::col14_val=L"";
CString CCodesChanged::col15_val=L"";
CString CCodesChanged::col16_val=L"";
CString CCodesChanged::col17_val=L"";

int CCodesChanged::col_click=0;
int CCodesChanged::a_d=0;


UINT Show_CCodesChanged(void *pParam);
CCodesChanged::CCodesChanged(void)
{
	UGXPThemes::UseThemes(false);	
	col_click=0;
	a_d=0;
}


CCodesChanged::~CCodesChanged(void)
{
	//delete m_pThread;
	UGXPThemes::CleanUp();
}

int CCodesChanged::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{

	if(ID == UGCT_DROPLIST)
	{
		return OnDropList(ID, col, row, msg, param);
	}

    return 0;
}
void CCodesChanged::OnSetup()
{
	try
	{					
		int	nIndex = 0;
		CUGCell cell;
		GetGridDefault(&cell);
		SetGridDefault(&cell);
		EnableExcelBorders(FALSE);
		SetHighlightRow(TRUE, FALSE);
		SetDoubleBufferMode(TRUE);
		SetUserSizingMode( TRUE );			
		// Create and set default font
		AddFont(L"Arial", -12, FW_NORMAL);
		AddFont(L"Arial", -12, FW_BOLD);
		SetDefFont(0);	
		CDC * pDC;	
		int iHeight;
		int i, j;	
		pDC = GetDC( );	
		iHeight = -MulDiv( 8, GetDeviceCaps( pDC->m_hDC, LOGPIXELSY), 72 );
		m_font.CreateFont( iHeight, 0, 0, 0, 400, 0, 0, 0, 0, 0, 0, 0, 0, _T( "MS Sans Serif" ) );	
		ReleaseDC( pDC );
		SetDefFont( &m_font );		
		GetGridDefault( &cell );
		cell.SetAlignment( UG_ALIGNCENTER | UG_ALIGNVCENTER );
		SetGridDefault( &cell );
		SetNumberCols( 7);		
		m_iArrowIndex = AddCellType( &m_sortArrow );
		SetCurrentCellMode( 2 );
		UseHints( TRUE );
		SetSH_Width( 0 );	
		QuickSetCellType( 0, -1, m_iArrowIndex );
		SortBy( 0, UG_SORT_ASCENDING );
		m_iSortCol = 0;
		m_bSortedAscending = TRUE;		
		InitMenu();
		SetTimer(0, 100, NULL);

		m_pThreads=AfxBeginThread(Show_CCodesChanged, this);	
	}
	 catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"   writeData");			
	}
}

void CCodesChanged::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();
	
	EnableMenu(TRUE);
	
	menu->AppendMenuW(MF_STRING|MF_UNCHECKED,2001,_T("Filter"));
	
	
	submenu.CreatePopupMenu();
}

void CCodesChanged::OnSheetSetup(int sheetNumber)
{
	int	nRow = 0, nCol = 0;	
	CUGCell cell;	
	SetGridDefault(&cell);
	EnableExcelBorders(TRUE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetDefFont(0);
	SetSH_Width(0);		
			
	SetNumberCols(18);

	QuickSetText(0,-1,L"CodeChange");
	SetColWidth(0,140);
	QuickSetText(1,-1,L"Login");
	SetColWidth(1,70);
	QuickSetText(2,-1,L"Order#");	
	SetColWidth(2,70);			
	QuickSetText(3,-1,L"Order_In_Time");
	SetColWidth(3,180);			
	QuickSetText(4,-1,L"Deal#");
	SetColWidth(4,70);
	QuickSetText(5,-1,L"Symbol");	
	SetColWidth(5,100);
	QuickSetText(6,-1,L"Type");
	SetColWidth(6,70);
	QuickSetText(7,-1,L"Volume");
	SetColWidth(7,80);			
	QuickSetText(8,-1,L"Price");
	SetColWidth(8,70);
	QuickSetText(9,-1,L"Comment");
	SetColWidth(9,80);	
	QuickSetText(10,-1,L"Status");
	SetColWidth(10,60);
	QuickSetText(11,-1,L"Opposite_Deal#");
	SetColWidth(11,60);
	QuickSetText(12,-1,L"Deal_Time");
	SetColWidth(12,60);
	QuickSetText(13,-1,L"Symbol");
	SetColWidth(13,60);
	QuickSetText(14,-1,L"Type");
	SetColWidth(14,70);
	QuickSetText(15,-1,L"Volume");
	SetColWidth(15,80);			
	QuickSetText(16,-1,L"Price");
	SetColWidth(16,70);
	QuickSetText(17,-1,L"Status");
	SetColWidth(17,60);
	
												
	// Header font
	for(int i = 0; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}	
}

void CCodesChanged::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();
	CString string;
	if(cell.GetLabelText() != NULL)
		string = cell.GetLabelText();

	if(processed){
		if(cell.GetCellType() == m_nSpinIndex)
			return ;
	}

	if(nParam == CELLTYPE_IS_EDITABLE || string == "CELLTYPE_IS_EDITABLE")
	{
		StartEdit();
	}
	

}	


int CCodesChanged::OnDropList(long ID,int col,long row,long msg,long param)
{
	if (msg==103)
	{
		if(CCodesChanged::insertFilterFlag==1 && row==0)
		{
			CString  strval=L"";
			CUGCell cell;
			GetCell(col,row,&cell);
			strval=cell.GetText();	
		}

		if(CCodesChanged::insertFilterFlag==1 && row==0 )
		{
			
			CString  strval=L"";
			CUGCell cell;
			GetCell(col,row,&cell);
			strval=cell.GetText();	
			if(col==0)
			{
				if (strval!=L"")
				{
					col0_val=strval;					
				}
				else
				{
					col0_val=L"ALL";					
				}
			}


			if(col==1)
			{
				if (strval!=L"")
				{
					col1_val=strval;					
				}
				else
				{
					col1_val=L"ALL";					
				}
			}

			if(col==2)
			{
				if (strval!=L"")
				{
					col2_val=strval;					
				}
				else
				{
					col2_val=L"ALL";					
				}
			}

			if(col==3)
			{
				if (strval!=L"")
				{
					col3_val=strval;					
				}
				else
				{
					col3_val=L"ALL";					
				}
			}

			if(col==4)
			{
				if (strval!=L"")
				{
				    col4_val=strval;					
				}
				else
				{
					col4_val=L"ALL";					
				}
			}

			if(col==5)
			{
				if (strval!=L"")
				{
					col5_val=strval;					
				}
				else
				{
					col5_val=L"ALL";					
				}
			}

			if(col==6)
			{
				if (strval!=L"")
				{
					col6_val=strval;					
				}
				else
				{
					col6_val=L"ALL";					
				}
			}

			if(col==7)
			{
				if (strval!=L"")
				{
					col7_val=strval;					
				}
				else
				{
					col7_val=L"ALL";					
				}
			}

			if(col==8)
			{
				if (strval!=L"")
				{
					col8_val=strval;					
				}
				else
				{
					col8_val=L"ALL";					
				}
			}

			if(col==9)
			{
				if (strval!=L"")
				{
					col9_val=strval;					
				}
				else
				{
					col9_val=L"ALL";					
				}
			}

			if(col==10)
			{
				if (strval!=L"")
				{
				    col10_val=strval;					
				}
				else
				{
				    col10_val=L"ALL";					
				}
			}

			if(col==11)
			{
				if (strval!=L"")
				{
					col11_val=strval;					
				}
				else
				{
					col11_val=L"ALL";					
				}
			}

			if(col==12)
			{
				if (strval!=L"")
				{
					col12_val=strval;					
				}
				else
				{
					col12_val=L"ALL";					
				}
			}

			if(col==13)
			{
				if (strval!=L"")
				{
					col13_val=strval;					
				}
				else
				{
					col13_val=L"ALL";					
				}
			}

			if(col==14)
			{
				if (strval!=L"")
				{
					col14_val=strval;					
				}
				else
				{
					col14_val=L"ALL";					
				}
			}

			if(col==15)
			{
				if (strval!=L"")
				{
					col15_val=strval;					
				}
				else
				{
					col15_val=L"ALL";					
				}
			}
			if(col==16)
			{
				if (strval!=L"")
				{
					col16_val=strval;					
				}
				else
				{
					col16_val=L"ALL";					
				}
			}
			if(col==17)
			{
				if (strval!=L"")
				{
					col17_val=strval;					
				}
				else
				{
					col17_val=L"ALL";					
				}
			}
		}
	}

	return true;

}

int CCodesChanged::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{

		if(CCodesChanged::insertFilterFlag==1 && row==0)
		{
			CString  strval=L"";
			CUGCell cell;
			GetCell(col,row,&cell);
			strval=string;	
		}

		if(CCodesChanged::insertFilterFlag==1 && row==0 )
		{
			
			CString  strval=L"";
			CUGCell cell;
			QuickSetText(col,row,string );
			GetCell(col,row,&cell);
			strval=cell.GetText();	

			if(col==0)
			{
				if (strval!=L"")
				{
					col0_val=strval;					
				}
				else
				{
					col0_val=L"ALL";					
				}
			}


			if(col==1)
			{
				if (strval!=L"")
				{
					col1_val=strval;					
				}
				else
				{
					col1_val=L"ALL";					
				}
			}

			if(col==2)
			{
				if (strval!=L"")
				{
					col2_val=strval;					
				}
				else
				{
					col2_val=L"ALL";					
				}
			}

			if(col==3)
			{
				if (strval!=L"")
				{
					col3_val=strval;					
				}
				else
				{
					col3_val=L"ALL";					
				}
			}

			if(col==4)
			{
				if (strval!=L"")
				{
				    col4_val=strval;					
				}
				else
				{
					col4_val=L"ALL";					
				}
			}

			if(col==5)
			{
				if (strval!=L"")
				{
					col5_val=strval;					
				}
				else
				{
					col5_val=L"ALL";					
				}
			}

			if(col==6)
			{
				if (strval!=L"")
				{
					col6_val=strval;					
				}
				else
				{
					col6_val=L"ALL";					
				}
			}

			if(col==7)
			{
				if (strval!=L"")
				{
					col7_val=strval;					
				}
				else
				{
					col7_val=L"ALL";					
				}
			}

			if(col==8)
			{
				if (strval!=L"")
				{
					col8_val=strval;					
				}
				else
				{
					col8_val=L"ALL";					
				}
			}

			if(col==9)
			{
				if (strval!=L"")
				{
					col9_val=strval;					
				}
				else
				{
					col9_val=L"ALL";					
				}
			}

			if(col==10)
			{
				if (strval!=L"")
				{
				    col10_val=strval;					
				}
				else
				{
				    col10_val=L"ALL";					
				}
			}

			if(col==11)
			{
				if (strval!=L"")
				{
					col11_val=strval;					
				}
				else
				{
					col11_val=L"ALL";					
				}
			}

			if(col==12)
			{
				if (strval!=L"")
				{
					col12_val=strval;					
				}
				else
				{
					col12_val=L"ALL";					
				}
			}

			if(col==13)
			{
				if (strval!=L"")
				{
					col13_val=strval;					
				}
				else
				{
					col13_val=L"ALL";					
				}
			}

			if(col==14)
			{
				if (strval!=L"")
				{
					col14_val=strval;					
				}
				else
				{
					col14_val=L"ALL";					
				}
			}

			if(col==15)
			{
				if (strval!=L"")
				{
					col15_val=strval;					
				}
				else
				{
					col15_val=L"ALL";					
				}
			}
			if(col==16)
			{
				if (strval!=L"")
				{
					col16_val=strval;					
				}
				else
				{
					col16_val=L"ALL";					
				}
			}
			if(col==17)
			{
				if (strval!=L"")
				{
					col17_val=strval;					
				}
				else
				{
					col17_val=L"ALL";					
				}
			}
		}
		return TRUE;

}

void CCodesChanged::OnTimer(UINT nIDEvent)
{		
    CCodesChanged::dealing_mutex.Lock(); 
	int r_count=CCodesChanged::m_st_Dealing_Grid_array.Total();
	CCodesChanged::dealing_mutex.Unlock();		
	int grid_total=GetNumberRows();
	
	if (CCodesChanged::insertFilterFlag==1)
	{
			r_count=r_count+1;
	}		
	if (grid_total!=r_count)
	{			
		if (r_count>0)
		{
			SetNumberRows(r_count);					
		}
	}
	else
	{			
			RedrawAll();			
	}					
		
}		


void CCodesChanged::OnGetCell(int col,long row,CUGCell *cell)
{
		//m_logfile_g.LogEvent(L"Start OnGetCell");
		st_Dealing mst_grid={};
		int rows_no=0;
		rows_no=row;		
		UNREFERENCED_PARAMETER(col);
		UNREFERENCED_PARAMETER(row);
		UNREFERENCED_PARAMETER(*cell);		
		if ( col >= 0 && row == -1 )
		{	
		}
		else if ( row >= 0 && col == -1 )
		{	
		}
		else if ( col >= 0 && row >= 0 )
		{
			if (CCodesChanged::insertFilterFlag==1)
			{
				rows_no=row-1;				
				if (row==0)
				{
					return;
				}
			}
			if (col==0)
			{				
				mst_grid=m_st_Dealing_Grid_array[rows_no];				
				CString tmp=mst_grid.Section ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==1)
			{
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Login ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==2)
			{				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				double m_order=mst_grid.Order  ;

				CString tmp=L"" ;
				tmp.Format(L"%.0f",m_order);
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==3)
			{			
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Order_In_Time ;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==4)
			{				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				int m_deal=mst_grid.Deal ;

				CString tmp=L"" ;
				tmp.Format(L"%d",m_deal);
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==5)
			{				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Symbol ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,mst_grid.Symbol)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==6)
			{	
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Type1;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==7)
			{				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=L"";
				tmp.Format(L"%.2f",mst_grid.Volume);
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==8)
			{	
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=L"";
				tmp.Format(L"%.4f",mst_grid.Price);											
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==9)
			{	
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Comment;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==10)
			{	
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Status;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==11)
			{	
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Opposite_Deal;
															
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==12)
			{	
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Deal_Time;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==13)
			{	
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Symbol1;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==14)
			{	
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Type;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==15)
			{				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				double m_deal=mst_grid.Volume1 ;

				CString tmp=L"" ;
				tmp.Format(L"%.2f",m_deal);
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==16)
			{				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				double m_deal=mst_grid.Price1 ;

				CString tmp=L"" ;
				tmp.Format(L"%.4f",m_deal);
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
            else if (col==17)
			{	
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Status1;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
	 }
}


void CCodesChanged::OnMenuCommand(int col,long row,int section,int item)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(section);
	// init. local variables
	
	CMenu* pMenu;
	pMenu = GetPopupMenu();

	CMenu* submenu=pMenu->GetSubMenu(1);

	switch( item )
	{
	case 2001:
			   {
						filter();
						break;
			   }		  
	}
}
void CCodesChanged::filter()
{
	try
	{
	 CMenu *pMnenu;
	 pMnenu= GetPopupMenu();

	if ( CCodesChanged::insertFilterFlag==0)
	{
			addItemToCombobox();
			CCodesChanged::insertFilterFlag=1;
			InsertRow(0);
			for (int col_count=0;col_count<18;col_count++)
			{
				CUGCell cell;
				int row=0;
				int col=col_count;
				cell.ClearAll();
				cell.SetCellType(UGCT_DROPLIST);
				cell.SetCellTypeEx(UGCT_DROPLISTHIDEBUTTON);
				cell.SetParam(CELLTYPE_IS_EDITABLE);
				QuickSetRange(col,row,col,row,&cell);
				QuickSetLabelText(col,row,str[col_count]);
				SetFocus();
			}
			pMnenu->CheckMenuItem(2001,MF_CHECKED);

	}
	else
	{
		
		DeleteRow(0);
		CCodesChanged::insertFilterFlag=0;
		CCodesChanged::col0_val=L"";
		CCodesChanged::col1_val=L"";
		CCodesChanged::col2_val=L"";
		CCodesChanged::col3_val=L"";
		CCodesChanged::col4_val=L"";
		CCodesChanged::col5_val=L"";
		CCodesChanged::col6_val=L"";
		CCodesChanged::col7_val=L"";
		CCodesChanged::col8_val=L"";
		CCodesChanged::col9_val=L"";
		CCodesChanged::col10_val=L"";
		CCodesChanged::col11_val=L"";
		CCodesChanged::col12_val=L"";
		CCodesChanged::col13_val=L"";
		CCodesChanged::col14_val=L"";
		CCodesChanged::col15_val=L"";
		CCodesChanged::col16_val=L"";
		CCodesChanged::col17_val=L"";
		pMnenu->CheckMenuItem(2001,MF_UNCHECKED);
	}
	RedrawAll();
	}
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"   filter");			
	} 
 }



void CCodesChanged::addItemToCombobox()
{
	CStringArray arr;
	CStringArray arr1;
	CStringArray arr2;
	CStringArray arr3;	
	CStringArray arr4;
	CStringArray arr5;
	CStringArray arr6;	
	CStringArray arr7;	
	CStringArray arr8;	
	CStringArray arr9;
	CStringArray arr10;	
	CStringArray arr11;	
	CStringArray arr12;
	CStringArray arr13;
	CStringArray arr14;	
	CStringArray arr15;	
	CStringArray arr16;
	CStringArray arr17;

	
	try
	{
		int rows=1;
		rows=m_st_Dealing_Array.Total();	
		CString str_val=L"";	
		for (int forcount=0;forcount<18;forcount++)
		{
			str[forcount]=L"ALL\n";		
		}
		for (int forcount=0;forcount<rows;forcount++)
		{
			 st_Dealing m_st_Netposition={};
			 m_st_Netposition=m_st_Dealing_Array[forcount];
			for (int clocount=0;clocount<18;clocount++)
			{											
					if (clocount==0)
					{
						
						str_val=m_st_Netposition.Section;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr,str_val)==false && str_val!=L"")
						{
							str[0]=str[0]+str_val+L"\n";										
							arr.Add(str_val);							
						}
					}
					if (clocount==1)
					{
						str_val=m_st_Netposition.Login ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr1,str_val)==false  && str_val!=L"")
						{
							str[1]=str[1]+str_val+L"\n";										
							arr1.Add(str_val);
						}
					}


					if (clocount==2)
					{
						double  u_deal=m_st_Netposition.Order  ;
						str_val.Format(L"%.0f",u_deal );
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr2,str_val)==false  && str_val!=L"")
						{
							str[2]=str[2]+str_val+L"\n";										
							arr2.Add(str_val);
						}
					}


					if (clocount==3)
					{
						
						str_val=m_st_Netposition.Order_In_Time;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr3,str_val)==false  && str_val!=L"")
						{
							str[3]=str[3]+str_val+L"\n";										
							arr3.Add(str_val);
						}
					}

					if (clocount==4)
					{
						
						str_val.Format(L"%d",m_st_Netposition.Deal );
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr4,str_val)==false  && str_val!=L"")
						{
							str[4]=str[4]+str_val+L"\n";										
							arr4.Add(str_val);
						}
					}
					if (clocount==5)
					{
						str_val=m_st_Netposition.Symbol;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr5,str_val)==false  && str_val!=L"")
						{
							str[5]=str[5]+str_val+L"\n";										
							arr5.Add(str_val);
						}
					}

					if (clocount==6)
					{
						str_val=m_st_Netposition.Type1  ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr6,str_val)==false  && str_val!=L"")
						{
							str[6]=str[6]+str_val+L"\n";										
							arr6.Add(str_val);
						}
					}
					if (clocount==7)
					{
						
						str_val.Format(L"%.2f",m_st_Netposition.Volume);
						if (CheckvalueInArray(arr7,str_val)==false  && str_val!=L"")
						{
							str[7]=str[7]+str_val+L"\n";										
							arr7.Add(str_val);
						}
					}
					if (clocount==8)
					{						
						str_val.Format(L"%.4f",m_st_Netposition.Price);
						if (CheckvalueInArray(arr8,str_val)==false  && str_val!=L"")
						{
							str[8]=str[8]+str_val+L"\n";										
							arr8.Add(str_val);
						}
					}	
					if (clocount==9)
					{						
						str_val=m_st_Netposition.Comment;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr9,str_val)==false  && str_val!=L"")
						{
							str[9]=str[9]+str_val+L"\n";										
							arr9.Add(str_val);
						}
					}	
					if (clocount==10)
					{						
						str_val=m_st_Netposition.Status;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr10,str_val)==false  && str_val!=L"")
						{
							str[10]=str[10]+str_val+L"\n";										
							arr10.Add(str_val);
						}
					}

					//extended colums
					if (clocount==11)
					{						
						str_val=m_st_Netposition.Opposite_Deal;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr11,str_val)==false  && str_val!=L"")
						{
							str[11]=str[11]+str_val+L"\n";										
							arr11.Add(str_val);
						}
					}
					if (clocount==12)
					{						
						str_val=m_st_Netposition.Deal_Time;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr12,str_val)==false  && str_val!=L"")
						{
							str[12]=str[12]+str_val+L"\n";										
							arr12.Add(str_val);
						}
					}
					if (clocount==13)
					{						
						str_val=m_st_Netposition.Symbol1;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr13,str_val)==false  && str_val!=L"")
						{
							str[13]=str[13]+str_val+L"\n";										
							arr13.Add(str_val);
						}
					}
					if (clocount==14)
					{						
						str_val=m_st_Netposition.Type;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr14,str_val)==false  && str_val!=L"")
						{
							str[14]=str[14]+str_val+L"\n";										
							arr14.Add(str_val);
						}
					}

					
					if (clocount==15)
					{
						double  u_deal=m_st_Netposition.Volume1  ;
						str_val.Format(L"%.2f",u_deal );
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr15,str_val)==false  && str_val!=L"")
						{
							str[15]=str[15]+str_val+L"\n";										
							arr15.Add(str_val);
						}
					}
					
					if (clocount==16)
					{
						double  u_deal=m_st_Netposition.Price1  ;
						str_val.Format(L"%.4f",u_deal );
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr16,str_val)==false  && str_val!=L"")
						{
							str[16]=str[16]+str_val+L"\n";										
							arr16.Add(str_val);
						}
					}
					if (clocount==17)
					{						
						str_val=m_st_Netposition.Status1;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr17,str_val)==false  && str_val!=L"")
						{
							str[17]=str[17]+str_val+L"\n";										
							arr17.Add(str_val);
						}
					}
					
			}												
		}
		
	}
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"addItemToCombobox");			
	} 
}

BOOLEAN  CCodesChanged::CheckvalueInArray(const CStringArray& arr,CString strval) 
{
	try
	{
		int arrcount=arr.GetCount();
		for (int forcount=0;forcount<arrcount;forcount++)
		{
			if (arr[forcount]==strval)
			{
				return true;
			}
                                                                                                                                                                                                                                                                                        		}
		return false  ;
	}
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"CheckvalueInArray");			
	} 
}


UINT Show_CCodesChanged(void *pParam)
{
	CCodesChanged* pThis= (CCodesChanged*)pParam;	
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<CodeChangedTable> > artists1;	
	HRESULT hr;
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=Tradedatabase;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	if(SUCCEEDED(hr))
	{
		hr=session.Open(connection);
		while (true )
		{				
			 CString strCommand=L"";		
			 strCommand.Format(L"code_change");        
			_bstr_t bstrCommand="";
			 bstrCommand=strCommand;
			char* strCommand_char=(char*)bstrCommand;
			 if(SUCCEEDED(hr))
			 {
				hr=artists1.Open(session,strCommand_char);							 
			 }		
			 if(SUCCEEDED(hr))
			 {
				 CCodesChanged::m_st_Dealing_Array.Clear();
				 CCodesChanged::st_Dealing m_st_Dealing={};
				 
				 while (artists1.MoveNext() == S_OK)
				 {																	  
					CMTStr::Copy(m_st_Dealing.Section ,artists1.m_Section );				 					
					CMTStr::Copy(m_st_Dealing.Login ,artists1.m_login );				 										
					m_st_Dealing.Order =artists1.m_Order;
					CMTStr::Copy(m_st_Dealing.Order_In_Time,artists1.m_Order_In_Time ) ;
					m_st_Dealing.Deal=artists1.m_Deal ;
				    CMTStr::Copy(m_st_Dealing.Symbol ,artists1.m_Symbol );		
					CMTStr::Copy(m_st_Dealing.Type1 ,artists1.m_Type1 );		
					m_st_Dealing.Volume =artists1.m_Volume ;
					m_st_Dealing.Price =artists1.m_Price;
					CMTStr::Copy(m_st_Dealing.Comment,artists1.m_Comment);
					CMTStr::Copy(m_st_Dealing.Status,artists1.m_Status);
					CMTStr::Copy(m_st_Dealing.Type,artists1.m_Type2);
					
					CCodesChanged::m_st_Dealing_Array.Add(&m_st_Dealing);
				 }
				 artists1.Close();	


	CCodesChanged::dealing_mutex.Lock();	
	//m_st_Dealing_Grid_array.Assign(m_st_Dealing_Array);

 if (CCodesChanged::insertFilterFlag==1)
 {
	int noof_rowsInStruc=CCodesChanged::m_st_Dealing_Array.Total();	
	if (noof_rowsInStruc>0)
	{
		CCodesChanged::m_st_Dealing_Grid_array.Clear();
	}
	for(int fcount=0;fcount<noof_rowsInStruc;fcount++)
	{
	
		CString	str_Order=L"";
		CCodesChanged::st_Dealing m_st_Netposition={};
		m_st_Netposition=CCodesChanged::m_st_Dealing_Array[fcount];
		
		int flag=0;				
		CString col_row_val[18];
		CString cstr_time=m_st_Netposition.Section ;
		col_row_val[0]=m_st_Netposition.Section;
		if (CCodesChanged::col0_val.Trim().GetLength()>0)
		{
			col_row_val[0]=col_row_val[0].Mid(0,CCodesChanged::col0_val.Trim().GetLength());
		}
		col_row_val[1]=m_st_Netposition.Login   ;
		if (CCodesChanged::col1_val.Trim().GetLength()>0)
		{
			col_row_val[1]=col_row_val[1].Mid(0,CCodesChanged::col1_val.Trim().GetLength());
		}


		CString str_deal=L"";
		str_deal.Format(L"%.0f",m_st_Netposition.Order  );
		col_row_val[2]=str_deal  ;
		if (CCodesChanged::col2_val.Trim().GetLength()>0)
		{
			col_row_val[2]=col_row_val[2].Mid(0,CCodesChanged::col2_val.Trim().GetLength());
		}

		
		
		col_row_val[3]=m_st_Netposition.Order_In_Time;	
		if (CCodesChanged::col3_val.Trim().GetLength()>0)
		{
			col_row_val[3]=col_row_val[3].Mid(0,CCodesChanged::col3_val.Trim().GetLength());
		}



		////////////////////////////////
		str_deal.Format(L"%d",m_st_Netposition.Deal );
		col_row_val[4]=str_deal  ;
		if (CCodesChanged::col4_val.Trim().GetLength()>0)
		{
			col_row_val[4]=col_row_val[4].Mid(0,CCodesChanged::col4_val.Trim().GetLength());
		}

		
		col_row_val[5]=m_st_Netposition.Symbol;  ;		
		if (CCodesChanged::col5_val.Trim().GetLength()>0)
		{
			col_row_val[5]=col_row_val[5].Mid(0,CCodesChanged::col5_val.Trim().GetLength());
		}
		
		
		col_row_val[6]=m_st_Netposition.Type1 ; ;
		if (CCodesChanged::col6_val.Trim().GetLength()>0)
		{
			col_row_val[6]=col_row_val[6].Mid(0,CCodesChanged::col6_val.Trim().GetLength());
		}

		
		str_Order.Format(L"%.2f",m_st_Netposition.Volume );
		col_row_val[7]=str_Order  ;
		if (CCodesChanged::col7_val.Trim().GetLength()>0)
		{
			col_row_val[7]=col_row_val[7].Mid(0,CCodesChanged::col7_val.Trim().GetLength());
		}

		str_Order.Format(L"%.4f",m_st_Netposition.Price );
		col_row_val[8]=str_Order;
		if (CCodesChanged::col8_val.Trim().GetLength()>0)
		{
			col_row_val[8]=col_row_val[8].Mid(0,CCodesChanged::col8_val.Trim().GetLength());
		}			

		str_Order=m_st_Netposition.Comment ;
		col_row_val[9]=str_Order ;
		if (CCodesChanged::col9_val.Trim().GetLength()>0)
		{
			col_row_val[9]=col_row_val[9].Mid(0,CCodesChanged::col9_val.Trim().GetLength());
		}

		str_Order=m_st_Netposition.Status ;
		col_row_val[10]=str_Order ;
		if (CCodesChanged::col10_val.Trim().GetLength()>0)
		{
			col_row_val[10]=col_row_val[10].Mid(0,CCodesChanged::col10_val.Trim().GetLength());
		}

		//extended cloums
		str_Order=m_st_Netposition.Opposite_Deal ;
		col_row_val[11]=str_Order ;
		if (CCodesChanged::col11_val.Trim().GetLength()>0)
		{
			col_row_val[11]=col_row_val[11].Mid(0,CCodesChanged::col11_val.Trim().GetLength());
		}
		str_Order=m_st_Netposition.Deal_Time ;
		col_row_val[12]=str_Order ;
		if (CCodesChanged::col12_val.Trim().GetLength()>0)
		{
			col_row_val[12]=col_row_val[12].Mid(0,CCodesChanged::col12_val.Trim().GetLength());
		}
		str_Order=m_st_Netposition.Symbol1 ;
		col_row_val[13]=str_Order ;
		if (CCodesChanged::col13_val.Trim().GetLength()>0)
		{
			col_row_val[13]=col_row_val[13].Mid(0,CCodesChanged::col13_val.Trim().GetLength());
		}

		str_Order=m_st_Netposition.Type;
		col_row_val[14]=str_Order ;
		if (CCodesChanged::col14_val.Trim().GetLength()>0)
		{
			col_row_val[14]=col_row_val[14].Mid(0,CCodesChanged::col14_val.Trim().GetLength());
		}

		str_Order.Format(L"%.2f",m_st_Netposition.Volume1 );
		col_row_val[15]=str_Order;
		if (CCodesChanged::col15_val.Trim().GetLength()>0)
		{
			col_row_val[15]=col_row_val[15].Mid(0,CCodesChanged::col15_val.Trim().GetLength());
		}	

		str_Order.Format(L"%.4f",m_st_Netposition.Price1 );
		col_row_val[16]=str_Order;
		if (CCodesChanged::col16_val.Trim().GetLength()>0)
		{
			col_row_val[16]=col_row_val[16].Mid(0,CCodesChanged::col16_val.Trim().GetLength());
		}	

		str_Order=m_st_Netposition.Status1;
		col_row_val[17]=str_Order;
		if (CCodesChanged::col17_val.Trim().GetLength()>0)
		{
		 	col_row_val[17]=col_row_val[17].Mid(0,CCodesChanged::col17_val.Trim().GetLength());
		}


		if((CCodesChanged::col0_val.Trim()==col_row_val[0].Trim() || CCodesChanged::col0_val.Trim()==L"ALL"||CCodesChanged::col0_val.Trim()==L"") && (CCodesChanged::col1_val.Trim()==col_row_val[1].Trim() || CCodesChanged::col1_val.Trim()==L"ALL"||CCodesChanged::col1_val.Trim()==L"") && (CCodesChanged::col2_val.Trim()==col_row_val[2].Trim() ||CCodesChanged::col2_val.Trim()==L"ALL"||CCodesChanged::col2_val.Trim()==L"")  && (CCodesChanged::col3_val.Trim()==col_row_val[3].Trim() ||CCodesChanged::col3_val.Trim()==L"ALL"||CCodesChanged::col3_val.Trim().Trim()==L"")  && (CCodesChanged::col4_val.Trim()==col_row_val[4].Trim() ||CCodesChanged::col4_val.Trim()==L"ALL"||CCodesChanged::col4_val.Trim()==L"")   && (CCodesChanged::col5_val.Trim()==col_row_val[5].Trim() || CCodesChanged::col5_val.Trim()==L"ALL"||CCodesChanged::col5_val.Trim()==L"")   && (CCodesChanged::col6_val.Trim()==col_row_val[6].Trim() || CCodesChanged::col6_val.Trim()==L"ALL"||CCodesChanged::col6_val.Trim()==L"")   && (CCodesChanged::col7_val.Trim()==col_row_val[7].Trim() || CCodesChanged::col7_val.Trim()==L"ALL"||CCodesChanged::col7_val.Trim()==L"")  && (CCodesChanged::col8_val.Trim()==col_row_val[8].Trim() || CCodesChanged::col8_val.Trim()==L"ALL"||CCodesChanged::col8_val.Trim()==L"")&&(CCodesChanged::col9_val.Trim()==col_row_val[9].Trim() || CCodesChanged::col9_val.Trim()==L"ALL"||CCodesChanged::col9_val.Trim()==L"") && (CCodesChanged::col10_val.Trim()==col_row_val[10].Trim() || CCodesChanged::col10_val.Trim()==L"ALL"||CCodesChanged::col10_val.Trim()==L"")&&(CCodesChanged::col11_val.Trim()==col_row_val[11].Trim() || CCodesChanged::col11_val.Trim()==L"ALL"||CCodesChanged::col11_val.Trim()==L"") && (CCodesChanged::col12_val.Trim()==col_row_val[12].Trim() || CCodesChanged::col12_val.Trim()==L"ALL"||CCodesChanged::col12_val.Trim().Trim()==L"")&& (CCodesChanged::col13_val.Trim()==col_row_val[13].Trim() || CCodesChanged::col13_val.Trim()==L"ALL"||CCodesChanged::col13_val.Trim()==L"")&& (CCodesChanged::col14_val.Trim()==col_row_val[14].Trim() || CCodesChanged::col14_val.Trim()==L"ALL"||CCodesChanged::col14_val.Trim()==L"")&& (CCodesChanged::col15_val.Trim()==col_row_val[15].Trim() || CCodesChanged::col15_val.Trim()==L"ALL"||CCodesChanged::col15_val.Trim()==L"")&& (CCodesChanged::col16_val.Trim()==col_row_val[16].Trim() ||CCodesChanged::col16_val.Trim()==L"ALL"||CCodesChanged::col16_val.Trim()==L"")&& (CCodesChanged::col17_val.Trim()==col_row_val[17].Trim() || CCodesChanged::col17_val.Trim()==L"ALL"||CCodesChanged::col17_val.Trim()==L""))
		{						
			CCodesChanged::m_st_Dealing_Grid_array.Add(&m_st_Netposition);						
		}
	 }
 }
 else
 {
	CCodesChanged::m_st_Dealing_Grid_array.Assign(CCodesChanged::m_st_Dealing_Array);	

 }




	//Shorting Column
	int t_rows=CCodesChanged::m_st_Dealing_Grid_array.Total();
	CCodesChanged::st_Dealing first_st={};
	CCodesChanged::st_Dealing swap_st={};
	CCodesChanged::st_Dealing next_st={};
	

	int val_type=0;
	if (CCodesChanged::col_click==0||CCodesChanged::col_click==1)
	{
		val_type=0;
	}
	else
	{
		val_type=1;
	}
	for (int i=0;i<t_rows;i++)
	{
		first_st=CCodesChanged::m_st_Dealing_Grid_array[i];
		for (int j=i+1;j<t_rows;j++)
		{
			next_st=CCodesChanged::m_st_Dealing_Grid_array[j];
			if (CCodesChanged::a_d==0)
			{
				if (val_type==0)
				{
					if (CCodesChanged::col_click==0)
					{
						if (wcscmp(first_st.Section ,next_st.Section )>0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Section ,swap_st.Section );							
						}
					}
					if (CCodesChanged::col_click==1)
					{
						if (wcscmp(first_st.Login  ,next_st.Login  )>0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Login  ,swap_st.Login );							
						}
					}
				}
				else
				{
					if (CCodesChanged::col_click==2)
					{															
						double d_val1=first_st.Order ;															
						double d_val2=next_st.Order;						
						if (d_val1>d_val2)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							first_st.Order =swap_st.Order ;							
						}
					}
					//Order_In_Time
					if (CCodesChanged::col_click==3)
					{															
						if (wcscmp(first_st.Order_In_Time  ,next_st.Order_In_Time  )>0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Order_In_Time  ,swap_st.Order_In_Time );							
						}
					}
					if (CCodesChanged::col_click==4)
					{															
						int d_val1=first_st.Deal ;															
						int d_val2=next_st.Deal;						
						if (d_val1>d_val2)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							first_st.Deal =swap_st.Deal ;							
						}
					}
					if (CCodesChanged::col_click==5)
					{															
						if (wcscmp(first_st.Symbol  ,next_st.Symbol  )>0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Symbol  ,swap_st.Symbol );							
						}
					}
					if (CCodesChanged::col_click==6)
					{															
						if (wcscmp(first_st.Type1  ,next_st.Type1  )>0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Type1  ,swap_st.Type1 );							
						}
					}
					if (CCodesChanged::col_click==7)
					{															
						double d_val1=first_st.Volume  ;															
						double d_val2=next_st.Volume;
						if (d_val1>d_val2)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							first_st.Volume =swap_st.Volume;							
						}
					}
					if (CCodesChanged::col_click==8)
					{															
						double d_val1=first_st.Price;															
						double d_val2=next_st.Price;
						if (d_val1>d_val2)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							first_st.Price =swap_st.Price;					
						}
					}
					if (CCodesChanged::col_click==9)
					{								
						if (wcscmp(first_st.Comment,next_st.Comment  )>0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Comment  ,swap_st.Comment );							
						}
					}
					if (CCodesChanged::col_click==10)
					{															
						if (wcscmp(first_st.Status  ,next_st.Status  )>0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Status  ,swap_st.Status );							
						}
					}
					if (CCodesChanged::col_click==11)
					{															
						if (wcscmp(first_st.Opposite_Deal  ,next_st.Opposite_Deal  )>0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Opposite_Deal  ,swap_st.Opposite_Deal );							
						}
					}
					if (CCodesChanged::col_click==12)
					{															
						if (wcscmp(first_st.Deal_Time  ,next_st.Deal_Time  )>0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Deal_Time  ,swap_st.Deal_Time );							
						}
					}

					//extended colums
					if (CCodesChanged::col_click==13)
					{															
						if (wcscmp(first_st.Symbol1  ,next_st.Symbol1  )>0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Symbol1  ,swap_st.Symbol1 );							
						}
					}
					if (CCodesChanged::col_click==14)
					{															
						if (wcscmp(first_st.Type  ,next_st.Type  )>0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Type  ,swap_st.Type );							
						}
					}
					if (CCodesChanged::col_click==15)
					{															
						double d_val1=first_st.Volume1;															
						double d_val2=next_st.Volume1;
						if (d_val1>d_val2)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							first_st.Volume1 =swap_st.Volume1;					
						}
					}
					if (CCodesChanged::col_click==16)
					{															
						double d_val1=first_st.Price1 ;															
						double d_val2=next_st.Price1;
						if (d_val1>d_val2)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							first_st.Price1 =swap_st.Price1;					
						}
					}
					if (CCodesChanged::col_click==17)
					{															
						if (wcscmp(first_st.Status1  ,next_st.Status1  )>0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Status1  ,swap_st.Status1 );							
						}
					}

				}
			}
			else
			{
if (val_type==0)
				{
					if (CCodesChanged::col_click==0)
					{
						if (wcscmp(first_st.Section ,next_st.Section )<0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Section ,swap_st.Section );							
						}
					}
					if (CCodesChanged::col_click==1)
					{
						if (wcscmp(first_st.Login  ,next_st.Login  )<0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Login  ,swap_st.Login );							
						}
					}
				}
				else
				{
					if (CCodesChanged::col_click==2)
					{															
						double d_val1=first_st.Order ;															
						double d_val2=next_st.Order;						
						if (d_val1<d_val2)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							first_st.Order =swap_st.Order ;							
						}
					}

					if (CCodesChanged::col_click==3)
					{															
						if (wcscmp(first_st.Order_In_Time  ,next_st.Order_In_Time  )<0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Order_In_Time  ,swap_st.Order_In_Time );							
						}
					}
					if (CCodesChanged::col_click==4)
					{															
						int d_val1=first_st.Deal ;															
						int d_val2=next_st.Deal;						
						if (d_val1<d_val2)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							first_st.Deal =swap_st.Deal ;							
						}
					}
					if (CCodesChanged::col_click==5)
					{															
						if (wcscmp(first_st.Symbol  ,next_st.Symbol  )<0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Symbol  ,swap_st.Symbol );							
						}
					}
					if (CCodesChanged::col_click==6)
					{															
						if (wcscmp(first_st.Type1  ,next_st.Type1  )<0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Type1  ,swap_st.Type1 );							
						}
					}
					if (CCodesChanged::col_click==7)
					{															
						double d_val1=first_st.Volume  ;															
						double d_val2=next_st.Volume;
						if (d_val1<d_val2)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							first_st.Volume =swap_st.Volume;							
						}
					}
					if (CCodesChanged::col_click==8)
					{															
						double d_val1=first_st.Price   ;															
						double d_val2=next_st.Price;
						if (d_val1<d_val2)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							first_st.Price =swap_st.Price;					
						}
					}
					if (CCodesChanged::col_click==9)
					{															
						if (wcscmp(first_st.Comment  ,next_st.Comment  )<0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Comment  ,swap_st.Comment );							
						}
					}
					if (CCodesChanged::col_click==10)
					{															
						if (wcscmp(first_st.Comment  ,next_st.Comment  )<0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Comment  ,swap_st.Comment );							
						}
					}
					if (CCodesChanged::col_click==11)
					{															
						if (wcscmp(first_st.Opposite_Deal  ,next_st.Opposite_Deal  )<0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Opposite_Deal  ,swap_st.Opposite_Deal );							
						}
					}
					if (CCodesChanged::col_click==12)
					{															
						if (wcscmp(first_st.Deal_Time  ,next_st.Deal_Time  )<0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Deal_Time  ,swap_st.Deal_Time );							
						}
					}

					//extended colums
					if (CCodesChanged::col_click==13)
					{															
						if (wcscmp(first_st.Symbol1  ,next_st.Symbol1  )<0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Symbol1  ,swap_st.Symbol1 );							
						}
					}
					if (CCodesChanged::col_click==14)
					{															
						if (wcscmp(first_st.Type  ,next_st.Type  )<0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Type  ,swap_st.Type );							
						}
					}
					if (CCodesChanged::col_click==15)
					{															
						double d_val1=first_st.Volume1;															
						double d_val2=next_st.Volume1;
						if (d_val1<d_val2)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							first_st.Volume1 =swap_st.Volume1;					
						}
					}
					if (CCodesChanged::col_click==16)
					{															
						double d_val1=first_st.Price1 ;															
						double d_val2=next_st.Price1;
						if (d_val1<d_val2)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							first_st.Price1 =swap_st.Price1;					
						}
					}
					if (CCodesChanged::col_click==17)
					{															
						if (wcscmp(first_st.Status1  ,next_st.Status1  )<0)
						{
							CCodesChanged::m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=CCodesChanged::m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Status1  ,swap_st.Status1 );							
						}
					}
	
				}
					
			}
		}
	 }
	//End of Shorting Col
	 CCodesChanged::dealing_mutex.Unlock();	

	      }
		  Sleep(1000);
      }
	}
    return 0;
}


void CCodesChanged::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{		
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);

	col_click=col;
	if( updn == 0)
		return;
	if (col_click!=col)
	{
		a_d=0;
	}
	else
	{
		if (a_d==0)
		{
			a_d=1;
		}
		else
		{
			a_d=0;
		}
	}


	QuickSetCellType( m_iSortCol, -1, 0 );

	if( col == m_iSortCol )
	{
		if( m_bSortedAscending )
			m_bSortedAscending = FALSE;
		else
			m_bSortedAscending = TRUE;
	}
	else
	{
		m_iSortCol = col;
		m_bSortedAscending = TRUE;
	}

	if( m_bSortedAscending )
	{
		SortBy( col, UG_SORT_ASCENDING );
		QuickSetCellType( m_iSortCol, -1, m_iArrowIndex );
		QuickSetCellTypeEx( m_iSortCol, -1, UGCT_SORTARROWDOWN );

//		((CFindAndSortDemo*)GetParent())->Trace( _T( "Sorted column %d ascending" ), iCol );
	}
	else
	{
		SortBy( col, UG_SORT_DESCENDING );
		QuickSetCellType( m_iSortCol, -1, m_iArrowIndex );
		QuickSetCellTypeEx( m_iSortCol, -1, UGCT_SORTARROWUP );
//		Trace( _T( "Sorted column %d descending" ), iCol );
	}			 				
	RedrawAll();
}
