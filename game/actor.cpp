#include "actor.h"

void Actor::Update(float dt)
{
	if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) m_transform.rotation -= m_transform.rotation;
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) m_transform.rotation += m_transform.rotation;

	vector2 forward = vector2::rotate(vector2::right, m_transform.rotation);
	if (Core::Input::IsPressed(Core::Input::KEY_UP))
	{
		m_transform.translation += forward;
	}

	if (m_transform.translation.x > 1200.0f) m_transform.translation.x = 0.0f;
	if (m_transform.translation.x < 0.0f) 	m_transform.translation.x = 1200.0f;
	if (m_transform.translation.y > 800.0f) m_transform.translation.y = 0.0f;
	if (m_transform.translation.y < 0.0f) 	m_transform.translation.y = 800.0f;

}

void Actor::Draw(Core::Graphics & graphics)
{
	m_transform.update();

	graphics.SetColor(m_color);
	
	for (size_t i = 0; i < m_verticies.size() - 1; i++)
	{
		//vector2 v1 = m_transform.translation + vector2::rotate(m_verticies[i], m_transform.rotation) * m_transform.scale;
		//vector2 v2 = m_transform.translation + vector2::rotate(m_verticies[i + 1], m_transform.rotation) * m_transform.scale;
		vector2 v1 = m_verticies[i] * m_transform.mxWorld;
		vector2 v2 = m_verticies[i +1] * m_transform.mxWorld;
		graphics.DrawLine(v1.x, v1.y, v2.x, v2.y);
	}
}

bool Actor::Load(const rapidjson::Value & value)
{
	bool success = false;

	if (json::get_string(value, "name", m_name) && json::get_string(value, "tag", m_tag))
	{
		const rapidjson::Value & tvalue = value["transform"];
		if (tvalue.IsObject())
		{
			m_transform.Load(tvalue);

			if (json::get_color(value, "color", m_color))
			{
				success = true;
				if (value.HasMember("vertex"))
				{
					const rapidjson::Value& vvalue = value["vertex"];

					if (vvalue.IsArray())
					{
						json::get_vector2(vvalue, "v", m_verticies);
					}
				}
				
			}
		}
	}

	return success;
}
