#include <stdio.h>			// Header File For Standard I/O Functions
#include <stdlib.h>			// Header File For Standard C Library Functions
#include <string>			// Header File For String
#include <vector>			// Header File For Vector
#include <math.h>			// Header File For Standard Mathematical Functions
#include <time.h>			// Header File For Time
#include <GL\glut.h>		// Header File For The OpenGL Functions
#include "ship.h"			// Header File For Ship
#include "castle.h"			// Header File For Castle
#include "nurb.h"			// Header File For Island
#include "words.h"			// Header File For Wordlist
#include "explosionclass.h"	// Header File For Explosion

#define WATERSIZE 600		// Defines size of water
#define DAMP 50				// Defines damping factor for water

/*
 * Structure for Storing information about ship
 * @x : x co-ordinate of ship
 * @y : y co-ordinate of ship
 * @z : z co-ordinate of ship
 * @word : Word to be displayed on top of ship
 * @destroy : True, if word is found
			  False, otherwise
 * @timedestroy : time taken by ball to destroy the ship/
 */
struct ship {
	string word;
	float x;
	float y;
	float z;
	bool destroy;
	float timedestroy;
};

/*
 * Structure for Storing information about ball
 * @x : x co-ordinate of ball
 * @y : y co-ordinate of ball
 * @z : z co-ordinate of ball
 * @vx : Velocity of ball in x direction
 * @vy : Velocity of ball in y direction
 * @vz : Velocity of ball in z direction
 * @t : time taken by ball to destroy the ship
 */
struct ball {
	float x;
	float y;
	float z;
	float vx;
	float vy;
	float vz;
	float t;
};

float xi = 0;					// Initial x co-ordinate of ball
float yi = 50;					// Initial y co-ordinate of ball
float zi = 800;					// Initial z co-ordinate of ball

vector <ship> boat;				// Vector to store information of all Ships
vector <ball> cannonballs;		// Vector to store information of all Balls
vector <CExplosion> explosions; // Vector to store information of all Explosion

ship temp;						// Temporary object of Ship
ball tempb;						// Temporary object of Ball

float water[2][WATERSIZE][WATERSIZE];		// Arrays to store current and previous/new wavemap for water
GLfloat mat_specular[] = { 250/256.0, 227/256.0, 67/256.0, 1.0};	// Color of Specular component of light
GLfloat position[] = { 0.0, 1050.0, 600, 1.0 };						// Position of light
int h, w;															// height, width  of window
int t = 0, f = 1;													// Refer to current and previous/new wavemap of water
int x1 = 2;															// Represents the speed of ship

GLfloat norm[3];													// Array for storing normals to water surface(Made using Triangles)
bool light;															// Gives information about lightning in cloud
GLuint	texture[2];													// Variable to store loaded Texture
string word = "";													// Variable to sore typed word
int score = 0;														// Variable to store score
int wrong = 0;
bool start = false;													// Represents whether the game has started
bool wrongtyped = true;

void init();														// Stores commands for initialising the window
AUX_RGBImageRec * LoadBMP(char *Filename);							// Function for Loading BMP Image
int LoadGLTextures();												// Function to Load Texture
void calcwater();													// Function to calculate wavemap for water
void reshape(int width, int height);								// Function for resizing the window
void normals(float, float, float, float,float,float, float, float, float); // Function to calculate the normals to water surface
void display(void);													// Function to display the scene
void idle(void);													// Function to update the scene continuously
void bail(int code);												// Function to exit the game
void search(string word);											// Function to search for the typed word
void keyboard(unsigned char key, int x, int y);						// Function to handle keyboard input
void mainpage();


