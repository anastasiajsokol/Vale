#ifndef VALE_TILE_H
#define VALE_TILE_H

#include "type.h"

namespace tile {

enum flag_masks{walkable = 0b10000000};
enum values{grass = 0b10000000, flowers = 0b10000001, path = 0b10000010};

ubyte map[] = {grass, flowers, path};

};

#endif