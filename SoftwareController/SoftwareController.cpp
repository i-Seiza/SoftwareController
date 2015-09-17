// SoftwareController.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "def.h"
#include "Inifile.h"
#include "CommandBase.h"

#include "FileIO.h"
#include "Argument.h"

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	std::wstring numericalPassword;
	if (numericalPassword.empty())
	{
		int i = 0;
	}
	std::vector<tstring> v;
	for (int i = 0; i < argc; i++)
	{
		v.push_back(argv[i]);
	}

	//CommandBase c;
	//c.Execute(argv[1], v);
	CArgument arg;
	arg.Open(argv[1], _T("argument"), v);

	return 0;
}

