#pragma once

#include "def.h"
#include "ArgBase.h"

#include "StartUp.h"

const std::unordered_map<tstring, CArgBase*> ARG_MAP =
{
	{ _T("start_up"), new CStartUp() },
};


class CArgument
{
public:
	CArgument(void);
	~CArgument(void);

private:

	CArgBase* GetClass( const tstring path );

public:

	_E_ERROR	Open( const tstring sKey, const _TCHAR *sContents,  std::vector< tstring > argv );
};
