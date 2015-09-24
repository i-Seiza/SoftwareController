#include "stdafx.h"
#include "GitLog.h"
#include "Inifile.h"


GitLog::GitLog()
{
	path.reset(new PathCommand(_T("BizPath")));
	main.reset(new MainCommand(_T("git_log")));
	close.reset(new CloseCommand(GetResultFile()));
}


GitLog::~GitLog()
{
}


