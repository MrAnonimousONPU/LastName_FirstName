#include "Draw.h"

Draw::Draw()
{
 SetWindowTitle();
 setFont();
 int height = getInfoLivesFieldHeight();
 height += getPlayingFieldHeight() + getInfoScoreFieldHeight();
 setWidowPos(10, 0);
 setWindowSize(height, getPlayingFieldWidth());

 setCursorVisibility(false);
}

void Draw::printMap(const std::vector<std::string>& map, bool winner)
{
 int y = 0;
 for (const std::string& i : map)
 {
  int x = 0;
  for (unsigned char j : i)
  {
   switch (j)
   {
    case static_cast<unsigned char> (250) :
     setChar(x, y + getInfoScoreFieldHeight(), j, getColorWhite());
     break;
    case 'o':
     setChar(x, y + getInfoScoreFieldHeight(), j, getColorWhite());
     break;
    case '-':
     setChar(x, y + getInfoScoreFieldHeight(), j, getColorWhite());
     break;
    default:
     if (winner)
     {
      setChar(x, y + getInfoScoreFieldHeight(), j, rand() % 14);
     }
     else
     {
      setChar(x, y + getInfoScoreFieldHeight(), j);
     }
     break;
   }
   x++;
  }
  y++;
 }
}

void Draw::printOneUp(bool& isOneUp)
{
 isOneUp = !isOneUp;
 char text[5] = "1 UP";

 for (int i = 0; i < 4; i++)
 {
  if (isOneUp)
  {
   setChar(3 + i, 0);
  }
  else
  {
   setChar(3 + i, 0, text[i], getColorWhite());
  }
 }
}

void Draw::printHightScore(const int& hightScore)
{
 std::string text = "HIGHT SCORE : ";
 
 text += std::to_string(hightScore);

 for (unsigned int i = 0; i < text.length(); i++)
 {
  setChar(i + 3, 1, text[i], getColorWhite());
 }
}

void Draw::printScore(int score)
{
 std::string text = "SCORE : ";
 text += std::to_string(score);

 for (unsigned int i = 0; i < text.length(); i++)
 {
  setChar(i + 9, 2, text[i], getColorWhite());
 }
}

void Draw::printCountOfLives(int lives)
{
 const int height = getInfoScoreFieldHeight() + getPlayingFieldHeight();
 char heart = static_cast<unsigned char> (254);

 for (int i = 0; i < lives; i++)
 {
  setChar(i + 2, height, heart, getColorRed());
 }
 for (int i = lives; i < 3; i++)
 {
  setChar(i + 2, height);
 }
}

void Draw::printFruits(const std::deque<int>& fruits)
{
 unsigned char fruitChar = static_cast<unsigned char> (253);
 for (unsigned int i = 0; i < fruits.size(); i++)
 {
  int x = getPlayingFieldWidth() - 2 - i;
  int y = getInfoScoreFieldHeight() + getPlayingFieldHeight();
  setChar(x, y, fruitChar, fruits[i]);
 }
}

void Draw::printReady(bool show)
{
 char text[6] = "READY";

 int y = getInfoScoreFieldHeight() + 17;

 for (int i = 0; i < 5; i++)
 {
  if (show)
  {
   setChar(i + 11, y, text[i], getColorWhite());
  }
  else
  {
   setChar(i + 11, y);
  }
 }
}

void Draw::printPause(bool show)
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
  setChar(width + i, 0, text[i], color);
 }
}

void Draw::printGhost(const Ghost& current, bool isWarning,
 int fruit, const std::vector<std::string>& map)
{
 int x = current.getOldPosition().getX();
 int y = current.getOldPosition().getY();
 unsigned char ch = map[y][x];
 unsigned char food = static_cast<unsigned char> (250);

 bool isFood = (ch == food || ch == 'o' || ch == '-');

 int color = isFood ? getColorWhite() : fruit;

 setChar(x, y + getInfoScoreFieldHeight(), ch, color);

 ch = current.getCharacter();
 color = current.getColor();
 if (isWarning)
  color = getColorWhite();
 x = current.getPosition().getX();
 y = current.getPosition().getY();
 setChar(x, y + getInfoScoreFieldHeight(), ch, color);
}

void Draw::printCombo(const Player& pacman, const std::vector<std::string>& map,
  int combo)
{
 int x = pacman.getPosition().getX();
 int y = pacman.getPosition().getY();
 int height = y + getInfoScoreFieldHeight();

 std::string text = std::to_string(combo);

 x -= (text.length() / 2);

 if (x < 0)
  x = 0;
 else if ((text.length() + x) >= getPlayingFieldWidth())
  x = (getPlayingFieldWidth() - 1 - text.length());

 for (unsigned int i = 0; i < text.length(); i++)
 {
  setChar(x + i, height, text[i], getColorCyan());
 }
  
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

 for (unsigned int i = 0; i < text.length(); i++)
 {
  setChar(x + i, height, map[y][x + i]);
 }
}

void Draw::printPacman(const Player& pacman, bool show)
{
 const int ch = pacman.getCurrentCharacter();
 const int color = pacman.getColor();
 if (show)
 {
  const int x = pacman.getPosition().getX();
  const int y = pacman.getPosition().getY() + getInfoScoreFieldHeight();
  setChar(x, y, ch, color);
 }
 else
 {
  const int x = pacman.getOldPosition().getX();
  const int y = pacman.getOldPosition().getY() + getInfoScoreFieldHeight();
  setChar(x, y);
 }
}

void Draw::printGameOver()
{
 char text[10] = "GAME OVER";

 int y = getInfoScoreFieldHeight() + 17;

 for (int i = 0; i < 9; i++)
 {
  setChar(i + 9, y, text[i], getColorWhite());
 }
}

void Draw::printFruit(int x, int y, int color)
{
 unsigned char fruitChar = static_cast<unsigned char> (253);
 Draw::setChar(x, y + getInfoScoreFieldHeight(), fruitChar, color);
}

void Draw::printDyingPacman()
{
 int x = getPlayingFieldWidth() / 2;
 int y = (getPlayingFieldHeight() / 2) + getInfoScoreFieldHeight();

 unsigned char ch = static_cast<unsigned char> (250);

 setChar(x, y, '<', getColorYellow());
 std::this_thread::sleep_for(std::chrono::milliseconds(200));
 setChar(x, y, 'v', getColorYellow());
 std::this_thread::sleep_for(std::chrono::milliseconds(200));
 setChar(x, y, '>', getColorYellow());
 std::this_thread::sleep_for(std::chrono::milliseconds(200));
 setChar(x, y, '^', getColorYellow());
 std::this_thread::sleep_for(std::chrono::milliseconds(200));
 setChar(x, y, ch, getColorYellow());
 std::this_thread::sleep_for(std::chrono::milliseconds(200));
 setChar(x, y);
}

void Draw::clearALL()
{
 clearScreen();
}
