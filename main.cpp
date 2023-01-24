#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <time.h>

#include "engine/message_bus.h"
#include "engine/work_queue.h"
#include "engine/scene.h"

#include "gfx/gfx.h"

int main(){
    // comment
    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(0);

    clock_t old = clock();

    do {
        // game logic
        kb_Scan();

        uint time = clock();
        uint fps = CLOCKS_PER_SEC / (time - old);
        old = time;

        // render logic
        vale::scene.draw();

        gfx_SetTextBGColor(1);
        gfx_SetTextFGColor(0);
        gfx_SetTextXY(0, 0);
        gfx_PrintUInt(fps, 3);
        
        gfx_SwapDraw();
    } while(kb_Data[1] != kb_2nd);
    
    gfx_End();
    return 0;
}
