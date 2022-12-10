//
// Created by henry on 10/12/22.
//

#ifndef CMINEFIELD_DEFINITIONS_H
#define CMINEFIELD_DEFINITIONS_H

struct position {
    int x;
    int y;
};
typedef struct position position_t;

enum celltype {field = 1, mine = -1};

struct cell {
    position_t pos;
    enum celltype value;
    char character;
    bool discovered;
};
typedef struct cell cell_t;

#endif //CMINEFIELD_DEFINITIONS_H
