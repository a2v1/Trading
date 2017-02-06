#ifndef PosEntryAna_GRID
#define PosEntryAna_GRID
#include "OrderGrid.h"
#include "ugctrl.h"
#include "LogFile.h"
class PosEntryAna :public CUGCtrl
{
public:
	PosEntryAna(void);
  	~PosEntryAna(void);
    static int insertFilterFlag;
	static int shorting;
	CString str[6];
	int	m_nSpinIndex;
	int run_check;
	CLogFile m_logfile;
	CUGSortArrowType m_sortArrow;
	CFont m_font;
	int  m_iSortCol;
	BOOL m_bSortedAscending;
	int m_iArrowIndex;
public:
	//***** Over-ridable Notify Functions *****
	void InitMenu();
	void filter();
	void    gridFilter(int colno,int rows_count,CString col_value);
	BOOLEAN  CheckvalueInArray(const CStringArray& arr,CString strval) ;
	void addItemToCombobox();
	//movement and sizing
	virtual int OnDropList(long ID,int col,long row,long msg,long param);
	virtual void OnSetup();
	virtual void OnSheetSetup(int sheetNumber);
	void Getdata(_bstr_t m_login);
	//mouse and key strokes
	virtual  int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	
	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);
};
#endif

