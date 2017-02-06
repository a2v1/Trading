#if !defined(AFX_UITHREAD_H__4161E89D_3655_46B2_AF28_6DB7E65C5031__INCLUDED_)
#define AFX_UITHREAD_H__4161E89D_3655_46B2_AF28_6DB7E65C5031__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define WM_INFORM_CLOSE		WM_USER + 100



class CUIThread : public CWinThread
{
	DECLARE_DYNCREATE(CUIThread)

protected:
	

// Attributes
public:

// Operations
public:
	void SetParent(CWnd* pParent);
	CUIThread();           // protected constructor used by dynamic creation
	virtual ~CUIThread();	
	BOOL IsRunning();
	//	The main loop for running the interface thread. In this case, it displays a modal dialog box.
	int Run();
	//	Kill the interface thread by posting a message to the dialog box object.
	void Kill();

private:
	CWnd* m_pParent;
	BOOL	m_bKill;
	BOOL	m_bRunning;	
	
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();	
protected:		
	DECLARE_MESSAGE_MAP()
};


#endif 
