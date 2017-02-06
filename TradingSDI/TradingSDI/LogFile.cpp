#include "stdafx.h"
#include "LogFile.h"
#include <direct.h>


void CLogFile::OpenFile(CString strFile, bool bAppend, long lTruncate)
{
	m_lTruncate = lTruncate;
	m_filename = strFile;

	TCHAR	szFile[MAX_PATH+1];
	if (_tcslen(strFile)>3 && strFile[1]!=':')	//no absolute path designated
	{
		::GetModuleFileName(NULL, szFile, MAX_PATH);
		long llength = _tcslen(szFile);
		TCHAR*	pcat = szFile+(llength - 1);	//point to the last char
		while (llength--)
		{
			pcat--;
			if (*pcat == '\\')
				break;
		}
		if (*pcat == '\\')
		{
			pcat++;
			_tcscpy(pcat, strFile);
		}
		else	//something wrong, use the original filename, ignore path problem
			_tcscpy(szFile, strFile);		
	}
	else
		_tcscpy(szFile, strFile);

	if (!(m_pLogFile = _wfopen(szFile, bAppend ? L"a" : L"w")))
		{
		CreateDirectories(szFile);

		m_pLogFile = _wfopen(szFile, bAppend ? L"a" : L"w");
		}

	InitializeCriticalSection(&m_cs);
}


 CLogFile::CLogFile() 
{
	OpenFile(L"demo.log", TRUE);
}

	/////////////////////////////////
	//	Destructor, close if logfile if opened
CLogFile::~CLogFile()
{
	CloseFile();
}

void CLogFile::CloseFile()
{
	if (m_pLogFile)
		{
		fputs("\n===============Finish Loging================\n\n", m_pLogFile);

		fclose(m_pLogFile);
		}

	DeleteCriticalSection(&m_cs);
}

void CLogFile::ChangeFile(CString strFile, bool bAppend, long lTruncate)
{
	if (strFile != m_filename)
		{
		CloseFile();
		OpenFile(strFile, bAppend, lTruncate);
		}
}

void CLogFile::CreateDirectories(CString filename)
{
	CString drivename, path;
	int drive, per;

	drivename = filename.Left(3);
	drive = drivename[0] - 'A' + 1;
	//_chdrive(drive);

	for (per = 1; per <= 20; per++)
		_chdir("..");

	filename = filename.Mid(3);
	while (!filename.IsEmpty())
		{
		per = filename.Find('\\');

		if (per == -1)
			break;

		path = filename.Left(per);
		if (_wchdir(path))
			{
			_wmkdir(path);
			_wchdir(path);
			}

		filename = filename.Mid(per + 1);
		}

}


void CLogFile::Write(CString pszFormat)
{
		if (!m_pLogFile)
			return;

		EnterCriticalSection(&m_cs);
		//write the formated log string to szLog
		TCHAR	szLog[5000];
		va_list argList;
		va_start( argList, pszFormat );
		_swprintf( szLog,pszFormat, argList );

		va_end( argList );

		SYSTEMTIME	time;
		::GetLocalTime(&time);
		TCHAR	szLine[256];
		

		_swprintf(szLine, L"%04d/%02d/%02d %02d:%02d:%02d:%03d \t%s\n", 
			time.wYear, time.wMonth, time.wDay,
			time.wHour, time.wMinute, time.wSecond, time.wMilliseconds,
			szLog);
		
		fputws(szLine, m_pLogFile);

		fflush(m_pLogFile);

		LeaveCriticalSection(&m_cs);
	}


void CLogFile::LogEvent(CString event)
{
	CString name;
	SYSTEMTIME systime;

	GetLocalTime(&systime);

	name.Format(L"MYLog\\log_%02i%02i%02i.txt",
		systime.wDay,
		systime.wMonth,
		systime.wYear		
		);
	ChangeFile(name);

	Write(event);
}

char* CLogFile::CstringToCharP(CString event)
{
	_bstr_t bstr=event;
	char* returnchar=bstr;
	return returnchar;
}