#pragma once
#include "Core/Vector2.h"
#include "FrameWork/Resource/Resource.h"

struct SDL_Texture;
namespace Twili
{
	class Texture : Resource
	{
	public:
		Texture() = default;
		~Texture();
		
		virtual bool Create(std::string filename, ...) override;

		bool Load(const std::string& filename,class Renderer& renderer);
		vec2 GetSize();

		friend class Renderer;
	private:
		SDL_Texture* m_texture = nullptr;

		// Inherited via Resource
		
	};
}