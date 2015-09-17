#pragma once
#include "ArgBase.h"

/*
	コマンドを実行するクラス
	-> コマンドを実行するファイルを作成する
	-> 結果を待機
	-> 結果を保持
	 -> 結果をどう使うかは継承先で決める
*/

class CommandBase :
	public CArgBase
{
public:
	CommandBase();
	~CommandBase();

protected:
	_TCHAR* GetCommandFile() const { return _T("command.bat"); }
	tstring GetResultFile() const;
	bool OpenResultFile();
	_E_ERROR ExecuteCommand();
	virtual tstring GetCommand();

	boost::optional<tstring> GetPathCommand(const TCHAR *sKey);

public:
	_E_ERROR Execute(const _TCHAR *sContents, std::vector< tstring > argv);

};

