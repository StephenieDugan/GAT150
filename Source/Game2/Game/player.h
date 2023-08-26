#pragma once
#include "FrameWork/Actor.h"
#include "FrameWork/Conponent/Physics.h"

namespace Twili
{



	class Player : public Twili::Actor
	{
	public:
		CLASS_DECLARATION(Player)
		/*Player(float speed, float turnRate, const Twili::Transform& transform) :
			Actor{ transform }, m_speed{ speed }, m_turnRate{ turnRate } {};*/

		bool Init() override;

		void Update(float dt) override;
		virtual void onCollisionEnter(Actor* actor) override;

	protected:
		float speed = 0;
		float turnRate = 0;
		float m_health = 100.0f;

		class Twili::Physics* m_physComp = nullptr;
	};
}