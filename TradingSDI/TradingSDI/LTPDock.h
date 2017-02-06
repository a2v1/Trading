#pragma once
#include "LTP_Dilog.h"

// LTPDock

class LTPDock : public CDockablePane
{
	DECLARE_DYNAMIC(LTPDock)

public:
	LTPDock();
	virtual ~LTPDock();
public:
	LTP_Dilog  ltpDock;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClipboardUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


