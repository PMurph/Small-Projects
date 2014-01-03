#include "main.h"

static float aspectRatio;

void initGlutWindow()
{
	glutInitWindowPosition(INIT_WIN_X_POS, INIT_WIN_Y_POS);
	glutInitWindowSize(INIT_WIN_WIDTH, INIT_WIN_HEIGHT);
	glutCreateWindow(GAME_WINDOW_TITLE);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	initGlutWindow();

	glutMainLoop();

	return 0;
}

const float getAspectRatio()
{
	return aspectRatio;
}