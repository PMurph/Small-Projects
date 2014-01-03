#ifndef __MAIN_H
#define __MAIN_H

#include <Windows.h>
#include <GL\glut.h>
#include <assert.h>
#include <math.h>

#include "Drawable.h"

const GLint INIT_WIN_WIDTH = 600;
const GLint INIT_WIN_HEIGHT = 400;

const GLint INIT_WIN_X_POS = 0;
const GLint INIT_WIN_Y_POS = 0;

const char GAME_WINDOW_TITLE[] = "Grid Snake";

const GLfloat getAspectRatio();
const GLint getWidth();
const GLint getHeight();

#endif