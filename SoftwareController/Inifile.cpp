#include "StdAfx.h"
#include "Inifile.h"
#include "FileIO.h"


CInifile::CInifile(void)
{
	// アプリ名を取得
#ifdef _UNICODE
	DWORD rc = GetModuleFileNameW(NULL, m_sIniFile, MAX_PATH);
#else
	DWORD rc = GetModuleFileName(NULL, m_sIniFile, MAX_PATH);
#endif

	// iniファイル名取得
	std::experimental::filesystem::path p(m_sIniFile);
	std::experimental::filesystem::path extension = std::experimental::filesystem::path(m_sIniFile).extension();
	p.replace_extension(".ini");

#ifdef _UNICODE
	swprintf_s( m_sIniFile, MAX_PATH, p.wstring().c_str());
#else
	sprintf_s(m_sIniFile, MAX_PATH, p.wstring().c_str());
#endif
}

CInifile::~CInifile(void)
{
}

/////////////////////////////////////


// inifileを読む
void CInifile::ReadInifile( const TCHAR *sName, const TCHAR *sKey, const TCHAR *sDefault )
{
#ifdef _UNICODE
	GetPrivateProfileStringW(sName, sKey, sDefault, m_sContent, MAX_PATH, m_sIniFile);
#else
	GetPrivateProfileString( sName, sKey, sDefault, m_sContent, MAX_PATH, m_sIniFile );
#endif

}


TCHAR*	CInifile::GetContents()
{
	return m_sContent;
}

/////////////////////////////////////
// inifileを書く
void CInifile::WriteInifile( const TCHAR *sName, const TCHAR *sKey, const TCHAR *sContent )
{
#ifdef _UNICODE
	WritePrivateProfileStringW(sName, sKey, sContent, m_sIniFile);
#else
	WritePrivateProfileString(sName, sKey, sContent, m_sIniFile);
#endif

}
/////////////////////////////////////
// inifile名を取得
const TCHAR* CInifile::GetInifileName()
{
	return m_sIniFile;
}

/////////////////////////////////////
// inifile情報を取得する（生データ）
void CInifile::ReadData()
{
	CFileIO io;
	m_vContent = io.Read(m_sIniFile);

	std::vector<tstring> keys = GetKeyName();
	std::vector<KEY_DATA> datas = GetKeyData();

	for (auto key : keys)
	{
		for ( auto data : datas)
		{
			ReadInifile(key.c_str(), data.sKey.c_str(), _T(""));
			if (tstring(GetContents()).size())
			{
				DATA::iterator it = m_data.find(key);
				if (it != m_data.end())
				{
					(*it).second.push_back(data);
				}
				else
				{
					m_data.insert(std::make_pair(key, std::vector<KEY_DATA>{ data }));
				}
			}
		}
	}
}

std::vector<tstring> CInifile::GetKeyName()
{
	std::vector<tstring> keys;
	for (auto line : m_vContent)
	{
		boost::optional<tstring> key = GetKeyName(line);
		if (key.is_initialized())
		{
			keys.push_back(*key);
		}
	}

	return keys;
}

boost::optional<tstring> CInifile::GetKeyName(tstring line)
{
#if UNICODE
	std::wregex re;
	std::wsmatch result;
#else
	std::regex re;
	std::smatch result;
#endif

	re = _T("\\[(.*)\\]");
	boost::optional<tstring> keyName = boost::none;
	if (std::regex_match(line, result, re))
	{
		keyName = result.str(1);
	}
	return keyName;
}

std::vector<KEY_DATA> CInifile::GetKeyData()
{
	std::vector <KEY_DATA> datas;
	for (auto line : m_vContent)
	{
		boost::optional<KEY_DATA> data = GetKeyData(line);
		if (data.is_initialized())
		{
			datas.push_back(*data);
		}
	}
	return datas;
}

boost::optional<KEY_DATA> CInifile::GetKeyData(tstring line)
{
#if UNICODE
	std::wregex re;
	std::wsmatch result;
#else
	std::regex re;
	std::smatch result;
#endif

	re = _T("^\\s*(.*)\\s*\\=\\s*(.*)$");
	boost::optional<KEY_DATA> keyData= boost::none;

	if (std::regex_match(line, result, re))
	{
		KEY_DATA data;
		data.sKey = result.str(1);
		data.sData = result.str(2);
		keyData = data;
	}

	return keyData;
}

CInifile::DATA CInifile::GetData()
{
	return m_data;
}

/////////////////////////////////////
// inifile情報を書き込みする（生データ）
void CInifile::WriteData(DATA mData)
{
	CFileIO io;
	for (auto data : mData)
	{
		io.Write(_T("[") + data.first + _T("]"), std::ios::out | std::ios::app, m_sIniFile);

		for (auto content : data.second)
		{
			io.Write(content.sKey + _T("=") + content.sData, std::ios::out | std::ios::app, m_sIniFile);
		}
		io.Write(_T(""), std::ios::out | std::ios::app, m_sIniFile);
	}
}