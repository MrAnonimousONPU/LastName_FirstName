#include "View.h"

void View::SetChar(int x, int y, char ch, char color)
{
SwitchColor(color);

COORD cursor = { static_cast<short>(x) , static_cast<short>(y) };
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);

std::cout << ch;

SwitchColor('0');
}

void View::SwitchColor(char color = '0')
{
char arr[] = "color 00";
arr[7] = color;
system(arr);
}

void SetWindowSize(int height, int width) {
SMALL_RECT window;
window.Top = 0;
window.Left = 0;
window.Bottom = height - 1;
window.Right = width - 1;
SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &window);
COORD buffer = { width,height };
SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), buffer);
}
