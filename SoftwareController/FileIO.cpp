#include "StdAfx.h"


#include "FileIO.h"
#include <locale>

namespace fs = boost::filesystem;

CFileIO::CFileIO(void)
{
}

CFileIO::~CFileIO(void)
{
}


// ファイルを開く
std::vector< std::string> CFileIO::Read( const char *path )
{
	//ifstreamの場合
	std::ifstream ifs( path );

	std::locale::global(std::locale("japanese"));
	_tsetlocale(LC_ALL, _T("Japanese"));

	std::string str;
	std::vector< std::string > vec;

	if(ifs.fail()) {
		return vec;
	}

	while(getline(ifs, str)) {
		vec.push_back( str );
	}
	return vec;
}

void CFileIO::Write( std::string data, std::ios_base::open_mode mode, const char *path )
{
	std::ofstream ofs;
	ofs.open( path, mode );
	ofs << data << std::endl;
	ofs.close();
}

std::vector<std::string> CFileIO::FindFile( const char *path, const char *name )
{
	CFileFind filefind;
	BOOL bNext = FALSE;
	std::vector<std::string> vec;

	// 指定したファイルまたはフォルダが存在しない場合は抜ける
	if( !boost::filesystem::exists( path ))	return vec;

	// 指定したものはファイルか？
	if( !boost::filesystem::is_directory( path ))	return vec;

	std::string str = std::string( path ) + std::string( "\\*.*" );

	if( filefind.FindFile( str.c_str() ) )
	{
		
		do
		{
			bNext = filefind.FindNextFile();

			TRACE("%s : %s\n", filefind.GetFileName().GetBuffer(), filefind.GetFilePath().GetBuffer() );

			if( filefind.IsDots() || filefind.GetFileName() == ".svn" || filefind.GetFileName() == ".git" ) {
				continue;
			}
			else if( filefind.IsDirectory() ) {
				std::vector<std::string> add = FindFile( filefind.GetFilePath().GetBuffer(), name );
				std::vector<std::string>::iterator it = add.begin();
				while( it != add.end() )
				{
					vec.push_back( *it );
					it++;
				}

			} else if( filefind.GetFileName().Compare( name ) == 0 ) {
				vec.push_back( filefind.GetFilePath().GetBuffer() );
			}

		}while( bNext );

			
		filefind.Close();
	}

	return vec;
}

std::vector<std::string> CFileIO::FindFolder( const char *path, const char *name )
{
	std::vector<std::string> vec;


	// 指定したファイルまたはフォルダが存在しない場合は抜ける
	if( !boost::filesystem::exists( path ))	return vec;

	// 指定したものはファイルか？
	if( !boost::filesystem::is_directory( path ))	return vec;

	const fs::path fsPath( path );
	BOOST_FOREACH(const fs::path& p, std::make_pair(fs::recursive_directory_iterator(fsPath),
													fs::recursive_directory_iterator())) {
		if ( fs::is_directory(p) && p.filename() == name )
		{
			vec.push_back( p.string() );
		}
	}

	return vec;
}