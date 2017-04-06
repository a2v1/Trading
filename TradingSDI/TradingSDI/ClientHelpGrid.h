#ifndef ClientHelp_Grid
#define ClientHelp_Grid
#include "ugctrl.h"
#include "OrderGrid.h"
#include <atldbcli.h>


class ClientHelpGrid :public CUGCtrl
{
public:
	ClientHelpGrid(void);
	~ClientHelpGrid(void);


	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	CUGSortArrowType m_sortArrow;
	int m_iSortCol;
	static CString m_Selcolvalue;

	//static BOOL m_checkvalue;
  //data base initilization for delete row
	CDataSource connection;
    CSession session;	
    HRESULT hr;
public:
	virtual void OnSetup();
	//virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	void InitMenu();
	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	virtual void OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed);

    virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);

};
#endif

