#pragma once

#include "def.h"
#include "ArgBase.h"

#include "StartUp.h"
#include "CommandBase.h"
#include "GitLog.h"

const std::unordered_map<tstring, CArgBase*> ARG_MAP =
{
	{ _T("start_up"), new CStartUp() },
	{ _T("command"), new CommandBase() },
	{ _T("git_log"), new GitLog() },
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
