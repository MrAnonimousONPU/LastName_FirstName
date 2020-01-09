#pragma once
#include <Windows.h>
#include <iostream>

class View
{
public:
//Sets the specified character to the specified position
static void SetChar(int x, int y, char ch = ' ', char color = 0);

static void SetWindowSize(int height, int width);

inline static void SetColor(int color);

static void SetCursorVisibility(bool show);
};

