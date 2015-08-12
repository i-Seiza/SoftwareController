// SoftwareController.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "def.h"
#include "SoftwareController.h"
#include "Argument.h"
#include <boost/lexical_cast.hpp>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一のアプリケーション オブジェクトです。

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// MFC を初期化して、エラーの場合は結果を印刷します。
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: 必要に応じてエラー コードを変更してください。
		_tprintf(_T("致命的なエラー: MFC の初期化ができませんでした。\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: アプリケーションの動作を記述するコードをここに挿入してください。
		std::wcout.imbue(std::locale("japanese"));
		// 引数がないとエラーにする
		if( argc < 2 )
		{
			return -1;
		}

		CInifile ini;

		// 引数を読む
		ini.ReadInifile( "argument", argv[1], "" );
	
		std::vector< std::string > vec;
		for ( int i = 0; i < argc; i++ )
		{
			vec.push_back( argv[i] );
		}


		// 引数付き処理
		CArgument arg;
		arg.Open( argv[1], ini.GetContents(), vec );
	}

	return nRetCode;
}
