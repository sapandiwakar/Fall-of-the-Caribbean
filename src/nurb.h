#include<iostream>
#include<gl/Glut.h>
#include<gl\glaux.h>
#include "tree.h"

using namespace std;

GLfloat Knots[8] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat ctrlPoints[4][4][3]= {{{ -12.0f, -14.0f, 0.0f}, // u = 0, v = 0
                              { -14.0f, -2.0f, 2.0f}, // v = 1
                              { -14.0f, 2.0f, 2.0f}, // v = 2
                              { -12.0f, 14.0f, 0.0f}},// v = 3
                              
                              {{ -2.0f, -10.0f, 0.0f}, // u = 1 v = 0
                              { -2.0f, -2.0f, 10.0f}, // v = 1
                              { -2.0f, 2.0f, 10.0f}, // v = 2
                              { -2.0f, 10.0f, 0.0f}}, // v = 3
                              
                              {{ 2.0f, -10.0f, 0.0f }, // u =2 v = 0
                              { 2.0f, -2.0f, 8.0f }, // v = 1
                              { 2.0f, 2.0f, 8.0f }, // v = 2
                              { 2.0f, 10.0f, 0.0f }}, // v = 3
                              
                              {{ 12.0f, -14.0f, 0.0f}, // u = 3 v = 0
                              { 18.0f, -2.0f, 3.0f}, // v = 1
                              { 14.0f, 2.0f, 3.0f}, // v = 2
                              { 12.0f, 14.0f, 0.0f}}}; // v = 3


int numPoints= 4;

GLUnurbsObj  *Nurb;

void Islandinit()
{

  	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   //Realy Nice perspective calculations

	Nurb = gluNewNurbsRenderer();
	
	if(!Load_Texture(texture2[1],"2.bmp")) {
		cout <<"\nSurabhi";

	}

	if(!Load_Texture(texture2[0],"10.bmp")) {
		cout <<"\nSurabhi";

	}

	if(!Load_Texture(texture2[2],"hi.bmp")) {
		cout <<"\nSurabhi";

	}
  // setup nurb drawing properties
 	
  	gluNurbsProperty(Nurb, GLU_SAMPLING_TOLERANCE, 40.0);   // Quality - Specifies the maximum length, in pixels, to use
  	gluNurbsProperty(Nurb, GLU_DISPLAY_MODE, GLU_FILL);  

	quadratic1=gluNewQuadric();                  // Create A Pointer To The Quadric Object ( NEW 
    gluQuadricNormals(quadratic1, GLU_SMOOTH);   // Create Smooth Normals
    gluQuadricTexture(quadratic1, GL_TRUE);      // Create Texture Coords ( NEW )
  
    
}


void island(GLfloat island[4][4][3])
{
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	gluBeginSurface(Nurb);
      gluNurbsSurface(Nurb,
          8,Knots,               // No. of knots and knot array u direction
          8,Knots,               // No. of knots and knot array v direction
          4 * 3,                  // Distance between control points in u dir.
          3, 
          &island[0][0][0],                     // Distance between control points in v dir.              						
          4, 4,                   // u and v order of surface
          GL_MAP2_VERTEX_3); 
		  glEnable(GL_TEXTURE_2D);
		  glEnable(GL_MAP2_TEXTURE_COORD_2);
// Type of surface
    gluEndSurface(Nurb);
	double texCtlPts[2][2][2] =
/* (i,j)=(0,0) (i,j)=(0,1) */
							{ { { 0, 0 }, { 0, .1 } },
/* (i,j)=(1,0) (i,j)=(1,1) */
							{ { .1, 0 }, { .1, .1 } }};

		glMap2d(GL_MAP2_TEXTURE_COORD_2,
		0.0, 1.0, // the u limits	
		4, 2, // ustride and uorder=2
		0.0, 1.0, // the v limits
		2, 2, // vstride and vorder=2
		&texCtlPts[0][0][0]);
		glDisable(GL_TEXTURE_2D);
    
    
    
}

void displayIsland()
{
	
	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture2[0]);
		glScalef(30,30,30);

		
		glPushMatrix();	
	
			glColor3f(1,1,1);
			glTranslatef(0.0,0.0,-15);
		
			island(ctrlPoints);
		
		glPopMatrix();
	
	glPopMatrix();

	
}
