#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "FrameWork/FrameWork.h"

namespace Twili
{
	CLASS_DEFINITION(Weapon)

	bool Weapon::Init()
	{
		Actor::Init();

		m_physComp = getComponent<Physics>();

		auto collisionComp = getComponent<Twili::CollisionComp>();
		if (collisionComp)
		{
		}

		return true;
	}

	void Weapon::Update(float dt)
	{
		Actor::Update(dt);

		Twili::Vector2 forward = Twili::vec2(0, -1).Rotate(transform.rotation);
		m_physComp->SetVelocity(forward * speed);

		transform.position.x = Twili::Wrap(transform.position.x, (float)Twili::g_rend.getWidth());
		transform.position.y = Twili::Wrap(transform.position.y, (float)Twili::g_rend.getHeight());
	}

	void Weapon::onCollisionEnter(Actor* other)
	{
		if (other->tag != tag)
		{
			destroyed = true;
		}
	}

	void Weapon::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
	}
}