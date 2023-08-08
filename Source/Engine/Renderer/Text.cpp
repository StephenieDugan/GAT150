#include "Text.h"
#include "Font.h"
#include "Renderer.h"
#include "SDL2-2.28.0/include/SDL.h"
#include <SDL2-2.28.0/include/SDL_ttf.h>

namespace Twili
{

Text::~Text()
{
	if (m_texture) SDL_DestroyTexture(m_texture);
};

void Text::Create(Renderer& r, const std::string& text, const Color& color)
{
	SDL_Color c{ Color::toInt(color.r), Color::toInt(color.g), Color::toInt(color.b), Color::toInt(color.a) };
	SDL_Surface* surface = TTF_RenderText_Solid(m_font->m_ttfFont, text.c_str(), c);
	m_texture = SDL_CreateTextureFromSurface(r.m_renderer, surface);
	SDL_FreeSurface(surface);
}

void Text::Draw(Renderer& r, int x, int y)
{
	int width, height;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);
	SDL_Rect rect{ x, y, width, height };
	SDL_RenderCopy(r.m_renderer, m_texture, NULL, &rect);
}

}