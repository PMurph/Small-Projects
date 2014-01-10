#include "main.h"

static void initGlutWindow();
static void displayGame();
static void windowReshape();
static void setupProjection();
static void setupModelView();
static void initGlSettings();
static void initGame();
static void cleanUpGame();

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

	glutDisplayFunc(displayGame);
	glutReshapeFunc(windowReshape);
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