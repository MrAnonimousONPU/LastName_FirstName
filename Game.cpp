#include "Game.h"

Game::Game()
{
 isWinner = false;
 isOneUp = false;
 isPause = false;

 amountOfFood = 0;
 score = 0;
 level = 0;

 mainFrameTime = 0;

 pacman = new Player(getStartX(), getStartY());
 initMap();
 /*
 map = {
  "╔══════════════════════════╗",
  "║............││............║",
  "║.┌──┐.┌───┐.││.┌───┐.┌──┐.║",
  "║ │  │.│   │.││.│   │.│  │ ║",
  "║.└──┘.└───┘.└┘.└───┘.└──┘.║",
  "║..........................║",
  "║.┌──┐.┌┐.┌──────┐.┌┐.┌──┐.║",
  "║.└──┘.││.└──┐┌──┘.││.└──┘.║",
  "║......││....││....││......║",
  "╚════╗.│└──┐ ││ ┌──┘│.╔════╝",
  "     ║.│┌──┘ └┘ └──┐│.║     ",
  "     ║.││          ││.║     ",
  "     ║.││ ╔══--══╗ ││.║     ",
  "═════╝.└┘ ║      ║ └┘.╚═════",
  "      .   ║      ║   .      ",
  "═════╗.┌┐ ║      ║ ┌┐.╔═════",
  "     ║.││ ╚══════╝ ││.║     ",
  "     ║.││          ││.║     ",
  "     ║.││ ┌──────┐ ││.║     ",
  "╔════╝.└┘ └──┐┌──┘ └┘.╚════╗",
  "║............││............║",
  "║.┌──┐.┌───┐.││.┌───┐.┌──┐.║",
  "║.└─┐│.└───┘.└┘.└───┘.│┌─┘.║",
  "║ ..││.......  .......││.. ║",
  "║─┐.││.┌┐.┌──────┐.┌┐.││.┌─║",
  "║─┘.└┘.││.└──┐┌──┘.││.└┘.└─║",
  "║......││....││....││......║",
  "║.┌────┘└──┐.││.┌──┘└────┐.║",
  "║.└────────┘.└┘.└────────┘.║",
  "║..........................║",
  "╚══════════════════════════╝",
 };
 */
}

void Game::run()
{
 printMap();
 printHightScore();
 auto startTime = std::chrono::high_resolution_clock::now();

 while (true) 
 {
  if (_kbhit())
  {
   keyPressed(_getch());
  }
  auto endTime = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> duration = endTime - startTime;
  startTime = std::chrono::high_resolution_clock::now();

  updateFrame(duration.count());
 }
}

void Game::updateFrame(float deltaTime)
{ 
 if (!isPause)
 {
  mainFrameTime += deltaTime;
  if (mainFrameTime > 0.35)
  {
   isOneUp = !isOneUp;
   printOneUp(isOneUp);
   printCountOfLives();
   printScore();

   mainFrameTime = 0;
  }
 }
} 

void Game::keyPressed(char ch)
{
 std::cin.clear();
 ch = std::toupper(ch);

 int x = pacman->getPosition().x;
 int y = pacman->getPosition().y;

 if (ch == 'P')
 {
  isPause = !isPause;
  printPause(isPause);
 }
 else if (ch == 'W' || ch == getArrowUp())
 {
  if (!checkColision(x, y - 1))
  {
   pacman->setDirection(getDirectionUp());
  }
 }
 else if (ch == 'S' || ch == getArrowDown())
 {
  if (!checkColision(x, y + 1))
  {
   pacman->setDirection(getDirectionDown());
  }
 }
 else if (ch == 'D' || ch == getArrowRight())
 {
  bool isOutOfBounds = (x == getPlayingFieldWidth() - 1);
  if (isOutOfBounds)
  {
   x = 0;
  }
  else 
  {
   x++;
  }
  if (!checkColision(x, y))
  {
   pacman->setDirection(getDirectionRight());
  }
 }
 else if (ch == 'A' || ch == getArrowLeft())
 {
  bool isOutOfBounds = (x == 0);
  if (isOutOfBounds)
  {
   x = getPlayingFieldWidth() - 1;
  }
  else 
  {
   x--;
  }
  if (!checkColision(x, y))
  {
   pacman->setDirection(getDirectionLeft());
  }
 }

}
 
