#pragma once
#include "ugctrl.h"
#include "OrderGrid.h"
class definemargin_grid :public CUGCtrl
{
public:
	definemargin_grid(void);
	~definemargin_grid(void);
	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	CUGSortArrowType m_sortArrow;
	int m_iSortCol;
	static int sorting_flag;
protected:
	 DECLARE_MESSAGE_MAP()

public:	
	virtual void OnSetup();
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
		//sorting
	virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

