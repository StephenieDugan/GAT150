#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"


namespace Twili
{
	class ModRendComp : public RenderComponent
	{
	public:
		CLASS_DECLARATION(ModRendComp)
			bool Init() override;

		void Update(float dt);
		void Draw(class Renderer& rend) override;

		virtual float getRadius() override { return m_model->getRadius(); }

	public:
		std::string modelName;
		res_t<Model> m_model;

	};
}