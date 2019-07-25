#include "emitter.h"
#include "scene.h"
#include "../effects/particle_system.h"

void Emitter::Update(float dt)
{
	m_spawnTimer += dt;
	while (m_spawnTimer >= m_spawnRate)
	{
		m_spawnTimer -= m_spawnRate;

		float lifespan = g_random(m_lifespanRange[0], m_lifespanRange[1]);
		float velocity = g_random(m_velocityRange[0], m_velocityRange[1]);
		float angle = g_random(m_angleRange[0], m_angleRange[1]);

		color c = m_colors[g_random_int() % m_colors.size()];

		vector2 randomDirection = vector2::rotate(vector2::up, m_transform.rotation + (angle * math::DEG_TO_RAD));
		vector2 v = randomDirection * velocity;

		m_scene->GetParticleSystem()->Create(m_transform.translation, v, c, m_damping, lifespan);
	}

	m_lifespan -= dt;
	if (m_lifespan <= 0.0f)
	{
		FlagForDestruction();
	}
}

bool Emitter::Load(const rapidjson::Value & value)
{
	bool success = false;
	
	if (Actor::Load(value))
	{
		if (json::get_float(value, "lifespan", m_lifespan))
		{
			if (json::get_float(value, "spawn_rate", m_spawnRate))
			{
				json::get_vector2(value, "lifespan_range", m_lifespanRange);
				json::get_vector2(value, "velocity_range", m_velocityRange);
				json::get_vector2(value, "angle_range", m_angleRange);

				json::get_float(value, "damping", m_damping);

				const rapidjson::Value& color_value = value["colors"];
				if (color_value.IsArray())
				{
					json::get_color(color_value, "c", m_colors);
				}

				success = true;
			}
		}
	}

	return success;
}
