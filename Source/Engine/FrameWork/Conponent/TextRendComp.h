#pragma once
#include "FrameWork/Conponent/RenderComponent.h"
#include "Renderer/Text.h"

namespace Twili
{
	class TextRendComp : public RenderComponent
	{
	public:
		CLASS_DECLARATION(TextRendComp)

		TextRendComp() = default;
		TextRendComp(const TextRendComp& other);
		bool Init() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
		void SetText(const std::string& string);
	public:
		std::string text;
		std::string fontName;
		int fontSize = 0;
	private:
		bool m_changed = true;
		std::unique_ptr<Text> m_text;
	};
}


