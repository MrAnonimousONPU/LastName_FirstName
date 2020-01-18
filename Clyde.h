#ifndef CLYDE_H
#define CLYDE_H

#include "Ghost.h"
#include "Player.h"
#include "Position.h"

class Clyde : public Ghost
{
public:
 Clyde(int x, int y, const std::vector<std::string>& map, const Player& pacman);

protected:
 virtual Position getTargetPos() final override;

private:
 const Player& pacman;
};

#endif