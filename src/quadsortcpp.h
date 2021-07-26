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
	quadsort 1.1.3.5
*/

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>

//typedef int CMPFUNC (const void *a, const void *b);
template<typename T>
using CMPFUNC=int (const T *a, const T *b);


//#define cmp(a,b) (*(a) > *(b))
#ifdef __cplusplus
#define register
#define CASTPVAR(a) static_cast<VAR*>(a)
#define CASTPINT(a) static_cast<int*>(a)
#define CASTPUINT(a) static_cast<unsigned int*>(a)
#define CASTPUCHAR(a) static_cast<unsigned char*>(a)
#define CASTPLONGLONG(a) static_cast<long long*>(a)
#define CASTPLONGDOUBLE(a) static_cast<long double*>(a)
#elif
#define CASTPVAR(a) a
	#define CASTPINT(a) a
    #define CASTPUINT(a) a
	#define CASTPUCHAR(a) a
	#define CASTPLONGLONG(a) a
	#define CASTPLONGDOUBLE(a) a
#endif

#define swap_two(array, swap)  \
{  \
	if (cmp(array, array + 1) > 0)  \
	{  \
		swap = array[1]; array[1] = array[0]; array[0] = swap;  \
	}  \
}

#define swap_three(array, swap)  \
{  \
	if (cmp(array, array + 1) > 0)  \
	{  \
		if (cmp(array, array + 2) <= 0)  \
		{  \
			swap = array[0]; array[0] = array[1]; array[1] = swap;  \
		}  \
		else if (cmp(array + 1, array + 2) > 0)  \
		{  \
			swap = array[0]; array[0] = array[2]; array[2] = swap;  \
		}  \
		else  \
		{  \
			swap = array[0]; array[0] = array[1]; array[1] = array[2]; array[2] = swap;  \
		}  \
	}  \
	else if (cmp(array + 1, array + 2) > 0)  \
	{  \
		if (cmp(array, array + 2) > 0)  \
		{  \
			swap = array[2]; array[2] = array[1]; array[1] = array[0]; array[0] = swap;  \
		}  \
		else   \
		{  \
			swap = array[2]; array[2] = array[1]; array[1] = swap;  \
		}  \
	}  \
}  \

#define swap_four(array, swap)  \
{  \
	if (cmp(array, array + 1) > 0)  \
	{  \
		swap = array[0]; array[0] = array[1]; array[1] = swap;  \
	}  \
	if (cmp(array + 2, array + 3) > 0)  \
	{  \
		swap = array[2]; array[2] = array[3]; array[3] = swap;  \
	}  \
	if (cmp(array + 1, array + 2) > 0)  \
	{  \
		if (cmp(array, array + 2) <= 0)  \
		{  \
			if (cmp(array + 1, array + 3) <= 0)  \
			{  \
				swap = array[1]; array[1] = array[2]; array[2] = swap;  \
			}  \
			else  \
			{  \
				swap = array[1]; array[1] = array[2]; array[2] = array[3]; array[3] = swap;  \
			}  \
		}  \
		else if (cmp(array, array + 3) > 0)  \
		{  \
			swap = array[1]; array[1] = array[3]; array[3] = swap;  \
			swap = array[0]; array[0] = array[2]; array[2] = swap;  \
		}  \
		else if (cmp(array + 1, array + 3) <= 0)  \
		{  \
			swap = array[1]; array[1] = array[0]; array[0] = array[2]; array[2] = swap;  \
		}  \
		else  \
		{  \
			swap = array[1]; array[1] = array[0]; array[0] = array[2]; array[2] = array[3]; array[3] = swap;  \
		}  \
	}  \
}

#define tail_swap_eight(array, pta, ptt, end, key, cmp) \
{ \
	pta = end++; \
	ptt = pta--; \
 \
	if (cmp(pta, ptt) > 0) \
	{ \
		key = *ptt; \
		*ptt-- = *pta--; \
 \
		if (cmp(pta - 2, &key) > 0) \
		{ \
			*ptt-- = *pta--; *ptt-- = *pta--; *ptt-- = *pta--; \
		} \
		if (pta > array && cmp(pta - 1, &key) > 0) \
		{ \
			*ptt-- = *pta--; *ptt-- = *pta--; \
		} \
		if (pta >= array && cmp(pta, &key) > 0) \
		{ \
			*ptt-- = *pta; \
		} \
		*ptt = key; \
	} \
}

#define swap_five(array, pta, ptt, end, key, cmp) \
{ \
	end = array + 4; \
 \
	pta = end++; \
	ptt = pta--; \
 \
	if (cmp(pta, ptt) > 0) \
	{ \
		key = *ptt; \
		*ptt-- = *pta--; \
 \
		if (pta > array && cmp(pta - 1, &key) > 0) \
		{ \
			*ptt-- = *pta--; *ptt-- = *pta--; \
		} \
		if (pta >= array && cmp(pta, &key) > 0) \
		{ \
			*ptt-- = *pta; \
		} \
		*ptt = key; \
	} \
}

#define swap_six(array, pta, ptt, end, key, cmp) \
{ \
	swap_five(array, pta, ptt, end, key, cmp); \
	tail_swap_eight(array, pta, ptt, end, key, cmp); \
}

#define swap_seven(array, pta, ptt, end, key, cmp) \
{ \
	swap_six(array, pta, ptt, end, key, cmp); \
	tail_swap_eight(array, pta, ptt, end, key, cmp); \
}

#define swap_eight(array, pta, ptt, end, key, cmp) \
{ \
	swap_seven(array, pta, ptt, end, key, cmp); \
	tail_swap_eight(array, pta, ptt, end, key, cmp); \
}

#undef FUNC
#undef PTR_VALUE
#define FUNC(NAME) NAME
#define PTR_VALUE(NAME) *(NAME)
#include "quadsortcpp.cpp"

#undef FUNC_PTR
#undef PTR_VALUE

