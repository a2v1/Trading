#include "stdafx.h"
#include "BalanceAnaGrid.h"
#include "document.h"
#include <iostream>
#include "BalanceTableAnalysis.h"
#include "GridTradeAndOrder.h"
using namespace std;
using namespace rapidjson;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
int BalanceAnaGrid::insertFilterFlag=0;

//Structure variable
BalanceAnaGrid::st_grid_balanalysis_array BalanceAnaGrid::m_st_grid_anlysis_Array_Fill;
BalanceAnaGrid::st_grid_balanalysis_array BalanceAnaGrid::m_st_grid_anlysis_Grid_array;

BalanceAnaGrid::st_grid_balanalysis BalanceAnaGrid::m_st_grid_anlysis={};

int BalanceAnaGrid::m_selectedclient =0;

int BalanceAnaGrid::val_type=0;
int BalanceAnaGrid::col_click=0;
int BalanceAnaGrid::a_d=0;
int BalanceAnaGrid::filter_break=0;

CString BalanceAnaGrid::col0_val=L"";
CString BalanceAnaGrid::col1_val=L"";
CString BalanceAnaGrid::col2_val=L"";
CString BalanceAnaGrid::col3_val=L"";
CString BalanceAnaGrid::col4_val=L"";
CString BalanceAnaGrid::col5_val=L"";
CString BalanceAnaGrid::col6_val=L"";
CString BalanceAnaGrid::col7_val=L"";
CString BalanceAnaGrid::col8_val=L"";
CString BalanceAnaGrid::col9_val=L"";
CString BalanceAnaGrid::col10_val=L"";
CString BalanceAnaGrid::col11_val=L"";
CString BalanceAnaGrid::col12_val=L"";
CString BalanceAnaGrid::col13_val=L"";
CString BalanceAnaGrid::col14_val=L"";
CString BalanceAnaGrid::col15_val=L"";
CString BalanceAnaGrid::col16_val=L"";
CString BalanceAnaGrid::col17_val=L"";
CString BalanceAnaGrid::col18_val=L"";
CString BalanceAnaGrid::col19_val=L"";
CString BalanceAnaGrid::col20_val=L"";
CString BalanceAnaGrid::col21_val=L"";
CString BalanceAnaGrid::col22_val=L"";
CString BalanceAnaGrid::col23_val=L"";

BalanceAnaGrid::BalanceAnaGrid(void)
{
	UGXPThemes::UseThemes(false);
}


BalanceAnaGrid::~BalanceAnaGrid(void)
{
	UGXPThemes::CleanUp();
}
boolean Check_numeric_col_filter_balance_analysis(CString  filter_value,CString  real_value);
boolean  Check_numeric_col_filter_balance_analysis(CString  filter_value,CString  real_value)
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

void BalanceAnaGrid::GetData(_bstr_t m_login)
{
	logfile.LogEvent(L"Start Balance Grid ");
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<CBalanceTableAnalysis> > artists1;	
	HRESULT hr;
	
	
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=64.251.7.161;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	hr=session.Open(connection);

	  _bstr_t strCommand ="";
	  strCommand="select [Login],Deal,[Time],[Order],Symbol,EntryAction,EntryVolume,EntryPrice,ExitDeal,ExitTime,ExitOrder,ExitAction,ExitVolume,ExitPrice,ProfitPoint_L,ProfitPoint_P,Multiplayer,Balance,potentialprofitpoint,PotentialLosspoint,DurationTime,high,low from BalanceTableAnalysis where [login]='" + m_login + "'";
		
	  hr=artists1.Open(session,(LPCTSTR)strCommand);	

		 if(SUCCEEDED(hr))
		 {
			
			 BalanceAnaGrid::m_st_grid_anlysis_Array_Fill.Clear();
			 while (artists1.MoveNext() == S_OK)
			 {

				BalanceAnaGrid::m_selectedclient=1;
				LPTSTR endPtr;
				CString price=L"";
				CString exit_price=L"";
				CString ProfitPoint_L=L"";
				CString ProfitPoint_P=L"";
				CString Multiplayer=L"";
				CString Balance=L"";
				CString potentialprofitpoint=L"";
				CString PotentialLosspoint=L"";
				CString DurationTime=L"";
				CString high=L"";
				CString low=L"";

				double d_price = _tcstod(artists1.m_EntryPrice, &endPtr);												
				price.Format(_T("%.4f"),d_price);	

				double d_exit_price = _tcstod(artists1.m_ExitPrice, &endPtr);												
				exit_price.Format(_T("%.4f"),d_exit_price);

				double d_ProfitPoint_L = _tcstod(artists1.m_ProfitPoint_L, &endPtr);												
				ProfitPoint_L.Format(_T("%.2f"),d_ProfitPoint_L);

				double d_ProfitPoint_P = _tcstod(artists1.m_ProfitPoint_P, &endPtr);												
				ProfitPoint_P.Format(_T("%.2f"),d_ProfitPoint_P);

				double d_Multiplayer = _tcstod(artists1.m_Multiplayer, &endPtr);												
				Multiplayer.Format(_T("%.2f"),d_Multiplayer);

				double d_Balance = _tcstod(artists1.m_Balance, &endPtr);												
				Balance.Format(_T("%.2f"),d_Balance);

				double d_potentialprofitpoint = _tcstod(artists1.m_potentialprofitpoint, &endPtr);												
				potentialprofitpoint.Format(_T("%.2f"),d_potentialprofitpoint);

				double d_PotentialLosspoint = _tcstod(artists1.m_PotentialLosspoint, &endPtr);												
				PotentialLosspoint.Format(_T("%.2f"),d_PotentialLosspoint);

				double d_DurationTime = _tcstod(artists1.m_DurationTime, &endPtr);												
				DurationTime.Format(_T("%.2f"),d_DurationTime);

				double d_high = _tcstod(artists1.m_high, &endPtr);												
				high.Format(_T("%.4f"),d_high);

				double d_low = _tcstod(artists1.m_low, &endPtr);												
				low.Format(_T("%.4f"),d_low);
				
				BalanceAnaGrid::st_grid_balanalysis m_st={};
			
				CMTStr::Copy(m_st.m_login ,artists1.m_Login);
				CMTStr::Copy(m_st.m_deal,artists1.m_deal);
				CMTStr::Copy(m_st.m_time ,artists1.m_Time);
				CMTStr::Copy(m_st.m_Order ,artists1.m_Order);
				CMTStr::Copy(m_st.m_symbol,artists1.m_Symbol);
				CMTStr::Copy(m_st.m_EntryAction,artists1.m_EntryAction);


				CMTStr::Copy(m_st.m_EntryVolume ,artists1.m_EntryVolume);
				CMTStr::Copy(m_st.m_Entryprice,price);
				CMTStr::Copy(m_st.m_ExitDeal ,artists1.m_ExitDeal);
				CMTStr::Copy(m_st.m_ExitTime ,artists1.m_ExitTime);
				CMTStr::Copy(m_st.m_ExitOrder,artists1.m_ExitOrder);
				CMTStr::Copy(m_st.m_ExitAction,artists1.m_ExitAction);

				
				CMTStr::Copy(m_st.m_ExitVolume ,artists1.m_ExitVolume);
				CMTStr::Copy(m_st.m_ExitPrice,exit_price);
				CMTStr::Copy(m_st.m_ProfitPoint_L ,ProfitPoint_L);
				CMTStr::Copy(m_st.m_ProfitPoint_P ,ProfitPoint_P);
				CMTStr::Copy(m_st.m_Multiplayer,Multiplayer);
				CMTStr::Copy(m_st.m_Balance,Balance);


				CMTStr::Copy(m_st.m_potentialprofitpoint ,potentialprofitpoint);
				CMTStr::Copy(m_st.m_DurationTime,PotentialLosspoint);
				CMTStr::Copy(m_st.m_high ,high);
				CMTStr::Copy(m_st.m_low ,low);

				BalanceAnaGrid::m_st_grid_anlysis_Array_Fill.Add(&m_st);
			 }
          }   

		  if(BalanceAnaGrid::m_selectedclient==0)
		  {
		      
		    AfxMessageBox(L"Data Not Found");
		  }
		  BalanceAnaGrid::m_selectedclient=0;

		  //ASSINGNING into main array
		  BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Assign(BalanceAnaGrid::m_st_grid_anlysis_Array_Fill);

	    //adding rows set rows
		RefreshGrid();


    artists1.Close();   
	session.Close();
	connection.Close();
	RedrawAll();
	logfile.LogEvent(L"END Balance Grid ");
}

