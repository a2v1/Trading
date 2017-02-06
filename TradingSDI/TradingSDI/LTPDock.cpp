// LTPDock.cpp : implementation file
//

#include "stdafx.h"
#include "TradingSDI.h"
#include "LTPDock.h"


// LTPDock

IMPLEMENT_DYNAMIC(LTPDock, CDockablePane)

LTPDock::LTPDock()
{

}

LTPDock::~LTPDock()
{
}


BEGIN_MESSAGE_MAP(LTPDock, CDockablePane)
	ON_WM_CLIPBOARDUPDATE()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// LTPDock message handlers




void LTPDock::OnClipboardUpdate()
{
	// This feature requires Windows Vista or greater.
	// The symbol _WIN32_WINNT must be >= 0x0600.
	// TODO: Add your message handler code here and/or call default

	CDockablePane::OnClipboardUpdate();
}


int LTPDock::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(!ltpDock.Create(LTP_Dilog::IDD,this))
		return -1;
	ltpDock.ShowWindow(SW_SHOWDEFAULT);
	return  0;

}


void LTPDock::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	ltpDock.SetWindowPos(NULL,0,0,cx,cy,SWP_NOACTIVATE|SWP_NOZORDER);

	// TODO: Add your message handler code here
}
