/**
 *
 * 
  Copyright (c) 2012-2020 "Bordeaux INP, Bertrand LE GAL"
  bertrand.legal@ims-bordeaux.fr
  [http://legal.vvv.enseirb-matmeca.fr]

  This file is part of a LDPC library for realtime LDPC decoding
  on processor cores.
 *
 *
 */
#ifdef __SSE4_2__
#include "vec_max_index_sse4.hpp"
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <limits.h>
#include <immintrin.h>
/*
 *
 *
 *##############################################################################
 *
 *
 */
int vec_max_index_sse4(
        const float* __restrict src,
        const int               length)
{
        const int simd  = sizeof(__m128) / sizeof(float);

        __m128 buff = _mm_loadu_ps( src ); // enlever la const devant pour pouvoir ecrir dessus

        float max = 0;
        int index_1 = 0;
        int index_2 = 0;
        int index   = 0;
        float tmp_tab[4];
        float tmp_tab1[4];
        float tmp_tab2[4];

         for(int x = 0; x < length; x += simd) {

                const __m128 others1 = _mm_loadu_ps( src + x );
                _mm_storeu_ps( tmp_tab1, others1 );

                buff = _mm_max_ps(buff , others);
                _mm_storeu_ps( tmp_tab, buff );

                for (int i = 0; i < simd; i+= 1)
                {
                        if (tmp_tab1[i] = tmp_tab[i] ) {
                                index_1 = x + i;
                        }

                        if (tmp_tab2[i] > tmp_tab[i] ) {
                                index_2 = x + i;
                        }
                }
         }
        
        _mm_storeu_ps( tab, buff );


        //
        // processing the rest of the elements
        //
        for (int i = 0; i < simd; i+= 1)
        {
                if (tab[i] > max ) {
                        max = tab[i];
                }
                printf("max = %f\n", max);
        }

        return max;
};
/*
 *
 *
 *##############################################################################
 *
 *
 */
#endif