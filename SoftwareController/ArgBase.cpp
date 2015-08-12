#include "StdAfx.h"
#include "ArgBase.h"

CArgBase::CArgBase(void)
{
	m_sReadedIniData = "";
}

CArgBase::~CArgBase(void)
{
}

///////////////////////////////
_E_ERROR CArgBase::Execute( const _TCHAR *sContents,  std::vector< std::string > argv )
{

	return _E_NOERROR;
}

///////////////////////////////
// Iniファイルから値を取得する
bool CArgBase::ReadInifile( const _TCHAR *sContents, const _TCHAR *sKey )
{
	m_sReadedIniData = "";

	CInifile ini;
	ini.ReadInifile( sContents, sKey, "" );
	if( strlen( ini.GetContents() )	<= 0 )	return false;

	m_sReadedIniData = ini.GetContents();
	return true;
}

std::string CArgBase::GetIniData()
{
	return m_sReadedIniData;
}

std::string CArgBase::Replace( std::string str1, std::string src, std::string dest )
{
	std::string::size_type  Pos( str1.find( src ) );
	while( Pos != std::string::npos )
	{
		str1.replace( Pos, src.length(), dest );
		Pos = str1.find( src, Pos + dest.length() );
	}
	return str1;

}
