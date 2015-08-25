#include "StdAfx.h"


#include "FileIO.h"
#include <locale>

//namespace fs = boost::filesystem;

CFileIO::CFileIO(void)
{
}

CFileIO::~CFileIO(void)
{
}


// ファイルを開く
std::vector< std::wstring> CFileIO::Read( const char *path )
{
	std::vector< std::wstring > vec;

#if 0
	//ifstreamの場合
	std::ifstream ifs(path);

	std::locale::global(std::locale("japanese"));
	_tsetlocale(LC_ALL, _T("Japanese"));

	std::wstring str;

	if (ifs.fail()) {
		return vec;
	}

	while (getline(ifs, str)) {
		vec.push_back(str);
	}
#endif // 0

	return vec;

}

std::vector<tstring> CFileIO::Read(const TCHAR * path)
{
	std::locale::global(std::locale("japanese"));
	_tsetlocale(LC_ALL, _T("Japanese"));
	std::locale::global(std::locale("japanese_japan.20932"));

	std::wstring str;

	std::wifstream in(path);
	std::getline(in, str);

	return std::vector<tstring>();
}

void CFileIO::Write( std::wstring data, std::ios_base::open_mode mode, const char *path )
{
#if 0
	std::ofstream ofs;
	ofs.open( path, mode );
	ofs << data << std::endl;
	ofs.close();
#endif
}

std::vector<std::tr2::sys::path> CFileIO::FindFile(const std::tr2::sys::path path, const std::tr2::sys::path name)
{
	std::vector<std::tr2::sys::path> list;
	std::tr2::sys::recursive_directory_iterator last;

	for (std::tr2::sys::recursive_directory_iterator it(path); it != last; ++it) {
		if (std::tr2::sys::is_regular_file(it->path())) { // ファイルなら...
			list.push_back(*it);
		}
	};

	return list;
}

std::vector<std::wstring> CFileIO::FindFile(const wchar_t *path, const wchar_t *name)
{
	std::vector<std::tr2::sys::path> list = FindFile(std::tr2::sys::path(path), std::tr2::sys::path(name));
	std::vector<std::wstring> vec;

	for (auto d : list)
	{
		vec.push_back(d.wstring());
	}

	return vec;
}
std::vector<std::string> CFileIO::FindFile( const char *path, const char *name )
{
	std::vector<std::tr2::sys::path> list = FindFile(std::tr2::sys::path(path), std::tr2::sys::path(name));
	std::vector<std::string> vec;

	for (auto d : list)
	{
		vec.push_back(d.string());
	}

	return vec;
}

std::vector<std::tr2::sys::path> CFileIO::FindFolder(const std::tr2::sys::path path, const std::tr2::sys::path name)
{
	std::vector<std::tr2::sys::path> list;
	std::tr2::sys::recursive_directory_iterator last;

	for (std::tr2::sys::recursive_directory_iterator it(path); it != last; ++it) {
		if (std::tr2::sys::is_directory(it->path())) { // ディレクトリなら...
			list.push_back(*it);
		}
	};

	return list;
}

std::vector<std::wstring> CFileIO::FindFolder(const wchar_t *path, const wchar_t *name)
{
	std::vector<std::tr2::sys::path> list = FindFolder(std::tr2::sys::path(path), std::tr2::sys::path(name));
	std::vector<std::wstring> vec;

	for (auto d : list)
	{
		vec.push_back(d.wstring());
	}

	return vec;
}

std::vector<std::string> CFileIO::FindFolder( const char *path, const char *name )
{
	std::vector<std::tr2::sys::path> list = FindFile(std::tr2::sys::path(path), std::tr2::sys::path(name));
	std::vector<std::string> vec;

	for (auto d : list)
	{
		vec.push_back(d.string());
	}

	return vec;
}