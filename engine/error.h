/**
 *  For performance reasons, never throw exceptions outside of critical meltdown
 *  !   if the error will leave the game uncorrupted, set flag so that emergency save can be made an available
**/

#ifndef VALE_ERROR_H
#define VALE_ERROR_H

#include "type.h"
#include <tice.h>
#include <graphx.h>
#include <time.h>

namespace error {

enum error_flag_bits{panic = 0, saveable = 0b10000000};

void exit_error(const char* message, ubyte code, ubyte flag){
    gfx_FillScreen(1);
    gfx_PrintStringXY(message, 5, 10);

    const char* hexcodes = "0123456789ABCDEF";
    char out[] = {'c', 'o', 'd', 'e', ':', ' ', hexcodes[code >> 4], hexcodes[code & 0xF], 0};
    gfx_PrintStringXY(out, 15, 30);

    out[0] = 'f';
    out[1] = 'l';
    out[2] = 'a';
    out[3] = 'g';

    out[6] = hexcodes[flag >> 4];
    out[7] = hexcodes[flag & 0xF];

    gfx_PrintStringXY(out, 15, 50);

    gfx_SwapDraw();

    uint wait = clock() + CLOCKS_PER_SEC;

    while(!os_GetCSC() || clock() < wait);

    gfx_End();
    
    exit(EXIT_FAILURE);
}

};

#endif