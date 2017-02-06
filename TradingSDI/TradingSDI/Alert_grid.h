#pragma once
#include "ugctrl.h"
#include "OrderGrid.h"
class Alert_grid :public CUGCtrl
{
public:
	Alert_grid(void);
	~Alert_grid(void);

protected:
	
	 DECLARE_MESSAGE_MAP();

public:
    CButton button;
	CStatic m_stText;
virtual void OnSetup();

virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
};

