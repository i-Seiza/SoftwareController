// SoftwareController.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "def.h"
#include "SoftwareController.h"
#include "Argument.h"
#include <boost/lexical_cast.hpp>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �B��̃A�v���P�[�V���� �I�u�W�F�N�g�ł��B

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// MFC �����������āA�G���[�̏ꍇ�͌��ʂ�������܂��B
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: �K�v�ɉ����ăG���[ �R�[�h��ύX���Ă��������B
		_tprintf(_T("�v���I�ȃG���[: MFC �̏��������ł��܂���ł����B\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: �A�v���P�[�V�����̓�����L�q����R�[�h�������ɑ}�����Ă��������B
		std::wcout.imbue(std::locale("japanese"));
		// �������Ȃ��ƃG���[�ɂ���
		if( argc < 2 )
		{
			return -1;
		}

		CInifile ini;

		// ������ǂ�
		ini.ReadInifile( "argument", argv[1], "" );
	
		std::vector< std::string > vec;
		for ( int i = 0; i < argc; i++ )
		{
			vec.push_back( argv[i] );
		}


		// �����t������
		CArgument arg;
		arg.Open( argv[1], ini.GetContents(), vec );
	}

	return nRetCode;
}
