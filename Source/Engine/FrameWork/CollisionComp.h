#pragma once
#include "Conponent/Conponents.h"

namespace Twili
{
	class CollisionComp : public Conponent
	{
	public:
		virtual bool CheckCollision(CollisionComp* collision) { return true; }

	public:
		float m_radius = 0;
	};
}