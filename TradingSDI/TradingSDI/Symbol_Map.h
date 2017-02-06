#pragma once
#include "ugctrl.h"
class Symbol_Map :public CUGCtrl
{
public:
	Symbol_Map(void);
	~Symbol_Map(void);

    DECLARE_MESSAGE_MAP()

	//virtual void OnGetCell(int col,long row,CUGCell *cell);
	virtual void OnSetup();
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	virtual void OnKeyDown(UINT *vcKey,BOOL processed);
};

