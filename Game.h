#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

#include <chrono>

#include <vector>
#include <deque>

#include <Windows.h>
#include <conio.h>

#include "Player.h"
#include "Ghost.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"
#include "Draw.h"

class Game : Draw
{
public:
 Game();

 ~Game();

 void run();

private:
 void updateFrame(float deltaTime);
 void keyPressed(unsigned char ch);

 bool isColision(int x, int y);
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

 float waveTime;
 float unitMoveTime;
 float deadGhostMoveTime;
 float frightenedMoveTime;
 float winTime;
 float spawnFruitTime;
 float superTime;
 float warningTime;
 float checkWaitTime;

 float superTimer;
 float waveTimer;
 const float unitMoveTimer;
 const float deadGhostMoveTimer;
 const float frightenedMoveTimer;
 const float winTimer;
 const float spawnFruitTimer;
 const float warningTimer;

 std::vector<std::string> map;
 Ghost* ghosts[4];
 std::deque<int> fruits;

 Player* pacman;
};

#endif