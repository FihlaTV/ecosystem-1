#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(lib, "sfml-system-d.lib")

#include <SFML/Graphics.hpp>

#include "environment.h"

using namespace sf;

int main()
{
	// ������, �������, ����������, �������� ������� ����� ����������
	RenderWindow window(VideoMode(800, 500), "Ecosystem");
	sf::RectangleShape background(sf::Vector2f(120.f, 50.f));
	background.setPosition(10.f, 50.f);
	background.setFillColor(sf::Color(150, 199, 255));
	background.setSize(sf::Vector2f(100.f, 100.f));
	
	Environment environment(new Cell(Gen({0,1,2,5,3,5,18,6})));

	// ������� ���� ����������. �����������, ���� ������� ����
	while (window.isOpen())
	{
		environment.Update();

		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == Event::Closed)
				// ����� ��������� ���
				window.close();
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(background);

		// ��������� ����	
		window.display();
	}

	return 0;
}
