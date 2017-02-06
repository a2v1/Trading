#pragma once
#include "OVERVIEW.h"
#include "tab2.h"
#include "tab3.h"
#include "tab4.h"
#include "tabcontrol.h"
// ADD_overview dialog
 
class ADD_overview : public CDialogEx
{
    DECLARE_DYNAMIC(ADD_overview)
 
public:
    ADD_overview(CWnd* pParent = NULL);   // standard constructor
    virtual ~ADD_overview();
 
// Dialog Data
    enum { IDD = IDD_OVERVIEW };
 
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    HICON m_hIcon;
 
    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    /*overview *p1;
    Tab2  *p2;
    tab3  *p3;
    tab4  *p4;*/
    int m_bInit;
public:
   /* CWinThread* m_pThreads;
    CWinThread* m_order_pThreads;*/
 
    tabControl m_ctrlTAB;
//  afx_msg void OnMove(int x, int y);
//  afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnNMClickTab(NMHDR *pNMHDR, LRESULT *pResult);
 
    afx_msg void OnClose();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnDestroy();
//  afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnNMClickTab1(NMHDR *pNMHDR, LRESULT *pResult);
     
};