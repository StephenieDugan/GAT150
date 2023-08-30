#pragma once

#include "Font.h"
#include "Model.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "Text.h"
#include "Texture.h"

#include <string>
#include "SDL2-2.28.0/include/SDL.h"
namespace Twili
{
	void CreateWindow(const std::string& title, int width, int height);

	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		bool Init();
		bool ShutDown();

		void CreateWindow(const std::string& title, int width, int height);
		void beginFrame();
		void EndFrame();

		void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		void drawLine(int x1, int y1, int x2, int y2);
		void drawPoint(int x, int y);
		void drawLine(float x1, float y1, float x2, float y2);
		void drawPoint(float x, float y);
		void DrawTexture(class Texture* texture, const Transform& transform);
		void DrawTexture(class Texture* texture, const Rect& source, const Transform& transform);
		void DrawTexture(class Texture* texture, const Rect& source, const Transform& transform, const vec2& origin, bool flipH);
		void DrawTexture(class Texture* texture, float x, float y, float angle = 0.0f);

		int getWidth() const { return m_width; };
		int getHeight() const { return m_height; };
		SDL_Renderer* m_renderer = nullptr;
		friend class Texture;
		friend class Text;
	private:
		int m_width = 0;
		int m_height = 0;

		
		SDL_Window* m_window = nullptr;

	};

	extern Renderer g_rend;





}

