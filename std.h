/*
 * std.h
 *
 * C++ header file for students at CSUSB.
 * Includes the all C++03 standard libraries and brings them to the global
 * namespace.
 *
 */
#ifndef CPP_03_STD_H
#define CPP_03_STD_H

/* Utilities */
#include <cstdlib>
#include <bitset>
#include <utility>
#include <ctime>
#include <cstddef>

/* Dynamic memory management */
#include <new>
#include <memory>

/* Numeric limits */
#include <climits>
#include <cfloat>
#include <limits>

/* Error handling */
#include <exception>
#include <stdexcept>
#include <cassert>

/* Strings */
#include <cctype>
#include <cstring>
#include <string>

/* Containers */
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>

/* Algorithms */
#include <algorithm>

/* Numerics */
#include <cmath>
#include <complex>
#include <valarray>
#include <numeric>

/* Input/Output */
#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <streambuf>
#include <cstdio>

/* Localization */
#include <locale>
#include <clocale>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

using namespace std;

#endif
