#pragma once

#include <Windows.h>
#include <iostream>
#include <mutex>
#include "Constants.h"

class View
{
public:
 //Sets the specified character to the specified position
 static void setChar(int x, int y, char ch = ' ', int color = getColorBlue());

 static void setWindowSize(int height, int width);

 static void setColor(int color);

 static void setCursorVisibility(bool show);
};

