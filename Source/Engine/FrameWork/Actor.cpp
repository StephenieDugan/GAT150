#include "Actor.h"
#include "Conponent/RenderComponent.h"
#include "Renderer/Renderer.h"

namespace Twili {
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1.0f)
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
			
		}
		for (auto& component : m_components)
		{
			component->Update(dt);
		}


	}
	void Actor::Draw(Twili::Renderer rend)
{
	//if (m_model) m_model->draw(rend, m_transform);

		for (auto& component : m_components)
		{
			RenderComponent* boop = dynamic_cast<RenderComponent*>(component.get());
			if (boop)
			{
				boop->Draw(rend);
			}
		}


}

	void Actor::AddComponent(std::unique_ptr<Conponent> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));

	}

}

