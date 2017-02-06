//#include "stdafx.h"
#include <atldbcli.h>
class CAnalysisTable
{
public:
	TCHAR m_Login[50];
	TCHAR m_Symbol[50];
	TCHAR m_RiskMeter[50];
	TCHAR m_Potencial_Meter[50];
	TCHAR m_BSMeter[50];
	TCHAR m_WeightAvgP[50];
	TCHAR m_SDP[50];
	TCHAR m_COVP[50];
	TCHAR m_Skewnessp[50];
	TCHAR m_KurtostsP[50];
	TCHAR m_Total_lots_P[50];
	TCHAR m_Weight_Avg_L[50];
	TCHAR m_SD_L[50];
	TCHAR m_COV_L[50];
	TCHAR m_Skewness_L[50];
	TCHAR m_Kurtosts_L[50];
	TCHAR m_Total_lots_L[50];
	TCHAR m_Weight_Avg_PP[50];
	TCHAR m_SD_PP[50];
	TCHAR m_COV_PP[50];
	TCHAR m_Skewness_PP[50];
	TCHAR m_Kurtosts_PP[50];
	TCHAR m_Weight_Avg_PL[50];
	TCHAR m_SD_PL[50];
	TCHAR m_COV_PL[50];
	TCHAR m_Skewness_PL[50];
	TCHAR m_Kurtosts_PL[50];


	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!
	
	DBSTATUS  m_Login_status;
	DBSTATUS  m_Symbol_status;
	DBSTATUS  m_RiskMeter_status;
	DBSTATUS  m_Potencial_Meter_status;
	DBSTATUS  m_BSMeter_status;
	DBSTATUS  m_WeightAvgP_status;
	DBSTATUS  m_SDP_status;
	DBSTATUS  m_COVP_status;
	DBSTATUS  m_Skewnessp_status;
	DBSTATUS  m_KurtostsP_status;
	DBSTATUS  m_Total_lots_P_status;
	DBSTATUS  m_Weight_Avg_L_status;
	DBSTATUS  m_SD_L_status;
	DBSTATUS  m_COV_L_status;
	DBSTATUS  m_Skewness_L_status;
	DBSTATUS  m_Kurtosts_L_status;
	DBSTATUS  m_Total_lots_L_status;
	DBSTATUS  m_Weight_Avg_PP_status;
	DBSTATUS  m_SD_PP_status;
	DBSTATUS  m_COV_PP_status;
	DBSTATUS  m_Skewness_PP_status;
	DBSTATUS  m_Kurtosts_PP_status;
	DBSTATUS  m_Weight_Avg_PL_status;
	DBSTATUS  m_SD_PL_status;
	DBSTATUS  m_COV_PL_status;
	DBSTATUS  m_Skewness_PL_status;
	DBSTATUS  m_Kurtosts_PL_status;
	
	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!



