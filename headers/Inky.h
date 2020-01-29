#ifndef INKY_H
#define INKY_H

#include "Ghost.h"
#include "Player.h"
#include "Position.h"

class Inky : public Ghost
{
public:
 Inky(int x, int y, const std::vector<std::string>& map, const Player& pacman,
  const Ghost& blinky);

protected:
 virtual Position getTargetPos() final override;

private:
 const Player& pacman;
 const Ghost& blinky;
};

#endif
