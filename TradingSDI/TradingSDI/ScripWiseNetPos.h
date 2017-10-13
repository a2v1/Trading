#ifndef SCRIPWISENETPOS
#define SCRIPWISENETPOS
#include "OrderGrid.h"
class ScripWiseNetPos:public CUGCtrl
{
public:
	static int g_ud;
	static int g_c;
	static int g_check;
	static int g_check_AND_BREAK;
	static int Data_Update;
	//CSocket m_Client;
	ScripWiseNetPos();
	~ScripWiseNetPos();
	CString t;
	static _bstr_t bstr_currenttime;
	static _bstr_t cellvalue;
	static int filter_break;
	static int insertFilterFlag;
	static int check_First;
	static _bstr_t strShort;
	static _bstr_t strFilter;
	static int Grid_Rows_Count;
	CWinThread* m_pThreads;	
	static _variant_t avarRecords;
	static int lock_data ;
	static int intRows;
	static int lock_data_fill ;
	static int data_display ;
	static int value_row_no;
	static CString m_c_symbol;
	static int  row_count;
	static CString m_COL_VAL;		
	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	CUGSortArrowType m_sortArrow;
	int m_iSortCol;
	CFont m_font;
	void filter();
	CUGCell cell1, cell2, cell3, cell4, cell5,cell6, cell7, cell8, cell9, cell10, cell11, cell12, cell13, cell14;



	struct st_scripwisenetpos
	{	
		wchar_t  m_Symnol[31];
		double   m_NetQty;
		double   m_Average;
		double   m_LastRate;
		double   m_PL;
	};
	typedef TMTArray<st_scripwisenetpos> scripwisenetpos_array;
	static scripwisenetpos_array m_scripwisenetpos_Array;	
	static scripwisenetpos_array m_scripwisenetpos_Array_data;
	static scripwisenetpos_array m_scripwisenetpos_grid_array;

	static CMutex m_mutex_scripnetpos;



	
protected:

	LRESULT OnThreadMessage(WPARAM, LPARAM);
	LRESULT OnThreadMessage_RowsNo(WPARAM, LPARAM);
	LRESULT GridRefresh(WPARAM, LPARAM);	
	LRESULT GridRowCount(WPARAM, LPARAM);	
	LRESULT RowDelete(WPARAM, LPARAM);
	LRESULT rownofind(WPARAM, LPARAM);
	LRESULT gridshorting(WPARAM wParam, LPARAM lParam);
	LRESULT getcellval(WPARAM wParam, LPARAM lParam);
	int c1_click;
	int c2_click;
	int c3_click;
	int c4_click;
	int c5_click;
	int c6_click;
	int c7_click;
	int c8_click;
	int c9_click;
	int c10_click;
	int c11_click;
	int c12_click;
	int c13_click;
	int c14_click;
	static long rgIndices[2];	
	//ArrowCellType	m_celllArrow;
	int				m_nArrowCellIndx;

private:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug)
	// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer( UINT nIDEvent );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString str[5];
	
	int	m_nSpinIndex;
	int run_check;
	
	void Thread_start_scrip_wise();
	void thread_destoy();


	void gridFilter(int colno,int rows_count,CString col_value);
	
	static CString total_result;
	void InitMenu();


	
	
	//virtual void OnCB_DClicked(RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnSetup();
	virtual void OnSheetSetup(int sheetNumber);

	_bstr_t get_string(CString  MainStr,CString SepStr);

	

	
	BOOLEAN  CheckvalueInArray(const CStringArray& arr,CString strval) ;
	void addItemToCombobox();
	//movement and sizing
	
	
	virtual int OnDropList(long ID,int col,long row,long msg,long param);

	
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	virtual void OnGetCell(int col,long row,CUGCell *cell);
	


	virtual  int OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);

	//mouse and key strokes
	virtual  int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);
//sorting
	virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);
	virtual void OnTabSelected(int ID);
	//focus rect setup
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
#endif