void Game::initMap()
{
 map = 
 {
  "1555555555555555555555555552",
  "6............^^............6",
  "6.!%%@.!%%%@.^^.!%%%@.!%%@.6",
  "6 ^  ^.^   ^.^^.^   ^.^  ^ 6",
  "6.#%%$.#%%%$.#$.#%%%$.#%%$.6",
  "6..........................6",
  "6.!%%@.!@.!%%%%%%@.!@.!%%@.6",
  "6.#%%$.^^.#%%@!%%$.^^.#%%$.6",
  "6......^^....^^....^^......6",
  "355552.^#%%@ ^^ !%%$^.155554",
  "     6.^!%%$ #$ #%%@^.6     ",
  "     6.^^          ^^.6     ",
  "     6.^^ 155--552 ^^.6     ",
  "555554.#$ 6      6 #$.355555",
  "      .   6      6   .      ",
  "555552.!@ 6      6 !@.155555",
  "     6.^^ 35555554 ^^.6     ",
  "     6.^^          ^^.6     ",
  "     6.^^ !%%%%%%@ ^^.6     ",
  "155554.#$ #%%@!%%$ #$.355552",
  "6............^^............6",
  "6.!%%@.!%%%@.^^.!%%%@.!%%@.6",
  "6.#%@^.#%%%$.#$.#%%%$.^!%$.6",
  "6 ..^^.......  .......^^.. 6",
  "6%@.^^.!@.!%%%%%%@.!@.^^.!%6",
  "6%$.#$.^^.#%%@!%%$.^^.#$.#%6",
  "6......^^....^^....^^......6",
  "6.!%%%%$#%%@.^^.!%%$#%%%%@.6",
  "6.#%%%%%%%%$.#$.#%%%%%%%%$.6",
  "6..........................6",
  "3555555555555555555555555554" 
 };
 for (int y = 0; y < getPlayingFieldHeight(); ++y) 
 {
  for (int x = 0; x < getPlayingFieldWidth(); ++x) 
  {
   char current = map[y][x];
   if (current == '.')
   {
    amountOfFood++;
    map[y][x] = static_cast<unsigned char> (250);
   }
   else if (current == '1')
   {
    map[y][x] = static_cast<unsigned char> (201);
   }
   else if (current == '2')
   {
    map[y][x] = static_cast<unsigned char> (187);
   }
   else if (current == '3')
   {
    map[y][x] = static_cast<unsigned char> (200);
   }
   else if (current == '4')
   {
    map[y][x] = static_cast<unsigned char> (188);
   }
   else if (current == '5')
   {
    map[y][x] = static_cast<unsigned char> (205);
   }
   else if (current == '6')
   {
    map[y][x] = static_cast<unsigned char> (186);
   }
   else if (current == '!')
   {
    map[y][x] = static_cast<unsigned char> (218);
   }
   else if (current == '@')
   {
    map[y][x] = static_cast<unsigned char> (191);
   }
   else if (current == '#')
   {
    map[y][x] = static_cast<unsigned char> (192);
   }
   else if (current == '$')
   {
    map[y][x] = static_cast<unsigned char> (217);
   }
   else if (current == '%')
   {
    map[y][x] = static_cast<unsigned char> (196);
   }
   else if (current == '^')
   {
    map[y][x] = static_cast<unsigned char> (179);
   }
  }
 }
}

void Game::printMap(bool winner)
{
 int y = 0;
 for (std::string i : map)
 {
  int x = 0;
  for (unsigned char j : i)
  {
   switch (j)
   {
    case static_cast<unsigned char> (250) :
     if (winner)
     {
      j = ' ';
	  View::setChar(x, y + getInfoScoreFieldHeight(), j);
	 }
	 else
	 {
      View::setChar(x, y + getInfoScoreFieldHeight(), j, getColorWhite());
	 }
	 break;
	case '-' :
     View::setChar(x, y + getInfoScoreFieldHeight(), j, getColorWhite());
	 break;
    default:
     if (winner)
     {
      View::setChar(x, y + getInfoScoreFieldHeight(), j, getColorWhite());
	 }
	 else
	 {
      View::setChar(x, y + getInfoScoreFieldHeight(), j);
	 }
     break;
   }
   x++;
  }
  y++;
 }
}

bool Game::checkColision(int x, int y)
{
 unsigned char ch = map[y][x];
 bool hasColision = !(ch == ' ' || ch == static_cast<unsigned char> (250));

 return hasColision;
}

void Game::printOneUp(bool hide)
{
 char text[5] = "1 UP";

 for (int i = 0; i < 4; i++)
 {
  if (hide)
  {
   View::setChar(3 + i, 0);
  }
  else
  {
   View::setChar(3 + i, 0, text[i], getColorWhite());
  }
 }
}

void Game::printHightScore()
{
 std::string text = "HIGHT SCORE : ";
 int highScore = 0;
 text += std::to_string(score);

 for (unsigned int i = 0; i < text.length(); i++)
 {
  View::setChar(i + 3, 1, text[i], getColorWhite());
 }
}

void Game::printScore()
{
 std::string text = "SCORE : ";
 text += std::to_string(score);

 for (unsigned int i = 0; i < text.length(); i++)
 {
  View::setChar(i + 9, 2, text[i], getColorWhite());
 }
}

void Game::printCountOfLives()
{
 int height = getInfoScoreFieldHeight();
 height += getPlayingFieldHeight();
 char heart = static_cast<unsigned char> (254);

 for (int i = 0; i < pacman->getLivesCount(); i++)
 {
  View::setChar(i + 2, height, heart, getColorRed());
 }
 for (int i = pacman->getLivesCount(); i < 3; i++)
 {
  View::setChar(i + 2, height);
 }
}

void Game::printPause(bool show)
{
 char text[6] = "Pause";
 int width = getPlayingFieldWidth() - 5;
 int color = getColorBlack();
 if (show)
 {
  color = getColorRed();
 }

 for (int i = 0; i < 5; i++)
 {
  View::setChar(width + i, 0, text[i], color);
 }
}
