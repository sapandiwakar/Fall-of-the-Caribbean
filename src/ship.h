#include<iostream>
#include<gl/Glut.h>
#include<gl\glaux.h>
#include"sail.h"
#include"pole.cpp"
#include"pole2.cpp"
#include"disk.cpp"
#include <string>

using namespace std;

LPVOID glutFonts[1] = {GLUT_BITMAP_TIMES_ROMAN_24};

struct tImage
{
	int channels;
	int sizeX;
	int sizeY;
	unsigned char *data;
};


GLuint	texture1[2];			// Storage For One Texture ( NEW )

tImage *LoadBMP1(const char *strFileName)
{
	AUX_RGBImageRec *pBitmap = NULL;
	FILE *pFile = NULL;
	
	if((pFile = fopen(strFileName, "rb")) == NULL) 
	{
		return NULL;
	}
	
	pBitmap = auxDIBImageLoad(strFileName);				
	
	tImage *pImage = (tImage *)malloc(sizeof(tImage));
	
	pImage->channels = 3;
	pImage->sizeX = pBitmap->sizeX;
	pImage->sizeY = pBitmap->sizeY;
	pImage->data  = pBitmap->data;
	
	free(pBitmap);
	
	return pImage;
}
bool Load_Texture(UINT &texture, LPSTR strFileName)
{
	if(!strFileName)  return false;

	tImage *pImage = NULL;
	
	if(strstr(strFileName, ".bmp"))
	{
		pImage = LoadBMP1(strFileName);
	}
	else	return false;
	
	if(pImage == NULL)	return false;
	
	glGenTextures(1, &texture);
	
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	
	int textureType = GL_RGB;
	
	if(pImage->channels == 4)
		textureType = GL_RGBA;
	
	gluBuild2DMipmaps(GL_TEXTURE_2D, pImage->channels, pImage->sizeX, 
		pImage->sizeY, textureType, GL_UNSIGNED_BYTE, pImage->data);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);							
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	if (pImage)	
	{
		if (pImage->data)	free(pImage->data);		
		free(pImage);
	}
	
	return true;
}




/////////////////////////////////////////////////////////////////////////////////////////////////
//										BMP LOADER
/////////////////////////////////////////////////////////////////////////////////////////////////

void glutPrint(float x, float y, LPVOID font, char* text, float r, float g, float b, float a) 
{ 
    if(!text || !strlen(text)) return; 
    bool blending = false; 
    if(glIsEnabled(GL_BLEND)) blending = true; 
    glEnable(GL_BLEND); 
    glColor4f(r,g,b,a); 
    glRasterPos2f(x,y); 
	while (*text) { 
        glutBitmapCharacter(font, *text); 
        text++; 
    } 
    if(!blending) glDisable(GL_BLEND); 
}

void init_ship()
{

	Load_Texture(texture1[0],"Nehe.bmp");
    Load_Texture(texture1[1],"1062000_skull_pirate_logo.bmp");  
}


