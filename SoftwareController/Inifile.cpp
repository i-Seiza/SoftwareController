#include "StdAfx.h"
#include "Inifile.h"
#include "FileIO.h"

#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

#include <boost/xpressive/xpressive.hpp>

CInifile::CInifile(void)
{
	// アプリ名を取得
	DWORD rc = GetModuleFileName( NULL, m_sIniFile, MAX_PATH );
	
	// iniファイル名取得

	for( size_t i = strlen(m_sIniFile) - 1 ; i >= 0 ; i-- )
	{
		if( m_sIniFile[i] != '.' ) continue;
		sprintf_s( &m_sIniFile[i], MAX_PATH, ".ini" );
		break;
	}

	memset( m_sContent, sizeof(m_sContent) , '\0' );
}

CInifile::~CInifile(void)
{
}

/////////////////////////////////////


// inifileを読む
void CInifile::ReadInifile( const char *sName, const char *sKey, const char *sDefault )
{
	// 
	GetPrivateProfileString( sName, sKey, sDefault, m_sContent, MAX_PATH, m_sIniFile );

}


char*	CInifile::GetContents()
{
	return m_sContent;
}

/////////////////////////////////////
// inifileを書く
void CInifile::WriteInifile( const char *sName, const char *sKey, const char *sContent )
{
	// 
	WritePrivateProfileString( sName, sKey, sContent, m_sIniFile );

}
/////////////////////////////////////
// inifile名を取得
const char* CInifile::GetInifileName()
{
	return m_sIniFile;
}
/////////////////////////////////////
// inifile情報を取得する（生データ）
void CInifile::ReadData()
{
	CFileIO io;
	std::vector< std::string > vec;
	vec = io.Read( m_sIniFile );
	std::vector< std::string >::iterator it = vec.begin();

	do
	{
		boost::regex re( "\\[(.*)\\]" );
		do{
			if( boost::regex_match( *it, re ) )	break;
		}while( ++it != vec.end() );
		
		if ( it == vec.end() )	break;
		CheckKey( it, vec.end()	);
	
	}while( it++ != vec.end() );
}

void CInifile::CheckKey( std::vector< std::string >::iterator it, std::vector< std::string >::iterator end )
{
	boost::regex re( "\\[(.*)\\]" );
	do{
		if( boost::regex_match( *it, re ) )	break;
	}while( ++it != end );


	boost::smatch result;
	boost::regex_search( std::string::const_iterator((*it).begin()), std::string::const_iterator((*it).end()), result, re );
	m_data.insert( std::make_pair(result.str(1), CheckName( ++it, end ) ));

}

std::vector< KEY_DATA > CInifile::CheckName( std::vector< std::string >::iterator it, std::vector< std::string >::iterator end )
{
	KEY_DATA	key;
	std::vector< KEY_DATA >	data;

	boost::regex rKey( "\\[(.*)\\]" );
	do{
		if( boost::regex_match( *it, rKey ) )	break;
		boost::regex re( "^\\s*(.*)\\s*\\=\\s*(.*)$" );
		if( boost::regex_match( *it, re )) 
		{
			boost::smatch result;
			boost::regex_search( std::string::const_iterator((*it).begin()), std::string::const_iterator((*it).end()), result, re );
			key.sKey = result.str(1);
			key.sData = result.str(2);
			data.push_back( key );
		}

	}while( ++it != end );

	return data;
}

std::map< std::string, std::vector< KEY_DATA >> CInifile::GetData()
{
	return m_data;
}

/////////////////////////////////////
// inifile情報を書き込みする（生データ）
void CInifile::WriteData(std::map< std::string, std::vector< KEY_DATA >> mData)
{
	std::map< std::string, std::vector< KEY_DATA >>::iterator mIt = mData.begin();
	std::vector< KEY_DATA >::iterator vIt;
	CFileIO io;
	io.Write( "", std::ios::out, m_sIniFile );

	while( mIt != mData.end() )
	{
		io.Write( "[" + (*mIt).first + "]", std::ios::out | std::ios::app, m_sIniFile );
		io.Write( "", std::ios::out | std::ios::app, m_sIniFile );

		vIt = (*mIt).second.begin();
		while( vIt != (*mIt).second.end() )
		{
			io.Write( (*vIt).sKey + " = " + (*vIt).sData, std::ios::out | std::ios::app, m_sIniFile );
			vIt++;
		}
		mIt++;

		io.Write( "", std::ios::out | std::ios::app, m_sIniFile );
	}





}