#include "stdafx.h"
#include "LTPupdate.h"
#include "OutputWnd.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
BEGIN_MESSAGE_MAP(LTPupdate,CUGCtrl)	
	
END_MESSAGE_MAP()


LTPupdate::LTPupdate(void)
{
}


LTPupdate::~LTPupdate(void)
{
}

void LTPupdate::GetData()
{
	
	CoInitialize(NULL);
	CDataSource connection;
	CSession session;
	CCommand<CAccessor<CLTPTable> > artists1;	
	HRESULT hr;
	 int intRows=0;
	
	hr=connection.OpenFromInitializationString(L"Provider=SQLNCLI11.1;Password=ok@12345;Persist Security Info=False;User ID=sa;Initial Catalog=TradeDataBase;Data Source=64.251.7.161;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=WINDOWS-LOJSHQK;Initial File Name=\"\";Use Encryption for Data=False;Tag with column collation when possible=False;MARS Connection=False;DataTypeCompatibility=0;Trust Server Certificate=False;Application Intent=READWRITE");
	
	session.Open(connection);
	
			
		_bstr_t strCommand="";		  
		strCommand="select t2.symbol,t2.Mapping_Symbol ,last_tick.last_tick  from (select t1.symbol,Mapping_Symbol from (select distinct(symbol) as symbol from mt5_deals  where isnull(symbol,'')<>'')t1 left outer join symbol_mapping on t1.symbol=symbol_mapping.symbol)t2 left outer join Last_tick on Last_tick.symbol=t2.Mapping_Symbol ";
        char* strCommand_char=(char*)strCommand;
		hr=artists1.Open(session,strCommand_char);	

		 if(SUCCEEDED(hr))
		 {
			int rownumber=0;
			 
			 while (artists1.MoveNext() == S_OK)
			 {
				 InsertRow(rownumber);
				QuickSetText(0,rownumber,artists1.m_Symbol);
				QuickSetText(1,rownumber,artists1.m_symbolmapping );
				CString str=L"";
				str.Format(L"%.4f",artists1.m_LTPUpdate);
				QuickSetText(2,rownumber,str );
				rownumber=rownumber+1;
			 }
			  
			   artists1.Close();
			   
             }
		  
	    RedrawAll();
     
}

void LTPupdate::OnSetup()
{
	SetNumberCols(3);
	//SetNumberRows(20);
	
	//soritng
	m_iArrowIndex = AddCellType( &m_sortArrow );

	SetCurrentCellMode( 2 );

	UseHints( TRUE );

	SetSH_Width( 0 );

	QuickSetCellType( 0, -1, m_iArrowIndex );
	SortBy( 0, UG_SORT_ASCENDING );

	m_iSortCol = 0;
	m_bSortedAscending = TRUE;


}
void LTPupdate::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{	
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(updn);
	UNREFERENCED_PARAMETER(*rect);
	UNREFERENCED_PARAMETER(*point);
	UNREFERENCED_PARAMETER(processed);

	if( updn == 0)
		return;

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

	int row_no=GetNumberRows();
	 for(int f=0;f<row_no;f++)
	 {
		 CString val=QuickGetText(0,f);
		 
	   if(wcscmp( val,L"")==0)
		{
			DeleteRow(f);
	    }
	 }
		
	RedrawAll();
}
int LTPupdate::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
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
case 2:
          if( cell1->GetNumber() < cell2->GetNumber())
					retVal = -1;
		   if( cell1->GetNumber() > cell2->GetNumber())
					retVal = 1;
		   	break;
        
default:
		if( CString(cell1->GetText()) == "" )
			return 1;
		else if( CString(cell2->GetText()) == "" )
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


void LTPupdate::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	if(row>-1 && col>=2)
	{
	  StartEdit();
	
	
	}

}


