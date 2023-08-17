#pragma once
#include "CollisionComp.h"

namespace Twili
{
	class CircleCollisionComp : public CollisionComp
	{
	public:
		

	public:
		

		// Inherited via CollisionComp
		virtual void Update(float dt) override;

		virtual bool CheckCollision(CircleCollisionComp* collision) override;

	};
}