#include "stdafx.h"
#include "resource.h"
#include "Dealing.h"
#include <afxdisp.h>
#include <time.h>
#include <locale.h>
#include "MainFrm.h"
#include "document.h"
#include <iostream>
#include "CNetPosTable.h"
#include "Login.h"
#include "clr_setting.h"
using namespace std;
using namespace rapidjson;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//CUIThread
BEGIN_MESSAGE_MAP(Dealing,CUGCtrl)	
	ON_WM_SIZE()
	ON_WM_TIMER()		
END_MESSAGE_MAP()

int Dealing::insertFilterFlag=0;
Dealing::st_Dealing_Array Dealing::m_st_Dealing_Array;	
Dealing::st_Dealing_Array Dealing::m_st_Dealing_Grid_array;
CMutex Dealing::dealing_mutex;
/////////////////////////////////////////////////////////////////////////////
//Standard MyCug construction/destruction
boolean  Check_numeric_col_filter_1(CString  filter_value,CString  real_value);
Dealing::Dealing()
{
	UGXPThemes::UseThemes(false);	
}

Dealing::~Dealing()
{
	//delete m_pThread;
	UGXPThemes::CleanUp();
}

void Dealing::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();
	
	EnableMenu(TRUE);
	
	menu->AppendMenuW(MF_STRING|MF_UNCHECKED,2001,_T("Filter"));
	
	
	submenu.CreatePopupMenu();
}
void Dealing::OnSetup()
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
		SetNumberCols( 13 );		
		m_iArrowIndex = AddCellType( &m_sortArrow );
		SetCurrentCellMode( 2 );
		UseHints( TRUE );
		SetSH_Width( 0 );	
		QuickSetCellType( 0, -1, m_iArrowIndex );
		SortBy( 0, UG_SORT_ASCENDING );
		m_iSortCol = 0;
		m_bSortedAscending = TRUE;		
		InitMenu();
		SetTimer(0, 1000, NULL);
	}
	 catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"   writeData");			
	} 
}
void Dealing::OnSheetSetup(int sheetNumber)
{
	int	nRow = 0, nCol = 0;	
	CUGCell cell;	
	SetGridDefault(&cell);
	EnableExcelBorders(TRUE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetDefFont(0);
	SetSH_Width(0);		
			
	SetNumberCols(13);
	QuickSetText(0,-1,L"LOG TIME");
	SetColWidth(0,130);

	QuickSetText(1,-1,L"TIME");
	SetColWidth(1,130);

	QuickSetText(2,-1,L"LOGIN");
	SetColWidth(2,90);

	QuickSetText(3,-1,L"DEAL");	
	SetColWidth(3,75);
			
	QuickSetText(4,-1,L"ORDER");
	SetColWidth(4,75);

	QuickSetText(5,-1,L"ORDER TYPE");
	SetColWidth(5,75);

	QuickSetText(6,-1,L"SYMBOL");
	SetColWidth(6,75);

	QuickSetText(7,-1,L"TYPE");	
	SetColWidth(7,70);
			
	QuickSetText(8,-1,L"VOLUME");
	SetColWidth(8,70);
			
	QuickSetText(9,-1,L"PRICE");
	SetColWidth(9,75);

	QuickSetText(10,-1,L"COMMENT");
	SetColWidth(10,100);

	QuickSetText(11,-1,L"ENTRYTYPE");
	SetColWidth(11,140);

	QuickSetText(12,-1,L"CURRENT STATUS");
	SetColWidth(12,140);
									
	// Header font
	for(int i = 0; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}	
}

void Dealing::OnTimer(UINT nIDEvent)
{		
	Dealing::dealing_mutex.Lock();	
	
	m_st_Dealing_Grid_array.Clear();
	if (Dealing::insertFilterFlag==1)
	{
	int noof_rowsInStruc=m_st_Dealing_Array.Total();	
	CString getColvalue=L"";
	CString col_filter_val[13];	
	for(int c=0;c<13;c++)
	{
		col_filter_val[c]=QuickGetText(c,0);
	}
	for(int fcount=noof_rowsInStruc-1;fcount>=0;fcount--)
	{
		st_Dealing m_st_Netposition={};
		m_st_Netposition=m_st_Dealing_Array[fcount];
		
		int flag=0;		
		
		CString col_row_val[13];

		//CString cstr_log_time=L"";
		//CTime t = CTime::GetCurrentTime();
		//cstr_log_time = t.Format("%Y.%m.%d %H:%M:%S %ms");	



		
		col_row_val[0]=m_st_Netposition.LOG_TIME;
		if (col_filter_val[0].Trim().GetLength()>0)
		{
			col_row_val[0]=col_row_val[0].Mid(0,col_filter_val[0].Trim().GetLength());
		}




		CString cstr_time=L"";
		cstr_time.Format(L"%d",m_st_Netposition.Time);
		col_row_val[1]=cstr_time;
		if (col_filter_val[1].Trim().GetLength()>0)
		{
			col_row_val[1]=col_row_val[1].Mid(0,col_filter_val[1].Trim().GetLength());
		}
		col_row_val[2]=m_st_Netposition.Login   ;
		if (col_filter_val[2].Trim().GetLength()>0)
		{
			col_row_val[2]=col_row_val[2].Mid(0,col_filter_val[2].Trim().GetLength());
		}
		CString str_deal=L"";
		str_deal.Format(L"%d",m_st_Netposition.Deal);
		col_row_val[3]=str_deal  ;
		if (col_filter_val[3].Trim().GetLength()>0)
		{
			col_row_val[3]=col_row_val[3].Mid(0,col_filter_val[3].Trim().GetLength());
		}

		CString str_Order=L"";
		str_Order.Format(L"%d",m_st_Netposition.Deal);
		col_row_val[4]=str_Order  ;		
		if (col_filter_val[4].Trim().GetLength()>0)
		{
			col_row_val[4]=col_row_val[4].Mid(0,col_filter_val[4].Trim().GetLength());
		}
		

		col_row_val[5]=m_st_Netposition.Order_type ;
		if (col_filter_val[5].Trim().GetLength()>0)
		{
			col_row_val[5]=col_row_val[5].Mid(0,col_filter_val[5].Trim().GetLength());
		}

		col_row_val[6]=m_st_Netposition.Symbol  ;
		if (col_filter_val[6].Trim().GetLength()>0)
		{
			col_row_val[6]=col_row_val[6].Mid(0,col_filter_val[6].Trim().GetLength());
		}

		col_row_val[7]=m_st_Netposition.Type  ;
		if (col_filter_val[7].Trim().GetLength()>0)
		{
			col_row_val[7]=col_row_val[7].Mid(0,col_filter_val[7].Trim().GetLength());
		}

		CString str_volume=L"";
		str_volume.Format(L"%.0f",m_st_Netposition.Volume);
		col_row_val[8]=str_volume  ;
		boolean bool_col7=Check_numeric_col_filter_1(col_filter_val[8],col_row_val[8]);

		CString str_price=L"";
		str_price.Format(L"%.4f",m_st_Netposition.Price);
		col_row_val[9]=str_price  ;
		boolean bool_col8=Check_numeric_col_filter_1(col_filter_val[9],col_row_val[9]);

		col_row_val[10]=m_st_Netposition.Comment  ;
		if (col_filter_val[10].Trim().GetLength()>0)
		{
			col_row_val[10]=col_row_val[10].Mid(0,col_filter_val[10].Trim().GetLength());
		}

		col_row_val[11]=m_st_Netposition.Entrytype  ;
		if (col_filter_val[11].Trim().GetLength()>0)
		{
			col_row_val[11]=col_row_val[11].Mid(0,col_filter_val[11].Trim().GetLength());
		}
		col_row_val[12]=m_st_Netposition.Current_Status  ;
		if (col_filter_val[12].Trim().GetLength()>0)
		{
			col_row_val[12]=col_row_val[12].Mid(0,col_filter_val[12].Trim().GetLength());
		}
				
		if((col_filter_val[0].Trim()==col_row_val[0].Trim() || col_filter_val[0].Trim()==L"ALL"||col_filter_val[0].Trim()==L"") && (col_filter_val[1].Trim()==col_row_val[1].Trim() || col_filter_val[1].Trim()==L"ALL"||col_filter_val[1].Trim()==L"") && (col_filter_val[2].Trim()==col_row_val[2].Trim() || col_filter_val[2].Trim()==L"ALL"||col_filter_val[2].Trim()==L"") && (col_filter_val[3].Trim()==col_row_val[3].Trim() || col_filter_val[3].Trim()==L"ALL"||col_filter_val[3].Trim()==L"")  && (col_filter_val[4].Trim()==col_row_val[4].Trim() || col_filter_val[4].Trim()==L"ALL"||col_filter_val[4].Trim()==L"")  && (col_filter_val[5].Trim()==col_row_val[5].Trim() || col_filter_val[5].Trim()==L"ALL"||col_filter_val[5].Trim()==L"")   && (col_filter_val[6].Trim()==col_row_val[6].Trim() || col_filter_val[6].Trim()==L"ALL"||col_filter_val[6].Trim()==L"")   && (col_filter_val[7].Trim()==col_row_val[7].Trim() || col_filter_val[7].Trim()==L"ALL"||col_filter_val[7].Trim()==L"")   && (bool_col7==true || col_filter_val[8].Trim()==L"ALL"||col_filter_val[8].Trim()==L"")   && (bool_col8==true || col_filter_val[9].Trim()==L"ALL"||col_filter_val[9].Trim()==L"") && (col_filter_val[10].Trim()==col_row_val[10].Trim() || col_filter_val[10].Trim()==L"ALL"||col_filter_val[10].Trim()==L"") &&(col_filter_val[11]==col_row_val[11] || col_filter_val[11]==L"ALL"||col_filter_val[11]==L"")&&(col_filter_val[12]==col_row_val[12] || col_filter_val[12]==L"ALL"||col_filter_val[12]==L""))
		{						
			m_st_Dealing_Grid_array.Add(&m_st_Netposition);						
		}
		
	 }
	}
	else
	{
		//m_st_Dealing_Grid_array.Assign( m_st_Dealing_Array);

		int noof_rowsInStruc=m_st_Dealing_Array.Total();	
	
		for(int fcount=noof_rowsInStruc-1;fcount>=0;fcount--)
		{
			st_Dealing m_st_Netposition={};
			m_st_Netposition=m_st_Dealing_Array[fcount];
			m_st_Dealing_Grid_array.Add(&m_st_Netposition);
		}


	}
	int r_count=m_st_Dealing_Grid_array.Total();
	Dealing::dealing_mutex.Unlock();		
	int grid_total=GetNumberRows();
	
	if (Dealing::insertFilterFlag==1)
	{
			r_count=r_count+1;
	}		
	if (grid_total!=r_count)
	{			
		SetNumberRows(r_count);					
	}
	else
	{			
			RedrawAll();			
	}					
}		


void Dealing::OnGetCell(int col,long row,CUGCell *cell)
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
			if (Dealing::insertFilterFlag==1)
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

				
				CString tmp=L"";				
				tmp=mst_grid.LOG_TIME;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			if (col==1)
			{				
				mst_grid=m_st_Dealing_Grid_array[rows_no];

				

				UINT64 m_time=mst_grid.Time;
				CString tmp=L"";
				CMTStr256 str;
				SMTFormat::FormatDateTime(str,m_time,true,true);
				tmp=str.Str();
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==2)
			{
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Login;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==3)
			{	
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				UINT64 m_deal=mst_grid.Deal;

				CString tmp=L"" ;
				tmp.Format(L"%d",m_deal);
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==4)
			{				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				UINT64 m_order=mst_grid.Order;
				CString tmp=L"" ;
				tmp.Format(L"%d",m_order);
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==5)
			{	
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=L"" ;
				tmp=mst_grid.Order_type;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==6)
			{				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Symbol;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==7)
			{	
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Type;												
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==8)
			{				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				double m_volume=mst_grid.Volume;
				CString tmp=L""   ;
				tmp.Format(L"%.2f",m_volume);
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==9)
			{
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				double m_price=mst_grid.Price;
				CString tmp=L"";
				tmp.Format(L"%.4f",m_price);
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==10)
			{
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Comment    ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==11)
			{
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Entrytype;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==12)
			{
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Current_Status;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			
		}					
}
void Dealing::OnMenuCommand(int col,long row,int section,int item)
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
void Dealing::filter()
{
	try
	{
	 CMenu *pMnenu;
	pMnenu= GetPopupMenu();

	if ( Dealing::insertFilterFlag==0)
	{
			addItemToCombobox();
			Dealing::insertFilterFlag=1;
			InsertRow(0);
			for (int col_count=0;col_count<13;col_count++)
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
			}
			pMnenu->CheckMenuItem(2001,MF_CHECKED);

	}
	else
	{
		
		DeleteRow(0);
		Dealing::insertFilterFlag=0;
		
		pMnenu->CheckMenuItem(2001,MF_UNCHECKED);
	}
	RedrawAll();
	}
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"   filter");			
	} 
 }



