#ifndef EDITABLEGRID_HEADER
#define EDITABLEGRID_HEADER
#include "ugctrl.h"
#include "OrderGrid.h"

class Editable_Grid:public CUGCtrl
{
public:
	Editable_Grid();	
	~Editable_Grid();
	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	CUGSortArrowType m_sortArrow;
	int m_iSortCol;
protected:	
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnGetCell(int col,long row,CUGCell *cell);
	virtual void OnSetup();
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
    virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);

};
#endif