#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "FrameWork/Factory.h"

namespace Twili
{
	class Sprite : public RenderComponent
	{
	public:
		CLASS_DECLARATION(Sprite)

		bool Init() override;

		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() { return m_texture->GetSize().length() * 0.5f; };

		

	public:
		std::string textureName;
		res_t<Texture> m_texture;
	};
}