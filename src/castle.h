/*
 *  Header files included
 */
#include<windows.h>		// For window
#include<gl/glut.h>		// For open Gl library
#include<math.h>		// For mathematical calculations
#include "RgbImage.h"	// For Bitmap Image loading

/*
 *  Rotation factors used in this program
 */

UINT Texture;
	GLUquadricObj *quadratic;
  	GLfloat x,y;
	char *filename = "stonewall1.bmp";

void pillar(){
// quadricOBJ , base radius , top radius , height , slices , stacks
		gluCylinder(quadratic,80.0f,80.0f,200.0f,100,1);// base cylinder

		glPushMatrix();
		glTranslatef(0,0,200);
			gluCylinder(quadratic,80.0f,110.0f,50.0f,100,1);	// cone above 
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0,0,250);
		gluCylinder(quadratic,110.0f,110.0f,50.0f,100,1); // cylinder above the cone
		glPopMatrix();

		//glPushMatrix();
		


		for(float i=0; i<2*(3.1415f); i+=(3.1415f)/4.0f){  //small cylinders which are above the pillars 
			glPushMatrix();

			glTranslatef(110.0f*cos(i),110.0f*sin(i),300-15);

			gluCylinder(quadratic,6.0f,6.0f,30.0f,100,1);

			glPopMatrix();
		}	
}
/*..................................Function for making wall by using cube.....................*/
void cube(){
		glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
	glEnd();

}
/*............................Function for making wall..................................*/
void wall(bool enableBigPillar){ // For when the big  pillars are not made
	if(enableBigPillar){
		glPushMatrix();
		glTranslatef(350,0,0);
			pillar();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(-350,0,0);
			pillar();
		glPopMatrix();
	}

		glPushMatrix(); //for making small pillar of right side 
		glTranslatef(120,0,0);
		glScalef(.5,.5,.7);
		pillar();
		glPopMatrix();

		glPushMatrix();   //For making big pillar of left side
		glTranslatef(-120,0,0);
		glScalef(.5,.5,.7);
		pillar();
		glPopMatrix();

		glPushMatrix();			//For making smallest pillar of the rigkt side
		glTranslatef(0,0,50);
		glScalef(80,20,50);
		cube();
		glPopMatrix();

		glPushMatrix();			//For making smallest pillar of left side
		glTranslatef(215,0,70);
		glScalef(55,20,70);
		cube();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-215,0,70);
		glScalef(55,20,70);
		cube();
		glPopMatrix();
}

void castle(){						//For making whole castle
		
	glPushMatrix();
		glTranslatef(0,350,0);
		wall(true);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,-350,0);
		wall(true);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(350,0,0);
		glRotatef(90.0f , 0,0,1);
		wall(false);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-350,0,0);
		glRotatef(90.0f , 0,0,1);
		wall(false);
	glPopMatrix();	
}

void RenderScene(){
	// Clear the window with current clearing color
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(quadratic,GL_TRUE);
	
glBindTexture(GL_TEXTURE_2D, Texture);

	glPushMatrix();


		glColor3ub(255,255,255);
		castle();	//outer castle

		glColor3ub(155,155,155);
		glPushMatrix();
			glScalef(.5,.5,1.5);
			castle();	//inner castle
		glPopMatrix();
	
		glColor3ub(255,255,255);
		for(float i=0; i<=2*(3.1415f); i+=(3.1415f)/4.0f){ //For making small pillars in the middle or the origin
					
					x = 100*cos(i);
					y = 100*sin(i);
					
					glPushMatrix();
					glTranslatef(x,y,0);
					gluCylinder(quadratic,5,5,350,34,1);
					glPopMatrix();
					

		}

				glPushMatrix();			//For the making disk above the middle of the pillars 
					glTranslatef(0,0,350);
					gluDisk(quadratic,0,100,36,1);
				glPopMatrix();
				
				//obj,base rad,top rad,height, slices,stacks

				glPushMatrix();			//for making a small cylinder above the disk.
					glTranslatef(0,0,350);
					gluCylinder(quadratic,100,100,30,36,1);
				glPopMatrix();

				glPushMatrix();			//For making Disk above the small cylinder
					glTranslatef(0,0,380);
					gluDisk(quadratic , 0 , 100 , 36 , 1);
				glPopMatrix();

				glColor3ub(180,180,180);
				glPushMatrix();			//For making a canon i have made a cone above the disk.
					glTranslatef(0,0,380);
					//glRotatef(0,0,1,0);
					gluCylinder(quadratic,40.0f,0.0f,30,30,1);
				glPopMatrix();
			
				glPushMatrix();			//For making a sphere above the Cone
					glTranslatef(0,0,440);
					gluSphere(quadratic,30,100,100);
				glPopMatrix();
				
				glPushMatrix(); // For making cylinder above the sphere
				glTranslatef(0,0,440);
				glRotatef(30, 0.0f, 1.0f, 0.0f);
				glRotatef(30, 0.0f, 0.0f, 1.0f);
				gluCylinder(quadratic,30,20,80,38,1);
				glPopMatrix();
		glPopMatrix();

	glPopMatrix();
}