int main(int argc, char** argv)
{
	srand (time (NULL));			// Seed the rand() function with system time

	/* 
	 * Sets the initial display mode.
	 * GLUT_DOUBLE : Bit mask to select a double buffered window
	 * GLUT_RGB : Selects the RGB color model
	 * GLUT_DEPTH : Bit mask to select a window with a depth buffer
	 */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	
    glutInitWindowPosition(50, 50);		// Sets the Initial window position
    glutInitWindowSize(1024,1024) ;		// Sets the Initial window position
    glutInit(&argc, argv);				// Initialize the GLUT library

    glutCreateWindow("The Fall Of Caribbean");		// Create window with the name "The Fall Of Caribbean"
	glutFullScreen();
    glutDisplayFunc(display);						// Sets the display callback for the current window
    glutReshapeFunc(reshape);						// Sets the reshape callback for the current window
    glutKeyboardFunc(keyboard);						// Sets the keyboard callback for the current window
    glEnable (GL_DEPTH_TEST);						// Do depth comparisons and update the depth buffer
	
	init();											// Initialize Our Newly Created GL Window

    glutIdleFunc(idle);								// Sets the global idle callback
    glutMainLoop();									// Enters the GLUT event processing loop
    return 0;
}

/* 
 * Function to load a Bitmap Image
 */
AUX_RGBImageRec * LoadBMP(char *Filename)				
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=fopen(Filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}

/*
 * Function to Load Bitmaps And Convert To Textures
 */
