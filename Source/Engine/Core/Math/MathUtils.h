#pragma once
#include <cmath>
#include <utility>

using namespace std;
namespace Twili
{
	constexpr float pi = 3.1415926535897932384626433f;
	constexpr float pi2 = 3.1415926535897932384626433f * 2;
	constexpr float halfPi = 3.1415926535897932384626433f / 2;

	constexpr float radiansToDegrees(float radians)
	{
		return radians * 180.0f / pi;
	}
	constexpr float degreesToRadians(float Degrees)
	{
		return Degrees * pi/180.0f;
	}

	constexpr int Wrap(int value, int max)
	{
		return (value % max) + ((value < 0) ? max : 0);
	}
	inline float Wrap(float value, float max)
	{
		return fmod(value , max) + ((value < 0) ? max : 0);
	}

	template <typename T>
	inline T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}
	template <typename T>
	inline T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}
	
	template <typename T>
	inline T Clamp(T value, T min, T max)
	{
		if (min > max) std::swap(min, max);
		if (value < min) value = min;
		else if (value > max) value = max;

		return value;
		//(value < min) ? min : (value > max)? max : value; same thing as above.
	}

	template<typename T>
	constexpr T Lerp(const T& a, const T& b, float t)
	{
		return (a * (1.0f - t)) + (b * t);
	}

}