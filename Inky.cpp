#include "Inky.h"

Inky::Inky(int x, int y, const std::vector<std::string>& map,
 const Player& pacman, const Ghost& blinky) : Ghost(x, y, map),
 pacman(pacman),
 blinky(blinky)
{
 setCagePos({ 12, 13 });
 setScatterPos({getPlayingFieldHeight() - 1, getPlayingFieldWidth() - 1});
 setMode(getModeWait());
 setStartMode(getMode());
 setColor(getColorCyan());
 setTypeGhost(getGhostInky());
}

Position Inky::getTargetPos()
{
 int x = pacman.getPosition().getX() - blinky.getPosition().getX();
 int y = pacman.getPosition().getY() - blinky.getPosition().getY();
 Position target(x, y);

 target = blinky.getPosition() + (target * 2);

 return target;
}
