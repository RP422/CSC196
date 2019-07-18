#pragma once

#include "matrix33.h"
#include "../core/core.h"

struct transform
{
	vector2 translation;
	float rotation;
	vector2 scale;

	matrix33 mxWorld;

	transform() {}
	transform(vector2& translation, float rotation, vector2 scale) :
		translation(translation),
		rotation(rotation),
		scale(scale) {}

	bool Load(const rapidjson::Value& value);

	void update();
};