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

void pole()
{
	
	GLUquadricObj *pObj;
	
	//glTranslatef(0,0,30);
	glScalef(0.033,0.033,0.033);
	glScalef(10,10,10);
	glMatrixMode(GL_MODELVIEW);
	
 //glPushMatrix();
		
		
		//glScalef(20, 20,20);
//		glLoadIdentity();
	
		glColor3ub(168,57,30);
	
		glTranslatef(2.5,20,-2);
//		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
//		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glRotatef(90,1.0,0.0,0.0);
		
	//	glRotatef(180,0.0,1.0,0.0);
	//	glRotatef(90,0,0,1);
		
		//glTranslatef(t,0,0);*/
	//	glRotatef(50,1.0,0.0,0.0);
	//	glRotatef(2,0.0,1.0,0.0);
		
		
	//	glScalef(1.5,1.25,1.5);
		pObj = gluNewQuadric();
		gluQuadricNormals(pObj, GLU_SMOOTH);

		gluCylinder(pObj,0.25,0.75,50,20,8);
			
	//glPopMatrix();
	
}

/*void TimerFunction(int value)
{
		glutPostRedisplay();
		glutTimerFunc(33,TimerFunction,1);
		
}*/

/*void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	

		glPushMatrix();	
			
			pole();
			
		glPopMatrix();
	
//	xrot += 0.2;
//	yrot += 0.02;
	
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
//	glutTimerFunc(1000,TimerFunction,1);
	glutSpecialFunc(SpecialKeys);
	init();
	glutMainLoop();
}*/