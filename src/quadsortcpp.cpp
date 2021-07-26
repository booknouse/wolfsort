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
	quadsort 1.1.4.1
*/
template<typename T>
void FUNC(tail_swap)(T *array, unsigned char nmemb, CMPFUNC<T> *cmp)
{
	T *pta, *end, *ptt, tmp;
	unsigned char mid, top, offset;

	switch (nmemb)
	{
		case 0:
		case 1:
			return;

		case 2:
			swap_two(array, tmp);
			return;

		case 3:
			swap_three(array, tmp);
			return;

		case 4:
			swap_four(array, tmp);
			return;

		case 5:
			swap_four(array, tmp);
			swap_five(array, pta, ptt, end, tmp, cmp);
			return;

		case 6:
			swap_four(array, tmp);
			swap_six(array, pta, ptt, end, tmp, cmp);
			return;

		case 7:
			swap_four(array, tmp);
			swap_seven(array, pta, ptt, end, tmp, cmp);
			return;
		case 8:
			swap_four(array, tmp);
			swap_eight(array, pta, ptt, end, tmp, cmp);
			return;
	}
	swap_four(array, tmp);
	swap_eight(array, pta, ptt, end, tmp, cmp);

	end = array + 8;
	offset = 8;

	while (offset < nmemb)
	{
		top = offset++;
		pta = end++;
		ptt = pta--;

		if (cmp(pta, ptt) <= 0)
		{
			continue;
		}

		tmp = *ptt;

		while (top > 1)
		{
			mid = top / 2;

			if (cmp(pta - mid, &tmp) > 0)
			{
				pta -= mid;
			}
			top -= mid;
		}

		//memmove(pta + 1, pta, (ptt - pta) * sizeof(VAR));
		std::copy(pta, ptt, pta+1);

		*pta = tmp;
	}
}

template<typename T>
void FUNC(parity_merge_sixteen)(T *dest, T *from, CMPFUNC<T> *cmp);
template<typename T>
void FUNC(tail_merge)(T *array, T *swap, unsigned int nmemb, unsigned int block, CMPFUNC<T> *cmp);

