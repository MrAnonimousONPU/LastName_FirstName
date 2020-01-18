#ifndef GHOST_H
#define GHOST_H

#include <vector>
#include <cmath>
#include <string>

#include "Constants.h"
#include "Position.h"

class Ghost
{
public:
 Ghost(int x, int y, const std::vector<std::string>& map);

 void makeMove();

 void toStartPosition();
 void setPosition(int x, int y);
 void setDirection(Position direction);
 void setMode(int mode);

 int getColor() const;
 int getCharacter() const;
 int getMode() const;
 int getType() const;
 const Position& getPosition() const;
 const Position& getOldPosition() const;
 const Position& getScatterPosition() const;

 virtual ~Ghost();

protected:
 virtual Position getTargetPos() = 0;

 void setCagePos(const Position& temp);
 void setScatterPos(const Position& temp);
 void setStartMode(int mode);
 void setColor(int color);
 void setTypeGhost(int ghost);

private:
 void aviableDirections(std::vector<Position>& directions);
 void checkDirection(Position& dir, std::vector<Position>& directions);
 void upToMode(Position& target);
 void chooseBestDirection(Position& target, std::vector<Position>& directions);
 void changePosition();

 bool checkColision(Position point);
 bool isSpecific(int x, int y);

 Position reverseDirection(const Position& direction);

private:
 char character;

 int color;
 int mode;
 int typeGhost;
 int oldMode;
 int startMode;

 Position cagePos;
 Position scatterPos;
 Position pos;
 Position oldPos;
 Position startPos;
 Position direction;
 Position oldDirection;

 std::vector<std::string> map;
 int specificX[2];
 int specificY[2];
};

#endif