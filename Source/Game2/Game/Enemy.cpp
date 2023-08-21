#include "Enemy.h"
#include "FrameWork/FrameWork.h"
#include "player.h"
#include "Weapon.h"

#include "Audio/AudioSystem.h"
#include "Renderer/Renderer.h"
#include "GAAAAME.h"
#include <FrameWork/Emitter.h>
#include <memory>
bool Enemy::Init()
{
	Actor::Init();

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
void Enemy::Update(float dt)
{
	Twili::Vector2 forward = Twili::vec2{0, -1}.Rotate(transform.rotation);
	Actor::Update(dt);

	Player* player = m_scene->getActor<Player>();
	if (player)
	{
		Twili::Vector2 direction = player->transform.position - transform.position;
		
		float turnAngle = Twili::vec2::SignedAngle(forward, direction.normalized());
		transform.rotation += turnAngle * dt;

		if (std::fabs(turnAngle) < Twili::degreesToRadians(30.0f))
		{
			//i see you 
		}
	}

	
	transform.position += forward * m_speed * Twili::g_time.getDeltaTime();
	transform.position.x = Twili::Wrap(transform.position.x, (float)Twili::g_rend.getWidth());
	transform.position.y = Twili::Wrap(transform.position.y, (float)Twili::g_rend.getHeight());

	m_fireTimer -= dt;

	if (m_fireTimer <= 0)
	{
		m_fireTimer = m_fireRate;
		Twili::Transform transform1{ transform.position, transform.rotation};
		std::unique_ptr<Twili::Weapon> weapon = std::make_unique<Twili::Weapon>(400.0f, transform);
		weapon->tag = "EnemyFire";
		m_scene->Add(std::move(weapon));
		std::cout << "blep";

		Twili::g_noise.AddAudio("Jump", "Jump.wav");
	}

}

void Enemy::onCollision(Actor* other)
{
	if (other->tag == "PlayerFire")
	{
		std::cout << "Blip";
		m_health -= 5;
		if (m_health <= 0) {
			
				
			if (this->tag == "Enemy2")
			{
				m_game->AddPoints(200); destroyed = true;
			}
			else if (this->tag == "Enemy3")
			{
				m_game->AddPoints(300); destroyed = true;
			}
			else if (this->tag == "Enemy4")
			{
				m_game->AddPoints(500); destroyed = true;

				std::unique_ptr<Player> player = std::make_unique<Player>(20.0f, Twili::pi, Twili::Transform{ {400, 300}, 0, 4 });
				player->tag = "Player";
				player->m_game = m_game;
				
				m_scene->Add(std::move(player));
			}
			else if (this->tag == "Enemy3")
			{
				m_game->AddPoints(5000); destroyed = true;
			}			
			else 
			{ 
				m_game->AddPoints(100); 
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
		auto emitter = std::make_unique<Twili::Emitter>(transform, data);
		emitter->lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
	
}