void BalanceAnaGrid::RefreshGrid()
{
	int r_count=BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Total();

		int grid_total=GetNumberRows();
		if (BalanceAnaGrid::insertFilterFlag==1)
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
void BalanceAnaGrid::OnSetup()
{
	CUGCell cell;
	GetGridDefault(&cell);
	SetGridDefault(&cell);
	EnableExcelBorders(FALSE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetUserSizingMode( TRUE  );

	
	InitMenu();
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

	SetNumberCols( 24);
	m_iArrowIndex = AddCellType( &m_sortArrow );

	SetCurrentCellMode( 2 );

	UseHints( TRUE );

	SetSH_Width( 0 );
	//SetUniformRowHeight( TRUE );
	






	// Start timers
	srand( (unsigned)time( NULL ) );
	SetTimer(0, 100, NULL);
	SetTimer(1, 100, NULL);

	

	QuickSetCellType( 0, -1, m_iArrowIndex );
	SortBy( 0, UG_SORT_ASCENDING );

	m_iSortCol = 0;
	m_bSortedAscending = TRUE;
}

int BalanceAnaGrid::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{

	if(ID == UGCT_DROPLIST){
		return OnDropList(ID, col, row, msg, param);
	}
}

void BalanceAnaGrid::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
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



int BalanceAnaGrid::OnDropList(long ID,int col,long row,long msg,long param)
{
  	if (msg==103)
	{
		if(BalanceAnaGrid::insertFilterFlag==1 && row==0)
		{
			BalanceAnaGrid::filter_break=1;
		//	check_First==0;
			CString  strval=L"";
			CUGCell cell;
			GetCell(col,row,&cell);
			strval=cell.GetText();
		//	BalanceAnaGrid::strFilter="";		
		}

		

		if(BalanceAnaGrid::insertFilterFlag==1 && row==0 )
		{
			
			CString  strval=L"";
			CUGCell cell;
			GetCell(col,row,&cell);
			strval=cell.GetText();	
			if(col==0)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col0_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col0_val=L"ALL";					
				}
			}


			if(col==1)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col1_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col1_val=L"ALL";					
				}
			}

			if(col==2)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col2_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col2_val=L"ALL";					
				}
			}

			if(col==3)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col3_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col3_val=L"ALL";					
				}
			}

			if(col==4)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col4_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col4_val=L"ALL";					
				}
			}

			if(col==5)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col5_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col5_val=L"ALL";					
				}
			}

			if(col==6)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col6_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col6_val=L"ALL";					
				}
			}

			if(col==7)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col7_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col7_val=L"ALL";					
				}
			}

			if(col==8)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col8_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col8_val=L"ALL";					
				}
			}

			if(col==9)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col9_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col9_val=L"ALL";					
				}
			}

			if(col==10)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col10_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col10_val=L"ALL";					
				}
			}

			//////////////////////
			if(col==11)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col11_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col11_val=L"ALL";					
				}
			}


			if(col==12)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col12_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col12_val=L"ALL";					
				}
			}

			if(col==13)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col13_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col13_val=L"ALL";					
				}
			}

			if(col==14)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col14_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col14_val=L"ALL";					
				}
			}

			if(col==15)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col15_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col15_val=L"ALL";					
				}
			}

			if(col==16)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col16_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col16_val=L"ALL";					
				}
			}

			if(col==17)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col17_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col17_val=L"ALL";					
				}
			}

			if(col==18)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col18_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col18_val=L"ALL";					
				}
			}

			if(col==19)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col19_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col19_val=L"ALL";					
				}
			}

			if(col==20)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col20_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col20_val=L"ALL";					
				}
			}

			if(col==21)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col21_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col21_val=L"ALL";					
				}
			}

			if(col==22)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col22_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col22_val=L"ALL";					
				}
			}
		 }
	   
	  ColValue_filter();
     }
	RedrawAll();
	return true;
}
	
