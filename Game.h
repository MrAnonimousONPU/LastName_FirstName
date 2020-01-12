#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

#include <chrono>
#include <thread>

#include <vector>
#include <deque>

#include <Windows.h>
#include <conio.h>

#include "Player.h"
#include "View.h"

class Game
{
public:
 Game();

 void run();

private:
 void updateFrame(float deltaTime);
 void keyPressed(unsigned char ch);

 void initMap();
 bool checkColision(int x, int y);
 void checkFood();
 void setFruit();
 void checkDeath();
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
 void printPacman(bool show, int x, int y);
 void printPacman(bool show);
 void printGameOver();

 bool isPause;
 bool isWinner;
 bool isDeath;
 bool isOneUp;
 bool isFirstCheckPassed;
 bool isFruitSetted;

 int amountOfFood;
 int score;
 int fruit;
 int hightScore;
 int level;

 float mainFrameTime;
 float winTime;
 float deathTime;
 float spawnFruitTime;
 float superTime;

 float mainFrameTimer;
 float winTimer;
 float deathTimer;
 float spawnFruitTimer;
 float superTimer;

 std::vector<std::string> map;
 std::vector<Position> ghosts;
 std::deque<int> fruits;

 Player* pacman;
};

