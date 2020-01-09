#include <iostream>
#include "View.h"

int main()
{
	View::SetWindowSize(50, 50);
	View::SetCursorVisibility(false);
	View::SetChar(5, 0, 'v', 13);
	View::SetChar(5, 0);
	View::SetChar(10, 1, '<', 3);
	View::SetChar(15, 2, '>', 1);
	View::SetChar(20, 3, '^', 14);
}
