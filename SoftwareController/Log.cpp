#include "StdAfx.h"
#include "Log.h"
#include "FileIO.h"
#include "Inifile.h"


#include <Shlobj.h>
#include <boost/date_time/posix_time/posix_time.hpp>

CLog::CLog(void)
{
}


CLog::~CLog(void)
{
}

bool CLog::IsWrite()
{
	CInifile ini;
	ini.ReadInifile( _T("argument"), _T("Log"), _T("false") );
	tstring contents = ini.GetContents();
	transform( contents.begin(), contents.end(), contents.begin(), ::tolower );

	return !contents.compare( _T("true") );
}

void CLog::Write( const tstring sLog )
{
	_tprintf_s(sLog.c_str());

	// ���O�o�̓��[�h�ɂȂ��Ă��邩���`�F�b�N
	if( !IsWrite() )	return;
	

#ifdef _UNICODE
	std::wostringstream file;
#else
	std::ostringstream file;
#endif

	// �f�X�N�g�b�v�ɏo��
	TCHAR desktopPath[_MAX_PATH];
	::SHGetSpecialFolderPath(NULL, desktopPath, CSIDL_DESKTOPDIRECTORY, FALSE);

	// �����̓��t�Ńt�@�C�����쐬����
	tm now = boost::posix_time::to_tm(boost::posix_time::second_clock::local_time());
	file << desktopPath << _T("\\") << 
		now.tm_year + 1970 << 
		std::setw(2) << now.tm_mon <<
		std::setw(2) << now.tm_yday << 
		_T("-") << 
		std::setw(2) << now.tm_hour << 
		std::setw(2) << now.tm_min << 
		std::setw(2) << now.tm_sec << 
		_T(".log");
	
	// �t�@�C����
	CFileIO io;
	io.Write(sLog, std::ios::app, file.str().c_str());
}

void CLog::Write( const tstring sClass, const int eType, const tstring sContents )
{
#ifdef _UNICODE
	std::wostringstream os;
#else
	std::ostringstream os;
#endif

	os << sClass << "[result:" << eType << "]\t" << sContents;
	Write( os.str() );
}