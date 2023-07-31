#pragma once
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

		int getWidth() const { return m_width; };
		int getHeight() const { return m_height; };

		friend class Text;
	private:
		int m_width = 0;
		int m_height = 0;

		SDL_Renderer* m_renderer = nullptr;
		SDL_Window* m_window = nullptr;

	};

	extern Renderer g_rend;





}

