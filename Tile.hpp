#pragma once
#include "SFML.hpp"

class Tile
{
public:

	Tile(int id)
	{
		this->id = id;
	}

	int getId()
	{
		return id;
	}

	void setId(int id)
	{
		this->id = id;
	}

private:

	int id;
};