/*** Copyright (C) 2020 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#ifndef SEAGULL_CORE_C_INCLUDED
#define SEAGULL_CORE_C_INCLUDED

#include "Seagull_Core.h"

SEAGULL* gSeagull = NULL;

void SGC_BufferFree(void) {
	if (gSeagull != NULL) {
		if (gSeagull->data.buffer0 != NULL) {ZTM8_Free(gSeagull->data.buffer0); gSeagull->data.buffer0 = NULL;}
		gSeagull->data.current = NULL;
	}
}
ZT_BOOL SGC_BufferNew(void) {
	if (gSeagull != NULL) {
		if ((gSeagull->data.buffer0 == NULL) && (gSeagull->data.buffer1 == NULL)) {
			if ((gSeagull->data.buffer0 = (ZT_U*)ZTM8_New(2 * gSeagull->data.length * sizeof(ZT_U))) != NULL) {
				gSeagull->data.buffer1 = gSeagull->data.buffer0 + gSeagull->data.length;
				gSeagull->data.current = gSeagull->data.buffer0;
				return ZT_TRUE;
			}
		}
	}
	return ZT_FALSE;
}
void SGC_Free(void) {
	if (gSeagull != NULL) {
		SGC_BufferFree();
		ZTM8_Free(gSeagull);
		gSeagull = NULL;
	}
}
SEAGULL* SGC_New(ZT_INDEX iWidth, ZT_INDEX iHeight) {
	if (gSeagull == NULL) {
		ZT_INDEX lLength = iWidth * iHeight;
		if (lLength) {
			if ((gSeagull = (SEAGULL*)ZTM8_New(sizeof(SEAGULL))) != NULL) {
				gSeagull->stat.version = SGCORE_VERSION;
				gSeagull->counter.alive = 0;
				gSeagull->counter.iteration = 0;
				gSeagull->value.alive = SGCORE_CELL_ALIVE;
				gSeagull->value.vacant = SGCORE_CELL_EMPTY;
				gSeagull->dimension.x = iWidth;
				gSeagull->dimension.y = iHeight;
				gSeagull->data.length = lLength;
				gSeagull->data.current = NULL;
				gSeagull->data.buffer0 = NULL;
				gSeagull->data.buffer1 = NULL;
				if (!SGC_BufferNew()) {SGC_Free();}
			}
		}
	}
	return gSeagull;
}

void SGC_Iterate(void) {
    if (gSeagull != NULL) {
        gSeagull->counter.alive = 0;
        ZT_U* workPtr = (gSeagull->data.current != gSeagull->data.buffer1) ? gSeagull->data.buffer1 : gSeagull->data.buffer0;
        for (ZT_INDEX y = 0; y < gSeagull->dimension.y; y++) {
            for (ZT_INDEX x = 0; x < gSeagull->dimension.x; x++) {
                ZT_INDEX nb_x[3];
                ZT_INDEX nb_y[3];
                for (ZT_INDEX i = 0; i < 3; i++) {
                    nb_x[i] = (((x - 1) + i) == gSeagull->dimension.x) ? 0 : (((x - 1) + i) > gSeagull->dimension.x) ? (gSeagull->dimension.x - 1) : ((x - 1) + i);
                    nb_y[i] = (((y - 1) + i) == gSeagull->dimension.y) ? 0 : (((y - 1) + i) > gSeagull->dimension.y) ? (gSeagull->dimension.y - 1) : ((y - 1) + i);
                }
                ZT_INDEX nb_cnt = 0;
                for (ZT_INDEX sb_y = 0; sb_y < 3; sb_y++) {
                    for (ZT_INDEX sb_x = 0; sb_x < 3; sb_x++) {
                        if (!(sb_x == 1 && sb_y == 1)) {
                            if (*(gSeagull->data.current + nb_x[sb_x] + nb_y[sb_y] * gSeagull->dimension.x) == gSeagull->value.alive) {
                                nb_cnt++;
                            }
                        }
                    }
                }
                if (*(gSeagull->data.current + x + y * gSeagull->dimension.x) == gSeagull->value.alive) {
                    if (nb_cnt > 1 && nb_cnt < 4) {
                        *(workPtr + x + y * gSeagull->dimension.x) = gSeagull->value.alive;
                        gSeagull->counter.alive++;
                    } else {
                        *(workPtr + x + y * gSeagull->dimension.x) = gSeagull->value.vacant;
                    }
                } else {
                    if (nb_cnt > 2 && nb_cnt < 4) {
                        *(workPtr + x + y * gSeagull->dimension.x) = gSeagull->value.alive;
                        gSeagull->counter.alive++;
                    } else {
                        *(workPtr + x + y * gSeagull->dimension.x) = gSeagull->value.vacant;
                    }
                }
            }
        }
        gSeagull->data.current = (gSeagull->data.current != gSeagull->data.buffer1) ? gSeagull->data.buffer1 : gSeagull->data.buffer0;
        gSeagull->counter.iteration++;
    }
}

void SGC_SetAlive(ZT_INDEX iX, ZT_INDEX iY) {
    if (gSeagull != NULL) {
        if ((iX < gSeagull->dimension.x) && (iY < gSeagull->dimension.y)) {
            ZT_U* lCell = gSeagull->data.current + iX + iY * gSeagull->dimension.x;
            if (*lCell != gSeagull->value.alive) {gSeagull->counter.alive++;}
            *lCell = gSeagull->value.alive;
        }
    }
}
void SGC_SetEmpty(ZT_INDEX iX, ZT_INDEX iY) {
    if (gSeagull != NULL) {
        if ((iX < gSeagull->dimension.x) && (iY < gSeagull->dimension.y)) {
            ZT_U* lCell = gSeagull->data.current + iX + iY * gSeagull->dimension.x;
            if (*lCell == gSeagull->value.alive) {gSeagull->counter.alive--;}
            *lCell = gSeagull->value.vacant;
        }
    }
}
void SGC_Flip(ZT_INDEX iX, ZT_INDEX iY) {
    if (gSeagull != NULL) {
        if ((iX < gSeagull->dimension.x) && (iY < gSeagull->dimension.y)) {
            ZT_U* lCell = gSeagull->data.current + iX + iY * gSeagull->dimension.x;
            if (*lCell == gSeagull->value.alive) {
                *lCell = gSeagull->value.vacant;
                gSeagull->counter.alive--;
            } else {
                *lCell = gSeagull->value.alive;
                gSeagull->counter.alive++;
            }
        }
    }
}
void SGC_Count(void) {
    if (gSeagull != NULL) {
        gSeagull->counter.alive = 0;
        for (ZT_INDEX i = 0; i < gSeagull->data.length; i++) {
            if (*(gSeagull->data.current + i) == gSeagull->value.alive) {gSeagull->counter.alive++;}
        }
    }
}

#endif // SEAGULL_CORE_C_INCLUDED
