#include "stdafx.h"
#include "Symbol_Map.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
BEGIN_MESSAGE_MAP(Symbol_Map,CUGCtrl)
	
END_MESSAGE_MAP()

Symbol_Map::Symbol_Map(void)
{
}


Symbol_Map::~Symbol_Map(void)
{
}

void Symbol_Map:: OnSetup()
{

	SetNumberCols(1);
	SetNumberRows(20);


	//soritng
	m_iArrowIndex = AddCellType( &m_sortArrow );

	//SetCurrentCellMode( 2 );


	QuickSetCellType( 0, -1, m_iArrowIndex );
	SortBy( 0, UG_SORT_ASCENDING );

	m_iSortCol = 0;
	m_bSortedAscending = TRUE;

}
void Symbol_Map:: OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	StartEdit();

}

void Symbol_Map::OnKeyDown(UINT *vcKey,BOOL processed)
{
	
		processed=false;
	StartEdit();
}

int Symbol_Map::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
{


if( flags & UG_SORT_DESCENDING )
{
	CUGCell *ptr = cell1;
	cell1 = cell2;
	cell2 = ptr;
}

int retVal = 0;
CString szComp1=L"";
CString szComp2=L"";
 switch ( m_iSortCol )
 {
   case 0:

     	szComp1=cell1->GetText();
		szComp2=cell2->GetText();

		if(!szComp1.IsEmpty() && !szComp2.IsEmpty())
		{
		  retVal=szComp1.Compare(szComp2);
		}
	
     default:
	    break;
   }
  return retVal;
}


void Symbol_Map::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
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