#include "StdAfx.h"

#include "FileIO.h"


CFileIO::CFileIO(void)
{
}

CFileIO::~CFileIO(void)
{
}


// ファイルを開く
std::vector<std::string> CFileIO::Read( const char *path )
{
	std::vector< std::string > vec;

	std::ifstream is(path);

	for (std::string line; std::getline(is, line); )
	{
		vec.push_back(line);
	}

	return vec;
}
std::vector<std::wstring> CFileIO::Read(const wchar_t *path)
{
	std::vector< std::wstring > vec;

	std::wifstream is(path);

	for (std::wstring line; std::getline(is, line); )
	{
		vec.push_back(line);
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

void CFileIO::Write(std::wstring data, std::ios_base::open_mode mode, const wchar_t *path)
{
	std::wofstream ofs;
	ofs.open(path, mode);
	ofs << data << std::endl;
	ofs.close();
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