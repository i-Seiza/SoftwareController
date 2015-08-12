#pragma once

// iniファイルのクラス
#include "def.h"

typedef struct KEY_DATA{
	std::string	sKey;
	std::string	sData;
} KEY_DATA;



class CInifile
{
public:
	CInifile(void);
	~CInifile(void);

private:

	char	m_sIniFile[MAX_PATH];
	char	m_sContent[MAX_PATH];
	std::map< std::string, std::vector< KEY_DATA >>	m_data;

private:


	void CInifile::CheckKey( std::vector< std::string >::iterator it, std::vector< std::string >::iterator end );
	std::vector< KEY_DATA >	CInifile::CheckName( std::vector< std::string >::iterator it, std::vector< std::string >::iterator end );

public:
	
	void		ReadInifile( const char *sName, const char *sKey, const char *sDefault );
	void		WriteInifile( const char *sName, const char *sKey, const char *sContent );
	char*		GetContents();
	const char* GetInifileName();
	void		ReadData();
	void		WriteData(std::map< std::string, std::vector< KEY_DATA >> mData);
	std::map< std::string, std::vector< KEY_DATA >> GetData();




};
