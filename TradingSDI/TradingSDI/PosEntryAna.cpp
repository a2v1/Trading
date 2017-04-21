#include "stdafx.h"
#include "PosEntryAna.h"
#include "document.h"
#include <iostream>
#include "Position_Entry_Analysis.h"
#include "GridTradeAndOrder.h"
#include "tab3.h"
#include <fstream>
using namespace std;
using namespace rapidjson;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
int PosEntryAna::insertFilterFlag=0;
//Structure variable
PosEntryAna::st_grid_anlysis_array PosEntryAna::m_st_grid_anlysis_Array_Fill;
PosEntryAna::st_grid_anlysis_array PosEntryAna::m_st_grid_anlysis_Grid_array;

PosEntryAna::st_grid_anlysis PosEntryAna::m_st_grid_anlysis={};

int PosEntryAna::m_selectedclient =0;
int PosEntryAna::val_type=0;
int PosEntryAna::col_click=0;
int PosEntryAna::a_d=0;
int PosEntryAna::filter_break=0;

CString PosEntryAna::col0_val=L"";
CString PosEntryAna::col1_val=L"";
CString PosEntryAna::col2_val=L"";
CString PosEntryAna::col3_val=L"";
CString PosEntryAna::col4_val=L"";
CString PosEntryAna::col5_val=L"";

PosEntryAna::PosEntryAna(void)
{
	UGXPThemes::UseThemes(false);
}


PosEntryAna::~PosEntryAna(void)
{
	UGXPThemes::CleanUp();
}

boolean Check_numeric_col_filter_analysis(CString  filter_value,CString  real_value);
boolean  Check_numeric_col_filter_analysis(CString  filter_value,CString  real_value)
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

void PosEntryAna::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
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

void PosEntryAna::Getdata(_bstr_t m_login)
{
	
	m_logfile.LogEvent(L"Start PosEntry Ana Grid ");
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<CPosition_Entry_Analysis> > artists1;	
	HRESULT hr;
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=CHECKDATA;Data Source=68.168.104.26;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	session.Open(connection);
	
			
	_bstr_t strCommand="select Deal,[Login],Symbol,Time,EntryVolume,EntryPrice from Position_Entry_Analysis where [login]='" + m_login + "'";		  
		hr=artists1.Open(session,(LPCTSTR)strCommand);	

		int rownumber=0;
	    if(SUCCEEDED(hr))
		 {
			PosEntryAna::m_st_grid_anlysis_Array_Fill.Clear();
			while (artists1.MoveNext() == S_OK)
			 {				 
				PosEntryAna::m_selectedclient=1;
				LPTSTR endPtr;
				double d_price = _tcstod(artists1.m_EntryPrice, &endPtr);												
				CString price;
				price.Format(_T("%.4f"),d_price);	
				PosEntryAna::st_grid_anlysis m_st={};
			
				CMTStr::Copy(m_st.m_deal ,artists1.m_deal);
				CMTStr::Copy(m_st.m_login,artists1.m_login);
				CMTStr::Copy(m_st.m_symbol ,artists1.m_symbol);
				CMTStr::Copy(m_st.m_time ,artists1.m_time);
				CMTStr::Copy(m_st.m_EntryVolume,artists1.m_EntryVolume);
				CMTStr::Copy(m_st.m_Entryprice,price);
				PosEntryAna::m_st_grid_anlysis_Array_Fill.Add(&m_st);
			 }
		  } 

		  if(PosEntryAna::m_selectedclient==0)
		  {
		      
		    AfxMessageBox(L"Data Not Found");
		  }
		  PosEntryAna::m_selectedclient=0;
		 //ASSINGNING into main array
		 PosEntryAna::m_st_grid_anlysis_Grid_array.Assign(PosEntryAna::m_st_grid_anlysis_Array_Fill);

	    //adding rows set rows
		RefreshGrid();

	artists1.Close();	
	session.Close();
	connection.Close();
    RedrawAll();
	m_logfile.LogEvent(L"END PosEntry Ana Grid");
	
}