	DBLENGTH  m_Login_length;
	DBLENGTH  m_Symbol_length;
	DBLENGTH  m_RiskMeter_length;
	DBLENGTH  m_Potencial_Meter_length;
	DBLENGTH  m_BSMeter_length;
	DBLENGTH  m_WeightAvgP_length;
	DBLENGTH  m_SDP_length;
	DBLENGTH  m_COVP_length;
	DBLENGTH  m_Skewnessp_length;
	DBLENGTH  m_KurtostsP_length;
	DBLENGTH  m_Total_lots_P_length;
	DBLENGTH  m_Weight_Avg_L_length;
	DBLENGTH  m_SD_L_length;
	DBLENGTH  m_COV_L_length;
	DBLENGTH  m_Skewness_L_length;
	DBLENGTH  m_Kurtosts_L_length;
	DBLENGTH  m_Total_lots_L_length;
	DBLENGTH  m_Weight_Avg_PP_length;
	DBLENGTH  m_SD_PP_length;
	DBLENGTH  m_COV_PP_length;
	DBLENGTH  m_Skewness_PP_length;
	DBLENGTH  m_Kurtosts_PP_length;
	DBLENGTH  m_Weight_Avg_PL_length;
	DBLENGTH  m_SD_PL_length;
	DBLENGTH  m_COV_PL_length;
	DBLENGTH  m_Skewness_PL_length;
	DBLENGTH  m_Kurtosts_PL_length;			
// Column binding map
BEGIN_COLUMN_MAP(CAnalysisTable)		
		COLUMN_ENTRY_LENGTH_STATUS(1,m_Login,m_Login_length,m_Login_status); 
		COLUMN_ENTRY_LENGTH_STATUS(2,m_Symbol,m_Symbol_length,m_Symbol_status);
		COLUMN_ENTRY_LENGTH_STATUS(3,m_RiskMeter,m_RiskMeter_length,m_RiskMeter_status);
		COLUMN_ENTRY_LENGTH_STATUS(4,m_Potencial_Meter,m_Potencial_Meter_length,m_Potencial_Meter_status);
		COLUMN_ENTRY_LENGTH_STATUS(5,m_BSMeter,m_BSMeter_length,m_BSMeter_status);
		COLUMN_ENTRY_LENGTH_STATUS(6,m_WeightAvgP,m_WeightAvgP_length,m_WeightAvgP_status);
		COLUMN_ENTRY_LENGTH_STATUS(7,m_SDP,m_SDP_length,m_SDP_status);
		COLUMN_ENTRY_LENGTH_STATUS(8,m_COVP,m_COVP_length,m_COVP_status);
		COLUMN_ENTRY_LENGTH_STATUS(9,m_Skewnessp,m_Skewnessp_length,m_Skewnessp_status);
		COLUMN_ENTRY_LENGTH_STATUS(10,m_KurtostsP,m_KurtostsP_length,m_KurtostsP_status);
		COLUMN_ENTRY_LENGTH_STATUS(11,m_Total_lots_P,m_Total_lots_P_length,m_Total_lots_P_status);
		COLUMN_ENTRY_LENGTH_STATUS(12,m_Weight_Avg_L,m_Weight_Avg_L_length,m_Weight_Avg_L_status);
		COLUMN_ENTRY_LENGTH_STATUS(13,m_SD_L,m_SD_L_length,m_SD_L_status);
		COLUMN_ENTRY_LENGTH_STATUS(14,m_COV_L,m_COV_L_length,m_COV_L_status);
		COLUMN_ENTRY_LENGTH_STATUS(15,m_Skewness_L,m_Skewness_L_length,m_Skewness_L_status);
		COLUMN_ENTRY_LENGTH_STATUS(16,m_Kurtosts_L,m_Kurtosts_L_length,m_Kurtosts_L_status);
		COLUMN_ENTRY_LENGTH_STATUS(17,m_Total_lots_L,m_Total_lots_L_length,m_Total_lots_L_status);
		COLUMN_ENTRY_LENGTH_STATUS(18,m_Weight_Avg_PP,m_Weight_Avg_PP_length,m_Weight_Avg_PP_status);
		COLUMN_ENTRY_LENGTH_STATUS(19,m_SD_PP,m_SD_PP_length,m_SD_PP_status);
		COLUMN_ENTRY_LENGTH_STATUS(20,m_COV_PP,m_COV_PP_length,m_COV_PP_status);
		COLUMN_ENTRY_LENGTH_STATUS(21,m_Skewness_PP,m_Skewness_PP_length,m_Skewness_PP_status);
		COLUMN_ENTRY_LENGTH_STATUS(22,m_Kurtosts_PP,m_Kurtosts_PP_length,m_Kurtosts_PP_status);
		COLUMN_ENTRY_LENGTH_STATUS(23,m_Weight_Avg_PL,m_Weight_Avg_PL_length,m_Weight_Avg_PL_status);
		COLUMN_ENTRY_LENGTH_STATUS(24,m_SD_PL,m_SD_PL_length,m_SD_PL_status);
		COLUMN_ENTRY_LENGTH_STATUS(25,m_COV_PL,m_COV_PL_length,m_COV_PL_status);
		COLUMN_ENTRY_LENGTH_STATUS(26,m_Skewness_PL,m_Skewness_PL_length,m_Skewness_PL_status);
		COLUMN_ENTRY_LENGTH_STATUS(27,m_Kurtosts_PL,m_Kurtosts_PL_length,m_Kurtosts_PL_status);
	END_COLUMN_MAP()
	
};