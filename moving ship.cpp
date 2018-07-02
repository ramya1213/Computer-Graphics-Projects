#include<glut.h>
#include<windows.h>

int flag=0;
float pos,y=0;

void ship(int x,int y)
{


			/*base*/

		glBegin(GL_POLYGON);
		glColor3f(0.30f,0.06f,0.42f);	
		glVertex2f(20+x,238+y);
		glColor3f(0.30f,0.06f,0.42f);		
		glVertex2f(20+x,220+y);
				glColor3f(.0f,0.0f,0.0f);	
		glVertex2f(82+x,140+y);
					glColor3f(0.0f,0.0f,0.0f);	
		glVertex2f(438+x,84+y);
						
			glColor3f(0.32f,0.06f,0.42f);	
		glVertex2f(584+x,196+y);
			glColor3f(0.30f,0.06f,0.42f);	
		glVertex2f(600+x,220+y);
		glEnd();
		
	/*p1*/
	
	glColor3f(0.70,0.0,0.0);
	glBegin(GL_POLYGON);
	
		glVertex2f(70+x,236+y);
		glVertex2f(70+x,256+y);
		glVertex2f(478+x,262+y);
		glVertex2f(478+x,222+y);
		glVertex2f(70+x,238+y);
		glEnd();
	

	

/*p2*/
		glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	//	glBegin(GL_LINE_LOOP);
		glVertex2f(90+x,258+y);
		glVertex2f(90+x,280+y);
		glVertex2f(466+x,298+y);
		glVertex2f(466+x,262+y);
		//glVertex2f(90+x,258+y);
		glEnd();


	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINE_LOOP);
		
		glVertex2f(90+x,258+y);
		glVertex2f(90+x,280+y);
		glVertex2f(466+x,298+y);
		glVertex2f(466+x,262+y);
		glVertex2f(90+x,258+y);
		glEnd();


	
/*p3*/

		glColor3f(0.30,0.30,0.30);
	glBegin(GL_POLYGON);
	
		glVertex2f(102+x,302+y);
		glVertex2f(102+x,280+y);
		glVertex2f(442+x,298+y);
		glVertex2f(442+x,330+y);
		glVertex2f(102+x,302+y);
	
	glEnd();






	
/*p4*/
	glColor3f(1.0,0.50,0.00);
	glBegin(GL_POLYGON);
	
		glVertex2f(158+x,304+y);
		glVertex2f(158+x,388+y);
		glColor3f(0.3,0.3,0.0);
		glVertex2f(188+x,388+y);
		glVertex2f(188+x,310+y);
	
	glEnd();

	
	

glBegin(GL_POLYGON);
	glColor3f(0.4,0.4,0.4);
		glVertex2f(442+x,328+y);
		glVertex2f(442+x,298+y);
		glVertex2f(494+x,294+y);
		glVertex2f(494+x,324+y);
		//glVertex2f(318+x,322+y);
		glEnd();

	
	glBegin(GL_POLYGON);
	glColor3f(0.80,0.80,0.80);
		glVertex2f(466+x,298+y);
		glVertex2f(466+x,262+y);
		glVertex2f(508+x,256+y);
		glVertex2f(508+x,290+y);
		//glVertex2f(318+x,322+y);
		glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.50,0.0,0.0);
		glVertex2f(478+x,262+y);
		glVertex2f(478+x,222+y);
		glVertex2f(514+x,220+y);
		glVertex2f(514+x,254+y);
		//glVertex2f(318+x,322+y);
		glEnd();

	
	glColor3f(1.0,0.50,0.0);
		glBegin(GL_POLYGON);
	
		glVertex2f(224+x,312+y);
		glVertex2f(224+x,396+y);
		glColor3f(0.3,0.3,0.0);
		glVertex2f(254+x,396+y);
		glVertex2f(254+x,315+y);
	glEnd();

	glColor3f(1.0,0.50,0.0);
		glBegin(GL_POLYGON);
//	glColor3f(0.5,0.5,0.2);
		glVertex2f(318+x,322+y);
//		glColor3f(0.3,0.1,0.0);
		glVertex2f(318+x,406+y);
			glColor3f(0.5,0.5,0.2);
		glVertex2f(358+x,406+y);
//		glColor3f(0.5,0.2,0.0);
		glVertex2f(358+x,320+y);
	//	glColor3f(0.3,0.3,0.0);
	
		glEnd();
	//}
}
void water1()
{
		glBegin(GL_POLYGON);
		glColor3f(0.0,0.0,1.0);
    		glVertex2f(0,160);
		glVertex2f(80,160);

		glVertex2f(480,100);
		glVertex2f(1024,100);
		glVertex2f(1024,0);
	glVertex2f(0,0);
	glEnd();
	
}

void water()
{
		glBegin(GL_POLYGON);
		glColor3f(0.0,0.0,1.0);
    //		glVertex2f(0,160);
		glVertex2f(80,160);

	//	glVertex2f(508,160);
		glVertex2f(1024,160);
		glVertex2f(1024,100);
	glVertex2f(480,100);
glVertex2f(80,160);
	glEnd();
	
}
void init()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(1.0,0.0,0.0);
	glLineWidth(3.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,1024,0,768);
	
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);


	pos+=0.1;
	water();
	ship(pos,y);
	 water1();

glutPostRedisplay();
	  glFlush();
		
      
        glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
		
	if(key==37)
	{
		pos-=0.1;
	water();
	ship(pos,y);
	 water1();

glutPostRedisplay();
	  glFlush();
	};
	if(key==39)
	{
		pos+=0.1;
	water();
	ship(pos,y);
	 water1();

glutPostRedisplay();
	  glFlush();
	};


	/*
	left arrow: 37 
up arrow: 38
right arrow: 39
down arrow: 40
	*/
		
}

void main(int argc,char ** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(1024,768);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Moving Ship");
	glutSwapBuffers();
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboardFunc);
	glEnable(GL_SMOOTH);
	init();
	glutMainLoop();

}