void PosEntryAna::RefreshGrid()
{
	int r_count=PosEntryAna::m_st_grid_anlysis_Grid_array.Total();

		int grid_total=GetNumberRows();
		if (PosEntryAna::insertFilterFlag==1)
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

void PosEntryAna::OnSetup()
{
	CUGCell cell;
	GetGridDefault(&cell);
	SetGridDefault(&cell);
	EnableExcelBorders(FALSE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetUserSizingMode( TRUE  );
	SetVScrollMode(TRUE);
	
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

	SetNumberCols( 6);
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
void PosEntryAna::OnSheetSetup(int sheetNumber)
{
	int	nRow = 0, nCol = 0;
	EnableExcelBorders(TRUE);
	SetHighlightRow(TRUE, FALSE);
	SetDoubleBufferMode(TRUE);
	SetVScrollMode(TRUE);
	SetDefFont(0);
	SetSH_Width(0);	
	SetNumberCols(6);
	

	QuickSetText(0,-1,L"Deal");
	SetColWidth(0,100);

	QuickSetText(1,-1,L"Login");
	SetColWidth(1,120);

	QuickSetText(2,-1,L"Symbol");	
	SetColWidth(2,120);
			
	QuickSetText(3,-1,L"Time");
	SetColWidth(3,130);

	QuickSetText(4,-1,L"EntryVolume");
	SetColWidth(4,130);

	QuickSetText(5,-1,L"EntryPrice");
	SetColWidth(5,120);

	for(int i = 0; i < GetNumberCols(); i++)
	{
		QuickSetFont(i, -1, 1);
	}	
}

void PosEntryAna::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{	
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);

	PosEntryAna::col_click=col;
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
int PosEntryAna::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
{
if( flags & UG_SORT_DESCENDING )
	{
		CUGCell *ptr = cell1;
		cell1 = cell2;
		cell2 = ptr;
	}

int retVal = 0;

switch ( m_iSortCol )
{
case 0:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		  if(cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;

case 1:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 3:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 4:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
case 5:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;

default:
		if( CString(cell1->GetText()) == "")
			return 1;
		else if( CString(cell2->GetText()) == "")
			return -1;

		switch( cell1->GetDataType() )
		{
			case UGCELLDATA_NUMBER:
			case UGCELLDATA_BOOL:
			case UGCELLDATA_CURRENCY:
				if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
				if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
				break;

			default:
				retVal = _tcscmp( cell1->GetText( ), cell2->GetText());
		}
    }
 return retVal;
}
int PosEntryAna::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{

	if(ID == UGCT_DROPLIST){
		return OnDropList(ID, col, row, msg, param);
	}
}

int PosEntryAna::OnDropList(long ID,int col,long row,long msg,long param)
{
   if (msg==103)
	{
		if(PosEntryAna::insertFilterFlag==1 && row==0)
		{
			PosEntryAna::filter_break=1;
		//	check_First==0;
			CString  strval=L"";
			CUGCell cell;
			GetCell(col,row,&cell);
			strval=cell.GetText();
		//	PosEntryAna::strFilter="";		
		}

		

		if(PosEntryAna::insertFilterFlag==1 && row==0 )
		{
			
			CString  strval=L"";
			CUGCell cell;
			GetCell(col,row,&cell);
			strval=cell.GetText();	
			if(col==0)
			{
				if (strval!=L"")
				{
					PosEntryAna::col0_val=strval;					
				}
				else
				{
					PosEntryAna::col0_val=L"ALL";					
				}
			}


			if(col==1)
			{
				if (strval!=L"")
				{
					PosEntryAna::col1_val=strval;					
				}
				else
				{
					PosEntryAna::col1_val=L"ALL";					
				}
			}

			if(col==2)
			{
				if (strval!=L"")
				{
					PosEntryAna::col2_val=strval;					
				}
				else
				{
					PosEntryAna::col2_val=L"ALL";					
				}
			}

			if(col==3)
			{
				if (strval!=L"")
				{
					PosEntryAna::col3_val=strval;					
				}
				else
				{
					PosEntryAna::col3_val=L"ALL";					
				}
			}

			if(col==4)
			{
				if (strval!=L"")
				{
					PosEntryAna::col4_val=strval;					
				}
				else
				{
					PosEntryAna::col4_val=L"ALL";					
				}
			}

			if(col==5)
			{
				if (strval!=L"")
				{
					PosEntryAna::col5_val=strval;					
				}
				else
				{


					PosEntryAna::col5_val=L"ALL";					
				}
			}

		}
	   
	  ColValue_filter();
     }
	return true;
}


int PosEntryAna::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	    QuickSetText(col,row,string);		

     	if(PosEntryAna::insertFilterFlag==1 && row==0 )
		{
			
			CString  strval=L"";
			CUGCell cell;
			GetCell(col,row,&cell);
			strval=cell.GetText();	
			if(col==0)
			{
				if (strval!=L"")
				{
					PosEntryAna::col0_val=strval;					
				}
				else
				{
					PosEntryAna::col0_val=L"ALL";					
				}
			}


			if(col==1)
			{
				if (strval!=L"")
				{
					PosEntryAna::col1_val=string;					
				}
				else
				{
					PosEntryAna::col1_val=L"ALL";					
				}
			}

			if(col==2)
			{
				if (strval!=L"")
				{
					PosEntryAna::col2_val=string;					
				}
				else
				{
					PosEntryAna::col2_val=L"ALL";					
				}
			}

			if(col==3)
			{
				if (strval!=L"")
				{
					PosEntryAna::col3_val=string;					
				}
				else
				{
					PosEntryAna::col3_val=L"ALL";					
				}
			}

			if(col==4)
			{
				if (strval!=L"")
				{
					PosEntryAna::col4_val=string;					
				}
				else
				{
					PosEntryAna::col4_val=L"ALL";					
				}
			}

			if(col==5)
			{
				if (strval!=L"")
				{
					PosEntryAna::col5_val=string;					
				}
				else
				{
					PosEntryAna::col5_val=L"ALL";					
				}
			}
     }

  ColValue_filter();
  return true;
}

void PosEntryAna::InitMenu()
{
	CMenu submenu;
	CMenu * menu = GetPopupMenu();
	
	EnableMenu(TRUE);
	
	menu->AppendMenuW(MF_STRING|MF_UNCHECKED,2001,_T("Filter"));
}
void PosEntryAna::OnMenuCommand(int col,long row,int section,int item)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(section);
	CMenu* pMenu;
	pMenu = GetPopupMenu();

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

void PosEntryAna::filter()
{
	 CMenu *pMnenu;
   	pMnenu= GetPopupMenu();

	if ( PosEntryAna::insertFilterFlag==0)
	{
			addItemToCombobox();
			PosEntryAna::insertFilterFlag=1;
			InsertRow(0);
			for (int col_count=0;col_count<6;col_count++)
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
		PosEntryAna::insertFilterFlag=0;
		PosEntryAna::col0_val=L"";
		PosEntryAna::col1_val=L"";
		PosEntryAna::col2_val=L"";
		PosEntryAna::col3_val=L"";
		PosEntryAna::col4_val=L"";
		PosEntryAna::col5_val=L"";
		
		ColValue_filter();

		pMnenu->CheckMenuItem(2001,MF_UNCHECKED);
	}
	RedrawAll();
 }

BOOLEAN  PosEntryAna::CheckvalueInArray(const CStringArray& arr,CString strval) 
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
 
void PosEntryAna::addItemToCombobox()
{
	CStringArray arr;
	CStringArray arr1;
	CStringArray arr2;
	CStringArray arr3;
	CStringArray arr4;
	CStringArray arr5;
	CStringArray arr6;
	
	try
	{
	int rows=1;
	CString str_val=L"";
	
	for (int forcount=0;forcount<6;forcount++)
	{
		str[forcount]=L"ALL\n";		
	}

	st_grid_anlysis_array m_array_filter;
	m_array_filter.Assign(PosEntryAna::m_st_grid_anlysis_Array_Fill);
	
	rows=m_array_filter.Total();
	for (int forcount=0;forcount<rows;forcount++)
	{

		st_grid_anlysis m_st_for_filter={};
	    m_st_for_filter=m_array_filter[forcount];

		for (int clocount=0;clocount<6;clocount++)
		{
				if (clocount==0)
				{
					str_val=m_st_for_filter.m_deal;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr.Add(str_val);
					}
				}


				if (clocount==1)
				{
					str_val=m_st_for_filter.m_login ;
					if (str_val.GetLength()>10)
					{
						str_val=str_val.Mid(0,10);
					}
					if (CheckvalueInArray(arr1,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr1.Add(str_val);
					}
				}


				if (clocount==2)
				{
					str_val=m_st_for_filter.m_symbol ;
					if (str_val.GetLength()>10)
					{
						str_val=str_val.Mid(0,10);
					}
					if (CheckvalueInArray(arr2,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr2.Add(str_val);
					}
					
				}



				if (clocount==3)
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
					if (CheckvalueInArray(arr3,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr3.Add(str_val);
					}
				}

				if (clocount==4)
				{
					str_val=m_st_for_filter.m_EntryVolume ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr4,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr4.Add(str_val);
					}
				}
				if (clocount==5)
				{
					str_val=m_st_for_filter.m_Entryprice ;
					str_val=str_val.Trim();
					if (CheckvalueInArray(arr5,str_val)==false )
					{
						str[clocount]=str[clocount]+str_val+L"\n";										
						arr5.Add(str_val);
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

void PosEntryAna::OnGetCell(int col,long row,CUGCell *cell)
{		
		//m_logfile_g.LogEvent(L"Start OnGetCell");
	    PosEntryAna::st_grid_anlysis mst_grid={};

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
			if (PosEntryAna::insertFilterFlag==1)
			{
				rows_no=row-1;				
				if (row==0)
				{
					return;
				}
			}
			if (col==0)
			{		
				mst_grid=PosEntryAna::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_deal;										
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}

			else if (col==1)
			{

				mst_grid=PosEntryAna::m_st_grid_anlysis_Grid_array[rows_no];				
				CString tmp=mst_grid.m_login;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}

			}
			else if (col==2)
			{		
				mst_grid=PosEntryAna::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_symbol ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
				
			}
			else if (col==3)
			{	
				mst_grid=PosEntryAna::m_st_grid_anlysis_Grid_array[rows_no];
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
			else if (col==4)
			{				
				mst_grid=PosEntryAna::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_EntryVolume;				
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
			else if (col==5)
			{				
				mst_grid=PosEntryAna::m_st_grid_anlysis_Grid_array[rows_no];
				CString tmp=mst_grid.m_Entryprice  ;
				CString str_get_value=cell->GetText();
				if (wcscmp(str_get_value,tmp)!=0)
				{
					cell->SetText(tmp);
				}
			}
     }
}


void PosEntryAna::Col_sorting()
{
	int t_rows=PosEntryAna::m_st_grid_anlysis_Grid_array.Total();
	PosEntryAna::st_grid_anlysis first_st={};
	PosEntryAna::st_grid_anlysis next_st={};
	PosEntryAna::st_grid_anlysis swap_st={};
	PosEntryAna::val_type=0;
	if (PosEntryAna::col_click==4 || PosEntryAna::col_click==5)
	{
		PosEntryAna::val_type=1;
	}
	for (int i=0;i<t_rows;i++)
	{
		first_st=PosEntryAna::m_st_grid_anlysis_Grid_array[i];
		for (int j=i+1;j<t_rows;j++)
		{
			next_st=PosEntryAna::m_st_grid_anlysis_Grid_array[j];
			if (PosEntryAna::a_d==0)
			{
				if (PosEntryAna::val_type==0)
				{
					if (PosEntryAna::col_click==0)
					{
						if (wcscmp(first_st.m_deal   ,next_st.m_deal)>0)
						{
							PosEntryAna::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=PosEntryAna::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_deal ,swap_st.m_deal);							
						}
					}
					
					if (PosEntryAna::col_click==1)
					{
						if (wcscmp(first_st.m_login  ,next_st.m_login)>0)
						{
							PosEntryAna::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=PosEntryAna::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_login  ,swap_st.m_login);							
						}
					}
					if (PosEntryAna::col_click==2)
					{
						if (wcscmp(first_st.m_symbol   ,next_st.m_symbol)>0)
						{
							PosEntryAna::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=PosEntryAna::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_symbol ,swap_st.m_symbol  );							
						}
					}	

					if (PosEntryAna::col_click==3)
					{
						if (wcscmp(first_st.m_time   ,next_st.m_time   )>0)
						{
							PosEntryAna::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=PosEntryAna::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_time   ,swap_st.m_time  );							
						}
					}

				}	
				else
				{
					if (PosEntryAna::col_click==4)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_EntryVolume, &endPtr1);
						double val2=_tcstod(next_st.m_EntryVolume, &endPtr1);
						if (val1>val2)
						{
							PosEntryAna::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=PosEntryAna::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_EntryVolume  ,swap_st.m_EntryVolume);							
						}
					}
					if (PosEntryAna::col_click==5)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_Entryprice, &endPtr1);
						double val2=_tcstod(next_st.m_Entryprice, &endPtr1);
						if (val1>val2)
						{
							PosEntryAna::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=PosEntryAna::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_Entryprice ,swap_st.m_Entryprice);							
						}
					}
				}
			 }
			else
			{
				if (PosEntryAna::val_type==0)
				{

					if (PosEntryAna::col_click==0)
					{
						if (wcscmp(first_st.m_deal   ,next_st.m_deal)<0)
						{
							PosEntryAna::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=PosEntryAna::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_deal ,swap_st.m_deal);							
						}
					}
					
					if (PosEntryAna::col_click==1)
					{
						if (wcscmp(first_st.m_login  ,next_st.m_login)<0)
						{
							PosEntryAna::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=PosEntryAna::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_login  ,swap_st.m_login);							
						}
					}
					if (PosEntryAna::col_click==2)
					{
						if (wcscmp(first_st.m_symbol   ,next_st.m_symbol)<0)
						{
							PosEntryAna::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=PosEntryAna::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_symbol ,swap_st.m_symbol  );							
						}
					}	

					if (PosEntryAna::col_click==3)
					{
						if (wcscmp(first_st.m_time   ,next_st.m_time   )<0)
						{
							PosEntryAna::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=PosEntryAna::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_time   ,swap_st.m_time  );							
						}
					}

				}	
				else
				{
					if (PosEntryAna::col_click==4)
					{						
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_EntryVolume, &endPtr1);
						double val2=_tcstod(next_st.m_EntryVolume, &endPtr1);
						if (val1<val2)
						{
							PosEntryAna::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=PosEntryAna::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_EntryVolume  ,swap_st.m_EntryVolume);							
						}
					}
					if (PosEntryAna::col_click==5)
					{
						LPTSTR endPtr1;								
						double val1=_tcstod(first_st.m_Entryprice, &endPtr1);
						double val2=_tcstod(next_st.m_Entryprice, &endPtr1);
						if (val1<val2)
						{
							PosEntryAna::m_st_grid_anlysis_Grid_array.Shift(j,i-j);
							swap_st=PosEntryAna::m_st_grid_anlysis_Grid_array[i];
							CMTStr::Copy(first_st.m_Entryprice ,swap_st.m_Entryprice);							
						}
				    }				
			    }
		    }
		 }
	 }
}

