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
	static int m_selectedclient;
	//Structure for fill data
	struct st_grid_anlysis
	{		 		
		wchar_t m_deal[100];
		wchar_t m_login[100];
		wchar_t m_symbol[50];
		wchar_t m_time[100];
		wchar_t m_EntryVolume[100];
		wchar_t m_Entryprice[100];
	};
	typedef TMTArray<st_grid_anlysis> st_grid_anlysis_array;
	static st_grid_anlysis m_st_grid_anlysis;
	static st_grid_anlysis_array m_st_grid_anlysis_Array_Fill;	
    static st_grid_anlysis_array m_st_grid_anlysis_Grid_array;
	

public:
	//***** Over-ridable Notify Functions *****
	void RefreshGrid();
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
	
	//set text
	void OnGetCell(int col,long row,CUGCell *cell);
	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);

};
#endif

