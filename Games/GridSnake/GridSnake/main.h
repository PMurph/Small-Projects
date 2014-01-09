#pragma once

#include <Windows.h>
#include <GL\glut.h>
#include <assert.h>
#include <math.h>

#include "Drawable.h"
#include "Drawer.h"
#include "Game.h"

const GLint INIT_WIN_WIDTH = 600;
const GLint INIT_WIN_HEIGHT = 400;

const GLint INIT_WIN_X_POS = 0;
const GLint INIT_WIN_Y_POS = 0;

const char GAME_WINDOW_TITLE[] = "Grid Snake";

const GLint getWidth();
const GLint getHeight();