#pragma once
#include <cstdlib>

#define NUMBER_OF_DIRECTIONS 4

class Position {
public:
    enum {
        UP,
        RIGHT,
        DOWN,
        LEFT,
        STAY
    };
    int y, x;
    static int getDirection() {
        switch (rand() % NUMBER_OF_DIRECTIONS) {
        case 0:
            return UP;
        case 1:
            return LEFT;
        case 2:
            return DOWN;
        case 3:
            return RIGHT;
        }
    }
};

