#ifndef NetPosGrid_HEADER
#define NetPosGrid_HEADER
#include "OrderGrid.h"
#include "cnetposdlg.h"
#include "LogFile.h"
#include "ADD_overview.h"
#include "Netpositoin_Table.h"
class NetPosGrid:public CUGCtrl
{
public:
	CDataSource connection;
	CSession session;
	HRESULT hr;
	struct st_shorting
	 {
		wchar_t  m_symbol[200];		
	 };
	typedef TMTArray<st_shorting> st_shortingArray;

	st_shortingArray m_str_array;

	static int netpos_lock;
	static int col_click;
	static CString  Str_Total_Bal;
	static int a_d;
	static CMutex mutex_Symbol_ltp;
	struct Symbol_rate
	 {
		wchar_t  m_symbol[60];
		double	 m_rate;
	 };
	typedef TMTArray<Symbol_rate> Symbol_rateArray;
	static Symbol_rateArray m_Symbol_rateArray;
	static int first_time_update;
	static Symbol_rate m_Symbol_rate;
	 struct colsett
	 {
		 CString colname;
		 CString visible;
	 };

	typedef TMTArray<colsett> colsettingArray;

	colsettingArray colarr;

	struct st_multiplyer
	{		 
		wchar_t  m_symbol[60];
		double	 m_multiplyer;
	};
	typedef TMTArray<st_multiplyer> SymbolMultiplyer;
	static SymbolMultiplyer m_SymbolMultiplyer;
	static st_multiplyer m_st_multiplyer;

	struct st_Netposition
	{
		wchar_t  m_login[60];
		wchar_t  m_symbol[60];
		wchar_t  m_netqty[60];
		wchar_t  m_avg_rate[60];
		wchar_t  m_last_update[60];
		wchar_t  m_pl_volume[60];
		wchar_t  m_Name[60];
		wchar_t  m_Group1[60];
		wchar_t  m_Group2[60];
		wchar_t  m_Group3[60];
		wchar_t  m_Checked_Status[60];
		wchar_t  m_Checked_Time[60];
		wchar_t  m_Alloted_Limit[60];
		wchar_t  m_Remark2[60];
		wchar_t  m_Standing_Avg_rate[60];
		wchar_t  m_Sq_Balance[60];
		wchar_t  m_new_qty[60];
		wchar_t  m_pre_qty[60];
		wchar_t  m_incre_qty[60];
		wchar_t  m_last_rate[60];
		wchar_t  m_Floating_Profit[60];
		wchar_t  m_Balance[60];
	};
	typedef TMTArray<st_Netposition> NetpositionArray;

	static NetpositionArray m_NetpositionArray;

	static st_Netposition m_st_Netposition;

	static st_Netposition m_st_Netposition_Ratecal;





	
	static CMutex str_grid_mutex;

	static CMutex str_grid_filter;

	static NetpositionArray m_NetpositionArray_For_Grid;
	static st_Netposition m_st_Netposition_For_Grid;

	static NetpositionArray m_NetpositionArray_For_Grid_Final;



	struct st_Netposition_Ignore_comment
	{
		wchar_t  m_login[60];
		wchar_t  m_symbol[60];
		wchar_t  m_netqty[60];
		wchar_t  m_avg_rate[60];
		wchar_t  m_last_update[60];
		wchar_t  m_pl_volume[60];
		wchar_t  m_Name[60];
		wchar_t  m_Group1[60];
		wchar_t  m_Group2[60];
		wchar_t  m_Group3[60];
		wchar_t  m_Checked_Status[60];
		wchar_t  m_Checked_Time[60];
		wchar_t  m_Alloted_Limit[60];
		wchar_t  m_Remark2[60];
		wchar_t  m_Standing_Avg_rate[60];
		wchar_t  m_Sq_Balance[60];
		wchar_t  m_new_qty[60];
		wchar_t  m_pre_qty[60];
		wchar_t  m_incre_qty[60];
		wchar_t  m_last_rate[60];
		wchar_t  m_Floating_Profit[60];
		wchar_t  m_Balance[60];
	};
	typedef TMTArray<st_Netposition_Ignore_comment> Netposition_Ignore_comment_Array;

	static Netposition_Ignore_comment_Array m_Netposition_Ignore_comment_Array;
	









	struct  Client_Details
   {
		wchar_t  V_login[64];
		wchar_t  V_Name[200];
		wchar_t  Comment_YN[64];
		wchar_t  Ignore_YN[64];
		wchar_t  client_group[64];
		wchar_t  Client_Group1[64];
		wchar_t  Client_Group2[64];
		wchar_t  Client_Group4[64];
		double   Client_Credit;
   };    
    typedef  TMTArray<Client_Details> Client_Details_Array;
	static Client_Details_Array m_Client_Details_Array;
	static Client_Details m_Client_Details;

	static double Pre_balance;	
	static int new_client;
	static int row_position;