int BalanceAnaGrid::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	    QuickSetText(col,row,string);	

	 	if(BalanceAnaGrid::insertFilterFlag==1 && row==0 )
		{
			
			CString  strval=L"";
			CUGCell cell;
			GetCell(col,row,&cell);
			strval=cell.GetText();	
			if(col==0)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col0_val=strval;					
				}
				else
				{
					BalanceAnaGrid::col0_val=L"ALL";					
				}
			}


			if(col==1)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col1_val=string;					
				}
				else
				{
					BalanceAnaGrid::col1_val=L"ALL";					
				}
			}

			if(col==2)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col2_val=string;					
				}
				else
				{
					BalanceAnaGrid::col2_val=L"ALL";					
				}
			}

			if(col==3)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col3_val=string;					
				}
				else
				{
					BalanceAnaGrid::col3_val=L"ALL";					
				}
			}

			if(col==4)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col4_val=string;					
				}
				else
				{
					BalanceAnaGrid::col4_val=L"ALL";					
				}
			}

			if(col==5)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col5_val=string;					
				}
				else
				{
					BalanceAnaGrid::col5_val=L"ALL";					
				}
			}

			if(col==6)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col6_val=string;					
				}
				else
				{
					BalanceAnaGrid::col6_val=L"ALL";					
				}
			}

			if(col==7)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col7_val=string;					
				}
				else
				{
					BalanceAnaGrid::col7_val=L"ALL";					
				}
			}

			if(col==8)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col8_val=string;					
				}
				else
				{
					BalanceAnaGrid::col8_val=L"ALL";					
				}
			}

			if(col==9)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col9_val=string;					
				}
				else
				{
					BalanceAnaGrid::col9_val=L"ALL";					
				}
			}

			if(col==10)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col10_val=string;					
				}
				else
				{
					BalanceAnaGrid::col10_val=L"ALL";					
				}
			}

			//////////////////////
			if(col==11)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col11_val=string;					
				}
				else
				{
					BalanceAnaGrid::col11_val=L"ALL";					
				}
			}


			if(col==12)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col12_val=string;					
				}
				else
				{
					BalanceAnaGrid::col12_val=L"ALL";					
				}
			}

			if(col==13)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col13_val=string;					
				}
				else
				{
					BalanceAnaGrid::col13_val=L"ALL";					
				}
			}

			if(col==14)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col14_val=string;					
				}
				else
				{
					BalanceAnaGrid::col14_val=L"ALL";					
				}
			}

			if(col==15)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col15_val=string;					
				}
				else
				{
					BalanceAnaGrid::col15_val=L"ALL";					
				}
			}

			if(col==16)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col16_val=string;					
				}
				else
				{
					BalanceAnaGrid::col16_val=L"ALL";					
				}
			}

			if(col==17)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col17_val=string;					
				}
				else
				{
					BalanceAnaGrid::col17_val=L"ALL";					
				}
			}

			if(col==18)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col18_val=string;					
				}
				else
				{
					BalanceAnaGrid::col18_val=L"ALL";					
				}
			}

			if(col==19)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col19_val=string;					
				}
				else
				{
					BalanceAnaGrid::col19_val=L"ALL";					
				}
			}

			if(col==20)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col20_val=string;					
				}
				else
				{
					BalanceAnaGrid::col20_val=L"ALL";					
				}
			}

			if(col==21)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col21_val=string;					
				}
				else
				{
					BalanceAnaGrid::col21_val=L"ALL";					
				}
			}

			if(col==22)
			{
				if (strval!=L"")
				{
					BalanceAnaGrid::col22_val=string;					
				}
				else
				{
					BalanceAnaGrid::col22_val=L"ALL";					
				}
		  }
	}
    
	ColValue_filter();

	RedrawAll();

	return true;
}

void BalanceAnaGrid::OnSheetSetup(int sheetNumber)
{
	int	nRow = 0, nCol = 0;
	EnableExcelBorders(TRUE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetDefFont(0);
	SetSH_Width(0);	
	SetNumberCols(23);

	QuickSetText(0,-1,L"Login");
	SetColWidth(0,100);

	QuickSetText(1,-1,L"Deal");
	SetColWidth(1,100);

	QuickSetText(2,-1,L"Time");	
	SetColWidth(2,120);
			
	QuickSetText(3,-1,L"Order");
	SetColWidth(3,120);

	QuickSetText(4,-1,L"Symbol");
	SetColWidth(4,100);

	QuickSetText(5,-1,L"EntryAction");
	SetColWidth(5,100);
	QuickSetText(6,-1,L"EntryVolume");
	SetColWidth(6,100);

	QuickSetText(7,-1,L"EntryPrice");
	SetColWidth(7,100);

	QuickSetText(8,-1,L"ExitDeal");	
	SetColWidth(8,100);
			
	QuickSetText(9,-1,L"ExitTime");
	SetColWidth(9,120);

	QuickSetText(10,-1,L"ExitOrder");
	SetColWidth(10,110);

	QuickSetText(11,-1,L"ExitAction");
	SetColWidth(11,120);
	QuickSetText(12,-1,L"ExitVolume");
	SetColWidth(12,100);

	QuickSetText(13,-1,L"ExitPrice");
	SetColWidth(13,120);

	QuickSetText(14,-1,L"ProfitPoint_L");	
	SetColWidth(14,120);
			
	QuickSetText(15,-1,L"ProfitPoint_P");
	SetColWidth(15,120);

	QuickSetText(16,-1,L"Multiplayer");
	SetColWidth(16,130);

	QuickSetText(17,-1,L"Balance");
	SetColWidth(17,120);
	QuickSetText(18,-1,L"PotentialProfitPoint");	
	SetColWidth(18,120);
			
	QuickSetText(19,-1,L"PotentialLossPoint");
	SetColWidth(19,130);

	QuickSetText(20,-1,L"TimeDuration");
	SetColWidth(20,130);

	QuickSetText(21,-1,L"High");
	SetColWidth(21,120);
    QuickSetText(22,-1,L"Low");
	SetColWidth(22,120);



	for(int i = 0; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}	
}

void BalanceAnaGrid::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{	
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);

	BalanceAnaGrid::col_click=col;
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

	}
	else
	{
		SortBy( col, UG_SORT_DESCENDING );
		QuickSetCellType( m_iSortCol, -1, m_iArrowIndex );
		QuickSetCellTypeEx( m_iSortCol, -1, UGCT_SORTARROWUP );

	}

	Col_sorting();
  
    RedrawAll();
}


void BalanceAnaGrid::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();
	
	EnableMenu(TRUE);
	
	menu->AppendMenuW(MF_STRING|MF_UNCHECKED,2001,_T("Filter"));
}
void BalanceAnaGrid::OnMenuCommand(int col,long row,int section,int item)
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
    RedrawAll();
}

void BalanceAnaGrid::filter()
{
	CMenu *pMnenu;
	pMnenu= GetPopupMenu();

	if ( BalanceAnaGrid::insertFilterFlag==0)
	{
			addItemToCombobox();
			BalanceAnaGrid::insertFilterFlag=1;
			InsertRow(0);
			for (int col_count=0;col_count<23;col_count++)
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
		BalanceAnaGrid::insertFilterFlag=0;

		BalanceAnaGrid::col0_val=L"";
		BalanceAnaGrid::col1_val=L"";
		BalanceAnaGrid::col2_val=L"";
		BalanceAnaGrid::col3_val=L"";
		BalanceAnaGrid::col4_val=L"";
		BalanceAnaGrid::col5_val=L"";
		BalanceAnaGrid::col6_val=L"";
		BalanceAnaGrid::col7_val=L"";
		BalanceAnaGrid::col8_val=L"";
		BalanceAnaGrid::col9_val=L"";
		BalanceAnaGrid::col10_val=L"";

		BalanceAnaGrid::col11_val=L"";
		BalanceAnaGrid::col12_val=L"";
		BalanceAnaGrid::col13_val=L"";
		BalanceAnaGrid::col14_val=L"";
		BalanceAnaGrid::col15_val=L"";
		BalanceAnaGrid::col16_val=L"";
		BalanceAnaGrid::col17_val=L"";
		BalanceAnaGrid::col18_val=L"";
		BalanceAnaGrid::col19_val=L"";
		BalanceAnaGrid::col20_val=L"";
		BalanceAnaGrid::col21_val=L"";
		BalanceAnaGrid::col22_val=L"";
	
		ColValue_filter();
		pMnenu->CheckMenuItem(2001,MF_UNCHECKED);
	}
	RedrawAll();
 }

BOOLEAN  BalanceAnaGrid::CheckvalueInArray(const CStringArray& arr,CString strval) 
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
 