int LoadGLTextures()									 
{
	int Status=FALSE;									// Status Indicator

	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

	memset(TextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0]=LoadBMP("data/cloudy_sky.bmp"))
	{
		Status=TRUE;	// Set The Status To TRUE

		glGenTextures(1, &texture[0]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}

	if (TextureImage[0]=LoadBMP("main.bmp"))
	{
		Status=TRUE;	// Set The Status To TRUE

		glGenTextures(1, &texture[1]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
 
	if (TextureImage[0])									 // If Texture Exists
	{
		if (TextureImage[0]->data)							 // If Texture Image Exists
		{
			free(TextureImage[0]->data);					 // Free The Texture Image Memory
		}

		free(TextureImage[0]);								 // Free The Image Structure
	}

	return Status;										     // Return The Status
} 

/* 
 * Function to update wavemap for water
 */
void calcwater()
{
	int x, y;
    float n;
    
	/*
	 * Calculating the amplitude at each point by taking average of amplitudes of surroundings and then subtract the value at our working position from previous wavemap
	   and them apply Damping
	 */

	for(y = 1; y < WATERSIZE-1; y++) {
		for(x = 1; x < WATERSIZE-1; x++) {
			n = (water[t][x-1][y] + water[t][x+1][y] + water[t][x][y-1] + water[t][x][y+1]) / 2;
            n -= water[f][x][y];
            n = n - (n / DAMP);
            water[f][x][y] = n;
        }
	}
	/*
	 * Calculating wavemap for the lower edge of water
	 */
    y = 0;
    for(x = 1; x < WATERSIZE-1; x++) {
		n = (water[t][x-1][y] + water[t][x+1][y] + water[t][x][y+1]) /2;
		n -= water[f][x][y];	
		n = n - (n / DAMP);
		water[f][x][y] = n;
	}
	
	/*
	 * Calculating wavemap for the left edge of water
	 */
	x = 0;
	for(y = 1; y < WATERSIZE-1; y++) {
		n = (water[t][x+1][y] + water[t][x][y-1] + water[t][x][y+1]) /2;
		n -= water[f][x][y];
		n = n - (n / DAMP);
		water[f][x][y] = n;
	}

	/*
	 * Calculating wavemap for the right edge of water
	 */
	x = WATERSIZE-1;
	for(y = 1; y < WATERSIZE-1; y++) {
		n = (water[t][x-1][y] + water[t][x][y-1] + water[t][x][y+1]) /2;
		n -= water[f][x][y];
		n = n - (n / DAMP);
		water[f][x][y] = n;
	}

	/*
	 * Calculating wavemap for the upper edge of water
	 */
	y = WATERSIZE-1;
	for(x = 1; x < WATERSIZE-1; x++) {
		n = (water[t][x-1][y] + water[t][x+1][y] + water[t][x][y-1]) /2;
		n -= water[f][x][y];
		n = n - (n / DAMP);
		water[f][x][y] = n;
	}
} 
/*
 * Function to be executed while resizing the window
 */
void reshape(int width, int height)
{
    w = width;
    h = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, (GLfloat) w/(GLfloat) h, 1.0, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
	glTranslatef(0.0,0.0,-1000.0);
}


/*
 * Function to calculate normals to surface of water
 * @x1 : x co-ordinate of 1st vertex
 * @y1 : y co-ordinate of 1st vertex
 * @z1 : z co-ordinate of 1st vertex
 * @x2 : x co-ordinate of 2nd vertex
 * @y2 : y co-ordinate of 2nd vertex
 * @z2 : z co-ordinate of 2nd vertex
 * @x3 : x co-ordinate of 3rd vertex
 * @y3 : y co-ordinate of 3rd vertex
 * @z3 : z co-ordinate of 3rd vertex
 */
void normals(float x1, float y1,float  z1, float x2,float  y2,float  z2, float x3,float  y3,float  z3) {
        /* calculate [1 - 2]x[2 - 3] -- the surface normals for a triangle */
                float v1[3], v2[3];
                float dist;

                /* vector1 - vector2 */
                v1[0] = x1 - x2;
                v1[1] = y1 - y2;
                v1[2] = z1 - z2;

                /* vector2 - vector3 */
                v2[0] = x2 - x3;
                v2[1] = y2 - y3;
                v2[2] = z2 - z3;

                /* now the cross product */
                norm[0] = v1[1]*v2[2] - v1[2]*v2[1];
                norm[1] = v1[2]*v2[0] - v1[0]*v2[2];
                norm[2] = v1[0]*v2[1] - v1[1]*v2[0];


                dist = sqrt(norm[0]*norm[0] + norm[1]*norm[1] + norm[2]*norm[2]);

                norm[0] /= dist;		// Now normalize the normal
                norm[1] /= dist;		// Now normalize the normal
                norm[2] /= dist;		// Now normalize the normal
}


/*
 * Function to display the scene on the screen
 */
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);						// Clear the Buffer
	glLightfv (GL_LIGHT0, GL_POSITION, position);							// Set Position of Light
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);						// Set Specular component of Light
	
	if (!start) {
		glPushMatrix();
		glTranslatef(0,0,800);
		mainpage();															// Display the front page
		glPopMatrix();
		glutSwapBuffers();
	} else {
		int i, j, tmp;
        float w = WATERSIZE/2;       
				
		glEnable(GL_LIGHT0);
        glPushMatrix();
		glEnable (GL_LIGHTING);
		glTranslatef(0,0,800);
        glRotatef(-60, 1, 0, 0);

        calcwater();														// Update the wavemap
        glColor3f(0.0f, 1.0f, 1.0f);

		/*
		 * Display the water using triangles
		 */
        glBegin(GL_TRIANGLES);
        for(i = 0; i < WATERSIZE-1; i++) {
                for(j = 0; j < WATERSIZE-1; j++) {
                        normals(j-w, i-w, water[t][j][i],j+1-w, i-w, water[t][j+1][i],j+1-w, i+1-w, water[t][j+1][i+1]);
                        glNormal3fv(norm);
                        glVertex3f(j-WATERSIZE/2, i-WATERSIZE/2, water[t][j][i]);
                        glVertex3f(j+1-WATERSIZE/2, i-WATERSIZE/2, water[t][j+1][i]);
                        glVertex3f(j+1-WATERSIZE/2, i+1-WATERSIZE/2, water[t][j+1][i+1]);

                        normals(j-w, i+1-w, water[t][j][i+1],
                                        j-w, i-w, water[t][j][i],
                                        j+1-w, i+1-w, water[t][j+1][i+1]);
                        glNormal3fv(norm);
                        glVertex3f(j-WATERSIZE/2, i+1-WATERSIZE/2, water[t][j][i+1]);
                        glVertex3f(j-WATERSIZE/2, i-WATERSIZE/2, water[t][j][i]);
                        glVertex3f(j+1-WATERSIZE/2, i+1-WATERSIZE/2, water[t][j+1][i+1]);

                        
                }
        }
        glEnd();
        
        tmp = t; t = f; f = tmp;					// Swap the wavemaps
		
		/*
		 * For creating thundering effect
		 */
		glPushMatrix();
		if (light) {
			glColor3f(1,1,1);
		} else {
			glColor3f(0.3,0.3,0.3);
		}
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTranslatef(0,1000,0);
		glScalef(1050,200,200 );
		glRotatef(60, 1, 0, 0);
		/*
		 * Make a texture mapped sky
		 */
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1,-1, 0);
		glTexCoord2f(1, 0);
		glVertex3f(1,-1, 0);
		glTexCoord2f(1, 1);
		glVertex3f(1,1, 0);
		glTexCoord2f(0, 1);
		glVertex3f(-1,1 , 0);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glPopMatrix();
		
		/*
		 * Dsiplay an Island in the middle of sea
		 */
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glTranslatef(0,36,832);
		glRotatef(-60,1,0,0);
		glScalef(.11,.12,.11);
		
		displayIsland();
		
		glEnable(GL_LIGHTING);
		glPopMatrix();

		/*
		 * Display tree n the island
		 */
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-33,-15,868);
		glRotatef(-20,1,0,0);
		glRotatef(20,0,0,1);
		glScalef(0.55,0.55,0.55);
		displaytree();
		glEnable(GL_LIGHTING);
		glPopMatrix();

		/*
		 * Display tree on the island
		 */
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(37,-15,868);
		glRotatef(-20,1,0,0);
		glRotatef(-15,0,0,1);
		glScalef(0.55,0.55,0.55);
		displaytree();
		glEnable(GL_LIGHTING);
		glPopMatrix();
		
		/* 
		 * Display castle on the island
		 */
		glPushMatrix();
		glDisable(GL_BLEND);
		glTranslatef(0,0,826);
		glRotatef(-60, 1, 0, 0);
		glScalef(.080,.080,.080);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
		
		RenderScene();
		
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_BLEND);
    	glPopMatrix();

		/*
		 * Display the ships
		 */
		glPushMatrix();
		glTranslatef(-1000,-1000,-1000);
		display_ship("TEMP");
		glPopMatrix();
		for (int i = 0; i < boat.size(); i ++) {
			glPushMatrix();
			glDisable(GL_BLEND);
			glDisable(GL_LIGHTING);
			boat[i].x -= x1;												// Decrease the x coordinate to move the ship
			glTranslatef(boat[i].x,boat[i].y ,boat[i].z );
			glRotatef(30,1,0,0);
			glScalef(0.03 ,0.03,0.03);
			display_ship(boat[i].word);										// Display ship
			if ((boat[i].z < 900) && (boat[i].z > (900 - 12*1.732))) {
				if (boat[i].x <= -90 ) {
					boat.erase(boat.begin()+i);								// Erase the ship if it crosses the boundary
				}
			} else {
				if (boat[i].x <= -250)
					boat.erase(boat.begin()+i);								// Erase the ship if it crosses the boundary
			}

			if (boat[i].destroy) {
				boat[i].timedestroy += 0.3;									// Increase the time 
			}
			if (boat[i].timedestroy >= 5.2) {								
				CExplosion tempe(boat[i].x, boat[i].y, boat[i].z);			// Start the explosion when the ball reaches the boat
				explosions.push_back(tempe);
				boat.erase(boat.begin()+i);									// Erase the boat
				PlaySound("Data/missile.wav",NULL,SND_FILENAME|SND_ASYNC);	// Play sound for explosion
				score++;													//Increase the score
				
			}
			glEnable(GL_BLEND);
			glEnable(GL_LIGHTING);
			glPopMatrix();
		}

		for (int i = 0; i < explosions.size(); i ++) {
			glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(explosions[i].x, explosions[i].y, explosions[i].z);
			explosions[i].continue_explosion();
			glEnable(GL_LIGHTING);
			glPopMatrix();
			if (explosions[i].fuel <= 0) {
				explosions.erase(explosions.begin() + i);
			}
		}

		for (int i = 0; i < cannonballs.size(); i ++) {
			glPushMatrix();
			glDisable(GL_BLEND);
			cannonballs[i].x = xi + cannonballs[i].vx*cannonballs[i].t ;
			cannonballs[i].y = yi + cannonballs[i].vy*cannonballs[i].t - 0.5*9.8*cannonballs[i].t*cannonballs[i].t ;
			cannonballs[i].z = zi + cannonballs[i].vz*cannonballs[i].t ;
			cannonballs[i].t += 0.3;
			glPushMatrix();
			glTranslatef(cannonballs[i].x,cannonballs[i].y,cannonballs[i].z);
			glutSolidSphere (3, 35, 28);
			if (cannonballs[i].t >= 5.2) {
				cannonballs.erase (cannonballs.begin () + i);
			}
			glEnable(GL_BLEND);
			glEnable(GL_LIGHTING);
			glPopMatrix();
		}

		glPushMatrix();
		char score_ch[10];
		itoa(score, score_ch, 10);
		glPushMatrix();
		glTranslatef(-73,-45.5,900);
		glDisable(GL_LIGHTING);
		glDisable(GL_BLEND);
		glColor3f(0,1,0);
		glScalef(2.2,2,1);
		glBegin(GL_QUADS);
		//glTexCoord2f(0,0);
		glVertex3f(-1,-1,0);
		//glTexCoord2f(0,1);
		glVertex3f(-1,1,0);
		//glTexCoord2f(1,1);
		glVertex3f(1,1,0);
		//glTexCoord2f(0,-1);
		glVertex3f(1,-1,0);
		glEnd();
		glEnable(GL_BLEND);
		glPopMatrix();
		glTranslatef(-59,-37,920);
		glutPrint(0.0f,0.0f, glutFonts[0], score_ch, 1,1,1, 1.0f);
		glPopMatrix();

		glPushMatrix();
		char wrong_ch[10];
		itoa(wrong, wrong_ch, 10);
		glPushMatrix();
		glTranslatef(-65,-45.5,900);
		glDisable(GL_LIGHTING);
		glDisable(GL_BLEND);
		glColor3f(1,0,0);
		glScalef(2.2,2,1);
		glBegin(GL_QUADS);
		//glTexCoord2f(0,0);
		glVertex3f(-1,-1,0);
		//glTexCoord2f(0,1);
		glVertex3f(-1,1,0);
		//glTexCoord2f(1,1);
		glVertex3f(1,1,0);
		//glTexCoord2f(0,-1);
		glVertex3f(1,-1,0);
		glEnd();
		glEnable(GL_BLEND);
		glPopMatrix();
		glTranslatef(-53,-37,920);
		glutPrint(0.0f,0.0f, glutFonts[0], wrong_ch, 1,1,1, 1.0f);
		glPopMatrix();
	
		glPushMatrix();
		int m;
		char wordc[30];
	for (  m = 0; m < word.size(); m ++ ) {
		wordc[m] = word[m];
	}
	wordc[m] = '\0';
		glDisable(GL_LIGHTING);
		glDisable(GL_BLEND);
		if (wrongtyped) {
			glColor3f(1,0,0);
		} else {
			glColor3f(0,1,0);
		}
		glPushMatrix();
		glTranslatef(73,-45.5,900);
		glScalef(15,2,1);
		glBegin(GL_QUADS);
		//glTexCoord2f(0,0);
		glVertex3f(-1,-1,0);
		//glTexCoord2f(0,1);
		glVertex3f(-1,1,0);
		//glTexCoord2f(1,1);
		glVertex3f(1,1,0);
		//glTexCoord2f(0,-1);
		glVertex3f(1,-1,0);
		glEnd();
		glEnable(GL_BLEND);
		glPopMatrix();
		glTranslatef(59.5-word.size()*1.07,-37,920);
		glutPrint(0.0f,0.0f, glutFonts[0],wordc, 1,1,1, 1.0f);
		glPopMatrix();
		glutSwapBuffers();
	}
    
}

