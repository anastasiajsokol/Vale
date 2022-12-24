#ifndef VALE_CHUNK_MANAGER
#define VALE_CHUNK_MANAGER

#include "type.h"
#include "tile.h"
#include "random.h"

namespace vale {

/*
class chunk_manager {
    private:
        struct chunk {
            ubyte map[4][4];

            chunk(){}

            chunk(vec2 seed){
                vrandom::seed = (seed.x & 0xF) | (seed.y << 4);
                for(ubyte i = 0; i < 4; ++i){
                    for(ubyte j = 0; j < 4; ++j){
                        map[i][j] = tile::map[vrandom::byte(0, 3)];
                    }
                }
            }
        };

        struct {
            chunk data[3][3];

            ubyte offset_x = 0;
            ubyte offset_y = 0;

            // tile.x and tile.y must both be in [0, 12)
            ubyte& operator [](const uvec2 &tile){
                // get chunk id (from 0 - 3)
                ubyte chunk_x = tile.x / 4;
                ubyte chunk_y = tile.y / 4;
                
                // tile tile id (from 0 - 4)
                ubyte sub_chunk_x = tile.x - chunk_x * 4;
                ubyte sub_chunk_y = tile.y - chunk_y * 4;
                
                // get real chunk index to account for circular grid design
                chunk_x = (chunk_x + offset_x) % 3;
                chunk_y = (chunk_y + offset_y) % 3;

                // return value at that point
                return data[chunk_x][chunk_y].map[sub_chunk_x][sub_chunk_y];
            }
        } map;
    public:
        chunk_manager(){
            for(int x = 0; x < 3; ++x){
                for(int y = 0; y < 3; ++y){
                    map.data[x][y] = chunk(vec2(x, y));
                }
            }
        }

        // tile.x and tile.y must both be in [0, 12)
        ubyte operator [](const uvec2 &tile){
            return map[tile];
        }
};
*/

class chunk_manager {
    private:
        ubyte map[12][12];

        void load_chunk(ubyte chunk_cordinate_x, ubyte chunk_cordinate_y){
            for(ubyte x = chunk_cordinate_x * 4, i = 0; i < 4; ++i, ++x){
                for(ubyte y = chunk_cordinate_y * 4, j = 0; j < 4; ++j, ++y){
                    map[x][y] = vrandom::rubyte() & 0b11;
                }
            }
        }

        void set_chunk(ubyte chunk_cordinate_x, ubyte chunk_cordinate_y, ubyte val){
            // real index
            chunk_cordinate_x *= 4;
            chunk_cordinate_y *= 4;
            
            // loop through ever (x, y) in chunk
            for(ubyte x = chunk_cordinate_x, xend = chunk_cordinate_x + 4; x < xend; ++x){
                for(ubyte y = chunk_cordinate_y, yend = chunk_cordinate_y + 4; y < yend; ++y){
                    map[x][y] = val;
                }
            }
        }

    public:
        chunk_manager(){
            set_chunk(0, 0, 3);
            /*
            for(ubyte i = 0; i < 3; ++i){
                for(ubyte j = 0; j < 3; ++j){
                    set_chunk(i, j, 3);
                }
            }
            set_chunk(1, 0, 2);
            //set_chunk(1, 2, 2);
            */
        }
        
        inline ubyte operator [](uvec2 pos){
            return map[pos.x][pos.y];
        }

        inline ubyte operator ()(ubyte x, ubyte y){
            return map[x][y];
        }
};

};

#endif