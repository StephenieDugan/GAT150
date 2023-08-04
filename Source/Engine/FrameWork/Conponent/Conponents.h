#pragma once


namespace Twili
{
	class Conponent
	{
	public:
		virtual void Update(float dt) =0;

	protected:
		class Actor* m_owner = nullptr;

	};



}