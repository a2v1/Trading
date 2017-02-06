#ifndef Dealing_ALERTGRID
#define Dealing_ALERTGRID
#include "AlertGrid.h"
#include "OrderGrid.h"
class AlertGrid:public CUGCtrl
{
public:
	
	AlertGrid();
	~AlertGrid();
	static int insertFilterFlag;
	static int shorting;
	CString str[8];
	int	m_nSpinIndex;
	int run_check;
	CUGSortArrowType m_sortArrow;
	CFont m_font;
	
protected:
	void    gridFilter(int colno,int rows_count,CString col_value);	
	LRESULT OnThreadMessage(WPARAM, LPARAM);
	LRESULT OnThreadMessage_RowsNo(WPARAM, LPARAM);
	LRESULT GridRefresh(WPARAM, LPARAM);	
	LRESULT GridRowCount(WPARAM, LPARAM);	
	LRESULT RowDelete(WPARAM, LPARAM);			
private:

	int  m_iSortCol;
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer( UINT nIDEvent );
	
	DECLARE_MESSAGE_MAP()

public:
	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	void InitMenu();
	void filter();
	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	virtual void OnSheetSetup(int sheetNumber);
	
	BOOLEAN  CheckvalueInArray(const CStringArray& arr,CString strval) ;
	void addItemToCombobox();
	//movement and sizing
	
	
	virtual int OnDropList(long ID,int col,long row,long msg,long param);

	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);

	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);


	virtual  int OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);

	//mouse and key strokes
	virtual  int OnCellTypeNotify(long ID,int col,long row,long msg,long param);			
	
	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);

	//sorting
	virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);
	
	virtual void OnTabSelected(int ID);
};
#endif

