#include "grafica.h"
#include "logica.h"

// Variabile
int SCREEN_WIDTH = 360;
int SCREEN_HEIGHT = 360;
int const SCREEN_FPS = 60;

int initGL()
{
    //Initialize clear color
    glClearColor( 0.75, 0.75, 0.75, 1.0f );

    //Set the viewport
    glViewport( 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT );

   //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0,-1,1);

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return 0;
    }

    return 1;
}

void render()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Draw
    draw();

    //Update screen
    glutSwapBuffers();
}

void change_size(int x, int y)
{
    SCREEN_HEIGHT = y;
    SCREEN_WIDTH = x;

    glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0,-1,1);
}

void draw()
{
    if (DIFFICULTY == 1)
    {
        SCREEN_HEIGHT = 360;
        SCREEN_WIDTH = 360;
        glutReshapeWindow(SCREEN_WIDTH,SCREEN_HEIGHT);
    }

    else if (DIFFICULTY == 2)
    {
        SCREEN_HEIGHT = 512;
        SCREEN_WIDTH = 512;
        glutReshapeWindow(SCREEN_WIDTH,SCREEN_HEIGHT);
    }

    else if (DIFFICULTY == 3)
    {
        SCREEN_HEIGHT = 512;
        SCREEN_WIDTH = 900;
        glutReshapeWindow(SCREEN_WIDTH,SCREEN_HEIGHT);
    }

    if(GAME_STATE==1) //Menu
    {
        int i;
        for(i=1; i<8; i+=2)
        {
            glColor3d(0,0,0);
            if(i==1)
            {
                glRasterPos2f(0.35*SCREEN_WIDTH,i*(SCREEN_HEIGHT/9)+0.65*(SCREEN_HEIGHT/9));
                glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"Start Game");
            }
            else if(i==3)
            {
                glRasterPos2f(0.35*SCREEN_WIDTH,i*(SCREEN_HEIGHT/9)+0.65*(SCREEN_HEIGHT/9));
                glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"Options");
            }
            else if(i==5)
            {
                glRasterPos2f(0.35*SCREEN_WIDTH,i*(SCREEN_HEIGHT/9)+0.65*(SCREEN_HEIGHT/9));
                glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"Help");
            }
            else if(i==7)
            {
                glRasterPos2f(0.35*SCREEN_WIDTH,i*(SCREEN_HEIGHT/9)+0.65*(SCREEN_HEIGHT/9));
                glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"Exit Game");
            }
        }
    }

    if(GAME_STATE==2) // Game
    {
        int i, j;

        for(i=0; i<CELL_HEIGHT_NR; ++i)
            for(j=0; j<CELL_WIDTH_NR; ++j)
            {
                if(matrice[i][j]<=9)
                    glColor3f(0.8,0.8,0.8);
                else if (matrice[i][j]>=20 && matrice[i][j]<=29)
                    glColor3d(0,128,0);
                else if(matrice[i][j]<=19 && matrice[i][j]>=10)
                    glColor3f(0.5,0.5,0.5);
                glBegin(GL_QUADS);
                glVertex2f( j*(SCREEN_WIDTH/CELL_WIDTH_NR), i*(SCREEN_HEIGHT/CELL_HEIGHT_NR));
                glVertex2f( (j+1)*(SCREEN_WIDTH/CELL_WIDTH_NR), i*(SCREEN_HEIGHT/CELL_HEIGHT_NR) );
                glVertex2f( (j+1)*(SCREEN_WIDTH/CELL_WIDTH_NR), (i+1)*(SCREEN_HEIGHT/CELL_HEIGHT_NR));
                glVertex2f( j*(SCREEN_WIDTH/CELL_WIDTH_NR), (i+1)*(SCREEN_HEIGHT/CELL_HEIGHT_NR ));
                glEnd();
                //Fonts
                if(matrice[i][j]>=11 && matrice[i][j]<=18)
                {
                    switch(matrice[i][j])
                    {
                        case 11: glColor3f(0,0,1); break;
                        case 12: glColor3d(0,250,154); break;
                        case 13: glColor3f(1,0,0); break;
                        case 14: glColor3d(25,25,112); break;
                        case 15: glColor3d(225,140,0); break;
                        case 16: glColor3d(102,205,170); break;
                        case 17: glColor3d(176,48,96); break;
                        case 18: glColor3d(225,215,0); break;
                        default:;
                    }
                    glRasterPos2f(j*(SCREEN_WIDTH/CELL_WIDTH_NR) + 0.3*(SCREEN_WIDTH/CELL_WIDTH_NR), i*(SCREEN_HEIGHT/CELL_HEIGHT_NR) + 0.7*(SCREEN_HEIGHT/CELL_HEIGHT_NR));
                    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, matrice[i][j]+38);
                }
            }


        //Draw Grid
        for(i=0; i<CELL_HEIGHT_NR; ++i)
        {
            glBegin(GL_LINE_LOOP);
            glColor3f(0.f, 0.f, 0.f);
            glVertex2f(0,i*(SCREEN_HEIGHT/CELL_HEIGHT_NR));
            glVertex2f(SCREEN_WIDTH,i*(SCREEN_HEIGHT/CELL_HEIGHT_NR));
            glEnd();
        }

        for(j=0; j<CELL_WIDTH_NR; ++j)
        {
            glBegin(GL_LINE_LOOP);
            glColor3f(0.f,0.f,0.f);
            glVertex2f(j*(SCREEN_WIDTH/CELL_WIDTH_NR),0);
            glVertex2f(j*(SCREEN_WIDTH/CELL_WIDTH_NR),SCREEN_HEIGHT);
            glEnd();
        }
    }

    if(GAME_STATE==3)//OPTIONS
    {
        int i;
        for(i=1; i<6; i+=2)
        {
            glColor3d(0,0,0);
            if(i==1)
            {
                glRasterPos2f(0.35*SCREEN_WIDTH,i*(SCREEN_HEIGHT/7)+0.65*(SCREEN_HEIGHT/7));
                glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"Easy");
            }
            else if(i==3)
            {
                glRasterPos2f(0.35*SCREEN_WIDTH,i*(SCREEN_HEIGHT/7)+0.65*(SCREEN_HEIGHT/7));
                glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"Medium");
            }
            else if(i==5)
            {
                glRasterPos2f(0.35*SCREEN_WIDTH,i*(SCREEN_HEIGHT/7)+0.65*(SCREEN_HEIGHT/7));
                glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"Hard");
            }
        }
    }

    if(GAME_STATE==4)//HELP
    {
        if(DIFFICULTY==1)
        {
            glRasterPos2d(15,30);
            glutBitmapString(GLUT_BITMAP_8_BY_13,"In a game of Minesweeper you must flag all");
            glRasterPos2d(15,50);
            glutBitmapString(GLUT_BITMAP_8_BY_13,"the mines in order to win.");
            glRasterPos2d(15,70);
            glutBitmapString(GLUT_BITMAP_8_BY_13,"However, if you reveal a mine you will");
            glRasterPos2d(15,90);
            glutBitmapString(GLUT_BITMAP_8_BY_13,"lose the game.");
            glRasterPos2d(15,160);
            glutBitmapString(GLUT_BITMAP_8_BY_13,"Left Click - Reveal Cell");
            glRasterPos2d(15,180);
            glutBitmapString(GLUT_BITMAP_8_BY_13,"Right Click - Flag Cell");
            glRasterPos2d(15,200);
            glutBitmapString(GLUT_BITMAP_8_BY_13,"Middle Click - Reveal Surrounding Cells");
        }

        if(DIFFICULTY==2)
        {
            glRasterPos2d(15,30);
            glutBitmapString(GLUT_BITMAP_9_BY_15,"In a game of Minesweeper you must flag all the mines");
            glRasterPos2d(15,55);
            glutBitmapString(GLUT_BITMAP_9_BY_15,"in order to win.");
            glRasterPos2d(15,80);
            glutBitmapString(GLUT_BITMAP_9_BY_15,"However, if you reveal a mine you will lose the game.");
            glRasterPos2d(15,160);
            glutBitmapString(GLUT_BITMAP_9_BY_15,"Left Click - Reveal Cell");
            glRasterPos2d(15,185);
            glutBitmapString(GLUT_BITMAP_9_BY_15,"Right Click - Flag Cell");
            glRasterPos2d(15,210);
            glutBitmapString(GLUT_BITMAP_9_BY_15,"Middle Click - Reveal Surrounding Cells");
        }

        if(DIFFICULTY==3)
        {
            glRasterPos2d(80,70);
            glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"In a game of Minesweeper you must flag all the mines in order to win.");
            glRasterPos2d(80,110);
            glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"However, if you reveal a mine you will lose the game.");
            glRasterPos2d(80,200);
            glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Left Click - Reveal Cell");
            glRasterPos2d(80,240);
            glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"Right Click - Flag Cell");
            glRasterPos2d(80,280);
            glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"Middle Click - Reveal Surrounding Cells");
        }
    }

    if(GAME_STATE==5)//TERMINAT
    {
       int i, j;

        for(i=0; i<CELL_HEIGHT_NR; ++i)
            for(j=0; j<CELL_WIDTH_NR; ++j)
            {
                if(matrice[i][j]<=19 && matrice[i][j]>=10)
                    glColor3f(0.5,0.5,0.5);
                else if(matrice[i][j]>=20 && matrice[i][j]<=28)
                    glColor3f(0.7,0.0,0.0);
                else if(matrice[i][j]==29)
                    glColor3d(0,125,0);
                else if(matrice[i][j]==30)
                    glColor3f(1.0,0.0,0.0);
                else if(matrice[i][j]==31)
                    glColor3f(0.7,0.0,0.0);
                glBegin(GL_QUADS);
                glVertex2f( j*(SCREEN_WIDTH/CELL_WIDTH_NR), i*(SCREEN_HEIGHT/CELL_HEIGHT_NR));
                glVertex2f( (j+1)*(SCREEN_WIDTH/CELL_WIDTH_NR), i*(SCREEN_HEIGHT/CELL_HEIGHT_NR) );
                glVertex2f( (j+1)*(SCREEN_WIDTH/CELL_WIDTH_NR), (i+1)*(SCREEN_HEIGHT/CELL_HEIGHT_NR));
                glVertex2f( j*(SCREEN_WIDTH/CELL_WIDTH_NR), (i+1)*(SCREEN_HEIGHT/CELL_HEIGHT_NR ));
                glEnd();

                if(matrice[i][j]>=11 && matrice[i][j]<=19)
                {
                    switch(matrice[i][j])
                    {
                        case 11: glColor3f(0,0,1); break;
                        case 12: glColor3d(0,250,154); break;
                        case 13: glColor3f(1,0,0); break;
                        case 14: glColor3d(25,25,112); break;
                        case 15: glColor3d(225,140,0); break;
                        case 16: glColor3d(102,205,170); break;
                        case 17: glColor3d(176,48,96); break;
                        case 18: glColor3d(225,215,0); break;
                        case 19: glColor3f(0,0,0); break;
                        default:;
                    }
                    glRasterPos2f(j*(SCREEN_WIDTH/CELL_WIDTH_NR) + 0.3*(SCREEN_WIDTH/CELL_WIDTH_NR), i*(SCREEN_HEIGHT/CELL_HEIGHT_NR) + 0.7*(SCREEN_HEIGHT/CELL_HEIGHT_NR));
                    if(matrice[i][j]==19)
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'#');
                    else glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, matrice[i][j]+38);
                }
            }

        //Draw Grid
        for(i=0; i<CELL_HEIGHT_NR; ++i)
        {
            glBegin(GL_LINE_LOOP);
            glColor3f(0.f, 0.f, 0.f);
            glVertex2f(0,i*(SCREEN_HEIGHT/CELL_HEIGHT_NR));
            glVertex2f(SCREEN_WIDTH,i*(SCREEN_HEIGHT/CELL_HEIGHT_NR));
            glEnd();
        }

        for(j=0; j<CELL_WIDTH_NR; ++j)
        {
            glBegin(GL_LINE_LOOP);
            glColor3f(0.f,0.f,0.f);
            glVertex2f(j*(SCREEN_WIDTH/CELL_WIDTH_NR),0);
            glVertex2f(j*(SCREEN_WIDTH/CELL_WIDTH_NR),SCREEN_HEIGHT);
            glEnd();
        }
    }
}

