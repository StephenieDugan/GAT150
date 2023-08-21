#pragma once
#include "FrameWork/Factory.h"
#include "Core/Json.h"
#include <string>

#define CLASS_DECLARATION(classname)\
	virtual	const char* GetClassName() {return #classname;}\
	virtual void Read(const json_t& value);\
	class Register\
		{\
		public:\
			Register()\
			{\
				Factory::Instance().Register<classname>(#classname);\
			}\
		};

#define CLASS_DEFINITION(classname)\
	 classname::Register register_class;

namespace Twili
{

	class Object
	{
	public:
		Object() = default;
		Object(const std::string& name) : name{ name } {}

		virtual ~Object() { OnDestroy(); }

		CLASS_DECLARATION(Object)

		virtual bool Init() { return true; };
		virtual void OnDestroy() {};

	protected:
		std::string name;

	};
}