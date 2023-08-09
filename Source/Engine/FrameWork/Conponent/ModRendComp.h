#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"


namespace Twili
{
	class ModRendComp : public RenderComponent
	{
	public:
		void Update(float dt);
		void Draw(class Renderer& rend) override;

	public:
		res_t<Model> m_model;

	};
}