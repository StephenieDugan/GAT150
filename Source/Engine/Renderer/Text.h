#pragma once
#include "Renderer.h"
#include "Font.h"
#include "Core/Color.h"
#include <string>
#include <memory>

namespace Twili
{
	class Text
	{
	public:
		Text() = default;
		Text(std::shared_ptr<Twili::Font> font) : m_font{ font } {};
		~Text();

		void Create(Renderer& r, const std::string& text, const Color& color);
		void Draw(Renderer& r, int x, int y);


	private:
		std::shared_ptr<Twili::Font> m_font;
		struct SDL_Texture* m_texture = nullptr;

	};
}
