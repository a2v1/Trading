#pragma once
#include "ugctrl.h"
#include "NetPosGrid.h"
class Columnsetting_grid :public CUGCtrl
{
public:
	Columnsetting_grid(void);
	~Columnsetting_grid(void);
	//check uncheck
	static int column_hide_checked;
	static int column_show_unchecked;
	static	CList<int, int> check_item;
	

	NetPosGrid objNetPosGrid;
protected:
	  DECLARE_MESSAGE_MAP()
public:
	//virtual void OnGetCell(int col,long row,CUGCell *cell);
	virtual void OnSetup();
	//virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	virtual void OnGetCell( int iCol, long lRow, CUGCell* pCell );
	//mouse and key strokes
	virtual  int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	
	
	int OnCheckbox(long ID,int col,long row,long msg,long param);
};

