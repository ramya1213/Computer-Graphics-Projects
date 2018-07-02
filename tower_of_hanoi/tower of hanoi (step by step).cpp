#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glut.h>

double WIDTH = 1100;
double HEIGHT = 500;

GLboolean motion = GL_TRUE;
GLboolean back_wall = GL_FALSE;
GLint xangle = 0, yangle = 0;
GLint xlangle = 0, ylangle = 0;

#define other(i,j) (6-(i+j))
#define wallz -(WIDTH/2)
#define DISK_HEIGHT 40
int NUM_DISKS = 11;
#define CONE NUM_DISKS+10
#define WALL CONE + 1
#define HANOI_SOLVE 1
#define HANOI_QUIT 2
#define HANOI_LIGHTING 3
#define HANOI_WALL 4
#define HANOI_FOG 5

GLfloat lightOneDirection[] ={0, 0, -1};

GLfloat lightOnePosition[] ={200, 100, 300, 1};

GLfloat lightOneColor[] ={1.0, 1.0, 0.5, 1.0};

GLfloat lightTwoDirection[] ={0, 0, -1};

GLfloat lightTwoPosition[] ={600, 100, 300, 1};

GLfloat lightTwoColor[] ={1.0, 0.0, 0.3, 1.0};

GLfloat lightZeroPosition[] ={400, 200, 300, 1};

GLfloat lightZeroColor[] ={.3, .3, .3, .3};

GLfloat diskColor[] ={1.0, 1.0, 1.0, .8}, poleColor[] ={1.0, 0.2, 0.2, .8};

typedef struct stack_node 
{
  int size;
  struct stack_node *next;
} stack_node;

typedef struct stack 
{
  struct stack_node *head;
  int depth;
} stack;

stack poles[4];

void output(GLfloat x, GLfloat y, char *text)
{
  char *p;
  int i=0;

  glPushMatrix();
  glTranslatef(x, y, 0);
	for (p = text; *p; p++)
		/* to display character */
		  glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
		  glPopMatrix();
}
void push(int which, int size)
{
  stack_node *new1 = new(stack_node);
  if (!new1) 
    {
      fprintf(stderr, "out of memory!\n");
      exit(-1);
    }
  new1->size = size;
  new1->next = poles[which].head;
  poles[which].head = new1;
  poles[which].depth++;
}

int pop(int which)
{
  int retval = poles[which].head->size;
  stack_node *temp = poles[which].head;
  poles[which].head = poles[which].head->next;
  poles[which].depth--;
  free(temp);
  return retval;
}

typedef struct move_node 
{
  int t, f;
  struct move_node *next;
  struct move_node *prev;
} move_node;

typedef struct move_stack 
{
  int depth;
  struct move_node *head, *tail;
} move_stack;

move_stack moves;

void init(void)
{
  int i;
  for (i = 0; i < 4; i++) 
    {
      poles[i].head = NULL;
      poles[i].depth = 0;
    }
  moves.head = NULL;
  moves.tail = NULL;
  moves.depth = 0;

  for (i = 1; i <= NUM_DISKS; i++) 
    {
      glNewList(i, GL_COMPILE);
        {
           glutSolidTorus(DISK_HEIGHT / 2, 5 * i, 15, 15);
        }
      glEndList();
    }
  glNewList(CONE, GL_COMPILE);
    {
      glutSolidCone(10, (NUM_DISKS + 1) * DISK_HEIGHT, 20, 20);
    }
  glEndList();
}

void mpop(void)
{
  move_node *temp = moves.head;
  moves.head = moves.head->next;
  free(temp);
  moves.depth--;
}

void mpush(int t, int f)
{
  move_node *new1 = new(move_node);
  if (!new1) {
    fprintf(stderr, "Out of memory!\n");
    exit(-1);
  }
  new1->t = t;
  new1->f = f;
  new1->next = NULL;
  new1->prev = moves.tail;
  if (moves.tail)
    moves.tail->next = new1;
  moves.tail = new1;
  if (!moves.head)
    moves.head = moves.tail;
  moves.depth++;
}


void update(void)
{
 //glutPostRedisplay();
}

void DrawPole(int xcenter)
{
  glPushMatrix();
  {
    glTranslatef(xcenter, 0, 0);
    glRotatef(90, -1, 0, 0);
    glCallList(CONE);
  } glPopMatrix();
}

