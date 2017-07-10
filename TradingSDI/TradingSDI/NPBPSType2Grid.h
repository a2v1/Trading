#pragma once
#ifndef NPBPSType2_HEADER
#define NPBPSType_HEADER
#include "OrderGrid.h"
#include "ugctrl.h"
class CNPBPSType2Grid :public CUGCtrl
{

private:
	DECLARE_MESSAGE_MAP();
public:
	CNPBPSType2Grid(void);
	~CNPBPSType2Grid(void);
public:
	CWinThread* m_pThreads;
	CString str[18];

	int col_click,a_d;

	struct st_Dealing
	{		 		
		wchar_t Section[100];
		wchar_t Login[100];
		double Order;
		wchar_t Order_In_Time[50];
		int Deal;
		wchar_t Symbol[100];
		wchar_t Type1[100];
		double Volume;		
		double Price;
		wchar_t Comment[100];
		wchar_t Status[100];
		wchar_t Type[100];
		wchar_t SubType[100];
		wchar_t Trade_Happen_Time[100];
		wchar_t Open[100];
		wchar_t High[100];
		wchar_t Low[100];
		wchar_t Close[100];
	};
	typedef TMTArray<st_Dealing> st_Dealing_Array;
	static st_Dealing_Array m_st_Dealing_Array;	
	static st_Dealing_Array m_st_Dealing_Array_fill;
	static st_Dealing_Array m_st_Dealing_Grid_array;	
	static CMutex dealing_mutex;
		

	struct st_shorting
	 {
		wchar_t  m_symbol[200];		
	 };
	typedef TMTArray<st_shorting> st_shortingArray;

	st_shortingArray m_str_array;

	int	m_nSpinIndex;
	static CString col0_val,col1_val,col2_val,col3_val,col4_val,col5_val,col6_val,col7_val,col8_val,col9_val,col10_val,col11_val,col12_val,col13_val,col14_val,col15_val,col16_val,col17_val;
	
	static  int insertFilterFlag;
	static  int Data_Update;
public:
	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	CUGSortArrowType m_sortArrow;
	int m_iSortCol;
	CFont m_font;
	CUGGridInfo *m_gi;
	void OnSheetSetup(int sheetNumber);	
	virtual void OnSetup();
	void OnTimer(UINT nIDEvent);
	void OnGetCell(int col,long row,CUGCell *cell);
	void OnMenuCommand(int col,long row,int section,int item);
	void filter();
	void addItemToCombobox();
	BOOLEAN  CheckvalueInArray(const CStringArray& arr,CString strval) ;
	void colShorting( int index);
	void data_ThreadStart();
	void thread_destoy();
	void InitMenu();
	void gridFilter(int colno,int rows_count,CString col_value);
	void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	virtual int OnDropList(long ID,int col,long row,long msg,long param);
	virtual int OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	//mouse and key strokes
	virtual  int OnCellTypeNotify(long ID,int col,long row,long msg,long param);

};
#endif