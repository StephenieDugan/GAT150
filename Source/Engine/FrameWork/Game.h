#pragma once
#include <memory>

namespace Twili
{
	class Scene;
	class Renderer;

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual bool Init() = 0;
		virtual void ShutDown() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw(Renderer& r) = 0;

		int getScore() const { return m_score; };
		void AddPoints(int points) { m_score += points; };
		int getLives() const { return m_lives; };
		void setLives(int lives) { m_lives = lives; };

		std::unique_ptr<Scene> m_scene;

	protected:
		

		int m_score = 0;
		int m_lives = 0;

	};
}

