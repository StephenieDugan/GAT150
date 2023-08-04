#pragma once
#include "FrameWork/Resource/Resource.h"
#include <map>
#include <memory>
#include <string>

namespace Twili
{
	class ResourceManager
	{
	public:
		template <typename T, typename ... TArgs>
		std::shared_ptr<T> Get(const std::string& filename, TArgs ... args);



	private:
		std::map<std::string, res_t<Resource>> m_resources;


	};

	template<typename T, typename ...TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& filename, TArgs ...args)
	{
		if (m_resources.find(filename) != m_resources.end())
		{
			return std::dynamic_pointer_cast<T>( m_resources[filename]);
		}

		res_t<T> resource = res_t<T>();
		resource->Create(filename, args...);
		m_resources[filename] = resource;


		return resource;
	}

	extern ResourceManager g_resMan;
}