#pragma once

// �t�@�C������Ɋ֘A���鏈�����L�ڂ���
#include "def.h"

class CFileIO
{
public:
	CFileIO(void);
	~CFileIO(void);

public:
	std::vector< std::wstring>	Read(const char *path);	// �t�@�C����ǂ�
	//std::vector< std::wstring>	Read(const TCHAR *path);	// �t�@�C����ǂ�
	std::vector<tstring>	Read(const TCHAR *path);	// �t�@�C����ǂ�
	void						Write( std::wstring data, std::ios_base::open_mode mode, const char *path );

	std::vector<std::tr2::sys::path>	FindFile(const std::tr2::sys::path path, const std::tr2::sys::path name);
	std::vector<std::wstring>			FindFile(const wchar_t * path, const wchar_t * name);
	std::vector<std::string>			FindFile( const char *path, const char *name );

	std::vector<std::string>			FindFolder( const char *path, const char *name );
	std::vector<std::wstring>			FindFolder(const wchar_t *path, const wchar_t *name);
	std::vector<std::tr2::sys::path>	FindFolder(const std::tr2::sys::path path, const std::tr2::sys::path name);
};
