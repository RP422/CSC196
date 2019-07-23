#include "enemy.h"
#include "scene.h"

void Enemy::Update(float dt)
{
	Actor* target = m_scene->GetActorByName("Player");

	if (target)
	{
		vector2 direction = target->m_transform.translation - m_transform.translation;
		float angle = vector2::get_angle(direction);
		m_transform.rotation = angle - math::HALF_PI;

		vector2 forward = vector2::rotate(vector2::up, m_transform.rotation);
		m_transform.translation += forward * m_speed * dt;
	}

	// TODO: Figure out a way for the enemy to fire missiles?

	//// With Screen Wrapping
	//if (m_transform.translation.x > 1200.0f) m_transform.translation.x = 0.0f;
	//if (m_transform.translation.x < 0.0f)   m_transform.translation.x = 1200.0f;
	//if (m_transform.translation.y > 800.0f) m_transform.translation.y = 0.0f;
	//if (m_transform.translation.y < 0.0f)   m_transform.translation.y = 800.0f;

	// Without Screen Wrapping
	if (m_transform.translation.x > 1200.0f)
	{
		FlagForDestruction();
	}
	if (m_transform.translation.x < 0.0f)
	{
		FlagForDestruction();
	}
	if (m_transform.translation.y > 800.0f)
	{
		FlagForDestruction();
	}
	if (m_transform.translation.y < 0.0f)
	{
		FlagForDestruction();
	}
}

bool Enemy::Load(const rapidjson::Value& value)
{
	bool success = Actor::Load(value);

	if (success)
	{
		success = json::get_float(value, "speed", m_speed);

		if (success)
		{
			success = json::get_float(value, "rotate", m_rotate);
		}
	}

	return success;
}

