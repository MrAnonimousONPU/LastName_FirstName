#ifndef PLAYER_H
#define PLAYER_H

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

 bool isSuper() const;
 int getLivesCount() const;
 int getColor() const;
 int getCurrentCharacter() const;
 int getDirection() const;
 const Position& getPosition() const;
 const Position& getOldPosition() const;

private:
 int lives;
 int color;
 int direction;

 char characters[4];

 bool super;

 Position currentPos;
 Position oldPos;
};

#endif