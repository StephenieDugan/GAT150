#include "ModRendComp.h"
#include "FrameWork/Actor.h"

namespace Twili
{
void ModRendComp::Update(float dt)
{

}

void ModRendComp::Draw(Renderer& rend)
{
	m_model->draw(rend, m_owner->m_transform);



}
}

