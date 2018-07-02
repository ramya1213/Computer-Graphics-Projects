#include<windows.h>
#include<gl/glut.h>
#include<stdlib.h>
#include<stdarg.h>
#include<stdio.h>
#include<string.h>
#define TEXTID      5
int f=0;
typedef GLfloat p2D[2];
static GLint fogMode;
//varible for quadratic object list
GLuint startList;
//variables for bouy, boat, sun and plane angle of rotation
GLint bouyAngle, boatAngle, sunAngle, planeAngle = 0;
//variable to assist the turing of the boat when changing direction
GLfloat boatFlip = 0;
//varible to store distnace out of waves
GLfloat waveDistance = 3.0;
//flag to allow for correct changing of direction
int dirFlag = 0;


void DrawTextXY(double x,double y,double z,double scale,char *s)
{
int i;
glPushMatrix();
glTranslatef(x,y,z);
glScalef(scale,scale,scale);
for(i=0;i<strlen(s);i++)
glutStrokeCharacter(GLUT_STROKE_ROMAN,s[i]);
glPopMatrix();
}
void myReshape(int w, int h)
{
glViewport(0, 0, w, h);
glMatrixMode(GL_PROJECTION); 
glLoadIdentity(); 
glMatrixMode(GL_PROJECTION);
gluPerspective(  50.0,(GLdouble)w/(GLdouble)h, 1.0, 10.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(0.0, 0.0, 5.0,0.0, 0.0, 0.0,0.0, 1.0, 0.0);  
}


void init(void)
{
//set up light properties
GLfloat mat_diffuse[] = {0.5,0.5,0.2,1.0};
GLfloat mat_specular[] = {0.4, 0.4, 0.6, 1.0};
GLfloat mat_shininess[] ={100.0};
GLfloat light_position[]={-1.0,2.0,4.0,0.0};
GLfloat lmodel_ambient[]={0.7,0.5,0.0,1.0};
//define objects for quads
GLUquadricObj *qobj;
startList = glGenLists(1);
qobj = gluNewQuadric();
//clylinder for bouy stick
gluQuadricDrawStyle(qobj, GLU_FILL);
gluQuadricNormals(qobj, GLU_SMOOTH);
glNewList(startList, GL_COMPILE);
gluCylinder(qobj, 0.025, 0.025, 1.0, 30, 10);
glEndList();
//cylinder for tree bases
gluQuadricDrawStyle(qobj, GLU_FILL);
gluQuadricNormals(qobj, GLU_SMOOTH);
glNewList(startList+1, GL_COMPILE);
gluCylinder(qobj, 0.25, 0.25, 1.0, 30, 10);
glEndList();
glClearColor(0.2, 0.2, 0.7, 1.0); /* black background */
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
glColorMaterial(GL_FRONT, GL_DIFFUSE);
glEnable(GL_COLOR_MATERIAL);           //enable colour tracking
glEnable(GL_LIGHTING);                       //enable lighting
glEnable(GL_LIGHT0);             //enable light0
glEnable(GL_DEPTH_TEST);               //enable depth testing

/* Set up for blending  */
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glShadeModel(GL_SMOOTH);
/*Set up for fog*/
glEnable(GL_FOG);
  {
GLfloat fogColor[4] = {0.3, 0.3, 0.6, 1.0};
fogMode = GL_EXP;
glFogi(GL_FOG_MODE, fogMode);
glFogfv(GL_FOG_COLOR, fogColor);
glFogf(GL_FOG_DENSITY, 0.3);
glHint(GL_FOG_HINT, GL_DONT_CARE);
glFogf(GL_FOG_START, 1.0);
glFogf(GL_FOG_END, 5.0);
   }
}

void drawHouse(p2D pos,const GLfloat size)
{
const GLfloat xzSize = (0.5*size) + (0.075*size);
const GLfloat yHeight = (0.5*size);
glPushMatrix();
glTranslatef(pos[0], (size), pos[1]);
glColor3f(0.6, 0.1, 0.1);
glutSolidCube(size);

//draw chimney
glPushMatrix();
glTranslatef(0.25*size, 0.6*size, 0.0);
glScalef(1.0, 2.0, 1.0);
glutSolidCube(0.2*size);
glPopMatrix();


//draw roof using triangles
glBegin(GL_TRIANGLES);
glColor3f(0.5, 0.5, 0.0);
glNormal3f(1.0, 2.2, 0.0);
glVertex3f(xzSize, yHeight, xzSize);
glColor3f(0.5, 0.5, 0.0);
glVertex3f(xzSize, yHeight, -xzSize);
glColor3f(0.0, 0.0, 0.8);
glVertex3f(0.0, (yHeight+(0.25*size)), 0.0);
glColor3f(0.5, 0.5, 0.0);
glNormal3f(0.0, 2.2, 1.0);
glVertex3f(xzSize, yHeight, xzSize);
glColor3f(0.5, 0.5, 0.0);
glVertex3f(-xzSize, yHeight, xzSize);
glColor3f(0.0, 0.0, 0.8);
glVertex3f(0.0, (yHeight+(0.25*size)), 0.0);
glColor3f(0.5, 0.5, 0.0);
glNormal3f(-1.0, 2.2, 0.0);
glVertex3f(-xzSize, yHeight, xzSize);
glColor3f(0.5, 0.5, 0.0);
glVertex3f(-xzSize, yHeight, -xzSize);
glColor3f(0.0, 0.0, 0.8);
glVertex3f(0.0, (yHeight+(0.25*size)), 0.0);
glColor3f(0.5, 0.5, 0.0);
glNormal3f(0.0, 2.2, -1.0);
glVertex3f(-xzSize, yHeight, -xzSize);
glColor3f(0.5, 0.5, 0.0);
glVertex3f(xzSize, yHeight, -xzSize);
glColor3f(0.0, 0.0, 0.8);
glVertex3f(0.0, (yHeight+(0.25*size)), 0.0);
glEnd();

//underside of the roof
glBegin(GL_POLYGON);
glColor3f(0.0, 0.0, 0.2);
glVertex3f(xzSize, yHeight, xzSize);
glVertex3f(-xzSize, yHeight, xzSize);
glVertex3f(-xzSize, yHeight, -xzSize);
glVertex3f(xzSize, yHeight, -xzSize);
glEnd();

//four legs of each house
//1
glPushMatrix();
glTranslatef(0.8*xzSize, -0.75*size, 0.8*xzSize);
glScalef(0.1, 1.0, 0.1);
glutSolidCube(size);
glPopMatrix();
//2
glPushMatrix();
glTranslatef(-0.8*xzSize, -0.75*size, 0.8*xzSize);
glScalef(0.1, 1.0, 0.1);
glutSolidCube(size);
glPopMatrix();

//3
glPushMatrix();
glTranslatef(-0.8*xzSize, -0.75*size, -0.8*xzSize);
glScalef(0.1, 1.0, 0.1);
glutSolidCube(size);
glPopMatrix();

//4
glPushMatrix();
glTranslatef(0.8*xzSize, -0.75*size, -0.8*xzSize);
glScalef(0.1, 1.0, 0.1);
glutSolidCube(size);
glPopMatrix();
glPopMatrix();
}

void DrawBeach()
{
//back section
glBegin(GL_POLYGON);
glColor3f(1.0,1.0,0.0);
glNormal3f(0, 1, 0);
glVertex3f(50.0, 0.0, 0.0);
glVertex3f(-50.0, 0.0, 0.0);
glVertex3f(-50.0, 0.0, -50.0);
glVertex3f(50.0, 0.0, -50.0);
glEnd();

//green grass in background
glBegin(GL_POLYGON);
glColor3f(0.0,0.8,0.0);
glNormal3f(0, 1, 0);
glVertex3f(50.0, 0.01, -1.0);
glVertex3f(-50.0, 0.01, -1.0);
glVertex3f(-50.0, 0.01, -50.0);
glVertex3f(50.0, 0.01, -50.0);
glEnd();

//slanted beach/waterfront
glBegin(GL_POLYGON);
glColor4f(1.0, 1.0, 0.0, 1.0);
glNormal3f(0, 0.6, 0.3);
glVertex3f(50.0, 0.0, 0.0);
glVertex3f(-50.0, 0.0, 0.0);
glColor3f(0.0, 0.0, 0.0);
glVertex3f(-50.0, -3.0, 6.0);
glVertex3f(50.0, -3.0, 6.0);
glEnd();

//draw ocean "floor"
glBegin(GL_POLYGON);
glColor4f(0.7, 0.7, 0.2, 1.0);
glVertex3f(50.0, -0.5, 0.0);
glVertex3f(-50.0, -0.5, 0.0);
glVertex3f(-50.0, -0.5, 6.0);
glVertex3f(50.0, -0.5, 6.0);
glEnd();

//draw water surface - translucent
glBegin(GL_POLYGON);
glColor4f(0.0, 0.2, 1.0, 0.75);
glVertex3f(50.0, -0.1, 0.0);
glVertex3f(-50.0, -0.1, 0.0);
glVertex3f(-50.0, -0.1, 6.0);
glVertex3f(50.0, -0.1, 6.0);
glEnd();
}

void DrawPier()
{
//draw main pier piece
glScalef(1.0, 0.2, 2.0);
glTranslatef(-3.25, 0.5, 0.5);
glColor3f(1.0, 1.0, 1.0);
glutSolidCube(1.0);

//draw six legs
glColor4f(0.05, 0.05, 0.0, 1.0);
glPushMatrix();
glTranslatef(0.47, -2.0, 0.5);
glScalef(0.1, 8.0, 0.1);
glutSolidCube(1.0);
glPopMatrix();
glPushMatrix();
glTranslatef(-0.47, -2.0, 0.5);
glScalef(0.1, 8.0, 0.1);
glutSolidCube(1.0);
glPopMatrix();
glPushMatrix();
glTranslatef(0.47, -2.0, 0.0);
glScalef(0.1, 8.0, 0.1);
glutSolidCube(1.0);
glPopMatrix();
glPushMatrix();
glTranslatef(-0.47, -2.0, 0.0);
glScalef(0.1, 8.0, 0.1);
glutSolidCube(1.0);
glPopMatrix();
glPushMatrix();
glTranslatef(0.47, -2.0, -0.5);
glScalef(0.1, 8.0, 0.1);
glutSolidCube(1.0);
glPopMatrix();
glPushMatrix();
glTranslatef(-0.47, -2.0, -0.5);
glScalef(0.1, 8.0, 0.1);
glutSolidCube(1.0);
glPopMatrix();
}

void DrawTree(p2D coord)
{
glPushMatrix();
glTranslatef(coord[0], 0.9, coord[1]);

//draw trunk clyinder
glPushMatrix();
glColor3f(0.5, 0.0, 0.0);
glRotatef(90.0, 1.0, 0.0, 0.0);
glCallList(startList+1);
glPopMatrix();

//draw green upper sections of the trees
glColor3f(0.1, 0.5, 0.1);
glTranslatef(0.0, -0.25, 0.0);
glRotatef(-90.0, 1.0, 0.0, 0.0);
glutSolidCone(0.75, 2.0, 100,20);
glTranslatef(0.0, 0.0, 0.5);
glutSolidCone(0.75, 2.0, 100,20);
glTranslatef(0.0, 0.0, 0.5);
glutSolidCone(0.75, 2.0, 100,20);
glPopMatrix();
}

void DrawWaves()
{
const GLfloat waveHeight = -0.0099;     //just above the water level
waveDistance = waveDistance-0.01;            //move waves closer
if (waveDistance<= 0.25)
waveDistance = 3.0;
glPushMatrix();
glTranslatef(0.0, 0.0, waveDistance);
glBegin(GL_TRIANGLES);
glColor4f(1.0, 1.0, 1.0, 1.0);
glNormal3f(0.0, 1.0, 0.0);
glVertex3f(-2.5, waveHeight, 0.0);
glVertex3f(-1.5, waveHeight, 0.0);
glColor4f(0.0, 0.2, 1.0, 0.2);         //transparent blue
glVertex3f(-2.0, waveHeight, 0.25);
glColor4f(1.0, 1.0, 1.0, 1.0);
glNormal3f(0.0, 1.0, 0.0);
glVertex3f(-1.2, waveHeight, 0.0);
glVertex3f(-0.2, waveHeight, 0.0);
glColor4f(0.0, 0.2, 1.0, 0.2);
glVertex3f(-0.7, waveHeight, 0.25);
glColor4f(1.0, 1.0, 1.0, 1.0);
glNormal3f(0.0, 1.0, 0.0);
glVertex3f(0.5, waveHeight, 0.0);
glVertex3f(1.5, waveHeight, 0.0);
glColor4f(0.0, 0.2, 1.0, 0.2);
glVertex3f(1.0, waveHeight, 0.25);
glEnd();
glPopMatrix();
}
void DrawBoat()
{
glPushMatrix();
glTranslatef(0.0, 0.0, 1.9);
glRotatef(boatAngle,0.0, 1.0, 0.0);      //for boat rotation around bouy
glTranslatef(1.0, -0.1, 0.0);
glRotatef(boatFlip, 0.0, 1.0, 0.0);       //use variable to turn boat

//draw boat hull, a very square boat hull
//i would have changed this shape but time was running out
glPushMatrix();
glColor3f(0.0, 0.0, 0.2);
glTranslatef(0.0, 0.3, 0.0);
glScalef(0.7, 8.0, 0.5);
glutSolidCube(0.1);
glPopMatrix();

//draw sail using a scaled cone
glPushMatrix();
glColor3f(1.0, 1.0, 1.0);
glTranslatef(0.0, 0.2, 0.0);
glRotatef(-90.0, 1.0, 0.0, 0.0);
glScalef(0.1, 1.0, 1.0);
glutSolidCone(0.3, 0.5, 20, 20);
glPopMatrix();

//draw mast using a scaled cube
glColor3f(0.4, 0.2, 0.2);
glPushMatrix();
glScalef(0.5, 0.5, 1.0);
glutSolidCube(0.5);
glPopMatrix();

//draw what should look like a rudder
glPushMatrix();
glTranslatef(0.0, 0.0, 0.25);
glScalef(0.3, 2.0, 2.0);
glutSolidCube(0.1);
glPopMatrix();

//build bow of boat
glBegin(GL_TRIANGLES);
glNormal3f(0.0, 1.0, 0.0);
glVertex3f(-0.125, 0.125, -0.25);
glVertex3f(0.125, 0.125, -0.25);
glVertex3f(0.0, 0.125, -0.5);
glNormal3f(-0.1875, -0.1875, -0.03125);
glVertex3f(-0.125, 0.125, -0.25);
glVertex3f(0.0, 0.125, -0.5);
glVertex3f(-0.125, -0.125, -0.25);
glNormal3f(0.1875, -0.1875, -0.03125);
glVertex3f(0.125, 0.125, -0.25);
glVertex3f(0.0, 0.125, -0.5);
glVertex3f(0.125, -0.125, -0.25);
glNormal3f(0.0, -0.5, -0.5);
glVertex3f(0.125, -0.125, -0.25);
glVertex3f(-0.125, -0.125, -0.25);
glVertex3f(0.0, 0.125, -0.5);
glEnd();
glPopMatrix();
}

void DrawSun()
{
int i = 0;
glPushMatrix();
glTranslatef(-3.0, 3.2, 0.0);
glColor3f(0.8, 0.6, 0.0);
glutSolidSphere(0.5, 20, 20);
glRotatef(sunAngle, 0.0, 0.0, 1.0);
//draw the six sun"beams"
glColor3f(1.0, 0.5, 0.0);
for (i = 0; i<=5; i++){
glBegin(GL_TRIANGLES);
glNormal3f(0.0, 0.0, 1.0);
glVertex3f(0.2, 0.4, 0.0);
glVertex3f(0.0, 0.9, 0.0);
glVertex3f(-0.2, 0.4, 0.0);
glEnd();
glRotatef(60.0, 0.0,0.0,1.0);
      }
glPopMatrix();
}

//function to draw a plane, well maybe not a plane, more of a
//flying saucer. Drawn on an angle so all sides can cumulatively be shown
void DrawPlane()
{
glPushMatrix();
glColor3f(0.0, 0.0, 0.0);
glRotatef(planeAngle, 0.0, 1.0, 0.0);
glTranslatef(0.0, 3.0, 1.0);
glRotatef(25.0, 1.0, 0.0, 0.0);
glutSolidSphere(0.2, 20, 20);
glPushMatrix();
glColor3f(0.8, 0.0, 0.0);
glRotatef(90.0, 1.0,0.0,0.0);
glutWireTorus(0.01, 0.5, 15, 20);
glPopMatrix();
glColor3f(0.0, 0.0, 0.2);
glTranslatef(0.0, 0.0, 0.0);
glRotatef(90.0, 0.0, 1.0, 0.0);
glScalef(1.0, 0.1, 1.0);
glutSolidSphere(0.5, 20, 20);
glPopMatrix();
}

void  Display(void)
{
      p2D house1 = {0.9/*x*/, 1.5/*z*/};
   p2D house2 = {-1.75/*x*/, 0.5/*z*/};
   p2D house3 = {0.2/*x*/, -1.0/*z*/};
   p2D tree1 = {-5.25/*x*/, -0.75/*z*/};
   p2D tree4 = {-4.5/*x*/, -2.0/*z*/};
   p2D tree2 = {2.25/*x*/, -0.75/*z*/};
   //p2D tree3 = {0.0/*x*/, -3.0/*z*/};
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glColor3f(1.0,1.0,1.0);
//draw houses at pre-defined positions
glPushMatrix();
glRotatef(45.0, 0.0, 1.0, 0.0);
drawHouse(house1, 1.25);
glPopMatrix();
glPushMatrix();
glRotatef(-10.0, 0.0, 1.0, 0.0);
drawHouse(house2, 1.5);
glPopMatrix();
drawHouse(house3, 1.4);
glPushMatrix();

DrawPier();
glPopMatrix();
//draw cool bouy in the ocean
glPushMatrix();
glColor4f(0.8, 0.2, 0.2, 1.0);
glTranslatef(0.0, 0.0, 1.9);
glutSolidSphere(0.25, 20, 20);

//Draw pole in the middle
glPushMatrix();
glColor3f(1.0, 1.0, 0.9);
glTranslatef(0.0, 1.0,0.0);
glRotatef(90.0, 1.0, 0.0, 0.0);
glCallList(startList);
glPopMatrix();

//draw main rotating beacon
glColor3f(0.0, 0.8, 0.1);
bouyAngle = (bouyAngle+5)%360;
glRotatef(bouyAngle, 0.0,1.0,0.0);
glTranslatef(0.0, 1.0, 0.0);
glutSolidSphere(0.1, 20, 20);


//draw smaller thing
glColor3f(0.0, 0.2, 0.8);
glRotatef(bouyAngle, 0.0, 1.0, 0.0);
glTranslatef(0.3, 0.0, 0.0);
glRotatef(bouyAngle, 0.0, 1.0, 0.0);
glutSolidSphere(0.05, 10, 10);

//smaller thing again
glColor3f(0.5, 0.5, 1.0);
glRotatef(bouyAngle, 0.0, 0.0, 1.0);
glTranslatef(0.0, 0.2, 0.2);
glRotatef(bouyAngle, 0.0, 1.0, 0.0);
glutSolidSphere(0.03, 10, 10);
glPopMatrix();

//draw trees according to positions
DrawTree(tree1);
DrawTree(tree2);
//DrawTree(tree3);
DrawTree(tree4);
DrawBoat();
DrawSun();
DrawPlane();

//draw objects on ocean floor
glColor3f(0.1, 0.1, 0.1);
glPushMatrix();
glTranslatef(-2.0, -0.5, 1.0);
glScalef(1.0, 0.3, 1.0);
glutSolidSphere(0.5, 20, 20);
glPopMatrix();
glPushMatrix();
glTranslatef(-1.0, -0.5, 2.0);
glScalef(1.0, 0.3, 1.0);
glutSolidSphere(0.5, 20, 20);
glPopMatrix();
glPushMatrix();
glTranslatef(1.0, -0.5, 1.0);
glScalef(1.0, 0.3, 1.0);
glutSolidSphere(0.5, 20, 20);
glPopMatrix();

DrawBeach();
DrawWaves();

}

void display2()
{  
glClearColor(0.0,0.0,0.0,1.0);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glColor3f(0.4,0.3,0.0);
glLoadName(TEXTID);
DrawTextXY(-4.15,2.05,1.0,0.004,"INDEX");
glColor3f(1.0,1.0,0.0);
glLoadName(TEXTID);
DrawTextXY(-4.15,1.05,0.1,0.004,"*INSTRUCTIONS");

glColor3f(1.0,1.0,0.0);
glLoadName(TEXTID);
DrawTextXY(-4.15,0.0,1.0,0.003,"press any key to continue ");

glFlush();
}
void help()
{
glClearColor(0.0,0.0,0.0,1.0);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
glColor3f(0.4,0.3,0.0);
glLoadName(TEXTID);
DrawTextXY(-2.0,2.05,0.0,0.003,"INSTRUCTIONS");
	glColor3f(0.4,0.3,0.0);
	glLoadName(TEXTID);
	DrawTextXY(-4.95,1.05,0.0,0.003,"right click to change direction ");
		glColor3f(1.0,1.0,0.0);
	glLoadName(TEXTID);
	DrawTextXY(-4.95,.50,0.0,0.003,"right click to stop");
glColor3f(1.0,1.0,0.0);
	glLoadName(TEXTID);
	DrawTextXY(-4.95,0.1,0.0,0.003,"right click to resume");
	glColor3f(1.0,0.5,1.0);
	glLoadName(TEXTID);
	DrawTextXY(-4.95,-.95,0.0,0.003,"right click to exit");
}

void display(void)
{
glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_MODELVIEW);
if (f==0)
	front();
else if(f==1)
  {
	display2();
  }
else if (f==2)
  {
	help();
  }
else {
Display();
  }
glutSwapBuffers();
  }

