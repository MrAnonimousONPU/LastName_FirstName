#include "Position.h"

Position::Position() : x_(0), y_(0)
{
}

Position::Position(int x, int y) : x_(x), y_(y)
{
}

void Position::setX(int x)
{
 x_ = x;
}

void Position::setY(int y)
{
 y_ = y;
}

int Position::getX() const
{
 return x_;
}

int Position::getY() const
{
 return y_;
}

Position& Position::operator=(const Position& A)
{
 if (this != &A)
 {
  x_ = A.x_;
  y_ = A.y_;
 }
 return *this;
}

Position& Position::operator+=(const Position& A)
{
 x_ += A.x_;

 if (-1 == x_)
  x_ = (27);
 else if (28 == x_)
  x_ = 0;

 y_ += A.y_;

 return *this;
}

Position operator+(const Position& A, const Position& B)
{
 Position newPos(A.x_ + B.x_, A.y_ + B.y_);
 if (-1 == newPos.getX())
  newPos.setX(27);
 else if (28 == newPos.getX())
  newPos.setX(0);
 return newPos;
}

double operator-(const Position& A, const Position& B)
{
 return sqrt(pow((A.x_ - B.x_), 2) + pow((A.y_ - B.y_), 2));;
}

Position operator*(const Position& A, int B)
{
 return Position(A.x_ * B, A.y_ * B);
}

bool operator==(const Position& A, const Position& B)
{
 return (A.x_ == B.x_ && A.y_ == B.y_);
}

bool operator!=(const Position& A, const Position& B)
{
 return !(A == B);
}
