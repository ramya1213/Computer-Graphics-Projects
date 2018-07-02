#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<stdlib.h>
#include<Windows.h>
#include<gl/GL.h>
#include<gl/glu.h>
#include<glut.h>
void renderscene()
{

glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0,0.3,0.0);

char c1[]="COMPUTER GRAPHICS PROJECT";
glRasterPos2f(600,375);
for(int i=0;c1[i]!='\0';i++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c1[i]);

char c2[]="NAME:";
glRasterPos2f(700.0,350.0);
for(i=0;c2[i]!='\0';i++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c2[i]);

char c3[]="COLLEGE:";
glRasterPos2f(700.0,325.0);
for(i=0;c3[i]!='\0';i++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c3[i]);

char c4[]="";
glRasterPos2f(700.0,300.0);
for(i=0;c4[i]!='\0';i++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c4[i]);

char c5[]="Press right button of mouse to get various options";
glRasterPos2f(300.0,200.0);
for(i=0;c5[i]!='\0';i++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c5[i]);
glFlush();
	
}


void init()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0f,0.0f,0.0f);
	glPointSize(0.8);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,2000.0,0.0,400.0);
}
struct node
{
	int info;
	struct node *rlink;
	struct node *llink;
};
typedef struct node *NODE;
static int count=0;
NODE head;
int h[100];
struct arr
{
	int p;
	int q;
}m[100];

NODE getnode()
{
	NODE temp;
	temp=(NODE)malloc(sizeof(struct node));
	if(temp==NULL)
	{
		printf("out of memory\n");
		exit(1);
	}
	return temp;
}
void disp()
{
	glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0,0.0,1.0);
char c[]="List is Empty";
glRasterPos2f(800.0,200.0);
for(int i=0;c[i]!='\0';i++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c[i]);
		glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2i(100,200);
	glVertex2i(100,225);
	glVertex2i(500,225);
	glVertex2i(500,200);
	glEnd();
	glFlush();
}
NODE display(NODE head)
{
	glClear(GL_COLOR_BUFFER_BIT);
	NODE temp;
	int i=0,k,j=0;
	temp=head->rlink;
	if(temp==head)
	{
		printf(" list is empty\n");
		disp();
			return head;
			
	}
	printf("elements are\n");
	
	while(temp!=head)
	{
		for(k=0;k<count;k++)
	  {
		  GLfloat x1=100,x2=150,x3=350,x4=400,x5=500,x6=480,x7=20,x9=0;
		h[j]=temp->info;
		printf("%d\n",h[j]);
		glColor3f(0.0,0.0,0.0);
char c[]="Info";
glRasterPos2f(220.0,230.0);
for(int a=0;c[a]!='\0';a++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,c[a]);
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_POLYGON);
	    glVertex2i(x2+k*400,200);
	    glVertex2i(x2+k*400,225);
	    glVertex2i(x3+k*400,225);
	    glVertex2i(x3+k*400,200);
	    glEnd();
		glColor3f(0.0,0.0,0.0);
char r[]="rlink";
glRasterPos2f(355.0,230.0);
for(int b=0;r[b]!='\0';b++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,r[b]);
		glColor3f(0.0,0.0,1.0);
	    glBegin(GL_POLYGON);
	    glVertex2i(x3+k*400,225);
	    glVertex2i(x3+k*400,200);
	    glVertex2i(x4+k*400,200);
	    glVertex2i(x4+k*400,225);
	    glEnd();
		glColor3f(0.0,0.0,0.0);
char s[]="llink";
glRasterPos2f(120.0,230.0);
for(int d=0;s[d]!='\0';d++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,s[d]);
		glColor3f(0.0,1.0,0.0);
		glBegin(GL_POLYGON);
	    glVertex2i(x1+k*400,225);
	    glVertex2i(x1+k*400,200);
	    glVertex2i(x2+k*400,200);
	    glVertex2i(x2+k*400,225);
	    glEnd();
		glColor3f(0.0,1.0,0.0);
	    glBegin(GL_LINES);
	    glVertex2i(x1+k*400,207);
	    glVertex2i(x9+k*400,207);
		glVertex2i(x9+k*400,207);
	    glVertex2i(x7+k*400,202);
	    glVertex2i(x9+k*400,207);
	    glVertex2i(x7+k*400,210);
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_LINES);
	    glVertex2i(x4+k*400,215);
	    glVertex2i(x5+k*400,215);
	    glVertex2i(x5+k*400,215);
	    glVertex2i(x6+k*400,210);
	    glVertex2i(x5+k*400,215);
	    glVertex2i(x6+k*400,219);
	    glEnd();
		m[i].p=h[j]/10;
		m[i].q=h[j]%10;
		m[i].p=m[i].p+48;
		m[i].q=m[i].q+48;
		int x8=225;
		glColor3f(0.0,0.0,0.0);
	    glRasterPos2i(x8+k*400,210);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,m[i].p);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,m[i].q);
		i++;
		j++;
		temp=temp->rlink;
		glFlush();	
		  }
 }
	return head;
}
NODE insertfront(NODE head,int item)
{
	NODE temp,cur;
	temp=getnode();
	temp->info=item;
	cur=head->rlink;
	head->rlink=temp;
	temp->llink=head;
	temp->rlink=cur;
	cur->llink=temp;
	return head;
	
}
NODE insertrear(NODE head,int item)
{
	NODE temp,cur;
	temp=getnode();
	temp->info=item;
	cur=head->llink;
	head->llink=temp;
	temp->rlink=head;
	temp->llink=cur;
	cur->rlink=temp;
	return head;
}
NODE insertleft(NODE head,int ele)
{
	int item;
	NODE temp,cur,pre;
	if(head->rlink==head)
	{
		printf("list is empty\n");
		count--;
		return head;
	}
	cur=head->rlink;
	while(cur!=head)
	{
		if(cur->info==ele)
			break;
			cur=cur->rlink;
	}
	if(cur==head)
		{
			printf("%d element not found\n",ele);
			count--;
	        return head;
	}
			printf("enter element to be inserted\n");
				scanf("%d",&item);
				pre=cur->llink;
				temp=getnode();
				temp->info=item;
				temp->llink=pre;
				temp->rlink=cur;
				cur->llink=temp;
				pre->rlink=temp;
				return head;
	
}
NODE insertright(NODE head,int ele)
{
	int item;
	glClear(GL_COLOR_BUFFER_BIT);
	NODE temp,cur,next;
	if(head->rlink==head)
	{
		printf("list is empty\n");
		count--;
		return head;
	}
	cur=head->rlink;
	while(cur!=head)
	{
		if(cur->info==ele)
		{
			printf("enter element to be inserted\n");
				scanf("%d",&item);
				next=cur->rlink;
				temp=getnode();
				temp->info=item;
				temp->llink=cur;
				temp->rlink=next;
				cur->rlink=temp;
				next->llink=temp;
				return head;
		}
		cur=cur->rlink;
	}
	printf("%d element not found\n",ele);
	count--;
	return head;
}
NODE deletfront(NODE head)
{
	NODE cur,next;
	if(head->rlink==head)
	{
		printf("list is empty\n");
		count++;
		return head;
	}
	cur=head->rlink;
	next=cur->rlink;
	head->rlink=next;
	next->llink=head;
	printf("node to b deleted is %d\n",cur->info);
	free(cur);
	return head;
}
NODE deletrear(NODE head)
{
	NODE cur,prev;
	if(head->llink==head)
	{
		printf("list is empty\n");
		count++;
		return head;
	}
	cur=head->llink;
	prev=cur->llink;
	head->llink=prev;
	prev->rlink=head;
	printf("node to b deleted is %d\n",cur->info);
	free(cur);
	return head;
}

