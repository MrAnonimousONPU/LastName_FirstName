#include "Ghost.h"

Ghost::Ghost(int x, int y, int typeGhost, const std::vector<std::string>& map) :
 map(map), pos({x, y}), oldPos({x, y}), character('M'),
 direction(getDirectionLeft()), oldDirection(direction), typeGhost(typeGhost)
{
 if (typeGhost == getGhostBlinky())
 {
  cagePos = {12, 15};
  scatterPos = {0, getPlayingFieldWidth() - 1};
  mode = getModeChase();
  startMode = mode;
  oldMode = mode;
  color = getColorRed();
 }
 else if (typeGhost == getGhostPinky())
 {
  cagePos = {15, 15};
  scatterPos = {0, 0};
  mode = getModeWait();
  startMode = mode;
  oldMode = mode;
  color = getColorPink();
 }
 else if (typeGhost == getGhostInky())
 {
  cagePos = {12, 13};
  scatterPos = {getPlayingFieldHeight() - 1, getPlayingFieldWidth() - 1};
  mode = getModeWait();
  startMode = mode;
  oldMode = mode;
  color = getColorCyan();
 }
 else
 {
  mode = getModeWait();
  startMode = mode;
  oldMode = mode;
  cagePos = {15, 13};
  scatterPos = {getPlayingFieldHeight() - 1, 0};
  color = getColorOrange();
 }
 startPos = { x, y };
 specificX[0] = 12;
 specificX[1] = 15;
 specificY[0] = 23;
 specificY[1] = 11;
}

void Ghost::move(int playerX, int playerY)
{
 if (mode == getModeScatter())
 {
  playerX = scatterPos.x;
  playerY = scatterPos.y;
 }
 else if (mode == getModeFrightened())
 {
  if (oldMode != mode)
  {
   oldMode = mode;
   setDirection(reverseDirection(direction));
   changePosition();
   return;
  }
 }
 else if (mode == getModeDead())
 {
  if (pos.x == cagePos.x && pos.y == cagePos.y)
  {
   oldMode = mode;
   mode = getModeExiting();
  }
  playerX = cagePos.x;
  playerY = cagePos.y;
 }
 else if (mode == getModeExiting())
 {
  if (pos.x == getGateX() && pos.y == getGateY() - 1)
  {
   oldMode = mode;
   mode = getModeChase();
  }
  playerX = getGateX();
  playerY = getGateY() - 1;
 }
 else if (mode == getModeWait())
 {
  oldPos = pos;
  if (pos.x == cagePos.x && pos.y == cagePos.y)
  {
   pos.x--;
   return;
  }
  pos.x++;
  return;
 }

 std::vector<int> directions;
 aviableDirections(directions);

 if (directions.size() > 1)
 {
  if(mode == getModeFrightened())
  {
   directions[0] = directions[rand() % directions.size()];
  }
  else
  {
   double minDistance = std::numeric_limits<double>::infinity();
   for (unsigned int i = 0; i < directions.size(); i++)
   {
    int x = pos.x;
    int y = pos.y;

    bool isHorisontal = (directions[i] == getDirectionLeft());
    isHorisontal = (isHorisontal || directions[i] == getDirectionRight());
    if (isHorisontal)
    {
     x += directions[i] == getDirectionLeft() ? -1 : 1;
    }
    else
    {
     y += directions[i] == getDirectionUp() ? -1 : 1;
    }

	double distance = sqrt(pow((x - playerX), 2) + pow((y - playerY), 2));
	if (distance < minDistance)
	{
     minDistance = distance;
	 directions[0] = directions[i];
	}
   }
  }
 }

 if (direction != directions[0])
  setDirection(directions[0]);

 changePosition();
}

void Ghost::setPosition(int x, int y)
{
 oldPos = pos;
 pos.x = x;
 pos.y = y;
}

void Ghost::setStartPosition()
{
 pos = startPos;
 mode = startMode;
}

void Ghost::setDirection(int direction)
{
 oldDirection = this->direction;
 this->direction = direction;
}

void Ghost::setMode(int mode)
{
 oldMode = this->mode;
 this->mode = mode;
}

int Ghost::getColor() const
{
 if (mode == getModeDead())
  return getColorWhite();
 else if (mode == getModeFrightened())
  return getColorBlue();
 else 
  return color;
}

int Ghost::getCharacter() const
{
 if (mode == getModeDead())
  return ('\"');
 else
  return character;
}

int Ghost::getMode() const
{
	return mode;
}

int Ghost::getType() const
{
 return typeGhost;
}

const Position& Ghost::getPosition() const
{
 return pos;
}

const Position& Ghost::getOldPosition() const
{
	return oldPos;
}

const Position& Ghost::getScatterPosition() const
{
 return scatterPos;
}

void Ghost::aviableDirections(std::vector<int>& directions)
{
 int upDir = getDirectionUp();
 bool directionNotReverse = (direction != reverseDirection(upDir));
 if (!checkColision(pos.x, pos.y - 1) && directionNotReverse)
  if (mode != getModeFrightened())
  {
   if (!isSpecific(pos.x, pos.y))
    directions.push_back(getDirectionUp());
  }
  else
   directions.push_back(getDirectionUp());

 directionNotReverse = (direction != reverseDirection(getDirectionLeft()));
 if (!checkColision(pos.x - 1, pos.y) && directionNotReverse)
  directions.push_back(getDirectionLeft());

 directionNotReverse = (direction != reverseDirection(getDirectionDown()));
 if (!checkColision(pos.x, pos.y + 1) && directionNotReverse)
  directions.push_back(getDirectionDown());

 directionNotReverse = (direction != reverseDirection(getDirectionRight()));
 if (!checkColision(pos.x + 1, pos.y) && directionNotReverse)
  directions.push_back(getDirectionRight());
}

void Ghost::changePosition()
{
 oldPos = pos;

 bool isHorisontal = (direction == getDirectionLeft());
 isHorisontal = (isHorisontal || direction == getDirectionRight());

 if (isHorisontal)
 {
  pos.x += direction == getDirectionLeft() ? -1 : 1;
  if (pos.x == getPlayingFieldWidth())
   pos.x = 0;
  else if (pos.x == -1)
   pos.x = getPlayingFieldWidth() - 1;
 }
 else
  pos.y += direction == getDirectionUp() ? -1 : 1;
}

int Ghost::reverseDirection(int direction)
{
 if (direction == getDirectionDown())
  return getDirectionUp();
 else if (direction == getDirectionUp())
  return getDirectionDown();
 else if (direction == getDirectionLeft())
  return getDirectionRight();
 else
  return getDirectionLeft();
}

bool Ghost::checkColision(int x, int y)
{
 if (x == getPlayingFieldWidth())
  x = 0;
 else if (x == -1)
  x = getPlayingFieldWidth() - 1;

 unsigned char ch = map[y][x];
 unsigned char food = static_cast<unsigned char> (250);
 unsigned char fruitChar = static_cast<unsigned char> (253);

 bool isGate = (x == getGateX() && y == getGateY());
 isGate = (isGate && (mode == getModeDead() || mode == getModeExiting()));

 bool isCanGo = (ch == ' ' || ch == food || ch == 'o'
 || ch == fruitChar || isGate);
 bool hasColision = (!isCanGo);

 return hasColision;
}

bool Ghost::isSpecific(int x, int y)
{
 for (int i = 0; i < 2; i++)
  if (x == specificX[i])
   for (int j = 0; j < 2; j++)
    if (y == specificY[j])
     return true;
 return false;
}