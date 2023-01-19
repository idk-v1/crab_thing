#pragma once
#include "SFML.hpp"
#include <vector>
#include "Tile.hpp"

class World
{
public:

	void create(int width, int height)
	{
		std::vector<Tile> vt;
		Tile t(6);

		size.x = width;
		size.y = height;

		for (int x = 0; x < size.x; x++)
		{
			tiles.push_back(vt);
			for (int y = 0; y < size.y; y++)
				tiles[x].push_back(t);
		}
	}

	sf::Vector2i getSize()
	{
		return size;
	}

	int getTileId(int x, int y)
	{
		if (x < size.x && x >= 0 && y < size.y && y >= 0)
			return tiles[x][y].getId();
		return -1;
	}

private:

	sf::Vector2i size;
	std::vector<std::vector<Tile>> tiles;
};