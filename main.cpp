#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(lib, "sfml-system-d.lib")

#include <SFML/Graphics.hpp>

#include "environment.h"

#include <iostream>
#include <string>

using namespace std;
using namespace sf;

const double SPEED = 1.0;

const int WINDOW_POS_X = 600;
const int WINDOW_POS_Y = 100;
const char* FONT = "SourceCodePro-Black.ttf";

int main()
{
	int loopback = 0;
	// ������, �������, ����������, �������� ������� ����� ����������
	RenderWindow window(VideoMode(ENVIRONMENT_SIZE_X * CELL_OUTLINE, ENVIRONMENT_SIZE_Y * CELL_OUTLINE), "Ecosystem | Map");
	window.setPosition(sf::Vector2i(WINDOW_POS_X, WINDOW_POS_Y));

	RenderWindow setting_window(VideoMode(200, ENVIRONMENT_SIZE_Y * CELL_OUTLINE), "Ecosystem | Settings", sf::Style::Titlebar);
	setting_window.setPosition(sf::Vector2i(WINDOW_POS_X + ENVIRONMENT_SIZE_X * CELL_OUTLINE + 15, WINDOW_POS_Y));
	
	sf::RectangleShape setting_background(sf::Vector2f(setting_window.getSize().x, setting_window.getSize().y));
	setting_background.setFillColor({ 230, 230, 230 });

	sf::Font font;
	if (!font.loadFromFile(FONT))
	{
		cerr << "font doesn't loaded properly... terminating..." << endl;
	}

	sf::RectangleShape view_rect(sf::Vector2f(190, 140));
	view_rect.setPosition(5, 15);
	view_rect.setOutlineThickness(1);
	view_rect.setFillColor({ 255, 255, 255 });
	view_rect.setOutlineColor(sf::Color(0, 0, 0));

	sf::Text view_title;
	view_title.setFont(font);
	view_title.setString("view");
	view_title.setCharacterSize(16);
	view_title.setPosition(75, 3);
	view_title.setFillColor(sf::Color::Black);

	sf::RectangleShape def_view_btn(sf::Vector2f(75, 30));
	def_view_btn.setPosition(15, 35);
	def_view_btn.setOutlineThickness(1);
	def_view_btn.setFillColor({ 230, 230, 230 });
	def_view_btn.setOutlineColor(sf::Color(0, 0, 0));

	sf::Text def_view_text;
	def_view_text.setFont(font);
	def_view_text.setString("default");
	def_view_text.setCharacterSize(14);
	def_view_text.setPosition(25, 40);
	def_view_text.setFillColor(sf::Color::Black);

	sf::RectangleShape energy_view_btn(sf::Vector2f(75, 30));
	energy_view_btn.setPosition(15, 70);
	energy_view_btn.setOutlineThickness(1);
	energy_view_btn.setFillColor({ 255, 255, 255 });
	energy_view_btn.setOutlineColor(sf::Color(0, 0, 0));

	sf::Text energy_view_text;
	energy_view_text.setFont(font);
	energy_view_text.setString("energy");
	energy_view_text.setCharacterSize(14);
	energy_view_text.setPosition(27, 75);
	energy_view_text.setFillColor(sf::Color::Black);

	sf::RectangleShape species_view_btn(sf::Vector2f(75, 30));
	species_view_btn.setPosition(110, 35);
	species_view_btn.setOutlineThickness(1);
	species_view_btn.setFillColor({ 255, 255, 255 });
	species_view_btn.setOutlineColor(sf::Color(0, 0, 0));

	sf::Text species_view_text;
	species_view_text.setFont(font);
	species_view_text.setString("species");
	species_view_text.setCharacterSize(14);
	species_view_text.setPosition(120, 40);
	species_view_text.setFillColor(sf::Color::Black);


	sf::RectangleShape info_rect(sf::Vector2f(190, 215));
	info_rect.setPosition(5, 170);
	info_rect.setOutlineThickness(1);
	info_rect.setFillColor({ 255, 255, 255 });
	info_rect.setOutlineColor(sf::Color(0, 0, 0));

	sf::Text info_title;
	info_title.setFont(font);
	info_title.setString("info");
	info_title.setCharacterSize(16);
	info_title.setPosition(75, 160);
	info_title.setFillColor(sf::Color::Black);

	sf::RectangleShape cell_ico(sf::Vector2f(50, 50));
	cell_ico.setPosition(10, 180);
	cell_ico.setOutlineThickness(1);
	cell_ico.setOutlineColor(sf::Color(0, 0, 0));

	sf::Text field_title;
	field_title.setFont(font);
	field_title.setCharacterSize(12);
	field_title.setPosition(85, 180);
	field_title.setFillColor(sf::Color::Black);
	
	sf::Text cell_generation;
	cell_generation.setFont(font);
	cell_generation.setCharacterSize(12);
	cell_generation.setPosition(65, 195);
	cell_generation.setFillColor(sf::Color::Black);

	sf::Text cell_age;
	cell_age.setFont(font);
	cell_age.setCharacterSize(12);
	cell_age.setPosition(65, 210);
	cell_age.setFillColor(sf::Color::Black);

	sf::Text cell_accenergy;
	cell_accenergy.setFont(font);
	cell_accenergy.setCharacterSize(12);
	cell_accenergy.setPosition(10, 235);
	cell_accenergy.setFillColor(sf::Color::Black);

	sf::Text cell_energy;
	cell_energy.setFont(font);
	cell_energy.setCharacterSize(12);
	cell_energy.setPosition(10, 250);
	cell_energy.setFillColor(sf::Color::Black);

	sf::Text cell_hp;
	cell_hp.setFont(font);
	cell_hp.setCharacterSize(12);
	cell_hp.setPosition(10, 265);
	cell_hp.setFillColor(sf::Color::Black);

	sf::Text field_food;
	field_food.setFont(font);
	field_food.setCharacterSize(12);
	field_food.setPosition(10, 280);
	field_food.setFillColor(sf::Color::Black);

	sf::Text field_light;
	field_light.setFont(font);
	field_light.setCharacterSize(12);
	field_light.setPosition(10, 295);
	field_light.setFillColor(sf::Color::Black);

	sf::Text cell_genom;
	cell_genom.setFont(font);
	cell_genom.setCharacterSize(12);
	cell_genom.setPosition(10, 310);
	cell_genom.setFillColor(sf::Color::Black);

	sf::RectangleShape info_clear_rect(sf::Vector2f(50, 20));
	info_clear_rect.setPosition(70, 375);
	info_clear_rect.setOutlineThickness(1);
	info_clear_rect.setFillColor({ 255, 255, 255 });
	info_clear_rect.setOutlineColor(sf::Color(0, 0, 0));

	sf::Text info_clear_text;
	info_clear_text.setFont(font);
	info_clear_text.setString("clear");
	info_clear_text.setCharacterSize(12);
	info_clear_text.setPosition(82, 377);
	info_clear_text.setFillColor(sf::Color::Black);

	Environment environment;

	bool turn_on_info_block = false;
	bool pause = false;

	// ������� ���� ����������. �����������, ���� ������� ����
	while (window.isOpen())
	{
		setting_window.clear();

		// ������������ ������� ������� � �����
		Event main_event, settings_event;
		while (setting_window.pollEvent(settings_event))
		{
		}
		while (window.pollEvent(main_event))
		{
			// ������������ ����� �� �������� � ����� ������� ����?
			if (main_event.type == Event::Closed)
			{
				// ����� ��������� ���
				setting_window.close();
				window.close();
			}
			
			// ������������ ����� � �������� �����-�� �� ������
			if (main_event.type == sf::Event::KeyReleased)
			{
				// turn on\off pause
				if (main_event.key.code == sf::Keyboard::P)
				{
					pause = !pause;
				}
			}

			// ������������ ����� � �������� ���
			if (main_event.type == sf::Event::MouseButtonPressed)
			{
				if (main_event.mouseButton.button == sf::Mouse::Left)
				{
					auto info = environment.GetInfo(main_event.mouseButton.x, main_event.mouseButton.y);
					turn_on_info_block = true;
					cell_ico.setFillColor({ info.color.r, info.color.g, info.color.b });
					field_title.setString("Structure");
					string genom = "\n";
					if (info.genom.size())
					{
						field_title.setString("Cell");
						size_t ndl = 0;
						for (auto command : info.genom)
						{
							genom += to_string(static_cast<unsigned int>(command)) + ' ';
							ndl++;
							if (ndl == 11)
							{
								ndl = 0;
								genom += '\n';
							}
						}
						cell_genom.setString("Genom: " + genom);
						cell_generation.setString("Generation: " + to_string(info.generation));
						cell_age.setString("Age: " + to_string(info.age.curr) + "/" + to_string(info.age.max));
						cell_accenergy.setString("Accumulated: " + to_string(info.acc_energy));
						cell_energy.setString("Energy: " + to_string(info.energy));
						cell_hp.setString("Hp: " + to_string(info.hp));
					}
					else
					{
						cell_genom.setString("Genom: -");
						cell_generation.setString("Generation: -");
						cell_age.setString("Age: -");
						cell_accenergy.setString("Accumulated: -");
						cell_energy.setString("Energy: -");
						cell_hp.setString("Hp: -");
					}
					field_food.setString("Food  power: " + to_string(info.food_power));
					field_light.setString("Light power: " + to_string(info.light_power));
				}
			}
		}

		setting_window.draw(setting_background);
		setting_window.draw(view_rect);
		setting_window.draw(view_title);
		setting_window.draw(def_view_btn);
		setting_window.draw(def_view_text);
		setting_window.draw(energy_view_btn);
		setting_window.draw(energy_view_text);
		setting_window.draw(species_view_btn);
		setting_window.draw(species_view_text);
		setting_window.draw(info_rect);
		setting_window.draw(info_title);

		if (turn_on_info_block)
		{
			setting_window.draw(field_title);
			setting_window.draw(cell_ico);
			setting_window.draw(cell_genom);
			setting_window.draw(cell_generation);
			setting_window.draw(cell_age);
			setting_window.draw(field_food);
			setting_window.draw(field_light);
			setting_window.draw(cell_accenergy);
			setting_window.draw(cell_energy);
			setting_window.draw(cell_hp);
			setting_window.draw(info_clear_rect);
			setting_window.draw(info_clear_text);
		}

		if (!loopback && !pause)
		{
			// clear the window and draw background with background color
			window.clear(sf::Color(0, 61, 156));

			// update environment
			auto envdata = environment.Update();
			// draw all entities
			for (const auto& object : envdata)
			{
				if (object.outline)
				{
					sf::RectangleShape sprite(sf::Vector2f(CELL_SIZE, CELL_SIZE));
					sprite.setPosition(object.position.x, object.position.y);
					sprite.setOutlineThickness(OUTLINE);
					sprite.setFillColor({ object.color.r, object.color.g, object.color.b,
						(unsigned char)((unsigned char)255 - object.shadow) });
					sprite.setOutlineColor(sf::Color(0, 0, 0,
						(unsigned char)((unsigned char)255 - object.shadow)));
					window.draw(sprite);
				}
				else
				{
					sf::RectangleShape sprite(sf::Vector2f(CELL_SIZE, CELL_SIZE));
					sprite.setPosition(object.position.x, object.position.y);
					sprite.setOutlineThickness(OUTLINE);
					sprite.setFillColor({ object.color.r, object.color.g, object.color.b });
					sprite.setOutlineColor(sf::Color(object.color.r, object.color.g, object.color.b,
						(unsigned char)((unsigned char)255 - object.shadow)));
					window.draw(sprite);
				}
			}

			// ��������� ����
			window.display();
		}

		loopback++;
		
		if (loopback == 100 * SPEED)
			loopback = 0;

		setting_window.display();
	}

	return 0;
}