void BalanceAnaGrid::addItemToCombobox()
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
	CStringArray arr22;

	try
	{
	int rows=1;
	
	
	CString str_val=L"";

	for (int forcount=0;forcount<24;forcount++)
	{
		str[forcount]=L"ALL\n";		
	}

	st_grid_balanalysis_array m_array_filter;
	m_array_filter.Assign(BalanceAnaGrid::m_st_grid_anlysis_Array_Fill);
	
	rows=m_array_filter.Total();
	for (int forcount=0;forcount<rows;forcount++)
	{
		st_grid_balanalysis m_st_for_filter={};
	    m_st_for_filter=m_array_filter[forcount];

		for (int clocount=0;clocount<24;clocount++)
		{
		    
			   if (clocount==0)
				{
					str_val=m_st_for_filter.m_login;
					str_val=str_val.Trim();

					if (CheckvalueInArray(arr,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr.Add(str_val);
					}
				}


				if (clocount==1)
				{
					str_val=m_st_for_filter.m_deal;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr1,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr1.Add(str_val);
					}
				}


				if (clocount==2)
				{
				
					UINT64 m_time=_wtoi( m_st_for_filter.m_time);
				    CString tmp=L"";
				    CMTStr256 str_time;
				    SMTFormat::FormatDateTime(str_time,m_time,true,true);
				    tmp=str_time.Str();

				//	str_val=m_st_for_filter.m_time ;
					str_val=tmp.Trim();
					if (str_val.GetLength()>10)
					{
						str_val=str_val.Mid(0,10);
					}
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr2,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr2.Add(str_val);
					}
				}



				if (clocount==3)
				{
					str_val=m_st_for_filter.m_Order;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr3,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr3.Add(str_val);
					}
				}

				if (clocount==4)
				{
					str_val=m_st_for_filter.m_symbol;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr4,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr4.Add(str_val);
					}
				}
				if (clocount==5)
				{
					str_val=m_st_for_filter.m_EntryAction;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr5,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr5.Add(str_val);
					}
				}
				if (clocount==6)
				{
					str_val=m_st_for_filter.m_EntryVolume;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr6,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr6.Add(str_val);
					}
				}
				if (clocount==7)
				{
					str_val=m_st_for_filter.m_Entryprice;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr7,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr7.Add(str_val);
					}
				}
				if (clocount==8)
				{
					str_val=m_st_for_filter.m_ExitDeal;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr8,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr8.Add(str_val);
					}
				}
				if (clocount==9)
				{
					UINT64 m_time=_wtoi( m_st_for_filter.m_ExitTime);
				    CString tmp=L"";
				    CMTStr256 str_time;
				    SMTFormat::FormatDateTime(str_time,m_time,true,true);
				    tmp=str_time.Str();

				//	str_val=m_st_for_filter.m_time ;
					str_val=tmp.Trim();
					if (str_val.GetLength()>10)
					{
						str_val=str_val.Mid(0,10);
					}
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr9,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr9.Add(str_val);
					}
				}
				if (clocount==10)
				{
					str_val=m_st_for_filter.m_ExitOrder;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr10,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr10.Add(str_val);
					}
				}
				if (clocount==11)
				{
					str_val=m_st_for_filter.m_ExitAction;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr11,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr11.Add(str_val);
					}
				}
				if (clocount==12)
				{
					str_val=m_st_for_filter.m_ExitVolume;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr12,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr12.Add(str_val);
					}
				}
				if (clocount==13)
				{
					str_val=m_st_for_filter.m_ExitPrice;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr13,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr13.Add(str_val);
					}
				}
				if (clocount==14)
				{
					str_val=m_st_for_filter.m_ProfitPoint_L;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr14,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr14.Add(str_val);
					}
				}
				if (clocount==15)
				{
					str_val=m_st_for_filter.m_ProfitPoint_P;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr15,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr15.Add(str_val);
					}
				}
				if (clocount==16)
				{
					str_val=m_st_for_filter.m_Multiplayer;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr16,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr16.Add(str_val);
					}
				}
				if (clocount==17)
				{
					str_val=m_st_for_filter.m_Balance;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr17,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr17.Add(str_val);
					}
				}
				if (clocount==18)
				{
					str_val=m_st_for_filter.m_potentialprofitpoint;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr18,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr18.Add(str_val);
					}
				}
				if (clocount==19)
				{
					str_val=m_st_for_filter.m_PotentialLosspoint;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr19,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr19.Add(str_val);
					}
				}
				if (clocount==20)
				{
					str_val=m_st_for_filter.m_DurationTime;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr20,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr20.Add(str_val);
					}
				}
				if (clocount==21)
				{
					str_val=m_st_for_filter.m_high;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr21,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr21.Add(str_val);
					}
				}
				if (clocount==22)
				{
					str_val=m_st_for_filter.m_low;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr22,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr22.Add(str_val);
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

//void BalanceAnaGrid::gridFilter(int colno,int rows_count,CString col_value)
//{
//	
//	CString getColvalue=L"";
//	CString col_filter_val[23];
//	
//	for(int c=0;c<23;c++)
//	{
//		col_filter_val[c]=QuickGetText(c,0);
//	}
//	for(int fcount=rows_count-1;fcount>0;fcount--)
//	{
//		int flag=0;		
//		
//		CString col_row_val[23];
//		for(int c=0;c<23;c++)
//		{
//			col_row_val[c]=QuickGetText(c,fcount);
//		}
//		if((col_filter_val[0]==col_row_val[0] || col_filter_val[0]==L"ALL"||col_filter_val[0]==L"") && (col_filter_val[1]==col_row_val[1] || col_filter_val[1]==L"ALL"||col_filter_val[1]==L"") && (col_filter_val[2]==col_row_val[2] || col_filter_val[2]==L"ALL"||col_filter_val[2]==L"")  && (col_filter_val[3]==col_row_val[3] || col_filter_val[3]==L"ALL"||col_filter_val[3]==L"")  && (col_filter_val[4]==col_row_val[4] || col_filter_val[4]==L"ALL"||col_filter_val[4]==L"")   && (col_filter_val[5]==col_row_val[5] || col_filter_val[5]==L"ALL"||col_filter_val[5]==L"")   && (col_filter_val[6]==col_row_val[6] || col_filter_val[6]==L"ALL"||col_filter_val[6]==L"")   && (col_filter_val[7]==col_row_val[7] || col_filter_val[7]==L"ALL"||col_filter_val[7]==L"")   && (col_filter_val[8]==col_row_val[8] || col_filter_val[8]==L"ALL"||col_filter_val[8]==L"") && (col_filter_val[9]==col_row_val[9] || col_filter_val[9]==L"ALL"||col_filter_val[9]==L"") &&(col_filter_val[10]==col_row_val[10] || col_filter_val[10]==L"ALL"||col_filter_val[10]==L"")&&(col_filter_val[11]==col_row_val[11] || col_filter_val[11]==L"ALL"||col_filter_val[11]==L"")&&(col_filter_val[12]==col_row_val[12] || col_filter_val[12]==L"ALL"||col_filter_val[12]==L"") &&(col_filter_val[13]==col_row_val[13] || col_filter_val[13]==L"ALL"||col_filter_val[13]==L"")&&(col_filter_val[14]==col_row_val[14] || col_filter_val[14]==L"ALL"||col_filter_val[14]==L"")&&(col_filter_val[15]==col_row_val[15] || col_filter_val[15]==L"ALL"||col_filter_val[15]==L"")&&(col_filter_val[16]==col_row_val[16] || col_filter_val[16]==L"ALL"||col_filter_val[16]==L"")&&(col_filter_val[17]==col_row_val[17] || col_filter_val[17]==L"ALL"||col_filter_val[17]==L"")&&(col_filter_val[18]==col_row_val[18] || col_filter_val[18]==L"ALL"||col_filter_val[18]==L"")&&(col_filter_val[19]==col_row_val[19] || col_filter_val[19]==L"ALL"||col_filter_val[19]==L"")&&(col_filter_val[20]==col_row_val[20] || col_filter_val[20]==L"ALL"||col_filter_val[20]==L"")&&(col_filter_val[21]==col_row_val[21] || col_filter_val[21]==L"ALL"||col_filter_val[21]==L"")&&(col_filter_val[22]==col_row_val[22] || col_filter_val[22]==L"ALL"||col_filter_val[22]==L""))
//		{			
//			CString checkblakval=QuickGetText(0,fcount);
//			checkblakval=checkblakval.Trim();
//			if(checkblakval.Trim().GetLength()>0)
//			{
//				flag=1;
//			}			
//		}
//		else
//		{			
//			flag=0;			
//		}
//				
//		
//		if (flag==1)
//		{
//			SetRowHeight(fcount, 20);
//		}
//		else
//		{   
//			 SetRowHeight(fcount, 0);
//		
//		 }
//	 }
//	
//}

void BalanceAnaGrid::OnGetCell(int col,long row,CUGCell *cell)
{		
		//m_logfile_g.LogEvent(L"Start OnGetCell");
	    BalanceAnaGrid::st_grid_balanalysis mst_grid={};

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
			if (BalanceAnaGrid::insertFilterFlag==1)
			{
				rows_no=row-1;				
				if (row==0)
				{
					return;
				}
			}
			if (col==0)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_login;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}

			else if (col==1)
			{

				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];				
				CString tmp=mst_grid.m_deal;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==2)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];

				UINT64 m_time=_wtoi( mst_grid.m_time);
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
			else if (col==3)
			{	
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_Order ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}


			else if (col==4)
			{	
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_symbol ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==5)
			{				
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_EntryAction;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==6)
			{				
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_EntryVolume  ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}


			//////////////////////////////
			else if (col==7)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_Entryprice;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}

			else if (col==8)
			{

				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];				
				CString tmp=mst_grid.m_ExitDeal;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==9)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];

				UINT64 m_time=_wtoi( mst_grid.m_ExitTime);
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
			else if (col==10)
			{	
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_ExitOrder ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==11)
			{				
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_ExitAction;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==12)
			{				
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_ExitVolume  ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}

			////////////////////////////////////
			else if (col==13)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_ExitPrice;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}

			else if (col==14)
			{

				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];				
				CString tmp=mst_grid.m_ProfitPoint_L;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==15)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_ProfitPoint_P ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
				
			}
			else if (col==16)
			{	
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_Multiplayer ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==17)
			{				
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_Balance;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==18)
			{				
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_potentialprofitpoint  ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			////////////////////////////////
			else if (col==19)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_PotentialLosspoint;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}

			else if (col==20)
			{

				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];				
				CString tmp=mst_grid.m_DurationTime;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==21)
			{		
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_high ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
				
			}
		  else if (col==22)
		  {	
				mst_grid=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_low ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

		   }
	}
}


