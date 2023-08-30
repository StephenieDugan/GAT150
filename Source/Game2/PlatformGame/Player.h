#pragma once
#include "FrameWork/Actor.h"
#include "FrameWork/Conponent/Physics.h"

namespace Twili
{
	class Player : public Twili::Actor
	{
	public:
		CLASS_DECLARATION(Player)
			
		bool Init() override;

		void Update(float dt) override;
		virtual void onCollisionEnter(Actor* actor) override;
		virtual void onCollisionExit(Actor* actor) override;

	protected:
		float speed = 0;
		float jump = 0;
		int groundCount = 0;
		float maxSpeed = 0;

		class Physics* m_physComp = nullptr;
		class AnimateComp* m_spriteComp = nullptr;
	};
}


