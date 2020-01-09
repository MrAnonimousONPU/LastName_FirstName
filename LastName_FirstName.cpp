#include <iostream>
#include "View.h"

int main()
{
View::SetWindowSize(30, 10);
View::SetChar(3, 3, ' ');
std::cout << "Hello World!\n";
}
