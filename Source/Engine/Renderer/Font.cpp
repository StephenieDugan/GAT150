#include "Font.h"
#include "Core/Logger.h"
#include "Renderer.h"
#include <SDL2-2.28.0/include/SDL_ttf.h>

namespace Twili
{
Twili::Font::Font(const std::string& filename, int fontSize)
{
	Load(filename, fontSize);
}

Twili::Font::~Font()
{
	if (m_ttfFont != NULL) TTF_CloseFont(m_ttfFont);
}

bool Twili::Font::Load(const std::string& filename, int fontSize)
{
	m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);
	if (m_ttfFont = nullptr)
	{
		WARNING_LOG("failed to open font:" << filename);
		return false;
	}
	return true;
}

bool Font::Create(std::string filename, ...)
{
	va_list args;

	va_start(args, filename);

	int fontSize = va_arg(args, int);

	va_end(args);

	return Load(filename, fontSize);
}

}

