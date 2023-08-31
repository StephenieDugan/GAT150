#pragma once
#include "FrameWork/Game.h"
#include "Renderer/Text.h"
#include "FrameWork/Event/EventManager.h"

namespace Twili
{



	class Platformer : public Twili::Game, Twili::IEventListener
	{
	public:

		enum class eState
		{
			Title,
			StartGame,
			StartLevel,
			Level1,
			GameOverStart,
			GameOver,
			WinnerStart,
			Winner
		};


		// Inherited via Game
		virtual bool Init() override;
		virtual void ShutDown() override;

		virtual void Update(float dt) override;
		virtual void Draw(Twili::Renderer& r) override;
		void setState(eState state) { m_state = state; }

		void AddPoints(const Twili::Event& event);
		void onPlayerDeath(const Twili::Event& event);

	private:
		eState m_state = eState::Title;
		float m_spawn_timer = 0;
		float m_spawnTime = 3;

		float m_stateTimer = 0;


	};

}

