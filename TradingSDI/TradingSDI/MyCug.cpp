/***************************************************
****************************************************
Skeleton Class for a Derived MyCug
****************************************************
****************************************************/

#include "stdafx.h"
//#include "uglibsel.h"		// Include the file which will select which library file to use

#include "resource.h"
#include "MyCug.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(MyCug,CUGCtrl)
	//{{AFX_MSG_MAP(MyCug)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/***************************************************
****************************************************/
MyCug::MyCug()
{

}
MyCug::MyCug(int  col,int row)
{	
	

}
/***************************************************
****************************************************/
MyCug::~MyCug()
{
	UGXPThemes::CleanUp();
}

/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void MyCug::OnSetup()
{
	
	EnableMenu(TRUE);
}

/***************************************************
sections - UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
			UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
****************************************************/
/***************************************************
OnGetDefBackColor
****************************************************/
