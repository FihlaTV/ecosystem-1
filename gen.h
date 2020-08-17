#pragma once
#include <array>

enum Command
{
	die,
	stay,
	move,
	turn_left,
	turn_right,
	fotosintesis,
	eat_minerals,
	attack, // ����� ������ ���� � ����� ���������� ����� ��� �� 2 ��������
	reproduction,  // ������� �� ���
	symbiosis
};

class Gen
{
public:
	static const size_t length = 32;
	static const size_t commands = 9;
	explicit Gen(std::array<Command, length> d, double mh, size_t g = 1)
		: generation(g), mutationChance(mh), data(d) {};

	size_t generation;
	double mutationChance;
	std::array<Command, length> data;

	Command Read()
	{
		if (index + 1 == data.size())
		{
			index = 0;
			return data[data.size() - 1];
		}
		else
			return data[index++];
	}
private:

	// ��������� ������� �������
	size_t index = 0;
};
