#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <chrono>
#include <thread>
#include <vector>

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
void keyPressed(char ch);

 void initMap();
 void printMap(bool winner = false);
bool checkColision(int x, int y);
 void gameOver();

 void printOneUp(bool hide);
 void printHightScore();
 void printScore();
 void printCountOfLives();
 void printReady();
 void printPause(bool show);
 void printGameOver();

 bool isPause;
 bool isWinner;
 bool isOneUp;

 int amountOfFood;
 int score;
 int level;

 float mainFrameTime;

 std::vector<std::string> map;

 Player* pacman;
};

