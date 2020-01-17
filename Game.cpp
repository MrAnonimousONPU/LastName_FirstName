#include "Game.h"

Game::Game() : isWinner(false), isOneUp(false), isPause(false),
isFruitSetted(false), warning(false),

amountOfFood(0), score(0), combo(100), level(1), waveCount(0),
waveMod(getModeScatter()), blinky(0),

warningTime(0), frightenedMoveTime(0), 
deadGhostMoveTime(0), unitMoveTime(0), winTime(0), spawnFruitTime(0), 
superTime(0), checkWaitTime(0), waveTime(0),

unitMoveTimer(0.15f), deadGhostMoveTimer(0.05f), frightenedMoveTimer(0.3f),
winTimer(1.0f), spawnFruitTimer(60.0f), superTimer(10.0f), warningTimer(0.2f),
waveTimer(7.0f)
{
 pacman = new Player(getStartX(), getStartY());
 initMap();
 /*
 map = {
  "╔══════════════════════════╗",
  "║............││............║",
  "║.┌──┐.┌───┐.││.┌───┐.┌──┐.║",
  "║o│  │.│   │.││.│   │.│  │o║",
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
  "║o..││.......  .......││..o║",
  "║─┐.││.┌┐.┌──────┐.┌┐.││.┌─║",
  "║─┘.└┘.││.└──┐┌──┘.││.└┘.└─║",
  "║......││....││....││......║",
  "║.┌────┘└──┐.││.┌──┘└────┐.║",
  "║.└────────┘.└┘.└────────┘.║",
  "║..........................║",
  "╚══════════════════════════╝",
 };
 */

 ghosts[0] = new Ghost(getStartXBlinky(), getStartYBlinky(), 
 getGhostBlinky(),map);


 ghosts[1] = new Ghost(getStartXPinky(), getStartYPinky(),
 getGhostPinky(), map);

 ghosts[2] = new Ghost(getStartXInky(), getStartYInky(),
 getGhostInky(), map);

 ghosts[3] = new Ghost(getStartXClyde(), getStartYClyde(),
 getGhostClyde(), map);
}

Game::~Game()
{
 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  if (NULL != ghosts[i])
  {
   delete ghosts[i];
  }
 }
 if (NULL != pacman)
 {
  delete pacman;
 }
}

void Game::run()
{
 printMap();
 printScore();
 printHightScore();
 printCountOfLives();
 printPacman(true);

 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  if (NULL != ghosts[i])
  {
   printGhost(ghosts[i]);
  }
 }

 printReady(true);
 Sleep(2500);
 printReady(false);
 
 auto startTime = std::chrono::high_resolution_clock::now();

 while (true) 
 {
  keyPressed(prevButton);
  if (_kbhit())
  {
   keyPressed(_getch());
  }
  auto endTime = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> duration = endTime - startTime;
  startTime = std::chrono::high_resolution_clock::now();

  updateFrame(duration.count());
  //printFPS(duration.count());
 }
}

