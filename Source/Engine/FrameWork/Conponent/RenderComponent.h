#pragma once
#include "Conponents.h"

namespace Twili
{
	class RenderComponent : public Conponent
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;
		virtual float getRadius() { return 0; }
	};
}