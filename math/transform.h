#pragma once

#include "vector2.h"
#include "../core/core.h"

struct transform
{
	vector2 translation;
	float rotation;
	vector2 scale;

	transform() {}
	transform(vector2& translation, float roation, vector2 scale) :
		translation(translation),
		rotation(rotation),
		scale(scale) {}

	bool Load(const rapidjson::Value& value);
};