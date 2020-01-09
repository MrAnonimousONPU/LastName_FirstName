#pragma once
#include <Windows.h>
#include <iostream>

class View
{
public:
//Sets the specified character to the specified position
//
static void SetChar(int x, int y, char ch, char color = '0');

//
inline static void SwitchColor(char color);

static void SetWindowSize(int, int);
};

