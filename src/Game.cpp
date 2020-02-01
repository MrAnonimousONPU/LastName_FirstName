#include "Game.h"

Game::Game() :
 isPause(false),
 isWinner(false), 
 isOneUp(false),
 isFruitSetted(false), 
 warning(false),

 waveCount(0),
 waveMod(getModeScatter()),
 amountOfFood(getMaxFood()),
 score(0), 
 combo(100), 
 level(1), 
 blinky(0),

 checkWaitTimer(1),
 superTimer(10.0f),
 waveTimer(7.0f),
 unitMoveTimer(0.15f), 
 deadGhostMoveTimer(0.05f), 
 frightenedMoveTimer(0.3f),
 winTimer(1.0f), 
 spawnFruitTimer(15.0f),
 warningTimer(0.2f)
{
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
  if (nullptr != ghosts[i])
  {
   delete ghosts[i];
  }
 }
 if (nullptr != pacman)
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
  if (nullptr != ghosts[i])
  {
   drawManager.printGhost(*ghosts[i], false, fruit, map);
  }
 }

 drawManager.printReady(true);
 std::this_thread::sleep_for(std::chrono::milliseconds(2500));
 drawManager.printReady(false);
 
 auto startTime = std::chrono::high_resolution_clock::now();

 while (true) 
 {
  keyPressed(prevButton);
  if (keyboard.kbhit())
  {
    keyPressed(keyboard.getch());
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
  if (isWinner)
  {
   if (winTimer(deltaTime))
   {
    gameWin();
   }
   drawManager.printMap(map, isWinner);
   drawManager.printPacman(*pacman, true);
  }
  else
  {

   if (checkWaitTimer(deltaTime))
   {
    releaseGhosts();
   }

   if (unitMoveTimer(deltaTime))
   {
    drawManager.printOneUp(isOneUp);

    movePlayer();
    moveNormalGhosts();
   }

   if (deadGhostMoveTimer(deltaTime))
   {
    moveAbnormalGhosts(getModeDead());
   }

   if (frightenedMoveTimer(deltaTime))
   {
    moveAbnormalGhosts(getModeFrightened());
   }

   if (pacman->isSuper())
   {
    if (3 > superTimer.getTime())
    {
     if (warningTimer(deltaTime))
     {
      warnPlayer();
     }
    }

    if(superTimer(deltaTime))
    {
     setSuper(false);
    }
   }
   else
   {
    if (7 != waveCount)
    {
     if (waveTimer(deltaTime))
     {
      changeWave();
     }

     for (int i = 0; i < getCountOfGhosts(); i++)
      if (ghosts[i]->getMode() == getReverseMod(waveMod))
       ghosts[i]->setMode(waveMod);
    }
   }

	  if (!isFruitSetted)
	  {
    if (spawnFruitTimer(deltaTime))
    {
     setFruit();
    }
	  }
  }
 }
} 

void Game::keyPressed(unsigned char ch)
{
 int arrow = 0;
 if ('\e' == ch)
 {
  ch = keyboard.getch();
    if ('[' == ch)
    {
      ch = 0;
      arrow = keyboard.getch();
    }
 }
 ch = std::toupper(ch);

 if ('P' == ch)
 {
  isPause = !isPause;
  drawManager.printPause(isPause);
 }
 else if ('W' == ch || arrow == getArrowUp())
 {
  if (!isColision(pacman->getPosition() + getDirectionUp()))
  {
   pacman->setDirection(getDirectionUp());
  }
  prevButton = 'W';
 }
 else if ('S' == ch || arrow == getArrowDown())
 {
  if (!isColision(pacman->getPosition() + getDirectionDown()))
  {
   pacman->setDirection(getDirectionDown());
  }
  prevButton = 'S';
 }
 else if ('D' == ch || arrow == getArrowRight())
 {
  if (!isColision(pacman->getPosition() + getDirectionRight()))
  {
   pacman->setDirection(getDirectionRight());
  }
  prevButton = 'D';
 }
 else if ('A' == ch || arrow == getArrowLeft())
 {
  if (!isColision(pacman->getPosition() + getDirectionLeft()))
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
  "____________________________",
  "|............||............|",
  "|.|~~|.|~~~|.||.|~~~|.|~~|.|",
  "|o|  |.|   |.||.|   |.|  |o|",
  "|.|__|.|___|.\\/.|___|.|__|.|",
  "|..........................|",
  "|.|~~|.TT.|~~~~~~|.TT.|~~|.|",
  "|.|__|.||.|__  __|.||.|__|.|",
  "|......||....||....||......|",
  "|_____.| ~~| || |~~ |._____|",
  "     |.|___| \\/ |__ |.|     ",
  "     |.||          ||.|     ",
  "     |.|| |~~--~~| ||.|     ",
  "_____|.\\/ |      | \\/.|_____",
  "      .   |      |   .      ",
  "______.TT |      | TT.______",
  "     |.|| |______| ||.|     ",
  "     |.||          ||.|     ",
  "     |.|| |~~~~~~| ||.|     ",
  "_____|.\\/ |__  __| \\/.|_____",
  "|............||............|",
  "|.|~~|.|~~~|.||.|~~~|.|~~|.|",
  "|.|_ |.|___|.\\/.|___|.| _|.|",
  "|o..||.......  .......||..o|",
  "|~|.||.TT.|~~~~~~|.TT.||.|~|",
  "|_|.\\/.||.|__  __|.||.\\/.|_|",
  "|......||....||....||......|",
  "|.|~~~~  ~~|.||.|~~  ~~~~|.|",
  "|.|________|.~~.|________|.|",
  "|..........................|",
  "|__________________________|"
 };
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
 
 std::this_thread::sleep_for(std::chrono::seconds(2));

 std::quick_exit(0);
}

