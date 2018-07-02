#include<windows.h>
#include<gl.h>
#include<glut.h>
#include<stdio.h>
void *currentfont;
//char str[10];
int size,a[10],ch=1,max;


void setFont(void *font)
{
	currentfont=font;
}

void init(void)
{
	glClearColor(1,1,1,1);
	glColor3f(0,1,0);
	gluOrtho2D(0.0,640.0,0.0,480.0);
	setFont(GLUT_BITMAP_HELVETICA_18);
}


void drawstring(GLfloat x,GLfloat y,char *string)
{
    char *c;
	glRasterPos2f(x,y);
 
	for(c=string;*c!='\0';*c++)
	{
		glutBitmapCharacter(currentfont,*c);
	}
}

void delay()
{
	int i,j;
	for(i=0;i<100000;i++)
		for(j=0;j<5000;j++);
}

void draw_tab()
{
	int i,h,k;
	char s[20],*s1;
	for(i=0;i<size;i++)
	{
		h=50+i*50;
		k=100+i*50;
		glBegin(GL_LINE_LOOP);
			glColor3f(0,0,0);
			glVertex2i(h,50);
			glVertex2i(k,50);
			glVertex2i(k,100);
			glVertex2i(h,100);
		glEnd();
		s1=itoa(a[i],s,10);
		glColor3f(0,0,1);
		drawstring(h+25,75,s1);
		glColor3f(0,1,0);
		
		//delay();
	}

	
	delay();
	glFlush();
}

void bdraw_tab(int b[])
{
	int i,h,k;
	char s[20],*s1;
	for(i=0;i<size;i++)
	{
		h=50+i*50;
		k=100+i*50;
		glBegin(GL_LINE_LOOP);
			glColor3f(0,0,0);
			glVertex2i(h,250);
			glVertex2i(k,250);
			glVertex2i(k,300);
			glVertex2i(h,300);
		glEnd();
		s1=itoa(b[i],s,10);
		glColor3f(0,0,1);
		drawstring(h+25,275,s1);
		glColor3f(0,1,0);
		drawstring(50,350,"THE TEMPORARY BUCKET ARRAY bucket[ ]");
		//delay();
	}
	

	glFlush();
}


void myDisplay(void)
{
	int* buckets = new int[max];
	int i,j,k;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	drawstring(50,125,"INPUT ARRAY a[ ]");
	draw_tab();
	delay();
	max = a[0];
	
	for(i=0;i<size;i++)
        if(a[i]>max)
           max=a[i];

	for(j =0;j<=max;j++)
	{
		buckets[j]=0;
		
	}
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	bdraw_tab(buckets);
	draw_tab();
	drawstring(50,125,"INPUT ARRAY a[ ]");
	delay();
		
	for(i=0;i<size;i++)
	{
		++buckets[a[i]];
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		bdraw_tab(buckets);
		draw_tab();
		drawstring(50,125,"INPUT ARRAY a[ ]");
		delay();
	}
		
	for(i=0,j=0;j<=max;++j)
	{
		for(k=buckets[j];k>0;k--)
		{
			a[i++]=j;
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			bdraw_tab(buckets);
			draw_tab();
			delay();

		}
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		draw_tab();
		drawstring(50,125,"INPUT ARRAY a[ ]");
		delay();
	}
			
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	draw_tab();
	drawstring(50,200,"THE SORTED ARRAY IS");	
	delay();
}


void main(void)
{
	int i;
	printf("Enter the size of the array\n");
	scanf("%d",&size);
	printf("Enter the elements\n");
	for(i=0;i<size;i++)
	{
		scanf("%d",&a[i]);
	}
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1024.0,780.0);
	glutInitWindowPosition(0.0,0.0);
	glutCreateWindow("BUCKET SORT");
	glutDisplayFunc(myDisplay);
	init();
	glutMainLoop();
}