#include "stdafx.h"
#include "npbpstype1grid.h"
#include "resource.h"
#include <afxdisp.h>
#include <time.h>
#include <locale.h>
#include "MainFrm.h"
#include "document.h"
#include <iostream>
#include "Login.h"
#include "NPBPSType1Table.h"

using namespace std;
using namespace rapidjson;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CNPBPSType1Grid,CUGCtrl)	
	ON_WM_SIZE()
	ON_WM_TIMER()		
END_MESSAGE_MAP()

int CNPBPSType1Grid::insertFilterFlag=0;
CNPBPSType1Grid::st_Dealing_Array CNPBPSType1Grid::m_st_Dealing_Array;	
CNPBPSType1Grid::st_Dealing_Array CNPBPSType1Grid::m_st_Dealing_Grid_array;
CMutex CNPBPSType1Grid::dealing_mutex;
CNPBPSType1Grid::st_Dealing_Array CNPBPSType1Grid::m_st_Dealing_Array_Fill;




UINT Show_NPBPStype1(void *pParam);
CNPBPSType1Grid::CNPBPSType1Grid(void)
{
	UGXPThemes::UseThemes(false);	
	col_click=0;
	a_d=0;
}


CNPBPSType1Grid::~CNPBPSType1Grid(void)
{
	//delete m_pThread;
	UGXPThemes::CleanUp();
}

void CNPBPSType1Grid::OnSetup()
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

		m_pThreads=AfxBeginThread(Show_NPBPStype1, this);	
	}
	 catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"   writeData");			
	}
}

void CNPBPSType1Grid::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();
	
	EnableMenu(TRUE);
	
	menu->AppendMenuW(MF_STRING|MF_UNCHECKED,2001,_T("Filter"));
	
	
	submenu.CreatePopupMenu();
}

