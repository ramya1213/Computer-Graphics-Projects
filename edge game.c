#include<GLUT.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<string.h>

void *currentfont;
float q=0,p=0;
int ww,wh;
float scaleX,scaleY;
float boxPosX,boxPosY;

void box()
{
	float x1=12.4+q,y1=10.1+p;
	boxPosX=12.4+q;boxPosY=10.1+p;
	glPointSize(4);
glBegin(GL_POINTS);
glColor3f(1,1,1);
glVertex2f(x1,y1);

glEnd();
glPointSize(1);

}

void setFont(void *font)
{
	currentfont=font;
}

void drawstring(float x,float y,float z,char *string)
{
	    char *c;
	glRasterPos3f(x,y,z);
 
	for(c=string;*c!='\0';c++)
	{	glColor3f(0.0,1.0,0.0);
		glutBitmapCharacter(currentfont,*c);
	}
}


void init()
{

	glClearColor(0,0,0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10,50,-10,50);
	glMatrixMode(GL_MODELVIEW);

setFont(GLUT_BITMAP_HELVETICA_10);
}

void reshape(int w,int h)
{
  glViewport(0,0,(GLsizei)w,(GLsizei)h);
  ww=w;wh=h;
  scaleX= 60.0/ww;
  scaleY= 60.0/wh;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


 
// FRONT SCREEN OF PROGRAM 


  

void displaytext()
{
  glClear(GL_COLOR_BUFFER_BIT);
  setFont(GLUT_BITMAP_HELVETICA_10);
	glColor3f(1,1,0);
  	setFont(GLUT_BITMAP_HELVETICA_18);
	drawstring(-5,25,0,"PROJECT PATNERS");
	drawstring(-5,22,0,"1");
	drawstring(-5,20,0,"2");

	glColor3f(1,1,0);
	drawstring(20,25,0,"PROJECT GUIDES");
	drawstring(20,22,0,"Lecturer,CSE");
	drawstring(20,20,0,"Lecturer,CSE");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0,1,1);
	drawstring(13,33,0,"GRAPHICAL EDGE GAME");
	glColor3f(0,1,0);
    drawstring(13,32,0,"______________________");
	glColor3f(1,0,0);
	drawstring(5,45,0,"Colleges");
	glColor3f(1,0,1);
	drawstring(13,40,0,"CG MINI PROJECT");
	drawstring(13,39,0,"________________");
	glColor3f(0,1,1);
     drawstring(30,5,0,"ENTER N TO CONTINUE");
	 glColor3f(0,0,1);
	 glBegin(GL_LINE_LOOP);//writer head
	glVertex2i(-7,-7);
	glVertex2i(-7,48);
	glVertex2i(48,48);
	glVertex2i(48,-7);
	glEnd();


	glEnd();
      

  
	glFlush();
}


//FIRST LEVEL 


void display1()
{

	glClear(GL_COLOR_BUFFER_BIT);
	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0,1,0);
	drawstring(20,45,0,"LEVEL 1");
	drawstring(20,44.7,0,"_______");

    setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0,1,0);
	drawstring(5,12.5,0,"START");
	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0,0,1);
	drawstring(1,37.5,0,"GOAL");
	glColor3f(1,1,0);
	drawstring(32,7,0,"ENTER N NEXT STAGE");
	glColor3f(1,0,1);
	drawstring(32,4,0,"ENTER E FOR EXIT");
	setFont(GLUT_BITMAP_HELVETICA_10);
	glColor3f(1,1,0);
	drawstring(2,2,0,"NOTE:IF U REACH GOAL THEN ONLY PRESS N");



	glColor3f(1,0,0);
	glBegin(GL_QUADS);
	glVertex2f(12.5,10);
	glVertex2f(30,10);
	glVertex2f(30,15);
	glVertex2f(12.5,15);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(30,10);
	glVertex2f(30,40);
	glVertex2f(25,40);
	glVertex2f(25,10);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(30,40);
	glVertex2f(5,40);
	glVertex2f(5,35);
	glVertex2f(30,35);
	glEnd();

	box();
	//axis1();
	glFlush();

}


