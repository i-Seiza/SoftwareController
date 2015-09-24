#pragma once
#include "ArgBase.h"

/*
	コマンドを実行するクラス
	-> コマンドを実行するファイルを作成する
	-> 結果を待機
	-> 結果を保持
	 -> 結果をどう使うかは継承先で決める
*/
template<class X> class value 
{
public:

	value() {}
	~value() {}

	void set(X v) { data += v; }
	X get() { return data; }

private:
	X data;
};

/*
パス情報をiniファイルから取得する
カラム： "path"
sKey: 取得したいパス情報のキー名
*/
class PathCommand
{
private:
	value<tstring> path;
	bool initialize;

public:
	PathCommand(){}
	PathCommand(tstring sKey)
	{
		CInifile ini;
		ini.ReadInifile(_T("path"), sKey.c_str(), _T(""));
		if (ini.IsSccuess())
		{
			path.set(ini.GetContents());
			initialize = true;
		}
	}
	~PathCommand() {}

	tstring GetCommand()
	{
		tstring command;
		if (initialize)
		{
			command.append(_T("cd "));
			command.append(path.get());
			command.append(_T("\n"));
		}
		return command;
	}
};

class MainCommand
{
private:
	value<tstring> main;
	bool initialize;


	boost::optional<tstring> GetCommand(const TCHAR *appName, int nPos)
	{
		tstring key;
		key.append(_T("command"));
#ifdef _UNICODE
		key.append(std::to_wstring(nPos));
#else
		key.append(std::to_string(nPos));
#endif

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
			boost::optional<tstring> line = GetCommand(sKey.c_str(), nPos);
			if (line.is_initialized())
			{
				if(!main.get().empty())	main.set(_T("\n"));
				main.set(*line);
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

	tstring GetCommand()
	{
		tstring command;
		if (initialize)
		{
			command.append(main.get());
		}
		return command;
	}
};

class CloseCommand
{
private:
	value<tstring> close;
	bool initialize;

public:
	CloseCommand() {}
	CloseCommand(tstring sKey)
	{
		close.set(sKey);
		initialize = true;
	}
	~CloseCommand() {}

	tstring GetCommand()
	{
		tstring command;
		if (initialize)
		{
			command.append(_T(" > "));
			command.append(close.get());
		}
		return command;
	}
};

class CommandBase :
	public CArgBase
{
public:
	CommandBase();
	~CommandBase();

protected:


	std::unique_ptr<PathCommand> path;
	std::unique_ptr<MainCommand> main;
	std::unique_ptr<CloseCommand> close;



	_TCHAR* GetCommandFile() const { return _T("command.bat"); }
	tstring GetResultFile() const;
	bool OpenResultFile();
	_E_ERROR ExecuteCommand();
	virtual tstring GetCommand();

public:
	_E_ERROR Execute(const _TCHAR *sContents, std::vector< tstring > argv);

};