int num  = 0;
int delay = 1;							// Delay between water ripples produced
int delay2 = 8;							// Delay between Lightning in clouds
int delay3 = 10;						// Delay between different ships generated

void idle(void)
{
	if (start) {
		if(!(++num %delay)) {
                water[f][rand()%WATERSIZE][rand()%WATERSIZE] = -rand()%10+10;
				if (light) 
					light = false ;
				if (!(num % delay2)) {
					light = rand() % 2;
				}
				
				if (num%delay3 == 0 && boat.size () < 15) {
					int random;
					if ( rand()%2 ) {
						random = 60 + rand()%80;
					} else {
						random = rand()%12;
					}
							
					temp.x = 90 + random*1.732/2;
					temp.y = -20 + random;
					temp.z = 900 - random*1.732 ;
					temp.destroy = false;
					temp.timedestroy = 0;
					temp.word = wordlist[rand()%wordlist.size()];
					boat.push_back(temp);
					
				}
        }
	}
		
    glutPostRedisplay();
}

void bail(int code)
{
    exit(code);
}

void search(string word)
{
	int i;
	for( i = 0; i < boat.size (); i ++) {
		if (word == boat[i].word && !boat[i].destroy) {
			boat[i].destroy = true;
			

			tempb.x = xi;
			tempb.y = yi;
			tempb.z = zi;
			
			tempb.vx = (boat[i].x - x1*5/0.3 - xi) / 5.0 ;
			tempb.vy = ((boat[i].y - yi) + 1/2.0*9.8*5*5) / 5.0 ;
			tempb.vz = (boat[i].z - zi) / 5.0 ;
			tempb.t = 0;

			PlaySound("Data/Cannon.wav",NULL,SND_FILENAME|SND_ASYNC);
			cannonballs.push_back (tempb);

			break;
		}
	}
	if (i == boat.size()) {
		wrong++;
	}
}
void keyboard(unsigned char key, int x, int y)
{
    static int old_x = 50;
    static int old_y = 50;
    static int old_width = 512;
    static int old_height = 512;

	if (!start) {
		if (key == 'p' || key == 'P') {
			start = true;
			return;
		}
	}
    switch (key) {
        case 27:
                bail(0);
            break;
        case '1':
                glutPositionWindow(old_x, old_y);
                glutReshapeWindow(old_width, old_height);
            break;
        case '2':
            if (glutGet(GLUT_WINDOW_WIDTH) < glutGet(GLUT_SCREEN_WIDTH)) {
                old_x = glutGet(GLUT_WINDOW_X);
                old_y = glutGet(GLUT_WINDOW_Y);
                old_width = glutGet(GLUT_WINDOW_WIDTH);
                old_height = glutGet(GLUT_WINDOW_HEIGHT);
                glutFullScreen();
            }
            break;
        case ' ':
		case 13:
			search(word);
			word.clear();
			break;
		case 8:
			if (!word.empty ()){
				word.erase(word.end () -1);
			}
			break;
		default:
			if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z')) {
				if (word.size() < 30) {
					word += key;
				}
				break;
			}
    }
	int i;
	for( i = 0; i < boat.size (); i ++) {
		if (word == boat[i].word && !boat[i].destroy) {
			wrongtyped = false;
			break;
		}
	}
	if (i == boat.size()) {
		wrongtyped= true;
	}

}