void DrawPoles(void)
{
  glColor3fv(poleColor);
  glLineWidth(10);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, poleColor);
  DrawPole(WIDTH / 4);
  DrawPole(2 * WIDTH / 4);
  DrawPole(3 * WIDTH / 4);
}

void DrawDisk(int xcenter, int ycenter, int size)
{
  glPushMatrix();
  {
    glTranslatef(xcenter, ycenter, 0);
    glRotatef(90, 1, 0, 0);
    glCallList(size);
  } glPopMatrix();
}

void DrawDisks(void)
{
  int i;
  stack_node *temp;
  int xcenter, ycenter;
  glColor3fv(diskColor);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diskColor);
  for (i = 1; i <= 3; i++) {
    xcenter = i * WIDTH / 4;
    for (temp = poles[i].head, ycenter = DISK_HEIGHT * poles[i].depth - DISK_HEIGHT / 2; temp; temp = temp->next, ycenter -= DISK_HEIGHT) {
      DrawDisk(xcenter, ycenter, temp->size);
    }
  }
}

#define MOVE(t,f) mpush((t),(f))

static void mov(int n, int s, int d)
{
  int t;

  if (n == 1) {
    MOVE(d, s);
    return;
  }
  t = other(s, d);
  mov(n - 1, s, t);
  /* nth disk from s to d*/
  mov(1, s, d);
  mov(n - 1, t, d);
}

GLfloat wallcolor[] =
{0, .3, 1, 1};

void DrawWall(void)
{
  int i;
  int j;
  glColor3fv(wallcolor);
  for (i = 0; i < WIDTH; i += 10) {
    for (j = 0; j < HEIGHT; j +=10) {
      glBegin(GL_TRIANGLE_FAN);
      {
         glNormal3f(0, 0, 1);
		 glTranslated(550,50,0);
		glColor3f(i+2,i+1,i+i);
		glVertex3f(550,0,0);
		glColor3f(1.0,0.0,0.0);
		 glVertex3f(i + 10, j, wallz);
		glColor3f(i,0.0,i+1);
		glVertex3f(i + 10, j + 10, wallz);
		glColor3f(0.0,1.0,1.1);
        glVertex3f(i, j + 10, wallz);
		glColor3f(i,i+1,0.5);
		glVertex3f(i, j, wallz);
		}
      glEnd();
    }
  }
}
void teamd()
{

  glPushMatrix();
  glLoadIdentity();
  glTranslated(0,200,0);
  glColor3f(1.0,1.0,1.0);
  glScaled(0.5,0.5,0);
  glTranslated(0,-50,0);
  output(50,400,"The");
  output(300,400,"Project is");
  glTranslated(50,0,0);
  output(1000,400,"Submitted by");
  glTranslated(0,-50,0);
  output(200,300,"Hari Sankar B ");
  glTranslated(10,0,0);
  output(900,300,"6th Sem CSE");
  glTranslated(0,-50,0);
  output(200,200,"USN:1ks10cs037");
  glutSwapBuffers();
  glPopMatrix();
}
void draw(void)
{
  int t, f;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (back_wall) 
    {  
       glMaterialfv(GL_FRONT, GL_DIFFUSE, wallcolor);
       DrawWall();
    }

  glPushMatrix();
  glLoadIdentity();
  glTranslated(0,180,0);
  glColor3f(0.0,1.0,1.0);
  glScaled(0.8,0.5,0);
  glTranslated(50,0,0);
  output(0,500,"Tower");
  output(350,500," of Hanoi");
  glPopMatrix();
  glPushMatrix();
  glColor3f(1.0,0.0,1.0);
  glScaled(0.5,0.2,1);
  glTranslated(150,0,0);
  output(185,300,"S");
  output(800,300,"T");
  output(1300,300,"D");
  glPopMatrix();

  glPushMatrix();
    {
      glTranslatef(WIDTH / 2, HEIGHT / 2, 0);
      glRotatef(xlangle, 0, 1, 0);
      glRotatef(ylangle, 1, 0, 0);
      glTranslatef(-WIDTH / 2, -HEIGHT / 2, 0);
      glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);
    }

  glPopMatrix();
  glPushMatrix();
    {
      glTranslatef(WIDTH / 2, HEIGHT / 2, 0);
      glRotatef(xangle, 0, 1, 0);
      glRotatef(yangle, 1, 0, 0);
      glTranslatef(-WIDTH / 2, -HEIGHT / 2, 0);
      DrawPoles();
      DrawDisks();
    }
  glPopMatrix();
  if (motion && moves.depth) 
    {
      t = moves.head->t;
      f = moves.head->f;
      push(t, pop(f));
      mpop();
    }
  glutSwapBuffers();
}

