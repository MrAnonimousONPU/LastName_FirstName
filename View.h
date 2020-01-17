#ifndef VIEW_H
#define VIEW_H

#include <Windows.h>
#include <iostream>
#include <mutex>
#include <string>
#include "Constants.h"

class View
{
protected:
 //Sets the specified character to the specified position
 void SetWindowTitle();

 void setChar(int x, int y, char ch = ' ', int color = getColorBlue());

 void setWindowSize(int height, int width);

 void setColor(int color);

 void setCursorVisibility(bool show);
};

#endif