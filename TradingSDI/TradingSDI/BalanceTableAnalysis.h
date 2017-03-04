#ifndef CBalance_HEADER
#define CBalance_HEADER
#include <atldbcli.h>
  class CBalanceTableAnalysis
	{

	public:
	
	TCHAR               m_Login[33];  
	TCHAR               m_deal[31];
	TCHAR               m_Time[31];
	TCHAR               m_Order[38];
	TCHAR               m_Symbol[32];
	TCHAR               m_EntryAction[40];
	TCHAR               m_EntryVolume[40];	
	TCHAR               m_EntryPrice[40];
	TCHAR               m_ExitDeal[40];
	TCHAR               m_ExitTime[40];
	TCHAR               m_ExitOrder[40];
	TCHAR               m_ExitAction[40];
	TCHAR               m_ExitVolume[40];
	TCHAR               m_ExitPrice[40];  
	TCHAR               m_ProfitPoint_L[40];
	TCHAR               m_ProfitPoint_P[40];
	TCHAR               m_Multiplayer[40];
	TCHAR               m_Balance[40];
	TCHAR               m_potentialprofitpoint[40];
	TCHAR               m_PotentialLosspoint[40];
	TCHAR               m_DurationTime[38];
	TCHAR               m_high[40];
	TCHAR               m_low[40];
	
	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Diata Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!
	
	DBSTATUS m_dwloginStatus;
	DBSTATUS m_dwdealStatus;
	DBSTATUS m_dwtimeStatus;
	DBSTATUS m_dworderStatus;
	DBSTATUS m_dwsymbolStatus;
	DBSTATUS m_dwEntryActionStatus;
	DBSTATUS m_dwEntryVolumeStatus;
	DBSTATUS m_dwEntryPriceStatus;
	DBSTATUS m_dwExitDealStatus;
	DBSTATUS m_dwExitTimeStatus;
	DBSTATUS m_dwExitOrderStatus;
	DBSTATUS m_dwExitActionStatus;
	DBSTATUS m_dwExitVolumeStatus;
	DBSTATUS m_dwExitPriceStatus;
	DBSTATUS m_dwProfitPoint_LStatus;
	DBSTATUS m_dwProfitPoint_PStatus;
	DBSTATUS m_dwMultiplayerStatus;
	DBSTATUS m_dwBalanceStatus;
	DBSTATUS m_dwpotentialprofitpointStatus;
	DBSTATUS m_dwPotentialLosspointStatus;
	DBSTATUS m_dwDurationTimeStatus;
	DBSTATUS m_dwhighStatus;
	DBSTATUS m_dwlowStatus;
	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize tbiginthese
	//       fields before setting/inserting data!



	DBLENGTH m_dwloginLength;
	DBLENGTH m_dwdealLength;
	DBLENGTH m_dwtimeLength;	
	DBLENGTH m_dworderLength;
	DBLENGTH m_dwSymbolLength;
	DBLENGTH m_dwEntryActionLength;	
	DBLENGTH m_dwEntryVolumeLength;
	DBLENGTH m_dwEntryPriceLength;
	DBLENGTH m_dwExitDealLength;	
	DBLENGTH m_dwExitTimeLength;
	DBLENGTH m_dwExitOrderLength;
	DBLENGTH m_dwExitActionLength;	
	DBLENGTH m_dwExitVolumeLength;
	DBLENGTH m_dwExitPriceLength;
	DBLENGTH m_dwProfitPoint_LLength;	
	DBLENGTH m_dwProfitPoint_PLength;
	DBLENGTH m_dwMultiplayerLength;
	DBLENGTH m_dwBalanceLength;	
	DBLENGTH m_dwpotentialprofitpointLength;
	DBLENGTH m_dwPotentialLosspointLength;
	DBLENGTH m_dwDurationTimeLength;	
	DBLENGTH m_dwhighLength;
	DBLENGTH m_dwLowLength;
	// Column binding map
	BEGIN_COLUMN_MAP(CBalanceTableAnalysis)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_Login,m_dwloginLength,m_dwloginStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_deal,m_dwdealLength ,m_dwdealStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_Time, m_dwtimeLength, m_dwtimeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_Order,m_dworderLength,m_dworderStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5, m_Symbol,m_dwSymbolLength, m_dwsymbolStatus)
		COLUMN_ENTRY_LENGTH_STATUS(6, m_EntryAction, m_dwEntryActionLength, m_dwEntryActionStatus)
		COLUMN_ENTRY_LENGTH_STATUS(7, m_EntryVolume,m_dwEntryVolumeLength,m_dwEntryVolumeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(8, m_EntryPrice,m_dwEntryPriceLength,m_dwEntryPriceStatus)
		COLUMN_ENTRY_LENGTH_STATUS(9, m_ExitDeal,m_dwExitDealLength ,m_dwExitDealStatus)
		COLUMN_ENTRY_LENGTH_STATUS(10, m_ExitTime, m_dwExitTimeLength, m_dwExitTimeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(11, m_ExitOrder,m_dwExitOrderLength,m_dwExitOrderStatus)
		COLUMN_ENTRY_LENGTH_STATUS(12, m_ExitAction,m_dwEntryActionLength, m_dwEntryActionStatus)
		COLUMN_ENTRY_LENGTH_STATUS(13, m_ExitVolume, m_dwExitVolumeLength, m_dwExitVolumeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(14, m_ExitPrice,m_dwExitPriceLength,m_dwExitPriceStatus)
		COLUMN_ENTRY_LENGTH_STATUS(15, m_ProfitPoint_L,m_dwProfitPoint_LLength,m_dwProfitPoint_LStatus)
		COLUMN_ENTRY_LENGTH_STATUS(16, m_ProfitPoint_P,m_dwProfitPoint_PLength ,m_dwProfitPoint_PStatus)
		COLUMN_ENTRY_LENGTH_STATUS(17, m_Multiplayer, m_dwMultiplayerLength, m_dwMultiplayerStatus)
		COLUMN_ENTRY_LENGTH_STATUS(18, m_Balance,m_dwBalanceLength,m_dwBalanceStatus)
		COLUMN_ENTRY_LENGTH_STATUS(19, m_potentialprofitpoint,m_dwpotentialprofitpointLength, m_dwpotentialprofitpointStatus)
		COLUMN_ENTRY_LENGTH_STATUS(20, m_PotentialLosspoint, m_dwPotentialLosspointLength, m_dwPotentialLosspointStatus)
		COLUMN_ENTRY_LENGTH_STATUS(21, m_DurationTime,m_dwDurationTimeLength,m_dwDurationTimeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(22, m_high,m_dwhighLength, m_dwhighStatus)
		COLUMN_ENTRY_LENGTH_STATUS(23, m_low, m_dwLowLength, m_dwlowStatus)
	END_COLUMN_MAP()
	
	};
	#endif