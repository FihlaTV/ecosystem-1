#pragma once

#include "cell_herbivorous.h"

#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <ctime>
#include <array>
#include <cmath>
#include "glass.h"
#include "water.h"
#include "air.h"
#include "ceramic.h"
#include "earth.h"
#include "sand.h"

#include <memory>
#include <ctime>
#include <array>

using namespace std;

const int CELL_START_COUNT = 4;

const int ENVIRONMENT_SIZE_X = 15;
const int ENVIRONMENT_SIZE_Y = 80;

using MapTerrain = std::array<std::array<std::shared_ptr<Structure>, ENVIRONMENT_SIZE_X>, ENVIRONMENT_SIZE_Y>;

#define GLASS std::shared_ptr<Structure>(new Glass())
#define WATER std::shared_ptr<Structure>(new Water())
#define AIR std::shared_ptr<Structure>(new Air())
#define CERAMIC std::shared_ptr<Structure>(new Ceramic())
#define EARTH std::shared_ptr<Structure>(new Earth())
#define SAND std::shared_ptr<Structure>(new Sand())


struct Position
{
	size_t x;
	size_t y;
};

bool operator == (const Position& lhs, const Position& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

using CellId = size_t;
using ObjectId = size_t;
using PositionId = size_t;

struct DrawData
{
	Position position;
	RGBColor color;
	bool outline;
	unsigned char shadow;
};

struct Info
{
	RGBColor color;
	struct Age
	{
		size_t curr = 0;
		size_t max = 0;
	} age;
	vector<Gen::Command> genom;
	unsigned short hp = 0;
	size_t energy = 0;
	size_t generation = 0;
	size_t light_power = 0;
	size_t food_power = 0;
	double ch_of_mut;
};

struct LightLevel
{
	size_t power;
	size_t power_max;
};

class Environment
{
public:
	explicit Environment()
	{
		size_t count = 0;
		srand(time(0) + rand());
		for (size_t y = 0; y < ENVIRONMENT_SIZE_Y; y++)
		{
			for (size_t x = 0; x < ENVIRONMENT_SIZE_X; x++)
			{
				// set up simply aquarium
				if ((x == 0 || x == ENVIRONMENT_SIZE_X - 1) ||
					(y == ENVIRONMENT_SIZE_Y - 1))
				{
					terrain[y][x] = shared_ptr<Structure>(new Glass());
				}
				else
				{
					terrain[y][x] = shared_ptr<Structure>(new Water());

					// put minerals
					if (y > (ENVIRONMENT_SIZE_Y - ENVIRONMENT_SIZE_Y / 8))
					{
						terrain[y][x]->SetFood(5000 * (double(y) / ENVIRONMENT_SIZE_Y));
					}

					// put first cells
					if (((rand() % 100) == 0) && count < CELL_START_COUNT)
					{
						count++;
						//double mutation_chance = static_cast<double>((rand() % 101) / (double)100);
						terrain[y][x]->SetEntity(
							new CellHerbivorous(
								0, 
								Genome::length / 2,
								200, 
								100,
								0.01,
								50,
								{ 0.3 }
							)
						);
					}
				}

				// set up light
				size_t power = LIGHT_POWER;
				if (y != 0)
					power = terrain[y - 1][x]->Transparency() * terrain[y - 1][x]->GetLightPower();

				terrain[y][x]->SetLightPower(power);
			}
		}
	}
	
	void Update()
	{
		size_t y = ENVIRONMENT_SIZE_Y - 2;
		while (true)
		{
			size_t x = ENVIRONMENT_SIZE_X - 1;
			while (true)
			{
				vector<Gen::Command> commands;
				terrain[y][x]->Tic(commands);
				for (auto command : commands)
				{
					Event(command, x, y);
				}

				// gravitation effect
				if (terrain[y][x]->IsContainsFood())
				{
					if (terrain[y + 1][x]->IsWalkable())
					{
						if (!terrain[y + 1][x]->IsContainsFood())
						{
							terrain[y + 1][x]->SetFood(terrain[y][x]->GetFood());
							terrain[y][x]->DelFood();
						}
					}
				}
				if (x == 0)
					break;
				x--;
			}
			if (y == 0)
				break;
			y--;
		}
	}

	vector<DrawData> UpdateColors()
	{
		vector<DrawData> result;
		
		for (size_t y = 0; y < ENVIRONMENT_SIZE_Y; y++)
		{
			for (size_t x = 0; x < ENVIRONMENT_SIZE_X; x++)
			{
				// set up light
				size_t power = LIGHT_POWER;
				if (y != 0)
					power = terrain[y - 1][x]->Transparency() * terrain[y - 1][x]->GetLightPower();
				terrain[y][x]->SetLightPower(power);

				terrain[y][x]->Untick();

				DrawData stat;
				switch (view)
				{
				case view_settings::terrain:
					stat.color = terrain[y][x]->TerrainColor();
					break;
				case minerals:
					stat.color = terrain[y][x]->MineralsColor();
					break;
				case ration:
					stat.color = terrain[y][x]->RationColor();
					break;
				case energy:
					stat.color = terrain[y][x]->EnergyColor();
					break;
				case species:
					stat.color = terrain[y][x]->SpeciesColor();
					break;
				case age:
					stat.color = terrain[y][x]->AgeColor();
					break;
				case hp:
					stat.color = terrain[y][x]->HpColor();
					break;
				case survival:
					stat.color = terrain[y][x]->SurvivalColor();
					break;
				}
				stat.outline = terrain[y][x]->Outline(view);
				if (view == view_settings::terrain)
					stat.shadow = terrain[y][x]->GetLightLevel();
				else
					stat.shadow = 0;
				stat.position = { x * CELL_OUTLINE, y * CELL_OUTLINE };
				result.push_back(stat);
			}
		}

		return result;
	}

	Info GetInfo(size_t x_px, size_t y_px)
	{
		size_t x = x_px / CELL_OUTLINE;
		size_t y = y_px / CELL_OUTLINE;
		Info info;

		switch (view)
		{
		case view_settings::terrain:
			info.color = terrain[y][x]->TerrainColor();
			break;
		case minerals:
			info.color = terrain[y][x]->MineralsColor();
			break;
		case ration:
			info.color = terrain[y][x]->RationColor();
			break;
		case energy:
			info.color = terrain[y][x]->EnergyColor();
			break;
		case species:
			info.color = terrain[y][x]->SpeciesColor();
			break;
		case age:
			info.color = terrain[y][x]->AgeColor();
			break;
		case hp:
			info.color = terrain[y][x]->HpColor();
			break;
		case survival:
			info.color = terrain[y][x]->SurvivalColor();
			break;
		}

		info.light_power = terrain[y][x]->GetLightPower();
		if (terrain[y][x]->IsContainsEntity())
		{
			info.age.curr = terrain[y][x]->GetEntity()->Age();
			info.age.max = terrain[y][x]->GetEntity()->MaxAge();
			auto& data = terrain[y][x]->GetEntity()->GetGenome().data;
			for (auto command : data)
			{
				info.genom.push_back(command.Read());
			}
			info.generation = terrain[y][x]->GetEntity()->GetGenome().generation;
			info.hp = terrain[y][x]->GetEntity()->Hp();
			info.ch_of_mut = terrain[y][x]->GetEntity()->GetGenome().mutationChance;
			info.energy = terrain[y][x]->GetEntity()->Energy();
		}
		if (terrain[y][x]->IsContainsFood())
		{
			info.food_power = terrain[y][x]->GetFood().Get();
		}
 		return info;
	}

	view_settings GetView()
	{
		return view;
	}
	void SetView(view_settings new_val)
	{
		view = new_val;
	}
private:

	view_settings view = view_settings::terrain;
		
	void Event(Gen::Command command, size_t x, size_t y)
	{
		switch (command)
		{
		case Gen::Command::sleep:
			terrain[y][x]->GetEntity()->DecreaceEnergy(1);
			break;
		case Gen::Command::stay:
			terrain[y][x]->GetEntity()->DecreaceEnergy(5);
			break;
		case Gen::Command::die:
			if (terrain[y][x]->IsContainsFood())
				terrain[y][x]->GetFood().Put(terrain[y][x]->GetEntity()->Energy() + 100);
			else
				terrain[y][x]->SetFood(terrain[y][x]->GetEntity()->Energy() + 100);

			terrain[y][x]->DelEntity();
			break;
		case Gen::Command::move:
		{
			Position new_position = GetViewedPosition(terrain[y][x]->GetEntity()->GetView(), { x, y });

			if (new_position == Position{ x, y })
				break;

			if (terrain[new_position.y][new_position.x]->IsWalkable() && !terrain[new_position.y][new_position.x]->IsContainsEntity())
			{
				terrain[y][x]->GetEntity()->DecreaceEnergy(10);
				terrain[new_position.y][new_position.x]->SetEntity(terrain[y][x]->GetEntity());
				terrain[y][x]->ClearEntity();
			}
			break;
		}
		case Gen::Command::turn_left:
		{
			unsigned short old_side = terrain[y][x]->GetEntity()->GetView();
			view_side new_side = static_cast<view_side>(old_side == 0 ? 7 : old_side - 1);
			terrain[y][x]->GetEntity()->SetView(new_side);
			terrain[y][x]->GetEntity()->DecreaceEnergy(8);
		}
			break;
		case Gen::Command::turn_right:
		{
			unsigned short old_side = terrain[y][x]->GetEntity()->GetView();
			view_side new_side = static_cast<view_side>(old_side == 7 ? 0 : old_side + 1);
			terrain[y][x]->GetEntity()->SetView(new_side);
			terrain[y][x]->GetEntity()->DecreaceEnergy(8);
		}
			break;
		case Gen::Command::eat:
		{
			Position viewed_pos = GetViewedPosition(terrain[y][x]->GetEntity()->GetView(), { x, y });

			terrain[y][x]->GetEntity()->Eat(&(*terrain[y][x]), &(*terrain[viewed_pos.y][viewed_pos.x]));

			break;
		}
		case Gen::Command::separation:
		{
			if (terrain[y][x]->GetEntity()->Energy() < terrain[y][x]->GetEntity()->SeparationCost())
				break;

			Position new_position = GetViewedPosition(terrain[y][x]->GetEntity()->GetView(), { x,y });

			if (new_position == Position{ x, y })
				break;

			if (!terrain[new_position.y][new_position.x]->IsContainsEntity() && terrain[new_position.y][new_position.x]->IsWalkable())
			{
				terrain[new_position.y][new_position.x]->SetEntity(terrain[y][x]->GetEntity()->Separation());
				break;
			}
			break;
		}
		case Gen::Command::birth:
		{
			if (terrain[y][x]->GetEntity()->Energy() < terrain[y][x]->GetEntity()->BirthCost())
				break;

			Position new_position = GetViewedPosition(terrain[y][x]->GetEntity()->GetView(), { x,y });

			if (new_position == Position{ x, y })
				break;

			if (!terrain[new_position.y][new_position.x]->IsContainsEntity() && terrain[new_position.y][new_position.x]->IsWalkable())
			{
				terrain[new_position.y][new_position.x]->SetEntity(terrain[y][x]->GetEntity()->Birth());
				break;
			}
			break;
		}
		}
	}

	Position GetViewedPosition(view_side view, Position init)
	{
		Position viewed_position = init;
		switch (view)
		{
		case view_side::left:
			if (init.x > 0)
			{
				viewed_position.x--;
			}
			break;
		case view_side::right:
			if (init.x < ENVIRONMENT_SIZE_X)
			{
				viewed_position.x++;
			}
			break;
		case view_side::bottom:
			if (init.y > 0)
			{
				viewed_position.y--;
			}
			break;
		case view_side::top:
			if (init.y < ENVIRONMENT_SIZE_Y)
			{
				viewed_position.y++;
			}
			break;
		case view_side::left_bottom:
			if (init.x > 0 && init.y > 0)
			{
				viewed_position.x--;
				viewed_position.y++;
			}
			break;
		case view_side::left_top:
			if (init.x > 0 && init.y > 0)
			{
				viewed_position.x--;
				viewed_position.y--;
			}
			break;
		case view_side::right_bottom:
			if (init.y < ENVIRONMENT_SIZE_Y && init.x < ENVIRONMENT_SIZE_X)
			{
				viewed_position.y++;
				viewed_position.x++;
			}
			break;
		case view_side::right_top:
			if (init.y > 0 && init.x < ENVIRONMENT_SIZE_X)
			{
				viewed_position.y--;
				viewed_position.x++;
			}
			break;
		}
		return viewed_position;
	}

	MapTerrain terrain;
};