void CNPBPSType1Grid::OnSheetSetup(int sheetNumber)
{
	int	nRow = 0, nCol = 0;	
	CUGCell cell;	
	SetGridDefault(&cell);
	EnableExcelBorders(TRUE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetDefFont(0);
	SetSH_Width(0);		
			
	SetNumberCols(22);

	QuickSetText(0,-1,L"Type1");
	SetColWidth(0,140);
	QuickSetText(1,-1,L"Login");
	SetColWidth(1,70);
	QuickSetText(2,-1,L"Order#");	
	SetColWidth(2,70);			
	QuickSetText(3,-1,L"Order_In_Time1");
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
	QuickSetText(11,-1,L"Type1");
	SetColWidth(11,60);
	QuickSetText(12,-1,L"SubType");
	SetColWidth(12,100);
    QuickSetText(13,-1,L"OldOrder#");
	SetColWidth(13,180);			
	QuickSetText(14,-1,L"Order_In_Time2");
	SetColWidth(14,70);
	QuickSetText(15,-1,L"Old_Deal");	
	SetColWidth(15,100);
	QuickSetText(16,-1,L"Deal_Time");
	SetColWidth(16,70);
	QuickSetText(17,-1,L"Symbol");
	SetColWidth(17,80);			
	QuickSetText(18,-1,L"Type");
	SetColWidth(18,70);
	QuickSetText(19,-1,L"Volume");
	SetColWidth(19,80);	
	QuickSetText(20,-1,L"Price");
	SetColWidth(20,60);
	QuickSetText(21,-1,L"Status");
	SetColWidth(21,60);



												
	// Header font
	for(int i = 0; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}	
}

void CNPBPSType1Grid::OnTimer(UINT nIDEvent)
{		
	CNPBPSType1Grid::dealing_mutex.Lock();	
	//m_st_Dealing_Grid_array.Assign(m_st_Dealing_Array);

	
	int noof_rowsInStruc=m_st_Dealing_Array.Total();	
	if (noof_rowsInStruc>0)
	{
		m_st_Dealing_Grid_array.Clear();
	}
	CString getColvalue=L"";
	CString col_filter_val[22];	
	for(int c=0;c<22;c++)
	{
		col_filter_val[c]=QuickGetText(c,0);
	}
	for(int fcount=0;fcount<noof_rowsInStruc;fcount++)
	{
		if (CNPBPSType1Grid::insertFilterFlag==1)
		{
		st_Dealing m_st_Netposition={};
		m_st_Netposition=m_st_Dealing_Array[fcount];
		
		int flag=0;				
		CString col_row_val[22];
		CString cstr_time=m_st_Netposition.Section ;
		
		col_row_val[0]=m_st_Netposition.Section  ;
		if (col_filter_val[0].Trim().GetLength()>0)
		{
			col_row_val[0]=col_row_val[0].Mid(0,col_filter_val[0].Trim().GetLength());
		}
		col_row_val[1]=m_st_Netposition.Login   ;
		if (col_filter_val[1].Trim().GetLength()>0)
		{
			col_row_val[1]=col_row_val[1].Mid(0,col_filter_val[1].Trim().GetLength());
		}


		CString str_deal=L"";
		str_deal.Format(L"%.0f",m_st_Netposition.Order  );
		col_row_val[2]=str_deal  ;
		if (col_filter_val[2].Trim().GetLength()>0)
		{
			col_row_val[2]=col_row_val[2].Mid(0,col_filter_val[2].Trim().GetLength());
		}

		CString str_Order=L"";
		str_Order.Format(L"%d",m_st_Netposition.Order_In_Time  );
		col_row_val[3]=str_Order  ;		
		if (col_filter_val[3].Trim().GetLength()>0)
		{
			col_row_val[3]=col_row_val[3].Mid(0,col_filter_val[3].Trim().GetLength());
		}



		
		str_deal.Format(L"%d",m_st_Netposition.Deal );
		col_row_val[4]=str_deal  ;
		if (col_filter_val[4].Trim().GetLength()>0)
		{
			col_row_val[4]=col_row_val[4].Mid(0,col_filter_val[4].Trim().GetLength());
		}

		
		str_Order=m_st_Netposition.Symbol;
		col_row_val[5]=str_Order  ;		
		if (col_filter_val[5].Trim().GetLength()>0)
		{
			col_row_val[5]=col_row_val[5].Mid(0,col_filter_val[5].Trim().GetLength());
		}
		
		str_Order=m_st_Netposition.Type1 ;
		col_row_val[6]=str_Order ;
		if (col_filter_val[6].Trim().GetLength()>0)
		{
			col_row_val[6]=col_row_val[6].Mid(0,col_filter_val[6].Trim().GetLength());
		}

		str_Order.Format(L"%.2f",m_st_Netposition.Volume );
		col_row_val[7]=str_Order  ;
		if (col_filter_val[7].Trim().GetLength()>0)
		{
			col_row_val[7]=col_row_val[7].Mid(0,col_filter_val[7].Trim().GetLength());
		}

		str_Order.Format(L"%.2f",m_st_Netposition.Price );
		col_row_val[8]=str_Order;
		if (col_filter_val[8].Trim().GetLength()>0)
		{
			col_row_val[8]=col_row_val[8].Mid(0,col_filter_val[8].Trim().GetLength());
		}			

		str_Order=m_st_Netposition.Comment ;
		col_row_val[9]=str_Order ;
		if (col_filter_val[9].Trim().GetLength()>0)
		{
			col_row_val[9]=col_row_val[9].Mid(0,col_filter_val[9].Trim().GetLength());
		}

		str_Order=m_st_Netposition.Status ;
		col_row_val[10]=str_Order ;
		if (col_filter_val[10].Trim().GetLength()>0)
		{
			col_row_val[10]=col_row_val[10].Mid(0,col_filter_val[10].Trim().GetLength());
		}

		str_Order=m_st_Netposition.Type ;
		col_row_val[11]=str_Order ;
		if (col_filter_val[11].Trim().GetLength()>0)
		{
			col_row_val[11]=col_row_val[11].Mid(0,col_filter_val[11].Trim().GetLength());
		}
		str_Order=m_st_Netposition.SubType ;
		col_row_val[12]=str_Order ;
		if (col_filter_val[12].Trim().GetLength()>0)
		{
			col_row_val[12]=col_row_val[12].Mid(0,col_filter_val[12].Trim().GetLength());
		}

		//extended colums
		str_Order=m_st_Netposition.OldOrder;
		col_row_val[13]=str_Order ;
		if (col_filter_val[13].Trim().GetLength()>0)
		{
			col_row_val[13]=col_row_val[13].Mid(0,col_filter_val[13].Trim().GetLength());
		}

		str_Order=m_st_Netposition.Order_In_Time;
		col_row_val[14]=str_Order ;
		if (col_filter_val[14].Trim().GetLength()>0)
		{
			col_row_val[14]=col_row_val[14].Mid(0,col_filter_val[14].Trim().GetLength());
		}

		str_Order=m_st_Netposition.Old_Deal;
		col_row_val[15]=str_Order ;
		if (col_filter_val[15].Trim().GetLength()>0)
		{
			col_row_val[15]=col_row_val[15].Mid(0,col_filter_val[15].Trim().GetLength());
		}

		str_Order=m_st_Netposition.Deal_Time;
		col_row_val[16]=str_Order ;
		if (col_filter_val[16].Trim().GetLength()>0)
		{
			col_row_val[16]=col_row_val[16].Mid(0,col_filter_val[16].Trim().GetLength());
		}

		str_Order=m_st_Netposition.Symbol1;
		col_row_val[17]=str_Order ;
		if (col_filter_val[17].Trim().GetLength()>0)
		{
			col_row_val[17]=col_row_val[17].Mid(0,col_filter_val[17].Trim().GetLength());
		}

		str_Order=m_st_Netposition.Type2;
		col_row_val[18]=str_Order ;
		if (col_filter_val[18].Trim().GetLength()>0)
		{
			col_row_val[18]=col_row_val[18].Mid(0,col_filter_val[18].Trim().GetLength());
		}

		str_Order.Format(L"%.2f",m_st_Netposition.Volume1 );
		col_row_val[19]=str_Order;
		if (col_filter_val[19].Trim().GetLength()>0)
		{
			col_row_val[19]=col_row_val[19].Mid(0,col_filter_val[19].Trim().GetLength());
		}	

		str_Order.Format(L"%.2f",m_st_Netposition.Price1 );
		col_row_val[20]=str_Order;
		if (col_filter_val[20].Trim().GetLength()>0)
		{
			col_row_val[20]=col_row_val[20].Mid(0,col_filter_val[20].Trim().GetLength());
		}	

		str_Order=m_st_Netposition.Status1;
		col_row_val[21]=str_Order ;
		if (col_filter_val[21].Trim().GetLength()>0)
		{
			col_row_val[21]=col_row_val[21].Mid(0,col_filter_val[21].Trim().GetLength());
		}


		if((col_filter_val[0].Trim()==col_row_val[0].Trim() || col_filter_val[0].Trim()==L"ALL"||col_filter_val[0].Trim()==L"") && (col_filter_val[1].Trim()==col_row_val[1].Trim() || col_filter_val[1].Trim()==L"ALL"||col_filter_val[1].Trim()==L"") && (col_filter_val[2].Trim()==col_row_val[2].Trim() || col_filter_val[2].Trim()==L"ALL"||col_filter_val[2].Trim()==L"")  && (col_filter_val[3].Trim()==col_row_val[3].Trim() || col_filter_val[3].Trim()==L"ALL"||col_filter_val[3].Trim()==L"")  && (col_filter_val[4].Trim()==col_row_val[4].Trim() || col_filter_val[4].Trim()==L"ALL"||col_filter_val[4].Trim()==L"")   && (col_filter_val[5].Trim()==col_row_val[5].Trim() || col_filter_val[5].Trim()==L"ALL"||col_filter_val[5].Trim()==L"")   && (col_filter_val[6].Trim()==col_row_val[6].Trim() || col_filter_val[6].Trim()==L"ALL"||col_filter_val[6].Trim()==L"")   && (col_filter_val[7].Trim()==col_row_val[7].Trim() || col_filter_val[7].Trim()==L"ALL"||col_filter_val[7].Trim()==L"")  && (col_filter_val[8].Trim()==col_row_val[8].Trim() || col_filter_val[8].Trim()==L"ALL"||col_filter_val[8].Trim()==L"")&&(col_filter_val[9].Trim()==col_row_val[9].Trim() || col_filter_val[9].Trim()==L"ALL"||col_filter_val[9].Trim()==L"") && (col_filter_val[10].Trim()==col_row_val[10].Trim() || col_filter_val[10].Trim()==L"ALL"||col_filter_val[10].Trim()==L"")&&(col_filter_val[11].Trim()==col_row_val[11].Trim() || col_filter_val[11].Trim()==L"ALL"||col_filter_val[11].Trim()==L"") && (col_filter_val[12].Trim()==col_row_val[12].Trim() || col_filter_val[12].Trim()==L"ALL"||col_filter_val[12].Trim()==L"")&& (col_filter_val[13].Trim()==col_row_val[13].Trim() || col_filter_val[13].Trim()==L"ALL"||col_filter_val[13].Trim()==L"")&& (col_filter_val[14].Trim()==col_row_val[14].Trim() || col_filter_val[14].Trim()==L"ALL"||col_filter_val[14].Trim()==L"")&& (col_filter_val[15].Trim()==col_row_val[15].Trim() || col_filter_val[15].Trim()==L"ALL"||col_filter_val[15].Trim()==L"")&& (col_filter_val[16].Trim()==col_row_val[16].Trim() || col_filter_val[16].Trim()==L"ALL"||col_filter_val[16].Trim()==L"")&& (col_filter_val[17].Trim()==col_row_val[17].Trim() || col_filter_val[17].Trim()==L"ALL"||col_filter_val[17].Trim()==L"")&& (col_filter_val[18].Trim()==col_row_val[18].Trim() || col_filter_val[18].Trim()==L"ALL"||col_filter_val[18].Trim()==L"")&& (col_filter_val[19].Trim()==col_row_val[19].Trim() || col_filter_val[19].Trim()==L"ALL"||col_filter_val[19].Trim()==L"")&& (col_filter_val[20].Trim()==col_row_val[20].Trim() || col_filter_val[20].Trim()==L"ALL"||col_filter_val[20].Trim()==L"")&& (col_filter_val[21].Trim()==col_row_val[21].Trim() || col_filter_val[21].Trim()==L"ALL"||col_filter_val[21].Trim()==L""))
		{						
			m_st_Dealing_Grid_array.Add(&m_st_Netposition);						
		}
		
	 }
		else
		{
			m_st_Dealing_Grid_array.Assign(m_st_Dealing_Array);	

		}
	}


	//Shorting Column
	int t_rows=m_st_Dealing_Grid_array.Total();
	st_Dealing first_st={};
	st_Dealing swap_st={};
	st_Dealing next_st={};
	

	int val_type=0;
	if (col_click==0||col_click==1)
	{
		val_type=0;
	}
	else
	{
		val_type=1;
	}
	for (int i=0;i<t_rows;i++)
	{
		first_st=m_st_Dealing_Grid_array[i];
		for (int j=i+1;j<t_rows;j++)
		{
			next_st=m_st_Dealing_Grid_array[j];
			if (a_d==0)
			{
				if (val_type==0)
				{
					if (col_click==0)
					{
						if (wcscmp(first_st.Section ,next_st.Section )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Section ,swap_st.Section );							
						}
					}
					if (col_click==1)
					{
						if (wcscmp(first_st.Login  ,next_st.Login  )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Login  ,swap_st.Login );							
						}
					}
				}
				else
				{
					if (col_click==2)
					{															
						double d_val1=first_st.Order ;															
						double d_val2=next_st.Order;						
						if (d_val1>d_val2)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							first_st.Order =swap_st.Order ;							
						}
					}
					//Order_In_Time
					if (col_click==3)
					{															
						if (wcscmp(first_st.Order_In_Time  ,next_st.Order_In_Time  )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Order_In_Time  ,swap_st.Order_In_Time );							
						}
					}
					if (col_click==4)
					{															
						int d_val1=first_st.Deal ;															
						int d_val2=next_st.Deal;						
						if (d_val1>d_val2)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							first_st.Deal =swap_st.Deal ;							
						}
					}
					if (col_click==5)
					{															
						if (wcscmp(first_st.Symbol  ,next_st.Symbol  )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Symbol  ,swap_st.Symbol );							
						}
					}
					if (col_click==6)
					{															
						if (wcscmp(first_st.Type1  ,next_st.Type1  )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Type1  ,swap_st.Type1 );							
						}
					}
					if (col_click==7)
					{															
						double d_val1=first_st.Volume  ;															
						double d_val2=next_st.Volume;
						if (d_val1>d_val2)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							first_st.Volume =swap_st.Volume;							
						}
					}
					if (col_click==8)
					{															
						double d_val1=first_st.Price   ;															
						double d_val2=next_st.Price;
						if (d_val1>d_val2)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							first_st.Price =swap_st.Price;					
						}
					}
					if (col_click==9)
					{															
						if (wcscmp(first_st.Comment  ,next_st.Comment  )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Comment  ,swap_st.Comment );							
						}
					}
					if (col_click==10)
					{															
						if (wcscmp(first_st.Status  ,next_st.Status  )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Status  ,swap_st.Status );							
						}
					}
					if (col_click==11)
					{															
						if (wcscmp(first_st.Type  ,next_st.Type  )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Type  ,swap_st.Type );							
						}
					}
					if (col_click==12)
					{															
						if (wcscmp(first_st.SubType  ,next_st.SubType  )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.SubType  ,swap_st.SubType );							
						}
					}

					//extended colums
					if (col_click==13)
					{															
						if (wcscmp(first_st.OldOrder  ,next_st.OldOrder  )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.OldOrder  ,swap_st.OldOrder );							
						}
					}

					if (col_click==14)
					{															
						if (wcscmp(first_st.Order_In_Time1  ,next_st.Order_In_Time1  )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Order_In_Time1  ,swap_st.Order_In_Time1 );							
						}
					}
					if (col_click==15)
					{															
						if (wcscmp(first_st.Old_Deal  ,next_st.Old_Deal  )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Old_Deal  ,swap_st.Old_Deal );							
						}
					}
					if (col_click==16)
					{															
						if (wcscmp(first_st.Deal_Time  ,next_st.Deal_Time  )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Deal_Time  ,swap_st.Deal_Time );							
						}
					}
					if (col_click==17)
					{															
						if (wcscmp(first_st.Symbol1  ,next_st.Symbol1  )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Symbol1  ,swap_st.Symbol1 );							
						}
					}
					if (col_click==18)
					{															
						if (wcscmp(first_st.Type2  ,next_st.Type2  )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Type2  ,swap_st.Type2 );							
						}
					}

					if (col_click==19)
					{															
						double d_val1=first_st.Volume1   ;															
						double d_val2=next_st.Volume1;
						if (d_val1>d_val2)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							first_st.Volume1 =swap_st.Volume1;					
						}
					}
					if (col_click==20)
					{															
						double d_val1=first_st.Price1   ;															
						double d_val2=next_st.Price1;
						if (d_val1>d_val2)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							first_st.Price1 =swap_st.Price1;					
						}
					}
					if (col_click==21)
					{															
						if (wcscmp(first_st.Status1  ,next_st.Status1  )>0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Status1  ,swap_st.Status1 );							
						}
					}
				}
			}
			else
			{
if (val_type==0)
				{
					if (col_click==0)
					{
						if (wcscmp(first_st.Section ,next_st.Section )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Section ,swap_st.Section );							
						}
					}
					if (col_click==1)
					{
						if (wcscmp(first_st.Login  ,next_st.Login  )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Login  ,swap_st.Login );							
						}
					}
				}
				else
				{
					if (col_click==2)
					{															
						double d_val1=first_st.Order ;															
						double d_val2=next_st.Order;						
						if (d_val1<d_val2)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							first_st.Order =swap_st.Order ;							
						}
					}

					if (col_click==3)
					{															
						if (wcscmp(first_st.Order_In_Time  ,next_st.Order_In_Time  )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Order_In_Time  ,swap_st.Order_In_Time );							
						}
					}
					if (col_click==4)
					{															
						int d_val1=first_st.Deal ;															
						int d_val2=next_st.Deal;						
						if (d_val1<d_val2)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							first_st.Deal =swap_st.Deal ;							
						}
					}
					if (col_click==5)
					{															
						if (wcscmp(first_st.Symbol  ,next_st.Symbol  )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Symbol  ,swap_st.Symbol );							
						}
					}
					if (col_click==6)
					{															
						if (wcscmp(first_st.Type1  ,next_st.Type1  )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Type1  ,swap_st.Type1 );							
						}
					}
					if (col_click==7)
					{															
						double d_val1=first_st.Volume ;															
						double d_val2=next_st.Volume;
						if (d_val1<d_val2)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							first_st.Volume =swap_st.Volume;							
						}
					}
					if (col_click==8)
					{															
						double d_val1=first_st.Price ;															
						double d_val2=next_st.Price;
						if (d_val1<d_val2)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							first_st.Price =swap_st.Price;					
						}
					}
					if (col_click==9)
					{															
						if (wcscmp(first_st.Comment  ,next_st.Comment  )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Comment  ,swap_st.Comment );							
						}
					}
					if (col_click==10)
					{															
						if (wcscmp(first_st.Comment  ,next_st.Comment  )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Comment  ,swap_st.Comment );							
						}
					}
					if (col_click==11)
					{															
						if (wcscmp(first_st.Type  ,next_st.Type  )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Type  ,swap_st.Type );							
						}
					}
					if (col_click==12)
					{															
						if (wcscmp(first_st.SubType  ,next_st.SubType  )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.SubType  ,swap_st.SubType );							
						}
					}

					//extended colums
					if (col_click==13)
					{															
						if (wcscmp(first_st.OldOrder  ,next_st.OldOrder  )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.OldOrder  ,swap_st.OldOrder );							
						}
					}

					if (col_click==14)
					{															
						if (wcscmp(first_st.Order_In_Time1  ,next_st.Order_In_Time1  )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Order_In_Time1  ,swap_st.Order_In_Time1 );							
						}
					}
					if (col_click==15)
					{															
						if (wcscmp(first_st.Old_Deal  ,next_st.Old_Deal  )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Old_Deal  ,swap_st.Old_Deal );							
						}
					}
					if (col_click==16)
					{															
						if (wcscmp(first_st.Deal_Time  ,next_st.Deal_Time  )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Deal_Time  ,swap_st.Deal_Time );							
						}
					}
					if (col_click==17)
					{															
						if (wcscmp(first_st.Symbol1  ,next_st.Symbol1  )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Symbol1  ,swap_st.Symbol1 );							
						}
					}
					if (col_click==18)
					{															
						if (wcscmp(first_st.Type2  ,next_st.Type2  )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Type2  ,swap_st.Type2 );							
						}
					}

					if (col_click==19)
					{															
						double d_val1=first_st.Volume1   ;															
						double d_val2=next_st.Volume1;
						if (d_val1<d_val2)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							first_st.Volume1 =swap_st.Volume1;					
						}
					}
					if (col_click==20)
					{															
						double d_val1=first_st.Price1   ;															
						double d_val2=next_st.Price1;
						if (d_val1<d_val2)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							first_st.Price1 =swap_st.Price1;					
						}
					}
					if (col_click==21)
					{															
						if (wcscmp(first_st.Status1  ,next_st.Status1  )<0)
						{
							m_st_Dealing_Grid_array.Shift(j,i-j);
							swap_st=m_st_Dealing_Grid_array[i];
							CMTStr::Copy(first_st.Status1  ,swap_st.Status1 );							
						}
					}
	
				}
					
			}
		}
	}
	//End of Shorting Col



	int r_count=m_st_Dealing_Grid_array.Total();
	CNPBPSType1Grid::dealing_mutex.Unlock();		
	int grid_total=GetNumberRows();
	
	if (CNPBPSType1Grid::insertFilterFlag==1)
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


