#pragma once

#include "def.h"
#include "Inifile.h"

enum _E_ARG_KEY
{
	_START_UP,		// スタートアップ


	_KEY_FIN,

};


const _TCHAR sArgKey[][256] = 
{
	"start_up",
};



class CArgBase
{
public:
	CArgBase(void);
	~CArgBase(void);
private:
	
	std::string	m_sReadedIniData;

protected:

	bool		ReadInifile( const _TCHAR *sContents, const _TCHAR *sKey );
	std::string GetIniData();

	std::string Replace( std::string str1, std::string src, std::string dest );

public:

	virtual _E_ERROR Execute( const _TCHAR *sContents,  std::vector< std::string > argv );
};
