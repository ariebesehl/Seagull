/*** Copyright (C) 2020 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#ifndef SEAGULL_CORE_C_INCLUDED
#define SEAGULL_CORE_C_INCLUDED

#include "Seagull_Core.h"

void SGC_BufferFree(void) {
    ZTM8_Free(gCore.data.buffer0);
    gCore.data.buffer0 = NULL;
    gCore.data.current = NULL;
}
void SGC_BufferNew(void) {
    gCore.data.buffer0 = (ZT_U*)ZTM8_New(2 * gCore.data.length * sizeof(ZT_U));
    gCore.data.buffer1 = gCore.data.buffer0 + gCore.data.length;
    gCore.data.current = gCore.data.buffer0;
}
void SGC_Free(void) {
    SGC_BufferFree();
}
SGL_CORE* SGC_New(ZT_INDEX iWidth, ZT_INDEX iHeight) {
    ZT_INDEX lLength = iWidth * iHeight;
    ZTM8_Zero(&gCore, sizeof(gCore));
    gCore.stat.version = SGCORE_VERSION;
    gCore.counter.alive = 0;
    gCore.counter.iteration = 0;
    gCore.value.alive = SGCORE_CELL_ALIVE;
    gCore.value.vacant = SGCORE_CELL_EMPTY;
    gCore.dimension.x = iWidth;
    gCore.dimension.y = iHeight;
    gCore.data.length = lLength;
    gCore.data.current = NULL;
    gCore.data.buffer0 = NULL;
    gCore.data.buffer1 = NULL;
    SGC_BufferNew();
	return &gCore;
}

void SGC_Iterate(void) {
    gCore.counter.alive = 0;
    ZT_U* workPtr = (gCore.data.current != gCore.data.buffer1) ? gCore.data.buffer1 : gCore.data.buffer0;
    for (ZT_INDEX y = 0; y < gCore.dimension.y; y++) {
        for (ZT_INDEX x = 0; x < gCore.dimension.x; x++) {
            ZT_INDEX nb_x[3];
            ZT_INDEX nb_y[3];
            for (ZT_INDEX i = 0; i < 3; i++) {
                nb_x[i] = (((x - 1) + i) == gCore.dimension.x) ? 0 : (((x - 1) + i) > gCore.dimension.x) ? (gCore.dimension.x - 1) : ((x - 1) + i);
                nb_y[i] = (((y - 1) + i) == gCore.dimension.y) ? 0 : (((y - 1) + i) > gCore.dimension.y) ? (gCore.dimension.y - 1) : ((y - 1) + i);
            }
            ZT_INDEX nb_cnt = 0;
            for (ZT_INDEX sb_y = 0; sb_y < 3; sb_y++) {
                for (ZT_INDEX sb_x = 0; sb_x < 3; sb_x++) {
                    if (!(sb_x == 1 && sb_y == 1)) {
                        if (*(gCore.data.current + nb_x[sb_x] + nb_y[sb_y] * gCore.dimension.x) == gCore.value.alive) {
                            nb_cnt++;
                        }
                    }
                }
            }
            if (*(gCore.data.current + x + y * gCore.dimension.x) == gCore.value.alive) {
                if (nb_cnt > 1 && nb_cnt < 4) {
                    *(workPtr + x + y * gCore.dimension.x) = gCore.value.alive;
                    gCore.counter.alive++;
                } else {
                    *(workPtr + x + y * gCore.dimension.x) = gCore.value.vacant;
                }
            } else {
                if (nb_cnt > 2 && nb_cnt < 4) {
                    *(workPtr + x + y * gCore.dimension.x) = gCore.value.alive;
                    gCore.counter.alive++;
                } else {
                    *(workPtr + x + y * gCore.dimension.x) = gCore.value.vacant;
                }
            }
        }
    }
    gCore.data.current = (gCore.data.current != gCore.data.buffer1) ? gCore.data.buffer1 : gCore.data.buffer0;
    gCore.counter.iteration++;
}

void SGC_SetAlive(ZT_INDEX iX, ZT_INDEX iY) {
    if ((iX < gCore.dimension.x) && (iY < gCore.dimension.y)) {
        ZT_U* lCell = gCore.data.current + iX + iY * gCore.dimension.x;
        if (*lCell != gCore.value.alive) {gCore.counter.alive++;}
        *lCell = gCore.value.alive;
    }
}
void SGC_SetEmpty(ZT_INDEX iX, ZT_INDEX iY) {
    if ((iX < gCore.dimension.x) && (iY < gCore.dimension.y)) {
        ZT_U* lCell = gCore.data.current + iX + iY * gCore.dimension.x;
        if (*lCell == gCore.value.alive) {gCore.counter.alive--;}
        *lCell = gCore.value.vacant;
    }
}
void SGC_Flip(ZT_INDEX iX, ZT_INDEX iY) {
    if ((iX < gCore.dimension.x) && (iY < gCore.dimension.y)) {
        ZT_U* lCell = gCore.data.current + iX + iY * gCore.dimension.x;
        if (*lCell == gCore.value.alive) {
            *lCell = gCore.value.vacant;
            gCore.counter.alive--;
        } else {
            *lCell = gCore.value.alive;
            gCore.counter.alive++;
        }
    }
}
void SGC_Count(void) {
    gCore.counter.alive = 0;
    for (ZT_INDEX i = 0; i < gCore.data.length; i++) {
        if (*(gCore.data.current + i) == gCore.value.alive) {gCore.counter.alive++;}
    }
}

#endif // SEAGULL_CORE_C_INCLUDED