void CNPBPSType1Grid::OnGetCell(int col,long row,CUGCell *cell)
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
			if (CNPBPSType1Grid::insertFilterFlag==1)
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
				tmp.Format(L"%.2f",mst_grid.Price);											
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
				CString tmp=mst_grid.Type;
															
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==12)
			{	
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.SubType;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}

			//exetended colums
			else if (col==13)
			{	
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.OldOrder;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==14)
			{	
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Order_In_Time1;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}

			else if (col==15)
			{	
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Old_Deal;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==16)
			{	
				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Deal_Time;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==17)
			{	
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Symbol1;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==18)
			{	
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				CString tmp=mst_grid.Type2;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==19)
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
			else if (col==20)
			{				
				mst_grid=m_st_Dealing_Grid_array[rows_no];
				double m_deal=mst_grid.Price1 ;

				CString tmp=L"" ;
				tmp.Format(L"%.2f",m_deal);
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
            else if (col==21)
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


void CNPBPSType1Grid::OnMenuCommand(int col,long row,int section,int item)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(section);
	// init. local variables

	switch( item )
	{
	  case 2001:
			   {
						filter();
						break;
			   }		  
	}
}
void CNPBPSType1Grid::filter()
{
	try
	{
	 CMenu *pMnenu;
	pMnenu= GetPopupMenu();

	if ( CNPBPSType1Grid::insertFilterFlag==0)
	{
			addItemToCombobox();
			CNPBPSType1Grid::insertFilterFlag=1;
			InsertRow(0);
			for (int col_count=0;col_count<22;col_count++)
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
		CNPBPSType1Grid::insertFilterFlag=0;
		
		pMnenu->CheckMenuItem(2001,MF_UNCHECKED);
	}
	RedrawAll();
	}
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"   filter");			
	} 
 }



