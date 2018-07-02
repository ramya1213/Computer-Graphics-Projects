#include<glut.h>
#include<stdio.h>
#include<iostream.h>
#include<stdlib.h>
#include<gl.h>
int i,j;
void *currentfont;

void setFont(void *font)
{
	currentfont=font;
}

void drawstring(float x,float y,float z,char *string)
{
	char *c;
	glRasterPos3f(x,y,z);
 
	for(c=string;*c!='\0';c++)
	{	glColor3f(0.0,0.0,0.0);
		glutBitmapCharacter(currentfont,*c);
	}
}

void text(void)											// to draw the menu screen
{

	

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,1.0,1.0);
	drawstring(140.0,455.0,1.0,"* * * * * THE BELLAMAN-FORD ALGORITHM * * * * *");

	glColor3f(0.0,0.0,1.0);
	drawstring(220.0,405.0,1.0,"See the Demo");				

	glColor3f(0.0,0.0,1.0);
	drawstring(220.0,350.0,1.0,"From src Node 1");

    glColor3f(0.0,0.0,1.0);
	drawstring(220.0,295.0,1.0,"From src Node 2");
	
	glColor3f(0.0,0.0,1.0);
	drawstring(220.0,240.0,1.0,"From src Node 3");

	glColor3f(0.0,0.0,1.0);
	drawstring(220.0,185.0,1.0,"From src Node 4");
	
	glColor3f(0.0,0.0,1.0);
	drawstring(220.0,130.0,1.0,"From src Node 5");

	glColor3f(1.0,1.0,1.0);
	drawstring(235.0,75.0,1.0,"EXIT ");
	glFlush();
																
}


void draw() // To draw the polygons for the menu box  
{

	glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);  // Demo Menu
	glColor3f(0.5f,0.5f,0.1f);
    glVertex2i(305,425);
	glVertex2i(180,425);
	glVertex2i(180,395);
    glVertex2i(305,395);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);  
	glColor3f(0.5f,0.5f,0.1f); // node 1
    glVertex2i(305,370);
	glVertex2i(180,370);
	glVertex2i(180,340);
    glVertex2i(305,340);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);  // node 2
	glColor3f(0.5f,0.5f,0.1f);
    glVertex2i(305,315);
	glVertex2i(180,315);
	glVertex2i(180,285);
    glVertex2i(305,285);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);  // node 3
	glColor3f(0.5f,0.5f,0.1f);
    glVertex2i(305,260);
	glVertex2i(180,260);
	glVertex2i(180,230);
    glVertex2i(305,230);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);  //node 4
	glColor3f(0.5f,0.5f,0.1f);
    glVertex2i(305,205);
	glVertex2i(180,205);
	glVertex2i(180,175);
    glVertex2i(305,175);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);  // node 5
	glColor3f(0.5f,0.5f,0.1f);
    glVertex2i(305,150);
	glVertex2i(180,150);
	glVertex2i(180,120);
    glVertex2i(305,120);
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);  // exit
	glColor3f(0.7f,0.2f,0.2f);
    glVertex2i(305,95);
	glVertex2i(180,95);
	glVertex2i(180,65);
    glVertex2i(305,65);
	glEnd();
	glFlush();

}		

void myInit()
{
    glClearColor(0.0,0.0,0.0,0.0);
	//glColor3f(0.0f,0.0f,0.0f);
//	glPointSize(5.0);
	gluOrtho2D(0.0,500.0,0.0,500.0);
	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	setFont(GLUT_BITMAP_HELVETICA_18);
	
}
void delay()
{
	
  j=15000;
	while(j!=0)
	{
		j--;
		i=15000;
		while(i!=0)
		{
			i--;
			
		}
	}


}
void delaypacket()
{
  j=1000;
	while(j!=0)
	{
		j--;
		i=1000;
		while(i!=0)
		{
			i--;
			
		}
	}


}



