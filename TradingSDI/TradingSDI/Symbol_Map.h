#pragma once
#include "ugctrl.h"
#include "OrderGrid.h"
class Symbol_Map :public CUGCtrl
{
public:
	Symbol_Map(void);
	~Symbol_Map(void);

	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	CUGSortArrowType m_sortArrow;
	int m_iSortCol;
    DECLARE_MESSAGE_MAP()

	//virtual void OnGetCell(int col,long row,CUGCell *cell);
	virtual void OnSetup();
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	virtual void OnKeyDown(UINT *vcKey,BOOL processed);
	//virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
    //sorting
	virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);
};

