#include<iostream>
#include<gl/Glut.h>

using namespace std;

void sail(float ctrl_sail[3][3][3])
{

	
	glMap2f(GL_MAP2_VERTEX_3|GL_MAP2_TEXTURE_COORD_2,	// Type of data generated
		0.0f,						// Lower u range
		10.0f,						// Upper u range
		3,							// Distance between points in the data
		3,							// Dimension in u direction (order)
		0.0f,						// Lover v range
		10.0f,						// Upper v range
		9,							// Distance between points in the data
		3,							// Dimension in v direction (order)
		&ctrl_sail[0][0][0]);		// array of control points
		glEnable(GL_MAP2_VERTEX_3);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_MAP2_TEXTURE_COORD_2);

		glEnable(GL_AUTO_NORMAL);
		
	// Map a grid of 10 points from 0 to 10
		glMapGrid2f(10,0.0f,10.0f,10,0.0f,10.0f);
	// Evaluate the grid, using lines
		glEvalMesh2(GL_FILL,0,10,0,10);

		double texCtlPts[2][2][2] =
/* (i,j)=(0,0) (i,j)=(0,1) */
							{ { { 0, 0 }, { 0, 0.1 } },
/* (i,j)=(1,0) (i,j)=(1,1) */
							{ { 0.1, 0 }, { 0.1, 0.1 } }};

		glMap2d(GL_MAP2_TEXTURE_COORD_2,
		0.0, 1.0, // the u limits	
		4, 2, // ustride and uorder=2
		0.0, 1.0, // the v limits
		2, 2, // vstride and vorder=2
		&texCtlPts[0][0][0]);
		glDisable(GL_TEXTURE_2D);

		
}