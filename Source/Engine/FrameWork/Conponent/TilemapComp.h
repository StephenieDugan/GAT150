#pragma once
#include "Conponents.h"
#include <vector>

namespace Twili
{
	class TilemapComp : public Conponent
	{
	public:
		CLASS_DECLARATION(TilemapComp)

		bool Init() override;
		void Update(float dt) override;

	public:
		int numColumns = 0;
		int numRows = 0;
		vec2 size;

		std::vector<std::string> tileNames;
		std::vector<int> tiles;

	};
}
