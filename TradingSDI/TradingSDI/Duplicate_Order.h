#ifndef DUPLICATEORDER
#define DUPLICATEORDER
#include "OrderGrid.h"
class Duplicate_Order:public CUGCtrl
{
public:
int short_click;
	struct st_Comment_Change
	{
		wchar_t  time[60];
		wchar_t  order[60];
		wchar_t  deal[60];
		wchar_t  symbol[60];
		wchar_t  action[60];
		wchar_t  volume[60];
		wchar_t  price[60];
		wchar_t  comment[60];
		wchar_t  OurComment[60];
		wchar_t  login[60];
		wchar_t  Change_YN[60];
		wchar_t  Opposite_Deal[50];
	};

	typedef TMTArray<st_Comment_Change> Comment_ChangeArray;
	//CSocket m_Client;
	Duplicate_Order();
	~Duplicate_Order();
	CString t;
	static _bstr_t bstr_currenttime;

	

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
	static int thred_killed_ok;
	static int value_row_no;
	
	static CString m_c_symbol;

	static st_Comment_Change m_st_Comment_Change;
	static Comment_ChangeArray m_Comment_ChangeArray;

	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	CUGSortArrowType m_sortArrow;
	int m_iSortCol;
	CFont m_font;
	void filter();
	CUGCell cell1, cell2, cell3, cell4, cell5,cell6, cell7, cell8, cell9, cell10, cell11, cell12, cell13, cell14;

	CUGButtonType		m_button;
	int					m_nButtonIndex;
	
protected:

	LRESULT OnThreadMessage(WPARAM, LPARAM);
	LRESULT OnThreadMessage_RowsNo(WPARAM, LPARAM);
	LRESULT GridRefresh(WPARAM, LPARAM);	
	LRESULT GridRowCount(WPARAM, LPARAM);	
	LRESULT RowDelete(WPARAM, LPARAM);	
	LRESULT CreatePushButton(WPARAM, LPARAM);
	LRESULT DeleteThred(WPARAM, LPARAM);	
	LRESULT rownofind(WPARAM, LPARAM);
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
	
	int OnPushButton(long ID,int col,long row,long msg,long param);
	int OnCheckbox(long ID,int col,long row,long msg,long param);
	
	void Selected_commentChange();
	CString str[14];
	
	int	m_nSpinIndex;
	int run_check;
	
	
	void    gridFilter(int colno,int rows_count,CString col_value);
	
	static _variant_t result;
	void InitMenu();
	
	
	
	
	//virtual void OnCB_DClicked(RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnSetup();
	virtual void OnSheetSetup(int sheetNumber);

	_bstr_t get_string(CString  MainStr,CString SepStr);

	boolean CheckvalueInArray(CString dealno);

	
	BOOLEAN  CheckvalueInArray(const CStringArray& arr,CString strval) ;
	void addItemToCombobox();
	//movement and sizing
	
	
	virtual int OnDropList(long ID,int col,long row,long msg,long param);

	
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	virtual int OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow);


	virtual  int OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);

	//mouse and key strokes
	virtual  int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	
	
	//editing
	
	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);

	
	void change_comment_dealwise(CString login,CString dealno,CString newcomment,CString precomment);

	

	//sorting
	virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);
	
	

	virtual void OnTabSelected(int ID);
	
	

	//focus rect setup
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
#endif

