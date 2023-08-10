#pragma once
#include "Vector2.h"
#include "Matrix33.h"
#include "Matrix22.h"

namespace Twili
{
	class Transform
	{
	public:
		vec2 position;
		float rotation = 0;
		float scale = 1;

	public:
		Transform() = default;
		Transform(const vec2 postion, float rotation, float scale = 1) : position{ postion }, rotation{ rotation }, scale{ scale } {};

		mat3 Getmatrix() const
		{
			mat3 ms = mat3::CreateScale(scale);
			mat3 mr = mat3::CreateRotation(rotation);
			mat3 mt = mat3::CreateTranslation(position);
			mat3 mx = mt * ms * mr;

			return mx;
		}

	};

};

