#pragma once

#include "../math/vector2.h"
#include "../renderer/color.h"

struct Particle
{
	vector2 position;
	vector2 prev_position;
	vector2 velocity;
	color hue;

	float damping;
	float lifespan;
	bool active;
};