// SECOND LEVEL
void display2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	setFont(GLUT_BITMAP_HELVETICA_18);

	glColor3f(0,1,0);
	drawstring(20,45,0,"LEVEL 2");
	drawstring(20,44.7,0,"_______");

    setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0,1,0);
	drawstring(10,7.5,0,"START");
	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0,0,1);
	drawstring(36,40,0,"GOAL");
	glColor3f(0,1,1);
	drawstring(32,7,0,"ENTER P FOR MAIN MENU");
	glColor3f(0,0,1);
	drawstring(32,4,0,"ENTER E FOR EXIT");




	glColor3f(1,0,0);
	glBegin(GL_QUADS);
	glVertex2f(10,10);
	glVertex2f(15,10);
	glVertex2f(15,20);
	glVertex2f(10,20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(10,20);
	glVertex2f(10,22.5);
	glVertex2f(22.5,22.5);
	glVertex2f(22.5,20);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(22.5,20);
	glVertex2f(25,20);
	glVertex2f(25,40);
	glVertex2f(22.5,40);
	glEnd();
	
	glBegin(GL_QUADS);
	glVertex2f(22.5,41.2);
	glVertex2f(35,41.2);
	glVertex2f(35,40);
	glVertex2f(22.5,40);
	glEnd();

	box();
	//axis1();
	glFlush();

}


void display()
{
   if(boxPosX >=34.5 && boxPosX <=35)
	{
		printf("LEVEL TWO COMPLETE \n");
	}

   
   else if(boxPosX >=4.5 && boxPosX <=5)
	{
		printf("LEVEL ONE COMPLETE \n");
	}
}

int disp=0;
void display3()
{
	if(disp==0)
	{
		displaytext();
;
	}
	else if(disp==1)
	{
		display1();
		display();
	}
	else if(disp==2)
	{
		display2();
		display();	;
	}
}

