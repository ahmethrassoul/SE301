/*
*	Optimized byte interleaving functions - Copyright (c) 2021 Bertrand LE GAL
*
*  This software is provided 'as-is', without any express or
*  implied warranty. In no event will the authors be held
*  liable for any damages arising from the use of this software.
*
*  Permission is granted to anyone to use this software for any purpose,
*  including commercial applications, and to alter it and redistribute
*  it freely, subject to the following restrictions:
*
*  1. The origin of this software must not be misrepresented;
*  you must not claim that you wrote the original software.
*  If you use this software in a product, an acknowledgment
*  in the product documentation would be appreciated but
*  is not required.
*
*  2. Altered source versions must be plainly marked as such,
*  and must not be misrepresented as being the original software.
*
*  3. This notice may not be removed or altered from any
*  source distribution.
*
*/

#include "vec_add_x86.hpp"
#include <omp.h>
/*
 *
 *
 *##############################################################################
 *
 *
 */
void vec_add_x86(
              float* __restrict dst,
        const float* __restrict src_1,
        const float* __restrict src_2,
        const int               length)
{
#pragma clang loop vectorize(enable)
    for (int i = 0; i < length; i+= 1)
    {
        dst[i] = src_1[i] + src_2[i];
    }
};
/*
 *
 *
 *##############################################################################
 *
 *
 */
void vec_add_omp(
              float* __restrict dst,
        const float* __restrict src_1,
        const float* __restrict src_2,
        const int               length)
{
#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < length; i+= 1)
        {
            dst[i] = src_1[i] + src_2[i];
        }
    }
};
/*
 *
 *
 *##############################################################################
 *
 *
 */
#if !defined (__clang__)
    __attribute__((optimize("no-tree-vectorize")))
#endif
void vec_add_x86_novect(
              float* __restrict dst,
        const float* __restrict src_1,
        const float* __restrict src_2,
        const int32_t length)
{
#if defined (__clang__)
    #pragma clang loop vectorize(disable)
#endif
    for (int i = 0; i < length; i+= 1)
    {
        dst[i] = src_1[i] + src_2[i];
    }
};
/*
 *
 *
 *##############################################################################
 *
 *
 */
