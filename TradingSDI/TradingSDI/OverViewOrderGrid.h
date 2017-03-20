#ifndef OverViewOrderGrid_HEADER
#define OverViewOrderGrid_HEADER
#include "OrderGrid.h"
class OverViewOrderGrid:public CUGCtrl
{
public:
	//CSocket m_Client;
	OverViewOrderGrid();
	~OverViewOrderGrid();
	CString t;
	static _bstr_t bstr_currenttime;
	static _bstr_t cellvalue;
	static int filter_break;
	static int thred_kill;
	static int thred_killed_ok;
	static int insertFilterFlag;
	static int check_First;

	static int OverViewOrderGrid_terminate;

	static _bstr_t strShort;
	static _bstr_t strFilter;
	static int Grid_Rows_Count;
	CWinThread* m_pThreads;
	CWinThread* m_SocketThred;
	static _variant_t avarRecords;
	static int lock_data ;
	static int intRows;
	static int lock_data_fill ;
	static int data_display ;
	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	CUGSortArrowType m_sortArrow;
	int m_iSortCol;
	CFont m_font;
	void filter();
	CUGCell cell1, cell2, cell3, cell4, cell5,cell6, cell7, cell8, cell9, cell10, cell11, cell12, cell13, cell14;
	static CString col0_val,col1_val,col2_val,col3_val,col4_val,col5_val,col6_val,col7_val,col8_val,col9_val;
	//Structure for fill data
	struct st_OverviewOrder
	{		 		
		wchar_t Symbol[100];
		wchar_t Order[100];
		wchar_t Time[100];
		wchar_t Type[50];
		wchar_t Volume[100];
		wchar_t Price[100];
		wchar_t Current_Rate[50];
		wchar_t PL[100];
		wchar_t Status[100];
		wchar_t Trade_Checked[100];
	};
	typedef TMTArray<st_OverviewOrder> st_OverviewOrder_Array;
	static st_OverviewOrder_Array m_OverviewOrder_Array_Fill;	
	static st_OverviewOrder_Array m_OverviewOrder_Array;	
	static st_OverviewOrder_Array m_OverviewOrder_Grid_array;
	static CMutex OverviewOrder_mutex;
	
protected:

	LRESULT OnThreadMessage(WPARAM, LPARAM);
	LRESULT OnThreadMessage_RowsNo(WPARAM, LPARAM);
	LRESULT GridRefresh(WPARAM, LPARAM);	
	LRESULT GridRowCount(WPARAM, LPARAM);	
	LRESULT RowDelete(WPARAM, LPARAM);	
	LRESULT DeleteThred(WPARAM, LPARAM);	
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
	CString str[10];
	int	m_nSpinIndex;
	int run_check;
	
	
	void    gridFilter(int colno,int rows_count,CString col_value);
	
	static _variant_t result;
	void InitMenu();
	
	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	virtual void OnSheetSetup(int sheetNumber);
	virtual int OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow);

	_bstr_t get_string(CString  MainStr,CString SepStr);



	
	BOOLEAN  CheckvalueInArray(const CStringArray& arr,CString strval) ;
	void addItemToCombobox();
	//movement and sizing
	
	
	virtual int OnDropList(long ID,int col,long row,long msg,long param);

	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);

	

	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);


	virtual  int OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);

	//mouse and key strokes
	virtual  int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	
	
	//editing
	
	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);

	
	//set text
	void OnGetCell(int col,long row,CUGCell *cell);

	

	//sorting
	virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);
	
	

	virtual void OnTabSelected(int ID);
	
	

	//focus rect setup
	
};
#endif

