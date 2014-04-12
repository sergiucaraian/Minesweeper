#include "grafica.h"
#include "logica.h"

// Variabile
int matrice[16][30];
int CELL_WIDTH_NR = 9;
int CELL_HEIGHT_NR = 9;
int DIFFICULTY = 1; // 1. Easy; 2.Medium; 3.Hard
int MINES = 10;
int matrice[16][30];
int GAME_STATE = 1; // 1. Menu, 2.Joc, 3.Optiuni, 4.Help, 5.Terminat
int FLAGS = 0;

void clear_point(int x, int y)
{
    if(matrice[x][y]==0)
        matrice[x][y]+=10;
    if(x>0 && y>0 && matrice[x-1][y-1]<=8)
    {
        int flag = 0;
        if(matrice[x-1][y-1]==0)
            flag = 1;
        matrice[x-1][y-1]+=10;
        if(flag==1)
            clear_point(x-1,y-1);
    }
    if(y>0 && matrice[x][y-1]<=8)
    {
        int flag = 0;
        if(matrice[x][y-1]==0)
            flag = 1;
        matrice[x][y-1]+=10;
        if(flag==1)
            clear_point(x,y-1);
    }
    if(x<CELL_HEIGHT_NR-1 && y>0 && matrice[x+1][y-1]<=8)
    {
        int flag = 0;
        if(matrice[x+1][y-1]==0)
            flag = 1;
        matrice[x+1][y-1]+=10;
        if(flag==1)
            clear_point(x+1,y-1);
    }
    if(x>0 && matrice[x-1][y]<=8)
    {
        int flag = 0;
        if(matrice[x-1][y]==0)
            flag = 1;
        matrice[x-1][y]+=10;
        if(flag==1)
            clear_point(x-1,y);
    }
    if(x<CELL_HEIGHT_NR-1 && matrice[x+1][y]<=8)
    {
        int flag = 0;
        if(matrice[x+1][y]==0)
            flag = 1;
        matrice[x+1][y]+=10;
        if(flag==1)
            clear_point(x+1,y);
    }
    if(x>0 && y<CELL_WIDTH_NR-1 && matrice[x-1][y+1]<=8)
    {
        int flag = 0;
        if(matrice[x-1][y+1]==0)
            flag = 1;
        matrice[x-1][y+1]+=10;
        if(flag==1)
            clear_point(x-1,y+1);
    }
    if(y<CELL_WIDTH_NR-1 && matrice[x][y+1]<=8)
    {
        int flag = 0;
        if(matrice[x][y+1]==0)
            flag = 1;
        matrice[x][y+1]+=10;
        if(flag==1)
            clear_point(x,y+1);
    }
    if(x<CELL_HEIGHT_NR-1 && y<CELL_WIDTH_NR-1 && matrice[x+1][y+1]<=8)
    {
        int flag = 0;
        if(matrice[x+1][y+1]==0)
            flag = 1;
        matrice[x+1][y+1]+=10;
        if(flag==1)
            clear_point(x+1,y+1);
    }
}

