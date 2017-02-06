#include "stdafx.h"
#include "Columnsetting_grid.h"
#include "NetPosGrid.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(Columnsetting_grid,CUGCtrl)
	
END_MESSAGE_MAP()

int Columnsetting_grid::column_hide_checked=1;
int Columnsetting_grid::column_show_unchecked=0;
CList<int,int> Columnsetting_grid::check_item;


Columnsetting_grid::Columnsetting_grid(void)
{
}


Columnsetting_grid::~Columnsetting_grid(void)
{
}
int Columnsetting_grid::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{

	
	if(ID == UGCT_CHECKBOX){
		return OnCheckbox(ID, col, row, msg, param);
	}
}
void Columnsetting_grid::OnSetup()
{

	SetNumberCols(2);

	SetNumberRows(18);
	

	CUGCell cell;

		LPTSTR Columnname[ 18 ] = { _T( "Login" ), _T( "Name" ), _T( "Symbol" ), _T( "Pre_NetQty" ), _T( "Diff_NetQty" ),
		_T( "NetQty" ), _T( "Average" ), _T( "LastRate" ), _T( "PL" ), _T( "Balance" ), _T( "LastUpdate" ), _T( "Group1" ),
		_T( "Group2" ), _T( "Group3" ), _T( "Checked Status" ), _T( "Checked Time" ), _T( "Alloted Limit" ), _T( "Remark2" )};
		
	GetCell( 0, 0, &cell );
	int j;
	for( j = 0 ; j < GetNumberRows() ; j++ )
	{
		cell.SetText( Columnname[j] );
		SetCell( 0, j, &cell );
	}



}
void Columnsetting_grid::OnGetCell( int iCol, long lRow, CUGCell* pCell )
{

	if( lRow >= 0 && iCol >= 1 )
	{
			
		pCell->SetCellType(UGCT_CHECKBOX);
		pCell->SetCellTypeEx(UGCT_CHECKBOXCHECKMARK);
		pCell->SetAlignment(UG_ALIGNCENTER);
      pCell->SetBackColor( RGB( 255, 255, 192 ) );
	}
	

}

int Columnsetting_grid::OnCheckbox(long ID,int col,long row,long msg,long param)
{	
	check_item.AddTail(row);
	
	return TRUE;
}