template<typename T>
unsigned int FUNC(quad_swap)(T *array, unsigned int nmemb, CMPFUNC<T> *cmp)
{
	T swap[16];
	unsigned int count, reverse;
	T *pta, *pts, *ptt, tmp;

	pta = array;

	count = nmemb / 4;

	while (count--)
	{
		if (cmp(&pta[0], &pta[1]) > 0)
		{
			if (cmp(&pta[2], &pta[3]) > 0)
			{
				if (cmp(&pta[1], &pta[2]) > 0)
				{
					pts = pta;
					pta += 4;
					goto swapper;
				}
				tmp = pta[2]; pta[2] = pta[3]; pta[3] = tmp;
			}
			tmp = pta[0]; pta[0] = pta[1]; pta[1] = tmp;
		}
		else if (cmp(&pta[2], &pta[3]) > 0)
		{
			tmp = pta[2]; pta[2] = pta[3]; pta[3] = tmp;
		}

		if (cmp(&pta[1], &pta[2]) > 0)
		{
			if (cmp(&pta[0], &pta[2]) <= 0)
			{
				if (cmp(&pta[1], &pta[3]) <= 0)
				{
					tmp = pta[1]; pta[1] = pta[2]; pta[2] = tmp;
				}
				else
				{
					tmp = pta[1]; pta[1] = pta[2]; pta[2] = pta[3]; pta[3] = tmp;
				}
			}
			else if (cmp(&pta[0], &pta[3]) > 0)
			{
				tmp = pta[1]; pta[1] = pta[3]; pta[3] = tmp; tmp = pta[0]; pta[0] = pta[2]; pta[2] = tmp;
			}
			else if (cmp(&pta[1], &pta[3]) <= 0)
			{
				tmp = pta[1]; pta[1] = pta[0]; pta[0] = pta[2]; pta[2] = tmp;
			}
			else
			{
				tmp = pta[1]; pta[1] = pta[0]; pta[0] = pta[2]; pta[2] = pta[3]; pta[3] = tmp;
			}
		}
		pta += 4;

		continue;

		swapper:

		if (count--)
		{
			if (cmp(&pta[0], &pta[1]) > 0)
			{
				if (cmp(&pta[2], &pta[3]) > 0)
				{
					if (cmp(&pta[1], &pta[2]) > 0)
					{
						if (cmp(&pta[-1], &pta[0]) > 0)
						{
							pta += 4;

							goto swapper;
						}
					}
					tmp = pta[2]; pta[2] = pta[3]; pta[3] = tmp;
				}
				tmp = pta[0]; pta[0] = pta[1]; pta[1] = tmp;
			}
			else if (cmp(&pta[2], &pta[3]) > 0)
			{
				tmp = pta[2]; pta[2] = pta[3]; pta[3] = tmp;
			}

			if (cmp(&pta[1], &pta[2]) > 0)
			{
				if (cmp(&pta[0], &pta[2]) <= 0)
				{
					if (cmp(&pta[1], &pta[3]) <= 0)
					{
						tmp = pta[1]; pta[1] = pta[2]; pta[2] = tmp;
					}
					else
					{
						tmp = pta[1]; pta[1] = pta[2]; pta[2] = pta[3]; pta[3] = tmp;
					}
				}
				else if (cmp(&pta[0], &pta[3]) > 0)
				{
					tmp = pta[0]; pta[0] = pta[2]; pta[2] = tmp; tmp = pta[1]; pta[1] = pta[3]; pta[3] = tmp;
				}
				else if (cmp(&pta[1], &pta[3]) <= 0)
				{
					tmp = pta[0]; pta[0] = pta[2]; pta[2] = pta[1]; pta[1] = tmp;
				}
				else
				{
					tmp = pta[0]; pta[0] = pta[2]; pta[2] = pta[3]; pta[3] = pta[1]; pta[1] = tmp;
				}
			}
			ptt = pta - 1;

			reverse = (ptt - pts) / 2;

			do
			{
				tmp = *pts; *pts++ = *ptt; *ptt-- = tmp;
			}
			while (reverse--);

			pta += 4;

			continue;
		}

		if (pts == array)
		{
			switch (nmemb % 4)
			{
				case 3:
					if (cmp(&pta[1], &pta[2]) <= 0)
					{
						break;
					}
				case 2:
					if (cmp(&pta[0], &pta[1]) <= 0)
					{
						break;
					}
				case 1:
					if (cmp(&pta[-1], &pta[0]) <= 0)
					{
						break;
					}
				case 0:
					ptt = pts + nmemb - 1;

					reverse = (ptt - pts) / 2;

					do
					{
						tmp = *pts; *pts++ = *ptt; *ptt-- = tmp;
					}
					while (reverse--);

					return 1;
			}
		}
		ptt = pta - 1;

		reverse = (ptt - pts) / 2;

		do
		{
			tmp = *pts; *pts++ = *ptt; *ptt-- = tmp;
		}
		while (reverse--);

		break;
	}

	FUNC(tail_swap)(pta, nmemb % 4, cmp);

	pta = array;

	count = nmemb / 16;

	while (count--)
	{
		FUNC(parity_merge_sixteen)(pta, swap, cmp);

		pta += 16;
	}

	if (nmemb % 16 > 4)
	{
		FUNC(tail_merge)(pta, swap, nmemb % 16, 4, cmp);
	}

	return 0;
}

template<typename T>
void FUNC(parity_merge_four)(T *dest, T *from, CMPFUNC<T> *cmp)
{
	T *ptl, *ptr;

	ptl = from;
	ptr = from + 4;

	*dest++ = cmp(ptl, ptr) <= 0 ? *ptl++ : *ptr++;
	*dest++ = cmp(ptl, ptr) <= 0 ? *ptl++ : *ptr++;
	*dest++ = cmp(ptl, ptr) <= 0 ? *ptl++ : *ptr++;
	*dest = cmp(ptl, ptr) <= 0 ? *ptl : *ptr;

	ptl = from + 3;
	ptr = from + 7;

	dest += 4;

	*dest-- = cmp(ptl, ptr) > 0 ? *ptl-- : *ptr--;
	*dest-- = cmp(ptl, ptr) > 0 ? *ptl-- : *ptr--;
	*dest-- = cmp(ptl, ptr) > 0 ? *ptl-- : *ptr--;
	*dest = cmp(ptl, ptr) > 0 ? *ptl : *ptr;
}