void myKey(unsigned char k, int x, int y)
{
	if(f==0)
	{
		f=1;
		display();
	}
else	if(f==1)
	{f=2;
		display();
	}
	else	{
		f=3;
		display();
	}
}

void MyReshape(int  w, int  h)
{
glViewport (0, 0, w, h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
gluLookAt(-1.0,2.0,5.0, -1.20,1.0,0.0, 0.0, 1.0, 0.0);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
Display();
}

//function for maintaining rotation in an anti-clockwise direction
void aClockWise()
{
sunAngle += 1%360;
boatAngle += 1%360;
planeAngle += 1%360;
boatFlip = 0.0;
glutPostRedisplay();
}

//function for maintaining rotation in a clockwise direction
void clockWise()
{
sunAngle -= 1%360;
boatAngle -= 1%360;
planeAngle -= 1%360;
boatFlip = 180.0;
glutPostRedisplay();
}
void main_menu_select(int value)
{
	switch(value)
	{
	case 2:exit(0);
case 1:{ if (dirFlag == 0)
    {
dirFlag = 1;
glutIdleFunc(clockWise);
      }
else
      {
dirFlag = 0;
glutIdleFunc(aClockWise);
            }
   }

		break;
case 3:glutIdleFunc(NULL);
		break;
	case 4:{if (dirFlag == 0)
glutIdleFunc(aClockWise);
else
glutIdleFunc(clockWise);
		}

	 }

glutPostRedisplay();
} 


int  main(int argc, char** argv)
{

glutInit(&argc, argv);

glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowSize(490,330);
glutInitWindowPosition(100,100);
glutCreateWindow("RESORT");

init();

glutDisplayFunc(display);           //register display function
glutKeyboardFunc(myKey);
	  
glutReshapeFunc(MyReshape);

glutIdleFunc(aClockWise);   /*Register idle callback function */
	glutCreateMenu(main_menu_select);
glutAddMenuEntry("change direction",1);
glutAddMenuEntry("stop", 3);
glutAddMenuEntry("resume", 4);
glutAddMenuEntry("Quit", 2);
glutAttachMenu(GLUT_RIGHT_BUTTON);
glutMainLoop();
return 0;
}


