void init(void) {
        int i, j;
    GLfloat mat_diffuse[] = { 100/255.0, 150/255.0, 255/255.0, 1.0};
   
    GLfloat mat_shininess[] = { 100.0 };

	
    w = glutGet(GLUT_WINDOW_WIDTH);
    h = glutGet(GLUT_WINDOW_HEIGHT);

    glClearColor (0.0, 0.0, 0.0, 0.5);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	//glDisable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);



        for( i = 0; i < WATERSIZE; i++) 
                for( j = 0; j < WATERSIZE; j++) {
                        water[0][j][i] = 0;
                        water[1][j][i] = 0;
                }
	if (!LoadGLTextures())								// Jump To Texture Loading Routine ( NEW )
	{
		return;									// If Texture Didn't Load Return FALSE
	}
	Setup_castle();
	init_ship();
	Islandinit();
	get_wordlist();
}

void mainpage()
{
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTranslatef(0,0,0);
		glScalef(150,95,100);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1,-1, 0);
		glTexCoord2f(1, 0);
		glVertex3f(1,-1, 0);
		glTexCoord2f(1, 1);
		glVertex3f(1,1, 0);
		glTexCoord2f(0, 1);
		glVertex3f(-1,1 , 0);
		glEnd();
		glPopMatrix();
}