#pragma once
#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

//
#ifndef _T
#if defined(UNICODE) || defined(_UNICODE)
#define __TX(s) L ## s
#define _TX(s) L ## s
#else
#define _TX(s) s
#endif
//
#else
#define _TX _T
#endif

/* UNICODE下STL定义. */
#ifdef WIN32

#if defined(UNICODE)  ||  defined(_UNICODE)

#define tstring std::wstring
#define tcout std::wcout
#define tsstream std::wstringstream
#define tosstream std::wostringstream
#define tistringstream std::wistringstream
#define tistream std::wistream
#define tostream std::wostream
#define tofstream std::wofstream
#define tifstream std::wifstream

typedef wchar_t xchar;

#define XFUNCTION_NAME __FUNCTIONW__

#else

#define tstring std::string
#define tcout std::cout
#define tsstream std::stringstream
#define tosstream std::ostringstream
#define tistringstream std::istringstream
#define tistream std::istream
#define tostream std::ostream
#define tofstream std::ofstream
#define tifstream std::ifstream

typedef char xchar;

#define XFUNCTION_NAME __FUNCTION__
#endif	//end-win32

#elif defined(__linux__)

#define tstring std::string
#define tcout std::cout
#define tsstream std::stringstream
#define tosstream std::ostringstream
#define tistringstream std::istringstream
#define tistream std::istream
#define tostream std::ostream
#define tofstream std::ofstream
#define tifstream std::ifstream

typedef char xchar;

#define XFUNCTION_NAME __FUNCTION__

#endif

//================================
//==特征类
template <typename T>
struct arg_type_traits{
    typedef const T& type;
};

template <typename T>
struct arg_type_traits<T&>
{
    typedef T& type;
};

template <typename T>
struct arg_type_traits<const T&>
{
    typedef const T& type;
};
//-|
#endif
