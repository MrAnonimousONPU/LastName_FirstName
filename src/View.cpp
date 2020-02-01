#include "View.h"

void View::SetWindowTitle()
{
 std::cout << "\033]0;Pacman\007";
}

void View::setFont()
{
  //TODO :: create function, character size must be equal x y
  //TODO ::font must be Lucida Console
}

void View::setChar(int x, int y, char ch, int color)
{
 setColor(color);

 std::cout << "\e[" << y + 1 << ";" << x + 1 << "H";

 std::cout << ch;
 std::cout.flush();

 setColor(getColorWhite());
}

void View::setString(int x, int y, const std::string& str, int color)
{
 setColor(color);

 std::cout << "\e[" << y + 1 << ";" << x + 1 << "H";

 std::cout << str;
 std::cout.flush();
 
 setColor(getColorWhite());
}

void View::setColor(int color)
{
 std::cout << "\e[" << color << "m";
}

void View::setWindowSize(int height, int width) {
 std::cout << "\e[8;" << height << ";" << width << "t";
}

void View::setWidowPos(int x, int y)
{
  std::cout << "\e[3;" << x + 1 << ";" << y + 1 << "t";
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
  for (int i = 0; i < 100; i++)
  {
    std::cout << std::endl;
  }
}
