#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

#include <chrono>
#include <thread>

#include <vector>
#include <deque>

#include "Player.h"
#include "Ghost.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"

#include "Draw.h"
#include "SimpleTimer.h"
#include "SimpleConio.h"

class Game
{
public:
 Game();

 ~Game();

 void run();

private:
 void updateFrame(float deltaTime);
 void keyPressed(unsigned char ch);

 bool isColision(Position pos);
 int getReverseMod(int mode);

 void initMap();
 void initHightScore();
 void checkFood();
 void setFruit();
 void checkDeath();
 void death();
 void gameOver();
 void gameWin();
 void releaseGhosts();

 void movePlayer();
 void moveNormalGhosts();
 void moveAbnormalGhosts(int mode);

 void warnPlayer();
 void setSuper(bool super);
 void changeWave();

private:
 bool isPause;
 bool isWinner;
 bool isOneUp;
 bool isFruitSetted;
 bool warning;

 char prevButton;

 int waveCount;
 int waveMod;
 int amountOfFood;
 int score;
 int fruit;
 int combo;
 int hightScore;
 int level;
 const int blinky;

 SimpleTimer superTimer;
 SimpleTimer waveTimer;
 SimpleTimer checkWaitTimer;
 const SimpleTimer unitMoveTimer;
 const SimpleTimer deadGhostMoveTimer;
 const SimpleTimer frightenedMoveTimer;
 const SimpleTimer winTimer;
 const SimpleTimer spawnFruitTimer;
 const SimpleTimer warningTimer;

 std::vector<std::string> map;
 Ghost* ghosts[4];
 std::deque<int> fruits;

 Player* pacman;
 Draw drawManager;
 SimpleConio keyboard;
};

#endif