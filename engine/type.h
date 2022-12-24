#ifndef VALE_TYPE_H
#define VALE_TYPE_H

// due to calculator hardware, unsigned variables are prefered
typedef unsigned int uint;
typedef char byte;
typedef unsigned char ubyte;

typedef unsigned long clock_t;

// TODO: impliment the rest of the logic for vec2 and uvec2

struct vec2 {
    int x;
    int y;

    vec2() : x(0), y(0) {}
    vec2(int x, int y) : x(x), y(y) {}
};

struct uvec2 {
    uint x;
    uint y;

    uvec2() : x(0), y(0) {}
    uvec2(uint x, uint y) : x(x), y(y) {}
};

#endif