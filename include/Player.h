#pragma once

#include "Actor.h"


class Player :
	public Actor
{
public:
	using Actor::Actor;
	Player()
	{
	}

	~Player()
	{
				
	}
	
	void left() override;
	void right() override;
	void up() override;
	void down() override;

private:
};

