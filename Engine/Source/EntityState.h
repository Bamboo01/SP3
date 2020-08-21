#pragma once

struct EntityState
{
	bool active;

	EntityState()
	{
		active = true;
	}

	EntityState(bool a)
	{
		active = a;
	}
};