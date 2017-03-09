/***************************************************
****************************************************
Skeleton Class for a Derived MyCug
****************************************************
****************************************************/

#include "stdafx.h"
//#include "uglibsel.h"		// Include the file which will select which library file to use

#include "resource.h"
#include "Editable_Grid.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(Editable_Grid,CUGCtrl)
	
END_MESSAGE_MAP()



Editable_Grid::Editable_Grid()
{
	
	UGXPThemes::UseThemes(false);

}


Editable_Grid::~Editable_Grid()
{
	//UGXPThemes::CleanUp();
}

//cell.SetParam(CELLTYPE_IS_EDITABLE);
void Editable_Grid::OnSetup()
{
	SetNumberCols(2);
	
		//soritng
	m_iArrowIndex = AddCellType( &m_sortArrow );

	SetCurrentCellMode( 2 );

	UseHints( TRUE );

	SetSH_Width( 0 );

	QuickSetCellType( 0, -1, m_iArrowIndex );
	SortBy( 0, UG_SORT_ASCENDING );

	m_iSortCol = 0;
	m_bSortedAscending = TRUE;


	EnableMenu(TRUE);
}
void Editable_Grid::OnGetCell(int col,long row,CUGCell *cell)
{
	
}
void Editable_Grid::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	StartEdit();
}	
			 


int Editable_Grid::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
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
		if( cell1->GetNumber() > cell2->GetNumber())
			retVal = 1;

		break;	
	
  case 1:
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

void Editable_Grid::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
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
	
	RedrawAll();
}

