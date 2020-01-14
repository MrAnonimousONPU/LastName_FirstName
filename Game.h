#pragma once

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
#include "View.h"

class Game
{
public:
 Game();

 ~Game();

 void run();

private:
 void updateFrame(float deltaTime);
 void keyPressed(unsigned char ch);

 bool checkColision(int x, int y);
 int getReverseMod(int mode);
 void initMap();
 void checkFood();
 void setFruit();
 void checkDeath();
 void death();
 void gameOver();
 void gameWin();

 void printMap(bool winner = false);
 void printOneUp(bool hide);
 void printHightScore();
 void printScore();
 void printCountOfLives();
 void printFruits();
 void printReady(bool show);
 void printPause(bool show);
 void printGhost(Ghost* current, bool isWarning = false);
 void printCombo();
 void printPacman(bool show);
 void printGameOver();

 void printFPS(float deltaTime);

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

 int fpsCount;

 float waveTime;
 float unitMoveTime;
 float deadGhostMoveTime;
 float frightenedMoveTime;
 float winTime;
 float deathTime;
 float spawnFruitTime;
 float superTime;
 float warningTime;
 float checkWaitTime;

 float fpsTime;

 float waveTimer;
 float unitMoveTimer;
 float deadGhostMoveTimer;
 float frightenedMoveTimer;
 float winTimer;
 float deathTimer;
 float spawnFruitTimer;
 float superTimer;
 float warningTimer;

 Position moveToDirection();

 std::vector<std::string> map;
 Ghost* ghosts[4];
 std::deque<int> fruits;

 Player* pacman;
};

