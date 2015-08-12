#pragma once

#include "def.h"
#include "ArgBase.h"


class CArgument
{
public:
	CArgument(void);
	~CArgument(void);

private:

	CArgBase* GetClass( const char *path );

public:

	_E_ERROR	Open( const char *sKey, const _TCHAR *sContents,  std::vector< std::string > argv );
};
