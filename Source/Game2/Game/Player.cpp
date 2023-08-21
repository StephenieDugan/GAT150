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
			Twili::Transform transform1{ transform.position, transform.rotation, 1};
			std::unique_ptr<Twili::Weapon> weapon = std::make_unique<Twili::Weapon>(400.0f, transform1);
			weapon->tag = "PlayerFire";

			//create components
			std::unique_ptr<Twili::Sprite> component = std::make_unique<Twili::Sprite>();
			component->m_texture = GET_RESOURCE(Twili::Texture,"New Piskel-1.png.png", Twili::g_rend);
			weapon->AddComponent(std::move(component));

			auto collisionComp = std::make_unique<Twili::CircleCollisionComp>();
			collisionComp->m_radius = 30.0f;
			weapon->AddComponent(std::move(collisionComp));

			weapon->Init();
			m_scene->Add(std::move(weapon));
		}
	}
	else if (transform.scale == 5 || transform.scale == 4) //2 weapons
	{
		if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE) && !Twili::g_inputSys.GetPreviousKeyDown(SDL_SCANCODE_SPACE) && tag == "Player")
		{
			Twili::Transform transform1{ transform.position, transform.rotation + Twili::degreesToRadians(10.0f), 1};
			std::unique_ptr<Twili::Weapon> weapon = std::make_unique<Twili::Weapon>(400.0f, transform1);
			weapon->tag = "PlayerFire";

			//create components
			auto component = std::make_unique<Twili::Sprite>();
			component->m_texture = GET_RESOURCE(Twili::Texture,"New Piskel-1.png.png", Twili::g_rend);
			weapon->AddComponent(std::move(component));

			auto collisionComp = std::make_unique<Twili::CircleCollisionComp>();
			collisionComp->m_radius = 30.0f;
			weapon->AddComponent(std::move(collisionComp));

			weapon->Init();
			m_scene->Add(std::move(weapon));

			Twili::Transform transform2{ transform.position, transform.rotation - Twili::degreesToRadians(10.0f), 1};
			weapon = std::make_unique<Twili::Weapon>(400.0f, transform2);
			weapon->tag = "PlayerFire";

			//create components
			component = std::make_unique<Twili::Sprite>();
			component->m_texture = GET_RESOURCE(Twili::Texture,"New Piskel-1.png.png", Twili::g_rend);
			weapon->AddComponent(std::move(component));

			collisionComp = std::make_unique<Twili::CircleCollisionComp>();
			collisionComp->m_radius = 30.0f;
			weapon->AddComponent(std::move(collisionComp));

			weapon->Init();
			m_scene->Add(std::move(weapon));
		}
	}
	else if (transform.scale == 7) //3 weapons
	{
		if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE) && !Twili::g_inputSys.GetPreviousKeyDown(SDL_SCANCODE_SPACE) && tag == "Player")
		{
			Twili::Transform transform2{ transform.position, transform.rotation, 1};
			std::unique_ptr<Twili::Weapon> weapon = std::make_unique<Twili::Weapon>(400.0f, transform2);
			weapon->tag = "PlayerFire";

			//create components
			std::unique_ptr<Twili::Sprite> component = std::make_unique<Twili::Sprite>();
			component->m_texture = GET_RESOURCE(Twili::Texture,"New Piskel-1.png.png", Twili::g_rend);
			weapon->AddComponent(std::move(component));

			auto collisionComp = std::make_unique<Twili::CircleCollisionComp>();
			collisionComp->m_radius = 30.0f;
			weapon->AddComponent(std::move(collisionComp));

			weapon->Init();
			m_scene->Add(std::move(weapon));

			Twili::Transform transform1{ transform.position, transform.rotation + Twili::degreesToRadians(10.0f), 1};
			weapon = std::make_unique<Twili::Weapon>(400.0f, transform1);
			weapon->tag = "PlayerFire";

			//create components
			std::unique_ptr<Twili::Sprite> renderComponent = std::make_unique<Twili::Sprite>();
			renderComponent->m_texture = GET_RESOURCE(Twili::Texture,"New Piskel-1.png.png", Twili::g_rend);
			weapon->AddComponent(std::move(renderComponent));

			collisionComp = std::make_unique<Twili::CircleCollisionComp>();
			collisionComp->m_radius = 30.0f;
			weapon->AddComponent(std::move(collisionComp));

			weapon->Init();
			m_scene->Add(std::move(weapon));

			Twili::Transform transform3{ transform.position, transform.rotation - Twili::degreesToRadians(10.0f), 1};
			weapon = std::make_unique<Twili::Weapon>(400.0f, transform3);
			weapon->tag = "PlayerFire";

			//create components
			std::unique_ptr<Twili::Sprite> renderComponent2 = std::make_unique<Twili::Sprite>();
			renderComponent2->m_texture = GET_RESOURCE(Twili::Texture,"New Piskel-1.png.png", Twili::g_rend);
			weapon->AddComponent(std::move(renderComponent2));

			collisionComp = std::make_unique<Twili::CircleCollisionComp>();
			collisionComp->m_radius = 30.0f;
			weapon->AddComponent(std::move(collisionComp));

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

