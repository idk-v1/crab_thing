#pragma once
#include "SFML.hpp"
#include "World.hpp"
#include <iostream>
#include <vector>

class Renderer
{
public:

	Renderer()
	{
		sf::Image miss;
		sf::Color pink(255, 0, 255);
		sf::Texture texture;
		miss.create(32, 32, sf::Color(0, 0, 0));
		for (int x = 0; x < 32; x++)
			for (int y = 0; y < 32; y++)
				if ((int(x / 8) % 2 + int(y / 8) % 2) % 2)
				{
					miss.setPixel(x, y, pink);
				}
		texture.create(32, 32);
		texture.update(miss);
		tiletex.push_back(texture);

		rect.setSize(sf::Vector2f(tileSize, tileSize));

		for (int i = 0; i < tilepath.size(); i++)
		{
			if (!texture.loadFromFile("res/" + tilepath[i]))
				texture = tiletex[0];
			tiletex.push_back(texture);
		}

		for (int i = 0; i < otherpath.size(); i++)
		{
			if (!texture.loadFromFile("res/" + otherpath[i]))
				texture = tiletex[0];
			othertex.push_back(texture);
		}
	}

	void render(World &world, sf::Vector2f offset, sf::RenderWindow &window, float size)
	{
		viewx = std::ceil(window.getSize().x / tileSize) + 2;
		viewy = std::ceil(window.getSize().y / tileSize) + 2;

		window.clear();

		renderTiles(world, offset, window);
		renderPlayer(size, offset, window);

		window.display();
	}

private:

	void renderTiles(World& world, sf::Vector2f offset, sf::RenderWindow& window)
	{
		int offx, offy;

		rect.setSize(sf::Vector2f(tileSize, tileSize));
		for (int x = (offset.x - viewx); x <= (offset.x + viewx); x++)
			for (int y = (offset.y - viewy); y <= (offset.y + viewy); y++)
				if (x >= 0 && x < world.getSize().x && y >= 0 && y < world.getSize().y)
				{
					offx = window.getSize().x / 2 + viewx / 2 * tileSize + -x * tileSize;
					offy = window.getSize().y / 2 + viewy / 2 * tileSize - y * tileSize;
					rect.setPosition(offx - float(offset.x - int(offset.x)) * tileSize, offy - float(offset.y - int(offset.y)) * tileSize);
					rect.setTexture(&tiletex[world.getTileId(x, y)]);
					window.draw(rect);
				}
	}

	void renderPlayer(float size, sf::Vector2f offset, sf::RenderWindow &window)
	{
		rect.setSize(sf::Vector2f(size * tileSize, size * tileSize));
		rect.setTexture(&othertex[0]);
		rect.setPosition(window.getSize().x / 2 - size * tileSize / 2, window.getSize().y / 2 - size * tileSize / 2);
		window.draw(rect);
	}

	sf::RectangleShape rect;
	int tileSize = 32;
	int viewy = 5;
	int viewx = 10;
	std::vector<sf::Texture> tiletex;
	std::vector<sf::Texture> othertex;
	std::vector<std::string> tilepath = 
	{
		"blank.png",
		"grass.png",
		"sandy-grass.png",
		"grassy-sand.png",
		"sand.png",
		"grass-tile.png"
	};
	std::vector<std::string> otherpath =
	{
		"player.png"
	};
};