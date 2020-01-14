#pragma once

#include "Constants.h"
#include "Position.h"

class Player
{
public:
 Player(int x, int y);

 void move();
 void setPosition(int x, int y);
 void death();

 void setDirection(int direction);
 void setSuper(bool super);

 bool isSuper();
 int getLivesCount();
 int getColor();
 int getCurrentCharacter();
 int getDirection();
 Position getPosition(); 
 Position getOldPosition();

private:
 int lives;
 int color;
 int direction;

 char characters[4];

 bool super;

 Position currentPos;
 Position oldPos;
};