#include "Sprite.h"
#include "Renderer/Renderer.h"
#include "FrameWork/Actor.h"
#include "Core/Json.h"

namespace Twili
{
	CLASS_DEFINITION(Sprite);

	bool Sprite::Init()
	{
		if (!textureName.empty()) m_model = GET_RESOURCE(Sprite, );
	}

void Sprite::Update(float dt)
{
	
}

void Sprite::Draw(Renderer& renderer)
{
	renderer.DrawTexture(m_texture.get(), m_owner->m_transform);

}

void Sprite::Read(const json_t& value)
{
	READ_DATA(value, textureName);
}

}




