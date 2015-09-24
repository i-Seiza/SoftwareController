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
���ʃt�@�C���͎��s�t�@�C���Ɠ����t�H���_�ɔz�u����
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
// ���ʃt�@�C�����J��
bool CommandBase::OpenResultFile()
{
	// �T�N���G�f�B�^�ŊJ��
	::ShellExecute(nullptr, nullptr, _T("sakura"), GetResultFile().c_str(), nullptr, SW_NORMAL);
	return false;
}

// �R�}���h���s
_E_ERROR CommandBase::ExecuteCommand()
{
	SHELLEXECUTEINFO	sei = { 0 };
	//�\���̂̃T�C�Y
	sei.cbSize = sizeof(SHELLEXECUTEINFO);
	//�N�����̃E�C���h�E�n���h��
	sei.hwnd = nullptr;
	//�N����̕\�����
	sei.nShow = SW_SHOWNORMAL;
	//���̃p�����[�^���d�v�ŁA�Z�b�g���Ȃ���SHELLEXECUTEINFO�\���̂�hProcess�����o���Z�b�g����Ȃ��B
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	//�N���v���O����
	sei.lpFile = GetCommandFile();
	//�v���Z�X�N��
	if (!ShellExecuteEx(&sei) || (const int)sei.hInstApp <= 32) {
		return _E_EXEC_ERROR;
	}
	//�I����҂�
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

	// �R�}���h�擾
	tstring dir = GetCommand();

	// �R�}���h�����o��
	io.Write(dir.c_str(), std::ios_base::out, GetCommandFile());

	// ���s
	_E_ERROR rc = ExecuteCommand();
	if (rc != _E_NOERROR)	return rc;

	// ���ʁc
	//std::vector<tstring> re = io.Read(GetResultFile().c_str());
	OpenResultFile();
	return _E_NOERROR;
}
