#include "ugctrl.h"
#include "UGCTsarw.h"	// Added by ClassView
#include "OrderGridFilter.h"
#include "ugctprog.h"
#include "ugctspin.h"
#include "ugctbutn.h"
#include "ugctsarw.h"
#include "ugctelps.h"
#include "ugctrado.h"
#include "ugctmfnt.h"
#include "ugctpie.h"
#include "ugctafnt.h"
#include "ugctexpand.h"
#include "ugctpro1.h"
#include "ugctsldr.h"
#include "ugctdtp.h"
#include "ugctmarquee.h"
#include "UGCTNote.h"
#include "UGCTLabeled.h"
#include "UIThread.h"
#ifndef _FindGrid_H_
#define _FindGrid_H_
#define	MY_COLOR_BACK			RGB(0,0,60)
#define	MY_COLOR_TEXT			RGB(192,192,192)
#define	MY_COLOR_LO_TEXT		RGB(255,0,0)
#define	MY_COLOR_HI_TEXT		RGB(0,255,0)
#define	MY_COLOR_CHANGED_TEXT	RGB(0,0,0)
#define	MY_COLOR_CHANGED_BACK	RGB(0,255,255)
#define	MY_COLOR_WHITE			RGB(255,255,255)
#define CELLTYPE_IS_EDITABLE	13
class ArrowCellType: public CUGCellType 
{    
protected:
	CBitmap	m_bmpUp;
	CBitmap	m_bmpDown;	
public: 			
	ArrowCellType() 
	{
		m_bmpUp.LoadBitmap(IDB_BITMAP_ARROW_UP);
		m_bmpDown.LoadBitmap(IDB_BITMAP_ARROW_DOWN);
	} 
	~ArrowCellType() 
	{
		m_bmpUp.DeleteObject();
		m_bmpDown.DeleteObject();
	}
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell, int selected,int current)
	{
		// Call base class drawing
		CUGCellType::OnDraw(dc, rect, col, row, cell, selected, current);

		// Draw arrow bitmap
		CBitmap *pBmp = (cell->GetParam()) ? &m_bmpDown : &m_bmpUp;
		DrawTransparentBitmap(dc->m_hDC, (HBITMAP)*pBmp, (short)(rect->left + 1), (short)(rect->top + ((rect->bottom - rect->top) - 8)/2), RGB(0,0,0));
	}
	void DrawTransparentBitmap(HDC hdc, HBITMAP hBitmap, short xStart,short yStart, COLORREF cTransparentColor)
	{
	   BITMAP     bm;
	   COLORREF   cColor;
	   HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
	   HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
	   HDC        hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
	   POINT      ptSize;

	   hdcTemp = CreateCompatibleDC(hdc);
	   SelectObject(hdcTemp, hBitmap);   // Select the bitmap

	   GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
	   ptSize.x = bm.bmWidth;            // Get width of bitmap
	   ptSize.y = bm.bmHeight;           // Get height of bitmap
	   DPtoLP(hdcTemp, &ptSize, 1);      // Convert from device

										 // to logical points

	   // Create some DCs to hold temporary data.
	   hdcBack   = CreateCompatibleDC(hdc);
	   hdcObject = CreateCompatibleDC(hdc);
	   hdcMem    = CreateCompatibleDC(hdc);
	   hdcSave   = CreateCompatibleDC(hdc);

	   // Create a bitmap for each DC. DCs are required for a number of
	   // GDI functions.

	   // Monochrome DC
	   bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

	   // Monochrome DC
	   bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

	   bmAndMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	   bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

	   // Each DC must select a bitmap object to store pixel data.
	   bmBackOld   = (HBITMAP)SelectObject(hdcBack, bmAndBack);
	   bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
	   bmMemOld    = (HBITMAP)SelectObject(hdcMem, bmAndMem);
	   bmSaveOld   = (HBITMAP)SelectObject(hdcSave, bmSave);

	   // Set proper mapping mode.
	   SetMapMode(hdcTemp, GetMapMode(hdc));

	   // Save the bitmap sent here, because it will be overwritten.
	   BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	   // Set the background color of the source DC to the color.
	   // contained in the parts of the bitmap that should be transparent
	   cColor = SetBkColor(hdcTemp, cTransparentColor);

	   // Create the object mask for the bitmap by performing a BitBlt
	   // from the source bitmap to a monochrome bitmap.
	   BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0,
			  SRCCOPY);

	   // Set the background color of the source DC back to the original
	   // color.
	   SetBkColor(hdcTemp, cColor);

	   // Create the inverse of the object mask.
	   BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
			  NOTSRCCOPY);

	   // Copy the background of the main DC to the destination.
	   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, xStart, yStart,
			  SRCCOPY);

	   // Mask out the places where the bitmap will be placed.
	   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

	   // Mask out the transparent colored pixels on the bitmap.
	   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

	   // XOR the bitmap with the background on the destination DC.
	   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);

	   // Copy the destination to the screen.
	   BitBlt(hdc, xStart, yStart, ptSize.x, ptSize.y, hdcMem, 0, 0,
			  SRCCOPY);

	   // Place the original bitmap back into the bitmap sent here.
	   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

	   // Delete the memory bitmaps.
	   DeleteObject(SelectObject(hdcBack, bmBackOld));
	   DeleteObject(SelectObject(hdcObject, bmObjectOld));
	   DeleteObject(SelectObject(hdcMem, bmMemOld));
	   DeleteObject(SelectObject(hdcSave, bmSaveOld));

	   // Delete the memory DCs.
	   DeleteDC(hdcMem);
	   DeleteDC(hdcBack);
	   DeleteDC(hdcObject);
	   DeleteDC(hdcSave);
	   DeleteDC(hdcTemp);
   } 
};

