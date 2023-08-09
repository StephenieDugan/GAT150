#include "Particle.h"
#include "Core/Math/Color.h"
#include "Renderer.h"
namespace Twili
{
	void Particle::Update(float dt)
	{
		m_data.lifetimer += dt;
		if (m_data.lifetimer >= m_data.lifetime)
		{
			m_isActive = false;
			return;
		}
		m_data.prevPosition = m_data.position;
		m_data.position += m_data.velocity * dt;
		m_data.velocity *= std::pow(1.0f - m_data.damping, dt);
	}

	void Particle::Draw(Renderer& renderer)
	{
		renderer.setColor(Color::toInt(m_data.color.r), Color::toInt(m_data.color.g), Color::toInt(m_data.color.b), Color::toInt(m_data.color.a));
		renderer.drawLine(m_data.position.x, m_data.position.y, m_data.prevPosition.x, m_data.prevPosition.y);

	}
}