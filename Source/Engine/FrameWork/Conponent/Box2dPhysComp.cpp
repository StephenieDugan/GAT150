#include "Box2dPhysComp.h"
#include "Framework/Actor.h"

namespace Twili
{
	CLASS_DEFINITION(Box2dPhysComp)

		bool Box2dPhysComp::Init()
	{
		m_body = PhysicsSystem::Instance().CreateBody(m_owner->transform.position, m_owner->transform.rotation, data);
		m_body->SetGravityScale(data.gravityScale);
		m_body->SetLinearDamping(data.damping);
		m_body->SetAngularDamping(data.angularDamping);

		return true;
	}

	void Box2dPhysComp::OnDestroy()
	{
		if (m_body)
		{
			m_body->SetEnabled(false);
			PhysicsSystem::Instance().destroyBody(m_body);
		}
	}

	void Box2dPhysComp::Update(float dt)
	{
		Vector2 position = B2VEC2_TO_VEC2(m_body->GetPosition());
		m_owner->transform.position = PhysicsSystem::Instance().WorldToScreen(position);
		m_owner->transform.rotation = m_body->GetAngle();
		m_velocity = B2VEC2_TO_VEC2(m_body->GetLinearVelocity());
	}

	void Box2dPhysComp::ApplyForce(const vec2& force)
	{
		m_body->ApplyForceToCenter(VEC2_TO_B2VEC2(force), true);
	}

	void Box2dPhysComp::ApplyTorque(float torque)
	{
		m_body->ApplyTorque(torque, true);
	}

	void Box2dPhysComp::SetVelocity(const vec2& velocity)
	{
		m_body->SetLinearVelocity(VEC2_TO_B2VEC2(velocity));
	}

	void Box2dPhysComp::Read(const json_t& value)
	{
		READ_NAME_DATA(value, "damping", data.damping);
		READ_NAME_DATA(value, "angularDamping", data.angularDamping);
		READ_NAME_DATA(value, "gravityScale", data.gravityScale);
		READ_NAME_DATA(value, "constrainAngle", data.constrainAngle);
		READ_NAME_DATA(value, "isDynamic", data.isDynamic);
	}
}