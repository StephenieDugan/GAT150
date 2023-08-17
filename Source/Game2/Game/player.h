#pragma once
#include "FrameWork/Actor.h"
#include "FrameWork/Conponent/Physics.h"

class Player : public Twili::Actor
{
public:
	Player(float speed, float turnRate, const Twili::Transform& transform) :
		Actor{ transform }, m_speed{ speed }, m_turnRate{turnRate} {};

	bool Init() override;

	void Update(float dt) override;
	virtual void onCollision(Actor* actor) override;

protected:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_health = 100.0f;

	class Twili::Physics* m_physComp = nullptr;
};