#pragma once

#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <boost/optional.hpp>


#include <iomanip>
#include <cstdlib>

#include <filesystem>

#include <algorithm>
#include <regex>

typedef std::basic_string<TCHAR> tstring;


#define MAX_LEN 256



#ifdef _UNICODE
#define stringstream std::wostringstream
#else
#define stringstream std::ostringstream
#endif

#ifdef _UNICODE
#define toString std::to_wstring
#else
#define toString std::to_string
#endif


enum _E_ERROR {

	_E_NOERROR,
	_E_NO_KEY,

	_E_NO_FILE,
	_E_VALUE_ERROR,
	_E_ARGV_ERROR,
	_E_EXTERN_ERROR,
	_E_EXEC_ERROR,
	_E_EXCEPTION_ERROR,

	_E_SKIP,
	_E_UPDATE,

	_E_ERROR_FIN,

};


template<class X> class value
{
public:

	value() {}
	~value() {}

	void set(X v) { data += v; }
	X get() { return data; }

private:
	X data;
};