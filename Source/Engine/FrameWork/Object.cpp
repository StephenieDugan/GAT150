#include "Object.h"

namespace Twili
{
	void Object::Read(const json_t& value)
	{
		READ_DATA(value, name);
	}
}