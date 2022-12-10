#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "definitions.h"
#include "ANSI-color-codes.h"

#define WIDTH 10
#define HEIGHT 10
#define N_MINES 3

void draw_minefield(int height, int width, cell_t *cells) {
    printf("  ");
    for(int j = 0; j < width; j++) {
        printf(" %d ", j);
    }
    printf("\n");
    for(int i = 0; i < height; i++) {
        printf("%d ", i);
        for(int j = 0; j < width; j++) {
            if(cells[i * height + j].discovered) {
                if(cells[i * height + j].value == mine) {
                    printf(RED "[%c]" , cells[i * height + j].character);
                } else {
                    printf("[%c]", cells[i * height + j].character);
                }
            } else {
                printf(GRN "[^]" reset);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void sample_cells(int height, int width, cell_t *cells, int n_mines, int *mine_positions) {
    for(int i = 0; i < n_mines; i++) {
        mine_positions[i] = (int)rand() % (height * width);
    }

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            cells[i * height + j].pos.x = i;
            cells[i * height + j].pos.y = j;
            cells[i * height + j].discovered = false;

            bool is_mine = false;
            for(int k = 0; k < n_mines; k++) {
                if (mine_positions[k] == (i * height + j)) {
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
            if(((i - 1) >= 0) && ((j - 1) >= 0) && (cells[(i - 1) * height + (j - 1)].value == mine)) {
                cells[i * height + j].character += 1;
            }
            // upper middle
            if(((i - 1) >= 0) && (cells[(i - 1) * height + j].value == mine)) {
                cells[i * height + j].character += 1;
            }
            // upper right
            if(((i - 1) >= 0) && ((j + 1) < width) && (cells[(i - 1) * height + (j + 1)].value == mine)) {
                cells[i * height + j].character += 1;
            }
            // left
            if(((j - 1) >= 0) && (cells[i * height + (j - 1)].value == mine)) {
                cells[i * height + j].character += 1;
            }
            // right
            if(((j + 1) < width) && (cells[i * height + (j + 1)].value == mine)) {
                cells[i * height + j].character += 1;
            }
            // lower left
            if(((i + 1) < height) && ((j - 1) >= 0) && (cells[(i + 1) * height + (j - 1)].value == mine)) {
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


void uncover_cells(int x, int y, int height, int width, cell_t *cells, int *count_uncovered) {
    cells[y * height + x].discovered = true;
    *count_uncovered += 1;

    if(cells[y * height + x].value == mine) {
        return;
    }
    // upper left
    if(((y - 1) >= 0) && ((x - 1) >= 0) && !(cells[(y - 1) * height + (x - 1)].discovered) && (cells[(y - 1) * height + (x - 1)].character == ' ')) {
        uncover_cells(x - 1, y - 1, height, width, cells, count_uncovered);
    }
    // upper middle
    if(((y - 1) >= 0) && !(cells[(y - 1) * height + x].discovered) && (cells[(y - 1) * height + x].character == ' ')) {
        uncover_cells(x, y - 1, height, width, cells, count_uncovered);
    }
    // upper right
    if(((y - 1) >= 0) && ((x + 1) < width) && !(cells[(y - 1) * height + (x + 1)].discovered) && (cells[(y - 1) * height + (x + 1)].character == ' ')) {
        uncover_cells(x + 1, y - 1, height, width, cells, count_uncovered);
    }
    // left
    if(((x - 1) >= 0) && !(cells[y * height + (x - 1)].discovered) && (cells[y * height + (x - 1)].character) == ' ') {
        uncover_cells(x - 1, y, height, width, cells, count_uncovered);
    }
    // right
    if(((x + 1) < width) && !(cells[y * height + (x + 1)].discovered) && (cells[y * height + (x + 1)].character == ' ')) {
        uncover_cells(x + 1, y, height, width, cells, count_uncovered);
    }
    // lower left
    if(((y + 1) < height) && ((x - 1) >= 0) && !(cells[(y + 1) * height + (x - 1)].discovered) && (cells[(y + 1) * height + (x - 1)].character == ' ')) {
        uncover_cells(x - 1, y + 1, height, width, cells, count_uncovered);
    }
    // lower middle
    if(((y + 1) < height) && !(cells[(y + 1) * height + x].discovered) && (cells[(y + 1) * height + x].character == ' ')) {
        uncover_cells(x, y + 1, height, width, cells, count_uncovered);
    }
    // lower right
    if(((y + 1) < height) && ((x + 1) < width) && !(cells[(y + 1) * height + (x + 1)].discovered) && (cells[(y + 1) * height + (x + 1)].character == ' ')) {
        uncover_cells(x + 1, y + 1, height, width, cells, count_uncovered);
    }
}

void update_minefield(
    int height, int width, cell_t *cells,
    int n_mines, int *mine_positions,
    int *count_uncovered,
    bool *victory, bool *defeat
) {

    int x = -1;
    int y = -1;
    bool valid_input = false;

    while(!valid_input) {
        printf("Digite as coordenadas desejadas:\n");
        printf("x: ");
        scanf("%d", &x);
        printf("y: ");
        scanf("%d", &y);
        printf("\n");
        if ((x < 0) || (x >= width) || (y < 0) || (y >= height)) {
            draw_minefield(height, width, cells);
            printf("As coordenadas devem estar dentro do grid do jogo (0 <= x <= %d e 0 <= y <= %d)\n", width, height);
        } else if(cells[y * height + x].discovered) {
            draw_minefield(height, width, cells);
            printf("A coordenada inserida já foi descoberta, tente de novo.\n");
        } else {
            valid_input = true;
        }
    }
    uncover_cells(x, y, height, width, cells, count_uncovered);
    if((height * width - *count_uncovered) == n_mines) {
        *victory = true;
    } else if(cells[y * height + x].value == mine) {
        *defeat = true;
    }
}

int main() {
    srand(time(0));

    bool defeat = false;
    bool victory = false;
    int count_uncovered = 0;
    cell_t cells[HEIGHT][WIDTH];
    int mines_positions[N_MINES];
    sample_cells(HEIGHT, WIDTH, &cells[0][0], N_MINES, &mines_positions[0]);
    while(!defeat && !victory) {
        draw_minefield(HEIGHT, WIDTH, &cells[0][0]);
        update_minefield(
        HEIGHT, WIDTH, &cells[0][0],
        N_MINES, &mines_positions[0],
        &count_uncovered,&victory, &defeat
        );
    }
    draw_minefield(HEIGHT, WIDTH, &cells[0][0]);
    if(victory) {
        printf("Você venceu! Parabéns!\n");
    } else {
        printf("Você perdeu! (acertou uma mina)\n");
    }
    return 0;
}

