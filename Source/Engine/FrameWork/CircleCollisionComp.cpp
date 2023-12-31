#include "CircleCollisionComp.h"
#include "FrameWork/Actor.h"

namespace Twili
{
	CLASS_DEFINITION(CircleCollisionComp)

	void CircleCollisionComp::Update(float dt)
	{

	}
	bool CircleCollisionComp::CheckCollision(CollisionComp* collision)
	{
		float distance = m_owner->transform.position.distance(collision->m_owner->transform.position);
		float radius = m_radius + collision->m_radius;

		return (distance <= radius);
	}

	void CircleCollisionComp::Read(const json_t& value)
	{
		//
	}
}