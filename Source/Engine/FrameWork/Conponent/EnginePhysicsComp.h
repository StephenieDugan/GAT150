#pragma once
#include "Physics.h"

namespace Twili
{
	

	class EnginePhysicsComp : public Physics
	{
	public:
		CLASS_DECLARATION(EnginePhysicsComp)
		// Inherited via Physics
		virtual void Update(float dt) override;

		virtual void ApplyForce(const vec2& force) override;

	};
}