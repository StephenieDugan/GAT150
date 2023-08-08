#include "Weapon.h"
#include "Renderer/Renderer.h"

void Weapon::Update(float dt)
{
    Actor::Update(dt);

    Twili::Vector2 forward = Twili::vec2(0, -1).Rotate(m_transform.rotation);
    m_transform.position += forward * m_speed * Twili::g_time.getDeltaTime();
    m_transform.position.x = Twili::Wrap(m_transform.position.x, (float)Twili::g_rend.getWidth());
    m_transform.position.y = Twili::Wrap(m_transform.position.y, (float)Twili::g_rend.getHeight());
}

void Weapon::onCollision(Actor* other)
{
    if (other->m_tag != m_tag)
    {
        m_destroyed = true;
   }
}
