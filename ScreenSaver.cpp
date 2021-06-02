#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

/**
Creates the main window, registers event handlers, and
initializes OpenGL stuff.
*/
void InitGraphics(int argc, char* argv[]);

/**
Sets the logical coordinate system we will use to specify
our drawings.
*/
void SetTransformations();

/**
Handles the paint event. This event is triggered whenever
our displayed graphics are lost or out-of-date.
ALL rendering code should be written here.
*/
void OnDisplay();


// you can find more details about key handling on this link
// http://www.lighthouse3d.com/opengl/glut/index.php?5

float fXPos, fYPos, fRot;
int state;

int main(int argc, char* argv[])
{
	fXPos = fYPos = fRot = state= 0;
	InitGraphics(argc, argv);
	return 0;
}

/**
Creates the main window, registers event handlers, and
initializes OpenGL stuff.
*/
void InitGraphics(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//Create an 800x600 window with its top-left corner at pixel (100, 100)
	glutInitWindowPosition(100, 100); //pass (-1, -1) for Window-Manager defaults
	glutInitWindowSize(800, 600);
	glutCreateWindow("Screen Saver");
	//OnDisplay will handle the paint event
	glutDisplayFunc(OnDisplay);
	// here is the setting of the idle function
	glutIdleFunc(OnDisplay);
	// here is the setting of the key function
	//glutKeyboardFunc(OnKeyPress);
	//glutSpecialFunc(OnSpecialKeyPress);

	SetTransformations();

	glutMainLoop();
}

/**
Sets the logical coordinate system we will use to specify
our drawings.
*/
void SetTransformations() {
	//set up the logical coordinate system of the window: [-100, 100] x [-100, 100]
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}

/**
Handles the paint event. This event is triggered whenever
our displayed graphics are lost or out-of-date.
ALL rendering code should be written here.
*/
void OnDisplay()
{
	// pushes the current matrix stack down by one,
	// duplicating the current matrix.
	// glPushMatrix and glPopMatrix are used here instead of glLoadIdentity.
	//glPushMatrix();
	// clear the transformation matrix
	glLoadIdentity();

	//set the background color to white
	glClearColor(1, 1, 1, 1);
	//fill the whole color buffer with the clear color
	glClear(GL_COLOR_BUFFER_BIT);
	
	glPushMatrix();

	glTranslatef(fXPos, fYPos, 0);
	glRotatef(fRot +=0.1, 0, 0, 1);
	if (state == 0)
	{
		fXPos += 0.01;
		fYPos += 0.005;

	}
	if (state == 1)
	{
		fXPos -= 0.01;
		fYPos += 0.01;
		fRot += 1;

	}
	if (state == 2)
	{
		fXPos -= 0.01;
		fYPos -= 0.01;

	}
	if (state == 3)
	{
		fXPos += 0.01;
		fYPos -= 0.01;
		fRot += 1;

	}
	 
	glBegin(GL_QUADS);

	if (state == 0)
		glColor3f(1, 0, 0);
	if (state == 0 && fXPos > 75)
	{
		state = 1;
		glColor3f(0, 1, 0);
	}
	if (state == 1 && fYPos > 75)
	{
		state = 2;
		glColor3f(0, 0, 1);
	}
	if (state == 2 && fXPos < -75)
	{
		state = 3;
		glColor3f(0, 0, 0);
	}
	if (state == 3 && fYPos <-75)
	{
		state = 0;
		glColor3f(1, 0, 0);
	}

		glVertex3f(-20, -20, 0);
		glVertex3f(20, -20, 0);
		glVertex3f(20, 20, 0);
		glVertex3f(-20, 20, 0);
	glEnd();

	glPopMatrix();

	// swapping the buffers causes the rendering above to be 
	// shown
	glutSwapBuffers();

}