void left_click(int x, int y)
{
    if (GAME_STATE==1) // MENU
    {
        //Start Game
        if(x>=0.25* SCREEN_WIDTH && x<=0.75* SCREEN_WIDTH && y>=1*SCREEN_HEIGHT/9 && y<=2*SCREEN_HEIGHT/9)
        {
            build_matrix();
            GAME_STATE=2;
        }
        // Options
        if(x>=0.25* SCREEN_WIDTH && x<=0.75* SCREEN_WIDTH && y>=3*SCREEN_HEIGHT/9 && y<=4*SCREEN_HEIGHT/9)
            GAME_STATE=3;

        // Help
        if(x>=0.25* SCREEN_WIDTH && x<=0.75* SCREEN_WIDTH && y>=5*SCREEN_HEIGHT/9 && y<=6*SCREEN_HEIGHT/9)
            GAME_STATE=4;

        // Exit
        if(x>=0.25* SCREEN_WIDTH && x<=0.75* SCREEN_WIDTH && y>=7*SCREEN_HEIGHT/9 && y<=8*SCREEN_HEIGHT/9)
            glutLeaveMainLoop();
    }

    else if (GAME_STATE==2) //JOC
    {
        //Determinarea coordonatelor
        if(MINES==FLAGS)
        {
            show_map();
            GAME_STATE = 5;
        }
        int contor;
        for(contor=0; contor<=SCREEN_WIDTH; contor++)
            if(contor*(SCREEN_WIDTH/CELL_WIDTH_NR)<=x && (contor+1)*(SCREEN_WIDTH/CELL_WIDTH_NR)>x)
            {
                x = contor;
                contor = SCREEN_WIDTH+1;
            }

        for(contor=0; contor<=SCREEN_HEIGHT; contor++)
            if(contor*(SCREEN_HEIGHT/CELL_HEIGHT_NR)<=y && (contor+1)*(SCREEN_HEIGHT/CELL_HEIGHT_NR)>y)
            {
                y = contor;
                contor = SCREEN_HEIGHT+1;
            }
        int aux = x;
        x = y;
        y = aux;

        if(matrice[x][y]==0)
        {
            clear_point(x,y);
        }
        else if(matrice[x][y]>=1 && matrice[x][y]<=8)
            matrice[x][y]+=10;
        else if(matrice[x][y]==9)
        {
            matrice[x][y]=30;
            show_map();
            GAME_STATE=5;
        }
    }

    else if (GAME_STATE==3) //OPTIUNI
    {
        // Easy
        if(x>=0.25* SCREEN_WIDTH && x<=0.75* SCREEN_WIDTH && y>=1*SCREEN_HEIGHT/7 && y<=2*SCREEN_HEIGHT/7)
        {
            DIFFICULTY = 1;
            CELL_HEIGHT_NR = 9;
            CELL_WIDTH_NR = 9;
            MINES = 10;
            GAME_STATE = 1;
        }

        // Medium
        else if(x>=0.25* SCREEN_WIDTH && x<=0.75* SCREEN_WIDTH && y>=3*SCREEN_HEIGHT/7 && y<=4*SCREEN_HEIGHT/7)
        {
            DIFFICULTY = 2;
            CELL_HEIGHT_NR = 16;
            CELL_WIDTH_NR = 16;
            MINES = 40;
            GAME_STATE = 1;
        }

        // Hard
        else if(x>=0.25* SCREEN_WIDTH && x<=0.75* SCREEN_WIDTH && y>=5*SCREEN_HEIGHT/7 && y<=6*SCREEN_HEIGHT/7)
        {
            DIFFICULTY = 3;
            CELL_HEIGHT_NR = 16;
            CELL_WIDTH_NR = 30;
            MINES = 99;
            GAME_STATE = 1;
        }
    }
    else if (GAME_STATE==4) //HELP
    {
        GAME_STATE = 1;
    }
    else if (GAME_STATE==5) // TERMINAT
    {
        GAME_STATE=1;
    }
}

void right_click(int x, int y)
{
    if(GAME_STATE==2) //JOC
    {
        if(FLAGS==MINES)
        {
            show_map();
            GAME_STATE = 1;
        }
        //Determinarea coordonatelor
        int contor;
        for(contor=0; contor<=SCREEN_WIDTH; contor++)
            if(contor*(SCREEN_WIDTH/CELL_WIDTH_NR)<=x && (contor+1)*(SCREEN_WIDTH/CELL_WIDTH_NR)>x)
            {
                x = contor;
                contor = SCREEN_WIDTH+1;
            }

        for(contor=0; contor<=SCREEN_HEIGHT; contor++)
            if(contor*(SCREEN_HEIGHT/CELL_HEIGHT_NR)<=y && (contor+1)*(SCREEN_HEIGHT/CELL_HEIGHT_NR)>y)
            {
                y = contor;
                contor = SCREEN_HEIGHT+1;
            }
        int aux = x;
        x = y;
        y = aux;

        if(matrice[x][y]>=0 && matrice[x][y]<=9)
        {
            if(matrice[x][y]==9)
                FLAGS++;
            matrice[x][y]+=20;
        }
        else if(matrice[x][y]>=20 && matrice[x][y]<=29)
        {
            if(matrice[x][y]==29)
                FLAGS--;
            matrice[x][y]-=20;
        }
    }
}

