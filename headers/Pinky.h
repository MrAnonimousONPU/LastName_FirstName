#ifndef PINKY_H
#define PINKY_H

#include "Ghost.h"
#include "Player.h"
#include "Position.h"

class Pinky : public Ghost
{
public:
 Pinky(int x, int y, const std::vector<std::string>& map, const Player& pacman);

protected:
 virtual Position getTargetPos() final override;

private:
 const Player& pacman;
};

#endif