void loadTextureFromFile(char *filename)
{    
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	RgbImage theTexMap( filename );
	
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);

	// Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3,theTexMap.GetNumCols(), theTexMap.GetNumRows(),
					 GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );

}

void Setup_castle(){
	quadratic=gluNewQuadric();
	loadTextureFromFile( filename );

	/*
	 * For Light source position
	 * and the light spot direction
	 */
	GLfloat	 lightPos1[] = { 0.0f, 0.0f, 1000.0f, 0.0f };	
	// Light values
	// Bright white light
	GLfloat ambientLight[] = { 1, 1, 1, 1.0f };
	GLfloat diffuseLight[] = { .9, .9, .35, 1.0f };
	
	/*
	 * For shiny castle
	 */
	 
	GLfloat  specular[] = { 1.0f, .5f, 0.2f, 1.0f};
	GLfloat  specref[] =  { 0.5f, 0.0f, 0.0f, 1.0f };

	
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	//glEnable(GL_CULL_FACE);		// Do not calculate inside of jet
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out

	// Lighting stuff
	//glEnable(GL_LIGHTING);			// Enable lighting	
   //glDisable(GL_LIGHT1);
   // Setup and enable light 1
	glLightfv(GL_LIGHT1,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT1,GL_SPECULAR,specular);
	glLightfv(GL_LIGHT1,GL_POSITION,lightPos1);
	//glEnable(GL_LIGHT1);
	glDisable(GL_LIGHT1);
	

	// Enable color tracking
/*	glEnable(GL_COLOR_MATERIAL);
	
	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

   // All materials hereafter have full specular reflectivity
	// with a high shine
	glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
//	glMateriali(GL_FRONT,GL_SHININESS,100);

*/
	glClearColor(0.2f,0.2f,0.2f,1.0f);
	
}

/*
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
	}
*/
/* 
 * Function for maintaining the aspect ratios
 * when the width and height of the board is varied
 * it also implements the perspective view
 */
/*
void ChangeSize(int w,int h) {
	
	GLfloat faspect;
	
	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
   glViewport(0,0,w,h);
	faspect=(GLfloat)w/(GLfloat)h;
	// Reset projection matrix stack
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish perspection
		gluPerspective(70.0,faspect,1.0,1800.0);
   
	// Reset Model view matrix stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0,0.0,-1000.0);
}
*/
/*
 * Read a texture map from a BMP bitmap file.
 */



// main function
/*void main(){
	// Intiating the display mode with double buffer and RGB color mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// Setting the window initial position
	glutInitWindowPosition( 10, 60 );
	// setting the size of the window
    glutInitWindowSize( 620, 620 );
    //Create the window
	glutCreateWindow("CASTLE");
    // Loading the texture file
	loadTextureFromFile( filename );
    /*
	 * Display function
	 * then Reshape function
	 * then timer function
	 
	glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
	//glutTimerFunc(100,TimerFunction,1);
	glutSpecialFunc(SpecialKeys);

	SetupRC();

	glutMainLoop();
}*/