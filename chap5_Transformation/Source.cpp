#include <iostream>
#include <fstream>
#include <string>
#include <glut.h>

using namespace std;

//Initiallizing GPoint class to hold vertices for example (x,y)-->(4,7)
class GPoint
{
public:
	float x;
	float y;
};

//Initiallizing variables
double PI = 3.14159265358979323846;
float angle = 0;   //Angle for rotation                 
float s = 1;       //Size variable
float T = 0;       //Translation variable
int screenWidth = 500;
int screenHeight = 500;

//drawing one wing than coping 4 time with rotatef
void drawFanWings() 
{ 
	for (int i = 0; i < 4; i++)
	{
		glRotatef(i * 90, 0, 0, 1);
		glBegin(GL_POLYGON);
		glVertex2f(-1, 3);
		glVertex2f(0, 0);
		glVertex2f(1, 3);
		glVertex2f(0, 4);
		glEnd();
	}
}

void mydisplay(void)
{
	glClearColor(0.9,0.9,0.9,0);
	glColor3f(0, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// These 3 cormands establish CS 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);

	//drawing fan wings
	glPushMatrix();
	glRotatef(angle, 0, 0, 1);
	glScalef(s, s, s);
	glTranslatef(T, T, 0);
	glColor3f(.5, .2, .5);
	drawFanWings();
	glPopMatrix();

	//house
	glColor3f(.2, 0.85, 1); 
	glBegin(GL_POLYGON);
	glVertex2f(7, -7);
	glVertex2f(5, -5);
	glVertex2f(3, -7);
	glVertex2f(3, -10);
	glVertex2f(7, -10);
	glEnd();

	//bar
	glColor3f(0, 0, 0);  
	glBegin(GL_LINE_STRIP);
	glVertex2f(7, -7);
	glVertex2f(3, -7);;
	glEnd();

	//house door
	glColor3f(.66,.66,.66); 
	glBegin(GL_POLYGON);
	glVertex2f(4, -10);
	glVertex2f(5, -10);
	glVertex2f(5, -8.5);
	glVertex2f(4, -8.5);
	glEnd();
	
	//Stand
	glColor3f(0, 0, 0);  
	glBegin(GL_POLYGON);  
	glVertex2f(0.1, 0);
	glVertex2f(-0.1, 0);
	glVertex2f(-0.1, -10);
	glVertex2f(.1, -10);
	glEnd();

	//base of the stand
	float X = 0, Y = -10, radius = .5;
	for (float a = 0; a < 2 * (PI / 2); a += 0.01) {
		glBegin(GL_POLYGON);
		glVertex2f(X + cos(a)*radius, Y + sin(a)*radius);
		glVertex2f(X + cos(a + 0.01)*radius, Y + sin(a + 0.01)*radius);
		glVertex2f(X, Y);
		glEnd();
	}

	//sun
	glColor3f(2.55,1.65,.79);  
	X = -6, Y = 6, radius = 2;
	for (float a = 0; a < 2 * (PI); a += 0.01) {
		glBegin(GL_POLYGON);
		glVertex2f(X + cos(a)*radius, Y + sin(a)*radius);
		glVertex2f(X + cos(a + 0.01)*radius, Y + sin(a + 0.01)*radius);
		glVertex2f(X, Y);
		glEnd();
	}

	glFlush();
}

//My mouse function
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON)
	{
		//if left button of mouse is clicked rotation variable will change 
		//means fan will rotate a little
		angle++;
		glutPostRedisplay();
	}
	if (button == GLUT_MIDDLE_BUTTON)
	{
		//if middle button of mouse is clicked transformation variable will change 
		//means fan wings will change its origin to another place
		T++;
		glutPostRedisplay();
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		//if Right button of mouse is clicked size variable will change 
		//means fan wings will change its size to a bigger one
		s++;
		glutPostRedisplay();
	}

}

//My Timer func --> Rotate a fan a little in every 50ms since time lap is so small fan will appear as it is continuously rotating 
void Timer(int t) 
{
	t++;
	angle -= 5;
	glutPostRedisplay();
	glutTimerFunc(50, Timer, t);
}

//Main Function.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Transfomation");

	glutDisplayFunc(mydisplay);
	glutMouseFunc(mouse);
	glutTimerFunc(50, Timer, 0.5);
	glutMainLoop();

	return 0;
}

