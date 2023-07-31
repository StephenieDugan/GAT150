#pragma once
#include "FrameWork/Game.h"
#include "Renderer/Text.h"

class GAAAAME : public Twili::Game
{
public:

	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Level1,
		Level2,
		Level3,
		Level4,
		Level5,
		PlayerDeadStart,
		PlayerDead,
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

private:
	eState m_state = eState::Title;
	std::shared_ptr<Twili::Font> font;
	std::shared_ptr<Twili::Font> font2;
	std::unique_ptr<Twili::Text> m_Scoretext;
	std::unique_ptr<Twili::Text> m_Livestext;
	std::unique_ptr<Twili::Text> m_Healthtext;
	std::unique_ptr<Twili::Text> m_Titletext;
	std::unique_ptr<Twili::Text> m_GOvertext;
	std::unique_ptr<Twili::Text> m_Winnertext;
	float m_spawn_timer = 0;
	float m_spawnTime = 3;

	float m_stateTimer = 0;


};