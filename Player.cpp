#include "Player.h"

Player::Player(int x, int y): 
lives(getMaxNumLives()), color(getColorYellow()), currentPos{x, y}, oldPos{x, y},
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

   bool isOutOfBounds = (currentPos.x > getPlayingFieldWidth() - 1);
   if (isOutOfBounds) {
	currentPos.x = 0;
   }
  }
 }
 {
  bool isLeft = (direction == getDirectionLeft());
  if (isLeft) {
   currentPos.x--;

   bool isOutOfBounds = (currentPos.x == -1);
   if (isOutOfBounds) {
    currentPos.x = getPlayingFieldWidth() - 1;
   }
  }
 }
}

void Player::stepBack()
{
 currentPos = oldPos;
}

void Player::setPosition(int x, int y)
{
	currentPos.x = x;
	currentPos.y = y;
	oldPos = currentPos;
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
