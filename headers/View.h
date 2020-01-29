#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include "Constants.h"

class View
{
protected:
 //Sets the specified character to the specified position
 void SetWindowTitle();

 void setFont();

 void setChar(int x, int y, char ch = ' ', int color = getColorBlue());

 void clearScreen();

 void setWindowSize(int height, int width);

 void setWidowPos(int x, int y);

 void setColor(int color);

 void setCursorVisibility(bool show);
};

#endif