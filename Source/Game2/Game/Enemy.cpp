#include "Enemy.h"
#include "FrameWork/FrameWork.h"
#include "player.h"
#include "Weapon.h"
#include "Core/Json.h"

#include "Audio/AudioSystem.h"
#include "Renderer/Renderer.h"
#include "GAAAAME.h"
#include <FrameWork/Emitter.h>
#include <memory>

namespace Twili
{
	CLASS_DEFINITION(Enemy)

	bool Enemy::Init()
	{
		Actor::Init();

		m_physicsComp = getComponent<Physics>();

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

	void Enemy::OnDestroy()
	{
		Actor::OnDestroy();
	}

	void Enemy::Update(float dt)
	{
		Twili::Vector2 forward = Twili::vec2{ 0, -1 }.Rotate(transform.rotation);
		Actor::Update(dt);

		Player* player = m_scene->getActor<Player>();
		if (player)
		{
			Twili::Vector2 direction = player->transform.position - transform.position;
			//turn towards player
			float turnAngle = Twili::vec2::SignedAngle(forward, direction.normalized());
			//transform.rotation += turnAngle * dt;
			m_physicsComp->ApplyTorque(turnAngle);

			if (std::fabs(turnAngle) < Twili::degreesToRadians(30.0f))
			{
				//i see you 
			}
		}

		m_physicsComp->ApplyForce(forward * speed);
		//transform.position += forward * m_speed * Twili::g_time.getDeltaTime();
		transform.position.x = Twili::Wrap(transform.position.x, (float)Twili::g_rend.getWidth());
		transform.position.y = Twili::Wrap(transform.position.y, (float)Twili::g_rend.getHeight());

		m_fireTimer -= dt;

		if (m_fireTimer <= 0)
		{
			m_fireTimer = fireRate;

			auto weapon = INSTANTIATE(Weapon, "Rocket2");
			weapon->transform = { transform.position, transform.rotation };
			weapon->Init();
			m_scene->Add(std::move(weapon));
			std::cout << "blep";

			Twili::g_noise.AddAudio("Jump", "Jump.wav");
		}

	}

	void Enemy::onCollisionEnter(Actor* other)
	{
		if (other->tag == "PlayerFire")
		{
			std::cout << "Blip";
			m_health -= 5;
			if (m_health <= 0) {


				if (this->tag == "Enemy2")
				{
					Twili::EventManager::Instance().DispatchEvent("AddPoints", 200);
					//m_game->AddPoints(200); 
					destroyed = true;
				}
				else if (this->tag == "Enemy3")
				{
					Twili::EventManager::Instance().DispatchEvent("AddPoints", 300);
					//m_game->AddPoints(300); 
					destroyed = true;
				}
				else if (this->tag == "Enemy4")
				{
					Twili::EventManager::Instance().DispatchEvent("AddPoints", 500);
					//m_game->AddPoints(500);
					destroyed = true;

					auto player = INSTANTIATE(Player, "Player");
					player->transform = { player->transform.position, player->transform.rotation, 4 };
					player->Init();
					m_scene->Add(std::move(player));
				}
				else if (this->tag == "Enemy3")
				{
					Twili::EventManager::Instance().DispatchEvent("AddPoints", 5000);
					//m_game->AddPoints(5000); 
					destroyed = true;
				}
				else
				{
					Twili::EventManager::Instance().DispatchEvent("AddPoints", 100);
					//m_game->AddPoints(100); 
					destroyed = true;
				}
			}

			Twili::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 0;
			data.angle = 0;
			data.angleRange = Twili::pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMax = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;
			data.color = Twili::Color{ 1, 1, 0, 1 };
			Twili::Transform transform1{ transform.position, 0, 1 };
			auto emitter = std::make_unique<Twili::Emitter>(transform1, data);
			emitter->lifespan = 1.0f;
			m_scene->Add(std::move(emitter));
		}

	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
		READ_DATA(value, fireRate);
	}
}