void CNPBPSType1Grid::addItemToCombobox()
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
	CStringArray arr18;
	CStringArray arr19;	
	CStringArray arr20;	
	CStringArray arr21;
	
	try
	{
		int rows=1;
		rows=m_st_Dealing_Array.Total();	
		CString str_val=L"";	
		for (int forcount=0;forcount<22;forcount++)
		{
			str[forcount]=L"ALL\n";		
		}
		for (int forcount=0;forcount<rows;forcount++)
		{
			 st_Dealing m_st_Netposition={};
			 m_st_Netposition=m_st_Dealing_Array[forcount];
			for (int clocount=0;clocount<22;clocount++)
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
						
						str_val.Format(L"%d",m_st_Netposition.Order_In_Time);
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
						str_val.Format(L"%.2f",m_st_Netposition.Price);
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
					if (clocount==11)
					{						
						str_val=m_st_Netposition.Type;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr11,str_val)==false  && str_val!=L"")
						{
							str[11]=str[11]+str_val+L"\n";										
							arr11.Add(str_val);
						}
					}
					if (clocount==12)
					{						
						str_val=m_st_Netposition.SubType;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr12,str_val)==false  && str_val!=L"")
						{
							str[12]=str[12]+str_val+L"\n";										
							arr12.Add(str_val);
						}
					}

					//extendned colums
					if (clocount==13)
					{						
						str_val=m_st_Netposition.OldOrder;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr13,str_val)==false  && str_val!=L"")
						{
							str[13]=str[13]+str_val+L"\n";										
							arr13.Add(str_val);
						}
					}
					if (clocount==14)
					{						
						str_val=m_st_Netposition.Order_In_Time1;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr14,str_val)==false  && str_val!=L"")
						{
							str[14]=str[14]+str_val+L"\n";										
							arr14.Add(str_val);
						}
					}
					if (clocount==15)
					{						
						str_val=m_st_Netposition.Old_Deal;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr15,str_val)==false  && str_val!=L"")
						{
							str[15]=str[15]+str_val+L"\n";										
							arr15.Add(str_val);
						}
					}
					if (clocount==16)
					{						
						str_val=m_st_Netposition.Deal_Time;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr16,str_val)==false  && str_val!=L"")
						{
							str[16]=str[16]+str_val+L"\n";										
							arr16.Add(str_val);
						}
					}
					if (clocount==17)
					{						
						str_val=m_st_Netposition.Symbol1;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr17,str_val)==false  && str_val!=L"")
						{
							str[17]=str[17]+str_val+L"\n";										
							arr17.Add(str_val);
						}
					}
					if (clocount==18)
					{						
						str_val=m_st_Netposition.Type2;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr18,str_val)==false  && str_val!=L"")
						{
							str[18]=str[18]+str_val+L"\n";										
							arr18.Add(str_val);
						}
					}

					
					if (clocount==19)
					{
						double  u_deal=m_st_Netposition.Volume1  ;
						str_val.Format(L"%.2f",u_deal );
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr19,str_val)==false  && str_val!=L"")
						{
							str[19]=str[19]+str_val+L"\n";										
							arr19.Add(str_val);
						}
					}
					
					if (clocount==20)
					{
						double  u_deal=m_st_Netposition.Price1  ;
						str_val.Format(L"%.2f",u_deal );
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr20,str_val)==false  && str_val!=L"")
						{
							str[20]=str[20]+str_val+L"\n";										
							arr20.Add(str_val);
						}
					}
					if (clocount==21)
					{						
						str_val=m_st_Netposition.Status1;
						str_val=str_val.Trim();
						if (CheckvalueInArray(arr21,str_val)==false  && str_val!=L"")
						{
							str[21]=str[21]+str_val+L"\n";										
							arr21.Add(str_val);
						}
					}
			  }												
		}
		for(int f=0;f<22;f++)
		{
			colShorting(f);
		}		
	}
	catch(_com_error & ce)
	{
		AfxMessageBox(ce.Description()+L"addItemToCombobox");			
	} 
}

