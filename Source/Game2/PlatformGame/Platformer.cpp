#include "Platformer.h"
#include "Enemy.h"
#include "FrameWork/FrameWork.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "FrameWork/Conponent/Sprite.h"
#include <FrameWork/Conponent/TextRendComp.h>

namespace Twili
{

	bool Platformer::Init()
	{
		Twili::g_noise.AddAudio("Jump", "Jump.wav");
		Twili::g_noise.AddAudio("MakeItPop", "MakeItPop.wav");


		m_scene = std::make_unique<Twili::Scene>();
		m_scene->Load("Scene/PlatformScene.json");
		m_scene->Load("Scene/tilemap.json");
		m_scene->Init();



		//add events
		EVENT_SUBSCRIBE("AddPoints", Platformer::AddPoints);
		EVENT_SUBSCRIBE("onPlayerDeath", Platformer::onPlayerDeath);
        m_scene->getActorByName("Player")->active = false;
		m_scene->getActorByName("Enemy")->active = false;
		m_scene->getActorByName("tile02")->active = false;
		m_scene->getActorByName("Score")->active = false; 
		m_scene->getActorByName("Winner")->active = false;
		m_scene->getActorByName("Game Over")->active = false;
		return true;
	}/*
			auto actor = INSTANTIATE(Actor, "Crate");
			actor->transform.position = { Twili::random(0,Twili::g_rend.getWidth()), 100 };
			actor->Init();

			m_scene->Add(std::move(actor));*/

	void Platformer::ShutDown()
	{
	}

	void Platformer::Update(float dt)
	{
		switch (m_state)
		{
		case Platformer::eState::Title:
		{
			
			
		
			if (Twili::g_inputSys.GetKeyDown(SDL_SCANCODE_SPACE))
			{
				m_state = eState::StartGame;
			}
		}
		break;
		case Platformer::eState::StartGame:
			m_score = 0;
			m_lives = 3;
			m_state = eState::StartLevel;
			break;
		case Platformer::eState::StartLevel:
			m_scene->getActorByName("Title")->active = false;
			//m_scene->getActorByName("Enemy")->active = true;
			m_scene->getActorByName("Player")->active = true;
			m_scene->getActorByName("Score")->active = true;
			m_state = eState::Level1;
			break;
		case Platformer::eState::Level1:
		{
			auto textrend = m_scene->getActorByName("Score")->getComponent<Twili::TextRendComp>();
			m_scene->getActorByName("Score")->active = true;
			textrend->text = "Score:" + m_score;

			if (m_score == 10)
			{
				m_state = eState::WinnerStart;
			}
		}
		break;
		case Platformer::eState::PlayerDeadStart:
			m_stateTimer = 3;
			if (m_lives == 0) m_state = eState::GameOverStart;
			else m_state = eState::PlayerDead;
			break;
		case Platformer::eState::PlayerDead:
			m_stateTimer -= dt;
			if (m_stateTimer <= 0)
			{
				m_state = eState::StartLevel;
			}
			break;
		case Platformer::eState::GameOverStart:
			m_stateTimer -= dt;
			m_scene->getActorByName("Game Over")->active = true;
			if (m_stateTimer <= 0)
			{
				m_state = eState::GameOver;
			}
			break;
		case Platformer::eState::GameOver:
			m_scene->getActorByName("Game Over")->active = false;
			m_state = eState::Title;
			break;
		case Platformer::eState::WinnerStart:
			m_stateTimer -= dt;
			m_scene->getActorByName("Winner")->active = true;
			if (m_stateTimer <= 0)
			{
				m_state = eState::Winner;
			}
			break;
		case Platformer::eState::Winner:
			m_scene->getActorByName("Winner")->active = false;
			m_state = eState::Title;
			break;
		default:
			break;
		}

		m_scene->Update(dt);

	}

	void Platformer::Draw(Twili::Renderer& r)
	{
		m_scene->Draw(r);
	}

	void Platformer::AddPoints(const Twili::Event& event)
	{
		m_score += std::get<int>(event.data);

	}

	void Platformer::onPlayerDeath(const Twili::Event& event)
	{
		m_lives--;
		auto healthchange = m_scene->getActorByName("Health")->getComponent<AnimateComp>();
		if (m_lives == 4)
		{
			healthchange->SetSequence("Minus1Health");
			m_state = eState::StartLevel;
		}
		else if (m_lives == 3)
		{
			healthchange->SetSequence("Minus2Health");
			m_state = eState::StartLevel;
		}
		else if (m_lives == 2)
		{
			healthchange->SetSequence("Minus3Health");
		}
		m_state = eState::GameOverStart;
	}

}
