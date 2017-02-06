#pragma once
#include "ugctrl.h"
#include "LTPTable.h"
#include "OrderGrid.h"
class LTPupdate :public CUGCtrl
{
public:
	LTPupdate(void);
	~LTPupdate(void);
	static _bstr_t cellvalue;
	static int data_display; 
	static int Grid_Rows_Count;
	//SORT
	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	CUGSortArrowType m_sortArrow;
	int m_iSortCol;
	CFont m_font;
	virtual void OnSetup();
    void GetData();
    virtual void  OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);

private:
    DECLARE_MESSAGE_MAP();
      


	
};

