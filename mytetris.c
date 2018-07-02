#include<glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define YELL 1
#define BOX 2
#define LINE 3
#define TEE 4
#define YEL 5
GLfloat color[6][3]={{1,0,0},
				   {0,1,0},
				   {0,0,1},
				   {1,1,0},
				   {0,1,1},
				   {1,0,1}};
GLint shapes[5][4][4][2]={{{{0,0},{20,0},{20,-20},{0,-20}},{{20,0},{40,0},{40,-20},{20,-20}},{{40,0},{60,0},{60,-20},{40,-20}},{{0,-20},{20,-20},{20,-40},{0,-40}}},
		{{{0,0},{20,0},{20,-20},{0,-20}},{{20,0},{40,0},{40,-20},{20,-20}},{{0,-20},{20,-20},{20,-40},{0,-40}},{{20,-20},{40,-20},{40,-40},{20,-40}}},
		{{{0,0},{20,0},{20,-20},{0,-20}},{{20,0},{40,0},{40,-20},{20,-20}},{{40,0},{60,0},{60,-20},{40,-20}},{{60,0},{80,0},{80,-20},{60,-20}}},
		{{{0,0},{20,0},{20,-20},{0,-20}},{{20,0},{40,0},{40,-20},{20,-20}},{{40,0},{60,0},{60,-20},{40,-20}},{{20,-20},{40,-20},{40,-40},{20,-40}}},
		{{{20,0},{40,0},{40,-20},{20,-20}},{{20,-20},{40,-20},{40,-40},{20,-40}},{{0,-20},{20,-20},{20,-40},{0,-40}},{{0,-40},{20,-40},{20,-60},{0,-60}}}};

