#include "Box2DCollisionComp.h"
#include "Box2DPhysComp.h"
#include "Sprite.h"
#include "Framework/Actor.h"

namespace Twili
{
	CLASS_DEFINITION(Box2dCollisionComp)

		bool Box2dCollisionComp::Init()
	{
		auto component = m_owner->getComponent<Box2dPhysComp>();
		if (component)
		{
			auto spritecomp = m_owner->getComponent<Sprite>();
			if (spritecomp)
			{
				if (data.size.x == 0 && data.size.y == 0)
				{
					data.size = vec2{ spritecomp->source.w, spritecomp->source.h };
				}
				data.offset = spritecomp->origin - vec2{ 0.5f,0.5f };
			}

			data.size = data.size * scaleOffset * m_owner->transform.scale;

			if (component->m_body->GetType() == b2_staticBody)
			{
				PhysicsSystem::Instance().setCollisionBoxStatic(component->m_body, data, m_owner);
			}
			else
			{
				PhysicsSystem::Instance().setCollisionBox(component->m_body, data, m_owner);
			}
		}

		return true;
	}

	void Box2dCollisionComp::Update(float dt)
	{

	}

	void Box2dCollisionComp::Read(const json_t& value)
	{
		READ_NAME_DATA(value, "size", data.size);
		READ_NAME_DATA(value, "density", data.density);
		READ_NAME_DATA(value, "friction", data.friction);
		READ_NAME_DATA(value, "resitution", data.restitution);
		READ_NAME_DATA(value, "isTrigger", data.isTrigger);

		READ_DATA(value, scaleOffset);
	}
}