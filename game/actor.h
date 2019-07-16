#pragma once

#include "../core/core.h"
#include "../math/transform.h"
#include "../renderer/color.h"

#include "../external/core/include/core.h"

class Actor
{
public:
	Actor() {}
	virtual ~Actor() {}

	virtual const char* GetType() { return "Actor"; }

	virtual void Update(float dt);
	virtual void Draw(Core::Graphics& graphics);

	virtual bool Load(const rapidjson::Value& value);

	const std::string& GetName() { return m_name; }

	void FlagForDestruction() { m_destroy = true; }

protected:
	bool m_destroy = false;
	std::string m_name;
	transform m_transform;

	color m_color;
	std::vector<vector2> m_verticies;
};