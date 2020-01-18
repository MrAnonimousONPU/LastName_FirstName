#include "Blinky.h"

Blinky::Blinky(int x, int y, const std::vector<std::string>& map,
 const Player& pacman) : Ghost(x, y, map),
 pacman(pacman)
{
 setCagePos({ 12, 15 });
 setScatterPos({ 0, getPlayingFieldWidth() - 1 });
 setMode(getModeChase());
 setStartMode(getMode());
 setColor(getColorRed());
 setTypeGhost(getGhostBlinky());
}

Position Blinky::getTargetPos()
{
 return Position(pacman.getPosition());
}
