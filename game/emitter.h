#pragma once

#include "actor.h"

class Emitter : public Actor
{
public:
	Emitter() {}
	virtual ~Emitter() {}

	const char* GetType() { return "Missile"; }

	void Update(float dt) override;
	void Draw(Core::Graphics& graphics) override {}

	virtual bool Load(const rapidjson::Value& value);

	virtual Emitter* Clone() { return new Emitter(*this); }

private:
	float m_lifespan = 3.0f;
	float m_spawnRate = 0.0f;
	float m_spawnTimer = 0.0f;

	vector2 m_lifespanRange;
	vector2 m_velocityRange;
	vector2 m_angleRange;

	float m_damping;

	std::vector<color> m_colors;
};