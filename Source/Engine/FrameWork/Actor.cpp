#include "Actor.h"
#include "Conponent/RenderComponent.h"
#include "Renderer/Renderer.h"

namespace Twili {

	CLASS_DEFINITION(Actor)

	Actor::Actor(const Actor& other)
	{
		name = other.name;
		tag = other.tag;
		lifespan = other.lifespan;
		transform = other.transform;
		m_scene = other.m_scene;
		m_game = other.m_game;

		for (auto& component : other.components)
		{
			auto clone = std::unique_ptr<Conponent>(dynamic_cast<Conponent*>(component->Clone().release()));
			AddComponent(std::move(clone));
		}
	}

	bool Actor::Init()
	{
		for (auto& component : components)
		{
			component->Init();
		}

		return true;
	}

	void Actor::OnDestroy()
	{
		for (auto& component : components)
		{
			component->OnDestroy();
		}
	}

	void Actor::Update(float dt)
	{
		if (lifespan != -1.0f)
		{
			lifespan -= dt;
			destroyed = (lifespan <= 0);
			
		}
		for (auto& component : components)
		{
			component->Update(dt);
		}


	}
	void Actor::Draw(Twili::Renderer rend)
{
	//if (m_model) m_model->draw(rend, m_transform);

		for (auto& component : components)
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
		components.push_back(std::move(component));

	}

	void Actor::Read(const json_t& value)
	{
		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, persistent);
		READ_DATA(value, prototype);
		READ_DATA(value, lifespan);


		if (HAS_DATA(value, transform)) transform.Read(GET_DATA(value,transform));

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
		{
			for (auto& compValue : GET_DATA(value, components).GetArray())
			{
				std::string type;
				READ_DATA(compValue, type);

				auto component = CREATE_BASE_CLASS(Conponent, type);
				component->Read(compValue);

				AddComponent(std::move(component));
			}
		}
		
		
	}

}

