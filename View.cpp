#include "View.h"

void View::setChar(int x, int y, char ch, int color)
{
 setColor(color);

 COORD cursor = { static_cast<short>(x) , static_cast<short>(y) };
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);

 std::cout << ch;

 setColor(15);
}

void View::setColor(int color)
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void View::setWindowSize(int height, int width) {
 SMALL_RECT window;
 window.Top = 0;
 window.Left = 0;
 window.Bottom = height - 1;
 window.Right = width - 1;
 SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &window);
 COORD buffer = { static_cast<short>(width), static_cast<short>(height) };
 SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), buffer);
}

void View::setCursorVisibility(bool show) {
 CONSOLE_CURSOR_INFO cursor;
 GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
 cursor.bVisible = show;
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
