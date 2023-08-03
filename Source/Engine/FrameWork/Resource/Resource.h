#pragma once
#include <string>

namespace Twili
{
	class Resource
	{
	public:
		virtual ~Resource() = default;

		virtual bool Create(std::string filename, ...) =0;

	private:



	};
}