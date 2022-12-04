#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define WIDTH 10
#define HEIGHT 10
#define N_MINES 3

struct position {
    int x;
    int y;
};
typedef struct position position_t;

enum celltype {field = 1, flag = 0, mine = -1};

struct cell {
    position_t pos;
    enum celltype value;
    char character;
    bool discovered;
};
typedef struct cell cell_t;

void draw_minefield(int height, int width, cell_t *cells) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
//            if(cells[i * height + j].discovered) {
                if(cells[i * height + j].value == field) {
                    printf("[o]");
                } else if (cells[i * height + j].value == mine) {
                    printf("[x]");
                } else {  // is flag
                    printf("[!]");
                }
//            } else {
//                printf("[ ]");
//            }
        }
        printf("\n");
    }
    printf("\n");
}

void sample_cells(int height, int width, cell_t *cells) {
    int mines_positions[N_MINES];
    for(int i = 0; i < N_MINES; i++) {
        mines_positions[i] = (int)rand() % (height * width);
    }

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            cells[i * height + j].pos.x = i;
            cells[i * height + j].pos.y = j;
            cells[i * height + j].discovered = false;

            bool is_mine = false;
            for(int k = 0; k < N_MINES; k++) {
                if (mines_positions[k] == (i * height + j)) {
                    is_mine = true;
                    break;
                }
            }
            if(is_mine) {
                cells[i * height + j].value = mine;
                cells[i * height + j].character = 'x';
            } else {
                cells[i * height + j].value = field;
                cells[i * height + j].character = ' ';
            }
        }
    }
}

void update_minefield(int height, int width, cell_t *cells, int x, int y) {

}

int main() {
    cell_t cells[HEIGHT][WIDTH];
    sample_cells(HEIGHT, WIDTH, &cells[0][0]);
    draw_minefield(HEIGHT, WIDTH, &cells[0][0]);


    printf("Hello, World!\n");
    return 0;
}
