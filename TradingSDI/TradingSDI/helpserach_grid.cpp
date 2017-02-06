#include "stdafx.h"
#include "helpserach_grid.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
BEGIN_MESSAGE_MAP(helpserach_grid,CUGCtrl)
	
END_MESSAGE_MAP()

helpserach_grid::helpserach_grid(void)
{
}


helpserach_grid::~helpserach_grid(void)
{
}

void helpserach_grid:: OnSetup()
{
	
	SetNumberCols(2);
	SetNumberRows(20);



}
void helpserach_grid:: OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{


	StartEdit();

}