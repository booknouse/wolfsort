#define tail_swap_two_cpy(dest, array, swap) \
{ \
	if (cmp(array, array + 1) > 0) \
	{ \
		dest[0] = MOVE(array[1]); dest[1] = MOVE(array[0]); \
	} \
	else \
	{ \
		dest[0] = MOVE(array[0]); dest[1] = MOVE(array[1]); \
	} \
}

#define tail_swap_three_cpy(dest, array, swap) \
{ \
	if (cmp(array, array + 1) > 0) \
	{ \
		if (cmp(array, array + 2) <= 0) \
		{ \
			dest[0] = MOVE(array[1]); dest[1] = MOVE(array[0]); dest[2] = MOVE(array[2]); \
		} \
		else if (cmp(array + 1, array + 2) > 0) \
		{ \
			dest[0] = MOVE(array[2]); dest[1] = MOVE(array[1]); dest[2] = MOVE(array[0]); \
		} \
		else \
		{ \
			dest[0] = MOVE(array[1]); dest[1] = MOVE(array[2]); dest[2] = MOVE(array[0]); \
		} \
	} \
	else if (cmp(array + 1, array + 2) > 0) \
	{ \
		if (cmp(array, array + 2) > 0) \
		{ \
			dest[0] = MOVE(array[2]); dest[1] = MOVE(array[0]); dest[2] = MOVE(array[1]); \
		} \
		else  \
		{ \
			dest[0] = MOVE(array[0]); dest[1] = MOVE(array[2]); dest[2] = MOVE(array[1]); \
		} \
	} \
	else \
	{ \
			dest[0] = MOVE(array[0]); dest[1] = MOVE(array[1]); dest[2] = MOVE(array[2]); \
	} \
}

#define tail_swap_four_cpy(dest, array, swap) \
{ \
	if (cmp(array, array + 1) > 0) \
	{ \
		if (cmp(array, array + 2) <= 0) \
		{ \
			dest[0] = MOVE(array[1]); dest[1] = MOVE(array[0]); dest[2] = MOVE(array[2]); \
		} \
		else if (cmp(array + 1, array + 2) > 0) \
		{ \
			dest[0] = MOVE(array[2]); dest[1] = MOVE(array[1]); dest[2] = MOVE(array[0]); \
		} \
		else \
		{ \
			dest[0] = MOVE(array[1]); dest[1] = MOVE(array[2]); dest[2] = MOVE(array[0]); \
		} \
	} \
	else if (cmp(array + 1, array + 2) > 0) \
	{ \
		if (cmp(array, array + 2) > 0) \
		{ \
			dest[0] = MOVE(array[2]); dest[1] = MOVE(array[0]); dest[2] = MOVE(array[1]); \
		} \
		else  \
		{ \
			dest[0] = MOVE(array[0]); dest[1] = MOVE(array[2]); dest[2] = MOVE(array[1]); \
		} \
	} \
	else \
	{ \
			dest[0] = MOVE(array[0]); dest[1] = MOVE(array[1]); dest[2] = MOVE(array[2]); \
	} \
 \
	if (cmp(dest + 1, array + 3) > 0) \
	{ \
		if (cmp(dest, array + 3) > 0) \
		{ \
			dest[3] = MOVE(dest[2]); dest[2] = MOVE(dest[1]); dest[1] = MOVE(dest[0]); dest[0] = MOVE(array[3]); \
		} \
		else \
		{ \
			dest[3] = MOVE(dest[2]); dest[2] = MOVE(dest[1]); dest[1] = MOVE(array[3]); \
		} \
	} \
	else if (cmp(dest + 2, array + 3) > 0) \
	{ \
		dest[3] = MOVE(dest[2]); dest[2] = MOVE(array[3]); \
	} \
	else \
	{ \
		dest[3] = MOVE(array[3]); \
	} \
}

template<typename T>
void FUNC(guarded_insert_cpy)(T *array, T key, unsigned char nmemb, CMPFUNC<T> cmp)
{
    T *pta, *tpa;
    unsigned char top;

    pta = array + nmemb;
    tpa = pta--;

    while (nmemb--)
    {
        if (cmp(pta, &key) <= 0)
        {
            break;
        }
        *tpa-- = MOVE(*pta--);
    }
    *tpa = MOVE(key);
}

template<typename T>
void FUNC(tail_swap_cpy)(T *dest, T *array, unsigned char nmemb, CMPFUNC<T> cmp)
{
    int swap;
    register unsigned char cnt;

    switch (nmemb)
    {
        case 0:
            return;
        case 1:
            *dest = MOVE(*array);
            return;
        case 2:
        tail_swap_two_cpy(dest, array, swap);
            return;
        case 3:
        tail_swap_three_cpy(dest, array, swap);
            return;
        case 4:
        tail_swap_four_cpy(dest, array, swap);
            return;
    }
    tail_swap_four_cpy(dest, array, swap);

    for (cnt = 4 ; cnt < nmemb ; cnt++)
    {
        FUNC(guarded_insert_cpy)(dest, array[cnt], cnt, cmp);
    }
    return;
}

template<typename T>
void FUNC(tail_merge_cpy)(T *dest, T *array, size_t nmemb, size_t block, CMPFUNC<T> cmp)
{
    register T *pta, *ptb, *ptd, *ptm;

    ptd = dest;

    pta = array;
    ptb = array + block;
    ptm = array + nmemb;

    if (cmp(ptb - 1, ptb) <= 0)
    {
        while (pta + 8 < ptm)
        {
            *ptd++ = *pta++; *ptd++ = *pta++; *ptd++ = *pta++; *ptd++ = *pta++;
            *ptd++ = *pta++; *ptd++ = *pta++; *ptd++ = *pta++; *ptd++ = *pta++;
        }
        while (pta < ptm)
        {
            *ptd++ = *pta++;
        }
        return;
    }

    if (cmp(ptb - 1, ptm - 1) <= 0)
    {
        ptm = array + block;

        while (pta < ptm)
        {
            while (cmp(pta, ptb) > 0)
            {
                *ptd++ = *ptb++;
            }
            *ptd++ = *pta++;
        }
        ptm = array + nmemb;

        while (ptb < ptm)
        {
            *ptd++ = *ptb++;
        }
    }
    else
    {
        while (ptb < ptm)
        {
            while (cmp(pta, ptb) <= 0)
            {
                *ptd++ = *pta++;
            }
            *ptd++ = *ptb++;
        }
        ptm = array + block;

        while (pta < ptm)
        {
            *ptd++ = *pta++;
        }
    }
}

#undef tail_swap_two_cpy
#undef tail_swap_three_cpy
#undef tail_swap_four_cpy