class OrderGrid:public CUGCtrl
{
public:
	void thread_destoy();

	struct st_Order_Update
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
		wchar_t  TYPE[60];
		wchar_t  subtype[60];
		wchar_t  orderno_2[60];
		wchar_t  trade_time[60];
	};	
	struct St_Client_balance
	{		
		wchar_t  Login[60];
		double   balance;		
	};	

	struct St_Client
	{		
		wchar_t  Login[60];		
	};	
	 
	static int col_click;
	static int a_d;
	typedef TMTArray<St_Client> m_client_Array;

	typedef TMTArray<St_Client_balance> St_Client_balanceArray;
	

	typedef TMTArray<st_Order_Update> st_Order_UpdateArray;

	static st_Order_UpdateArray m_st_Order_UpdateArray;

	static CMutex m_order_mutex;

	static st_Order_UpdateArray m_st_Order_GridArray;

	static st_Order_Update m_st_Order_Update;

	static St_Client_balance m_St_Client_balance;
	
	static St_Client_balanceArray m_St_Client_balanceArray;

	static m_client_Array m_client_list;

	static St_Client m_St_Client_1;
	static St_Client m_St_Client_2;
	static St_Client m_St_Client_3;
	static St_Client m_St_Client_4;
	static St_Client m_St_Client_5;

	//CSocket m_Client;
	OrderGrid();
	~OrderGrid();
	static _bstr_t cellvalue;
	static int filter_break;
	static int insertFilterFlag;
	static int check_First;
	static _bstr_t strShort;
	static _bstr_t strFilter;
	static int Grid_Rows_Count;
	CWinThread* m_pThreads;
	CWinThread* m_SocketThred;
	static _variant_t avarRecords;
	static int lock_data ;
	static int intRows;
	static int lock_data_fill ;

	static int first_time_data_Received_YN;

	static int Data_Update;


	static CString str_text_Update_Final_Balance;
	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	CUGSortArrowType m_sortArrow;
	int m_iSortCol;
	CFont m_font;
	void filter();
	CUGCell cell1, cell2, cell3, cell4, cell5,cell6, cell7, cell8, cell9, cell10, cell11, cell12, cell13, cell14;
	static CString str_symbol_for_rate;
	static double  dbl_rate;

	static int grid_rows_count;
	static CString ordergrid_text;
	static st_Order_Update m_cc_th;
	
	static CSocket m_Client;

	static CString str_orderGrid_settext;
	
	static CString str_orderGrid_gettext_2;

	static CMutex mutex_client_list;
	static CMutex mutex_client_balance;

