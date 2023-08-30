#include "Sprite.h"
#include "Renderer/Renderer.h"
#include "FrameWork/Actor.h"
#include "Core/Json.h"
#include "FrameWork/ResourceManager.h"

namespace Twili
{
	CLASS_DEFINITION(Sprite);

	bool Sprite::Init()
	{
		if(!textureName.empty()) m_texture = GET_RESOURCE(Texture, textureName, g_rend);
		if (source.w == 0 && source.h == 0)
		{
			if (m_texture)
			{
				source.x = 0;
				source.y = 0;
				source.w = (int)m_texture->GetSize().x;
				source.h = (int)m_texture->GetSize().y;
			}
		}

		return true;
	}

void Sprite::Update(float dt)
{
	
}

void Sprite::Draw(Renderer& renderer)
{

	renderer.DrawTexture(m_texture.get(), source, m_owner->transform, origin, flipH);

}

void Sprite::Read(const json_t& value)
{
	READ_DATA(value, textureName);
	READ_DATA(value, source);
	READ_DATA(value, flipH);
	READ_DATA(value, origin);
}
}