void naming()
{
	glColor3f(1.0,1.0,1.0);
	drawstring(105.5,403.5,1.0,"1");
	glColor3f(1.0,1.0,1.0);
	drawstring(105.5,203.5,1.0,"2");
	glColor3f(1.0,1.0,1.0);
	drawstring(305.5,403.0,1.0,"3");
	glColor3f(1.0,1.0,1.0);
	drawstring(205.5,303.0,1.0,"4");
	glColor3f(1.0,1.0,1.0);
	drawstring(305.5,203.0,1.0,"5");
	glColor3f(1.0,1.0,1.0);
	drawstring(420.5,303.5,1.0,"6");
	//on the lines
	glColor3f(1.0,1.0,1.0);
	drawstring(200.5,415.0,1.0,"2");//1&3
	glColor3f(1.0,1.0,1.0);
	drawstring(100.0,307.0,1.0,"3");//1&2
	glColor3f(1.0,1.0,1.0);
	drawstring(155.0,368.0,1.0,"5");//1&4
	glColor3f(1.0,1.0,1.0);
	drawstring(160.0,240.0,1.0,"1");//2&4
	glColor3f(1.0,1.0,1.0);
	drawstring(200.0,192.0,1.0,"3");//2&5
	glColor3f(1.0,1.0,1.0);
	drawstring(260.0,345.0,1.0,"2");//3&4
	glColor3f(1.0,1.0,1.0);
	drawstring(365.0,375.0,1.0,"1");//3&6
	glColor3f(1.0,1.0,1.0);
	drawstring(255.0,265.0,1.0,"3");//4&5
	glColor3f(1.0,1.0,1.0);
	drawstring(365.0,235.0,1.0,"2");//5&6
	
	
	
	glFlush();

	
}
void shape()
{
	//int i,j,temp=0.3;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	{
		// square for 1
		glVertex2f(100.0,415.0);
		glVertex2f(115.0,415.0);
		glVertex2f(115.0,415.0);
		glVertex2f(115.0,400.0);
		glVertex2f(115.0,400.0);
		glVertex2f(100.0,400.0);
		glVertex2f(100.0,400.0);
		glVertex2f(100.0,415.0);
		//square for 2
		glVertex2f(100.0,215.0);
		glVertex2f(115.0,215.0);
		glVertex2f(115.0,215.0);
		glVertex2f(115.0,200.0);
		glVertex2f(115.0,200.0);
		glVertex2f(100.0,200.0);
		glVertex2f(100.0,200.0);
		glVertex2f(100.0,215.0);
		//square for 3
        glVertex2f(300.0,415.0);
		glVertex2f(315.0,415.0);
		glVertex2f(315.0,415.0);
		glVertex2f(315.0,400.0);
		glVertex2f(315.0,400.0);
		glVertex2f(300.0,400.0);
		glVertex2f(300.0,400.0);
		glVertex2f(300.0,415.0);
		//square for 4
		glVertex2f(200.0,315.0);
		glVertex2f(215.0,315.0);
		glVertex2f(215.0,315.0);
		glVertex2f(215.0,300.0);
		glVertex2f(215.0,300.0);
		glVertex2f(200.0,300.0);
		glVertex2f(200.0,300.0);
		glVertex2f(200.0,315.0);
		//square for 5
		glVertex2f(300.0,215.0);
		glVertex2f(315.0,215.0);
		glVertex2f(315.0,215.0);
		glVertex2f(315.0,200.0);
		glVertex2f(315.0,200.0);
		glVertex2f(300.0,200.0);
		glVertex2f(300.0,200.0);
		glVertex2f(300.0,215.0);
		//square for 6
		glVertex2f(415.0,315.0);
		glVertex2f(430.0,315.0);
		glVertex2f(430.0,315.0);
		glVertex2f(430.0,300.0);
		glVertex2f(430.0,300.0);
		glVertex2f(415.0,300.0);
		glVertex2f(415.0,300.0);
		glVertex2f(415.0,315.0);
		//lines b/w 1&3
		glVertex2f(115.0,407.5);
		glVertex2f(300.0,407.5);
		//lines b/w 1&2
		glVertex2f(107.5,400.0);
		glVertex2f(107.5,215.0);
		//lines b/w 1&4
		glVertex2f(115.0,407.5);
		glVertex2f(200.0,307.5);
		//lines b/w 2&4
		glVertex2f(200.0,307.5);
		glVertex2f(115.0,207.5);
		//lines b/w 2&5
		glVertex2f(115.0,207.5);
		glVertex2f(300.0,207.5);
		//lines b/w 4&5
		glVertex2f(215.0,307.5);
		glVertex2f(300.0,207.5);
		//lines b/w 4&3
		glVertex2f(215.0,307.5);
		glVertex2f(300.0,407.5);
		// lines b/w 3&6 
		glVertex2f(315.0,407.5);
		glVertex2f(415.0,307.5);
		// lines b/w 5&6 
        glVertex2f(415.0,307.5);
		glVertex2f(315.0,207.5);
	}

	glEnd();
	glFlush();
																		
}

