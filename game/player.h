#pragma once

#include "actor.h"

class Player : public Actor
{
public:
	Player() {}
	virtual ~Player() {}

	const char* GetType() { return "Player"; }

	void Update(float dt) override;

private:

};