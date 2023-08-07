#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "FrameWork/Conponent/Conponents.h"
#include <memory>
namespace Twili
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const Twili::Transform& transform) : 
			m_transform{ transform } 
		{}
		
		virtual void Update(float dt);
		virtual void Draw(Twili::Renderer rend);

		void AddComponent(std::unique_ptr<Conponent> component);
		template<typename T>
		T* getComponent();

		float getRadius() { return 30.0f; }
		virtual void onCollision(Actor* other) {}

		class Scene* m_scene = nullptr;
		friend class Scene;
		class Game* m_game = nullptr;


		Twili::Transform m_transform;
		std::string m_tag;
		float m_lifespan = -1.0f;
		bool m_destroyed = false;
	protected:

		std::vector<std::unique_ptr<class Conponent>> m_components;
		
	};

	template<typename T>
	inline T* Actor::getComponent()
	{
		for (auto& component : m_components)
		{
			T* result = dynamic_cast<T*> (component.get());

			if (result)
				return result;
		}
		return nullptr;
	}

}