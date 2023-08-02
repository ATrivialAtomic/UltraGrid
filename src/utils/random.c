/**
 * @file   utils/random.h
 * @author Martin Pulec     <pulec@cesnet.cz>
 */
/*
 * Copyright (c) 2023 CESNET, z. s. p. o.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, is permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of CESNET nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define _CRT_RAND_S // request rand_s (Win)
#include <stdlib.h>

#include "random.h"

/**
 * @remark
 * thread-safe
 */
void
ug_srand(uint32_t seed)
{
#ifdef _WIN32
        (void) seed;
#else
        srandom(seed);
#endif
}

/**
 * @returns pseudorandom number in interval [0, 2^32-1]
 *
 * @remark
 * thread-safe
 */
uint32_t
ug_rand(void)
{
#ifdef _WIN32
        uint32_t ret = 0;
        rand_s(&ret);
#else
        uint32_t ret = (uint32_t) random() << 1;
        ret |= random() & 0x1;
#endif
        return ret;
}

/**
 * Behaves similarly to drand48()
 *
 * uses only 2^32 values from the interval (drand48 may use 48 bits)
 *
 * @returns val in interval [0.0, 1.0)
 *
 * @remark
 * thread-safe
 */
double
ug_drand()
{
        return ug_rand() / (UINT32_MAX + 1.0);
}
