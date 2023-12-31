#include "Transform.h"


namespace Twili
{
void Transform::Read(const json_t& value)
{
	READ_DATA(value, position);
	READ_DATA(value, scale);
	READ_DATA(value, rotation);
}
}

