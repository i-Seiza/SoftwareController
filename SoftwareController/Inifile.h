#pragma once

// iniファイルのクラス
#include "def.h"
#include <boost/optional.hpp>


typedef struct KEY_DATA{
	tstring	sKey;
	tstring	sData;
} KEY_DATA;



class CInifile
{
	typedef std::map<tstring, std::vector<KEY_DATA>> DATA;

public:
	CInifile(void);
	~CInifile(void);

private:

	std::experimental::filesystem::path m_sIniFile;
	boost::optional<tstring>	m_sContent;
	tstring						m_default;
	DATA	m_data;

	std::vector<tstring> m_vContent;

private:



	std::vector<tstring>		GetKeyName();
	boost::optional<tstring>	GetKeyName(tstring line);
	std::vector<KEY_DATA>		GetKeyData();
	boost::optional<KEY_DATA>	GetKeyData(tstring line);


public:
	
	void		ReadInifile( const TCHAR *sName, const TCHAR *sKey, const TCHAR *sDefault );
	bool IsSccuess();
	void		WriteInifile( const TCHAR *sName, const TCHAR *sKey, const TCHAR *sContent );

	tstring		GetContents();
	const TCHAR*	GetInifileName();
	std::experimental::filesystem::path GetPath();
	void		ReadData();
	void		WriteData(DATA mData);
	DATA		GetData();


};
