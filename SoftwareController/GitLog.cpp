#include "stdafx.h"
#include "GitLog.h"
#include "Inifile.h"


GitLog::GitLog()
{
}


GitLog::~GitLog()
{
}

tstring GitLog::GetCommand()
{
	tstring command;

	CInifile ini;
	ini.ReadInifile(_T("command"), _T("git_log"), _T(""));
	if (!ini.IsSccuess())	return command;
	tstring log = ini.GetContents();

	boost::optional<tstring> path = GetPathCommand(_T("BizPath"));
	if (!path.is_initialized())	return  command;

	command.append(tstring(_T("cd ")));
	command.append(*path);
	command.append(tstring(_T("\n")));
	command.append(log);
	command.append(_T(" > "));
	command.append(GetResultFile());

	return command;
}
