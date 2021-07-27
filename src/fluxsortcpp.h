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
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
	CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*
	fluxsort 1.1.3.5
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include "quadsortcpp.h"

//template<typename T>
//using CMPFUNC=int (const T *a, const T *b);

#undef FUNC
#define MOVE(NAME) NAME
#define FUNC(NAME) NAME
#include "fluxsortcpp.cpp"

#undef FUNC
#undef MOVE

#define MOVE(NAME) std::move(NAME)
#define FUNC(NAME) NAME##_move
#include "fluxsortcpp.cpp"

#undef FUNC_PTR
#undef MOVE