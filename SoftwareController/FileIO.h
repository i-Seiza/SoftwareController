#pragma once

// ファイル操作に関連する処理を記載する
#include "def.h"

class CFileIO
{
public:
	CFileIO(void);
	~CFileIO(void);

public:

	// ファイルを読む
	std::vector<std::string>	Read(const char *path);
	std::vector<std::wstring>	Read(const wchar_t *path);

	void	Write( std::string data, std::ios_base::open_mode mode, const char *path );
	void	Write(std::wstring data, std::ios_base::open_mode mode, const wchar_t *path);

	std::vector<std::tr2::sys::path>	FindFile(const std::tr2::sys::path path, const std::tr2::sys::path name);
	std::vector<std::wstring>			FindFile(const wchar_t * path, const wchar_t * name);
	std::vector<std::string>			FindFile( const char *path, const char *name );

	std::vector<std::string>			FindFolder( const char *path, const char *name );
	std::vector<std::wstring>			FindFolder(const wchar_t *path, const wchar_t *name);
	std::vector<std::tr2::sys::path>	FindFolder(const std::tr2::sys::path path, const std::tr2::sys::path name);
};
