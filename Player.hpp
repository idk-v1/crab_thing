#pragma once
#include "SFML.hpp"

class Player
{

public:

	sf::Vector2f getPos()
	{
		return pos;
	}

	void setPos(float x, float y)
	{
		pos.x = x;
		pos.y = y;
	}

	void changePos(float x, float y)
	{
		acc.x = x;
		acc.y = y;

		vel.x += acc.x;
		vel.y += acc.y;

		vel.x *= 0.9;
		vel.y *= 0.9;

		pos.x += vel.x;
		pos.y += vel.y;

		acc.x = 0;
		acc.y = 0;

		if (std::abs(vel.x) < 0.05)
			vel.x = 0;
		if (std::abs(vel.y) < 0.05)
			vel.y = 0;
	}

	float getSize()
	{
		return size;
	}

	float getSpeed()
	{
		return speed;
	}

private:

	sf::Vector2f pos = sf::Vector2f(0, 0);
	sf::Vector2f vel = sf::Vector2f(0, 0);
	sf::Vector2f acc = sf::Vector2f(0, 0);

	float size = 3.5;
	float speed = 0.1;
};