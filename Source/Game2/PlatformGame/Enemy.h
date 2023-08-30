#pragma once
#include "FrameWork/Actor.h"
#include "FrameWork/Conponent/Physics.h"

namespace Twili
{
	class Enemy : public Twili::Actor
	{
	public:
		CLASS_DECLARATION(Enemy)

			bool Init() override;

		void Update(float dt) override;
		virtual void onCollisionEnter(Actor* actor) override;
		virtual void onCollisionExit(Actor* actor) override;

	protected:
		float speed = 0;
		float jump = 0;
		

		class Twili::Physics* m_physComp = nullptr;
	};
}




