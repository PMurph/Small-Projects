#include "main.h"

#include <iostream>

static void initGlutWindow();
static void displayGame();
static void windowReshape();
static void setupProjection();
static void setupModelView();
static void initGlSettings();
static void initGame();
static void cleanUpGame();
static void setupCallbacks();
static void handleInput(unsigned char key, int x, int y);
static void updateGame(int value);

static GLint width, height;
static Game * game;

static void initGlutWindow()
{
	glutInitWindowPosition(INIT_WIN_X_POS, INIT_WIN_Y_POS);
	glutInitWindowSize(INIT_WIN_WIDTH, INIT_WIN_HEIGHT);
	glutCreateWindow(GAME_WINDOW_TITLE);
	
	width = INIT_WIN_WIDTH;
	height = INIT_WIN_HEIGHT;
}

static void initGlSettings()
{
	glClearColor(static_cast<GLclampf>(0.7), static_cast<GLclampf>(0.7), static_cast<GLclampf>(0.7), static_cast<GLclampf>(1.0));
}

static void initGame()
{
	game = new Game();
}

static void windowReshape(int newWidth, int newHeight)
{
	//TODO: This function is not working correctly

	width = static_cast<GLint>(newWidth);
	height = static_cast<GLint>(newHeight);

	game->windowReshaped();

	displayGame();
}

static void setupCallbacks()
{
	glutDisplayFunc(displayGame);
	glutReshapeFunc(windowReshape);
	glutTimerFunc( static_cast<int>( 1000.0f / 60.0f ), updateGame, 0 );
	glutKeyboardFunc(handleInput);
}

static void updateGame(int value)
{
	game->updateGame(value);

	glutPostRedisplay();
	glutTimerFunc( static_cast<int>( 1000.0f / 60.0f ), updateGame, 0 );
}

static void handleInput(unsigned char key, int x, int y)
{
	game->handleInput(key);
}

static void displayGame()
{
	glClear(GL_COLOR_BUFFER_BIT);

	setupProjection();
	setupModelView();

	game->drawGame();

	glFlush();
	glutSwapBuffers();
}

static void setupProjection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, width, 0, height);
}

static void setupModelView()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void cleanUpGame()
{
	delete game;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	initGlutWindow();
	initGlSettings();
	initGame();

	setupCallbacks();
	glutMainLoop();

	cleanUpGame();

	return 0;
}

const int getWidth()
{
	return width;
}

const int getHeight()
{
	return height;
}