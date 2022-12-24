#ifndef VALE_SCENE
#define VALE_SCENE

#include <graphx.h>

#include "type.h"
#include "chunk_manager.h"

#include "../gfx/gfx.h"

namespace vale {

class Scene {
    private:
        chunk_manager map;

        gfx_sprite_t* tile_sprite_map[4] = {grass, grass, flowers, path};

    public:
        void draw(){
            for(int x = 0; x < 12; ++x){
                for(int y = 0; y < 12; ++y){
                    gfx_Sprite(tile_sprite_map[map[uvec2(x, y)] & 0xF], x * 40, y * 40 - 180);
                }
            }
        }
} scene;

};

#endif