NODE del(NODE head,int ele)
{
	NODE cur,next,pre;
	glClear(GL_COLOR_BUFFER_BIT);
	if(head->rlink==head)
	{
		printf("list is empty\n");
		count++;
		return head;
	}
	cur=head->rlink;
	while(cur!=head)
	{
		if(cur->info==ele)
			break;
		cur=cur->rlink;
	}
	if(cur==head)
	{
		printf("%d element not found\n",ele);
		count++;
	    return head;
	}
			pre=cur->llink;
			next=cur->rlink;
			printf("%d element found and deleted\n",ele);
			pre->rlink=next;
			next->llink=pre;
			free(cur);
			return head;
	
}


void top_menu(int option)
{
	int ele;
	switch(option)
	{
	case 1:
	
		printf("enter item to be inserted\n");
				scanf("%d",&ele);
				head=insertfront(head,ele);
				count++;
				display(head);
				break;
	case 2:
		printf("enter item to be inserted\n");
				scanf("%d",&ele);
				head=insertrear(head,ele);
				count++;
				display(head);
				break;
	case 3:
		printf("enter key to be searched\n");
			    scanf("%d",&ele);
			    head=insertleft(head,ele);
			    count++;
			    display(head);
			    break;
	case 4:
		printf("enter key to be searched\n");
			    scanf("%d",&ele);
			    head=insertright(head,ele);
			    count++;
			    display(head);
			    break;
	case 5:
		head=deletfront(head);
		count--;
		display(head);
		break;
	case 6:
		head=deletrear(head);
		count--;
		display(head);
		break;
	case  7:printf("enter key\n");
				scanf("%d",&ele);
				count--;
				head=del(head,ele);
				display(head);
				break;
	case 8:exit(0);
	}
}
void main(int argc,char**argv)
{
	head=getnode();
	head->rlink=head;
	head->llink=head;
	head->info=NULL;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(700,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Doubly Linked List");
	glutCreateMenu(top_menu);
	glutAddMenuEntry("InsertFront",1);
	glutAddMenuEntry("InsertRear",2);
	glutAddMenuEntry("InsertLeft",3);
	glutAddMenuEntry("InsertRight",4);
	glutAddMenuEntry("DeleteFront",5);
	glutAddMenuEntry("DeleteRear",6);
	glutAddMenuEntry("DeletSpecified",7);
	glutAddMenuEntry("Exit",8);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(renderscene);
	init();
glutMainLoop();
	
}









