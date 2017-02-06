#ifndef _ATA_LOGFILE_
#define _ATA_LOGFILE_
class CLogFile
{
public:
	
	void  CreateDirectories(CString filename);
	//	Constructor, open the logfile
	 CLogFile();

	//	Destructor, close if logfile if opened
	~CLogFile();

	void OpenFile(CString strFile, bool bAppend = TRUE, long lTruncate = 4096);
	void ChangeFile(CString strFile, bool bAppend = TRUE, long lTruncate = 4096);
	void CloseFile();

	char* CstringToCharP(CString event);

	//	Write log info into the logfile, with printf like parameters support
	void CLogFile::Write(CString pszFormat);
	void CLogFile::LogEvent(CString event);
private:
	FILE*	m_pLogFile;
	long	m_lTruncate;
	CRITICAL_SECTION	m_cs;

	CString	m_filename;


	
};

#endif //_ATA_LOGFILE_
