#pragma once
#include "Conponents.h"
#include "Core/Math/Vector2.h"

namespace Twili
{
	class Physics : public Conponent
	{
	public:

		virtual void ApplyForce(const vec2& force) = 0;
		virtual void ApplyTorque(float torque) = 0;

		virtual void SetVelocity(const vec2& velocity) { this->m_velocity = velocity; }

	public:
		vec2 m_velocity;
		vec2 m_acceleration;
		float m_mass = 1.0f;
		float m_damping = 0;
	};
}