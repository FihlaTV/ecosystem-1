#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(lib, "sfml-system-d.lib")

#include <SFML/Graphics.hpp>

#include "environment.h"

#include <iostream>

using namespace std;
using namespace sf;

const int SPEED = 1;

int main()
{
	int loopback = 0;
	// ������, �������, ����������, �������� ������� ����� ����������
	RenderWindow window(VideoMode(ENVIRONMENT_SIZE_X, ENVIRONMENT_SIZE_Y), "Ecosystem");

	Environment environment(
		ENVIRONMENT_SIZE_X / 2, 
		ENVIRONMENT_SIZE_Y / 2,
		shared_ptr<Entity>(new Cell(Ration{ 2,1,2 }, Gen({
			move_left,
			move_right,
			move_right,
			move_left,
			fotosintesis,
			move_top,
			fotosintesis,
			fotosintesis,
		})))
	);

	// ������� ���� ����������. �����������, ���� ������� ����
	while (window.isOpen())
	{
		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == Event::Closed)
				// ����� ��������� ���
				window.close();
		}

		if (!loopback)
		{
			// clear the window and draw background with background color
			window.clear(sf::Color(0, 61, 156));

			// set up background light levels
			sf::RectangleShape background_light_level(sf::Vector2f(ENVIRONMENT_SIZE_X, Environment::light_level::surface));
			background_light_level.setPosition(0, 0);
			background_light_level.setFillColor({ 176, 207, 255 });
			window.draw(background_light_level);

			background_light_level = sf::RectangleShape(sf::Vector2f(ENVIRONMENT_SIZE_X, Environment::light_level::depth));
			background_light_level.setPosition(0, CELL_SIZE * 4);
			background_light_level.setFillColor({ 92, 156, 255 });
			window.draw(background_light_level);

			background_light_level = sf::RectangleShape((sf::Vector2f(ENVIRONMENT_SIZE_X, Environment::light_level::shallow)));
			background_light_level.setPosition(0, CELL_SIZE * 4 + CELL_SIZE * 8);
			background_light_level.setFillColor({ 0, 100, 255 });
			window.draw(background_light_level);
			
			// update entities in environment
			vector<EntityState> envdata = environment.UpdateEntities();
			// draw all entities
			for (const auto& entity : envdata)
			{
				sf::RectangleShape entity_sprite(sf::Vector2f(CELL_SIZE, CELL_SIZE));
				entity_sprite.setPosition(entity.position.x, entity.position.y);
				entity_sprite.setFillColor({ entity.color.r, entity.color.g, entity.color.b });

				window.draw(entity_sprite);
			}

			// update materials and resources in environment
			envdata = environment.UpdateMaterials();
			// draw all entities
			for (const auto& entity : envdata)
			{
				sf::RectangleShape entity_sprite(sf::Vector2f(CELL_SIZE, CELL_SIZE));
				entity_sprite.setPosition(entity.position.x, entity.position.y);
				entity_sprite.setFillColor({ entity.color.r, entity.color.g, entity.color.b });
				window.draw(entity_sprite);
			}

			// ��������� ����	
			window.display();
		}

		loopback++;
		if (loopback == 10000 * SPEED)
			loopback = 0;

	}

	return 0;
}
