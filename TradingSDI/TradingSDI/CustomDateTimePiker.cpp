
#include "stdafx.h"
#include "CustomDateTimePiker.h"
#include "NetPosGrid.h"
#include "OutputWnd.h"
#include "MainFrm.h"
#pragma warning (push, 3)
#include <string>
#pragma warning (pop)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define CALENDAR_AS_POPUP 1
IMPLEMENT_DYNAMIC(CDateTimeEditCtrl, CDateTimeCtrl)

CDateTimeEditCtrl::CDateTimeEditCtrl()
{
	SYSTEMTIME curr_from;
	GetSystemTime(&curr_from);
	CMainFrame::int_currenttime=SMTTime::STToTime(curr_from);
}

CDateTimeEditCtrl::~CDateTimeEditCtrl()
{

}

BEGIN_MESSAGE_MAP(CDateTimeEditCtrl, CDateTimeCtrl)
	//{{AFX_MSG_MAP(CDateTimeEditCtrl)
	ON_WM_CREATE()
	ON_WM_ENABLE()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_CANCELMODE()
	ON_WM_NCCALCSIZE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP() 
	//}}AFX_MSG_MAP		
	ON_WM_STYLECHANGING()		
END_MESSAGE_MAP()

BOOL CDateTimeEditCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
  NMHDR* pnmhdr = (NMHDR*)lParam;
  
  return CDateTimeCtrl::OnNotify(wParam, lParam, pResult);
}

void WINAPI CDateTimeEditCtrl::DoDateTimeChange(LPNMDATETIMECHANGE lpChange)
{
    // If the user has unchecked the DTP's check box, change the
    // text in a static control to show the appropriate message.
    //
    // g_hwndDlg - a program-global address of a dialog box.

    
}

void CDateTimeEditCtrl::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CDateTimeCtrl::OnKeyDown( nChar, nRepCnt, nFlags);
	/*CTime Time; 
	GetTime (Time); 	
	NetPosGrid::bstr_currenttime=Time.Format ("%m-%d-%Y %H:%M:%S");;*/
	
}


void CDateTimeEditCtrl::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CDateTimeCtrl::OnKeyUp( nChar, nRepCnt, nFlags);
	if (nChar==13)
	{
		CTime Time; 
		GetTime (Time); 	
		NetPosGrid::bstr_currenttime=Time.Format ("%m-%d-%Y %H:%M:%S");
		SYSTEMTIME curr_from;
		GetTime (&curr_from); 
		CMainFrame::int_currenttime=SMTTime::STToTime(curr_from);
		//COutputWnd::m_wndOutputPos.UpdatePre_Post_Position();
		
	}
	
}