template<typename T>
void FUNC(parity_merge_eight)(T *dest, T *from, CMPFUNC<T> *cmp)
{
	T *ptl, *ptr;

	ptl = from;
	ptr = from + 8;

	*dest++ = cmp(ptl, ptr) <= 0 ? *ptl++ : *ptr++;
	*dest++ = cmp(ptl, ptr) <= 0 ? *ptl++ : *ptr++;
	*dest++ = cmp(ptl, ptr) <= 0 ? *ptl++ : *ptr++;
	*dest++ = cmp(ptl, ptr) <= 0 ? *ptl++ : *ptr++;
	*dest++ = cmp(ptl, ptr) <= 0 ? *ptl++ : *ptr++;
	*dest++ = cmp(ptl, ptr) <= 0 ? *ptl++ : *ptr++;
	*dest++ = cmp(ptl, ptr) <= 0 ? *ptl++ : *ptr++;
	*dest = cmp(ptl, ptr) <= 0 ? *ptl : *ptr;

	ptl = from + 7;
	ptr = from + 15;

	dest += 8;

	*dest-- = cmp(ptl, ptr) > 0 ? *ptl-- : *ptr--;
	*dest-- = cmp(ptl, ptr) > 0 ? *ptl-- : *ptr--;
	*dest-- = cmp(ptl, ptr) > 0 ? *ptl-- : *ptr--;
	*dest-- = cmp(ptl, ptr) > 0 ? *ptl-- : *ptr--;
	*dest-- = cmp(ptl, ptr) > 0 ? *ptl-- : *ptr--;
	*dest-- = cmp(ptl, ptr) > 0 ? *ptl-- : *ptr--;
	*dest-- = cmp(ptl, ptr) > 0 ? *ptl-- : *ptr--;
	*dest = cmp(ptl, ptr) > 0 ? *ptl : *ptr;
}

template<typename T>
void FUNC(parity_merge_sixteen)(T *array, T *swap, CMPFUNC<T> *cmp)
{
	if (cmp(array + 3, array + 4) <= 0 && cmp(array + 7, array + 8) <= 0 && cmp(array + 11, array + 12) <= 0)
	{
		return;
	}
	FUNC(parity_merge_four)(swap, array, cmp);
	FUNC(parity_merge_four)(swap + 8, array + 8, cmp);

	FUNC(parity_merge_eight)(array, swap, cmp);
}

template<typename T>
void FUNC(forward_merge)(T *dest, T *from, size_t block, CMPFUNC<T> *cmp)
{
	T *l, *r, *m, *e; // left, right, middle, end

	l = from;
	r = from + block;
	m = r;
	e = r + block;

	if (cmp(r - 1, e - 1) <= 0)
	{
		do
		{
			if (cmp(l, r) <= 0)
			{
				*dest++ = *l++;
				continue;
			}
			*dest++ = *r++;
			if (cmp(l, r) <= 0)
			{
				*dest++ = *l++;
				continue;
			}
			*dest++ = *r++;
			if (cmp(l, r) <= 0)
			{
				*dest++ = *l++;
				continue;
			}
			*dest++ = *r++;
		}
		while (l < m);

		do *dest++ = *r++; while (r < e);
	}
	else
	{
		do
		{
			if (cmp(l, r) > 0)
			{
				*dest++ = *r++;
				continue;
			}
			*dest++ = *l++;
			if (cmp(l, r) > 0)
			{
				*dest++ = *r++;
				continue;
			}
			*dest++ = *l++;
			if (cmp(l, r) > 0)
			{
				*dest++ = *r++;
				continue;
			}
			*dest++ = *l++;
		}
		while (r < e);

		do *dest++ = *l++; while (l < m);
	}
}

// main memory: [A][B][C][D]
// swap memory: [A  B]       step 1
// swap memory: [A  B][C  D] step 2
// main memory: [A  B  C  D] step 3

template<typename T>
void FUNC(quad_merge_block)(T *array, T *swap, unsigned int block, CMPFUNC<T> *cmp)
{
	register T *pts, *c, *c_max;
	unsigned int block_x_2 = block * 2;

	c_max = array + block;

	if (cmp(c_max - 1, c_max) <= 0)
	{
		c_max += block_x_2;

		if (cmp(c_max - 1, c_max) <= 0)
		{
			c_max -= block;

			if (cmp(c_max - 1, c_max) <= 0)
			{
				return;
			}
			pts = swap;

			c = array;

			do *pts++ = *c++; while (c < c_max); // step 1

			c_max = c + block_x_2;

			do *pts++ = *c++; while (c < c_max); // step 2

			return FUNC(forward_merge)(array, swap, block_x_2, cmp); // step 3
		}
		pts = swap;

		c = array;
		c_max = array + block_x_2;

		do *pts++ = *c++; while (c < c_max); // step 1
	}
	else
	{
		FUNC(forward_merge)(swap, array, block, cmp); // step 1
	}
	FUNC(forward_merge)(swap + block_x_2, array + block_x_2, block, cmp); // step 2

	FUNC(forward_merge)(array, swap, block_x_2, cmp); // step 3
}

