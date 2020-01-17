#ifndef DRAW_H
#define DRAW_H

#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <deque>

#include "View.h"
#include "Ghost.h"
#include "Player.h"

class Draw : protected View
{
public:
 Draw();

protected:
 void printMap(const std::vector<std::string>& map, bool winner = false);
 void printOneUp(bool& isOneUp);
 void printHightScore(const int& hightScore);
 void printScore(int score);
 void printCountOfLives(int lives);
 void printFruits(const std::deque<int>& fruits);
 void printReady(bool show);
 void printPause(bool show);
 void printGhost(const Ghost& current, bool isWarning,
  int fruit, const std::vector<std::string>& map);
 void printCombo(const Player& pacman, const std::vector<std::string>& map,
  int combo);
 void printPacman(const Player& pacman, bool show);
 void printGameOver();
 void printFruit(int x, int y, int color);
 void printDyingPacman();
 void paintPlayingField(int color);
};

#endif