void hanoi_menu(int value)
{
  switch (value) {
	  
  case HANOI_SOLVE:
	 // motion=!motion;
       if(motion) {
      glutIdleFunc(update);
    } else {
      glutIdleFunc(NULL);
    }
    break;
  case HANOI_LIGHTING:
    if (glIsEnabled(GL_LIGHTING))
      glDisable(GL_LIGHTING);
    else
      glEnable(GL_LIGHTING);
    break;
  case HANOI_WALL:
    back_wall = !back_wall;
    break;
  case HANOI_FOG:
    if (glIsEnabled(GL_FOG))
      glDisable(GL_FOG);
    else {
      glEnable(GL_FOG);
      glFogi(GL_FOG_MODE, GL_EXP);
      glFogf(GL_FOG_DENSITY, .01);
    }
    break;
  case HANOI_QUIT:
    exit(0);
    break;
  }
  glutPostRedisplay();
}
void 
keyboard(unsigned char key, int x, int y)
{	
  switch (key) 

    {
       case 27: 
                /* ESC */
       case 'Q':
                exit(0);
       case 't':teamd();
		break;
	
    }

}

int oldx, oldy;

GLboolean leftb = GL_FALSE, middleb = GL_FALSE;

void hanoi_mouse(int button, int state, int x, int y)
{

  int i;
  if (button == GLUT_LEFT_BUTTON) 
    {
      oldx = x;
      oldy = y;
      /* we can change the position of poles by moving the mouse botton */
      if (state == GLUT_DOWN)
        leftb = GL_TRUE;
      else
        leftb = GL_FALSE;
    }
  if (button == GLUT_MIDDLE_BUTTON) {
    oldx = x;
    oldy = y;
    if (state == GLUT_DOWN)
      middleb = GL_TRUE;
    else
      middleb = GL_FALSE;
  }
}

void hanoi_visibility(int state)
{
  if (state == GLUT_VISIBLE ) {
    glutIdleFunc(update);
  } else {
    glutIdleFunc(NULL);
  }
  
}

void hanoi_motion(int x, int y)
{
  if (leftb) {
	  /* to set the position of poles */
    xangle -= (x - oldx);
    yangle -= (y - oldy);
  }
  if (middleb) {
    xlangle -= (x - oldx);
    ylangle -= (y - oldy);
  }
  oldx = x;
  oldy = y;
  glutPostRedisplay();
}
void myinit()
{
  glViewport(0, 0, WIDTH, HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WIDTH, 0, HEIGHT, -10000, 10000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0, 0, 0, 0);
  glClearDepth(1.0);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);  

  glLightfv(GL_LIGHT1, GL_POSITION, lightOnePosition);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightOneColor);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightOneDirection);
  glEnable(GL_LIGHT1);

  glLightfv(GL_LIGHT2, GL_POSITION, lightTwoPosition);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, lightTwoColor);
  glLightf(GL_LIGHT2,GL_LINEAR_ATTENUATION,.005); 
  glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 10);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightTwoDirection);
  glEnable(GL_LIGHT2);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
  glEnable(GL_LIGHT0);

  glEnable(GL_LIGHTING);
}
int 
main(int argc, char *argv[])
{
  int i;
	printf("enter the number of disks\n");
	scanf("%d",& NUM_DISKS); 
	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Hanoi");
	glutDisplayFunc(draw);
	myinit();
	glClearColor(0.0,0.0,0.0,1.0);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(hanoi_mouse);
	glutMotionFunc(hanoi_motion);
	glutVisibilityFunc(hanoi_visibility);
        glutCreateMenu(hanoi_menu);
	glutAddMenuEntry("Solve", HANOI_SOLVE);
	glutAddMenuEntry("Lighting", HANOI_LIGHTING);
	glutAddMenuEntry("Back Wall", HANOI_WALL);
	glutAddMenuEntry("Fog", HANOI_FOG);
	glutAddMenuEntry("Quit", HANOI_QUIT);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();

	 for (i = 0; i < NUM_DISKS; i++)
		push(1, NUM_DISKS - i);
		 mov(NUM_DISKS, 1, 3);

  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}


