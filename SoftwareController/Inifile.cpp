#include "StdAfx.h"
#include "Inifile.h"
#include "FileIO.h"


CInifile::CInifile(void):
m_sContent(boost::none),
m_default(tstring())
{
	// �A�v�������擾
	TCHAR exe[MAX_PATH];
	DWORD rc = GetModuleFileName(NULL, exe, MAX_PATH);

	// ini�t�@�C�����擾
	m_sIniFile = exe;
	std::experimental::filesystem::path extension = std::experimental::filesystem::path(exe).extension();
	m_sIniFile.replace_extension(".ini");
}

CInifile::~CInifile(void)
{
}

/////////////////////////////////////
/* inifile��ǂ�
AppName: �Z�N�V������
sKey�F �L�[��
*/
void CInifile::ReadInifile( const TCHAR *AppName, const TCHAR *sKey, const TCHAR *sDefault )
{
	m_default = sDefault;

	TCHAR content[MAX_PATH];
	DWORD len = GetPrivateProfileString(AppName, sKey, sDefault, content, MAX_PATH, m_sIniFile.c_str());
	if (len > 0)
	{
		m_sContent = content;
	}
}

/*
Ini�t�@�C���ǂݍ��ݐ������ǂ���
true: ����
false: ���s
*/
bool CInifile::IsSccuess()
{
	return m_sContent.is_initialized();
}

/*
Ini�t�@�C���Ǎ����ʂ𔽉f����
�ǂݍ��݌��ʂ����s���Ă���ꍇ��ReadIniFile�Ŏw�肳�ꂽdefault�l�𔽉f����
*/
tstring	CInifile::GetContents()
{
	return m_sContent.get_value_or(m_default);
}

/////////////////////////////////////
// inifile������
void CInifile::WriteInifile( const TCHAR *sName, const TCHAR *sKey, const TCHAR *sContent )
{
	WritePrivateProfileString(sName, sKey, sContent, m_sIniFile.c_str());

}
/////////////////////////////////////
// inifile�����擾
const TCHAR* CInifile::GetInifileName()
{
	return m_sIniFile.c_str();
}

std::experimental::filesystem::path CInifile::GetPath()
{
	return m_sIniFile.parent_path();
}

/////////////////////////////////////
// inifile�����擾����i���f�[�^�j
void CInifile::ReadData()
{
	CFileIO io;
	m_vContent = io.Read(GetInifileName());

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
// inifile�����������݂���i���f�[�^�j
void CInifile::WriteData(DATA mData)
{
	CFileIO io;
	for (auto data : mData)
	{
		io.Write(_T("[") + data.first + _T("]"), std::ios::out | std::ios::app, GetInifileName());

		for (auto content : data.second)
		{
			io.Write(content.sKey + _T("=") + content.sData, std::ios::out | std::ios::app, GetInifileName());
		}
		io.Write(_T(""), std::ios::out | std::ios::app, GetInifileName());
	}
}