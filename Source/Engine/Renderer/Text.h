#pragma once

#include "Font.h"
#include "Core/Math/Color.h"
#include <string>
#include <memory>

struct SDL_Texture;
namespace Twili
{
	class Renderer;
	class Text
	{
	public:
		Text() = default;
		Text(std::shared_ptr<Twili::Font> font) : m_font{ font } {};
		~Text();

		void Create(Renderer& r, const std::string& text, const Color& color);
		void Draw(Renderer& r, int x, int y);

		void Draw(Renderer& r, const class Transform& transform);


	private:
		std::shared_ptr<Twili::Font> m_font;
		 SDL_Texture* m_texture = nullptr;

	};
}
