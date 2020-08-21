#include<GL/gl.h>
#include<GL/glut.h>
#include<ctime>
#include <windows.h>
#include <cstdlib>
#include <math.h>

#include "game.h"

# define PI           3.14159265358979323846

extern int score;

int GridX,GridY;
int snake_length=6;
int PositionX[60]={20,20,20,20,20,20},PositionY[60]={10,19,18,17,16};

bool Food=true;
int foodx,foody;

extern bool GameOver;

short SnakeDirection=Right;

void Unit(int,int);

void InitGrid(int x,int y)
{
    GridX=x;
    GridY=y;

}

void DrawFood()
{
    glColor3ub(245, 53, 11);
    GLfloat x=foodx+.5; GLfloat y=foody+.5; GLfloat radius =.5;
	int triangleAmount = 20;

	GLfloat twicePi = 2.0f * PI;
    int i;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	if(Food==true )
    {
        random(foodx,foody);
        Food=false;
    }
}

void DrawGrid()
{
    for(int x=0;x<GridX;x++)
    {
        for(int y=0;y<GridY;y++)
        {
            Unit(x,y);
        }
    }

}

void Unit(int x,int y)
{
    if(x==0 || y==0 ||x==GridX-1 ||y==GridY-1)
    {
        glLineWidth(3.0);
        glColor3f(1.0,0.0,0.0);
    }
    else
    {
        glLineWidth(1.0);
        glColor3f(1.0,1.0,1.0);
    }

    glBegin(GL_LINE_LOOP);

    glVertex2d(x,y);
    glVertex2d(x+1,y);
    glVertex2d(x+1,y+1);
    glVertex2d(x,y+1);

    glEnd();
}

void Sound()
{

    PlaySound("breakout.wav", NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);

}

void DrawSnake()
{
    for(int i=1; i<snake_length; i++){
        if((PositionX[0]==PositionX[i]) && (PositionY[0]==PositionY[i]))
            GameOver = true;
    }

    for(int i=snake_length-1;i>0;i--)
    {
        PositionX[i]=PositionX[i-1];
        PositionY[i]=PositionY[i-1];
    }
    if(SnakeDirection==Up)
        PositionY[0]++;
    else if(SnakeDirection==Down)
        PositionY[0]--;
    else if(SnakeDirection==Left)
        PositionX[0]--;
    else if(SnakeDirection==Right)
        PositionX[0]++;

        for(int i=0;i<snake_length;i++)
        {
            if(i==0)
                {glColor3f(0,1,0);}
            else
                {glColor3f(0,0,1);}

            glRectd(PositionX[i],PositionY[i],PositionX[i]+1,PositionY[i]+1);
            if(i!=0){
                    if(SnakeDirection==Left || SnakeDirection==Right){
                        glColor3ub(64, 162, 27);
                        glRectd(PositionX[i]+.4,PositionY[i],PositionX[i]+.6,PositionY[i]+1);
                    }
                    else if(SnakeDirection==Up || SnakeDirection==Down){
                        glColor3ub(64, 162, 27);
                        glRectd(PositionX[i],PositionY[i]+.4,PositionX[i]+1,PositionY[i]+.6);
                    }
            }
        }

     if(PositionX[0]==0 || PositionX[0]==GridX-1 || PositionY[0]==0 || PositionY[0]==GridY-1)
     {
        GameOver=true;
     }
     if(PositionX[0]==foodx && PositionY[0]==foody)
     {
         score+=10;
         snake_length++;
         if(snake_length>=Max)
           {
            snake_length=Max;}
         Food=true;
     }
}

void random(int &x,int &y)
{
    int _maxX=GridX-2;
    int _maxY=GridY-2;
    int _min=1;

    srand(time(NULL));

    x=_min+rand()%(_maxX-_min);
    y=_min+rand()%(_maxY-_min);

}