BOOLEAN  CNPBPSType1Grid::CheckvalueInArray(const CStringArray& arr,CString strval) 
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

void CNPBPSType1Grid::colShorting( int index)
{
	m_str_array.Clear();
	CString cstr=str[index];
	int str_len=cstr.GetLength();
	CString split_str=L"";
	for (int f=0;f<str_len;f++)
	{		
		if (cstr.Mid(f,1)!=L"\n")
		{
			split_str=split_str+cstr.Mid(f,1);
		}
		else
		{
			if (split_str.Trim().GetLength()>0 && split_str.Trim()!="ALL")
			{
				st_shorting m_st_shorting={};
				CMTStr::Copy(m_st_shorting.m_symbol,split_str);
				m_str_array.Add(&m_st_shorting);
			}
			split_str=L"";
		}
	}	
	int arr_count=m_str_array.Total();
	st_shorting  first_st={};
	st_shorting  next_st={};
	st_shorting  swap_st={};
	for (int f=0;f<arr_count;f++)
	{		
		first_st=m_str_array[f] ;
		for (int j=f+1;j<arr_count;j++)
		{			
			next_st=m_str_array[j];			
			if (wcscmp(first_st.m_symbol,next_st.m_symbol)>0)
			{
				m_str_array.Shift(j,f-j);
				swap_st=m_str_array[f];
				first_st=swap_st;							
			}
		}
	}
	st_shorting st_str={};
	CString final_str=L"";
	for (int f=0;f<arr_count;f++)
	{
		st_str=m_str_array[f];
		CString temp_str=st_str.m_symbol ;
		final_str=final_str+L"\n"+temp_str;
	}
	str[index]=L"ALL"+final_str;
}