void display_ship(string word)
{

	int i;
	char wordc[30];
	for (  i = 0; i < word.size(); i ++ ) {
		wordc[i] = word[i];
	}
	wordc[i] = '\0';

	
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		

		
		glPushMatrix();
		
			
			glScalef(30,30,30);
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, texture1[1]);
				glColor3f(1,1,1);
				GLfloat ctrl_sail1[3][3][3] = {{{ 1.0f, 6.0f, 0.0f},
													{ 1.5f, 0.0f, 0.0f},
													{ 1.0f, 6.0f, 0.0f }},
										
													{{ 1.5f, 3.0f, 0.0f},
													{ 2.0f, 5.0f, 1.0f},
													{ 5.0f, 3.5f, 0.0f }},
										
													{{ 1.0f, 1.0f, 0.0f},
													{ 3.0f, 2.0f, 0.0f},
													{ 6.0f, 1.0f, 0.0f }}};
										
												
												
				sail(ctrl_sail1);
		
			glPopMatrix();	
	
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, texture1[1]);
				glColor3f(1,1,1);
					GLfloat ctrl_sail2[3][3][3] = {{{ 0.5f, 6.0f, 0.0f},
													{ 0.0f, 0.0f, 0.0f},
													{ 0.5f, 6.0f, 0.0f }},
										
													{{ 0.0, 3.0f, 0.0f},
													{ 1.5f, 1.0f, 2.5f},
													{ -3.0f, 2.5, 0.0f }},
										
													{{ 0.5f, -8.0f, 0.0f},
													{ -2.0f, -6.0f, 0.0f},
													{ -7.0f, -8.0f, 0.0f }}};
	
				sail(ctrl_sail2);
		
			glPopMatrix();
	
			glPushMatrix();

				//glEnable(GL_TEXTURE_2D);
				glColor3ub(168,57,30);
				glBindTexture(GL_TEXTURE_2D, texture1[0]);
				GLfloat ctrl_boat1[3][3][3] = {{{ -8.0f, -9.0f, -1.0f},
													{ 1.0f, -11.0f, 2.0f},
													{ 8.0f, -9.0f, -1.0f }},
										
													{{ -9.0f, -11, -1.0f},
													{ -2.0f, -11, 2.0f},
													{ 9.0f, -11, -1.0f }},
										
													{{ -7.0f, -15.0f, -1.0f},
													{ 0.0f, -15.0f, 2.0f},
													{ 7.0f, -15.0f, -1.0f }}};
	
	
	
				sail(ctrl_boat1);

		
				glColor3ub(100,20,10);
				GLfloat ctrl_boat3[3][3][3] = {{{ -8.0f, -9.0f, -1.0f},
													{ 1.0f, -11.0f, -4.0f},
													{ 8.0f, -9.0f, -1.0f }},
										
													{{ -9.0f, -11, -1.0f},
													{ -2.0f, -11, -4.0f},
													{ 9.0f, -11, -1.0f }},
										
													{{ -7.0f, -15.0f, -1.0f},
													{ 0.0f, -15.0f, -4.0f},
													{ 7.0f, -15.0f, -1.0f }}};
	
				sail(ctrl_boat3);
				
						
			glPopMatrix();
	
		
			glPushMatrix();
		
				glColor3f(1,1,1);
					glBindTexture(GL_TEXTURE_2D, texture1[1]);
				GLfloat ctrl_sail4[3][3][3] = {{{ 1.0f, 0.0f, 0.0f},
													{ 1.0f, -2.0f, 2.0f},
													{ 6.0f, 0.0f, 0.0f }},
										
													{{ 2.0f, -4.0f, 0.0f},
													{ 5.0f, -2.0f, -1.0f},
													{ 6.0f, -4.5f, 0.0f }},
										
													{{ 1.0f, -8.0f, 0.0f},
													{ 5.0f, -6.0f, 2.0f},
													{ 7.0f, -8.0f, 0.0f }}};
													
	
				sail(ctrl_sail4);
		
			glPopMatrix();
	
			glPushMatrix();
	
				pole();
                
			glPopMatrix();
			glPushMatrix();
				//glTranslatef(-5.5,-4.5,0);
				pole2();
		
			glPopMatrix();
			
			glPushMatrix();
				
				glColor3ub(80,20,10);
					glBindTexture(GL_TEXTURE_2D, texture1[0]);
				GLfloat ctrl_boat5[3][3][3] = {{{ -8.0f, -9.0f, -1.0f},
													{ 1.0f, -11.0f, -4.0f},
													{ 8.0f, -9.0f, -1.0f }},
													
													{{ -9.0f, -11, -1.0f},
													{ 0.0f, -12, -1},
													{ 9.0f, -11, -1.0f }},
										
													{{ -8.0f, -9.0f, -1.0f},
													{ 1.0f, -11.0f, 2.0f},
													{ 8.0f, -9.0f, -1.0f }}};
				
			
				sail(ctrl_boat5);
			
			glPopMatrix();
			
					
			glPushMatrix();
			
			for ( int i=0; i<4; i++ ){
				glPushMatrix();
				
					glTranslatef(2*i,-11.5+0.1*i,1-0.1*i);
					disk();
			
				glPopMatrix();
				
			}
			for ( int i=0; i<4; i++ ){
				glPushMatrix();
				
					glTranslatef(-2*i,-11.5+0.1*i,1-0.2*i);
					disk();
			
				glPopMatrix();
				
			}
			
			glPopMatrix();
		
		glPopMatrix();
		
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_FRONT);
	glTranslatef(-175, 230, 0);
	glColor3f(0,0,0); 
	glClearColor(0.2,0.2,0.2,1);
	glutPrint(0.0f,0.0f, glutFonts[0], wordc, 1,1,1, 1.0f);
	glEnable(GL_FRONT);
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glPopMatrix();
	
}


