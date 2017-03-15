#include "stdafx.h"
#include "definemargin_grid.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
BEGIN_MESSAGE_MAP(definemargin_grid,CUGCtrl)
	
END_MESSAGE_MAP()

int definemargin_grid::sorting_flag=0;

definemargin_grid::definemargin_grid(void)
{
}


definemargin_grid::~definemargin_grid(void)
{
}

void definemargin_grid:: OnSetup()
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


}
void definemargin_grid:: OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{

   StartEdit();

}
int definemargin_grid::OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags)
{
	if( flags & UG_SORT_DESCENDING )
	{
		CUGCell *ptr = cell1;
		cell1 = cell2;
		cell2 = ptr;
	}

int retVal = 0;
// initialize variables for numeric check and text change
double num1, num2;
CString szComp1=L"";
CString szComp2=L"";

 switch(m_iSortCol)
 {
	  
	  case 0:
			szComp1=cell1->GetText();
			szComp2=cell2->GetText();

			if(!szComp1.IsEmpty() && !szComp2.IsEmpty())
			{
				retVal=szComp1.CompareNoCase(szComp2);
			}
			break;

	  case 1:
			num1 = cell1->GetNumber();
			num2 = cell2->GetNumber();

			if(num1!=0 && num2!=0)
			{
				if(num1 < num2)
					retVal = -1;
				if(num1 > num2)
					retVal = 1;
			}
			break;
	  default:
			retVal = _tcscmp( cell1->GetText( ), cell2->GetText());
	}
  return retVal;
}

void definemargin_grid::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
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

BOOL definemargin_grid::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	int x=(int)pMsg->wParam;

	if(pMsg->message==WM_KEYDOWN )
	{

	if(x==70 && GetKeyState( VK_CONTROL) < 0)
		{
		
		
			/*filter();*/

			return TRUE;
		
		}

		
		
	}
	return CUGCtrl::PreTranslateMessage(pMsg);
}

//void definemargin_grid::InitMenu()
//{
//	CMenu submenu;
//	CMenu * menu = GetPopupMenu();
//	
//	EnableMenu(TRUE);
//	
//	
//	AddMenuItem( 2000, _T( "Filter" ) );
//	
//		
//}
