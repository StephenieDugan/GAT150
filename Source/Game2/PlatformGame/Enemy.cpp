#include "Enemy.h"
#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "FrameWork/FrameWork.h"

namespace Twili
{

	CLASS_DEFINITION(Enemy)

		bool Enemy::Init()
	{
		Actor::Init();

		m_physComp = getComponent<Twili::Physics>();

		return true;
	}
	void Enemy::Update(float dt)
	{
		Actor::Update(dt);
		
		Twili::vec2 forward = Twili::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->getActor<Player>();
		if (player)
		{
		Twili::vec2 direction = player->transform.position - transform.position;
			m_physComp->ApplyForce(direction.normalized() * speed);
		}
		float dir = 0;
		if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_D)) dir = 1;
		

	}

	void Enemy::onCollisionEnter(Actor* other)
	{
		if (other->tag == "Player")
		{
			std::cout << "boop";

			Twili::EventManager::Instance().DispatchEvent("AddPoints", 100);
			destroyed = true;

		}
	}

	void Enemy::onCollisionExit(Actor* other)
	{
			
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}