void BalanceAnaGrid::Col_sorting()
{
	int t_rows=BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Total();
	BalanceAnaGrid::st_grid_balanalysis first_st={};
	BalanceAnaGrid::st_grid_balanalysis next_st={};
	BalanceAnaGrid::st_grid_balanalysis swap_st={};
	BalanceAnaGrid::val_type=0;
	if (BalanceAnaGrid::col_click==6||BalanceAnaGrid::col_click==7 ||BalanceAnaGrid::col_click==12|| BalanceAnaGrid::col_click==13||BalanceAnaGrid::col_click==14 || BalanceAnaGrid::col_click==15||BalanceAnaGrid::col_click==16 || BalanceAnaGrid::col_click==17||BalanceAnaGrid::col_click==18 || BalanceAnaGrid::col_click==19||BalanceAnaGrid::col_click==20 || BalanceAnaGrid::col_click==21||BalanceAnaGrid::col_click==22|| BalanceAnaGrid::col_click==23)
	{
		BalanceAnaGrid::val_type=1;
	}
	for (int i=0;i<t_rows;i++)
	{
		first_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
		for (int j=i+1;j<t_rows;j++)
		{
			next_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[j];
			if (BalanceAnaGrid::a_d==0)
			{
				if (BalanceAnaGrid::val_type==0)
				{
					if (BalanceAnaGrid::col_click==0)
					{
						if (wcscmp(first_st.m_login  ,next_st.m_login)>0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_login ,swap_st.m_login);							
						}
					}
					
					if (BalanceAnaGrid::col_click==1)
					{
						if (wcscmp(first_st.m_deal  ,next_st.m_deal)>0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_deal  ,swap_st.m_deal);							
						}
					}
					if (BalanceAnaGrid::col_click==2)
					{
						if (wcscmp(first_st.m_time   ,next_st.m_time)>0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_time ,swap_st.m_time  );							
						}
					}	

					if (BalanceAnaGrid::col_click==3)
					{
						if (wcscmp(first_st.m_Order   ,next_st.m_Order   )>0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_Order   ,swap_st.m_Order  );							
						}
					}

					//////////////////////////////////
					
					if (BalanceAnaGrid::col_click==4)
					{
						if (wcscmp(first_st.m_symbol  ,next_st.m_symbol)>0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_symbol  ,swap_st.m_symbol);							
						}
					}
					if (BalanceAnaGrid::col_click==5)
					{
						if (wcscmp(first_st.m_EntryAction   ,next_st.m_EntryAction)>0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_EntryAction ,swap_st.m_EntryAction  );							
						}
					}	

					////////////////////////////////////
					if (BalanceAnaGrid::col_click==8)
					{
						if (wcscmp(first_st.m_ExitDeal   ,next_st.m_ExitDeal)>0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ExitDeal ,swap_st.m_ExitDeal);							
						}
					}

					if (BalanceAnaGrid::col_click==9)
					{
						if (wcscmp(first_st.m_ExitTime   ,next_st.m_ExitTime)>0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ExitTime ,swap_st.m_ExitTime);							
						}
					}
					
					if (BalanceAnaGrid::col_click==10)
					{
						if (wcscmp(first_st.m_ExitOrder  ,next_st.m_ExitOrder)>0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ExitOrder  ,swap_st.m_ExitOrder);							
						}
					}
					if (BalanceAnaGrid::col_click==11)
					{
						if (wcscmp(first_st.m_ExitAction   ,next_st.m_ExitAction)>0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ExitAction ,swap_st.m_ExitAction  );							
						}
					}	

				}	
				else
				{
					if (BalanceAnaGrid::col_click==6)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_EntryVolume, &endPtr1);
						double val2=_tcstod(next_st.m_EntryVolume, &endPtr1);
						if (val1>val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_EntryVolume  ,swap_st.m_EntryVolume);							
						}
					}


					if (BalanceAnaGrid::col_click==7)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_Entryprice, &endPtr1);
						double val2=_tcstod(next_st.m_Entryprice, &endPtr1);
						if (val1>val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_Entryprice  ,swap_st.m_Entryprice);							
						}
					}

					if (BalanceAnaGrid::col_click==12)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_ExitVolume, &endPtr1);
						double val2=_tcstod(next_st.m_ExitVolume, &endPtr1);
						if (val1>val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ExitVolume  ,swap_st.m_ExitVolume);							
						}
					}

					
					if (BalanceAnaGrid::col_click==13)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_ExitPrice, &endPtr1);
						double val2=_tcstod(next_st.m_ExitPrice, &endPtr1);
						if (val1>val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ExitPrice ,swap_st.m_ExitPrice);							
						}
					}
					///////////////////////////
					if (BalanceAnaGrid::col_click==14)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_ProfitPoint_L, &endPtr1);
						double val2=_tcstod(next_st.m_ProfitPoint_L, &endPtr1);
						if (val1>val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ProfitPoint_L  ,swap_st.m_ProfitPoint_L);							
						}
					}
					if (BalanceAnaGrid::col_click==15)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_ProfitPoint_P, &endPtr1);
						double val2=_tcstod(next_st.m_ProfitPoint_P, &endPtr1);
						if (val1>val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ProfitPoint_P ,swap_st.m_ProfitPoint_P);							
						}
					}
					if (BalanceAnaGrid::col_click==16)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_Multiplayer, &endPtr1);
						double val2=_tcstod(next_st.m_Multiplayer, &endPtr1);
						if (val1>val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_Multiplayer  ,swap_st.m_Multiplayer);							
						}
					}
					if (BalanceAnaGrid::col_click==17)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_Balance, &endPtr1);
						double val2=_tcstod(next_st.m_Balance, &endPtr1);
						if (val1>val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_Balance ,swap_st.m_Balance);							
						}
					}
					/////////////////////////////
					if (BalanceAnaGrid::col_click==18)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_potentialprofitpoint, &endPtr1);
						double val2=_tcstod(next_st.m_potentialprofitpoint, &endPtr1);
						if (val1>val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_potentialprofitpoint  ,swap_st.m_potentialprofitpoint);							
						}
					}
					if (BalanceAnaGrid::col_click==19)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_PotentialLosspoint, &endPtr1);
						double val2=_tcstod(next_st.m_PotentialLosspoint, &endPtr1);
						if (val1>val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_PotentialLosspoint ,swap_st.m_PotentialLosspoint);							
						}
					}
					if (BalanceAnaGrid::col_click==20)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_DurationTime, &endPtr1);
						double val2=_tcstod(next_st.m_DurationTime, &endPtr1);
						if (val1>val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_DurationTime  ,swap_st.m_DurationTime);							
						}
					}
					if (BalanceAnaGrid::col_click==21)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_high, &endPtr1);
						double val2=_tcstod(next_st.m_high, &endPtr1);
						if (val1>val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_high ,swap_st.m_high);							
						}
					}
					if (BalanceAnaGrid::col_click==22)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_low, &endPtr1);
						double val2=_tcstod(next_st.m_low, &endPtr1);
						if (val1>val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_low ,swap_st.m_low);							
						}
					}
				
				}
			 }
			else
			{
				if (BalanceAnaGrid::val_type==0)
				{

					if (BalanceAnaGrid::col_click==0)
					{
						if (wcscmp(first_st.m_login  ,next_st.m_login)<0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_login ,swap_st.m_login);							
						}
					}
					
					if (BalanceAnaGrid::col_click==1)
					{
						if (wcscmp(first_st.m_deal  ,next_st.m_deal)<0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_deal  ,swap_st.m_deal);							
						}
					}
					if (BalanceAnaGrid::col_click==2)
					{
						if (wcscmp(first_st.m_time   ,next_st.m_time)<0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_time ,swap_st.m_time  );							
						}
					}	

					if (BalanceAnaGrid::col_click==3)
					{
						if (wcscmp(first_st.m_Order   ,next_st.m_Order   )<0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_Order   ,swap_st.m_Order  );							
						}
					}

					//////////////////////////////////
					
					if (BalanceAnaGrid::col_click==4)
					{
						if (wcscmp(first_st.m_symbol  ,next_st.m_symbol)<0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_symbol  ,swap_st.m_symbol);							
						}
					}
					if (BalanceAnaGrid::col_click==5)
					{
						if (wcscmp(first_st.m_EntryAction   ,next_st.m_EntryAction)<0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_EntryAction ,swap_st.m_EntryAction  );							
						}
					}	

					////////////////////////////////////
					if (BalanceAnaGrid::col_click==8)
					{
						if (wcscmp(first_st.m_ExitDeal   ,next_st.m_ExitDeal)<0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ExitDeal ,swap_st.m_ExitDeal);							
						}
					}

					if (BalanceAnaGrid::col_click==9)
					{
						if (wcscmp(first_st.m_ExitTime   ,next_st.m_ExitTime)<0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ExitTime ,swap_st.m_ExitTime);							
						}
					}
					
					if (BalanceAnaGrid::col_click==10)
					{
						if (wcscmp(first_st.m_ExitOrder  ,next_st.m_ExitOrder)<0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ExitOrder  ,swap_st.m_ExitOrder);							
						}
					}
					if (BalanceAnaGrid::col_click==11)
					{
						if (wcscmp(first_st.m_ExitAction   ,next_st.m_ExitAction)<0)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ExitAction ,swap_st.m_ExitAction  );							
						}
					}

				}	
				else
				{

					
					if (BalanceAnaGrid::col_click==6)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_EntryVolume, &endPtr1);
						double val2=_tcstod(next_st.m_EntryVolume, &endPtr1);
						if (val1<val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_EntryVolume  ,swap_st.m_EntryVolume);							
						}
					}

					if (BalanceAnaGrid::col_click==7)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_Entryprice, &endPtr1);
						double val2=_tcstod(next_st.m_Entryprice, &endPtr1);
						if (val1<val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_Entryprice  ,swap_st.m_Entryprice);							
						}
					}

					if (BalanceAnaGrid::col_click==12)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_ExitVolume, &endPtr1);
						double val2=_tcstod(next_st.m_ExitVolume, &endPtr1);
						if (val1<val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ExitVolume  ,swap_st.m_ExitVolume);							
						}
					}


					if (BalanceAnaGrid::col_click==13)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_ExitPrice, &endPtr1);
						double val2=_tcstod(next_st.m_ExitPrice, &endPtr1);
						if (val1<val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ExitPrice ,swap_st.m_ExitPrice);							
						}
					}
					///////////////////////////
					if (BalanceAnaGrid::col_click==14)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_ProfitPoint_L, &endPtr1);
						double val2=_tcstod(next_st.m_ProfitPoint_L, &endPtr1);
						if (val1<val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ProfitPoint_L  ,swap_st.m_ProfitPoint_L);							
						}
					}
					if (BalanceAnaGrid::col_click==15)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_ProfitPoint_P, &endPtr1);
						double val2=_tcstod(next_st.m_ProfitPoint_P, &endPtr1);
						if (val1<val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_ProfitPoint_P ,swap_st.m_ProfitPoint_P);							
						}
					}
					if (BalanceAnaGrid::col_click==16)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_Multiplayer, &endPtr1);
						double val2=_tcstod(next_st.m_Multiplayer, &endPtr1);
						if (val1<val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_Multiplayer  ,swap_st.m_Multiplayer);							
						}
					}
					if (BalanceAnaGrid::col_click==17)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_Balance, &endPtr1);
						double val2=_tcstod(next_st.m_Balance, &endPtr1);
						if (val1<val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_Balance ,swap_st.m_Balance);							
						}
					}
					/////////////////////////////
					if (BalanceAnaGrid::col_click==18)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_potentialprofitpoint, &endPtr1);
						double val2=_tcstod(next_st.m_potentialprofitpoint, &endPtr1);
						if (val1<val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_potentialprofitpoint  ,swap_st.m_potentialprofitpoint);							
						}
					}
					if (BalanceAnaGrid::col_click==19)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_PotentialLosspoint, &endPtr1);
						double val2=_tcstod(next_st.m_PotentialLosspoint, &endPtr1);
						if (val1>val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_PotentialLosspoint ,swap_st.m_PotentialLosspoint);							
						}
					}
					if (BalanceAnaGrid::col_click==20)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_DurationTime, &endPtr1);
						double val2=_tcstod(next_st.m_DurationTime, &endPtr1);
						if (val1<val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_DurationTime  ,swap_st.m_DurationTime);							
						}
					}
					if (BalanceAnaGrid::col_click==21)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_high, &endPtr1);
						double val2=_tcstod(next_st.m_high, &endPtr1);
						if (val1<val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_high ,swap_st.m_high);							
						}
					}
					if (BalanceAnaGrid::col_click==22)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_low, &endPtr1);
						double val2=_tcstod(next_st.m_low, &endPtr1);
						if (val1<val2)
						{
							BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=BalanceAnaGrid::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_low ,swap_st.m_low);							
						}
					}				
			    }
		    }
		 }
	 }
}