void move() 
{

	float i,temp=0.3,temp1=0.3;
	
for(i=0;i<170;i=i+temp) //movement of data packet from 1 to 3
	 {   glColor3f(1,0,0);
		 glBegin(GL_QUADS);
	  	glVertex2f(116+i,410.0);glVertex2f(116+i,415);glVertex2f(126+i,415);glVertex2f(126+i,410.0);
    glEnd();
    glFlush();
	
	delaypacket();

	
   glColor3f(0,0,0);
		 glBegin(GL_QUADS);
	glVertex2f(116+i,410.0);glVertex2f(116+i,415);glVertex2f(126+i,415);glVertex2f(126+i,410.0);
    glEnd();
    glFlush();
 } 

for(i=0;i<90;i=i+temp)//movement of data packet 3 to 6

	 {   
		glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
			glEnd();
		glFlush();
	
	delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
    glEnd();
    glFlush();
 }
glColor3f(1.0,1.0,1.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 1 to destination node 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,98.5,1.0,"1 -> 3 -> 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,86.5,1.0,"Cost C16= 3 (2+1) ");
    glFlush();/////////1
	delay();
	delay();
glColor3f(0.0,0.0,0.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 1 to destination node 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,98.5,1.0,"1 -> 3 -> 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,86.5,1.0,"Cost C16= 3 (2+1) ");
	glFlush();//2
delaypacket();
for(i=0;i<70;i=i+temp)//movement of data packet 2 to 4

	 {   glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(118.546056+i,224.13+i);glVertex2f(115.5+i,228.0+i);glVertex2f(123.26950+i,238.211241+i);glVertex2f(125.894+i,233.773028+i);
    glEnd();
    glFlush();
	
	delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(118.546056+i,224.13+i);glVertex2f(115.5+i,228.0+i);glVertex2f(123.26950+i,238.211241+i);glVertex2f(126.894+i,233.773028+i);
    glEnd();
    glFlush();
 }
for(i=0;i<65;i=i+temp)//movement of data packet 4 to 3

	 {   glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		glVertex2f(216.546056+i,328.03+i);glVertex2f(218.5+i,323.0+i);glVertex2f(227.894+i,335.773028+i);
		glVertex2f(225.26950+i,340.211241+i);
    glEnd();
    glFlush();
	
	delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 	glVertex2f(216.546056+i,328.03+i);glVertex2f(218.5+i,323.0+i);glVertex2f(227.894+i,335.773028+i);
		glVertex2f(225.26950+i,340.211241+i);
    glEnd();
    glFlush();
 }
for(i=0;i<90;i=i+temp)//movement of data packet 3 to 6

	 {   
		glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
			glEnd();
		glFlush();
	
	delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
    glEnd();
    glFlush();
 }

glColor3f(1.0,1.0,1.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 2 to destination node 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,98.5,1.0,"2 -> 4 -> 3 -> 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,86.5,1.0,"Cost C26= 4 (1+2+1) ");
	glFlush();//////3
	delay();
	delay();
glColor3f(0.0,0.0,0.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 2 to destination node 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,98.5,1.0,"2 -> 4 -> 3 -> 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,86.5,1.0,"Cost C26= 4 (1+2+1) ");
	glFlush();/////////4
 delaypacket();

 for(i=0;i<90;i=i+temp)//movement of data packet 3 to 6

	 {   
		glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
			glEnd();
		glFlush();
	
	delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
    glEnd();
    glFlush();
 }

glColor3f(1.0,1.0,1.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 3 to destination node 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,98.5,1.0,"3 -> 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,86.5,1.0,"Cost C36= 1 ");
	glFlush();//////5
	delay();
	delay();
glColor3f(0.0,0.0,0.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 3 to destination node 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,98.5,1.0,"3 -> 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,86.5,1.0,"Cost C36= 1 ");
	glFlush();/////6
 delaypacket();


 for(i=0;i<65;i=i+temp)//movement of data packet 4 to 3

	 {   glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		glVertex2f(216.546056+i,328.03+i);glVertex2f(218.5+i,323.0+i);glVertex2f(227.894+i,335.773028+i);
		glVertex2f(225.26950+i,340.211241+i);
    glEnd();
    glFlush();
	
	delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 	glVertex2f(216.546056+i,328.03+i);glVertex2f(218.5+i,323.0+i);glVertex2f(227.894+i,335.773028+i);
		glVertex2f(225.26950+i,340.211241+i);
    glEnd();
    glFlush();
 }
for(i=0;i<90;i=i+temp)//movement of data packet 3 to 6

	 {   
		glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
			glEnd();
		glFlush();
	
	delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
    glEnd();
    glFlush();
 }

glColor3f(1.0,1.0,1.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 4 to destination node 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,98.5,1.0,"4 -> 3 -> 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,86.5,1.0,"Cost C46= 3 (2+1) ");
	glFlush();//////7
	delay();
	delay();
glColor3f(0.0,0.0,0.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 4 to destination node 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,98.5,1.0,"4 -> 3 -> 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,86.5,1.0,"Cost C46= 3 (2+1) ");
	glFlush();/////8	
 delaypacket();
for(i=0;i<83;i=i+temp)//movement of data packet 5 to 6

	 {   glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(321.546056+i,216.438213 +i);glVertex2f(316.546056+i,220.0+i);glVertex2f(324.280894+i,226.773028+i);glVertex2f(329.826950+i,224.211241+i);
    glEnd();
    glFlush();
	
	delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(321.546056+i,216.438213 +i);glVertex2f(316.546056+i,220.0+i);glVertex2f(324.280894+i,226.773028+i);glVertex2f(329.826950+i,224.211241+i);
    glEnd();
    glFlush();
 }
glColor3f(1.0,1.0,1.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 5 to destination node 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,98.5,1.0,"5 -> 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,86.5,1.0,"Cost C56= 2  ");
	glFlush();//8
	delay();
	delay();
glColor3f(0.0,0.0,0.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 5 to destination node 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,98.5,1.0,"5 -> 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,86.5,1.0,"Cost C56= 2  ");
	glFlush();//////9
}
   
void node1()
{


		float i,temp=0.3,temp1=0.3;
	
 for(i=0;i<170;i=i+temp) //movement of data packet from 1 to 3
	 {  
	 
		glColor3f(1,0,0);
		glBegin(GL_QUADS);
		glVertex2f(116+i,410.0);glVertex2f(116+i,415);glVertex2f(126+i,415);glVertex2f(126+i,410.0);
		glEnd();
		glFlush();
	
	delaypacket();

	
		glColor3f(0,0,0);
		glBegin(GL_QUADS);
		glVertex2f(116+i,410.0);glVertex2f(116+i,415);glVertex2f(126+i,415);glVertex2f(126+i,410.0);
		glEnd();
		glFlush();
 } 

for(i=0;i<90;i=i+temp)//movement of data packet 3 to 6

	 {   glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
         glEnd();
        glFlush();
	
	    delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
    glEnd();
    glFlush();
 }
glColor3f(1.0,1.0,1.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 1 to destination node 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,98.5,1.0,"1 -> 3 -> 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,86.5,1.0,"Cost C16= 3 (2+1) ");
	glFlush();////10
	delay();
	delay();
    glColor3f(0.0,0.0,0.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 1 to destination node 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,98.5,1.0,"1 -> 3 -> 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,86.5,1.0,"Cost C16= 3 (2+1) ");
	glFlush();//11

}

void node2()
{
	float i,temp=0.3,temp1=0.3;
	for(i=0;i<70;i=i+temp)//movement of data packet 2 to 4

	 {   glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(118.546056+i,224.13+i);glVertex2f(115.5+i,228.0+i);glVertex2f(123.26950+i,238.211241+i);glVertex2f(125.894+i,233.773028+i);
    glEnd();
    glFlush();
	
	delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(118.546056+i,224.13+i);glVertex2f(115.5+i,228.0+i);glVertex2f(123.26950+i,238.211241+i);glVertex2f(126.894+i,233.773028+i);
    glEnd();
    glFlush();
 }
for(i=0;i<65;i=i+temp)//movement of data packet 4 to 3

	 {   glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		glVertex2f(216.546056+i,328.03+i);glVertex2f(218.5+i,323.0+i);glVertex2f(227.894+i,335.773028+i);
		glVertex2f(225.26950+i,340.211241+i);
    glEnd();
    glFlush();
	
	delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 	glVertex2f(216.546056+i,328.03+i);glVertex2f(218.5+i,323.0+i);glVertex2f(227.894+i,335.773028+i);
		glVertex2f(225.26950+i,340.211241+i);
    glEnd();
    glFlush();
 }
for(i=0;i<90;i=i+temp)//movement of data packet 3 to 6

	 {   
		glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
			glEnd();
		glFlush();
	
	delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
    glEnd();
    glFlush();
 }

glColor3f(1.0,1.0,1.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 2 to destination node 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,98.5,1.0,"2 -> 4 -> 3 -> 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,86.5,1.0,"Cost C26= 4 (1+2+1) ");
	glFlush();//12
	delay();
	delay();
glColor3f(0.0,0.0,0.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 2 to destination node 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,98.5,1.0,"2 -> 4 -> 3 -> 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,86.5,1.0,"Cost C26= 4 (1+2+1) ");
	glFlush();//13
 }

void node3()
{
		float i,temp=0.3,temp1=0.3;

 for(i=0;i<90;i=i+temp)//movement of data packet 3 to 6

	 {   
		glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
			glEnd();
		glFlush();
	
	delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
    glEnd();
    glFlush();
 }

glColor3f(1.0,1.0,1.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 3 to destination node 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,98.5,1.0,"3 -> 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,86.5,1.0,"Cost C36= 1 ");
	glFlush();//14
	delay();
	delay();
glColor3f(0.0,0.0,0.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 3 to destination node 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,98.5,1.0,"3 -> 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,86.5,1.0,"Cost C36= 1 ");
	glFlush();//15
}
void node4()
{
	float i,temp=0.3,temp1=0.3;
	for(i=0;i<65;i=i+temp)//movement of data packet 4 to 3

	 {   glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		glVertex2f(216.546056+i,328.03+i);glVertex2f(218.5+i,323.0+i);glVertex2f(227.894+i,335.773028+i);
		glVertex2f(225.26950+i,340.211241+i);
    glEnd();
    glFlush();
	
	delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 	glVertex2f(216.546056+i,328.03+i);glVertex2f(218.5+i,323.0+i);glVertex2f(227.894+i,335.773028+i);
		glVertex2f(225.26950+i,340.211241+i);
    glEnd();
    glFlush();
 }
for(i=0;i<90;i=i+temp)//movement of data packet 3 to 6

	 {   
		glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
			glEnd();
		glFlush();
	
	delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(316+i,410.0-i);glVertex2f(323.546056+i,403.438213-i);glVertex2f(326.826950+i,407.211241-i);glVertex2f(319.280894+i,413.773028-i);
    glEnd();
    glFlush();
 }

glColor3f(1.0,1.0,1.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 4 to destination node 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,98.5,1.0,"4 -> 3 -> 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,86.5,1.0,"Cost C46= 3 (2+1) ");
	glFlush();////////////////////////////////

	delay();
	delay();
glColor3f(0.0,0.0,0.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 4 to destination node 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,98.5,1.0,"4 -> 3 -> 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,86.5,1.0,"Cost C26= 3 (2+1) ");
	glFlush();//16
}

void node5()
{
		float i,temp=0.3,temp1=0.3;
for(i=0;i<83;i=i+temp)//movement of data packet 5 to 6

	 {   glColor3f(1,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(321.546056+i,216.438213 +i);glVertex2f(316.546056+i,220.0+i);glVertex2f(324.280894+i,226.773028+i);glVertex2f(329.826950+i,224.211241+i);
    glEnd();
    glFlush();
	
	delaypacket();

	
        glColor3f(0,0,0);
		 glBegin(GL_QUADS);
		 glVertex2f(321.546056+i,216.438213 +i);glVertex2f(316.546056+i,220.0+i);glVertex2f(324.280894+i,226.773028+i);glVertex2f(329.826950+i,224.211241+i);
    glEnd();
    glFlush();
 }
glColor3f(1.0,1.0,1.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 5 to destination node 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,98.5,1.0,"5 -> 6");
	glColor3f(1.0,1.0,1.0);
	drawstring(160.5,86.5,1.0,"Cost C56= 2  ");
	glFlush();//17
	delay();
	delay();
glColor3f(0.0,0.0,0.0);
	drawstring(160.5,110.5,1.0,"Shortest path from Node 5 to destination node 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,98.5,1.0,"5 -> 6");
	glColor3f(0.0,0.0,0.0);
	drawstring(160.5,86.5,1.0,"Cost C56= 2  ");
	glFlush();//18
}

void title()												// to draw the starting screen
{
		
	setFont(GLUT_BITMAP_HELVETICA_18);


	glColor3f(1.0,1.0,1.0);
	drawstring(75.0,435.0,1.0,"* * * * *  GRAPHICAL IMPLEMENTATION OF BELLMAN-FORD ALGORITHM FOR SHORTEST PATH  * * * * *");
	
	glColor3f(1.0,1.0,1.0);
	drawstring(210.0,365.0,1.0,"SUBMITTED   BY");				
	
	glColor3f(0.0,1.0,1.0);
	drawstring(180.0,340.0,1.0,"");
	
	glColor3f(0.0,1.0,1.0);
	drawstring(180.0,320.0,1.0,"");
	
	glColor3f(1.0,1.0,1.0);
	drawstring(190.0,260.0,1.0,"UNDER THE GUIDANCE OF");
	
	glColor3f(0.0,1.0,1.0);
	drawstring(70.0,230.0,1.0," ");

		setFont(GLUT_BITMAP_HELVETICA_12);

	glColor3f(0.0,1.0,1.0);
	drawstring(135.0,230.0,1.0," ,");		
	
	glColor3f(0.0,1.0,1.0);
	drawstring(70.0,215.0,1.0,"  Lecturer, Dept of CS&E");

	glColor3f(0.0,1.0,1.0);
	drawstring(70.0,200.0,1.0,"  ");

	
	setFont(GLUT_BITMAP_HELVETICA_18);

	glColor3f(0.0,1.0,1.0);
	drawstring(280.0,230.0,1.0,"           ");
	setFont(GLUT_BITMAP_HELVETICA_12);

	glColor3f(0.0,1.0,1.0);
	drawstring(360.0,230.0,1.0,"           ,");		
	
	glColor3f(0.0,1.0,1.0);
	drawstring(285.0,215.0,1.0,"          ");

	glColor3f(0.0,1.0,1.0);
	drawstring(285.0,200.0,1.0,"          ");

    
	glFlush();
}

void draw1()
{

	shape();
	naming();
}


void keyboardinteraction(void)				// text for keyboard interaction

{

	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(0,135);
	glVertex2f(500,135);
	glVertex2f(500,0);
	glEnd();
	glFlush();


	glColor3f(1.0f,1.0f,1.0f);
	setFont(GLUT_BITMAP_HELVETICA_18);
	drawstring(360.0,130.0,1.0,"DO U WISH TO CONTINUE?");
	glColor3f(1.0f,1.0f,1.0f);
	drawstring(360.0,110.0,1.0,"PRESS  Y/N");
	glFlush();
}




void display(void)
{  

	glClear(GL_COLOR_BUFFER_BIT);
	title();
	delay();
	draw();
	text();
}



	

void mykeyboard(unsigned char key,int x,int y)
{
	if(key=='y' || key=='Y')
	{
		
		draw();
		text();
	}
	else if(key=='N' || key=='n')
	{
		exit(0);
	}
}
	




void myMouse(int btn, int state, int x, int y)
{

	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		x=x/2;
		y=(1000-y)/2.1;
		if ((x>=185 && x<=310) && (y>=405 && y<=425 ))// Demo menu
		
		{
		    draw1();
		    move();
			delay();
			keyboardinteraction();
		
		}
		
		if ((x>=185 && x<=310) && (y>=370 && y<=390 ))// 1 menu
		{
	
		draw1();
		node1();
		keyboardinteraction();
		 
		}
		if((x>=185 && x<=310) && (y>=330 && y<=355 ))  //  2 menu
		{
		draw1();
		node2();
		keyboardinteraction();	

		}
		if((x>=185 && x<=310) && (y>=295 && y<=320 ))  // 3 menu
		{
			draw1();
		node3();
		keyboardinteraction();
		}

		if((x>=185 && x<=310) && (y>=260 && y<=280 ))  // 4 menu
		{
		draw1();
		node4();
		keyboardinteraction();	
		}

		if((x>=185 && x<=310) && (y>=220 && y<=240 ))  // 5 menu
		{
		draw1();
		node5();
		keyboardinteraction();
		}

		if((x>=185 && x<=310) && (y>=185 && y<=210 ))  // exit menu
		{
			exit(0);
		}
		
	}
}


void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
  	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("Bellaman-Ford Algorithm");
    glutDisplayFunc(display);
	glutMouseFunc(myMouse);
	//glutMouseFunc(myMouse1);
//	glutKeyboardFunc(keytostart);
	glutKeyboardFunc(mykeyboard);
	
	myInit();
	glutMainLoop();
    

}
