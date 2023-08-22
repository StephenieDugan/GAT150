#include "PhysicsSystem.h"

namespace Twili
{
	bool PhysicsSystem::Init()
	{
		b2Vec2 gravity{ 0, 10 };
		m_world = std::make_unique<b2World>(gravity);
		return true;
	}

	void PhysicsSystem::Update(float dt)
	{
		//
	}
}
