#include "Actor.h"
#include "Conponent/RenderComponent.h"

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
	//if (m_model) m_model->draw(rend, m_transform);

		for (auto& component : m_components)
		{
			if (dynamic_cast<RenderComponent*>(component.get()))
			{
				dynamic_cast<RenderComponent*>(component.get())->Draw(rend);
			}
		}


}

	void Actor::AddComponent(std::unique_ptr<Conponent> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));

	}

}

