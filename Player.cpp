#include "Player.h"

Player::Player(int x, int y) : 
 lives(getMaxNumLives()),
 color(getColorYellow()),
 characters{ 'v', '^', '<', '>' },
 super(false),
 currentPos(x, y),
 oldPos(x, y),
 direction(getDirectionLeft()) 
{
}

void Player::move()
{
 oldPos = currentPos;

 currentPos += direction;
}

void Player::setPosition(int x, int y)
{
 oldPos = currentPos;
	currentPos.setX(x);
	currentPos.setY(y);
	direction = (getDirectionLeft());
}

void Player::death() 
{
 lives--;
}

void Player::setDirection(const Position& direction)
{
 this->direction = direction;
}

void Player::setSuper(bool super)
{
 this->super = super;
}

bool Player::isSuper() const
{
 return super;
}

int Player::getLivesCount() const
{
 return lives;
}

int Player::getColor() const
{
 return color;
}

int Player::getCurrentCharacter() const
{
 if (direction.getY() == -1)
  return characters[0];
 else if (direction.getY() == 1)
  return characters[1];
 else if (direction.getX() == 1)
  return characters[2];
 else
  return characters[3];
}

const Position& Player::getDirection() const
{
 return direction;
}

const Position& Player::getPosition() const
{
 return currentPos;
}

const Position& Player::getOldPosition() const
{
 return oldPos;
}