#include "Model.h"
#include "Renderer.h"
#include <sstream>

namespace Twili {
	bool Model::Load(const std::string& fileName)
	{
		std::string buffer;
		Twili::readFile(fileName, buffer);
		

		std::istringstream stream(buffer);
		stream >> m_color;
		std::string line;
		std::getline(stream, line);

		int numPoints = std::stoi(line);
		for (int i = 0; i < numPoints; i++)
		{
			vec2 point;
			stream >> point;
			m_points.push_back(point);
		}
		return true;
	}
	void Model::draw(Renderer& r, const vec2& position,float rotation, float scale)
	{
		if (m_points.empty())return;

		r.setColor(Color::toInt(m_color.r), Color::toInt(m_color.g), Color::toInt(m_color.b), Color::toInt(m_color.a));

		for (int i = 0; i < m_points.size()-1; i++)
		{
			vec2 p1 = (m_points[i]*scale).Rotate(rotation) + position;
			vec2 p2 = (m_points[i+1]*scale).Rotate(rotation) + position;

			r.drawLine(p1.x,p1.y,p2.x,p2.y);
		}
		
	}

	void Model::draw(Renderer& r, const Transform& transform)
	{
		if (m_points.empty())return;

		mat2 mx = transform.Getmatrix();

		r.setColor(Color::toInt(m_color.r), Color::toInt(m_color.g), Color::toInt(m_color.b), Color::toInt(m_color.a));

		for (int i = 0; i < m_points.size() - 1; i++)
		{
			vec2 p1 = (mx * m_points[i]) + transform.position;
			vec2 p2 = (mx * m_points[i + 1]) + transform.position;

			r.drawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	float Model::getRadius()
	{
		if (m_radius) return m_radius;

		for (auto point : m_points)
		{
			float length = point.length();
			m_radius = Max(m_radius, length);
			
		}

		return m_radius;
	}

	bool Model::Create(std::string filename, ...)
	{
		return Load(filename);
	}




}