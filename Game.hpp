#pragma once
#include "SFML.hpp"
#include "Renderer.hpp"
#include "World.hpp"
#include "Player.hpp"
#include <chrono>

class Game
{
public:

	Game(int width, int height)
	{
		size.x = width;
		size.y = height;
	}

	void start()
	{
		window.create(sf::VideoMode(size.x, size.y), "Crab Game v00.00.02");
		window.setFramerateLimit(fps);

		world.create(500, 500);

		while (window.isOpen())
		{
			sf::Event evt;
			while (window.pollEvent(evt))
			{
				switch (evt.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					window.setView(sf::View(sf::FloatRect(0.f, 0.f, float(evt.size.width), float(evt.size.height))));
					size.x = evt.size.width;
					size.y = evt.size.height;
					break;
				case sf::Event::GainedFocus:
					focus = true;
					break;
				case sf::Event::LostFocus:
					focus = false;
					// SET ALL KEYS TO FALSE
					break;
				case sf::Event::KeyPressed:
					if (focus)
					{
						switch (evt.key.code)
						{
						case sf::Keyboard::W:
							wk = true;
							break;
						case sf::Keyboard::A:
							ak = true;
							break;
						case sf::Keyboard::S:
							sk = true;
							break;
						case sf::Keyboard::D:
							dk = true;
							break;
						}
					}
					break;
				case sf::Event::KeyReleased:
					if (focus)
					{
						switch (evt.key.code)
						{
						case sf::Keyboard::W:
							wk = false;
							break;
						case sf::Keyboard::A:
							ak = false;
							break;
						case sf::Keyboard::S:
							sk = false;
							break;
						case sf::Keyboard::D:
							dk = false;
							break;
						}
					}
					break;
				}
			}

			now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			if (last == 0)
				last = now;
			lag += now - last;
			last = now;

			while (lag >= 1000 / ups)
			{
				lag -= 1000 / ups;
				update();
			}

			render();
		}
	}

	void update()
	{
		player.changePos((int(dk) - int(ak)) * player.getSpeed(), (int(sk) - int(wk)) * player.getSpeed());
	}

	void render()
	{
		renderer.render(world, player.getPos(), window, player.getSize());
	}

private:

	sf::Vector2i size;
	sf::RenderWindow window;
	Renderer renderer;
	World world;
	Player player;
	int ups = 20, fps = 60;
	long last = 0, now = 0, lag = 0, ticks = 0;
	bool focus = true;
	bool wk = false, ak = false, sk = false, dk = false;
};