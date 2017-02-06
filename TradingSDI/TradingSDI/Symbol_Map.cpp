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