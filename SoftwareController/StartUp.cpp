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
	// ��ɋN������A�v���P�[�V����
	Execute( sContents, sKeyWord_StartUp[_ALWAYS] );
	// �J�n-�I�����ԂɈ˂�A�v���P�[�V����
	if( IsExecutePossible( sContents ) )	Execute( sContents, sKeyWord_StartUp[_POSSIBLE] );

	return _E_NOERROR;
}


///////////////////////////////
// Possible�̃A�v���P�[�V�������N�����邩
bool CStartUp::IsExecutePossible( const _TCHAR *sContents )
{
	// �{���̓��t���擾����
	struct tm ltm;
	time_t t_time;

	time( &t_time );	// �V�X�e�����Ԃ��擾
	localtime_s( &ltm, &t_time );	// ���[�J�����Ԃ��擾

	// ���Ԃ��擾
	std::vector<std::string> vStart, vEnd;
	vStart = GetTime( sContents, sKeyWord_StartUp[_START_TIME] );
	vEnd = GetTime( sContents, sKeyWord_StartUp[_END_TIME] );

	// �`�F�b�N
	if( vStart.size() < 2 )	return false;
	if( vEnd.size() < 2 )	return false;

	// ��r����
	int nTime = ltm.tm_hour * 60 + ltm.tm_min;
	int nCom = boost::lexical_cast<int>( vStart.at(0) ) * 60 + boost::lexical_cast<int>( vStart.at(1) );
	if( nTime < nCom )	return false;

	nCom = boost::lexical_cast<int>( vEnd.at(0) ) * 60 + boost::lexical_cast<int>( vEnd.at(1) );
	if( nTime > nCom )	return false;

	return true;
}

// ���Ԃ��擾����B�擾���鎞�Ԃ�sKey�Ŏw��
std::vector< std::string > CStartUp::GetTime( const _TCHAR *sContents, const _TCHAR *sKey )
{
	std::vector< std::string > vTokened;
	std::string sTokened, str;

	if( !this->ReadInifile( sContents, sKey ))	return vTokened;
	str = this->GetIniData();

	// ��������
	boost::char_separator<char> sep(":;�F�G");
	boost::tokenizer< boost::char_separator<char> > token( str , sep );
	BOOST_FOREACH( std::string sTokened, token )
		vTokened.push_back( sTokened );

	return vTokened;
}

// ���s����
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