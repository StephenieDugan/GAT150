#include "player.h"
#include "Weapon.h"
#include "GAAAAME.h"

#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "FrameWork/FrameWork.h"

bool Player::Init()
{
	Actor::Init();

	m_physComp = getComponent<Twili::Physics>();
	auto collisionComp = getComponent<Twili::CollisionComp>();
	if (collisionComp)
	{
		auto renderComp = getComponent<Twili::RenderComponent>();
		if (renderComp) 
		{
			float scale = transform.scale;
			collisionComp->m_radius = renderComp->getRadius() * scale;
		}
		

	}


	return true;
}
void Player::Update(float dt)
{
	Actor::Update(dt);

	float rotate = 0;
	if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	transform.rotation += rotate * m_turnRate * Twili::g_time.getDeltaTime();

	float thrust = 0;
	if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	Twili::Vector2 forward = Twili::vec2(0, -1).Rotate(transform.rotation);

	m_physComp->ApplyForce(forward * m_speed * thrust);

	//m_transform.position += forward * m_speed * thrust * Twili::g_time.getDeltaTime();

	transform.position.x = Twili::Wrap(transform.position.x, (float)Twili::g_rend.getWidth());
	transform.position.y = Twili::Wrap(transform.position.y, (float)Twili::g_rend.getHeight());

	if (transform.scale == 6)
	{
		if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!Twili::g_inputSys.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			auto weapon = INSTANTIATE(Twili::Weapon, "Rocket");
			weapon->transform = { transform.position, transform.rotation, 1 };
			weapon->Init();
			m_scene->Add(std::move(weapon));

		}
	}
	else if (transform.scale == 5 || transform.scale == 4) //2 weapons
	{
		if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE) && !Twili::g_inputSys.GetPreviousKeyDown(SDL_SCANCODE_SPACE) && tag == "Player")
		{
			auto weapon = INSTANTIATE(Twili::Weapon, "Rocket");
			weapon->transform = { transform.position, transform.rotation + Twili::degreesToRadians(10.0f), 1 };
			weapon->Init();
			m_scene->Add(std::move(weapon));

			weapon = INSTANTIATE(Twili::Weapon, "Rocket");
			weapon->transform = { transform.position, transform.rotation - Twili::degreesToRadians(10.0f), 1 };
			weapon->Init();
			m_scene->Add(std::move(weapon));
		}
	}
	else if (transform.scale == 7) //3 weapons
	{
		if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE) && !Twili::g_inputSys.GetPreviousKeyDown(SDL_SCANCODE_SPACE) && tag == "Player")
		{
			auto weapon = INSTANTIATE(Twili::Weapon, "Rocket");
			weapon->transform = { transform.position, transform.rotation + Twili::degreesToRadians(10.0f), 1 };
			weapon->Init();
			m_scene->Add(std::move(weapon));

			weapon = INSTANTIATE(Twili::Weapon, "Rocket");
			weapon->transform = { transform.position, transform.rotation, 1 };
			weapon->Init();
			m_scene->Add(std::move(weapon));

			weapon = INSTANTIATE(Twili::Weapon, "Rocket");
			weapon->transform = { transform.position, transform.rotation - Twili::degreesToRadians(10.0f), 1 };
			weapon->Init();
			m_scene->Add(std::move(weapon));
		}
	}

	if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE)) Twili::g_time.setTimeScale(0.3f);
	else Twili::g_time.setTimeScale(1.0f);



}

void Player::onCollision(Actor* other)
{
	if (other->tag == "EnemyFire" )
	{
		std::cout << "boop";
		m_health -= 10;
		if (m_health <= 0)
		{
			m_game->setLives(m_game->getLives() - 1);
			destroyed = true;
			dynamic_cast<GAAAAME*>(m_game)->setState(GAAAAME::eState::PlayerDeadStart);
			
		}
	}

	if (other->tag == "PowerUp")
	{
		if (transform.scale == 6)
		{
			transform.scale -= 1;
			other->destroyed = true;
		}
	}
	if (other->tag == "PowerUp2")
	{
		if (transform.scale == 5)
		{
			transform.scale += 2;
			other->destroyed = true;
		}
	}
	
}

