#pragma once
#include "Physics.h"
#include "Physics/PhysicsSystem.h"

class b2Body;

namespace Twili
{
	class Box2dPhysComp : public Physics
	{
	public:
		CLASS_DECLARATION(Box2dPhysComp)

			bool Init() override;
		void OnDestroy() override;

		void Update(float dt) override;

		virtual void ApplyForce(const vec2& force) override;
		virtual void ApplyTorque(float torque) override;
		virtual void SetVelocity(const vec2& velocity) override;

		friend class Box2dCollisionComp;

		b2Body* m_body = nullptr;
	private:
		PhysicsSystem::RigidBodyData data;
	};
}