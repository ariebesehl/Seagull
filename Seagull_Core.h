/*** Copyright (C) 2020 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#ifndef SEAGULL_CORE_H_INCLUDED
#define SEAGULL_CORE_H_INCLUDED

#include <ZTK.h>

#define SGCORE_VERSION 191109
#define SGCORE_CELL_ALIVE 0xffffffff
#define SGCORE_CELL_EMPTY 0xff000000

#define SGCORE_FLAG_NONE 0x0

typedef struct {
	struct {
		ZT_INDEX version;
	} stat;
	struct {
	    ZT_INDEX alive;
		ZT_INDEX iteration;
	} counter;
	struct {
		ZT_INDEX x;
		ZT_INDEX y;
	} dimension;
	struct {
		ZT_U alive;
		ZT_U vacant;
	} value;
	struct {
		ZT_INDEX length;
		ZT_U* current;
		ZT_U* buffer0;
		ZT_U* buffer1;
	} data;
	ZT_FLAG flag;
} SGL_CORE;

SGL_CORE gCore;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
SGL_CORE* SGC_New(ZT_INDEX iWidth, ZT_INDEX iHeight);
void SGC_Iterate(void);
void SGC_Count(void);
void SGC_SetAlive(ZT_INDEX iX, ZT_INDEX iY);
void SGC_SetEmpty(ZT_INDEX iX, ZT_INDEX iY);
void SGC_Flip(ZT_INDEX iX, ZT_INDEX iY);
void SGC_Free(void);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SEAGULL_CORE_H_INCLUDED
