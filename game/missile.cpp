#include "missile.h"
#include "scene.h"

void Missile::Update(float dt)
{
	vector2 forward = vector2::rotate(vector2::up, m_transform.rotation);
	m_transform.translation += forward * m_speed * dt;

	m_lifetime -= dt;

	if (m_lifetime <= 0)
	{
		FlagForDestruction();
	}

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

bool Missile::Load(const rapidjson::Value& value)
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
