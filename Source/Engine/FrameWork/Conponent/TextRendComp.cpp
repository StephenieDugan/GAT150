#include "TextRendComp.h"
#include "FrameWork/ResourceManager.h"
#include "FrameWork/Actor.h"
#include "Renderer/Text.h"

namespace Twili
{
	CLASS_DEFINITION(TextRendComp)

	TextRendComp::TextRendComp(const TextRendComp& other)
	{
		text = other.text;
		fontName = other.fontName;
		fontSize = other.fontSize;
		m_changed = true;
		m_text = std::make_unique<Text>(*other.m_text.get());
	}
	bool TextRendComp::Init()
	{
		if (!fontName.empty()) m_text = std::make_unique<Twili::Text>(GET_RESOURCE(Twili::Font, fontName, fontSize));
			
		return true;
	}
	void TextRendComp::Update(float dt)
	{

	}
	void TextRendComp::Draw(Renderer& renderer)
	{
		// update the text if changed
		if (m_changed)
		{
			m_changed = false;
			// create text using text string and color
			m_text->Create(renderer, text, { 1, 1, 1, 1 });
		}
		// draw text
		m_text->Draw(renderer, m_owner->transform); //<draw using renderer and transform>
	}
	void TextRendComp::SetText(const std::string& string)
	{
		// check if text has changed, if changed set new string and update
		if (string != text)
		{
			text = string;
			m_changed = true;
		}
	}
	void TextRendComp::Read(const json_t& value)
	{
		READ_DATA(value, text);
		READ_DATA(value, fontName);
		READ_DATA(value, fontSize);
	}
}