GLint board[20][10]={{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};
int bs=20,yell,x2=100,y2=400;//box size
int color1=0,color2=1,color3=3,color4=2,randshape=1,angle=0,mode=0,anychanges=1;

GLfloat m1[16],m2[4][4],angle1;
GLint tempshape[4][4][2];
void createrand(void)
{
x2=100;
y2=400;
	srand(time(NULL));
	color1=rand()%6;
	color2=rand()%6;
	color3=rand()%6;
	color4=rand()%6;
	randshape=rand()%5;
}
void drawtempshape()
{
	int i,j,x11,y11;
	GLfloat temp;
	glPushMatrix();
		angle1=((float)angle*3.14157)/180;
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					m2[i][j]=0;
			m2[0][0]=cos(angle1);
				m2[0][1]=-sin(angle1);
				m2[1][0]=sin(angle1);
				m2[1][1]=cos(angle1);
				m2[2][2]=1;
				m2[0][3]=-20;
				m2[1][3]=20;
				m2[3][3]=1;
				if(randshape==2) m2[0][3]=m2[0][3]-20;
		temp=m2[0][3]*cos(angle1)-m2[1][3]*sin(angle1);
		m2[1][3]=y2+m2[0][3]*sin(angle1)+m2[1][3]*cos(angle1);
		m2[0][3]=x2+temp;
				for(i=0;i<4;i++)
				{
					for(j=0;j<4;j++)
						{
					tempshape[i][j][0]=shapes[randshape][i][j][0]*m2[0][0]+shapes[randshape][i][j][1]*m2[0][1]+m2[0][3];
					tempshape[i][j][1]=shapes[randshape][i][j][0]*m2[1][0]+shapes[randshape][i][j][1]*m2[1][1]+m2[1][3];
						}
				}
		for(i=0;i<10;i++)
			for(j=0;j<20;j++)
				if(board[j][i]>=6) board[j][i]=-1;
	for(i=0;i<4;i++)
		{

			x11=(tempshape[i][0][0]+tempshape[i][2][0])/2;
			y11=(tempshape[i][0][1]+tempshape[i][2][1])/2;
			if(x11>200||x11<0||y11>400||y11<0) continue;
			if(mode==0)
			{
			switch(i)
			{
				case 0:board[y11/20][x11/20]=color1+6;break;
				case 1:board[y11/20][x11/20]=color2+6;break;
				case 2:board[y11/20][x11/20]=color3+6;break;
				case 3:board[y11/20][x11/20]=color4+6;break;
			}
			}
			else {
				switch(i)
							{
								case 0:board[y11/20][x11/20]=color1;break;
								case 1:board[y11/20][x11/20]=color2;break;
								case 2:board[y11/20][x11/20]=color3;break;
								case 3:board[y11/20][x11/20]=color4;break;
							}

			}
		}
	for(i=0;i<10;i++)
			for(j=0;j<20;j++)
			{
				if(board[j][i]==-1)
					glColor3f(1,1,1);
				else
		glColor3fv(color[board[j][i]%6]);

		glBegin(GL_POLYGON);
		glVertex2i(i*20,j*20);
		glVertex2i(i*20+20,j*20);
		glVertex2i(i*20+20,j*20+20);
		glVertex2i(i*20,j*20+20);
		glEnd();
			}
	glPopMatrix();
	if(mode==1)
	{
		mode=0;
		createrand();
				angle=0;
	}
anychanges=0;
}

void mykey(unsigned int key,int x,int y)
{

}
void mouse(int btn,int state,int x,int y)
{

}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
if(anychanges==1)
	drawtempshape(0);
	glutSwapBuffers();
	glFlush();
}
int testifcanbedrawn()
{
int i,j,x11,y11;
GLint tempshape[4][4][2];
	GLfloat temp;

		angle1=((float)angle*3.14157)/180;
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					m2[i][j]=0;
			m2[0][0]=cos(angle1);
				m2[0][1]=-sin(angle1);
				m2[1][0]=sin(angle1);
				m2[1][1]=cos(angle1);
				m2[2][2]=1;
				m2[0][3]=-20;
				m2[1][3]=20;
				m2[3][3]=1;
				if(randshape==2) m2[0][3]=m2[0][3]-20;
		temp=m2[0][3]*cos(angle1)-m2[1][3]*sin(angle1);
		m2[1][3]=y2+m2[0][3]*sin(angle1)+m2[1][3]*cos(angle1);
		m2[0][3]=x2+temp;
				for(i=0;i<4;i++)
				{
					for(j=0;j<4;j++)
						{
					tempshape[i][j][0]=shapes[randshape][i][j][0]*m2[0][0]+shapes[randshape][i][j][1]*m2[0][1]+m2[0][3];
					tempshape[i][j][1]=shapes[randshape][i][j][0]*m2[1][0]+shapes[randshape][i][j][1]*m2[1][1]+m2[1][3];
						}
				}
for(i=0;i<4;i++)
{x11=(tempshape[i][0][0]+tempshape[i][2][0])/2;
y11=(tempshape[i][0][1]+tempshape[i][2][1])/2;
if(x11>200||x11<0||y11<0)
{
return 0;
}
else if(board[y11/20][x11/20]>=0 && board[y11/20][x11/20]<=5) return 0;

}
	return 1;
}
void dropdown()
{
	anychanges=1;
	y2-=20;
	if(testifcanbedrawn()==0)
	{
		y2+=20;
		mode=1;
		}
	else mode=0;
	glutPostRedisplay();
	glutTimerFunc(500,dropdown,1);
}
void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,200,0,400,-1,1);
	glMatrixMode(GL_MODELVIEW);
}


void Keys(int key,int x,int y){
anychanges=1;
        switch(key){
        case GLUT_KEY_LEFT:x2-=20;
        					if(testifcanbedrawn()==0) x2+=20;
                            break;
        case GLUT_KEY_RIGHT:x2+=20;
        					if(testifcanbedrawn()==0) x2-=20;
        					break;
        case GLUT_KEY_UP:angle=(angle-90)%360;
        				if(testifcanbedrawn()==0) angle=(angle+90)%360;
        					break;
        case GLUT_KEY_DOWN:angle=(angle+90)%360;
        				if(testifcanbedrawn()==0) angle=(angle-90)%360;
        					break;
        }

        glutPostRedisplay();
}
int main(int argc,char**argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowSize(200,400);
glutCreateWindow("tetris");
createrand();
glutDisplayFunc(display);
glutTimerFunc(1000,dropdown,1);
glutSpecialFunc(Keys);
init();
glutMainLoop();
return 0;
}
