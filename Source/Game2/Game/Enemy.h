#pragma once
# include "FrameWork/Actor.h"
#include "FrameWork/Conponent/Physics.h"

namespace Twili
{
	class Enemy : public Actor
	{
	public:
		CLASS_DECLARATION(Enemy)

		/*Enemy(float speed, float turnRate, const Twili::Transform& transform) :
			Actor{ transform }, m_speed{ speed }, m_turnRate{ turnRate }
		{
			m_fireRate = 2.0f;
			m_fireTimer = m_fireRate;
		}*/
		bool Init() override;
		void OnDestroy() override;

		void Update(float dt) override;
		void onCollisionEnter(Actor* actor) override;

		float m_health = 80.0f;
	protected:
		float speed = 0;
		float turnRate = 0;

		float fireRate = 0;
		float m_fireTimer = 0;

		Twili::Physics* m_physicsComp = nullptr;

	};

}