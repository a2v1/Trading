#pragma once
#ifndef PASSEDBYMNGR_HEDDER
#define PASSEDBYMNGR_HEDDER
#include "OrderGrid.h"
#include "ugctrl.h"

class CPassedBYMngr :public CUGCtrl
{
private:
	DECLARE_MESSAGE_MAP();
public:
	CPassedBYMngr(void);
	~CPassedBYMngr(void);
public:
	CWinThread* m_pThreads;
	CString str[13];

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
	};
	typedef TMTArray<st_Dealing> st_Dealing_Array;
	static st_Dealing_Array m_st_Dealing_Array;	
	static st_Dealing_Array m_st_Dealing_Grid_array;	
	static CMutex dealing_mutex;
		

	struct st_shorting
	 {
		wchar_t  m_symbol[200];		
	 };
	typedef TMTArray<st_shorting> st_shortingArray;

	st_shortingArray m_str_array;

	static  int insertFilterFlag;

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
	void InitMenu();
	void gridFilter(int colno,int rows_count,CString col_value);
	void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
};
#endif