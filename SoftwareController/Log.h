#pragma once

#include "def.h"

class CLog
{
public:
	CLog(void);
	~CLog(void);

private:
	bool IsWrite();

public:
	void Write( const tstring sLog );
	void Write( const tstring sClass, const int eType, const tstring sContents );
};

