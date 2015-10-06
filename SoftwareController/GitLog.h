#pragma once
#include "CommandBase.h"

class GitLog :
	public CommandBase
{
public:
	GitLog();
	~GitLog();

};

class GitLogManager :
	public ExecuteBase
{
public:


private:
	GitLog log;
	ExecuteClipboad clip;

public:

	virtual		_E_ERROR Execute(const _TCHAR *sContents, std::vector< tstring > argv);


};

