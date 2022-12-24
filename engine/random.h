#ifndef VALE_RANDOM
#define VALE_RANDOM

#include "type.h"

namespace vrandom {

unsigned short seed = 0x4E7Cu;

ubyte rubyte(){
    unsigned short bit = ((seed >> 0) ^ (seed >> 2) ^ (seed >> 3) ^ (seed >> 5)) & 1;
    return seed = (seed >> 1) | (bit << 15);
}

ubyte rubyte(ubyte min, ubyte max){
    return (byte() % (max - min)) + min;
}

};

#endif