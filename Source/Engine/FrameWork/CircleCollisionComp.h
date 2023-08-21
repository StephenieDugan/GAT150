#pragma once
#include "CollisionComp.h"

namespace Twili
{
	class CircleCollisionComp : public CollisionComp
	{
	public:
		CLASS_DECLARATION(CircleCollisionComp)

	public:
		// Inherited via CollisionComp
		virtual void Update(float dt) override;

		virtual bool CheckCollision(CollisionComp* collision) override;

	};
}