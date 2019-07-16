#pragma once

#include <cmath>
#include <random>
#include <algorithm>

namespace math
{
	const float PI = 3.1415f;
	const float TWO_PI = PI * 2.0f;
	const float HALF_PI = PI * 0.5f;

	const float DEG_TO_RAD = PI / 180.0f;
	const float RAD_TO_DEG = 180.0f / PI;

	template <typename TBase>
	inline TBase clamp(TBase v, TBase low, TBase high)
	{
		return std::min<TBase>(high, std::max<TBase>(v, low));
	}

	template <typename TBase>
	inline TBase clamp01(TBase v)
	{
		return std::min<TBase>(1, std::max<TBase>(v, 0));
	}

	template <typename TBase>
	inline TBase lerp(const TBase& v1, const TBase& v2, float t)
	{
		t = clamp01<float>(t);
		return (v1 + ((v2 - v1) * t));
	}

	template <typename TBase>
	inline TBase lerp_unclamped(const TBase& v1, const TBase& v2, float t)
	{
		return (v1 + ((v2 - v1) * t));
	}
}