void Game::updateFrame(float deltaTime)
{
 if (!isPause)
 {
  if (isWinner)
  {
   winTime += deltaTime;
   if (winTime > winTimer)
   {
    gameWin();
    winTime = 0;
   }
   printMap(isWinner);
   printPacman(true);
  }
  else
  {
   unitMoveTime += deltaTime;
   deadGhostMoveTime += deltaTime;
   frightenedMoveTime += deltaTime;
   checkWaitTime += deltaTime;

   if (checkWaitTime > 1)
   {
    releaseGhosts();
    checkWaitTime = 0;
   }

   if (unitMoveTime > unitMoveTimer)
   {
    printOneUp(isOneUp);

    movePlayer();
    moveNormalGhosts();
    unitMoveTime = 0;
   }

   if (deadGhostMoveTime > deadGhostMoveTimer)
   {
    moveAbnormalGhosts(getModeDead());
    deadGhostMoveTime = 0;
   }

   if (frightenedMoveTime > frightenedMoveTimer)
   {
    moveAbnormalGhosts(getModeFrightened());
    frightenedMoveTime = 0;
   }

   if (pacman->isSuper())
   {

    superTime += deltaTime;

    if (superTime > (superTimer - 3))
    {
     warningTime += deltaTime;
     if (warningTime > warningTimer)
     {
      warnPlayer();
      warningTime = 0;
     }
    }

    if(superTime > superTimer)
    {
     setSuper(false);
    }
   }
   else
   {
    if (7 != waveCount)
    {
     waveTime += deltaTime;
     for (int i = 0; i < getCountOfGhosts(); i++)
      if (ghosts[i]->getMode() == getReverseMod(waveMod))
       ghosts[i]->setMode(waveMod);
    }

    if (waveTime > waveTimer)
    {
     changeWave();
     waveTime = 0;
    }
   }

	  if (!isFruitSetted)
	  {
    spawnFruitTime += deltaTime;
    if (spawnFruitTime > spawnFruitTimer)
    {
     setFruit();
     spawnFruitTime = 0;
    }
	  }
  }
 }
} 

void Game::keyPressed(unsigned char ch)
{
 int arrow = 0;
 if (224 == ch)
 {
  ch = 0;

  arrow = _getch();
 }
 ch = std::toupper(ch);

 int x = pacman->getPosition().x;
 int y = pacman->getPosition().y;

 if ('P' == ch)
 {
  isPause = !isPause;
  printPause(isPause);
 }
 else if ('W' == ch || arrow == getArrowUp())
 {
  if (!isColision(x, y - 1))
   pacman->setDirection(getDirectionUp());
  
  prevButton = 'W';
 }
 else if ('S' == ch || arrow == getArrowDown())
 {
  if (!isColision(x, y + 1))
   pacman->setDirection(getDirectionDown());
  
  prevButton = 'S';
 }
 else if ('D' == ch || arrow == getArrowRight())
 {
  const bool isOutOfBounds = (x == getPlayingFieldWidth() - 1);
  if (isOutOfBounds)
   x = 0;
  else 
   x++;
  if (!isColision(x, y))
   pacman->setDirection(getDirectionRight());
  
  prevButton = 'D';
 }
 else if ('A' == ch || arrow == getArrowLeft())
 {
  const bool isOutOfBounds = (x == 0);
  if (isOutOfBounds)
   x = getPlayingFieldWidth() - 1;
  else 
   x--;
  if (!isColision(x, y))
   pacman->setDirection(getDirectionLeft());
  
  prevButton = 'A';
 }

}
 
void Game::initMap()
{
 map = 
 {
  "1555555555555555555555555552",
  "6............^^............6",
  "6.!%%@.!%%%@.^^.!%%%@.!%%@.6",
  "6o^  ^.^   ^.^^.^   ^.^  ^o6",
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
  "6o..^^.......  .......^^..o6",
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
   if ('.' == current)
   {
    amountOfFood++;
    map[y][x] = static_cast<unsigned char> (250);
   }
   else if ('o' == current)
   {
    amountOfFood++;
   }
   else if ('1' == current)
   {
    map[y][x] = static_cast<unsigned char> (201);
   }
   else if ('2' == current)
   {
    map[y][x] = static_cast<unsigned char> (187);
   }
   else if ('3' == current)
   {
    map[y][x] = static_cast<unsigned char> (200);
   }
   else if ('4' == current)
   {
    map[y][x] = static_cast<unsigned char> (188);
   }
   else if ('5' == current)
   {
    map[y][x] = static_cast<unsigned char> (205);
   }
   else if ('6' == current)
   {
    map[y][x] = static_cast<unsigned char> (186);
   }
   else if ('!' == current)
   {
    map[y][x] = static_cast<unsigned char> (218);
   }
   else if ('@' == current)
   {
    map[y][x] = static_cast<unsigned char> (191);
   }
   else if ('#' == current)
   {
    map[y][x] = static_cast<unsigned char> (192);
   }
   else if ('$' == current)
   {
    map[y][x] = static_cast<unsigned char> (217);
   }
   else if ('%' == current)
   {
    map[y][x] = static_cast<unsigned char> (196);
   }
   else if ('^' == current)
   {
    map[y][x] = static_cast<unsigned char> (179);
   }
  }
 }
}

