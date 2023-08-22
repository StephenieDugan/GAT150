#pragma once
#include "FrameWork/Singleton.h"
#include "box2d/include/box2d/b2_world.h"  
#include <memory>
namespace Twili
{
	class PhysicsSystem : public Singleton<PhysicsSystem>
	{
	public:
		bool Init();
		void Update(float dt);

		friend class Singleton;
		
	private:
		PhysicsSystem() = default;  
	private:
		std::unique_ptr<b2World> m_world;
	};
}


