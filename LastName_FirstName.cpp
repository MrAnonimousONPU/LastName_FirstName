#include <iostream>
#include "Game.h"

int main()
{
 int height = getInfoLivesFieldHeight();
 height += getPlayingFieldHeight() + getInfoScoreFieldHeight();
 View::setWindowSize(height, getPlayingFieldWidth());
 View::setCursorVisibility(false);
 Game game;
 game.run();
 return 0;
}
