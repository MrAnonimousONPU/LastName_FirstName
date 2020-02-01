#include "SimpleConio.h"

void SimpleConio::resetTermios()
{
  tcsetattr(STDIN_FILENO, TCSANOW, &old);
}

void SimpleConio::initTermios()
{
  tcgetattr(STDIN_FILENO, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  current.c_lflag &= ~ECHO; /* set no echo mode */
  tcsetattr(STDIN_FILENO, TCSANOW, &current); /* use these new terminal i/o settings now */
}

bool SimpleConio::kbhit()
{
  int ch;
  int oldf;
  
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  
  ch = getchar();
  
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return true;
  }
  
  return false;
}

char SimpleConio::getch()
{
  char ch;
  ch = getchar();
  return ch;
}

SimpleConio::SimpleConio()
{
  initTermios();
}

SimpleConio::~SimpleConio()
{
  resetTermios();
}

