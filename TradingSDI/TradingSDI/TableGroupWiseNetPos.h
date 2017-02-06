//#include "stdafx.h"
#include <atldbcli.h>
class CGroupWiseNetPos
{

public:
		TCHAR  Group[100];
		TCHAR  Symbol[100];	
		double PreNetqty;
		double Diffqty;
		double Netqty;
		double avg_rate;
		double current_rate;
		double pl;		
		double Total_Amount;	
	

	
		DBSTATUS	d_Group;
		DBSTATUS	d_Symbol;	
		DBSTATUS	d_PreNetqty;
		DBSTATUS	d_Diffqty;
		DBSTATUS	d_Netqty;
		DBSTATUS	d_avg_rate;
		DBSTATUS	d_current_rate;
		DBSTATUS	d_pl;		
		DBSTATUS	d_Total_Amount;	
	




		DBLENGTH 	l_Group;
		DBLENGTH	l_Symbol;	
		DBLENGTH	l_PreNetqty;
		DBLENGTH	l_Diffqty;
		DBLENGTH	l_Netqty;
		DBLENGTH	l_avg_rate;
		DBLENGTH	l_current_rate;
		DBLENGTH	l_pl;		
		DBLENGTH	l_Total_Amount;	


	
	

	
// Column binding map
BEGIN_COLUMN_MAP(CGroupWiseNetPos)
		COLUMN_ENTRY_LENGTH_STATUS(1, Group, l_Group,d_Group)
		COLUMN_ENTRY_LENGTH_STATUS(2, Symbol, l_Symbol, d_Symbol)

		COLUMN_ENTRY_LENGTH_STATUS(3, PreNetqty, l_PreNetqty, d_PreNetqty)
		COLUMN_ENTRY_LENGTH_STATUS(4, Diffqty, l_Diffqty, d_Diffqty)

		COLUMN_ENTRY_LENGTH_STATUS(5, Netqty, l_Netqty, d_Netqty)
		COLUMN_ENTRY_LENGTH_STATUS(6, avg_rate, l_avg_rate, d_avg_rate)
		COLUMN_ENTRY_LENGTH_STATUS(7,  current_rate, l_current_rate, d_current_rate)
		COLUMN_ENTRY_LENGTH_STATUS(8,  pl, l_pl, d_pl)
		COLUMN_ENTRY_LENGTH_STATUS(9, Total_Amount, l_Total_Amount, d_Total_Amount)
		
	END_COLUMN_MAP()
	
};