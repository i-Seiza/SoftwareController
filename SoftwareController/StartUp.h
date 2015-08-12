#pragma once
#include "argbase.h"

enum {
	_ALWAYS,
	_POSSIBLE,
	_START_TIME,
	_END_TIME,


	_START_UP_FIN,
};

const _TCHAR sKeyWord_StartUp[_START_UP_FIN][256] = 
{
	"Always",
	"Possible",
	"start_time",
	"end_time",
};

class CStartUp :
	public CArgBase
{
public:
	CStartUp(void);
	~CStartUp(void);

private:

	bool		IsExecutePossible( const _TCHAR *sContents );
	std::vector< std::string > CStartUp::GetTime( const _TCHAR *sContents, const _TCHAR *sKey );
	_E_ERROR	Execute( const _TCHAR *sContents, const _TCHAR *sKey );


public:
	_E_ERROR Execute( const _TCHAR *sContents,  std::vector< std::string > argv );

};
