#include "Ghost.h"

Ghost::Ghost(int x, int y, const std::vector<std::string>& map) :
 character('M'),
 oldMode(getModeDead()),
 pos(x, y),
 oldPos(x, y),
 direction(getDirectionLeft()),
 oldDirection(direction),
 map(map)
{
 startPos = { x, y };
 specificX[0] = 12;
 specificX[1] = 15;
 specificY[0] = 23;
 specificY[1] = 11;
}

void Ghost::makeMove()
{
 Position target = getTargetPos();
 
 upToMode(target);

 std::vector<Position> directions;
 aviableDirections(directions);

 chooseBestDirection(target, directions);

 if (mode == getModeFrightened())
 {
  if (oldMode != mode)
  {
   oldMode = mode;
   directions[0] = reverseDirection(direction);
  }
 }

 if (direction != directions[0])
  setDirection(directions[0]);

 changePosition();
}

void Ghost::setPosition(int x, int y)
{
 oldPos = pos;
 pos.setX(x);
 pos.setY(y);
}

void Ghost::toStartPosition()
{
 pos = startPos;
 mode = startMode;
}

void Ghost::setDirection(Position direction)
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

Ghost::~Ghost()
{
}

void Ghost::setCagePos(const Position& temp)
{
 cagePos = temp;
}

void Ghost::setScatterPos(const Position& temp)
{
 scatterPos = temp;
}

void Ghost::setStartMode(int mode)
{
 startMode = mode;
}

void Ghost::setColor(int color)
{
 this->color = color;
}

void Ghost::setTypeGhost(int ghost)
{
 typeGhost = ghost;
}

void Ghost::aviableDirections(std::vector<Position>& directions)
{
 Position dir = getDirectionUp();
 bool directionNotReverse = (direction != reverseDirection(dir));
 if (!checkColision(pos + dir) && directionNotReverse)
  if (mode != getModeFrightened())
  {
   if (!isSpecific(pos.getX(), pos.getY()))
   {
    directions.push_back(dir);
   }
  }
  else
  {
   directions.push_back(dir);
  }

 dir = getDirectionLeft();
 checkDirection(dir, directions);

 dir = getDirectionDown();
 checkDirection(dir, directions);

 dir = getDirectionRight();
 checkDirection(dir, directions);
}

void Ghost::checkDirection(Position& dir, std::vector<Position>& directions)
{
 bool directionNotReverse = (direction != reverseDirection(dir));
 if (!checkColision(pos + dir) && directionNotReverse)
 {
  directions.push_back(dir);
 }
}

void Ghost::changePosition()
{
 oldPos = pos;

 pos += direction;
}

void Ghost::upToMode(Position& target)
{
 if (mode == getModeScatter())
 {
  target = scatterPos;
 }
 else if (mode == getModeDead())
 {
  if (pos == cagePos)
  {
   oldMode = mode;
   mode = getModeExiting();
  }
  target = cagePos;
 }
 else if (mode == getModeExiting())
 {
  if (pos.getX() == getGateX() && pos.getY() == getGateY() - 1)
  {
   oldMode = mode;
   mode = getModeChase();
  }
  target.setX(getGateX());
  target.setY(getGateY() - 1);
 }
 else if (mode == getModeWait())
 {
  oldPos = pos;
  if (pos == cagePos)
  {
   target = (pos + getDirectionLeft());
  }
  target = (pos + getDirectionRight());
 }
}

void Ghost::chooseBestDirection(Position& target, 
 std::vector<Position>& directions)
{
 if (directions.size() > 1)
 {
  if (mode == getModeFrightened())
  {
   directions[0] = directions[rand() % directions.size()];
  }
  else
  {
   double minDistance = std::numeric_limits<double>::infinity();
   for (unsigned int i = 0; i < directions.size(); i++)
   {
    Position temp = pos + directions[i];

    double distance = temp - target;
    if (distance < minDistance)
    {
     minDistance = distance;
     directions[0] = directions[i];
    }
   }
  }
 }
}

Position Ghost::reverseDirection(const Position& direction)
{
 Position temp = direction;
 if (direction.getY() == -1)
  temp.setY(1);
 else if (direction.getY() == 1)
  temp.setY(-1);
 else if (direction.getX() == 1)
  temp.setX(-1);
 else
  temp.setX(1);

 return temp;
}

bool Ghost::checkColision(Position point)
{
 if (point.getX() == getPlayingFieldWidth())
  point.setX(0);
 else if (point.getX() == -1)
  point.setX(getPlayingFieldWidth() - 1);

 unsigned char ch = map[point.getY()][point.getX()];
 unsigned char food = '.';
 auto fruitChar = static_cast<unsigned char> (253);

 bool isGate = ((mode == getModeDead() || mode == getModeExiting()) && ch == '-');

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