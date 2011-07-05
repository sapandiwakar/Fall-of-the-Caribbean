GLuint	texture2[3];			// Storage For One Texture ( NEW )
GLUquadricObj *quadratic1;

void displaytree()
{
	glEnable(GL_TEXTURE_2D);
//	shades();
	//glEnable(GL_LIGHTING);
	
	//glColor3f(1.0f , 0.0f , 0.0f);
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
    
	//LoadGLTextures("1.bmp");

	//glTranslatef( 13 , 0 , 5 );
	
//Trunk

	glScalef(3,3,3);

	glBindTexture(GL_TEXTURE_2D, texture2[1]);
	//glColor3f(0.6,0.4,1.2);
	glTranslatef(0.0f,0.0f,-5.0f);          // move 5 units into the screen. 
    glRotatef(-90.0f,1.0f,0.0f,0.0f);		// Rotate On The X Axis 
	glTranslatef(0.0f,2.0f,-1.5f);	// Center the cylinder
	gluCylinder(quadratic1,0.5f,.5f,3,32,32);

	//left branch

	quadratic1=gluNewQuadric();                  // Create A Pointer To The Quadric Object ( NEW 
    gluQuadricNormals(quadratic1, GLU_SMOOTH);   // Create Smooth Normals
    gluQuadricTexture(quadratic1, GL_TRUE);      // Create Texture Coords ( NEW )
	glTranslatef(0.0f,0.0f,3.0f);
	glRotatef(45.0f,0.0f,1.0f,0.0f);
	gluCylinder(quadratic1,0.3f,.2f,3,32,32);
	
//right branch

	quadratic1=gluNewQuadric();                  // Create A Pointer To The Quadric Object ( NEW 
    gluQuadricNormals(quadratic1, GLU_SMOOTH);   // Create Smooth Normals
    gluQuadricTexture(quadratic1, GL_TRUE);      // Create Texture Coords ( NEW )
	//glTranslatef(0.0f,0.0f,3.0f);
	glRotatef(-90.0f,0.0f,1.0f,0.0f);
	gluCylinder(quadratic1,0.3f,.2f,2,32,32);
	glPopMatrix();
	
	//LoadGLTextures("hi.bmp");
	
	glBindTexture(GL_TEXTURE_2D, texture2[2]);

	glScalef(3,3,3);
	//glTranslatef( 10 , 0 , 5 );
	
	glPushMatrix();
	//glColor3f(0.0,1.0,0.0);
	quadratic1=gluNewQuadric();                  // Create A Pointer To The Quadric Object ( NEW 
    gluQuadricNormals(quadratic1, GLU_SMOOTH);   // Create Smooth Normals
    gluQuadricTexture(quadratic1, GL_TRUE);      // Create Texture Coords ( NEW )
	glTranslatef(2.2f,3.6f,-5.0f);
	glRotatef(-90.0f,0.0f,1.0f,0.0f);
	gluSphere(quadratic1,.8f,25,25);
	glPopMatrix();

	glPushMatrix();
	//	glColor3f(0.0,1.0,0.0);
	quadratic1=gluNewQuadric();                  // Create A Pointer To The Quadric Object ( NEW 
    gluQuadricNormals(quadratic1, GLU_SMOOTH);   // Create Smooth Normals
    gluQuadricTexture(quadratic1, GL_TRUE);      // Create Texture Coords ( NEW )
	glTranslatef(2.5f,2.8f,-5.0f);
	//glRotatef(-45.0f,0.0f,0.0f,1.0f);
	gluSphere(quadratic1,.8f,25,25);
	glPopMatrix();

	glPushMatrix();
	//	glColor3f(0.0,1.0,0.0);
	quadratic1=gluNewQuadric();                  // Create A Pointer To The Quadric Object ( NEW 
    gluQuadricNormals(quadratic1, GLU_SMOOTH);   // Create Smooth Normals
    gluQuadricTexture(quadratic1, GL_TRUE);      // Create Texture Coords ( NEW )
	glTranslatef(0.9f,3.4f,-5.0f);
	//glRotatef(-45.0f,0.0f,0.0f,1.0f);
	gluSphere(quadratic1,.8f,25,25);
	glPopMatrix();

	glPushMatrix();
	//	glColor3f(0.0,1.0,0.0);
	quadratic1=gluNewQuadric();                  // Create A Pointer To The Quadric Object ( NEW 
    gluQuadricNormals(quadratic1, GLU_SMOOTH);   // Create Smooth Normals
    gluQuadricTexture(quadratic1, GL_TRUE);      // Create Texture Coords ( NEW )
	glTranslatef(-0.8f,4.3f,-6.0f);
	//glRotatef(-45.0f,0.0f,0.0f,1.0f);
	gluSphere(quadratic1,1.2f,25,25);
	glPopMatrix();

	glPushMatrix();
	//	glColor3f(0.0,1.0,0.0);
	quadratic1=gluNewQuadric();                  // Create A Pointer To The Quadric Object ( NEW 
    gluQuadricNormals(quadratic1, GLU_SMOOTH);   // Create Smooth Normals
    gluQuadricTexture(quadratic1, GL_TRUE);      // Create Texture Coords ( NEW )
	glTranslatef(0.9f,4.1f,-5.0f);
	//glRotatef(-45.0f,0.0f,0.0f,1.0f);
	gluSphere(quadratic1,.8f,25,25);
	glPopMatrix();

	glPushMatrix();
	//	glColor3f(0.0,1.0,0.0);
	quadratic1=gluNewQuadric();                  // Create A Pointer To The Quadric Object ( NEW 
    gluQuadricNormals(quadratic1, GLU_SMOOTH);   // Create Smooth Normals
    gluQuadricTexture(quadratic1, GL_TRUE);      // Create Texture Coords ( NEW )
	glTranslatef(-2.2f,3.7f,-6.0f);
	glRotatef(-90.0f,0.0f,1.0f,0.0f);
	gluSphere(quadratic1,.8f,25,25);
	glPopMatrix();

	glPushMatrix();
	//	glColor3f(0.0,1.0,0.0);
	quadratic1=gluNewQuadric();                  // Create A Pointer To The Quadric Object ( NEW 
    gluQuadricNormals(quadratic1, GLU_SMOOTH);   // Create Smooth Normals
    gluQuadricTexture(quadratic1, GL_TRUE);      // Create Texture Coords ( NEW )
	glTranslatef(-2.5f,2.6f,-6.0f);
	//glRotatef(-45.0f,0.0f,0.0f,1.0f);
	gluSphere(quadratic1,.8f,25,25);
	glPopMatrix();

	glPushMatrix();
	//	glColor3f(0.0,1.0,0.0);
	quadratic1=gluNewQuadric();                  // Create A Pointer To The Quadric Object ( NEW 
    gluQuadricNormals(quadratic1, GLU_SMOOTH);   // Create Smooth Normals
    gluQuadricTexture(quadratic1, GL_TRUE);      // Create Texture Coords ( NEW )
	glTranslatef(-0.9f,3.2f,-6.0f);
	//glRotatef(-45.0f,0.0f,0.0f,1.0f);
	gluSphere(quadratic1,.8f,25,25);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_LIGHTING);
	
}