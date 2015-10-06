#include "stdafx.h"
#include "GitLog.h"
#include "Inifile.h"
#include "Clipboard.h"

GitLog::GitLog()
{
	path.reset(new PathCommand(_T("BizPath")));
	main.reset(new MainCommand(_T("git_log")));
	result.reset(new ResultCommand(GetResultFile()));
}


GitLog::~GitLog()
{
}

_E_ERROR GitLogManager::Execute(const _TCHAR * sContents, std::vector<tstring> argv)
{
	_E_ERROR rc = log.Execute(sContents, argv);
	if (rc != _E_NOERROR)	return rc;

	rc = clip.Execute(sContents, argv);
	return rc;
}

