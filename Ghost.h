#pragma once

#include <vector>
#include <cmath>
#include <string>

#include "Constants.h"
#include "Position.h"

class Ghost
{
public:
 Ghost(int x, int y, int typeGhost,const std::vector<std::string>& map);

 void move(int playerX, int playerY);

 void setPosition(int x, int y);
 void setStartPosition();
 void setDirection(int direction);
 void setMode(int mode);

 int getColor();
 int getCharacter();
 int getMode();
 int getType();
 Position getPosition();
 Position getOldPosition();
 Position getScatterPosition();

private:
 int color;
 int direction;
 int oldDirection;
 int mode;
 int oldMode;
 int typeGhost;
 int startMode;

 char character;

 Position cagePos;
 Position scatterPos;
 Position pos;
 Position oldPos;
 Position startPos;

 void aviableDirections(std::vector<int>& directions);
 void changePosition();

 int reverseDirection(int direction);

 bool checkColision(int x, int y);
 bool isSpecific(int x, int y);

 std::vector<std::string> map;
 int specificX[2];
 int specificY[2];
};