#include <atldbcli.h>
class Netposition_table
{
public:
	TCHAR m_login[100];
	TCHAR m_name[200];
	TCHAR m_symbol[100];
	TCHAR m_Pre_NetQty[100];
	TCHAR m_Diff_NetQty[100];
	TCHAR m_NetQty[100];
	TCHAR m_Average[100];
	TCHAR m_LastRate[100];
	TCHAR m_PL[100];
	TCHAR m_balance[100];
	TCHAR m_lastupdate[100];
	TCHAR m_Group1[100];
	TCHAR m_Group2[100];
	TCHAR m_Group3[100];
    TCHAR m_Checked_Status[100];
	TCHAR m_checked_time[100];
	TCHAR m_Alloted_Limit[100];
	TCHAR m_Remark2[100];
	TCHAR m_Standing_Avg_rate[100];
	TCHAR m_SQ_Balance[100];
	TCHAR m_pl_volume[100];
	TCHAR m_creditClient[100];
	//TCHAR m_marginlive[100];
	
	
	
	DBSTATUS m_dwlogin;
	DBSTATUS m_dwname;
	DBSTATUS m_dwsymbol;
	DBSTATUS m_dwPre_NetQty;
	DBSTATUS m_dwDiff_NetQty;
	DBSTATUS m_dwNetQty;
	DBSTATUS m_dwAverage;
	DBSTATUS m_dwLastRate;
	DBSTATUS m_dwPL;
	DBSTATUS m_dwbalance;
	DBSTATUS m_dwlastupdate;
	DBSTATUS m_dwGroup1;                                              
	DBSTATUS m_dwGroup2;
	DBSTATUS m_dwGroup3;
	DBSTATUS m_dwChecked_Status;
	DBSTATUS m_dwchecked_time;
	DBSTATUS m_dwAlloted_Limit;
	DBSTATUS m_dwRemark2;
	DBSTATUS m_dwStanding_Avg_rate;
	DBSTATUS m_dwSQ_Balance;
	DBSTATUS m_dwpl_volume;
	DBSTATUS m_creditClient_s;
	//DBSTATUS m_dwmarginlive;


    DBLENGTH m_dwLoginLength;
	DBLENGTH m_dwnameLength;
	DBLENGTH m_dwsymbolLength;	
	DBLENGTH m_dwPre_NetQtylength;
	DBLENGTH m_dwDiff_NetQtyLength;
	DBLENGTH m_dwNetQtyLength;
	DBLENGTH m_dwAverageLength;
	DBLENGTH m_dwLastRateLength;
	DBLENGTH m_dwPLLength;	
	DBLENGTH m_dwbalancelength;
	DBLENGTH m_dwlastupdateLength;
	DBLENGTH m_dwGroup1Length;
	DBLENGTH m_dwGroup2Length;
	DBLENGTH m_dwGroup3Length;
	DBLENGTH m_dwChecked_StatusLength;	
	DBLENGTH m_dwchecked_timelength;
	DBLENGTH m_dwAlloted_LimitLength;
	DBLENGTH m_dwRemark2Length;
	DBLENGTH m_dwStanding_Avg_ratelength;
	DBLENGTH m_dwSQ_BalanceLength;
	DBLENGTH m_dwpl_volumeLength;
	DBLENGTH m_creditClient_l;
	//DBLENGTH m_dwmarginliveLength;

		

BEGIN_COLUMN_MAP(Netposition_table)
	    COLUMN_ENTRY_LENGTH_STATUS(1, m_login,m_dwlogin,m_dwLoginLength)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_name,m_dwname, m_dwnameLength)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_symbol, m_dwsymbol, m_dwsymbolLength)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_Pre_NetQty, m_dwPre_NetQty, m_dwPre_NetQtylength)
        COLUMN_ENTRY_LENGTH_STATUS(5, m_Diff_NetQty, m_dwDiff_NetQty, m_dwDiff_NetQtyLength)
        COLUMN_ENTRY_LENGTH_STATUS(6, m_NetQty,m_dwNetQty,m_dwNetQtyLength)
		COLUMN_ENTRY_LENGTH_STATUS(7, m_Average,m_dwAverage, m_dwAverageLength)
		COLUMN_ENTRY_LENGTH_STATUS(8, m_LastRate, m_dwLastRate, m_dwLastRateLength)
		COLUMN_ENTRY_LENGTH_STATUS(9, m_PL, m_dwPL, m_dwPLLength)
		COLUMN_ENTRY_LENGTH_STATUS(10, m_balance, m_dwbalance, m_dwbalancelength)
        COLUMN_ENTRY_LENGTH_STATUS(11, m_lastupdate, m_dwlastupdate, m_dwlastupdateLength)	
        COLUMN_ENTRY_LENGTH_STATUS(12, m_Group1,m_dwGroup1,m_dwGroup1Length)
		COLUMN_ENTRY_LENGTH_STATUS(13, m_Group2,m_dwGroup2, m_dwGroup2Length)
		COLUMN_ENTRY_LENGTH_STATUS(14, m_Group3,m_dwGroup3, m_dwGroup3Length)
		COLUMN_ENTRY_LENGTH_STATUS(15, m_Checked_Status,m_Checked_Status, m_dwChecked_StatusLength)
        COLUMN_ENTRY_LENGTH_STATUS(16, m_checked_time, m_dwchecked_time, m_dwchecked_timelength)	
		COLUMN_ENTRY_LENGTH_STATUS(17, m_Alloted_Limit,m_dwAlloted_Limit,m_dwAlloted_LimitLength)
		COLUMN_ENTRY_LENGTH_STATUS(18, m_Remark2,m_dwRemark2, m_dwRemark2Length)
		COLUMN_ENTRY_LENGTH_STATUS(19, m_Standing_Avg_rate, m_dwStanding_Avg_rate, m_dwStanding_Avg_ratelength)
		COLUMN_ENTRY_LENGTH_STATUS(20, m_SQ_Balance, m_dwSQ_Balance, m_dwSQ_BalanceLength)
        COLUMN_ENTRY_LENGTH_STATUS(21, m_pl_volume, m_dwpl_volume, m_dwpl_volumeLength)
		COLUMN_ENTRY_LENGTH_STATUS(22, m_creditClient,m_creditClient_s, m_creditClient_l)
	//	COLUMN_ENTRY_LENGTH_STATUS(22, m_marginlive, m_dwmarginlive, m_dwmarginliveLength)
END_COLUMN_MAP()	
};