template<typename T>
void FUNC(quad_merge)(T *array, T *swap, unsigned int nmemb, unsigned int block, CMPFUNC<T> *cmp)
{
	T *pta, *pte;

	pte = array + nmemb;

	block *= 4;

	while (block * 2 <= nmemb)
	{
		pta = array;

		do
		{
			FUNC(quad_merge_block)(pta, swap, block / 4, cmp);

			pta += block;
		}
		while (pta + block <= pte);

		FUNC(tail_merge)(pta, swap, pte - pta, block / 4, cmp);

		block *= 4;
	}
	FUNC(tail_merge)(array, swap, nmemb, block / 4, cmp);
}

template<typename T>
void FUNC(partial_backward_merge)(T *array, T *swap, size_t nmemb, size_t block, CMPFUNC<T> *cmp)
{
	T *r, *m, *e, *s; // right, middle, end, swap

	m = array + block;
	e = array + nmemb - 1;
	r = m--;

	if (cmp(m, r) <= 0)
	{
		return;
	}

	while (cmp(m, e) <= 0)
	{
		e--;
	}

	//memcpy(swap, r, (e - m) * sizeof(VAR));
	std::copy(r, r+(e-m), swap);

	s = swap + (e - r);

	*e-- = *m--;

	if (cmp(array, swap) <= 0)
	{
		do
		{
			while (cmp(m, s) > 0)
			{
				*e-- = *m--;
			}
			*e-- = *s--;
		}
		while (s >= swap);
	}
	else
	{
		do
		{
			while (cmp(m, s) <= 0)
			{
				*e-- = *s--;
			}
			*e-- = *m--;
		}
		while (m >= array);

		do *e-- = *s--; while (s >= swap);
	}
}

template<typename T>
void FUNC(tail_merge)(T *array, T *swap, unsigned int nmemb, unsigned int block, CMPFUNC<T> *cmp)
{
	register T *pta, *pte;

	pte = array + nmemb;

	while (block < nmemb)
	{
		pta = array;

		for (pta = array ; pta + block < pte ; pta += block * 2)
		{
			if (pta + block * 2 < pte)
			{
				FUNC(partial_backward_merge)(pta, swap, block * 2, block, cmp);

				continue;
			}
			FUNC(partial_backward_merge)(pta, swap, pte - pta, block, cmp);

			break;
		}
		block *= 2;
	}
}

///////////////////////////////////////////////////////////////////////////////
//┌─────────────────────────────────────────────────────────────────────────┐//
//│    ██████┐ ██┐   ██┐ █████┐ ██████┐ ███████┐ ██████┐ ██████┐ ████████┐  │//
//│   ██┌───██┐██│   ██│██┌──██┐██┌──██┐██┌────┘██┌───██┐██┌──██┐└──██┌──┘  │//
//│   ██│   ██│██│   ██│███████│██│  ██│███████┐██│   ██│██████┌┘   ██│     │//
//│   ██│▄▄ ██│██│   ██│██┌──██│██│  ██│└────██│██│   ██│██┌──██┐   ██│     │//
//│   └██████┌┘└██████┌┘██│  ██│██████┌┘███████│└██████┌┘██│  ██│   ██│     │//
//│    └──▀▀─┘  └─────┘ └─┘  └─┘└─────┘ └──────┘ └─────┘ └─┘  └─┘   └─┘     │//
//└─────────────────────────────────────────────────────────────────────────┘//
///////////////////////////////////////////////////////////////////////////////

template<typename T>
void FUNC(quadsort)(T *array, size_t nmemb, CMPFUNC<T> *cmp)
{
    if (nmemb < 2)
    {
        return;
    }

	if (nmemb < 16)
	{
		FUNC(tail_swap)(array, nmemb, cmp);
	}
	else if (nmemb < 256)
	{
		if (FUNC(quad_swap)(array, nmemb, cmp) == 0)
		{
			T swap[128];

			FUNC(tail_merge)(array, swap, nmemb, 16, cmp);
		}
	}
	else if (FUNC(quad_swap)(array, nmemb, cmp) == 0)
	{
		//VAR *swap = malloc(nmemb * sizeof(VAR) / 2);
		auto swap = std::vector<T>(nmemb/2);

		FUNC(quad_merge)(array, swap.data(), nmemb, 16, cmp);

		//free(swap);
	}
}

template<typename T>
void FUNC(quadsort_swap)(T *array, T *swap, size_t nmemb, CMPFUNC<T> *cmp)
{
	if (nmemb < 16)
	{
		FUNC(tail_swap)(array, nmemb, cmp);
	}
	else if (nmemb < 256)
	{
		if (FUNC(quad_swap)(array, nmemb, cmp) == 0)
		{
			FUNC(tail_merge)(array, swap, nmemb, 16, cmp);
		}
	}
	else if (FUNC(quad_swap)(array, nmemb, cmp) == 0)
	{
		FUNC(quad_merge)(array, swap, nmemb, 16, cmp);
	}
}
