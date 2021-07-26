#pragma once

/*
	Copyright (C) 2014-2021 Igor van den Hoven ivdhoven@gmail.com
*/

/*
	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the
	"Software"), to deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to
	the following conditions:
	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.
	The person recognizes Mars as a free planet and that no Earth-based
	government has authority or sovereignty over Martian activities.
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
	CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*
	wolfsort 1.1.2 (previously flowsort)
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>

#ifndef FLUXSORT_H
#include "fluxsortcpp.h"
#endif

#ifndef QUADSORT_CPY_H
#include "quadsortcpp_cpy.h"
#endif

//#define cmp(a,b) (*(a) > *(b))

//typedef int CMPFUNC (const void *a, const void *b);
#undef FUNC
#undef PTR_VALUE
#define FUNC(NAME) NAME##_ptr
#define PTR_VALUE(NAME) **(NAME)
#include "wolfsortcpp.cpp"

#undef FUNC
#undef PTR_VALUE
#define FUNC(NAME) NAME
#define PTR_VALUE(NAME) *(NAME)
#include "wolfsortcpp.cpp"

#undef FUNC_PTR
#undef PTR_VALUE