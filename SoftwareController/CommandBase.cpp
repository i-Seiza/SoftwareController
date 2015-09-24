#include "stdafx.h"
#include "CommandBase.h"

#include "FileIO.h"
#include "Inifile.h"


CommandBase::CommandBase()
{
	path.reset(new PathCommand(_T("")));
	main.reset(new MainCommand(_T("")));
	close.reset(new CloseCommand(GetResultFile()));
}


CommandBase::~CommandBase()
{
}

/*
結果ファイルは実行ファイルと同じフォルダに配置する
*/
tstring CommandBase::GetResultFile() const
{
	tstring name;
	CInifile ini;
	name.append(ini.GetPath());
	name.append(_T("\\result.txt"));
	return name.c_str();
}

///////////////////////////
// 結果ファイルを開く
bool CommandBase::OpenResultFile()
{
	// サクラエディタで開く
	::ShellExecute(nullptr, nullptr, _T("sakura"), GetResultFile().c_str(), nullptr, SW_NORMAL);
	return false;
}

// コマンド実行
_E_ERROR CommandBase::ExecuteCommand()
{
	SHELLEXECUTEINFO	sei = { 0 };
	//構造体のサイズ
	sei.cbSize = sizeof(SHELLEXECUTEINFO);
	//起動側のウインドウハンドル
	sei.hwnd = nullptr;
	//起動後の表示状態
	sei.nShow = SW_SHOWNORMAL;
	//このパラメータが重要で、セットしないとSHELLEXECUTEINFO構造体のhProcessメンバがセットされない。
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	//起動プログラム
	sei.lpFile = GetCommandFile();
	//プロセス起動
	if (!ShellExecuteEx(&sei) || (const int)sei.hInstApp <= 32) {
		return _E_EXEC_ERROR;
	}
	//終了を待つ
	WaitForSingleObject(sei.hProcess, INFINITE);

	return _E_NOERROR;
}

///////////////////////////
tstring CommandBase::GetCommand()
{
	tstring command;
	command.append(path->GetCommand());
	command.append(main->GetCommand());
	command.append(close->GetCommand());
	return command;
}

_E_ERROR CommandBase::Execute(const _TCHAR * sContents, std::vector<tstring> argv)
{
	CFileIO io;

	// コマンド取得
	tstring dir = GetCommand();

	// コマンド書き出し
	io.Write(dir.c_str(), std::ios_base::out, GetCommandFile());

	// 実行
	_E_ERROR rc = ExecuteCommand();
	if (rc != _E_NOERROR)	return rc;

	// 結果…
	//std::vector<tstring> re = io.Read(GetResultFile().c_str());
	OpenResultFile();
	return _E_NOERROR;
}
