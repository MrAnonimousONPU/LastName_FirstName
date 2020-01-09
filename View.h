#pragma once

#include <Windows.h>
#include <iostream>

class View
{
public:
 //Sets the specified character to the specified position
 static void setChar(int x, int y, char ch = ' ', int color = 0);

 static void setWindowSize(int height, int width);

 static void setColor(int color);

 static void setCursorVisibility(bool show);
};