void BalanceAnaGrid::ColValue_filter()
{
      	BalanceAnaGrid::val_type=0;
		if (BalanceAnaGrid::insertFilterFlag==1 )
		{
		 BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Clear();
		 int noof_rowsInStruc=BalanceAnaGrid::m_st_grid_anlysis_Array_Fill.Total();
		 for(int fcount=0;fcount<noof_rowsInStruc;fcount++)
		 {
			st_grid_balanalysis m_st_Netposition={};
			m_st_Netposition=BalanceAnaGrid::m_st_grid_anlysis_Array_Fill[fcount];
			int flag=0;				
			CString col_row_val[23];		
			col_row_val[0]=m_st_Netposition.m_login ;
			if (BalanceAnaGrid::col0_val.Trim().GetLength()>0)
			{
				col_row_val[0]=col_row_val[0].Mid(0,BalanceAnaGrid::col0_val.Trim().GetLength());
			}
			col_row_val[1]=m_st_Netposition.m_deal ;
			if (BalanceAnaGrid::col1_val.Trim().GetLength()>0)
			{
				col_row_val[1]=col_row_val[1].Mid(0,BalanceAnaGrid::col1_val.Trim().GetLength());
				
			}

			UINT64 m_time=_wtoi( m_st_Netposition.m_time);
			CString tmp=L"";
			CMTStr256 str_time;
			SMTFormat::FormatDateTime(str_time,m_time,true,true);
			tmp=str_time.Str();
			col_row_val[2]=tmp;

			if (BalanceAnaGrid::col2_val.Trim().GetLength()>0)
			{
				col_row_val[2]=col_row_val[2].Mid(0,BalanceAnaGrid::col2_val.Trim().GetLength());
				col_row_val[2]=col_row_val[2].Mid(0,10);
			}
						
			col_row_val[3]=m_st_Netposition.m_Order ;
			if (BalanceAnaGrid::col3_val.Trim().GetLength()>0)
			{
				col_row_val[3]=col_row_val[3].Mid(0,BalanceAnaGrid::col3_val.Trim().GetLength());
			}


			/////////////////////////////////
			col_row_val[4]=m_st_Netposition.m_symbol ;
			if (BalanceAnaGrid::col4_val.Trim().GetLength()>0)
			{
				col_row_val[4]=col_row_val[4].Mid(0,BalanceAnaGrid::col4_val.Trim().GetLength());
			}
			col_row_val[5]=m_st_Netposition.m_EntryAction ;
			if (BalanceAnaGrid::col5_val.Trim().GetLength()>0)
			{
				col_row_val[5]=col_row_val[5].Mid(0,BalanceAnaGrid::col5_val.Trim().GetLength());
				//col_row_val[1]=col_row_val[1].Mid(0,10);
			}
		
						
			col_row_val[8]=m_st_Netposition.m_ExitDeal;
			if (BalanceAnaGrid::col8_val.Trim().GetLength()>0)
			{
				col_row_val[8]=col_row_val[8].Mid(0,BalanceAnaGrid::col8_val.Trim().GetLength());
			}
			/////////////////////////////

			UINT64 m_exit_time=_wtoi( m_st_Netposition.m_ExitTime);
			CString exit_tmp=L"";
			CMTStr256 str_exit_time;
			SMTFormat::FormatDateTime(str_exit_time,m_exit_time,true,true);
			exit_tmp=str_exit_time.Str();

			col_row_val[9]=exit_tmp.Trim();

			if (BalanceAnaGrid::col9_val.Trim().GetLength()>0)
			{
				col_row_val[9]=col_row_val[9].Mid(0,BalanceAnaGrid::col9_val.Trim().GetLength());
				col_row_val[9]=col_row_val[9].Mid(0,10);
			}

			col_row_val[10]=m_st_Netposition.m_ExitOrder;
			if (BalanceAnaGrid::col10_val.Trim().GetLength()>0)
			{
				col_row_val[10]=col_row_val[10].Mid(0,BalanceAnaGrid::col10_val.Trim().GetLength());
				
			}
			col_row_val[11]=m_st_Netposition.m_ExitAction;
			if (BalanceAnaGrid::col11_val.Trim().GetLength()>0)
			{
				col_row_val[11]=col_row_val[11].Mid(0,BalanceAnaGrid::col11_val.Trim().GetLength());
			}
			
			col_row_val[6]=m_st_Netposition.m_EntryVolume;
			boolean bool_col6=Check_numeric_col_filter_balance_analysis(BalanceAnaGrid::col6_val,col_row_val[6]);


			col_row_val[7]=m_st_Netposition.m_Entryprice;
			boolean bool_col7=Check_numeric_col_filter_balance_analysis(BalanceAnaGrid::col7_val,col_row_val[7]);

			col_row_val[12]=m_st_Netposition.m_ExitVolume ;
			boolean bool_col12=Check_numeric_col_filter_balance_analysis(BalanceAnaGrid::col12_val,col_row_val[12]);

			col_row_val[13]=m_st_Netposition.m_ExitPrice;
			boolean bool_col13=Check_numeric_col_filter_balance_analysis(BalanceAnaGrid::col13_val,col_row_val[13]);

			col_row_val[14]=m_st_Netposition.m_ProfitPoint_L;
			boolean bool_col14=Check_numeric_col_filter_balance_analysis(BalanceAnaGrid::col14_val,col_row_val[14]);

			col_row_val[15]=m_st_Netposition.m_ProfitPoint_P;
			boolean bool_col15=Check_numeric_col_filter_balance_analysis(BalanceAnaGrid::col15_val,col_row_val[15]);

			col_row_val[16]=m_st_Netposition.m_Multiplayer;
			boolean bool_col16=Check_numeric_col_filter_balance_analysis(BalanceAnaGrid::col16_val,col_row_val[16]);

			col_row_val[17]=m_st_Netposition.m_Balance;
			boolean bool_col17=Check_numeric_col_filter_balance_analysis(BalanceAnaGrid::col17_val,col_row_val[17]);

			col_row_val[18]=m_st_Netposition.m_potentialprofitpoint;
			boolean bool_col18=Check_numeric_col_filter_balance_analysis(BalanceAnaGrid::col18_val,col_row_val[18]);

			col_row_val[19]=m_st_Netposition.m_PotentialLosspoint;
			boolean bool_col19=Check_numeric_col_filter_balance_analysis(BalanceAnaGrid::col19_val,col_row_val[19]);

			col_row_val[20]=m_st_Netposition.m_DurationTime;
			boolean bool_col20=Check_numeric_col_filter_balance_analysis(BalanceAnaGrid::col20_val,col_row_val[20]);

			col_row_val[21]=m_st_Netposition.m_high;
			boolean bool_col21=Check_numeric_col_filter_balance_analysis(BalanceAnaGrid::col21_val,col_row_val[21]);

			col_row_val[22]=m_st_Netposition.m_low;
			boolean bool_col22=Check_numeric_col_filter_balance_analysis(BalanceAnaGrid::col22_val,col_row_val[22]);

			
			if((BalanceAnaGrid::col0_val.Trim()==col_row_val[0].Trim() || BalanceAnaGrid::col0_val.Trim()==L"ALL"||BalanceAnaGrid::col0_val.Trim()==L"") && (BalanceAnaGrid::col1_val.Trim()==col_row_val[1].Trim() || BalanceAnaGrid::col1_val.Trim()==L"ALL"||BalanceAnaGrid::col1_val.Trim()==L"") && (BalanceAnaGrid::col2_val.Trim()==col_row_val[2].Trim() || BalanceAnaGrid::col2_val.Trim()==L"ALL"||BalanceAnaGrid::col2_val.Trim()==L"")  && (BalanceAnaGrid::col3_val.Trim()==col_row_val[3].Trim() || BalanceAnaGrid::col3_val.Trim()==L"ALL"||BalanceAnaGrid::col3_val.Trim()==L"") && (BalanceAnaGrid::col4_val.Trim()==col_row_val[4].Trim() || BalanceAnaGrid::col4_val.Trim()==L"ALL"||BalanceAnaGrid::col4_val.Trim()==L"")   && (BalanceAnaGrid::col5_val.Trim()==col_row_val[5].Trim() || BalanceAnaGrid::col5_val.Trim()==L"ALL"||BalanceAnaGrid::col5_val.Trim()==L"") &&(bool_col6==true || BalanceAnaGrid::col6_val.Trim()==L"ALL"||BalanceAnaGrid::col6_val.Trim()==L"")   && (bool_col7==true || BalanceAnaGrid::col7_val.Trim()==L"ALL"||BalanceAnaGrid::col7_val.Trim()==L"")  && (BalanceAnaGrid::col8_val.Trim()==col_row_val[8].Trim() || BalanceAnaGrid::col8_val.Trim()==L"ALL"||BalanceAnaGrid::col8_val.Trim()==L"")  && (BalanceAnaGrid::col9_val.Trim()==col_row_val[9].Trim() || BalanceAnaGrid::col9_val.Trim()==L"ALL"||BalanceAnaGrid::col9_val.Trim()==L"") && (BalanceAnaGrid::col10_val.Trim()==col_row_val[10].Trim() || BalanceAnaGrid::col10_val.Trim()==L"ALL"||BalanceAnaGrid::col0_val.Trim()==L"") && (BalanceAnaGrid::col11_val.Trim()==col_row_val[11].Trim() || BalanceAnaGrid::col11_val.Trim()==L"ALL"||BalanceAnaGrid::col11_val.Trim()==L"")   && (bool_col12==true || BalanceAnaGrid::col12_val.Trim()==L"ALL"||BalanceAnaGrid::col12_val.Trim()==L"")   &&(bool_col13==true || BalanceAnaGrid::col13_val.Trim()==L"ALL"||BalanceAnaGrid::col13_val.Trim()==L"")  &&(bool_col14==true || BalanceAnaGrid::col14_val.Trim()==L"ALL"||BalanceAnaGrid::col14_val.Trim()==L"") && (bool_col15==true || BalanceAnaGrid::col15_val.Trim()==L"ALL"||BalanceAnaGrid::col15_val.Trim()==L"") && (bool_col16==true || BalanceAnaGrid::col16_val.Trim()==L"ALL"||BalanceAnaGrid::col16_val.Trim()==L"") && (bool_col17==true || BalanceAnaGrid::col17_val.Trim()==L"ALL"||BalanceAnaGrid::col17_val.Trim()==L"") && (bool_col18==true || BalanceAnaGrid::col18_val.Trim()==L"ALL"||BalanceAnaGrid::col18_val.Trim()==L"")  && (bool_col19==true || BalanceAnaGrid::col19_val.Trim()==L"ALL"||BalanceAnaGrid::col19_val.Trim()==L"")  && (bool_col20==true || BalanceAnaGrid::col20_val.Trim()==L"ALL"||BalanceAnaGrid::col20_val.Trim()==L"") && (bool_col21==true || BalanceAnaGrid::col21_val.Trim()==L"ALL"||BalanceAnaGrid::col21_val.Trim()==L"")   && (bool_col22==true || BalanceAnaGrid::col22_val.Trim()==L"ALL"||BalanceAnaGrid::col22_val.Trim()==L"")) 
			{
				BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Add(&m_st_Netposition);
			}
		  }
		}
		else
		{
		
			BalanceAnaGrid::m_st_grid_anlysis_Grid_array.Assign(BalanceAnaGrid::m_st_grid_anlysis_Array_Fill);
		}


	RefreshGrid();

}
