#define NUM_PARTICLES    1000          /* Number of particles  */
#define NUM_p2       70            /* Number of p2     */
//#pragma comment (lib, "winmm.lib") //MCI


#define PAUSE              0
#define NORMALIZE_SPEED    1
#define QUIT               2

struct particleData
{
  float   position[3];
  float   speed[3];
  float   color[3];
};
typedef struct particleData    particleData;


/* A piece of p2 */

struct p2Data
{
  float   position[3];
  float   speed[3];
  float   orientation[3];        /* Rotation angles around x, y, and z axes */
  float   orientationSpeed[3];
  float   color[3];
  float   scale[3];
};
typedef struct p2Data    p2Data;


/* Globals */

particleData     particles[NUM_PARTICLES];
p2Data       p2[NUM_p2];   
int              fuel = 0;                /* "fuel" of the explosion */

float            angle = 0.0;             /* camera rotation angle */


/* Light sources and material */
/*
GLfloat  light0Amb[4] =  { 1.0, 0.6, 0.2, 1.0 };
GLfloat  light0Dif[4] =  { 1.0, 0.6, 0.2, 1.0 };   
GLfloat  light0Spec[4] = { 0.0, 0.0, 0.0, 1.0 };   
GLfloat  light0Pos[4] =  { 0.0, 0.0, 0.0, 1.0 };

GLfloat  light1Amb[4] =  { 0.0, 0.0, 0.0, 1.0 };
GLfloat  light1Dif[4] =  { 1.0, 1.0, 1.0, 1.0 };   
GLfloat  light1Spec[4] = { 1.0, 1.0, 1.0, 1.0 };   
GLfloat  light1Pos[4] =  { 0.0, 5.0, 5.0, 0.0 };

GLfloat  materialAmb[4] = { 0.25, 0.22, 0.26, 1.0 };
GLfloat  materialDif[4] = { 0.63, 0.57, 0.60, 1.0 };
GLfloat  materialSpec[4] = { 0.99, 0.91, 0.81, 1.0 };
GLfloat  materialShininess = 27.8;
*/

int      wantNormalize = 0;   
int      wantPause = 0;       



void display_explosion(int fuel)
{
  int    i;
  glTranslatef (0.0, 0.0, -10.0);
  //glRotatef (angle, 0.0, 1.0, 0.0);

  cout << fuel;
 /* if (fuel == 0)
    {
      glEnable (GL_LIGHTING);
      glDisable (GL_LIGHT0);
      glEnable (GL_DEPTH_TEST);
      glutSolidCube (1.0);
    }*/

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

      glEnable (GL_LIGHTING); 
      glEnable (GL_LIGHT0); 
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


void newSpeed (float dest[3])
{
  float    x;
  float    y;
  float    z;
  float    len;

  x = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  y = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
  z = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

 

  if (wantNormalize)
    {
      len = sqrt (x * x + y * y + z * z);

      if (len)
	{
	  x = x / len;
	  y = y / len;
	  z = z / len;
	}
    }

  dest[0] = x;
  dest[1] = y;
  dest[2] = z;
}

void newExplosion (int fuel)
{
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

      p2[i].color[0] = 0.7;
      p2[i].color[1] = 0.7;
      p2[i].color[2] = 0.7;

      p2[i].scale[0] = (2.0 * 
			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
      p2[i].scale[1] = (2.0 * 
			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
      p2[i].scale[2] = (2.0 * 
			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

      newSpeed (p2[i].speed);
      newSpeed (p2[i].orientationSpeed);
    }
}
void continue_explosion(int fuel)
{
	int i = 0;
  if (fuel > 0)
		{
		  for (i = 0; i < NUM_PARTICLES; i++)
			{
			  particles[i].position[0] += particles[i].speed[0];
			  particles[i].position[1] += particles[i].speed[1];// * 0.5;
			  particles[i].position[2] += particles[i].speed[2];// * 0.5;
		      
			  particles[i].color[0] -= 1.0 / 500.0;
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
			  p2[i].position[0] += p2[i].speed[0];// * 0.25;
			  p2[i].position[1] += p2[i].speed[1];// * 0.25;
			  p2[i].position[2] += p2[i].speed[2];// * 0.25;
		      
			  p2[i].orientation[0] += p2[i].orientationSpeed[0];// * 20;
			  p2[i].orientation[1] += p2[i].orientationSpeed[1];// * 20;
			  p2[i].orientation[2] += p2[i].orientationSpeed[2];// * 20;
			}
		  
		  --fuel;
		}
	      
		  angle += 0.3; 
		  display_explosion(fuel);
}


/*void keyboard (unsigned char key, int x, int y)
{
  switch (key)
    {
    case ' ':
      newExplosion ();
	  PlaySound ("explosion.wav", NULL, SND_SYNC|SND_FILENAME);
      break;

    case 27:
      exit (0);
      break;

    case 'p':
      wantPause = 1 - wantPause;
      break;
    }
}

*//*
void idle (void)
{
  
  glutPostRedisplay ();
}*/
/*
void reshape (int w, int h)
{
  glViewport (0.0, 0.0, (GLfloat) w, (GLfloat) h);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (45.0, (GLfloat) w / (GLfloat) h, 0.1, 100.0);
  
  glMatrixMode (GL_MODELVIEW);
}

void menuSelect (int value)
{
  switch (value)
    {
    case PAUSE:
      wantPause = 1 - wantPause;
      break;

    case NORMALIZE_SPEED:
      wantNormalize = 1 - wantNormalize;
      break;
      
    case QUIT:
      exit (0);
      break;
    }
}


int main (int argc, char *argv[])
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
  
  glutCreateWindow ("Explosion demo");
  //glClearColor ( 1.0, 1.0, 1.0, 0.0 );
 // glutKeyboardFunc (keyboard);
  //glutIdleFunc (idle);
  glutDisplayFunc (newExplosion);
  glutReshapeFunc (reshape);

  srand (time (NULL));

  glEnable (GL_LIGHT0);
  glEnable (GL_LIGHT1);
  glLightfv (GL_LIGHT0, GL_AMBIENT, light0Amb);
  glLightfv (GL_LIGHT0, GL_DIFFUSE, light0Dif);
  glLightfv (GL_LIGHT0, GL_SPECULAR, light0Spec);
  glLightfv (GL_LIGHT0, GL_POSITION, light0Pos);
  glLightfv (GL_LIGHT1, GL_AMBIENT, light1Amb);
  glLightfv (GL_LIGHT1, GL_DIFFUSE, light1Dif);
  glLightfv (GL_LIGHT1, GL_SPECULAR, light1Spec);
  glLightfv (GL_LIGHT1, GL_POSITION, light1Pos);
  glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, materialAmb);
  glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, materialDif);
  glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, materialSpec);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);
  glEnable (GL_NORMALIZE);

  glutCreateMenu (menuSelect);
  glutAddMenuEntry ("Pause", PAUSE);
  glutAddMenuEntry ("Toggle normalized speed vectors", NORMALIZE_SPEED);
  glutAddMenuEntry ("Quit", QUIT);
  glutAttachMenu (GLUT_RIGHT_BUTTON);

  glutMainLoop ();

  return 0;
}*/