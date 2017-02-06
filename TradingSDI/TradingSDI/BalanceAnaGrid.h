#ifndef BalanceAna_GRID
#define BalanceAna_GRID
#include "OrderGrid.h"
#include "ugctrl.h"
#include "LogFile.h"
class BalanceAnaGrid :
	public CUGCtrl
{
public:
	BalanceAnaGrid(void);
	~BalanceAnaGrid(void);
    static int insertFilterFlag;
	static int shorting;
	CString str[24];
	int	m_nSpinIndex;
	int run_check;
	CLogFile logfile;
	CUGSortArrowType m_sortArrow;
	CFont m_font;
	int  m_iSortCol;
	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	void filter();
public:
	
	//***** Over-ridable Notify Functions *****
	void InitMenu();
	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int OnDropList(long ID,int col,long row,long msg,long param);
	//mouse and key strokes
	virtual  int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	void    gridFilter(int colno,int rows_count,CString col_value);
	BOOLEAN  CheckvalueInArray(const CStringArray& arr,CString strval) ;
	void addItemToCombobox();
	virtual void OnSetup();
	virtual void OnSheetSetup(int sheetNumber);
	void GetData(_bstr_t m_login);
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);
};

#endif