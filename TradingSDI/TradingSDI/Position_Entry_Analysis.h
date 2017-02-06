#ifndef CPosEntryAna_HEADER
#define CPosEntryAna_HEADER
#include <atldbcli.h>
  class CPosition_Entry_Analysis
	{

	public:
	
	TCHAR               m_deal[33];  
	TCHAR               m_login[38];
	TCHAR               m_symbol[31];
	TCHAR               m_time[38];
	TCHAR               m_EntryVolume[32];
	float               m_EntryPrice;
	
	// The following wizard-generated data members contain status
	// values for the corresponding fields in the column map. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Diata Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!
	
	DBSTATUS m_dwdealStatus;
	DBSTATUS m_dwloginStatus;
	DBSTATUS m_dwsymbolStatus;
	DBSTATUS m_dwtimeStatus;
	DBSTATUS m_dwEntryVolumeStatus;
	DBSTATUS m_dwEntryPriceStatus;
	// The following wizard-generated data members contain length
	// values for the corresponding fields in the column map.
	// NOTE: For variable-length columns, you must initialize tbiginthese
	//       fields before setting/inserting data!



	DBLENGTH m_dwdealLength;
	DBLENGTH m_dwloginLength;
	DBLENGTH m_dwsymbolLength;	
	DBLENGTH m_dwtimeLength;
	DBLENGTH m_dwEntryVolumeLength;
	DBLENGTH m_dwEntryPriceLength;	
	
	// Column binding map
	BEGIN_COLUMN_MAP(CPosition_Entry_Analysis)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_deal,m_dwdealLength,m_dwdealStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_login, m_dwloginLength,m_dwloginStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_symbol, m_dwsymbolLength, m_dwsymbolStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_time,m_dwtimeLength,m_dwtimeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5, m_EntryVolume,m_dwEntryVolumeLength, m_dwEntryVolumeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(6, m_EntryPrice, m_dwEntryPriceLength, m_dwEntryPriceStatus)
	END_COLUMN_MAP()
	
	};
#endif