#pragma once
#include "ArgBase.h"
#include "BatchCommand.h"




/*
パス情報をiniファイルから取得する
カラム： "path"
sKey: 取得したいパス情報のキー名
*/
class PathCommand : public BatchCommand
{

public:
	PathCommand(){}
	PathCommand(tstring sKey)
	{
		pre = _T("cd ");
		main = GetValueFromSettingfile(_T("path"), sKey);
		post = _T("\n");
	}
	~PathCommand() {}
	
};

/*
メインの処理情報をiniファイルから取得する
カラム： "command1"/"commadn2"/…
sKey: 取得したいパス情報のキー名
*/
class MainCommand : public BatchCommand
{
private:

	boost::optional<tstring> GetCommandMain(const TCHAR *appName, int nPos)
	{
		tstring key;
		key.append(_T("command"));
		key.append(toString(nPos));

		CInifile ini;
		ini.ReadInifile(appName, key.c_str(), _T(""));
		if (!ini.IsSccuess())	return boost::none;

		return ini.GetContents();

	}
public:
	MainCommand() {}
	MainCommand(tstring sKey)
	{
		size_t nPos = 1;
		while (true)
		{
			boost::optional<tstring> line = GetCommandMain(sKey.c_str(), nPos);
			if (line.is_initialized())
			{
				if(!main.IsEmpty())	main += _T("\n");
				main += *line;
				initialize = true;
				nPos++;
			}
			else
			{
				break;
			}

		}
	}
	~MainCommand() {}

};

/*
結果ファイル書き出す必要がある場合、結果ファイルを登録する
*/
class ResultCommand : public BatchCommand
{
public:
	ResultCommand() {}
	ResultCommand(tstring sKey)
	{
		main = sKey;
		if (main.size())
		{
			post = _T(" > ");
		}
	}
	~ResultCommand() {}

};


class ExecuteBase : public CArgBase
{
protected:
	tstring GetResultFile() const;

public:

	virtual		_E_ERROR Execute(const _TCHAR *sContents, std::vector< tstring > argv) = 0;
};

class CommandBase :
	public ExecuteBase
{
public:
	CommandBase();
	~CommandBase();

protected:


	std::unique_ptr<PathCommand> path;
	std::unique_ptr<MainCommand> main;
	std::unique_ptr<ResultCommand> result;

	_TCHAR* GetCommandFile() const { return _T("command.bat"); }
	bool OpenResultFile();
	_E_ERROR ExecuteCommand();
	virtual tstring GetCommand();

public:
	_E_ERROR Execute(const _TCHAR *sContents, std::vector< tstring > argv);

};

class ExecuteClipboad : public ExecuteBase
{
public:
	_E_ERROR Execute(const _TCHAR *sContents, std::vector< tstring > argv);

};
