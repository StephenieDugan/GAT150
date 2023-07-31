#include "Actor.h"

namespace Twili {
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1.0f)
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
			
		}
		m_transform.position += m_velocity * dt;
		m_velocity *= std::pow(1.0f - m_damping, dt);

	}
	void Actor::Draw(Twili::Renderer rend)
{
	if (m_model) m_model->draw(rend, m_transform);
}

}

