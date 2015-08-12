#pragma once


class CLog
{
public:
	CLog(void);
	~CLog(void);

private:
	bool IsWrite();

public:
	void Write( const std::string sLog );
	void Write( const std::string sClass, const int eType, const std::string sContents );
};

