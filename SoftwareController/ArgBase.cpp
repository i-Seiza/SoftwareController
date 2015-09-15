#include "StdAfx.h"
#include "ArgBase.h"

#include <boost/algorithm/string.hpp>

CArgBase::CArgBase(void)
{
	m_sReadedIniData = _T("");
}

CArgBase::~CArgBase(void)
{
}

///////////////////////////////
_E_ERROR CArgBase::Execute( const _TCHAR *sContents,  std::vector< tstring > argv )
{

	return _E_NOERROR;
}

///////////////////////////////
// Iniファイルから値を取得する
bool CArgBase::ReadInifile( const _TCHAR *sContents, const _TCHAR *sKey )
{
	m_sReadedIniData.clear();

	CInifile ini;
	ini.ReadInifile( sContents, sKey, _T("") );

	tstring contents = ini.GetContents();
	if (contents.empty())	return false;

	m_sReadedIniData = ini.GetContents();
	return true;
}

tstring CArgBase::GetIniData()
{
	return m_sReadedIniData;
}

tstring CArgBase::Replace( tstring str1, tstring src, tstring dest )
{
	boost::algorithm::replace_all(str1, src, dest);
	return str1;
}
