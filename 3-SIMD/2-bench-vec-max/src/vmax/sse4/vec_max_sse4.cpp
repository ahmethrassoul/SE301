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
#include "vec_max_sse4.hpp"
#include <cstdint>
#include <cstdio>
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
float vec_max_sse4(
        const float* __restrict src,
        const int               length)
{
        const int simd  = sizeof(__m128) / sizeof(float);

        __m128 buff = _mm_loadu_ps( src ); // enlever la const devant pour pouvoir ecrir dessus

        float max = 0;
        float tab[4];

         for(int x = 0; x < length; x += simd) {

                const __m128 others = _mm_loadu_ps( src + x );

                buff = _mm_max_ps(buff , others);

               // const __m128 buff = c;
         }
        
        _mm_storeu_ps( tab, buff );

        // Afficher les elements du buffer
        for(int i = 0; i < 4; i += 1) {
                printf("buff[%d] = %f\n", i ,  buff[i]);
        }

        //
        // processing the rest of the elements
        //
        for (int i = 0; i < 4; i+= 1)
        {
                if (tab[i] > max ) {
                        max = tab[i];
                }
                printf("tab[%d] = %f\n", i, tab[i]);
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