void Dealing::addItemToCombobox()
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
	try
	{
		int rows=1;
		rows=m_st_Dealing_Array.Total();	
		CString str_val=L"";	
		for (int forcount=0;forcount<13;forcount++)
		{
			str[forcount]=L"ALL\n";		
		}
		for (int forcount=0;forcount<rows;forcount++)
		{
			 st_Dealing m_st_Netposition={};
			m_st_Netposition=m_st_Dealing_Array[forcount];
			for (int clocount=0;clocount<13;clocount++)
			{		

				if (clocount==0)
					{						
						str_val=m_st_Netposition.LOG_TIME;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr,str_val)==false && str_val!=L"")
						{
							str[0]=str[0]+str_val+L"\n";										
							arr.Add(str_val);							
						}
					}

					if (clocount==1)
					{
						UINT64 u_time=m_st_Netposition.Time;
						str_val.Format(L"%d",u_time);
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr1,str_val)==false && str_val!=L"")
						{
							str[1]=str[1]+str_val+L"\n";										
							arr1.Add(str_val);							
						}
					}
					if (clocount==2)
					{
						str_val=m_st_Netposition.Login;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr2,str_val)==false  && str_val!=L"")
						{
							str[2]=str[2]+str_val+L"\n";										
							arr2.Add(str_val);
						}
					}
					if (clocount==3)
					{
						UINT64 u_deal=m_st_Netposition.Deal;
						str_val.Format(L"%d",m_st_Netposition.Deal);
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr3,str_val)==false  && str_val!=L"")
						{
							str[3]=str[3]+str_val+L"\n";										
							arr3.Add(str_val);
						}
					}
					if (clocount==4)
					{
						UINT64 u_order=m_st_Netposition.Order;
						str_val.Format(L"%d",m_st_Netposition.Order) ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr4,str_val)==false  && str_val!=L"")
						{
							str[4]=str[4]+str_val+L"\n";										
							arr4.Add(str_val);
						}
					}

					if (clocount==5)
					{
						str_val=m_st_Netposition.Order_type ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr5,str_val)==false  && str_val!=L"")
						{
							str[5]=str[5]+str_val+L"\n";										
							arr5.Add(str_val);
						}
					}
					if (clocount==6)
					{
						str_val=m_st_Netposition.Symbol ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr6,str_val)==false  && str_val!=L"")
						{
							str[6]=str[6]+str_val+L"\n";										
							arr6.Add(str_val);
						}
					}
					if (clocount==7)
					{
						str_val=m_st_Netposition.Type ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr7,str_val)==false  && str_val!=L"")
						{
							str[7]=str[7]+str_val+L"\n";										
							arr7.Add(str_val);
						}
					}
					if (clocount==8)
					{
						double d_volume=m_st_Netposition.Volume;
						str_val.Format(L"%.2f",d_volume);
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr8,str_val)==false  && str_val!=L"")
						{
							str[8]=str[8]+str_val+L"\n";										
							arr8.Add(str_val);
						}
					}
					if (clocount==9)
					{
						double d_price=m_st_Netposition.Price;
						str_val.Format(L"%.4f",d_price);
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr9,str_val)==false  && str_val!=L"")
						{
							str[9]=str[9]+str_val+L"\n";										
							arr9.Add(str_val);
						}
					}
					if (clocount==10)
					{
						str_val=m_st_Netposition.Comment  ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr10,str_val)==false  && str_val!=L"")
						{
							str[10]=str[10]+str_val+L"\n";										
							arr10.Add(str_val);
						}
					}
					if (clocount==11)
					{
						str_val=m_st_Netposition.Entrytype ;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr11,str_val)==false  && str_val!=L"")
						{
							str[11]=str[11]+str_val+L"\n";										
							arr11.Add(str_val);
						}
					}
					if (clocount==12)
					{
						str_val=m_st_Netposition.Current_Status;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr12,str_val)==false  && str_val!=L"")
						{
							str[12]=str[12]+str_val+L"\n";										
							arr12.Add(str_val);
						}
					}					
			}												
		}
		for(int f=0;f<13;f++)
		{
			colShorting(f);
		}		
	}
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"addItemToCombobox");			
	} 
}

