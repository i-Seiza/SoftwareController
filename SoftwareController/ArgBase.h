#pragma once

#include "def.h"
#include "Inifile.h"

enum _E_ARG_KEY
{
	_START_UP,		// スタートアップ


	_KEY_FIN,

};

class CArgBase
{
public:
	CArgBase(void);
	~CArgBase(void);
private:
	
	tstring	m_sReadedIniData;

protected:

	bool		ReadInifile( const _TCHAR *sContents, const _TCHAR *sKey );
	tstring		GetIniData();

	tstring		Replace( tstring str1, tstring src, tstring dest );

public:

	virtual		_E_ERROR Execute( const _TCHAR *sContents,  std::vector< tstring > argv );
};
