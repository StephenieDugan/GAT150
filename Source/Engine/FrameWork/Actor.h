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
		Actor(const Twili::Transform& transform) : m_transform{ transform } {}
		Actor(const Twili::Transform& transform, std::shared_ptr<Model> model) : m_transform{ transform }, m_model{ model } {}
		
		
		virtual void Update(float dt);
		virtual void Draw(Twili::Renderer rend);

		void AddComponent(std::unique_ptr<Conponent> component);

		float getRadius() { return (m_model) ? m_model->getRadius() * m_transform.scale : 0; }
		virtual void onCollision(Actor* other) {}


		void addForce(const vec2& force) {	m_velocity += force; };
		void setDamping(float damping) { m_damping = damping; };

		class Scene* m_scene = nullptr;
		friend class Scene;
		class Game* m_game = nullptr;


		Twili::Transform m_transform;
		std::string m_tag;
		float m_lifespan = -1.0f;
		bool m_destroyed = false;
	protected:

		std::vector<std::unique_ptr<class Conponent>> m_components;
		
		std::shared_ptr<Model> m_model;

		vec2 m_velocity;
		float m_damping=0;

	};

}