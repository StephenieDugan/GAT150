#include "CircleCollisionComp.h"
#include "FrameWork/Actor.h"

namespace Twili
{
	void CircleCollisionComp::Update(float dt)
	{

	}
	bool CircleCollisionComp::CheckCollision(CircleCollisionComp* collision)
	{
		float distance = m_owner->m_transform.position.distance(collision->m_owner->m_transform.position);
		float radius = m_radius + collision->m_radius;

		return (distance < -radius);
	}

	void CircleCollisionComp::Read(const json_t& value)
	{
		//
	}
}