#ifndef POSITION_H
#define POSITION_H

#include <cmath>

class Position
{
public:
 Position();
 Position(int x, int y);

 void setX(int x);
 void setY(int y);

 int getX() const;
 int getY() const;

 Position& operator=(const Position& A);
 Position& operator+=(const Position& A);

 friend Position operator+(const Position& A, const Position& B);
 friend double operator-(const Position& A, const Position& B);
 friend Position operator*(const Position& A, int B);

 friend bool operator==(const Position& A, const Position& B);
 friend bool operator!=(const Position& A, const Position& B);

private:
 int x_;
 int y_;
};

#endif

