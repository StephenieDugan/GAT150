#pragma once
#include "Core/Core.h"
#include "Framework/Resource/Resource.h"
#include <vector>

namespace Twili
{
	class Renderer;

class Model : public Resource
{
public:

	Model() = default;
	Model(const std::vector<vec2>& points) : m_points{ points } {};

	// Inherited via Resource
	virtual bool Create(std::string filename, ...) override;

	bool Load(const std::string& fileName);

	void draw(Renderer& r, const vec2& position, float rotation, float scale);
	void draw(Renderer& r,const Transform& transform);

	float getRadius();

private:
	std::vector<vec2> m_points;
	Color m_color;
	float m_radius = 0;

};


}






