#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "FrameWork/FrameWork.h"

namespace Twili
{

	CLASS_DEFINITION(Player)

		bool Player::Init()
	{
		Actor::Init();

		m_physComp = getComponent<Physics>();
		m_spriteComp = getComponent<AnimateComp>();

		return true;
	}
	void Player::Update(float dt)
	{
		Actor::Update(dt);

		bool onGround = (groundCount > 0);
		vec2 velocity = m_physComp->m_velocity;
		float dir = 0;
		

		if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_D)) dir = 1;
		

		if (dir) 
		{
			velocity.x += speed * dir * ((onGround) ? 1 : 0.25f) * dt;
			velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
			m_physComp->SetVelocity(velocity);

			//m_physComp->ApplyForce(forward * speed * dir);
		}

		//jump
		if (onGround && Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE) && !Twili::g_inputSys.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			Twili::vec2 up = Twili::vec2{0,-1};
			m_physComp->SetVelocity(velocity + (up * jump));
		}

		//animation
		
		if (std::fabs(velocity.x) > 0.2f)
		{
			m_spriteComp->flipH = (velocity.x < -0.1f);
			m_spriteComp->SetSequence("run");
		}
		else
		{
			m_spriteComp->SetSequence("idle");
		}

	}

	void Player::onCollisionEnter(Actor* other)
	{
		if (other->tag == "EnemyFire")
		{
			std::cout << "boop";
			
				Twili::EventManager::Instance().DispatchEvent("onPlayerDeath", 0);
				destroyed = true;
			
		}

		if (other->tag == "Ground") groundCount++;
	}

	void Twili::Player::onCollisionExit(Actor* other)
	{

		if (other->tag == "Ground") groundCount--;
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);

		READ_DATA(value, maxSpeed);
	}
}