	struct  Client_Balance
   {
		wchar_t  V_login[64];		
		double   Total_Balance;
   };    
	typedef  TMTArray<Client_Balance> Client_Balance_Array;
	static Client_Balance_Array m_Client_Balance_Array;



	struct  login_in_m
   {
		wchar_t  V_login[64];
		
   };    
    typedef  TMTArray<login_in_m> login_in_m_Array;
	static login_in_m_Array m_login_in_m_Array;
	
	

	struct  Symbol_in_m
   {
		wchar_t  V_symbol[64];
		
   };    
    typedef  TMTArray<Symbol_in_m> Symbol_in_m_Array;
	static Symbol_in_m_Array m_Symbol_in_m_Array;


	
public:
	//CSocket m_Client;
	NetPosGrid();
	~NetPosGrid();
	CString t;

	static int int_ignoreQty;
	static int int_igrore_comment;
	static _bstr_t ignore0ty;
	static _bstr_t ignoremain;
	static _bstr_t ignorecomment;
	static _bstr_t bstr_currenttime;
	static _bstr_t cellvalue;
	static int filter_break;
	static int insertFilterFlag;
	static int check_First;
	static _bstr_t strShort;
	static _bstr_t strFilter;
	static int Grid_Rows_Count;	
	static _variant_t avarRecords;
	static int lock_data ;
	static int intRows;
	static int lock_data_fill ;
	static int data_display ;
	static int value_row_no;
	static CString m_c_login;
	static CString m_c_symbol;
	static int menu_item_cheked;
	static const char* strcol;
	static CString m_COL_VAL;
	static CString m_total;
	static COLORREF old_color;
	static COLORREF new_color;
	static CEdit	m_taxt_total;
	
	static int netpos_grid_total;
	static CUGCell cellSymbol;
	static CUGCell cellRate;
	static CUGCell cellNetqty;
	static CUGCell cellpl;
	static CUGCell cellpl_volume;
	static CUGCell cellLogin;
	
	static CUGCell pl_cell;
	static CUGCell Final_Balance_cell;

	static CUGCell temp_Cell;

	static CString text_for_update;

	static CString get_Text_fromGrid;

	static CString strSettext2;



	static CUGCell cell_pl;
	static CUGCell cell_netqty;
	static CUGCell cell_balan;

	static int sub_rows_count;


	static CString col0_val,col1_val,col2_val,col3_val,col4_val,col5_val,col6_val,col7_val,col8_val,col9_val,col10_val,col11_val,col12_val,col13_val,col14_val,col15_val,col16_val,col17_val,col18_val,col19_val,col20_val;

	//SORT
	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	CUGSortArrowType m_sortArrow;
	int m_iSortCol;
	CFont m_font;
	CUGGridInfo *m_gi;
	void filter();
	
	CUGCell cell1, cell2, cell3, cell4, cell5,cell6, cell7, cell8, cell9, cell10, cell11, cell12, cell13, cell14;		
protected:	
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
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:

	CLogFile m_logfile;

	//afx_msg void OnTimer( UINT nIDEvent );

	
	CString str[18];
	
	int	m_nSpinIndex;
	int run_check;
	
	
	void    gridFilter(int colno,int rows_count,CString col_value);
	afx_msg void OnTimer( UINT nIDEvent );
	
	
	static _variant_t result;
	void InitMenu();
	void writeData();
	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	virtual void OnSheetSetup(int sheetNumber);
	virtual int OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow);

	void colShorting( int index);

	_bstr_t get_string(CString  MainStr,CString SepStr);

	BOOLEAN  CheckvalueInArray(const CStringArray& arr,CString strval) ;
	void addItemToCombobox();
	//movement and sizing
	
	
	virtual int OnDropList(long ID,int col,long row,long msg,long param);

	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);

	void Thread_start_st_netpos_update();

	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);


	virtual  int OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);

	//mouse and key strokes
	virtual  int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	
	//editing
	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);

	
	virtual void NetPosGrid::OnGetCell(int col,long row,CUGCell *cell);

	

	//sorting
	virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);
	
	
	//void updateandinsert_netposition_rate(int row_index);
	virtual void OnTabSelected(int ID);
	
	//void updateandinsert_netposition(int row_index);

	//void update_rate_and_pl(CString symbol,double rate);

	double get_Multi(CString symbol);


	double getBalance(CString strlogin);

	//void update_rate_and_pl_byindex(CString symbol,double rate,int index);


	double getColumnSum(int col_index);

	
	//void rows_count();
	

	/*void getcellSymbol(int col,int row);
	void getcellNetqty(int col,int row);
	void getcellpl_volume(int col,int row);
	void getcellLogin(int col,int row);
	void getcell_netqty(int col,int row);
	void getcell_pl(int col,int row);
	void getcell_balan(int col,int row);*/		
	
	//void sub_grid_rows_count();
	
	//void getFinal_Balance_cell(int col,int row);

	void UpdatePre_Post_Position();
	
	
};
#endif

