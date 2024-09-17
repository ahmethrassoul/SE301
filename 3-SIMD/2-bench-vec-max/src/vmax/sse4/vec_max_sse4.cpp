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

        const __m128 buff = _mm_loadu_ps( src );

         for(int x = 0; x < length; x += simd) {

                const __m128 others = _mm_loadu_ps( src + x );

                const __m128 c = _mm_max_ps(....)
         }


        return 0;
};
/*
 *
 *
 *##############################################################################
 *
 *
 */
#endif