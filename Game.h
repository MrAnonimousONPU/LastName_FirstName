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
 bool checkColision(int x, int y);
 void checkFood();
 void checkfruit();
 void checkDeath();
 void gameOver();
 void gameWin();

 void printMap(bool winner = false);
 void printOneUp(bool hide);
 void printHightScore();
 void printScore();
 void printCountOfLives();
 void printReady();
 void printPause(bool show);
 void printPacman(bool show, int x, int y);
 void printPacman(bool show);
 void printGameOver();

 bool isPause;
 bool isWinner;
 bool isOneUp;
 bool isFirstCheckPassed;

 int amountOfFood;
 int score;
 int level;

 float mainFrameTime;

 std::vector<std::string> map;
 std::vector<Position> ghosts;

 Player* pacman;
};

