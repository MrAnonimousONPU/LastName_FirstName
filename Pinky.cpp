#include "Pinky.h"

Pinky::Pinky(int x, int y, const std::vector<std::string>& map,
 const Player& pacman) : Ghost(x, y, map),
 pacman(pacman)
{
 setCagePos({ 15, 15 });
 setScatterPos({0, 0});
 setMode(getModeWait());
 setStartMode(getMode());
 setColor(getColorPink());
 setTypeGhost(getGhostPinky());
}

Position Pinky::getTargetPos()
{
 return Position((pacman.getPosition() + (pacman.getDirection() * 4)));
}
