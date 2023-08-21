#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "FrameWork/FrameWork.h"

namespace Twili
{


	bool Weapon::Init()
	{

		auto collisionComp = getComponent<Twili::CollisionComp>();
		if (collisionComp)
		{
			auto renderComp = getComponent<Twili::RenderComponent>();
			if (renderComp)
			{
				float scale = transform.scale;
				collisionComp->m_radius = renderComp->getRadius() * scale;
			}


		}

		return true;
	}

	void Weapon::Update(float dt)
	{

		Twili::Vector2 forward = Twili::vec2(0, -1).Rotate(transform.rotation);
		transform.position += forward * speed * Twili::g_time.getDeltaTime();
		transform.position.x = Twili::Wrap(transform.position.x, (float)Twili::g_rend.getWidth());
		transform.position.y = Twili::Wrap(transform.position.y, (float)Twili::g_rend.getHeight());
	}

	void Weapon::onCollision(Actor* other)
	{
		if (other->tag != tag)
		{
			destroyed = true;
		}
	}

	void Weapon::Read(const json_t& value)
	{
		READ_DATA(value, speed);
	}
}