void PosEntryAna::ColValue_filter()
{
      	PosEntryAna::val_type=0;
		if (PosEntryAna::insertFilterFlag==1 )
		{
		 PosEntryAna::m_st_grid_anlysis_Grid_array.Clear();
		 int noof_rowsInStruc=PosEntryAna::m_st_grid_anlysis_Array_Fill.Total();
		 for(int fcount=0;fcount<noof_rowsInStruc;fcount++)
		 {
			 st_grid_anlysis m_st_Netposition={};
			m_st_Netposition=PosEntryAna::m_st_grid_anlysis_Array_Fill[fcount];
			int flag=0;				
			CString col_row_val[11];		
			col_row_val[0]=m_st_Netposition.m_deal ;
			if (PosEntryAna::col0_val.Trim().GetLength()>0)
			{
				col_row_val[0]=col_row_val[0].Mid(0,PosEntryAna::col0_val.Trim().GetLength());
			}
			col_row_val[1]=m_st_Netposition.m_login ;
			if (PosEntryAna::col1_val.Trim().GetLength()>0)
			{
				col_row_val[1]=col_row_val[1].Mid(0,PosEntryAna::col1_val.Trim().GetLength());
				//col_row_val[1]=col_row_val[1].Mid(0,10);
			}
			col_row_val[2]=m_st_Netposition.m_symbol;
			if (PosEntryAna::col2_val.Trim().GetLength()>0)
			{
				col_row_val[2]=col_row_val[2].Mid(0,PosEntryAna::col2_val.Trim().GetLength());
			}

			UINT64 m_time=_wtoi( m_st_Netposition.m_time);
			CString tmp=L"";
			CMTStr256 str_time;
			SMTFormat::FormatDateTime(str_time,m_time,true,true);
			tmp=str_time.Str();

		    col_row_val[3]=tmp;

			if (PosEntryAna::col3_val.Trim().GetLength()>0)
			{
				col_row_val[3]=col_row_val[3].Mid(0,PosEntryAna::col3_val.Trim().GetLength());
				col_row_val[3]=col_row_val[3].Mid(0,10);
			}


			col_row_val[4]=m_st_Netposition.m_EntryVolume;
			boolean bool_col4=Check_numeric_col_filter_analysis(PosEntryAna::col4_val,col_row_val[4]);

			col_row_val[5]=m_st_Netposition.m_Entryprice;
			boolean bool_col5=Check_numeric_col_filter_analysis(PosEntryAna::col5_val,col_row_val[5]);

			
			if((PosEntryAna::col0_val.Trim()==col_row_val[0].Trim() || PosEntryAna::col0_val.Trim()==L"ALL"||PosEntryAna::col0_val.Trim()==L"") && (PosEntryAna::col1_val.Trim()==col_row_val[1].Trim() || PosEntryAna::col1_val.Trim()==L"ALL"||PosEntryAna::col1_val.Trim()==L"") && (PosEntryAna::col2_val.Trim()==col_row_val[2].Trim() || PosEntryAna::col2_val.Trim()==L"ALL"||PosEntryAna::col2_val.Trim()==L"")  && (PosEntryAna::col3_val.Trim()==col_row_val[3].Trim() || PosEntryAna::col3_val.Trim()==L"ALL"||PosEntryAna::col3_val.Trim()==L"") && (bool_col4==true || PosEntryAna::col4_val.Trim()==L"ALL"||PosEntryAna::col4_val.Trim()==L"")   && (bool_col5==true || PosEntryAna::col5_val.Trim()==L"ALL"||PosEntryAna::col5_val.Trim()==L"")) 
			{
				PosEntryAna::m_st_grid_anlysis_Grid_array.Add(&m_st_Netposition);
			}
		  }
		}
		else
		{
		
			PosEntryAna::m_st_grid_anlysis_Grid_array.Assign(PosEntryAna::m_st_grid_anlysis_Array_Fill);
		}


	RefreshGrid();

}
