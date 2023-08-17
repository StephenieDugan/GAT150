#include "Actor.h"
#include "Conponent/RenderComponent.h"
#include "Renderer/Renderer.h"

namespace Twili {

	CLASS_DEFINITION(Actor);

	bool Actor::Init()
	{
		for (auto& component : m_components)
		{
			component->Init();
		}

		return true;
	}

	void Actor::OnDestroy()
	{
		for (auto& component : m_components)
		{
			component->OnDestroy();
		}
	}

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

	bool Actor::Read(const rapidjson::Value& value)
	{
		if (HAS_DATA(value, actors) && GET_DATA(value, actors).isArray())
		{
			for (auto& actorValue : GET_DATA(value, actors).GetArray())
			{
				std::string type;
				READ_DATA(actorValue, type);

				auto actor = CREATE_CLASS_BASE(Conponent, type);
				actor->Read(actorvalue);


			}
		}
		return true;
	}

}

