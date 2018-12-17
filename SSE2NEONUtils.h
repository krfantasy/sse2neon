#pragma once

#include <math.h>

static inline __m128  _mm_isinf_ps(__m128 x)
{
	__m128 SIGN_MASK = _mm_set1_ps(-0.0);
	__m128 INF = _mm_set1_ps(INFINITY);

	return _mm_cmpeq_ps(INF, _mm_andnot_ps(SIGN_MASK, x));
}
