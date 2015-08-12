#pragma once

// ファイル操作に関連する処理を記載する
#include "def.h"

class CFileIO
{
public:
	CFileIO(void);
	~CFileIO(void);

public:
	std::vector< std::string>	Read( const char *path );	// ファイルを読む
	void						Write( std::string data, std::ios_base::open_mode mode, const char *path );
	std::vector<std::string> CFileIO::FindFile( const char *path, const char *name );
	std::vector<std::string> CFileIO::FindFolder( const char *path, const char *name );
};
