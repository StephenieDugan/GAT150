#include "ModRendComp.h"
#include "FrameWork/Actor.h"
#include "FrameWork/ResourceManager.h"

namespace Twili
{
	CLASS_DEFINITION(ModRendComp)

		bool ModRendComp::Init()
	{
		if(!modelName.empty()) m_model = GET_RESOURCE(Model, modelName);

		return true;
	}

	void ModRendComp::Update(float dt)
{

}

void ModRendComp::Draw(Renderer& rend)
{
	m_model->draw(rend, m_owner->transform);



}
void ModRendComp::Read(const json_t& value)
{
	READ_DATA(value, modelName);
}

}

