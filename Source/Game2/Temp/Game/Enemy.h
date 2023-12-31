#pragma once
# include "FrameWork/Actor.h"
class Enemy: public Twili::Actor
{
public:
	Enemy(float speed, float turnRate, const Twili::Transform& transform, std::shared_ptr<Twili::Model> model) :
		Actor{ transform, model }, m_speed{ speed }, m_turnRate{ turnRate } 
	{
		m_fireRate = 2.0f;
		m_fireTimer = m_fireRate;
	}

	void Update(float dt) override;
	void onCollision(Actor* actor) override;
	float m_health = 5.0f;
protected:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;
	
};

