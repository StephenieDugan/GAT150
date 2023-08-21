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

		return true;
	}

void Sprite::Update(float dt)
{
	
}

void Sprite::Draw(Renderer& renderer)
{
	renderer.DrawTexture(m_texture.get(), m_owner->transform);

}

void Sprite::Read(const json_t& value)
{
	READ_DATA(value, textureName);
}
}




