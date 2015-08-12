#include "StdAfx.h"
#include "Argument.h"


#include "argbase.h"
#include "StartUp.h"

CArgument::CArgument(void)
{
}

CArgument::~CArgument(void)
{
}

///////////////////////////////
// ƒNƒ‰ƒX‚ğæ“¾
CArgBase* CArgument::GetClass( const char *path )
{
	CArgBase	*pBase = NULL;

	if(!_stricmp( path, sArgKey[_START_UP] ) )						pBase = new CStartUp();
	
	return pBase;
}


///////////////////////////////
// ˆ—‚ğs‚¤
_E_ERROR CArgument::Open( const char *sKey, const _TCHAR *sContents, std::vector< std::string > argv )
{
	CArgBase *pBase = GetClass( sKey );
	if( pBase == NULL )	return _E_NO_KEY;

	_E_ERROR ret = pBase->Execute( sContents, argv );

	delete pBase;
	return ret;
}