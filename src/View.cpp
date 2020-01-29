#include "View.h"

void View::SetWindowTitle()
{
 //TODO :: set window title "PACMAN"
}

void View::setFont()
{
  //TODO :: create function, character size must be equal x y
  //TODO ::font must be Lucida Console
}

void View::setChar(int x, int y, char ch, int color)
{
 setColor(color);

 std::cout << "\e[" << y << ";" << x << "H";

 std::cout << ch;

 setColor(getColorWhite());
}

void View::setColor(int color)
{
 std::cout << "\e[" << color << "m";
}

void View::setWindowSize(int height, int width) {
 std::cout << "\e[8;" << height << ";" << width << ";t";
}

void View::setWidowPos(int x, int y)
{
 //TODO :: create function;
}

void View::setCursorVisibility(bool show)
{
  if (true == show)
  {
    std::cout << "\e[?25h";
  }
  else
  {
    std::cout << "\e[?25l";
  }
}

void View::clearScreen()
{
  std::cout << "\e[2J";
}
