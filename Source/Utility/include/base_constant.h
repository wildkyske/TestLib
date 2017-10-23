#pragma once
#ifndef BASE_CONSTANT_H
#define BASE_CONSTANT_H

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <cassert>
#include <vector>
#include <list>
#include <map>
#include <set>

#include "typedefs.h"

typedef xchar* LPXSTR;
typedef const LPXSTR LPCXSTR;

typedef std::list<tstring> STRING_LIST;
typedef STRING_LIST::iterator STRING_LIST_ITER;
typedef STRING_LIST::const_iterator STRING_LIST_CONST_ITER;

typedef int xint;
typedef float xfloat;
typedef unsigned char xbyte;
typedef double xdouble;

typedef xdouble xglbase;

#endif
