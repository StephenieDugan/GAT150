#include "Enemy.h"
#include "FrameWork/Scene.h"
#include "player.h"
#include "Weapon.h"

#include "Audio/AudioSystem.h"
#include "Renderer/Renderer.h"
#include "GAAAAME.h"
#include <FrameWork/Emitter.h>
#include <memory>
void Enemy::Update(float dt)
{
	Twili::Vector2 forward = Twili::vec2{0, -1}.Rotate(m_transform.rotation);
	Actor::Update(dt);

	Player* player = m_scene->getActor<Player>();
	if (player)
	{
		Twili::Vector2 direction = player->m_transform.position - m_transform.position;
		
		float turnAngle = Twili::vec2::SignedAngle(forward, direction.normalized());
		m_transform.rotation += turnAngle * dt;

		if (std::fabs(turnAngle) < Twili::degreesToRadians(30.0f))
		{
			//i see you 
		}
	}

	
	m_transform.position += forward * m_speed * Twili::g_time.getDeltaTime();
	m_transform.position.x = Twili::Wrap(m_transform.position.x, (float)Twili::g_rend.getWidth());
	m_transform.position.y = Twili::Wrap(m_transform.position.y, (float)Twili::g_rend.getHeight());

	m_fireTimer -= dt;

	if (m_fireTimer <= 0)
	{
		m_fireTimer = m_fireRate;
		Twili::Transform transform{ m_transform.position, m_transform.rotation};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform);
		weapon->m_tag = "EnemyFire";
		m_scene->Add(std::move(weapon));
		std::cout << "blep";

		Twili::g_noise.AddAudio("Jump", "Jump.wav");
	}

}

void Enemy::onCollision(Actor* other)
{
	if (other->m_tag == "PlayerFire")
	{
		std::cout << "Blip";
		m_health -= 5;
		if (m_health <= 0) {
			
				
			if (this->m_tag == "Enemy2")
			{
				m_game->AddPoints(200); m_destroyed = true;
			}
			else if (this->m_tag == "Enemy3")
			{
				m_game->AddPoints(300); m_destroyed = true;
			}
			else if (this->m_tag == "Enemy4")
			{
				m_game->AddPoints(500); m_destroyed = true;

				std::unique_ptr<Player> player = std::make_unique<Player>(20.0f, Twili::pi, Twili::Transform{ {400, 300}, 0, 4 });
				player->m_tag = "Player";
				player->m_game = m_game;
				
				m_scene->Add(std::move(player));
			}
			else if (this->m_tag == "Enemy3")
			{
				m_game->AddPoints(5000); m_destroyed = true;
			}			
			else 
			{ 
				m_game->AddPoints(100); 
				m_destroyed = true; 
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
		Twili::Transform transform{ m_transform.position, 0, 1 };
		auto emitter = std::make_unique<Twili::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
	
}