void keyboard(unsigned char key,int x,int y)
{
	boxPosX=12.4+q;boxPosY=10.1+p;
	printf("x=%d,y=%d\n",x,y);
	printf("SCREEN NO=%d\n",disp);
	
	
	if(disp==0)
	{
		if((key=='n'|| key=='N'))
		{
			q=0;
			p=0;
			disp=1;
		}
	}
	else if(disp==2)//FOR SECOND LEVEL
	{
		if(key=='s'|| key=='S') 
		{
			// CONDITIONS TO MOVE VOX WITHIN THE SPECIFIED PATH
			if(boxPosX >=10 && boxPosX <=15)
				if(boxPosY >=10.7 && boxPosY <=22.5)
			      p=p-0.7;
			if(boxPosY >=20.7 && boxPosY <=22.5)
				if(boxPosX >=10 && boxPosX <=22.5)
				  p-=0.7;
			if(boxPosX >=22.5 && boxPosX <=25)
				if(boxPosY >=20.7 && boxPosY <=40)
				  p-=0.7;
			if(boxPosY >=20.7 && boxPosY<=40.5)
				if(boxPosX >=22.5 && boxPosX <=35)
				  p-=0.7;
		}
		if(key=='w'|| key=='W') 
		{
			if(boxPosX >=10 && boxPosX <=15)
				if(boxPosY >=10 && boxPosY <=20)
				      p=p+0.7;
			if(boxPosY >=20 && boxPosY <=21.8)
				if(boxPosX >=10 && boxPosX <=22.5)
					  p+=0.7;
			if(boxPosX >=22.5 && boxPosX <=25)
				if(boxPosY >=20 && boxPosY <=40)
					  p+=0.7;
			if(boxPosY >=40 && boxPosY<=40.5)
				if(boxPosX >=22.5 && boxPosX <=35)
					  p+=0.7;
	
		}	
		if(key=='a'|| key=='A') 
		{
			if(boxPosX >=10.7 && boxPosX <=15)
				if(boxPosY >=10 && boxPosY <=20)
			      q=q-0.7;
			if(boxPosY >=20 && boxPosY <=21.8)
				if(boxPosX >=10.7 && boxPosX <=22.5)
				  q-=0.7;
			if(boxPosX >=23.2 && boxPosX <=25)
				if(boxPosY >=20 && boxPosY <=40)
				  q-=0.7;
			if(boxPosY >=40 && boxPosY<=40.5)
				if(boxPosX >=23.2 && boxPosX <=35)
				  q-=0.7;
		}
		if(key=='d'|| key=='D')
		{
			if(boxPosX >=10 && boxPosX <=14.3)
				if(boxPosY >=10 && boxPosY <=20)
				  q=q+0.7;
			if(boxPosY >=20 && boxPosY <=21.8)
				if(boxPosX >=10 && boxPosX <=22.5)
				  q+=0.7;
			if(boxPosX >=22.5 && boxPosX <=24.3)
				if(boxPosY >=20 && boxPosY <=40)
				  q+=0.7;
			if(boxPosY >=40 && boxPosY<=40.5)
				if(boxPosX >=22.5 && boxPosX <=34.3)
				  q+=0.7;
		} 
		if((key=='p'|| key=='P'))
		{
			q=0;
			p=0;
			disp=0;
		}


		if((key=='E'|| key=='e'))
		{
			exit(0);
		}
	}
    else if(disp==1) //FOR LEVEL 1
	{    
		boxPosX=12.5+q;boxPosY=10+p;
		printf("x=%d,y=%d\n",x,y);
		//printf("scaledX=%f,scaledY=%f\n",boxPosX,(wh-y)*scaleY)
		if(key=='s'|| key=='S')
		{    // CONDITIONS TO MOVE VOX WITHIN THE SPECIFIED PATH
			if(boxPosY >=10 && boxPosY <=15)
				if(boxPosX >=12.5 && boxPosX <=25)
				  p=p-0.7;
			if(boxPosX >=25 && boxPosX <=30)
				if(boxPosY >=15 && boxPosY <=40)
				  p-=0.7;
			if(boxPosY >=35 && boxPosY <=40)
				if(boxPosX >=5 && boxPosX <=25)
				  p-=0.7;
		}
		if(key=='w'|| key=='W')
		{
			if(boxPosY >=10 && boxPosY <=14.3)
				if(boxPosX >=12.5 && boxPosX <=25)
				  p+=0.7;
			if(boxPosX >=25 && boxPosX <=30)
				if(boxPosY >=10 && boxPosY <=40)
				  p+=0.7;
			if(boxPosY >=35 && boxPosY <=40)
				if(boxPosX >=5 && boxPosX <=25)
				  p+=0.7;
		}	
		if(key=='a'|| key=='A')
		{
			if(boxPosY >=10 && boxPosY <=15)
				if(boxPosX >=12.5 && boxPosX <=25)
				  q-=0.7;
			if(boxPosX >=24.5 && boxPosX <=30)
				if(boxPosY >=15 && boxPosY <=40)
				  q-=0.7;
			if(boxPosY >=35 && boxPosY <=40)
				if(boxPosX >=5 && boxPosX <=30)
				  q-=0.7;
		}
		if(key=='d'|| key=='D')
		{
			if(boxPosY >=10 && boxPosY <=15)
				if(boxPosX >=12.5 && boxPosX <=29.3)
				  q=q+0.7;
			if(boxPosX >=25 && boxPosX <=30)
				if(boxPosY >=15 && boxPosY <=40)
				  q+=0.7;
	/*	if(boxPosY >=10 && boxPosY <=14.3)
			if(boxPosX >=12.5 && boxPosX <=30)
		      q=q+0.7;
             */
		}
		// INTERACTIVE MENU TO SWITCH BETWEEN MAIN MENU AND STAGES
		if((key=='n'|| key=='N'))
		{
			q=0;
			p=0;
			disp=2;
		}
		if((key=='p'|| key=='P'))
		{
			q=0;
			p=0;
			disp=0;
		} 

		if((key=='E'|| key=='e'))
		{
			exit(0);
		}
	}
	display3();
}



void main(int argc,char **argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(900,700);
glClearColor(0.7, 0.4, 0.2, 1.0);
glutCreateWindow("CG MINI PROJECT");
glutKeyboardFunc(keyboard);
glutDisplayFunc(display3);
init();
glutMainLoop();
}
