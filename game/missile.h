#pragma once

#include "actor.h"

class Missile : public Actor
{
public:
	Missile() {}
	virtual ~Missile() {}

	const char* GetType() { return "Missile"; }

	void Update(float dt) override;

	virtual bool Load(const rapidjson::Value& value);

	virtual Missile* Clone() { return new Missile(*this); }

private:
	float m_speed = 0.0f;
	float m_rotate = 0.0f;
};