BOOLEAN  Dealing::CheckvalueInArray(const CStringArray& arr,CString strval) 
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

void Dealing::colShorting( int index)
{
	
}



boolean  Check_numeric_col_filter_1(CString  filter_value,CString  real_value)
{
		boolean bool_col=false;		
		double temp_double=0;
		LPTSTR endPtr;
		temp_double= _tcstod(real_value, &endPtr);	
		filter_value=filter_value.Trim();
		if (filter_value.GetLength()>2)
		{
			if (filter_value.Mid(0,2)==L">=")
			{
				CString o_real_val=filter_value.Mid(2,filter_value.GetLength()-2);
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(o_real_val, &endPtr1);	
				if (temp_double>=db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}
			if (filter_value.Mid(0,2)==L"<=")
			{
				CString o_real_val=filter_value.Mid(2,filter_value.GetLength()-2);
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(o_real_val, &endPtr1);	
				if (temp_double<=db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}

			if (filter_value.Mid(0,1)==L"<")
			{
				CString o_real_val=filter_value.Mid(1,filter_value.GetLength()-1);
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(o_real_val, &endPtr1);	
				if (temp_double<db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}
			if (filter_value.Mid(0,1)==L">")
			{
				CString o_real_val=filter_value.Mid(1,filter_value.GetLength()-1);
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(o_real_val, &endPtr1);	
				if (temp_double>db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}	

			
			if (filter_value.Mid(0,1)!=L">" &&  filter_value.Mid(0,1)!=L"<")
			{
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(filter_value, &endPtr1);	
				if (temp_double==db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}

		}
		else
		{

			if (filter_value.Mid(0,1)==L"<")
			{
				CString o_real_val=filter_value.Mid(1,filter_value.GetLength()-1);
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(o_real_val, &endPtr1);	
				if (temp_double<db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}
			if (filter_value.Mid(0,1)==L">")
			{
				CString o_real_val=filter_value.Mid(1,filter_value.GetLength()-1);
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(o_real_val, &endPtr1);	
				if (temp_double>db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}	

			if (filter_value.Mid(0,1)!=L">" &&  filter_value.Mid(0,1)!=L"<")
			{
				double db_filter_val=0;
				LPTSTR endPtr1;				
				db_filter_val= _tcstod(filter_value, &endPtr1);	
				if (temp_double==db_filter_val)
				{
					bool_col=true;
					return bool_col;
				}
			}
		}
		return bool_col;
}


void Dealing::gridFilter(int colno,int rows_count,CString col_value)
{
	try
	{
	CString getColvalue=L"";
	CString col_filter_val[13];	
	for(int c=0;c<13;c++)
	{
		col_filter_val[c]=QuickGetText(c,0);
	}
	int noof_filterdata_count=0;	
	int noof_rowsInStruc=m_st_Dealing_Array.Total();	
	for(int fcount=0;fcount<noof_rowsInStruc;fcount++)
	{
		st_Dealing m_st_Netposition={};
		m_st_Netposition=m_st_Dealing_Array[fcount];		
		int flag=0;				
		CString col_row_val[13];
		CString cstr_time=L"";
		cstr_time.Format(L"%d",m_st_Netposition.Time);
		col_row_val[1]=cstr_time ;
		if (col_filter_val[1].Trim().GetLength()>0)
		{
			col_row_val[1]=col_row_val[1].Mid(0,col_filter_val[1].Trim().GetLength());
		}
		col_row_val[2]=m_st_Netposition.Login   ;
		if (col_filter_val[2].Trim().GetLength()>0)
		{
			col_row_val[2]=col_row_val[2].Mid(0,col_filter_val[2].Trim().GetLength());
		}
		CString str_deal=L"";
		str_deal.Format(L"%d",m_st_Netposition.Deal);
		col_row_val[3]=str_deal  ;
		if (col_filter_val[3].Trim().GetLength()>0)
		{
			col_row_val[3]=col_row_val[3].Mid(0,col_filter_val[3].Trim().GetLength());
		}

		CString str_Order=L"";
		str_Order.Format(L"%d",m_st_Netposition.Deal);
		col_row_val[4]=str_Order  ;		
		if (col_filter_val[4].Trim().GetLength()>0)
		{
			col_row_val[4]=col_row_val[4].Mid(0,col_filter_val[4].Trim().GetLength());
		}
		

		col_row_val[5]=m_st_Netposition.Order_type ;
		if (col_filter_val[5].Trim().GetLength()>0)
		{
			col_row_val[5]=col_row_val[5].Mid(0,col_filter_val[5].Trim().GetLength());
		}

		col_row_val[6]=m_st_Netposition.Symbol  ;
		if (col_filter_val[6].Trim().GetLength()>0)
		{
			col_row_val[6]=col_row_val[6].Mid(0,col_filter_val[6].Trim().GetLength());
		}

		col_row_val[7]=m_st_Netposition.Type  ;
		if (col_filter_val[7].Trim().GetLength()>0)
		{
			col_row_val[7]=col_row_val[7].Mid(0,col_filter_val[7].Trim().GetLength());
		}

		CString str_volume=L"";
		str_volume.Format(L"%.0f",m_st_Netposition.Volume);
		col_row_val[8]=str_volume  ;
		boolean bool_col7=Check_numeric_col_filter_1(col_filter_val[8],col_row_val[8]);

		CString str_price=L"";
		str_price.Format(L"%.4f",m_st_Netposition.Price);
		col_row_val[9]=str_price  ;
		boolean bool_col8=Check_numeric_col_filter_1(col_filter_val[9],col_row_val[9]);

		col_row_val[10]=m_st_Netposition.Comment  ;
		if (col_filter_val[10].Trim().GetLength()>0)
		{
			col_row_val[10]=col_row_val[10].Mid(0,col_filter_val[10].Trim().GetLength());
		}

		col_row_val[11]=m_st_Netposition.Entrytype  ;
		if (col_filter_val[11].Trim().GetLength()>0)
		{
			col_row_val[11]=col_row_val[11].Mid(0,col_filter_val[11].Trim().GetLength());
		}
		col_row_val[12]=m_st_Netposition.Current_Status  ;
		if (col_filter_val[12].Trim().GetLength()>0)
		{
			col_row_val[12]=col_row_val[12].Mid(0,col_filter_val[12].Trim().GetLength());
		}
				
		/*if((col_filter_val[0].Trim()==col_row_val[0].Trim() || col_filter_val[0].Trim()==L"ALL"||col_filter_val[0].Trim()==L"") && (col_filter_val[1].Trim()==col_row_val[1].Trim() || col_filter_val[1].Trim()==L"ALL"||col_filter_val[1].Trim()==L"") && (col_filter_val[2].Trim()==col_row_val[2].Trim() || col_filter_val[2].Trim()==L"ALL"||col_filter_val[2].Trim()==L"")  && (bool_col3==true  || col_filter_val[3].Trim()==L"ALL"||col_filter_val[3].Trim()==L"")  && (bool_col4==true  ||  col_filter_val[4].Trim()==L"ALL"||col_filter_val[4].Trim()==L"")   && (bool_col5==true || col_filter_val[5].Trim()==L"ALL"||col_filter_val[5].Trim()==L"")   && (bool_col6==true || col_filter_val[6].Trim()==L"ALL"||col_filter_val[6].Trim()==L"")   && (bool_col7==true || col_filter_val[7].Trim()==L"ALL"||col_filter_val[7].Trim()==L"")   && (bool_col8==true || col_filter_val[8].Trim()==L"ALL"||col_filter_val[8].Trim()==L"") && (bool_col9==true || col_filter_val[9]==L"ALL"||col_filter_val[9]==L"") &&(col_filter_val[10]==col_row_val[10] || col_filter_val[10]==L"ALL"||col_filter_val[10]==L"")&&(col_filter_val[11]==col_row_val[11] || col_filter_val[11]==L"ALL"||col_filter_val[11]==L""))
		{						
				noof_filterdata_count=noof_filterdata_count+1;						
		}*/
		
	 }
	 } 	 
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"   Grid Filter");			
	} 
}



void Dealing::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{	
	if (Dealing::insertFilterFlag==1)
	{
		if( row==0)
		{
			StartEdit();
		}	
	}

	
}	