#pragma once
#include "Core/Math/MathUtils.h"
#include <cstdint>
#include <iostream>
#include <string>
namespace Twili
{
	class Color
	{
	public:
		
		float r, g, b, a;

		Color() : r{ 0 }, g{ 0 }, b{ 0 }, a{ 0 } {}
		Color(float r, float g, float b, float a =1) : r{ r }, g{ g }, b{ b }, a{ a } {}

		float operator [] (size_t index) const { return (&r)[index]; }
		float& operator [] (size_t index) { return (&r)[index]; }

		static uint8_t toInt(float c)
		{
			return (uint8_t)(Clamp(c, 0.0f, 1.0f) * 255);
		};
	private:


	};
	inline std::istream& operator >> (std::istream& stream, Color& color)
	{
		std::string line;
		std::getline(stream, line);
		//red
		std::string str = line.substr(line.find("{")+1, line.find(",") - line.find("{")-1);
		color.r = std::stof(str);

		//green
		line = line.substr(line.find(",") + 1);
		str = line.substr(0,line.find(","));

		color.g = std::stof(str);

		//blue
		str = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
		color.b = std::stof(str);

		//alpha
		color.a = 1;

		return stream;
	}

}