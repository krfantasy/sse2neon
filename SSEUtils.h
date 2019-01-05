#pragma once

#if defined(__x86_64__) || defined(__i386__)
#include <x86intrin.h>
#elif defined(__ARM_NEON__)
#include "SSE2NEON.h"
#endif

#include <math.h>

static inline __m128  _mm_isinf_ps(__m128 x)
{
	__m128 SIGN_MASK = _mm_set1_ps(-0.0);
	__m128 INF = _mm_set1_ps(INFINITY);

	return _mm_cmpeq_ps(INF, _mm_andnot_ps(SIGN_MASK, x));
}

static inline __m128 _mm_abs_ps(__m128 x)
{
	__m128 ABS_MASK = _mm_castsi128_ps(_mm_set1_epi32(-1.0));
	return _mm_and_ps(x, ABS_MASK);
}

static inline float _mm_sum_ps(__m128 x)
{
	x = _mm_hadd_ps(x, x);
	x = _mm_hadd_ps(x, x);
	return _mm_cvtss_f32(x);
}
