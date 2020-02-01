#ifndef SIMPLECONIO_H
#define SIMPLECONIO_H

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

class SimpleConio
{
public:
  SimpleConio();
  bool kbhit();
  char getch();
  ~SimpleConio();
  
private:
  void initTermios();
  void resetTermios();
  
private:
  struct termios old, current;
};


#endif