void Game::gameOver()
{
 if (score > hightScore)
 {
  std::ofstream fout("hightScr.bin", std::ios_base::out | std::ios_base::trunc);
  fout << score;
 }

 printGameOver();

 Sleep(3000);

 std::quick_exit(0);
}

void Game::gameWin()
{
 isWinner = false;
 isFruitSetted = false;

 combo = 100;

 printPacman(false);
 initMap();
 printMap();
 pacman->setPosition(getStartX(), getStartY());
 pacman->setDirection(getDirectionLeft());

 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  ghosts[i]->setStartPosition();
  printGhost(ghosts[i]);
 }
 printPacman(true);

 printReady(true);
 Sleep(2500);
 printReady(false);

 level++;

 if (5 < level)
 {
  waveTimer = static_cast<float>(7);
 }
 else if (10 < level)
 {
  superTimer -= 1;
 }
 waveTimer = static_cast<float>(5);
 waveCount = 0;
 waveTime = 0;

 if (level > 255)
 {
  gameOver();
 }
}

void Game::releaseGhosts()
{
 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  if (ghosts[i]->getMode() == getModeWait())
  {
   if (ghosts[i]->getType() == getGhostPinky())
   {
    ghosts[i]->setMode(getModeExiting());
   }
   else if (ghosts[i]->getType() == getGhostInky())
   {
    if (amountOfFood < (getMaxFood() - 30))
    {
     ghosts[i]->setMode(getModeExiting());
    }
   }
   else if (ghosts[i]->getType() == getGhostClyde())
   {
    if (amountOfFood < (getMaxFood() - (getMaxFood() / 3)))
    {
     ghosts[i]->setMode(getModeExiting());
    }
   }
  }
 }
}

void Game::movePlayer()
{
 Position pos = moveToDirection();
 if (!isColision(pos.x, pos.y))
 {
  pacman->move();
  printPacman(false);
  printPacman(true);
  checkFood();
  checkDeath();
 }
}

void Game::moveNormalGhosts()
{
 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  bool isNormal = (!(ghosts[i]->getMode() == getModeDead() || 
  ghosts[i]->getMode() == getModeFrightened()));
  if (isNormal)
  {
   if (ghosts[i]->getType() == getGhostBlinky())
   {
    ghosts[i]->move(pacman->getPosition().x, pacman->getPosition().y);
   }
   else if (ghosts[i]->getType() == getGhostPinky())
   {
    moveGhostPinky(ghosts[i]);
   }
   else if (ghosts[i]->getType() == getGhostInky())
   {
    moveGhostInky(ghosts[i]);
   }
   else if (ghosts[i]->getType() == getGhostClyde())
   {
    moveGhostClyde(ghosts[i]);
   }
   printGhost(ghosts[i]);
   printPacman(true);
   checkDeath();
  }
 }
}

void Game::moveAbnormalGhosts(int mode)
{
 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  if (mode == ghosts[i]->getMode())
  {
   ghosts[i]->move(0, 0);
   printGhost(ghosts[i]);
   printPacman(true);
  }
 }
}

void Game::moveGhostPinky(Ghost* ghost)
{
 const int direction = pacman->getDirection();
 int x = pacman->getPosition().x;
 int y = pacman->getPosition().y;

 bool isHorisontal = (direction == getDirectionLeft());
 isHorisontal = (isHorisontal || direction == getDirectionRight());

 if (isHorisontal)
 {
  x += direction == getDirectionLeft() ? -4 : 4;
 }
 else
 {
  y += direction == getDirectionUp() ? -4 : 4;
 }

 ghost->move(x, y);
}

