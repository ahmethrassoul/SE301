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

        int index_max   = 0;
        int index_max_src = 0;
        float max = src[0];
        float tmp_tab[4];

         for(int x = 0; x < length; x += simd) {

                const __m128 others = _mm_loadu_ps( src + x );

                buff = _mm_max_ps(buff , others);
         }
        
        _mm_storeu_ps( tmp_tab, buff );


        //
        // processing the rest of the elements
        //
        for (int i = 0; i < simd; i+= 1) { // chercher l'indice global dans le buffer de maximum qui contient que 4 max
                
                if (tmp_tab[i] > max ) {
                        max = tmp_tab[i];
                        index_max = i;
                }
                
        }

        for (int j = 0; j < length; j+= index_max) { // chercher l'indice global dans src
                        if (max == src[j]) {
                                index_max_src = j;
                        }        
                }

        printf("max = %f\n", max);
        printf("indice max = %f\n", index_max);
        printf("indice max = %f\n", index_max_src);
        return index_max_src;
};
/*
 *
 *
 *##############################################################################
 *
 *
 */
#endif