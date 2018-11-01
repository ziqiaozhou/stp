/********************************************************************
 * AUTHOR: Felix Kutzner, Mate Soos
 *
 * BEGIN DATE: Apr, 2017
 *
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
// ********************************************************************/

#ifndef ATTRIBUTES_H_
#define ATTRIBUTES_H_

#include "stp/config.h"


#if defined(_MSC_VER)
#define ATTR_NORETURN __declspec(noreturn)
#elif defined(__GNUC__) || defined(__clang__)
#define ATTR_NORETURN __attribute__((noreturn))
#else
#define ATTR_NORETURN
#endif

#if defined(_MSC_VER)
// NOTE: for now, we need STP_SHARED_LIB for clients of the statically linked
// STP library, for which linking fails when DLL_PUBLIC is __declspec(dllimport).
#if defined(STP_SHARED_LIB) && defined(STP_EXPORTS)
// This is visible when building the STP library as a DLL.
#define DLL_PUBLIC __declspec(dllexport)
#elif defined(STP_SHARED_LIB)
// This is visible for STP clients.
#define DLL_PUBLIC __declspec(dllimport)
#else
#define DLL_PUBLIC
#endif

// Symbols are hidden by default in MSVC.
#define DLL_LOCAL

#elif defined(__GNUC__) || defined(__clang__)
#define DLL_PUBLIC __attribute__((visibility("default")))
#define DLL_LOCAL __attribute__((visibility("hidden")))
#else
#define DLL_PUBLIC
#define DLL_LOCAL
#endif

//Defining THREAD_LOCAL
#if !USE_THREAD_LOCAL
#define THREAD_LOCAL
#elif __cplusplus >= 201103L
#define THREAD_LOCAL thread_local
#elif defined _WIN32 && (defined _MSC_VER || defined __ICL ||                  \
                         defined __DMC__ || defined __BORLANDC__)

//********************
// For windows, this does not work, DLL_PUBLIC and THREAD_LOCAL together die
//********************
//#define THREAD_LOCAL __declspec(thread)
#define THREAD_LOCAL

/* note that ICC (linux) and Clang are covered by __GNUC__ */
#elif defined __GNUC__ || defined __SUNPRO_C || defined __xlC__
#define THREAD_LOCAL __thread
#else
#error "Cannot define THREAD_LOCAL"
#endif

#endif //ATTRIBUTES_H_