void Game::moveGhostInky(Ghost* ghost)
{
 int x = pacman->getPosition().x - ghosts[blinky]->getPosition().x;
 int y = pacman->getPosition().y - ghosts[blinky]->getPosition().y;
 x = ghosts[blinky]->getPosition().x + (x * 2);
 y = ghosts[blinky]->getPosition().y + (y * 2);

 ghost->move(x, y);
}

void Game::moveGhostClyde(Ghost* ghost)
{
 int x = ghost->getPosition().x;
 int y = ghost->getPosition().y;
 int pacX = pacman->getPosition().x;
 int pacY = pacman->getPosition().y;
 double distance = sqrt(pow((x - pacX), 2) + pow((y - pacY), 2));
 if (distance > 8)
 {
  ghost->move(pacX, pacY);
 }
 else
 {
  x = ghost->getScatterPosition().x;
  y = ghost->getScatterPosition().y;
  ghost->move(x, y);
 }
}

void Game::warnPlayer()
{
 warning = !warning;
 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  if (ghosts[i]->getMode() == getModeFrightened())
  {
   printGhost(ghosts[i], warning);
  }
 }
}

void Game::setSuper(bool super)
{
 pacman->setSuper(super);
 superTime = 0;
 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  const int ghostMode = ghosts[i]->getMode();
  const bool isModifiable = (ghostMode == getModeScatter() ||
  ghostMode == getModeChase() || ghostMode == getModeFrightened());

  if (isModifiable)
  {
   if (super)
   {
    ghosts[i]->setMode(getModeFrightened());
   }
   else 
    ghosts[i]->setMode(getModeChase());
  }
 }
}

