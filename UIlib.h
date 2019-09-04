#pragma once

#include<string>
using namespace std;
#ifdef _DUBUG
#  ifdef _UNICODE
#	   pragma comment(lib,"DuiLib_ud.lib")
#  else
#      pragma comment(lib,"DuiLib_d.lib")
#  endif
#else
#  ifdef _UNICODE
#    pragma comment(lib,"DuiLib_u.lib")
#  else 
#    pragma comment(lib,"DuiLib.lib")
#   endif
#endif

//string UnicodeToANSI(const CDuiString& str);
//CDuiString ANSIToUnicode(const string& str)