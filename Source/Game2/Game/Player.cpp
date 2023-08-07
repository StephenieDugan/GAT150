#include "player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Weapon.h"
#include "FrameWork/ResourceManager.h"
#include "FrameWork/Conponent/Sprite.h"
#include "Framework/Scene.h"
#include "FrameWork/Conponent/Physics.h"
#include "GAAAAME.h"
void Player::Update(float dt)
{
	Actor::Update(dt);

	float rotate = 0;
	if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * Twili::g_time.getDeltaTime();

	float thrust = 0;
	if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	Twili::Vector2 forward = Twili::vec2(0, -1).Rotate(m_transform.rotation);

	auto physicsComponent = getComponent<Twili::Physics>();
	physicsComponent->ApplyForce(forward * m_speed * thrust);

	//m_transform.position += forward * m_speed * thrust * Twili::g_time.getDeltaTime();

	m_transform.position.x = Twili::Wrap(m_transform.position.x, (float)Twili::g_rend.getWidth());
	m_transform.position.y = Twili::Wrap(m_transform.position.y, (float)Twili::g_rend.getHeight());

	if (m_transform.scale == 6)
	{
		if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!Twili::g_inputSys.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			Twili::Transform transform1{ m_transform.position, m_transform.rotation, 1};
			std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1);
			weapon->m_tag = "PlayerFire";

			//create components
			std::unique_ptr<Twili::Sprite> component = std::make_unique<Twili::Sprite>();
			component->m_texture = Twili::g_resMan.Get<Twili::Texture>("New Piskel-1.png.png", Twili::g_rend);
			weapon->AddComponent(std::move(component));

			m_scene->Add(std::move(weapon));
		}
	}
	else if (m_transform.scale == 5 || m_transform.scale == 4) //2 weapons
	{
		if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE) && !Twili::g_inputSys.GetPreviousKeyDown(SDL_SCANCODE_SPACE) && m_tag == "Player")
		{
			Twili::Transform transform1{ m_transform.position, m_transform.rotation + Twili::degreesToRadians(10.0f), 1};
			std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1);
			weapon->m_tag = "PlayerFire";

			//create components
			std::unique_ptr<Twili::Sprite> component = std::make_unique<Twili::Sprite>();
			component->m_texture = Twili::g_resMan.Get<Twili::Texture>("New Piskel-1.png.png", Twili::g_rend);
			weapon->AddComponent(std::move(component));

			m_scene->Add(std::move(weapon));

			Twili::Transform transform2{ m_transform.position, m_transform.rotation - Twili::degreesToRadians(10.0f), 1};
			weapon = std::make_unique<Weapon>(400.0f, transform2);
			weapon->m_tag = "PlayerFire";

			//create components
			std::unique_ptr<Twili::Sprite> renderComponent = std::make_unique<Twili::Sprite>();
		renderComponent->m_texture = Twili::g_resMan.Get<Twili::Texture>("New Piskel-1.png.png", Twili::g_rend);
			weapon->AddComponent(std::move(renderComponent));

			m_scene->Add(std::move(weapon));
		}
	}
	else if (m_transform.scale == 7) //3 weapons
	{
		if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE) && !Twili::g_inputSys.GetPreviousKeyDown(SDL_SCANCODE_SPACE) && m_tag == "Player")
		{
			Twili::Transform transform{ m_transform.position, m_transform.rotation, 1};
			std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform);
			weapon->m_tag = "PlayerFire";

			//create components
			std::unique_ptr<Twili::Sprite> component = std::make_unique<Twili::Sprite>();
			component->m_texture = Twili::g_resMan.Get<Twili::Texture>("New Piskel-1.png.png", Twili::g_rend);
			weapon->AddComponent(std::move(component));

			m_scene->Add(std::move(weapon));

			Twili::Transform transform1{ m_transform.position, m_transform.rotation + Twili::degreesToRadians(10.0f), 1};
			weapon = std::make_unique<Weapon>(400.0f, transform1);
			weapon->m_tag = "PlayerFire";

			//create components
			std::unique_ptr<Twili::Sprite> renderComponent = std::make_unique<Twili::Sprite>();
			renderComponent->m_texture = Twili::g_resMan.Get<Twili::Texture>("New Piskel-1.png.png", Twili::g_rend);
			weapon->AddComponent(std::move(renderComponent));

			m_scene->Add(std::move(weapon));

			Twili::Transform transform2{ m_transform.position, m_transform.rotation - Twili::degreesToRadians(10.0f), 1};
			weapon = std::make_unique<Weapon>(400.0f, transform2);
			weapon->m_tag = "PlayerFire";

			//create components
			std::unique_ptr<Twili::Sprite> renderComponent2 = std::make_unique<Twili::Sprite>();
			renderComponent2->m_texture = Twili::g_resMan.Get<Twili::Texture>("New Piskel-1.png.png", Twili::g_rend);
			weapon->AddComponent(std::move(renderComponent2));

			m_scene->Add(std::move(weapon));
		}
	}

	if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE)) Twili::g_time.setTimeScale(0.3f);
	else Twili::g_time.setTimeScale(1.0f);



}

void Player::onCollision(Actor* other)
{
	if (other->m_tag == "EnemyFire" )
	{
		std::cout << "boop";
		m_health -= 10;
		if (m_health <= 0)
		{
			m_game->setLives(m_game->getLives() - 1);
			m_destroyed = true;
			dynamic_cast<GAAAAME*>(m_game)->setState(GAAAAME::eState::PlayerDeadStart);
			
		}
	}

	if (other->m_tag == "PowerUp")
	{
		if (m_transform.scale == 6)
		{
			m_transform.scale -= 1;
			other->m_destroyed = true;
		}
	}
	if (other->m_tag == "PowerUp2")
	{
		if (m_transform.scale == 5)
		{
			m_transform.scale += 2;
			other->m_destroyed = true;
		}
	}
	
}

