#ifndef __MAIN_H
#define __MAIN_H

#include <Windows.h>
#include <GL\glut.h>
#include <assert.h>

#include "Drawable.h"

const int INIT_WIN_WIDTH = 600;
const int INIT_WIN_HEIGHT = 400;

const int INIT_WIN_X_POS = 0;
const int INIT_WIN_Y_POS = 0;

const char GAME_WINDOW_TITLE[] = "Grid Snake";

const float getAspectRatio();

#endif