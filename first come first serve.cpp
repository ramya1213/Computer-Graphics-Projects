#include<iostream>
#include<glut.h>
using namespace std;
struct process
{
int bt,at,pno,st,ct;
char name;
};
process p[5];
int one=1,np=1,n=0,att,index,btt,btotal=0,keypa=1,same[8];
float basic=36.0;
float col[5][3]={{.94,.90,.55},{.48,.41,.93},{1,.6,.2},{.5,1.0,0.0},{1,.84,.0}};
void delay()
{
for(int i=0;i<35000;i++)
for(int j=0;j<5000;j++);
}
void delay2()
{
for(int i=0;i<35000;i++)
for(int j=0;j<10000;j++);
}
void reshape(int w,int h)
{
glViewport(0, 0, w, h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
keypa=1;
}
void init()
{
glClearColor(.07,.07,.07,0.0);
/*glClearColor(.41,.41,.41,0.0);*/
/*glClearColor(0,0,0,0);*/
glColor3f(0.0,0.87,.803);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluOrtho2D(0,1000,0,400);
for(int i=0;i<=7;i++)
same[i]=1;
}//Initialiasation
void mouse(int bt,int st,int x,int y)
{
if(bt==GLUT_LEFT_BUTTON && st==GLUT_DOWN)
cout<<"\n"<<x<<"\n"<<400-y;
}
void strin(char *p,int n,GLint x,GLint y)
{
glRasterPos2f(x,y);
for(int i=0;i<n;i++)
    glutBitmapCharacter( GLUT_BITMAP_8_BY_13 , p[i] );
}//prints string
void constr()
{
int p=15,q=265;
glColor3f(1,.6,.2);
strin("Constraints On Input:",21,p,q);
strin("_____________________",21,p,q-4);
strin("1.Number of processes limited to 5.",35,p,q-(30*1));
strin("2.All processes must arrive before 7sec.",40,p,q-(30*2));
strin("3.Two processes cannot have same Arrival Time.",46,p,q-(30*3));
strin("4.Burst Time must be less than or equal to 5.",45,p,q-(30*4));
glColor3f(.5,1.0,0.0);
strin("PRESS E or e TO RUN PROGRAM FOR STATIC INPUT",44,15,320);
    strin("PRESS R or r TO RESET THE PROGRAM",33,15,300);
glColor3f(0.0,0.87,.803);
strin("FCFS",4,5,25);
}
void backgrnp()
{
strin("ENTER THE NUMBER OF PROCESSES:",30,15,375);
constr();
glFlush();
}//background for number of processes
void backgrat()
{
strin("ENTER THE ARRIVAL TIME OF PROCESSES:",35,15,375);
constr();
glFlush();
}//background for getting arrival time
void backgrbt()
{
strin("ENTER THE BRUST TIME OF PROCESSES:",33,15,375);
constr();
glFlush();
}//background for getting brust time
void pro()
{
int j;
char a;
for( j=0;j<n;j++)
{
a='0'+p[j].at;
strin(&a,1,175,378-(25*(j+2)));
a='0'+p[j].bt;
strin(&a,1,265,378-(25*(j+2)));
}
}
void s(int &a,int &b)
{
int te;
te=a;
a=b;
b=te;
}
void c(char &a,char &b)
{
char te;
te=a;
a=b;
b=te;
}
void swap(int x,int y)
{
s(p[x].at,p[y].at);
s(p[x].bt,p[y].bt);
c(p[x].name,p[y].name);
s(p[x].pno,p[y].pno);
}
void sort()
{
int i,j;
for(i=0;i<n;i++)
for(j=0;j<n-1;j++)
if(p[j].at>p[j+1].at)
{
swap(j,j+1);
}
}
void drawrec(int p,int q,int r, int s)
{
glBegin(GL_POLYGON);
glVertex2f(p,q);
glVertex2f(p,s);
glVertex2f(r,s);
glVertex2f(r,q);
glEnd();
}
void drawloop(int p,int q,int r, int s)
{
glBegin(GL_LINE_LOOP);
glVertex2f(p,q);
glVertex2f(p,s);
glVertex2f(r,s);
glVertex2f(r,q);
glEnd();
}
void setcst()
{
for(int i=0;i<n;i++)
{
if(i==0)
{
p[i].ct=p[i].bt+p[i].at;
p[i].st=p[i].at;
}
else if(p[i].at<p[i-1].ct)
{
p[i].ct=p[i].bt+p[i-1].ct;
p[i].st=p[i-1].ct;
}
else
{
p[i].ct=p[i].at+p[i].bt;
p[i].st=p[i].at;
}
}
}
void drawscale()
{
int i,j;
char a;
glLineWidth(2.0);
glBegin(GL_LINES);
glVertex2i(30,145);
glVertex2i(931,145);
for(i=1;i<=25;i++)
{
glVertex2f(30+basic*i,145);
glVertex2f(30+basic*i,141);
}
glEnd();
for(i=0,j=0;i<=25;i++)
{
if(i<10)
{
a='0'+i;
strin(&a,1,27+basic*i,147);
}
else if(i>9 && i<20)
{
j=1;
a='0'+j;
strin(&a,1,24+basic*i,147);
a='0'+(i%10);
strin(&a,1,32+basic*i,147);
}
else
{
j=2;
a='0'+j;
strin(&a,1,24+basic*i,147);
a='0'+(i%10);
strin(&a,1,32+basic*i,147);
}
}
glFlush();
}
void arri(int po)
{
for(int i=0;i<n;i++)
{
if(p[i].at<=p[po].ct)
{
glColor3fv(col[i]);
strin("P",1,30+36*p[i].at-8,173);
strin(&p[i].name,1,30+36*p[i].at,173);
glBegin(GL_LINES);
glVertex2i(30+36*p[i].at,170);
glVertex2i(30+36*p[i].at,160);
glVertex2i(30+36*p[i].at+2,163);
glVertex2i(30+36*p[i].at,160);
glVertex2i(30+36*p[i].at-2,163);
glVertex2i(30+36*p[i].at,160);
glEnd();
}
}
glFlush();
glColor3f(0.0,0.87,.803);
}
void prinum(int x,int y,float num)
{
int r=(int)num,q=(((int)(num*10))%10),p=(((int)(num*100))%10);
char a;
a='0'+r;
strin(&a,1,x,y);
strin(".",1,x+8,y);
a='0'+q;
strin(&a,1,x+16,y);
a='0'+p;
strin(&a,1,x+24,y);
glFlush();
}
void avg()
{
float awt,atat;
int ata=0,wt=0;
for(int i=0;i<n;i++)
{
wt+=(p[i].st-p[i].at);
ata+=(p[i].ct-p[i].st);
}
awt=(float)wt/n;
atat=(float)ata/n;
strin("Average Wait Time =",19,30,70);
strin("Average Turn Around Time =",26,30,45);
prinum(185,70,awt);
prinum(245,45,atat);
}
void gchart()
{
int i;
float me;
sort();
setcst();
drawscale();
basic=34;
strin("Gantt Chart",11,30,158+40);
strin("___________",11,30,156+40);
//arri();
for(i=0;i<n;i++)
{
glColor3fv(col[i]);
drawrec(30+p[i].st*36,100,30+p[i].ct*36,130);
glLineWidth(2.0);
glColor3f(0.0,0,0);
drawloop(30+p[i].st*36,100,30+p[i].ct*36,130);
glColor3fv(col[i]);
me=(30+p[i].st*36+30+p[i].ct*36)/2;
strin("P",1,me-8,88);
strin(&p[i].name,1,me,88);
arri(i);
glFlush();
delay2();
}
glLineWidth(1.0);
glColor3f(1,.84,.0);
avg();
}
void table()
{
int p,q,r,s,i;
char a;
keypa=0;
glColor3f(1,.84,.0);
p=30;
q=375-(25*(1+n));
s=375;
r=330;
glLineWidth(2.0);
glBegin(GL_LINE_LOOP);
glVertex2i(p,q);
glVertex2i(p,s);
glVertex2i(r,s);
glVertex2i(r,q);
glEnd();
glBegin(GL_LINES);
glVertex2i(130,s);
glVertex2i(130,q);
glVertex2i(233,s);
glVertex2i(233,q);
glVertex2i(p,350);
glVertex2i(r,350);
glEnd();
strin("Process",7,55,355);
strin("Arrival time",12,135,355);
strin("Burst time",10,240,355);
for( i=1;i<=n;i++)
{
strin("P",1,75,378-(25*(i+1)));
a='0'+i;
strin(&a,1,83,378-(25*(i+1)));
}
pro();
glFlush();
glLineWidth(1.0);
glColor3f(0.0,0.87,.803);
gchart();
}
void setname()
{
for(int i=0;i<n;i++)
{
p[i].name='0'+i+1;
p[i].pno=i+1;
}
}
void example()
{
p[0].at=1;
p[1].at=3;
p[2].at=2;
p[3].at=4;
p[4].at=5;
p[0].bt=3;
p[1].bt=4;
p[2].bt=5;
p[3].bt=1;
p[4].bt=3;
n=5;
glClear(GL_COLOR_BUFFER_BIT);
setname();
table();
}
void key1(unsigned char k,int x,int y)
{
char a=k;
int numb;
if(keypa==1)
{
if(isdigit(a) && one==1)
{
one=0;
numb=a-'0';
if(np==1)
{
if(numb<=5)
{
strin(&a,1,260,375);
backgrnp();

      np=0;
att=numb-1;
index=0;
n=numb;
delay();
glClear(GL_COLOR_BUFFER_BIT);
backgrat();

one=1;
setname();
}
else
{
glClear(GL_COLOR_BUFFER_BIT);
backgrnp();
glFlush();
glColor3f(1,1,1);
strin("ERROR",5,15,95);
strin("_____",5,15,93);
strin("Number of processes greater than 5 not allowed ",47,15,80);
glFlush();
delay();
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0,0.87,.803);
backgrnp();
glFlush();
delay();
glColor3f(1,1,1);
strin("ERROR",5,15,95);
strin("_____",5,15,93);
strin("Number of processes greater than 5 not allowed ",47,15,80);
glFlush();
one=1;
glColor3f(0.0,0.87,.803);
glColor3f(1,1,1);
strin("ERROR",5,15,95);
strin("_____",5,15,93);
strin("Number of processes greater than 5 not allowed ",47,15,80);
glFlush();
delay();
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0,0.87,.803);
backgrnp();
glFlush();
delay();
glColor3f(1,1,1);
strin("ERROR",5,15,95);
strin("_____",5,15,93);
strin("Number of processes greater than 5 not allowed ",47,15,80);
glFlush();
delay();
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0,0.87,.803);
backgrnp();

glFlush();
one=1;
glColor3f(0.0,0.87,.803);

}
}
else if(att>=0)
{
if(!same[numb] && numb<=7)
{
glColor3f(1,1,1);
strin("ERROR",5,15,95);
strin("_____",5,15,93);
strin("Arrival Time is same as previous process",40,15,80);
glColor3f(0.0,0.87,.803);
backgrat();
glFlush();
delay();
glClear(GL_COLOR_BUFFER_BIT);
backgrat();
glFlush();
delay();
glColor3f(1,1,1);
strin("ERROR",5,15,95);
strin("_____",5,15,93);
strin("Arrival Time is same as previous process",40,15,80);
glColor3f(0.0,0.87,.803);
backgrat();
glFlush();
delay();
glClear(GL_COLOR_BUFFER_BIT);
backgrat();
glFlush();
delay();
glColor3f(1,1,1);
strin("ERROR",5,15,95);
strin("_____",5,15,93);
strin("Arrival Time is same as previous process",40,15,80);
glColor3f(0.0,0.87,.803);
glFlush();
delay();
glClear(GL_COLOR_BUFFER_BIT);
backgrat();
glFlush();
delay();
one=1;
}
else if(numb<=7)
{
same[numb]=0;
strin(&a,1,300,375);
att--;
delay();
backgrat();

p[index++].at=numb;
one=1;
if(att<0)
{
delay();
glClear(GL_COLOR_BUFFER_BIT);
btt=n-1;
index=0;
backgrbt();


}
glClear(GL_COLOR_BUFFER_BIT);

}
else
{
glColor3f(1,1,1);
strin("ERROR",5,15,95);
strin("_____",5,15,93);
strin("Arrival time greater than 7 not allowed ",40,15,80);
glColor3f(0.0,0.87,.803);
backgrat();
glFlush();
delay();
glClear(GL_COLOR_BUFFER_BIT);
backgrat();
glFlush();
delay();
glColor3f(1,1,1);
strin("ERROR",5,15,95);
strin("_____",5,15,93);
strin("Arrival time greater than 7 not allowed ",40,15,80);
glColor3f(0.0,0.87,.803);
backgrat();
glFlush();
delay();
glClear(GL_COLOR_BUFFER_BIT);
backgrat();
glFlush();
delay();
glColor3f(1,1,1);
strin("ERROR",5,15,95);
strin("_____",5,15,93);
strin("Arrival time greater than 7 not allowed ",40,15,80);
glColor3f(0.0,0.87,.803);
glFlush();
delay();
glClear(GL_COLOR_BUFFER_BIT);
backgrat();
glFlush();
delay();
one=1;
}
}
else if(btt>=0)
{
if(numb<=5)
{
strin(&a,1,300,375);
delay();
btt--;
backgrbt();

p[index++].bt=numb;
btotal+=numb;
one=1;
glClear(GL_COLOR_BUFFER_BIT);
if(btt<0)
{
delay();
glClear(GL_COLOR_BUFFER_BIT);
glFlush();
table();
}
}
else
{
glColor3f(1,1,1);
strin("ERROR",5,15,95);
strin("_____",5,15,93);
strin("Burst time greater than 5 not allowed ",38,15,80);
glColor3f(0.0,0.87,.803);
backgrbt();
glFlush();
delay();
glClear(GL_COLOR_BUFFER_BIT);
backgrbt();
glFlush();
delay();
glColor3f(1,1,1);
strin("ERROR",5,15,95);
strin("_____",5,15,93);
strin("Burst time greater than 5 not allowed ",38,15,80);
glColor3f(0.0,0.87,.803);
backgrbt();
glFlush();
delay();
glClear(GL_COLOR_BUFFER_BIT);
backgrbt();
glFlush();
delay();
glColor3f(1,1,1);
strin("ERROR",5,15,95);
strin("_____",5,15,93);
strin("Burst time greater than 5 not allowed ",38,15,80);
glColor3f(0.0,0.87,.803);
backgrbt();
glFlush();
delay();
glClear(GL_COLOR_BUFFER_BIT);
backgrbt();
glFlush();
one=1;
}
}
 
}
else if(k=='R'||k=='r')
{
np=1;
glClear(GL_COLOR_BUFFER_BIT);
backgrnp();

}
else if(k=='e'||k=='E')
{
example();
np=0;
}
else
{
        glColor3f(1,1,1);
strin("ERROR",5,15,95);
strin("_____",5,15,93);
strin("Number not pressed",18,15,80);
glColor3f(0.0,0.87,.803);
if(np==1)
backgrnp();
else if(att==1)
backgrat();
else
backgrbt();
glFlush();
one=1;
}
}

}
void disp()
{
glClear(GL_COLOR_BUFFER_BIT);
strin("FCFS",4,5,25);
backgrnp();

glFlush();
}
void main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(1000,400);
glutCreateWindow("My move");
init();
glutDisplayFunc(disp);
glutKeyboardFunc(key1);
glutMouseFunc(mouse);
glutReshapeFunc(reshape);
glutMainLoop();
}