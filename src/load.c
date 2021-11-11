#include <load.h>

Block orientations[MAX_ORI][5];
bool  unique[MAX_ORI];

void rotate_normalise (Block* blocks, int size) {
    Block min = { 9, 9, 9 };
    for (int i=0; i < size; i++) {
        if (blocks[i].x < min.x) min.x = blocks[i].x;
        if (blocks[i].y < min.y) min.y = blocks[i].y;
        if (blocks[i].z < min.z) min.z = blocks[i].z;
    }
    for (int i=0; i < size; i++) {
        blocks[i].x -= min.x;
        blocks[i].y -= min.y;
        blocks[i].z -= min.z;
    }
}

void write_ori(int ori, int size, Block* blocks) {
    for (int i=0; i < size; i++) {
        orientations[ori][i].x = blocks[i].x;
        orientations[ori][i].y = blocks[i].y;
        orientations[ori][i].z = blocks[i].z;
    } 
}

void rotate (int ori, int dir, int size, Block* blocks) {
    write_ori(ori, size, blocks);
    int tmp;
    for (int i=0; i < size; i++) {
        switch (dir) {
            case NEXT:
                tmp = blocks[i].y;
                blocks[i].y = blocks[i].z;
                blocks[i].z = -tmp;
                break;
            case CLOCK:
                tmp = blocks[i].x;
                blocks[i].x = blocks[i].z;
                blocks[i].z = -tmp;
                break;
            case ANCLK:
                tmp = blocks[i].z;
                blocks[i].z = blocks[i].x;
                blocks[i].x = -tmp;
                break;
        }
    }
    rotate_normalise(blocks, size);
}

bool idential (int a, int b, int size) {
    Block* pa = orientations[a];
    Block* pb = orientations[b];
    int count = 0;
    for (int i=0; i < size; i++) {
        for (int j=0; j < size; j++) {
            if (pa[i].x == pb[j].x && pa[i].y == pb[j].y && pa[i].z == pb[j].z) {
                count++;
                break;
            }
        }
    }
    return count == size;
}

int unique_ori (int size) {
    int nunique = 0;

    for (int o=0; o < MAX_ORI; o++) {
        unique[o] = true;
        for (int i=0; i < o; i++) {
            if (idential(o, i, size)) {
                unique[o] = false;
                break;
            }
        }
        if (unique[o]) nunique++;
    }

    return nunique;
}

void create_piece (int id, int size, int nunique) {
    pieces[id].id = id;
    pieces[id].size = size;
    pieces[id].nunique = nunique;
    pieces[id].ori = (int*)malloc(nunique * sizeof(int));
    pieces[id].block = (Block**)malloc(nunique * sizeof(Block*));

    int count = 0;
    for (int ori=0; ori < MAX_ORI; ori++) {
        if (unique[ori]) {
            pieces[id].ori[count] = ori;
            pieces[id].block[count] = (Block*)malloc(size * sizeof(Block));
            for (int b=0; b < size; b++) {
                pieces[id].block[count][b].x = orientations[ori][b].x;
                pieces[id].block[count][b].y = orientations[ori][b].y;
                pieces[id].block[count][b].z = orientations[ori][b].z;
            }
            count++;
        }
    }
}

void create_ori(int id, int size, Block* blocks) {
    bool clk = true;
    for (int f=0; f < 6; f++) {
        for (int r=0; r < 3; r++) {
            if (clk) rotate(f*4+r, CLOCK, size, blocks);
            else     rotate(f*4+r, ANCLK, size, blocks);
        }
        rotate(f*4+3, NEXT, size, blocks);
        clk = !clk;
    }
    int nunique = unique_ori(size);
    create_piece(id, size, nunique);
}

void show_ori () {
    for (int i=0; i < MAX_ORI; i++) {
        printf("ORI: %d\t[ ", i);
        for (int b=0; b < 5; b++) {
            printf("%d%d%d ", orientations[i][b].x, orientations[i][b].y, orientations[i][b].z);
        }
        printf("]\n");
    }
}

void load(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    Block blocks[5];
    char x, y, z;
    int num = 0;
    int size = 0;

    do {
        x = (char)fgetc(fp);
        switch(x) {
            case EOF:
                create_ori(num, size+1, blocks);
                break;
            case '\n':
                create_ori(num, size+1, blocks);
                num++;
                size = 0;
                break;
            case ' ':
                size++;
                break;
            default:
                y = (char)fgetc(fp);
                z = (char)fgetc(fp);
                blocks[size].x = x - '0';
                blocks[size].y = y - '0';
                blocks[size].z = z - '0';

        }
    } while(x != EOF);
}
