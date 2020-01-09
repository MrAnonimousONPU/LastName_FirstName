#include "Player.h"

Player::Player(int x, int y)
: lives(getMaxNumLives()), color(getColorYellow()), currentPos{ x, y }, oldPos{ x, y },
  direction(getDirectionLeft()), super(false), characters{'v', '^', '<', '>'}
{
}

void Player::move()
{
 oldPos = currentPos;

 {
  bool isUp = (direction == getDirectionUp());
  if (isUp)
   currentPos.y--;
 }
 {
  bool isDown = (direction == getDirectionDown());
  if (isDown)
   currentPos.y++;
 }
 {
  bool isRight = (direction == getDirectionRight());
  if (isRight) {
   currentPos.x++;

   bool isOutOfBounds = (currentPos.x > getPlayingFieldWidth());
   if (isOutOfBounds) {
	currentPos.x == 0;
   }
  }
 }
 {
  bool isLeft = (direction == getDirectionLeft());
  if (isLeft)
   currentPos.x--;
 }
}

void Player::stepBack()
{
	currentPos = oldPos;
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

bool Player::isSuper()
{
	return super;
}

int Player::getLivesCount()
{
	return lives;
}

int Player::getColor()
{
	return color;
}

int Player::getCurrentCharacter()
{
	return characters[direction];
}

Position Player::getPosition()
{
	return currentPos;
}
