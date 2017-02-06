#pragma once
#include "ugctrl.h"
class helpserach_grid :public CUGCtrl
{
public:
	helpserach_grid(void);
	~helpserach_grid(void);

	 DECLARE_MESSAGE_MAP()

	
	virtual void OnSetup();
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	//virtual void OnKeyDown(UINT *vcKey,BOOL processed);



};

