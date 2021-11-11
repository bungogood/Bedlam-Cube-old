#include <cube.h>
#include <load.h>

int main(int argc, char** argv) {
    load("puzzles/pieces.txt");
    init_cube();
    show_cube();
    show_pieces();
    return 0;
}