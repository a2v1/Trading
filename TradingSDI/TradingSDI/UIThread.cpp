#include "stdafx.h"
#include "UIThread.h"
#include "OrderGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CUIThread, CWinThread)
	OrderGrid  oGrid;
CUIThread::CUIThread()
{
	
	m_bKill = FALSE;
	m_bRunning = FALSE;
}

CUIThread::~CUIThread()
{
}


BOOL CUIThread::InitInstance()
{
	return TRUE;
}

int CUIThread::ExitInstance()
{
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CUIThread, CWinThread)

END_MESSAGE_MAP()


void CUIThread::Kill()
{

	if(m_bKill) return;

	
}


int CUIThread::Run()
{
	
	//OrderGrid::m_wndOutputOrder->GetOrders();
	return 0;
}



BOOL CUIThread::IsRunning()
{
	return m_bRunning;
}


void CUIThread::SetParent(CWnd *pParent)
{
	m_pParent = pParent;
}