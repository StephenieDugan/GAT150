#pragma once

#include "Conponent/Conponents.h"

namespace Twili
{
	class CollisionComp : public Conponent
	{
	public:
		virtual bool CheckCollision(CollisionComp* collision) = 0;

	public:
		float m_radius = 0;
	};
}