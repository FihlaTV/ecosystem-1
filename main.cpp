#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(lib, "sfml-system-d.lib")

#include <SFML/Graphics.hpp>

#include "environment.h"

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
		shared_ptr<Object>(new Cell(fotosintesis, Gen({
			move_left,
			move_left,
			skip,
			move_top,
			move_top,
			move_top,
			move_top,
			move_top,
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
			window.clear(sf::Color(156, 195, 255));

			// update environment
			vector<EntityState> envdata = environment.Update();
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
