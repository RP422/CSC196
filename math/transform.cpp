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

void transform::update()
{
	matrix33 mxs;
	mxs.scale(scale);

	matrix33 mxr;
	mxr.rotate(rotation);

	matrix33 mxt;
	mxt.translate(translation);

	mxWorld = mxs * mxr * mxt;
}
