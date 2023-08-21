#pragma once
#include "Object.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Conponent/Conponents.h"
#include <memory>

namespace Twili
{
	class Actor : public Object
	{
	public:
		CLASS_DECLARATION(Actor)

		Actor() = default;
		Actor(const Twili::Transform& transform) : 
			transform{ transform } 
		{}

		virtual bool Init() override;
		virtual void OnDestroy() override;
		
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


		Twili::Transform transform;
		std::string tag;
		float lifespan = -1.0f;
		bool destroyed = false;

	protected:

		std::vector<std::unique_ptr<class Conponent>> components;
		
	};

	template<typename T>
	inline T* Actor::getComponent()
	{
		for (auto& component : components)
		{
			T* result = dynamic_cast<T*> (component.get());

			if (result)
				return result;
		}
		return nullptr;
	}

}