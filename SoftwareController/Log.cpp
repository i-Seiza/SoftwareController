#include "StdAfx.h"
#include "Log.h"
#include "FileIO.h"
#include "Inifile.h"


#include <time.h>



CLog::CLog(void)
{
}


CLog::~CLog(void)
{
}

bool CLog::IsWrite()
{
	CInifile ini;
	ini.ReadInifile( "argument", "Log", "false" );
	std::string contents = ini.GetContents();
	transform( contents.begin(), contents.end(), contents.begin(), ::tolower );

	return !contents.compare( "true" );
}


void CLog::Write( const std::string sLog )
{
	printf( sLog.c_str() );

	// ログ出力モードになっているかをチェック
	if( !IsWrite() )	return;
	// 今日の日付でファイルを作成する
	struct tm *date;
	time_t now;
	time(&now);
	date = localtime(&now);

	// ファイル名
	char buffa[_MAX_PATH];
	SHGetSpecialFolderPath(NULL, buffa, CSIDL_DESKTOPDIRECTORY, FALSE);
	sprintf_s( buffa, _MAX_PATH, "%s\\%04d%02d%02d.log", buffa, date->tm_year + 1900, date->tm_mon + 1 , date->tm_mday );

	std::ostringstream os;
	os << std::setw(2) << date->tm_hour << ":" << std::setw(2) << date->tm_min << "\t" << sLog;

	CFileIO io;
	io.Write( os.str(), std::ios::app, buffa );
}

void CLog::Write( const std::string sClass, const int eType, const std::string sContents )
{
	std::ostringstream os;
	os << sClass << "[result:" << eType << "]\t" << sContents;
	Write( os.str() );
}