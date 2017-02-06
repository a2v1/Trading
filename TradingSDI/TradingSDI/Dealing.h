#ifndef Dealing_HEADER
#define Dealing_HEADER
#include "OrderGrid.h"
class Dealing:public CUGCtrl//,public IMTDealSink
{
private:
	DECLARE_MESSAGE_MAP();
public:	
	
	CString str[13];
	struct st_Dealing
	{	
		wchar_t LOG_TIME[20];
		UINT64 Time; 
		wchar_t Login[20];  
		UINT64 Deal;
		UINT64 Order;
		wchar_t Order_type[100];
		wchar_t Symbol[100];
		wchar_t Type[30];
		double Volume;
		double Price;
		wchar_t Comment[30];
		wchar_t Entrytype[20];
		wchar_t Current_Status[200];
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



	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	CUGSortArrowType m_sortArrow;
	int m_iSortCol;
	CFont m_font;
	CUGGridInfo *m_gi;
	//CSocket m_Client;
	Dealing();
	~Dealing();
	int	m_nSpinIndex;
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
	void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
};
#endif

