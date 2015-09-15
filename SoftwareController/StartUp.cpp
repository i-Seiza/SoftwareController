#include "StdAfx.h"
#include "StartUp.h"

#include <time.h>
#include <locale>
#include <boost/date_time/posix_time/posix_time.hpp>

CStartUp::CStartUp(void)
{
}

CStartUp::~CStartUp(void)
{
}

///////////////////////////////
_E_ERROR CStartUp::Execute( const _TCHAR *sContents,  std::vector< std::string > argv )
{
	// 常に起動するアプリケーション
	Execute( sContents, KEYWORD_STARTUP.at(_ALWAYS) );
	// 開始-終了時間に依るアプリケーション
	if( IsExecutePossible( sContents ) )	Execute( sContents, KEYWORD_STARTUP.at(_POSSIBLE) );

	return _E_NOERROR;
}


///////////////////////////////
// Possibleのアプリケーションを起動するか
bool CStartUp::IsExecutePossible( const _TCHAR *sContents )
{
	// 時間を取得
	CExecuteTime vStart, vEnd;
	vStart = GetTime(sContents, KEYWORD_STARTUP.at(_START_TIME));
	vEnd = GetTime(sContents, KEYWORD_STARTUP.at(_END_TIME));

	// チェック
	if (!vStart.IsInitialized())	return false;
	if (!vEnd.IsInitialized())		return false;

	// 本日の日付を取得する
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();

	// 比較する
	int nTime = now.time_of_day().hours() * 60 + now.time_of_day().minutes();
	if (nTime < vStart.GetTotalMinites())	return false;
	if (nTime > vEnd.GetTotalMinites())	return false;

	return true;
}


// 時間を取得する。取得する時間はsKeyで指定
CStartUp::CExecuteTime CStartUp::GetTime( const _TCHAR *sContents, const tstring sKey )
{
	CExecuteTime KeyTime;
	tstring str;

	if( !this->ReadInifile( sContents, sKey.c_str() ))	return KeyTime;
	str = this->GetIniData();

#if UNICODE
	std::wregex re;
	std::wsmatch result;
#else
	std::regex re;
	std::smatch result;
#endif

	re = _T("(.*?)[:;：；](.*?)");
	if (std::regex_match(str, result, re))
	{
		KeyTime.SetHour(std::stoi(result.str(1)));
		KeyTime.SetMinites(std::stoi(result.str(2)));
	}
	
	return KeyTime;
}

// 実行する
_E_ERROR CStartUp::Execute( const _TCHAR *sContents, const tstring sKeyWord )
{
	int nPos = 1;
	while( true )
	{
		_TCHAR	sKey[MAX_PATH];
		_tprintf_s( sKey, sizeof( sKey ), _T("%s%d"), sKeyWord, nPos );

		if( this->ReadInifile( sContents, sKey ) )
		{
			ShellExecute( NULL, _T("open"), this->GetIniData().c_str(), NULL, NULL, SW_SHOWNA );
			nPos++;
			continue;
		}
		break;
	}

	return _E_NOERROR;
}