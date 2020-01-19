#include "View.h"

void View::SetWindowTitle()
{
 TCHAR name[7] = (__TEXT("Pacman"));
 int height = getInfoLivesFieldHeight();
 height += getPlayingFieldHeight() + getInfoScoreFieldHeight();
 SetConsoleTitle(name);
}

void View::setFont()
{
 CONSOLE_FONT_INFOEX cfi;
 cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
 cfi.nFont = 0;
 cfi.dwFontSize.X = 16;
 cfi.dwFontSize.Y = 16;
 cfi.FontFamily = FF_DONTCARE;
 cfi.FontWeight = 400;
 wcscpy_s(cfi.FaceName, L"Lucida Console");
 SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfi);
}

void View::setChar(int x, int y, char ch, int color)
{
 setColor(color);

 COORD cursor = { static_cast<short>(x) , static_cast<short>(y) };
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);

 std::cout << ch;

 setColor(15);
}

void View::setString(int x, int y, std::string str, int color)
{
 setColor(color);

 COORD cursor = { static_cast<short>(x) , static_cast<short>(y) };
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);

 std::cout << str;

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

void View::setWidowPos(int x, int y)
{
 HWND hwnd = GetConsoleWindow();
 SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOZORDER || SWP_NOSIZE);
}

void View::setCursorVisibility(bool show) {
 CONSOLE_CURSOR_INFO cursor;
 GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
 cursor.bVisible = show;
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
