#include "transform.h"

bool transform::Load(const rapidjson::Value& value)
{
	bool success = false;

	if (json::get_vector2(value, "position", translation))
	{
		if (json::get_float(value, "rotation", rotation))
		{
			if (json::get_vector2(value, "scale", scale))
			{
				success = true;
			}
		}
	}

	return success;
}
