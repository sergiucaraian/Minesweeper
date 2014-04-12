#ifndef LOGICA_H
#define LOGICA_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Variabile si Matrici
extern int CELL_WIDTH_NR;
extern int CELL_HEIGHT_NR;
extern int DIFFICULTY; // 1. Easy; 2.Medium; 3.Hard
extern int MINES;
extern int matrice[16][30];
extern int GAME_STATE; // 1. Menu, 2.Joc, 3.Optiuni, 4.Help, 5.Terminat

// Input
void user_input(int button, int state, int x, int y);

#endif // LOGICA_H
