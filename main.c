#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

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
                printf("[%c]", cells[i * height + j].character);
//            } else {
//                printf("[^]");
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
                cells[i * height + j].character = 0;
            }
        }
    }

    // atualiza células próximas às minas para apresentarem números quando forem mostradas
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(cells[i * height + j].value == mine) {
                continue;
            }
            // upper left
            if(((i - 1) > 0) && ((j - 1) > 0) && (cells[(i - 1) * height + (j - 1)].value == mine)) {
                cells[i * height + j].character += 1;
            }
            // upper middle
            if(((i - 1) > 0) && (cells[(i - 1) * height + j].value == mine)) {
                cells[i * height + j].character += 1;
            }
            // upper right
            if(((i - 1) > 0) && ((j + 1) < width) && (cells[(i - 1) * height + (j + 1)].value == mine)) {
                cells[i * height + j].character += 1;
            }
            // left
            if(((j - 1) > 0) && (cells[i * height + (j - 1)].value == mine)) {
                cells[i * height + j].character += 1;
            }
            // right
            if(((j + 1) < width) && (cells[i * height + (j + 1)].value == mine)) {
                cells[i * height + j].character += 1;
            }
            // lower left
            if(((i + 1) < height) && ((j - 1) > 0) && (cells[(i + 1) * height + (j - 1)].value == mine)) {
                cells[i * height + j].character += 1;
            }
            // lower middle
            if(((i + 1) < height) && (cells[(i + 1) * height + j].value == mine)) {
                cells[i * height + j].character += 1;
            }
            // lower right
            if(((i + 1) < height) && ((j + 1) < width) && (cells[(i + 1) * height + (j + 1)].value == mine)) {
                cells[i * height + j].character += 1;
            }
            if(cells[i * height + j].character > 0) {
                cells[i * height + j].character += '0';
            } else {
                cells[i * height + j].character = ' ';
            }
        }
    }
}

bool update_minefield(int height, int width, cell_t *cells) {
    int x = -1;
    int y = -1;
    bool passed = false;

    while(!passed) {
        printf("Digite as coordenadas desejadas:\n");
        printf("x: ");
        scanf("%d", &x);
        printf("y: ");
        scanf("%d", &y);
        printf("\n");
        if ((x < 0) || (x >= width) || (y < 0) || (y >= height)) {
            printf("As coordenadas devem estar dentro do grid do jogo (0 <= x <= %d e 0 <= y <= %d)\n", width, height);
        } else if(cells[y * HEIGHT + x].discovered == true) {
            printf("A coordenada inserida já foi descoberta, tente de novo.\n");
        } else {
            passed = true;
        }
    }
    cells[y * HEIGHT + x].discovered = true;

    return cells[y * HEIGHT + x].value == mine;
}

int main() {
    srand(time(0));

    bool lost = false;
    cell_t cells[HEIGHT][WIDTH];
    sample_cells(HEIGHT, WIDTH, &cells[0][0]);
    while(!lost) {
        draw_minefield(HEIGHT, WIDTH, &cells[0][0]);
        lost = update_minefield(HEIGHT, WIDTH, &cells[0][0]);
    }
    printf("Hello, World!\n");
    return 0;
}
