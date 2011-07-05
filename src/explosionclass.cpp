#include "explosionclass.h"
#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>

CExplosion :: CExplosion (int a, int b, int c)
{
	x = a;
	y = b;
	z = c;
	angle = 0.0;
	fuel = 5;
	int    i;

  for (i = 0; i < NUM_PARTICLES; i++)
    {
      particles[i].position[0] = 0.0;
      particles[i].position[1] = 0.0;
      particles[i].position[2] = 0.0;

      particles[i].color[0] = 1.0;
      particles[i].color[1] = 1.0;
      particles[i].color[2] = 0.5;

      newSpeed (particles[i].speed);
    }

  for (i = 0; i < NUM_p2; i++)
    {
      p2[i].position[0] = 0.0;
      p2[i].position[1] = 0.0;
      p2[i].position[2] = 0.0;

      p2[i].orientation[0] = 0.0;
      p2[i].orientation[1] = 0.0;
      p2[i].orientation[2] = 0.0;

      p2[i].color[0] = 103/256.0;
      p2[i].color[1] = 93/256.0;
      p2[i].color[2] = 34/256.0;

      p2[i].scale[0] = (5.0 * 
			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
      p2[i].scale[1] = (5.0 * 
			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
      p2[i].scale[2] = (5.0 * 
			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

      newSpeed (p2[i].speed);
      newSpeed (p2[i].orientationSpeed);
    }
}

CExplosion :: ~CExplosion()
{
}
void CExplosion :: display_explosion()
{
  int    i;
  glTranslatef (0.0, 0.0, -10.0);
  
  if (fuel > 0)
    {
      glPushMatrix ();

      glDisable (GL_LIGHTING);
      glDisable (GL_DEPTH_TEST);

      glBegin (GL_POINTS);

      for (i = 0; i < NUM_PARTICLES; i++)
	{
	  glColor3fv (particles[i].color);
	  glVertex3fv (particles[i].position);
	}
  
      glEnd ();

      glPopMatrix ();

      glEnable (GL_DEPTH_TEST);

      glNormal3f (0.0, 0.0, 1.0);

      for (i = 0; i < NUM_p2; i++)
	{
	  glColor3fv (p2[i].color);

	  glPushMatrix ();
      
	  glTranslatef (p2[i].position[0],
			p2[i].position[1],
			p2[i].position[2]);

	  glRotatef (p2[i].orientation[0], 1.0, 0.0, 0.0);
	  glRotatef (p2[i].orientation[1], 0.0, 1.0, 0.0);
	  glRotatef (p2[i].orientation[2], 0.0, 0.0, 1.0);

	  glScalef (p2[i].scale[0],
		    p2[i].scale[1],
		    p2[i].scale[2]);

	  glBegin (GL_TRIANGLES);
	  glVertex3f (0.0, 0.5, 0.0);
	  glVertex3f (-0.25, 0.0, 0.0);
	  glVertex3f (0.25, 0.0, 0.0);
	  glEnd ();
	  glPopMatrix ();
	}
    }

  //glutSwapBuffers ();
}


void CExplosion :: newSpeed (float dest[3])
{
  float    x;
  float    y;
  float    z;
  float    len;

  x = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  y = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  z = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

  dest[0] = x;
  dest[1] = y;
  dest[2] = z;
}


void CExplosion :: continue_explosion()
{
	int i = 0;
    if (fuel > 0)
		{
		  for (i = 0; i < NUM_PARTICLES; i++)
			{
			  particles[i].position[0] += particles[i].speed[0]*5;
			  particles[i].position[1] += particles[i].speed[1]*5;// * 0.5;
			  particles[i].position[2] += particles[i].speed[2]*5;// * 0.5;
		      
			  particles[i].color[0] -= 1.0 / 200.0;
			  if (particles[i].color[0] < 0.0)
			{
			  particles[i].color[0] = 0.0;
			}
		      
			  particles[i].color[1] -= 1.0 / 100.0;
			  if (particles[i].color[1] < 0.0)
			{
			  particles[i].color[1] = 0.0;
			}
		      
			  particles[i].color[2] -= 1.0 / 50.0;
			  if (particles[i].color[2] < 0.0)
			{
			  particles[i].color[2] = 0.0;
			}
			}
		  
		  for (i = 0; i < NUM_p2; i++)
			{
			  p2[i].position[0] += p2[i].speed[0]*2.5;// * 0.25;
			  p2[i].position[1] += p2[i].speed[1]*2.5;// * 0.25;
			  p2[i].position[2] += p2[i].speed[2]*2.5;// * 0.25;
		      
			  p2[i].orientation[0] += p2[i].orientationSpeed[0]*20;// * 20;
			  p2[i].orientation[1] += p2[i].orientationSpeed[1]*20;// * 20;
			  p2[i].orientation[2] += p2[i].orientationSpeed[2]*20;// * 20;
			}
		  
		  --fuel;
		}
	      
		  angle += 0.3; 
		  display_explosion();
}

