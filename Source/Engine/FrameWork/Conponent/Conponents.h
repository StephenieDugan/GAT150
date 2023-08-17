#pragma once
#include "FrameWork/Object.h"


namespace Twili
{
	class Conponent : public Object
	{
	public:
		virtual void Update(float dt) =0;

		friend class Actor;


	protected:
		class Actor* m_owner = nullptr;

	};



}