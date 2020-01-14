#include <iostream>
#include "Game.h"

int main()
{
 TCHAR text[] =(__TEXT("Pacman"));
 int height = getInfoLivesFieldHeight();
 height += getPlayingFieldHeight() + getInfoScoreFieldHeight();
 SetConsoleTitle(text);
 srand(time(0));
 View::setWindowSize(height, getPlayingFieldWidth());
 View::setCursorVisibility(false);
 Game game;
 game.run();

 return 0;
}