protected:

	LRESULT OnThreadMessage(WPARAM, LPARAM);
	LRESULT OnThreadMessage_RowsNo(WPARAM, LPARAM);
	LRESULT GridRefresh(WPARAM, LPARAM);	
	LRESULT GridRowCount(WPARAM, LPARAM);	
	LRESULT RowDelete(WPARAM, LPARAM);	
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
	
	
	int					m_nButtonIndex;
	CUGButtonType		m_button;
	CString str[16];
	
	int	m_nSpinIndex;
	int run_check;
	
	void    GetOrders();
	
	static _variant_t result;
	void InitMenu();
	
	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	virtual void OnSheetSetup(int sheetNumber);

	static CString col0_val,col1_val,col2_val,col3_val,col4_val,col5_val,col6_val,col7_val,col8_val,col9_val,col10_val,col11_val,col12_val,col13_val,col14_val,col15_val;

	
	BOOLEAN  CheckvalueInArray(const CStringArray& arr,CString strval) ;
	void addItemToCombobox();
	//movement and sizing
	virtual int OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow);
	
	virtual int OnDropList(long ID,int col,long row,long msg,long param);

	virtual void OrderGrid::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);

	int OnCheckbox(long ID,int col,long row,long msg,long param);

	virtual void OrderGrid::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);


	virtual  int OrderGrid::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);

	virtual   void OnGetCell(int col,long row,CUGCell *cell);

	//mouse and key strokes
	virtual  int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	
	
	//editing
	
	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);

	

	boolean CheckvalueInArray(CString dealno);
	

	int OnPushButton(long ID,int col,long row,long msg,long param);

	//sorting
	virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);
	
	

	virtual void OnTabSelected(int ID);
	
	

	
	//LRESULT DisplayData_Netposition_UpdateAndInsert(WPARAM wParam, LPARAM lParam);
	LRESULT DisplayData_Netposition_UpdateAndInsert_rate(WPARAM wParam, LPARAM lParam);

	
	

	

/*	LRESULT getcellSymbol(WPARAM wParam, LPARAM lParam);
	LRESULT getcellNetqty(WPARAM wParam, LPARAM lParam);
	LRESULT getcellpl_volume(WPARAM wParam, LPARAM lParam);
	LRESULT getcellLogin(WPARAM wParam, LPARAM lParam);
	LRESULT getcell_netqty(WPARAM wParam, LPARAM lParam);
	LRESULT getcell_pl(WPARAM wParam, LPARAM lParam);
	LRESULT getcell_balan(WPARAM wParam, LPARAM lParam)*/;		
	//LRESULT SetTextValue(WPARAM wParam, LPARAM lParam);	

	//LRESULT redraw_ALL(WPARAM wParam, LPARAM lParam);		
	//LRESULT GetTextValue(WPARAM wParam, LPARAM lParam);	
	//LRESULT sub_grid_rows_count(WPARAM wParam, LPARAM lParam);
	//LRESULT getpl_cell(WPARAM wParam, LPARAM lParam);
	//LRESULT Final_Balance_cell(WPARAM wParam, LPARAM lParam);
	//LRESULT gettemp_cell(WPARAM wParam, LPARAM lParam);
	LRESULT Get_order_grid_rowcount(WPARAM wParam, LPARAM lParam);
	LRESULT Get_order_grid_text(WPARAM wParam, LPARAM lParam);
	LRESULT OrderGrid_rowDelete(WPARAM wParam, LPARAM lParam);
	LRESULT Set_order_grid_text(WPARAM wParam, LPARAM lParam);
	LRESULT Ordergrid_cellFormat(WPARAM wParam, LPARAM lParam);
	LRESULT Set_Norow_order_grid(WPARAM wParam, LPARAM lParam);
	LRESULT OrderGrid_Redrawall(WPARAM wParam, LPARAM lParam);
	//LRESULT Get_Netpos_grid_text_thread1(WPARAM wParam, LPARAM lParam);
	//LRESULT Get_Netpos_grid_text_thread2(WPARAM wParam, LPARAM lParam);
	//LRESULT SetTextValue_2(WPARAM wParam, LPARAM lParam);	

	void ThreadStart();

	void data_ThreadStart();
	void Selected_ActivateOrder();

};

#endif //_FindGrid_H_