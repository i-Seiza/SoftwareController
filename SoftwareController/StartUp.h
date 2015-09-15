#pragma once
#include "argbase.h"

enum STARTUP_TYPE{
	_ALWAYS,
	_POSSIBLE,
	_START_TIME,
	_END_TIME,


	_START_UP_FIN,
};

const std::unordered_map<STARTUP_TYPE, const tstring> KEYWORD_STARTUP =
{
	{ _ALWAYS, tstring(_T("Always"))},
	{ _POSSIBLE, tstring(_T("Possible")) },
	{ _START_TIME, tstring(_T("start_time")) },
	{ _END_TIME, tstring(_T("end_time")) },
};

template <class X> class Value {

private:
	boost::optional<X> value;
	
public:
	void	set(X _value) { value = _value; }
	X		get() { return value.is_initialized() ? *value : X(); }
	bool	isInitialized() { return value.is_initialized(); }
};

class CStartUp :
	public CArgBase
{
	class CExecuteTime
	{
	private:
		Value<int>	hour;
		Value<int>	minites;
	public:
		int GetHour() { return hour.get(); }
		int GetMinites() { return minites.get(); }
		void SetHour(int _hour) { hour.set(_hour); }
		void SetMinites(int _minites) { minites.set(_minites); }
		bool IsInitialized() { return hour.isInitialized() && minites.isInitialized(); }
		int GetTotalMinites() {
			return hour.get() * 60 + minites.get();
		}
	};
	

public:
	CStartUp(void);
	~CStartUp(void);

private:

	bool		IsExecutePossible( const _TCHAR *sContents );
	CExecuteTime		GetTime( const _TCHAR *sContents, const tstring sKey );
	_E_ERROR	Execute( const _TCHAR *sContents, const tstring sKey );


public:
	_E_ERROR Execute( const _TCHAR *sContents,  std::vector< std::string > argv );

};