void middle_click(int x, int y)
{
    if(GAME_STATE==2) //Joc
    {
        //Determinarea Coordonatelor
        int contor;
        for(contor=0; contor<=SCREEN_WIDTH; contor++)
            if(contor*(SCREEN_WIDTH/CELL_WIDTH_NR)<=x && (contor+1)*(SCREEN_WIDTH/CELL_WIDTH_NR)>x)
            {
                x = contor;
                contor = SCREEN_WIDTH+1;
            }

        for(contor=0; contor<=SCREEN_HEIGHT; contor++)
            if(contor*(SCREEN_HEIGHT/CELL_HEIGHT_NR)<=y && (contor+1)*(SCREEN_HEIGHT/CELL_HEIGHT_NR)>y)
            {
                y = contor;
                contor = SCREEN_HEIGHT+1;
            }
        int aux = x;
        x = y;
        y = aux;

        if(matrice[x][y]>=10 && matrice[x][y]<=18)
        {
            int gresit = 0, g[8] = {0,0,0,0,0,0,0,0};
            contor = 0;
            if(x>0 && y>0 && matrice[x-1][y-1]>=20 && matrice[x-1][y-1]<=29)
            {
                contor++;
                if(matrice[x-1][y-1]!=29)
                 {
                     g[0]=1;
                     gresit=1;
                 }
            }
            if(y>0 && matrice[x][y-1]>=20 && matrice[x][y-1]<=29)
            {
                contor++;
                if(matrice[x][y-1]!=29)
                {
                    g[1]=1;
                    gresit=1;
                }
            }
            if(x<CELL_HEIGHT_NR-1 && y>0 && matrice[x+1][y-1]>=20 && matrice[x+1][y-1]<=29)
            {
                contor++;
                if(matrice[x+1][y-1]!=29)
                {
                    g[2]=1;
                    gresit=1;
                }
            }
            if(x>0 && matrice[x-1][y]>=20 && matrice[x-1][y]<=29)
            {
                contor++;
                if(matrice[x-1][y]!=29)
                {
                    g[3]=1;
                    gresit=1;
                }
            }
            if(x<CELL_HEIGHT_NR-1 && matrice[x+1][y]>=20 && matrice[x+1][y]<=29)
            {
                contor++;
                if(matrice[x+1][y]!=29)
                {
                    g[4]=1;
                    gresit=1;
                }
            }
            if(x>0 && y<CELL_WIDTH_NR-1 && matrice[x-1][y+1]>=20 && matrice[x-1][y+1]<=29)
            {
                contor++;
                if(matrice[x-1][y+1]!=29)
                {
                    g[5]=1;
                    gresit=1;
                }
            }
            if(y<CELL_WIDTH_NR-1 && matrice[x][y+1]>=20 && matrice[x][y+1]<=29)
            {
                contor++;
                if(matrice[x][y+1]!=29)
                {
                    g[6]=1;
                    gresit=1;
                }
            }
            if(x<CELL_HEIGHT_NR-1 && y<CELL_WIDTH_NR-1 && matrice[x+1][y+1]>=20 && matrice[x+1][y+1]<=29)
            {
                contor++;
                if(matrice[x+1][y+1]!=29)
                {
                    g[7]=1;
                    gresit=1;
                }
            }

            if (contor+10 == matrice[x][y])
            {
                if(gresit)
                {
                    if(g[0]==1)
                        matrice[x-1][y-1]=30;
                    if(g[1]==1)
                        matrice[x][y-1]=30;
                    if(g[2]==1)
                        matrice[x+1][y-1]=30;
                    if(g[3]==1)
                        matrice[x-1][y]=30;
                    if(g[4]==1)
                        matrice[x+1][y]=30;
                    if(g[5]==1)
                        matrice[x-1][y+1]=30;
                    if(g[6]==1)
                        matrice[x][y+1]=30;
                    if(g[7]==1)
                        matrice[x+1][y+1]=30;

                    show_map();
                    GAME_STATE=5;
                }
                else
                {
                    if(x>0 && y>0 && matrice[x-1][y-1]>=0 && matrice[x-1][y-1]<=8)
                    {
                        matrice[x-1][y-1]+=10;
                        if(matrice[x-1][y-1]==10)
                            clear_point(x-1,y-1);
                    }
                    if(y>0 && matrice[x][y-1]>=0 && matrice[x][y-1]<=8)
                    {
                        matrice[x][y-1]+=10;
                        if(matrice[x][y-1]==10)
                            clear_point(x,y-1);
                    }
                    if(x<CELL_HEIGHT_NR-1 && y>0 && matrice[x+1][y-1]>=0 && matrice[x+1][y-1]<=8)
                    {
                        matrice[x+1][y-1]+=10;
                        if(matrice[x+1][y-1]==10)
                            clear_point(x+1,y-1);
                    }
                    if(x>0 && matrice[x-1][y]>=0 && matrice[x-1][y]<=8)
                    {
                        matrice[x-1][y]+=10;
                        if(matrice[x-1][y]==10)
                            clear_point(x-1,y);
                    }
                    if(x<CELL_HEIGHT_NR-1 && matrice[x+1][y]>=0 && matrice[x+1][y]<=8)
                    {
                        matrice[x+1][y]+=10;
                        if(matrice[x+1][y]==10)
                            clear_point(x+1,y);
                    }
                    if(x>0 && y<CELL_WIDTH_NR-1 && matrice[x-1][y+1]>=0 && matrice[x-1][y+1]<=8)
                    {
                        matrice[x-1][y+1]+=10;
                        if(matrice[x-1][y+1]==10)
                            clear_point(x-1,y+1);
                    }
                    if(y<CELL_WIDTH_NR-1 && matrice[x][y+1]>=0 && matrice[x][y+1]<=8)
                    {
                        matrice[x][y+1]+=10;
                        if(matrice[x][y+1]==10)
                            clear_point(x,y+1);
                    }
                    if(x<CELL_HEIGHT_NR-1 && y<CELL_WIDTH_NR-1 && matrice[x+1][y+1]>=0 && matrice[x+1][y+1]<=8)
                    {
                        matrice[x+1][y+1]+=10;
                        if(matrice[x+1][y+1]==10)
                            clear_point(x+1,y+1);
                    }
                }
            }
        }
    }
}