UINT Show_NPBPStype1(void *pParam);
UINT Show_NPBPStype1(void *pParam)
{
	CNPBPSType1Grid* pThis= (CNPBPSType1Grid*)pParam;	
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<NPBPSType1Table> > artists1;	
	HRESULT hr;
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=Tradedatabase;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	if(SUCCEEDED(hr))
	{
		hr=session.Open(connection);
		while (true )
		{				
			CString strCommand=L"";		
			strCommand.Format(L"proc_Type1");        
			 if(SUCCEEDED(hr))
			 {
				hr=artists1.Open(session,(LPCTSTR)strCommand);							 
			 }
			 		
			 if(SUCCEEDED(hr))
			 {
				 CNPBPSType1Grid::m_st_Dealing_Array_Fill.Clear();
				 CNPBPSType1Grid::st_Dealing m_st_Dealing={};				 
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
					CMTStr::Copy(m_st_Dealing.SubType,artists1.m_SubType);
                    CMTStr::Copy(m_st_Dealing.OldOrder,artists1.m_OldOrder);
					CMTStr::Copy(m_st_Dealing.Order_In_Time1,artists1.m_Order_In_Time1);
					CMTStr::Copy(m_st_Dealing.Old_Deal,artists1.m_OldDeal);
					CMTStr::Copy(m_st_Dealing.Deal_Time,artists1.m_DealTime);
                    CMTStr::Copy(m_st_Dealing.Symbol1,artists1.m_Symbol1);
					CMTStr::Copy(m_st_Dealing.Type2,artists1.m_Type3);
					m_st_Dealing.Volume1 =artists1.m_Volume1 ;
					m_st_Dealing.Price1 =artists1.m_Price1;
					CMTStr::Copy(m_st_Dealing.Status1,artists1.m_Status1);
					

					CNPBPSType1Grid::m_st_Dealing_Array_Fill.Add(&m_st_Dealing);
				 }
				 artists1.Close();				    									 			 				 
			 }


			 CNPBPSType1Grid::dealing_mutex.Lock();	
			 CNPBPSType1Grid::m_st_Dealing_Array.Assign(CNPBPSType1Grid::m_st_Dealing_Array_Fill);
			 CNPBPSType1Grid::dealing_mutex.Unlock();	
			 Sleep(1000);
		}
	}
    return 0;
}


void CNPBPSType1Grid::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{		
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(processed);

	if( updn == 0)
		return;


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
