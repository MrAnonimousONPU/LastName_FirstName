#pragma once

struct Position
{
	int x;
	int y;
};

class Unit
{
public:
 virtual void move() = 0;
 virtual void setDirection(int) = 0;

 virtual int getColor() = 0;
};

