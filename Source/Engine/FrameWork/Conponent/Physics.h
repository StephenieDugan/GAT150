#pragma once
#include "Conponents.h"
#include "Core/Math/Vector2.h"

namespace Twili
{
	class Physics : public Conponent
	{
	public:

		virtual void ApplyForce(const vec2& force) = 0;

	public:
		vec2 m_velocity;
		vec2 m_acceleration;
		float m_mass = 1.0f;
		float m_damping = 0;
	};
}