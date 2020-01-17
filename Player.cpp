#include "Player.h"

Player::Player(int x, int y): 
lives(getMaxNumLives()), color(getColorYellow()), currentPos{x, y}, oldPos{x, y},
direction(getDirectionLeft()), super(false), characters{'v', '^', '<', '>'}
{
}

void Player::move()
{
 oldPos = currentPos;

 bool isHorisontal = (direction == getDirectionLeft());
 isHorisontal = (isHorisontal || direction == getDirectionRight());

 if (isHorisontal)
 {
  currentPos.x += direction == getDirectionLeft() ? -1 : 1;
  if (currentPos.x == getPlayingFieldWidth())
   currentPos.x = 0;
  else if (currentPos.x == -1)
   currentPos.x = getPlayingFieldWidth() - 1;
 }
 else
  currentPos.y += direction == getDirectionUp() ? -1 : 1;
}

void Player::setPosition(int x, int y)
{
 oldPos = currentPos;
	currentPos.x = x;
	currentPos.y = y;
	direction = (getDirectionLeft());
}

void Player::death() 
{
 lives--;
}

void Player::setDirection(int direction)
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
 return characters[direction];
}

int Player::getDirection() const
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