void Game::gameWin()
{
 isWinner = false;
 isFruitSetted = false;

 combo = 100;

 drawManager.printPacman(*pacman, false);
 initMap();
 amountOfFood = getMaxFood();
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
  std::this_thread::sleep_for(std::chrono::milliseconds(2500));
 drawManager.printReady(false);

 level++;

 if (5 < level)
 {
  superTimer.setTimer(5);
 }
 else if (10 < level)
 {
  superTimer.setTimer(superTimer.getMaxTime() - 1);
 }
 waveTimer.setTimer(5);
 waveCount = 0;

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
 if (!isColision(pacman->getPosition() + pacman->getDirection()))
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
  waveTimer.setTimer(20);
  break;
 case 2:
  waveMod = getModeScatter();
  if (level < 5)
   waveTimer.setTimer(7);
  else
   waveTimer.setTimer(5);
  break;
 case 3:
  waveMod = getModeChase();
  waveTimer.setTimer(20);
  break;
 case 4:
  waveMod = getModeScatter();
  waveTimer.setTimer(5.0f / static_cast<float>(level));
  break;
 case 5:
  waveMod = getModeChase();
  waveTimer.setTimer(20.0f * static_cast<float>(level));
  break;
 case 6:
  waveMod = getModeScatter();
  waveTimer.setTimer(5.0f / static_cast<float>(level));
  break;
 case 7:
  waveMod = getModeChase();
  waveTimer.setTimer(0.01);
  break;
 default :
  waveMod = getModeChase();
  waveCount = 7;
 }
}

bool Game::isColision(Position pos)
{
 unsigned char ch = map[pos.getY()][pos.getX()];
 const auto food = '.';
 const auto fruitChar = static_cast<unsigned char> (253);

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

 const auto food = '.';
 const auto fruitChar = static_cast<unsigned char> (253);
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
  superTimer.setTimer(superTimer.getMaxTime());

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
 auto fruitChar = static_cast<unsigned char> (253);

 int x = getFruitX();
 int y = getFruitY();
 
 fruit = (rand() % 7) + 91;
 
 map[y][x] = fruitChar;
 drawManager.printFruit(x, y, fruit);

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
 
 drawManager.clearALL();
 
 drawManager.printCountOfLives(pacman->getLivesCount());
 std::this_thread::sleep_for(std::chrono::milliseconds(200));

 drawManager.printDyingPacman();

 if (pacman->getLivesCount() == 0)
 {
   std::this_thread::sleep_for(std::chrono::milliseconds(500));
  gameOver();
 }

 if (level < 5)
  waveTimer.setTimer(7);
 else
  waveTimer.setTimer(5);
 waveCount = 0;

 drawManager.printHightScore(hightScore);
 drawManager.printMap(map);
 pacman->setPosition(getStartX(), getStartY());
 pacman->setDirection(getDirectionLeft());
 for (int i = 0; i < getCountOfGhosts(); i++)
 {
  ghosts[i]->toStartPosition();
  drawManager.printGhost(*ghosts[i], false, fruit, map);
 }
 drawManager.printPacman(*pacman, true);
 
 map[getFruitY()][getFruitX()] = ' ';
 isFruitSetted = false;
 
 drawManager.printReady(true);
 std::this_thread::sleep_for(std::chrono::milliseconds(2500));
 drawManager.printReady(false);
}