#pragma once
#include "Vector2.h"
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

		mat2 Getmatrix() const
		{
			mat2 ms = mat2::CreateScale(scale);
			mat2 mr = mat2::CreateRotation(rotation);

			return ms * mr;
		}

	};

};

