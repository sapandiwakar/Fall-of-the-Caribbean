#include<iostream>
#include<gl/Glut.h>

using namespace std;

/*GLfloat xRot = 0.0;
GLfloat yRot = 0.0;

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	
}



void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if(key > 356.0f)
		xRot = 0.0f;

	if(key < -1.0f)
		xRot = 355.0f;

	if(key > 356.0f)
		yRot = 0.0f;

	if(key < -1.0f)
		yRot = 355.0f;

	// Refresh the Window
	glutPostRedisplay();
}*/
void disk()
{
	
	GLUquadricObj *pObj;
//	glScalef(30,30,30);
		
	glMatrixMode(GL_MODELVIEW);
	
//	glPushMatrix();
		glScalef(0.033,0.033,0.033);
		
		glColor3f(0,0,0);
//		glTranslatef(0,0,-100);
//		glTranslatef(10,0,0);
		//glRotatef(10,1,0,0);
		pObj = gluNewQuadric();
		gluQuadricNormals(pObj, GLU_SMOOTH);
	
		gluDisk(pObj,0,10,20,8);
	
		
//	glPopMatrix();
	
}

/*void TimerFunction(int value)
{
		glutPostRedisplay();
		glutTimerFunc(33,TimerFunction,1);
		
}*/

/*void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
		
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	
	disk();
	
	glutSwapBuffers();
	
}


void ChangeSize(int w, int h)
{
		
	// Prevent a divide by zero
	
	if(h == 0)
		h = 1;
	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60,w/h, 1,2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-1000);


}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Pole");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(display);
	glutSpecialFunc(SpecialKeys);
	init();
	glutMainLoop();
}*/		