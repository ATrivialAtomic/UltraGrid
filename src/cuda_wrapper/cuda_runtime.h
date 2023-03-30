/**
 * @file   cuda_wrapper/cuda_runtime.h
 * @author Martin Pulec     <pulec@cesnet.cz>
 *
 * Replaces some CUDA functions with wrapped variant for modules, that doesn't
 * use cuda_wrapper directly. Currently used by LDGM, which is outside UG so we
 * don't make it dependent on UltraGrid codebase).
 */
/*
 * Copyright (c) 2014 CESNET z.s.p.o.
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
#define cudaError_t int
#define cudaFreeHost cuda_wrapper_free_host
#define cudaMalloc cuda_wrapper_malloc
#define cudaMemcpy cuda_wrapper_memcpy
#define cudaGetErrorString cuda_wrapper_get_error_string
#define cudaGetLastError cuda_wrapper_get_last_error
#define cudaSuccess CUDA_WRAPPER_SUCCESS
#define cudaFree cuda_wrapper_free
#define cudaHostAllocDefault 0
#define cudaHostAlloc cuda_wrapper_host_alloc
#define cudaMemcpyHostToDevice CUDA_WRAPPER_MEMCPY_HOST_TO_DEVICE

#include "cuda_wrapper.h"