void user_input(int button, int state, int x, int y)
{
    if(state==GLUT_UP)
    {
        if(button==GLUT_LEFT_BUTTON)
        {
            left_click(x,y);
        }
        else if(button==GLUT_RIGHT_BUTTON)
        {
            right_click(x,y);
        }
        else if(button==GLUT_MIDDLE_BUTTON)
        {
            middle_click(x,y);
        }
    }
}


void build_matrix()
{
    int i,j;
    srand(time(0));
    for(i=0; i<CELL_HEIGHT_NR; ++i)
        for(j=0; j<CELL_WIDTH_NR; ++j)
            matrice[i][j]=0;

    FLAGS = 0;

    for(i=0; i<MINES; ++i)
    {
        int x, y;
        do
        {
            x = rand() % CELL_HEIGHT_NR;
            y = rand() % CELL_WIDTH_NR;
        } while(matrice[x][y]==9);
        matrice[x][y]=9;
    }

    for(i=0; i<CELL_HEIGHT_NR; ++i)
        for(j=0; j<CELL_WIDTH_NR; ++j)
        {
            if(matrice[i][j]!=9)
            {
                if(i>0 && j>0 && matrice[i-1][j-1]==9)
                    matrice[i][j]+=1;
                if(j>0 && matrice[i][j-1]==9)
                    matrice[i][j]+=1;
                if(i<CELL_HEIGHT_NR-1 && j>0 && matrice[i+1][j-1]==9)
                    matrice[i][j]+=1;
                if(i>0 && matrice[i-1][j]==9)
                    matrice[i][j]+=1;
                if(i<CELL_HEIGHT_NR-1 && matrice[i+1][j]==9)
                    matrice[i][j]+=1;
                if(i>0 && j<CELL_WIDTH_NR-1 && matrice[i-1][j+1]==9)
                    matrice[i][j]+=1;
                if(j<CELL_WIDTH_NR-1 && matrice[i][j+1]==9)
                    matrice[i][j]+=1;
                if(i<CELL_HEIGHT_NR-1 && j<CELL_WIDTH_NR-1 && matrice[i+1][j+1]==9)
                    matrice[i][j]+=1;
            }
        }
}

void show_map()
{
    // Lista coduri:
    // 0-8 : Camp liber Nedescoperit
    // 9 : Bomba nedescoperita
    // 10-18: Camp liber Descoperit
    // 19 : Bomba Descoperita
    // 20-28 : Camp liber Steag
    // 29 : Bomba Steag
    // 30 : Bomba Explodata
    // 31 : Steag Gresit

    int i, j;
    for(i=0; i<CELL_HEIGHT_NR; ++i)
        for(j=0; j<CELL_WIDTH_NR; ++j)
            if(matrice[i][j]<=9)
                matrice[i][j]+=10;
            else if(matrice[i][j]<=28 && matrice[i][j]>=20)
                matrice[i][j]=31;
}
