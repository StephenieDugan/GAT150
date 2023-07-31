#pragma once
#include "Core/Core.h"
#include <vector>
#include "Renderer.h"


namespace Twili
{
class Model
{
public:

	Model() = default;
	Model(const std::vector<vec2>& points) : m_points{ points } {};

	bool Load(const std::string& fileName);
	void draw(Renderer& r, const vec2& position, float rotation, float scale);
	void draw(Renderer& r, const Transform& transform);
	float getRadius();

private:
	std::vector<vec2> m_points;
	Color m_color;
	float m_radius = 0;




};


}






