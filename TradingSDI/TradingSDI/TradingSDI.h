
// TradingSDI.h : main header file for the TradingSDI application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTradingSDIApp:
// See TradingSDI.cpp for the implementation of this class
//

class CTradingSDIApp : public CWinAppEx
{
public:
	CTradingSDIApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	
	DECLARE_MESSAGE_MAP()
};

extern CTradingSDIApp theApp;
