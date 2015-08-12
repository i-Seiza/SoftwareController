#include "StdAfx.h"
#include "StartUp.h"

#include <time.h>
#include <locale>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

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
	Execute( sContents, sKeyWord_StartUp[_ALWAYS] );
	// 開始-終了時間に依るアプリケーション
	if( IsExecutePossible( sContents ) )	Execute( sContents, sKeyWord_StartUp[_POSSIBLE] );

	return _E_NOERROR;
}


///////////////////////////////
// Possibleのアプリケーションを起動するか
bool CStartUp::IsExecutePossible( const _TCHAR *sContents )
{
	// 本日の日付を取得する
	struct tm ltm;
	time_t t_time;

	time( &t_time );	// システム時間を取得
	localtime_s( &ltm, &t_time );	// ローカル時間を取得

	// 時間を取得
	std::vector<std::string> vStart, vEnd;
	vStart = GetTime( sContents, sKeyWord_StartUp[_START_TIME] );
	vEnd = GetTime( sContents, sKeyWord_StartUp[_END_TIME] );

	// チェック
	if( vStart.size() < 2 )	return false;
	if( vEnd.size() < 2 )	return false;

	// 比較する
	int nTime = ltm.tm_hour * 60 + ltm.tm_min;
	int nCom = boost::lexical_cast<int>( vStart.at(0) ) * 60 + boost::lexical_cast<int>( vStart.at(1) );
	if( nTime < nCom )	return false;

	nCom = boost::lexical_cast<int>( vEnd.at(0) ) * 60 + boost::lexical_cast<int>( vEnd.at(1) );
	if( nTime > nCom )	return false;

	return true;
}

// 時間を取得する。取得する時間はsKeyで指定
std::vector< std::string > CStartUp::GetTime( const _TCHAR *sContents, const _TCHAR *sKey )
{
	std::vector< std::string > vTokened;
	std::string sTokened, str;

	if( !this->ReadInifile( sContents, sKey ))	return vTokened;
	str = this->GetIniData();

	// 分解する
	boost::char_separator<char> sep(":;：；");
	boost::tokenizer< boost::char_separator<char> > token( str , sep );
	BOOST_FOREACH( std::string sTokened, token )
		vTokened.push_back( sTokened );

	return vTokened;
}

// 実行する
_E_ERROR CStartUp::Execute( const _TCHAR *sContents, const _TCHAR *sKeyWord )
{

	int nPos = 1;
	while( true )
	{
		_TCHAR	sKey[MAX_PATH];
		sprintf_s( sKey, sizeof( sKey ), "%s%d", sKeyWord, nPos );

		if( this->ReadInifile( sContents, sKey ) )
//		if( this->ReadInifile( sContents, boost::lexical_cast<std::string>( sKeyWord + nPos ).c_str()) )
		{

			printf( "%s\n", this->GetIniData().c_str());
			HINSTANCE hins;

			hins = ShellExecute( NULL, "open", this->GetIniData().c_str(), NULL, NULL, SW_SHOWNA );
			nPos++;
			continue;
		}
		break;
	}

	return _E_NOERROR;
}