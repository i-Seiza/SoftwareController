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
CArgBase* CArgument::GetClass( const tstring path )
{
	auto it = ARG_MAP.find(path);
	if (it != ARG_MAP.end())	return it->second;

	return nullptr;
}


///////////////////////////////
// ˆ—‚ğs‚¤
_E_ERROR CArgument::Open( const tstring sKey, const _TCHAR *sContents, std::vector< tstring > argv )
{
	CArgBase *pBase = GetClass( sKey );
	if( pBase == NULL )	return _E_NO_KEY;

	_E_ERROR ret = pBase->Execute( sContents, argv );

	delete pBase;
	return ret;
}