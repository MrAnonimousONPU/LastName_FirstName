#pragma once

#include "Unit.h"
#include "Constants.h"

class Player : Unit
{
public:
 Player(int x, int y);

 void move();
 void stepBack();
 void setPosition(int x, int y);
 void death();

 void setDirection(int direction);
 void setSuper(bool super);

 bool isSuper();
 int getLivesCount();
 int getColor();
 int getCurrentCharacter();
 Position getPosition(); 

private:
 int lives;
 int color;
 int direction;

 char characters[4];

 bool super;

 Position currentPos;
 Position oldPos;
};