void Game::changeWave()
{
 waveCount++;
 switch (waveCount)
 {
 case 1:
  waveMod = getModeChase();
  waveTimer = static_cast<float>(20);
  break;
 case 2:
  waveMod = getModeScatter();
  if (level < 5)
   waveTimer = static_cast<float>(7);
  else
   waveTimer = static_cast<float>(5);
  break;
 case 3:
  waveMod = getModeChase();
  waveTimer = static_cast<float>(20);
  break;
 case 4:
  waveMod = getModeScatter();
  waveTimer = static_cast<float>(5) / level;
  break;
 case 5:
  waveMod = getModeChase();
  waveTimer = static_cast<float>(20) * level;
  break;
 case 6:
  waveMod = getModeScatter();
  waveTimer = static_cast<float>(5) / level;
  break;
 case 7:
  waveMod = getModeChase();
  waveTimer = 0.01f;
  break;
 default :
  waveMod = getModeChase();
  waveCount = 7;
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
     View::setChar(x, y + getInfoScoreFieldHeight(), j, getColorWhite());
	    break;
	   case 'o' :
     View::setChar(x, y + getInfoScoreFieldHeight(), j, getColorWhite());
     break;
	   case '-' :
     View::setChar(x, y + getInfoScoreFieldHeight(), j, getColorWhite());
	    break;
    default:
     if (winner)
     {
      View::setChar(x, y + getInfoScoreFieldHeight(), j, rand() % 14);
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

bool Game::isColision(int x, int y)
{
 unsigned char ch = map[y][x];
 const unsigned char food = static_cast<unsigned char> (250);
 const unsigned char fruitChar = static_cast<unsigned char> (253);

 const bool isCanGo = (ch == ' ' || ch == food || ch == 'o' || ch == fruitChar);
 bool hasColision = !(isCanGo);

 return hasColision;
}

int Game::getReverseMod(int mode)
{
 if (mode == getModeChase())
 {
  return getModeScatter();
 }
 else
 {
  return getModeChase();
 }
}

void Game::checkFood()
{
 int x = pacman->getPosition().x;
 int y = pacman->getPosition().y;

 const unsigned char food = static_cast<unsigned char> (250);
 const unsigned char fruitChar = static_cast<unsigned char> (253);
 unsigned char currentChar = map[y][x];

 if (currentChar == food)
 {
  score += 10;
  map[y][x] = ' ';
  amountOfFood--;
  if (0 == amountOfFood)
  {
   isWinner = true;
  }
 }
 else if ('o' == currentChar)
 {
  score += 50;
  combo = 100;

  setSuper(true);

  map[y][x] = ' ';
  amountOfFood--;
  if (amountOfFood == 0)
  {
   isWinner = true;
  }
 }
 else if (currentChar == fruitChar)
 {
  score += 100;
  map[y][x] = ' ';
  fruits.push_front(fruit);

  if(fruits.size() > 8)
  {
   fruits.pop_back();
  }
  printFruits();
  isFruitSetted = false;
 }
 printScore();
}

void Game::setFruit()
{
 unsigned char fruitChar = static_cast<unsigned char> (253);

 int x = getFruitX();
 int y = getFruitY();
 
 map[y][x] = fruitChar;
 View::setChar(x, y + getInfoScoreFieldHeight(), fruitChar, fruit);

 isFruitSetted = true;
}

void Game::checkDeath()
{
 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  bool isColisionX = (pacman->getPosition().x == ghosts[i]->getPosition().x);
  bool isColisionY = (pacman->getPosition().y == ghosts[i]->getPosition().y);
  if (isColisionX && isColisionY)
  {
   bool isDanger = (ghosts[i]->getMode() == getModeScatter());
   isDanger = (isDanger || (ghosts[i]->getMode() == getModeChase()));
   if (isDanger)
   {
    death();
   }
   else if (ghosts[i]->getMode() == getModeFrightened())
   {
    combo *= 2;
    score += combo;
    printCombo();
    printGhost(ghosts[i]);
    ghosts[i]->setMode(getModeDead());
   }
  }
 }
 printCountOfLives();
}

void Game::death()
{
 pacman->death();
 
 unsigned char ch = static_cast<unsigned char> (219);

 for (int x = 0; x < getPlayingFieldWidth(); x++)
 {
  for (int y = 0; y < getPlayingFieldHeight(); y++)
  {
   View::setChar(x, y + getInfoScoreFieldHeight(), ch, getColorBlack());
   Sleep(1);
  }
 }
 int x = getPlayingFieldWidth() / 2;
 int y = (getPlayingFieldHeight() / 2) + getInfoScoreFieldHeight();

 ch = static_cast<unsigned char> (250);

 View::setChar(x, y, '<', getColorYellow());
 Sleep(200);
 View::setChar(x, y, 'v', getColorYellow());
 Sleep(200);
 View::setChar(x, y, '>', getColorYellow());
 Sleep(200);
 View::setChar(x, y, '^', getColorYellow());
 Sleep(200);
 View::setChar(x, y, ch, getColorYellow());
 Sleep(200);
 View::setChar(x, y);
 printCountOfLives();
 Sleep(200);
 if (pacman->getLivesCount() == 0)
 {
  Sleep(500);
  gameOver();
 }

 if (level < 5)
  waveTimer = static_cast<float>(7);
 else
  waveTimer = static_cast<float>(5);
 waveCount = 0;
 waveTime = 0;

 printMap();
 pacman->setPosition(getStartX(), getStartY());
 pacman->setDirection(getDirectionLeft());
 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  ghosts[i]->setStartPosition();
  printGhost(ghosts[i]);
 }
 printPacman(true);

 printReady(true);
 Sleep(2500);
 printReady(false);
}

void Game::printOneUp(bool hide)
{
 isOneUp = !isOneUp;
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
 std::string highScore = "0";

 std::ifstream fin("hightScr.bin", std::ios_base::binary);
 if (fin.is_open())
 {
  fin >> highScore;
 }
  
 this->hightScore = std::stoi(highScore);
 text += highScore;

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

void Game::printFruits()
{
 unsigned char fruitChar = static_cast<unsigned char> (253);
 for (unsigned int i = 0; i < fruits.size(); i++)
 {
  int x = getPlayingFieldWidth() - 2 - i;
  int y = getInfoScoreFieldHeight() + getPlayingFieldHeight();
  View::setChar(x, y, fruitChar, fruits[i]);
 }
}

void Game::printReady(bool show)
{
 char text[6] = "READY";

 int y = getInfoScoreFieldHeight() + 17;

 for (int i = 0; i < 5; i++)
 {
  if (show)
  {
   View::setChar(i + 11, y, text[i], getColorWhite());
  }
  else
  {
   View::setChar(i + 11, y);
  }
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

void Game::printGhost(Ghost* current, bool isWarning)
{
 int x = current->getOldPosition().x;
 int y = current->getOldPosition().y;
 unsigned char ch = map[y][x];
 unsigned char food = static_cast<unsigned char> (250);

 bool isFood = (ch == food || ch == 'o' || ch == '-');

 int color = isFood ? getColorWhite() : fruit;

 View::setChar(x, y + getInfoScoreFieldHeight(), ch, color);

 ch = current->getCharacter();
 color = current->getColor();
 if (isWarning)
  color = getColorWhite();
 x = current->getPosition().x;
 y = current->getPosition().y;
 View::setChar(x, y + getInfoScoreFieldHeight(), ch, color);
}

void Game::printCombo()
{
 int x = pacman->getPosition().x;
 int y = pacman->getPosition().y;
 int height = y + getInfoScoreFieldHeight();

 std::string text = std::to_string(combo);

 x -= (text.length() / 2);

 if (x < 0)
  x = 0;
 else if ((x + text.length()) >= getPlayingFieldWidth())
  x = (getPlayingFieldWidth() - 1 - text.length());
 
 for (unsigned int i = 0; i < text.length(); i++)
 {  
  View::setChar(x + i, height, text[i], getColorCyan());
 }

 Sleep(500);

 for (unsigned int i = 0; i < text.length(); i++)
 {
  View::setChar(x + i, height, map[y][x + i]);
 }
}

void Game::printPacman(bool show)
{
 char ch = pacman->getCurrentCharacter();
 int color = pacman->getColor();
 if (show)
 {
  int x = pacman->getPosition().x;
  int y = pacman->getPosition().y + getInfoScoreFieldHeight();
  View::setChar(x, y, ch, color);
 }
 else
 {
  int x = pacman->getOldPosition().x;
  int y = pacman->getOldPosition().y + getInfoScoreFieldHeight();
  View::setChar(x, y);
 }
}

void Game::printGameOver()
{
 printCountOfLives();
 char text[10] = "GAME OVER";

 int y = getInfoScoreFieldHeight() + 17;

 for (int i = 0; i < 9; i++)
 {
  View::setChar(i + 9, y, text[i], getColorWhite());
 }
}

void Game::printFPS(float deltaTime)
{
 fpsTime += deltaTime;
 fpsCount++;
 if (fpsTime > 1)
 {
  std::string text = "FPS : ";
  text += std::to_string(fpsCount);

  for (unsigned int i = 0; i < text.length(); i++)
  {
   View::setChar(i + 9, 0, text[i], getColorWhite());

  }

  fpsCount = 0;
  fpsTime = 0;
 }
}

Position Game::moveToDirection()
{
 Position pos = pacman->getPosition();
 int direction = pacman->getDirection();
 bool isHorisontal = (direction == getDirectionLeft() || 
 direction == getDirectionRight());

 if (isHorisontal)
 {
  pos.x += direction == getDirectionLeft() ? -1 : 1;
  if (pos.x == getPlayingFieldWidth())
   pos.x = 0;
  else if (pos.x == -1)
   pos.x = getPlayingFieldWidth() - 1;
 }
 else
  pos.y += direction == getDirectionUp() ? -1 : 1;

 return pos;
}