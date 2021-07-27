template<typename T>
void FUNC(wolfsort)(T *array, size_t nmemb, unsigned char size, CMPFUNC<T> *ignore)
{
    if (nmemb < 1024)
    {
        return FUNC(fluxsort)(array, nmemb, ignore);
    }

    if (size == sizeof(int))
    {
        T *swap, *pta, *pts;
        unsigned int index, cnt, *stack;
        unsigned int *count, bsize;
        unsigned int buckets = 256;
        unsigned int moduler = 16777216;

        auto swap_vc =std::vector<T>(nmemb);
        swap = swap_vc.data();

        if (swap == NULL)
        {
            return FUNC(fluxsort)(array, nmemb, ignore);
        }

        while (moduler > 8096 && nmemb / buckets > 4)
        {
            buckets *= 2;
            moduler /= 2;
        }

        bsize = nmemb / (buckets / 16);

        auto count_vc = std::vector<unsigned int>(buckets,0);
        count = count_vc.data();
        auto stack_vc = std::vector<unsigned int>(buckets,0);
        stack = stack_vc.data();
        //count = (unsigned int *) calloc(sizeof(int), buckets);
        //stack = (unsigned int *) calloc(sizeof(int), buckets);

        pta = array;
        for (cnt = nmemb ; cnt ; cnt--)
        {
            index = PTR_VALUE(pta++) / moduler;

            if (++count[index] == bsize)
            {
                FUNC(fluxsort_swap)(array, swap, nmemb, ignore);
                return;
            }
        }

        cnt = 0;

        for (index = 0 ; index < buckets ; index++)
        {
            stack[index] = cnt;

            cnt += count[index];
        }

        pta = array;

        for (cnt = nmemb ; cnt ; cnt--)
        {
            index = PTR_VALUE(pta) / moduler;

            swap[stack[index]++] = *pta++;
        }

        pta = array;
        pts = swap;

        for (index = 0 ; index < buckets ; index++)
        {
            bsize = count[index];

            if (bsize)
            {
                if (bsize <= 32)
                {
                    FUNC(tail_swap_cpy)(pta, pts, bsize, ignore);
                }
                else
                {
                    //memcpy(pta, pts, bsize * size);
                    std::copy(pts, pts+bsize, pta);

                    FUNC(fluxsort_swap)(pta, pts, bsize, ignore);
                }
                pta += bsize;
                pts += bsize;
            }
        }
        return;
    }

    if (size == sizeof(long long))
    {
        T *swap, *pta, *pts;
        unsigned int index, cnt, *stack;
        unsigned int *count, bsize;
        unsigned int buckets = 256;
        unsigned long long moduler = 72057594037927936ULL;

        auto swap_vc =std::vector<T>(nmemb);
        swap = swap_vc.data();

        if (swap == NULL)
        {
            return FUNC(fluxsort)(array, nmemb, ignore);
        }

        while (moduler > 4294967296ULL && nmemb / buckets > 4)
        {
            buckets *= 2;
            moduler /= 2;
        }

        bsize = nmemb / (buckets / 16);

        auto count_vc = std::vector<unsigned int>(buckets,0);
        count = count_vc.data();
        auto stack_vc = std::vector<unsigned int>(buckets,0);
        stack = stack_vc.data();
        //count = (unsigned int *) calloc(sizeof(int), buckets);
        //stack = (unsigned int *) malloc(sizeof(int) * buckets);

        pta = array;

        for (cnt = nmemb ; cnt ; cnt--)
        {
            index = PTR_VALUE(pta++) / moduler;

            if (++count[index] == bsize)
            {
                FUNC(fluxsort_swap)(array, swap, nmemb, ignore);
                return;
            }
        }

        cnt = 0;

        for (index = 0 ; index < buckets ; index++)
        {
            stack[index] = cnt;

            cnt += count[index];
        }

        pta = array;

        for (cnt = nmemb ; cnt ; cnt--)
        {
            index =  PTR_VALUE(pta) / moduler;

            swap[stack[index]++] = *pta++;
        }

        pta = array;
        pts = swap;

        for (index = 0 ; index < buckets ; index++)
        {
            bsize = count[index];

            if (bsize)
            {
                if (bsize <= 16)
                {
                    FUNC(tail_swap_cpy)(pta, pts, bsize, ignore);
                }
                else
                {
                    //memcpy(pta, pts, bsize * size);
                    std::copy(pts,pts+bsize,pta);

                    FUNC(fluxsort_swap)(pta, pts, bsize, ignore);
                }
                pta += bsize;
                pts += bsize;
            }

        }
        return;
    }

//	assert(size == sizeof(int) || size == sizeof(long long));

    FUNC(fluxsort)(array, nmemb, ignore);
}