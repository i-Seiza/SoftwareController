#pragma once
#include "ArgBase.h"

/*
	�R�}���h�����s����N���X
	-> �R�}���h�����s����t�@�C�����쐬����
	-> ���ʂ�ҋ@
	-> ���ʂ�ێ�
	 -> ���ʂ��ǂ��g�����͌p����Ō��߂�
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

