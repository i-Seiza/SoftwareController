#pragma once

#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include "resource.h"
#include "Log.h"

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/foreach.hpp>
#include <boost/regex.hpp>


#include <iomanip>
#include <cstdlib>

#include <algorithm>


#define MAX_LEN 256


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


