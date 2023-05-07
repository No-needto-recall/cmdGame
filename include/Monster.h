#pragma once
#include "Actor.h"

class Monster :
	public Actor
{
public:
	using Actor::Actor;
	Monster();
	~Monster();
};

