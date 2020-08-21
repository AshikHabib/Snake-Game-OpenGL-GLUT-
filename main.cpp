#include <Gl/gl.h>
#include <Gl/glut.h>
#include <windows.h>
#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<mmsystem.h>

#include "Game.h"

#define Columns 50
#define Rows 50
#define FPS 10

bool GameScreen = false;
bool controlFlag = false;

int score=0;
int btnPosition = 1;
extern short SnakeDirection; //to excess from Game.cpp

bool GameOver=false;
void frontscreen();
void DispalyCallback();
void ReshapeCallBack(int,int);
void TimerCallBack(int);
void SpecialInput(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);


void drawstring(float x, float y, void *font, char* string)
{
  char *c;

  glRasterPos2f(x,y);
  for(c=string;*c!='\0';c++)
  {
      glutBitmapCharacter(font,*c);
  }

}

 void frontscreen(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    char buf[100]={0};
    if(btnPosition!=1)glColor3ub(246,171,171);
    else glColor3ub(246,19,19);
    glRectd(20,32,30,37);

    if(btnPosition!=2)glColor3ub(246,171,171);
    else glColor3ub(246,19,19);
    glRectd(20,25,30,30);

    if(btnPosition!=3)glColor3ub(246,171,171);
    else glColor3ub(246,19,19);
    glRectd(20,18,30,23);

    glColor3ub(236, 247, 0);
    sprintf(buf,"START");
    drawstring(23.5, 34,GLUT_BITMAP_TIMES_ROMAN_24,buf);

    glColor3ub(236, 247, 0);
    sprintf(buf,"CONTROLS");
    drawstring(23,27,GLUT_BITMAP_HELVETICA_18,buf);

    glColor3ub(236, 247, 0);
    sprintf(buf,"EXIT");
    drawstring(24, 20,GLUT_BITMAP_HELVETICA_18,buf);


    glPopMatrix();

    glutSwapBuffers();

    glFlush();
 }

void ControlScreen(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    char buf[100]={0};
    glColor3ub(236, 247, 0);
    sprintf(buf,"Press UP key to go Up");
    drawstring(19, 35,GLUT_BITMAP_TIMES_ROMAN_24,buf);

    glColor3ub(236, 247, 0);
    sprintf(buf,"Press DOWN key to go Down");
    drawstring(19,30,GLUT_BITMAP_HELVETICA_18,buf);

    glColor3ub(236, 247, 0);
    sprintf(buf,"Press RIGHT key to go Right");
    drawstring(19, 25,GLUT_BITMAP_HELVETICA_18,buf);
    glPopMatrix();
    glColor3ub(236, 247, 0);
    sprintf(buf,"Press LEFT key to go Left");
    drawstring(19, 20,GLUT_BITMAP_HELVETICA_18,buf);
    glPopMatrix();

    sprintf(buf,"Press ESC key to go exit");
    drawstring(19, 15,GLUT_BITMAP_HELVETICA_18,buf);
    glPopMatrix();

    glutSwapBuffers();

    glFlush();

}

void Init()
{
    glClearColor(0,0,0,1);
    InitGrid(Columns,Rows);
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(100,200);
    glutInitWindowSize(1000,800);
    glutCreateWindow("Snake Game!");

    glutDisplayFunc(DispalyCallback);

    glutReshapeFunc(ReshapeCallBack);

    glutTimerFunc(0,TimerCallBack,0);
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(keyboard);

    Init();
    Sound();
    glutMainLoop();

    return 0;
}

void DispalyCallback()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(!GameScreen && !controlFlag)
    {
        frontscreen();
    }
    else if(!GameScreen) ControlScreen();
    else
    {
        DrawFood();
        DrawSnake();

        char buf[100]={0};
        glColor3f(1.0,0.0,1.0);
        sprintf(buf,"Score: %d", score);
        drawstring(2,49,GLUT_BITMAP_HELVETICA_18,buf);

        glutSwapBuffers();
        if(GameOver)
        {
            char _score[10];
            itoa(score,_score,10);
            char text[50]="Score:";
            strcat(text,_score);
           MessageBox(NULL,text,"Game Over!",0);
           exit(0);
        }
    }
}

void ReshapeCallBack(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,Columns,0,Rows,-1,1);  // screen size,ratio;
    glMatrixMode(GL_MODELVIEW);
}

void TimerCallBack(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,TimerCallBack,0);
}

void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        if(!GameScreen){
            btnPosition--;
            if(btnPosition<1) btnPosition=3;
        }
        else{
            if(SnakeDirection!=Down){
                SnakeDirection=Up;
                break;
            }
        }
    break;
    case GLUT_KEY_DOWN:
        if(!GameScreen){
            btnPosition++;
            if(btnPosition>3) btnPosition=1;
        }
        else{
            if(SnakeDirection!=Up){
                SnakeDirection=Down;
                break;
            }
        }
    break;
    case GLUT_KEY_LEFT:
        if(SnakeDirection!=Right){
            SnakeDirection=Left;
            break;
        }
        break;
    case GLUT_KEY_RIGHT:
        if(SnakeDirection!=Left){
            SnakeDirection=Right;
            break;
        }
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
	{
	//ESC
	case 27 :
		if(GameScreen) GameScreen = false;
		else if(controlFlag) controlFlag = false;
		else{
            exit(0);
		}
		break;

	// Enter
	case 13 :
        if(btnPosition==1) GameScreen = true;
        else if(btnPosition==2) controlFlag = true;
        else if(btnPosition==3) exit(0);
        break;

	}
	glutPostRedisplay();
}
