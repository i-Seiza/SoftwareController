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
	// ��ɋN������A�v���P�[�V����
	Execute( sContents, KEYWORD_STARTUP.at(_ALWAYS) );
	// �J�n-�I�����ԂɈ˂�A�v���P�[�V����
	if( IsExecutePossible( sContents ) )	Execute( sContents, KEYWORD_STARTUP.at(_POSSIBLE) );

	return _E_NOERROR;
}


///////////////////////////////
// Possible�̃A�v���P�[�V�������N�����邩
bool CStartUp::IsExecutePossible( const _TCHAR *sContents )
{
	// ���Ԃ��擾
	CExecuteTime vStart, vEnd;
	vStart = GetTime(sContents, KEYWORD_STARTUP.at(_START_TIME));
	vEnd = GetTime(sContents, KEYWORD_STARTUP.at(_END_TIME));

	// �`�F�b�N
	if (!vStart.IsInitialized())	return false;
	if (!vEnd.IsInitialized())		return false;

	// �{���̓��t���擾����
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();

	// ��r����
	int nTime = now.time_of_day().hours() * 60 + now.time_of_day().minutes();
	if (nTime < vStart.GetTotalMinites())	return false;
	if (nTime > vEnd.GetTotalMinites())	return false;

	return true;
}


// ���Ԃ��擾����B�擾���鎞�Ԃ�sKey�Ŏw��
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

	re = _T("(.*?)[:;�F�G](.*?)");
	if (std::regex_match(str, result, re))
	{
		KeyTime.SetHour(std::stoi(result.str(1)));
		KeyTime.SetMinites(std::stoi(result.str(2)));
	}
	
	return KeyTime;
}

// ���s����
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