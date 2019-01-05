#pragma once

#if defined(__x86_64__) || defined(__i386__)
#include <x86intrin.h>
#elif defined(__ARM_NEON__)
#include "SSE2NEON.h"
#endif

#include <type_traits>

template<class T, std::size_t N = sizeof(__m128i) / sizeof(T)>
union SSEVector
{
	// Type without CV
	using TwoCV = typename std::remove_cv<T>::type;
	static_assert(std::is_same<TwoCV, float>::value
				  || std::is_same<TwoCV, double>::value
				  || std::is_integral<TwoCV>::value,
				  "incompatible type for sse vector");


	using SSEType = typename std::conditional<
		std::is_same<TwoCV, float>::value,
		__m128,
		typename std::conditional<std::is_same<TwoCV, double>::value, __m128d, __m128i>::type>::type;

	alignas(SSEType) SSEType v;
	alignas(SSEType) T s[N];

	SSEVector() = default;
	SSEVector(const SSEVector&) = default;
	SSEVector& operator=(const SSEVector&) = default;

	SSEVector(const SSEType& sse) : v(sse)
	{
	}

	inline T& operator[](std::size_t idx)
	{
		return s[idx];
	}

	inline const T& operator[](std::size_t idx) const
	{
		return s[idx];
	}

	inline SSEVector& operator=(const SSEType& sse)
	{
		v = sse;
		return *this;
	}

	inline operator SSEType() const
	{
		return v;
	}
};

using SSEVectorf = SSEVector<float>;
using SSEVectord = SSEVector<double>;
using SSEVectori = SSEVector<int32_t>;
using SSEVectori32 = SSEVector<int32_t>;
using SSEVectori16 = SSEVector<int16_t>;
using SSEVectori8 = SSEVector<int8_t>;
