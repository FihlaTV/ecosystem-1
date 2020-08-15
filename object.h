#pragma once
#include <vector>
const short OUTLINE = 1;
const short CELL_SIZE = 15;
const short CELL_OUTLINE = CELL_SIZE + OUTLINE;

const unsigned short LIGHT_LEVEL_POWER = 10;
const unsigned int MAX_CELL_AGE = 100; // � �����

enum Command
{
	die,
	stay,
	move_left,
	move_right,
	move_bottom,
	move_top,
	fotosintesis,
	reproduction,  // ������� �� ���
};

struct RGBColor
{
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
};

struct Object
{
	virtual RGBColor Color() = 0;
	virtual bool Outline() = 0;
};
