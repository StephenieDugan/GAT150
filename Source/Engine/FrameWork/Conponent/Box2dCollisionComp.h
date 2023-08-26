#pragma once
#include "FrameWork/CollisionComp.h"
#include "Physics/PhysicsSystem.h"
#include <functional>

namespace Twili
{
	class Box2dCollisionComp : public CollisionComp
	{
	public:
		using collisionFunction = std::function<void(Actor*)>;

	public:
		CLASS_DECLARATION(Box2dCollisionComp)

		virtual bool Init() override;
		virtual void Update(float dt) override;

	private:
		PhysicsSystem::CollisionData data;
		vec2 scaleOffset = vec2{ 1, 1 };
	};
}
