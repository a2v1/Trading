#include "ugctrl.h"


class MyCug:public CUGCtrl
{
public:
	MyCug();
	MyCug(int  col,int row);
	~MyCug();

	
	DECLARE_MESSAGE_MAP()


	virtual void OnSetup();
};
