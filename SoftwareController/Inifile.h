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

	TCHAR	m_sIniFile[MAX_PATH];
	TCHAR	m_sContent[MAX_PATH];
	DATA	m_data;

	std::vector<tstring> m_vContent;

private:



	std::vector<tstring>		GetKeyName();
	boost::optional<tstring>	GetKeyName(tstring line);
	std::vector<KEY_DATA>		GetKeyData();
	boost::optional<KEY_DATA>	GetKeyData(tstring line);


public:
	
	void		ReadInifile( const TCHAR *sName, const TCHAR *sKey, const TCHAR *sDefault );
	void		WriteInifile( const TCHAR *sName, const TCHAR *sKey, const TCHAR *sContent );

	TCHAR*		GetContents();
	const TCHAR*	GetInifileName();
	void		ReadData();
	void		WriteData(DATA mData);
	DATA		GetData();


};
