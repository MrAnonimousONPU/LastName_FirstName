#include "Game.h"

Game::Game() :
 isPause(false),
 isWinner(false), 
 isOneUp(false),
 isFruitSetted(false), 
 warning(false),

 waveCount(0),
 waveMod(getModeScatter()),
 amountOfFood(0), 
 score(0), 
 combo(100), 
 level(1), 
 blinky(0),

 waveTime(0),
 unitMoveTime(0),
 deadGhostMoveTime(0),
 frightenedMoveTime(0),
 winTime(0),
 spawnFruitTime(0),
 superTime(0),
 warningTime(0),
 checkWaitTime(0),

 superTimer(10.0f),
 waveTimer(7.0f),
 unitMoveTimer(0.15f), 
 deadGhostMoveTimer(0.05f), 
 frightenedMoveTimer(0.3f),
 winTimer(1.0f), 
 spawnFruitTimer(60.0f), 
 warningTimer(0.2f)
{
 srand(time(static_cast<unsigned int> (0)));
 pacman = new Player(getStartX(), getStartY());
 initMap();
 initHightScore();

 ghosts[0] = new Blinky(getStartXBlinky(), getStartYBlinky(), map, *pacman);


 ghosts[1] = new Pinky(getStartXPinky(), getStartYPinky(), map, *pacman);

 ghosts[2] = new Inky(getStartXInky(), getStartYInky(),
  map, *pacman, *ghosts[blinky]);

 ghosts[3] = new Clyde(getStartXClyde(), getStartYClyde(), map, *pacman);
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
 drawManager.printMap(map);
 drawManager.printScore(score);
 drawManager.printHightScore(hightScore);
 drawManager.printCountOfLives(pacman->getLivesCount());
 drawManager.printPacman(*pacman, true);

 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  if (NULL != ghosts[i])
  {
   drawManager.printGhost(*ghosts[i], false, fruit, map);
  }
 }

 drawManager.printReady(true);
 Sleep(2500);
 drawManager.printReady(false);
 
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
   drawManager.printMap(map, isWinner);
   drawManager.printPacman(*pacman, true);
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
    drawManager.printOneUp(isOneUp);

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

 int x = pacman->getPosition().getX();
 int y = pacman->getPosition().getY();

 if ('P' == ch)
 {
  isPause = !isPause;
  drawManager.printPause(isPause);
 }
 else if ('W' == ch || arrow == getArrowUp())
 {
  if (!isColision(x, y - 1))
  {
   pacman->setDirection(getDirectionUp());
  }
  prevButton = 'W';
 }
 else if ('S' == ch || arrow == getArrowDown())
 {
  if (!isColision(x, y + 1))
  {
   pacman->setDirection(getDirectionDown());
  }
  prevButton = 'S';
 }
 else if ('D' == ch || arrow == getArrowRight())
 {
  const bool isOutOfBounds = (x == getPlayingFieldWidth() - 1);
  if (isOutOfBounds)
  {
   x = 0;
  }
  else
  {
   x++;
  }
  if (!isColision(x, y))
  {
   pacman->setDirection(getDirectionRight());
  }
  prevButton = 'D';
 }
 else if ('A' == ch || arrow == getArrowLeft())
 {
  const bool isOutOfBounds = (x == 0);
  if (isOutOfBounds)
  {
   x = getPlayingFieldWidth() - 1;
  }
  else
  {
   x--;
  }
  if (!isColision(x, y))
  {
   pacman->setDirection(getDirectionLeft());
  }

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

void Game::initHightScore()
{
 std::string highScore = "0";

 std::ifstream fin("hightScr.bin", std::ios_base::binary);
 if (fin.is_open())
 {
  fin >> highScore;
 }

 hightScore = std::stoi(highScore);
}

void Game::gameOver()
{
 if (score > hightScore)
 {
  std::ofstream fout("hightScr.bin", std::ios_base::out | std::ios_base::trunc);
  fout << score;
 }

 drawManager.printGameOver();

 Sleep(3000);

 std::quick_exit(0);
}

void Game::gameWin()
{
 isWinner = false;
 isFruitSetted = false;

 combo = 100;

 drawManager.printPacman(*pacman, false);
 initMap();
 drawManager.printMap(map);
 pacman->setPosition(getStartX(), getStartY());
 pacman->setDirection(getDirectionLeft());

 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  ghosts[i]->toStartPosition();
  drawManager.printGhost(*ghosts[i], false, fruit, map);
 }
 drawManager.printPacman(*pacman, true);

 drawManager.printReady(true);
 Sleep(2500);
 drawManager.printReady(false);

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
 Position temp = pacman->getPosition() + pacman->getDirection();
 if (!isColision(temp.getX(), temp.getY()))
 {
  pacman->move();
  drawManager.printPacman(*pacman, false);
  drawManager.printPacman(*pacman, true);
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
   ghosts[i]->makeMove();

   drawManager.printGhost(*ghosts[i], false, fruit, map);
   drawManager.printPacman(*pacman, true);
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
   ghosts[i]->makeMove();
   drawManager.printGhost(*ghosts[i], false, fruit, map);
   drawManager.printPacman(*pacman, true);
   checkDeath();
  }
 }
}

void Game::warnPlayer()
{
 warning = !warning;
 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  if (ghosts[i]->getMode() == getModeFrightened())
  {
   drawManager.printGhost(*ghosts[i], warning, fruit, map);
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
 const int x = pacman->getPosition().getX();
 const int y = pacman->getPosition().getY();

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
  drawManager.printFruits(fruits);
  isFruitSetted = false;
 }
 drawManager.printScore(score);
}

void Game::setFruit()
{
 unsigned char fruitChar = static_cast<unsigned char> (253);

 int x = getFruitX();
 int y = getFruitY();
 
 map[y][x] = fruitChar;
 drawManager.printFruit(x, y + getInfoScoreFieldHeight(), fruit);

 isFruitSetted = true;
}

void Game::checkDeath()
{
 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  if (pacman->getPosition() == ghosts[i]->getPosition())
  {
   bool isDanger = (ghosts[i]->getMode() == getModeScatter() || 
    (ghosts[i]->getMode() == getModeChase()));
   if (isDanger)
   {
    death();
   }
   else if (ghosts[i]->getMode() == getModeFrightened())
   {
    combo *= 2;
    score += combo;
    drawManager.printCombo(*pacman, map, combo);
    drawManager.printGhost(*ghosts[i], false, fruit, map);
    ghosts[i]->setMode(getModeDead());
   }
  }
 }
 drawManager.printCountOfLives(pacman->getLivesCount());
}

void Game::death()
{
 pacman->death();
 
 drawManager.paintPlayingField(getColorBlack());
 
 drawManager.printCountOfLives(pacman->getLivesCount());
 Sleep(200);

 drawManager.printDyingPacman();

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

 drawManager.printMap(map);
 pacman->setPosition(getStartX(), getStartY());
 pacman->setDirection(getDirectionLeft());
 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  ghosts[i]->toStartPosition();
  drawManager.printGhost(*ghosts[i], false, fruit, map);
 }
 drawManager.printPacman(*pacman, true);

 drawManager.printReady(true);
 Sleep(2500);
 drawManager.printReady(false);
}