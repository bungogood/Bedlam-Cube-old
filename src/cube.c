#include <cube.h>

void init_cube() {
    for (int z=0; z < 4; z++) {
        for (int y=0; y < 4; y++) {
            for (int x=0; x < 4; x++) {
                cube[x][y][z] = EMPTY;
            }
        }
    }
}

void place_piece(Piece* piece, int ori, Block* loc) {
    for (int b=0; b < piece->size; b++) {
        cube[piece->block[ori][b].x + loc->x]
            [piece->block[ori][b].y + loc->y]
            [piece->block[ori][b].z + loc->z] = piece->id;
    }
}

void remove_piece(Piece* piece, int ori, Block* loc) {
    for (int b=0; b < piece->size; b++) {
        cube[piece->block[ori][b].x + loc->x]
            [piece->block[ori][b].y + loc->y]
            [piece->block[ori][b].z + loc->z] = EMPTY;
    }
}

bool isValid(Piece* piece, int ori, Block* loc) {
    for (int b=0; b < piece->size; b++) {
        if (cube[piece->block[ori][b].x + loc->x]
                [piece->block[ori][b].y + loc->y]
                [piece->block[ori][b].z + loc->z] != EMPTY) return false;
    }
    return true;
}

void show_cube () {
    for (int z=0; z < 4; z++) {
        for (int y=0; y < 4; y++) {
            for (int x=0; x < 4; x++) {
                printf("%d\t", cube[x][y][z]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void show_piece (int id) {
    Piece piece = pieces[id];
    printf("ID: %d\tsize: %d\tnunique: %d\n", piece.id, piece.size, piece.nunique);
    for (int i=0; i < piece.nunique; i++) {
        printf("ori: %d\t[ ", piece.ori[i]);
        for (int b=0; b < piece.size; b++) {
            printf("%d%d%d ", piece.block[i][b].x, piece.block[i][b].y, piece.block[i][b].z);
        }
        printf("]\n");
    }
}

void show_pieces () {
    for (int i=0; i < NUM_PIECES; i++) {
        show_piece(i);
    }
}
