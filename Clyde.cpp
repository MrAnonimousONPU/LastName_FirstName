#include "Clyde.h"

Clyde::Clyde(int x, int y, const std::vector<std::string>& map,
 const Player& pacman) : Ghost(x, y, map),
 pacman(pacman)
{
 setCagePos({ 15, 13 });
 setScatterPos({getPlayingFieldHeight() - 1, 0});
 setMode(getModeWait());
 setStartMode(getMode());
 setColor(getColorOrange());
 setTypeGhost(getGhostClyde());
}

Position Clyde::getTargetPos()
{
 double distance = pacman.getPosition() - getPosition();
 if (distance > 8)
 {
  return pacman.getPosition();
 }
 else
 {
  return getScatterPosition();
 }
}
