#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BOX_SIZE    4
#define NUM_PIECES  13
#define MAX_ORI  24
#define EMPTY   -1

#define NEXT    0
#define CLOCK   1
#define ANCLK   2

typedef struct Block {
    int x,y,z;
} Block;

typedef struct Piece {
    int id, size, nunique;
    int* ori;
    Block** block;
} Piece;

int cube[BOX_SIZE+2][BOX_SIZE+2][BOX_SIZE+2];
Piece pieces[NUM_PIECES];

void init_cube ();

void place_piece (Piece* piece, int ori, Block* loc);
void remove_piece (Piece* piece, int ori, Block* loc);
bool isValid (Piece* piece, int ori, Block* loc);

void show_cube ();
void show_piece (int id);
void show_pieces ();