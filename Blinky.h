#ifndef BLINKY_H
#define BLINKY_H

#include "Ghost.h"
#include "Player.h"
#include "Position.h"

class Blinky : public Ghost
{
public:
 Blinky(int x, int y, const std::vector<std::string>& map, const Player& pacman);

protected:
virtual Position getTargetPos() final override;

private:
 const Player& pacman;
};

#endif