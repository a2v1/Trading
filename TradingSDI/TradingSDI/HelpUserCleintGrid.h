#pragma once
#include "ugctrl.h"
#include "OrderGrid.h"
#include "UserClientTable.h"
class HelpUserCleintGrid :public CUGCtrl
{
public:
	HelpUserCleintGrid(void);
	~HelpUserCleintGrid(void);

	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	CUGSortArrowType m_sortArrow;
	int m_iSortCol;	
  //data base initilization for delete row
	CDataSource connection;
    CSession session;	
    HRESULT hr;
public:
	virtual void OnSetup();
	void DisplayData();
	//virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	//void InitMenu();
	//void delete_row();
	////menu notifications
	//virtual void OnMenuCommand(int col,long row,int section,int item);
	//virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	//virtual void OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed);

 //   virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);
};

