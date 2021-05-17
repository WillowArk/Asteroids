#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <string>
#include "Textbox.h";

struct Button : sf::RectangleShape
{
	Button();
	Button(sf::Vector2f size, std::string img_path) : sf::RectangleShape(size)
	{
		if (!bTexture.loadFromFile(img_path))
		{
			std::cout << "Failed to load " << img_path << std::endl;
		}
		setTexture(&bTexture);
		setOrigin(size.x/2, size.y/2);
	}
	bool active = false;
	sf::Texture bTexture;
};
class GameMenu
{
	std::list<sf::RectangleShape> components;

	Button start = Button(sf::Vector2f(150,60), "Textures/start_button.png");
	Button multiplayer = Button(sf::Vector2f(200, 60), "Textures/multiplayer_button.png");
	Button host = Button(sf::Vector2f(150, 60), "Textures/host_button.png");
	Button join = Button(sf::Vector2f(150, 60), "Textures/join_button.png");

	sf::RectangleShape backgroundBox1 = sf::RectangleShape(sf::Vector2f(400,300));
	sf::RectangleShape backgroundBox2 = sf::RectangleShape(sf::Vector2f(350, 100));

	Textbox textBox = Textbox();

public:
	bool active = true;

	GameMenu()
	{
		start.setPosition(800, 400);
		start.setFillColor(sf::Color::Red);
	}

	GameMenu(sf::RenderWindow &window)
	{
		
		start.setPosition(800, 400);
		multiplayer.setPosition(800, 500);

		start.active = true;
		multiplayer.active = true;

		host.setPosition(800, 400);
		join.setPosition(800, 500);

		backgroundBox1.setFillColor(sf::Color::Magenta);
		backgroundBox1.setOrigin(200, 150);
		backgroundBox1.setPosition(800, 450);

		backgroundBox2.setFillColor(sf::Color::Green);
		backgroundBox2.setOrigin(175, 50);
		backgroundBox2.setPosition(800, 450);

		components.push_back(start);
		components.push_back(multiplayer);


		runMenu(window);
	}

	void runMenu( sf::RenderWindow &window)
	{
		bool menuActive = true;
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						int xClick = event.mouseButton.x;
						int yClick = event.mouseButton.y;
						if (clickedButton(xClick, yClick, host))
						{

						}
						else if (clickedButton(xClick, yClick, join))
						{
							components.push_back(backgroundBox2);
						}
						else if (clickedButton(xClick, yClick, multiplayer))
						{
							start.active = false;
							multiplayer.active = false;

							components.push_back(backgroundBox1);
							components.push_back(host);
							components.push_back(join);

							host.active = true;
							join.active = true;
						}
						else if (clickedButton(xClick, yClick, start))
							menuActive = false;
					}
				}
				if (event.type == sf::Event::TextEntered)
				{
					textBox.typed(event.text.unicode);
				}
				if (event.type == sf::Event::Closed)
					window.close();
			}
			if (!menuActive)
				break;
			window.clear(sf::Color::Blue);
			for (auto c : components)
			{
				window.draw(c);
			}
			textBox.drawTo(window);
			window.display();
		}
	}

	bool clickedButton(int mx, int my, Button btn)
	{
		if (!btn.active)
			return false;
		//assumes origin is in middle of object
		int w = btn.getGlobalBounds().width;
		int h = btn.getGlobalBounds().height;
		std::cout << w << ", " << h << std::endl;
		int diffX = abs(mx - btn.getPosition().x);
		int diffY = abs(my - btn.getPosition().y);

		if (diffX < w / 2 && diffY < h / 2)
		{
			return true;
		}

		return false;
	}

};

