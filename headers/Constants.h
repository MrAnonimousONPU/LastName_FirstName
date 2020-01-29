#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Position.h"

int getColorBlack();
int getColorBlue();
int getColorCyan();
int getColorPink();
int getColorRed();
int getColorOrange();
int getColorYellow();
int getColorWhite();

int getCountOfGhosts();
int getMaxNumLives();
int getMaxFood();
int getStartX();
int getStartY();
int getGateX();
int getGateY();

int getInfoScoreFieldHeight();
int getInfoLivesFieldHeight();
int getPlayingFieldWidth();
int getPlayingFieldHeight();

Position getDirectionUp();
Position getDirectionDown();
Position getDirectionRight();
Position getDirectionLeft();

int getFruitX();
int getFruitY();

int getArrowUp();
int getArrowDown();
int getArrowRight();
int getArrowLeft();

int getGhostBlinky();
int getGhostPinky();
int getGhostInky();
int getGhostClyde();

int getModeDead();
int getModeWait();
int getModeChase();
int getModeScatter();
int getModeFrightened();
int getModeExiting();

int getStartXBlinky();
int getStartYBlinky();
int getStartXPinky();
int getStartYPinky();
int getStartXInky();
int getStartYInky();
int getStartXClyde();
int getStartYClyde();

#endif