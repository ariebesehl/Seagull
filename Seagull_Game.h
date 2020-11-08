/*** Copyright (C) 2020 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#ifndef SEAGULL_GAME_H_INCLUDED
#define SEAGULL_GAME_H_INCLUDED

#include "Seagull.h"
#include "Seagull_Core.h"

#define SGGAME_FLAG_NONE 0x0
#define SGGAME_FLAG_ITERATE 0x1
#define SGGAME_FLAG_PAUSE_USER 0x2
#define SGGAME_FLAG_PAUSE_SYSTEM 0x4
#define SGGAME_FLAG_PAUSE (SGGAME_FLAG_PAUSE_USER | SGGAME_FLAG_PAUSE_SYSTEM)
#define SGGAME_FLAG_DRAW_GRID 0x8

#define SGGAME_GFX_FLAG_NONE 0x0
#define SGGAME_GFX_FLAG_CAMERA_MOVE 0x1

#define SGGAME_GFX_MAX_ZOOM 5
#define SGGAME_MAX_SPEED 8

#define SGGAME_OPTION_NONE 0x0
#define SGGAME_OPTION_TIMED_ITERATION 0x1

#define SGGAME_DEFAULT_DENSITY 12
#define SGGAME_DEFAULT_SPEED 0
#define SGGAME_DEFAULT_FLAG (SGGAME_FLAG_NONE | SGGAME_FLAG_PAUSE_SYSTEM)
#define SGGAME_DEFAULT_GFX_FLAG (SGGAME_GFX_FLAG_NONE)
#define SGGAME_DEFAULT_OPTIONS (SGGAME_OPTION_NONE)

typedef struct {
    SEAGULL* game;
    ZT_U* cache;
    ZT_U32 seed;
    ZT_FLAG flag;
    ZT_FLAG options;
    struct {
        ZT_INDEX timer;
        ZT_INDEX density;
        ZT_INDEX fps;
    } stat;
    struct {
        ZT_INDEX timer;
        ZT_INDEX fps;
    } counter;
    struct {
        ZT_TIME timer;
        ZT_TIME fps;
    } timestamp;
    struct {
        ZT_TIME timer;
        ZT_TIME fps;
    } timeout;
    struct {
        ZT_FLAG flag;
        ZT_INDEX zoom;
        ZT_POINT camera;
        ZT_RECT view;
        ZT_SURFACE background;
        ZT_SURFACE grid;
    } gfx;
} GAME_HIVE;

GAME_HIVE* gGame;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void SGG_Exit(void);
void SGG_ViewUpdate(void);
void SGG_Spawn(void);
void SGG_Wipe(void);
void SGG_InitGFX(void);
void SGG_Init(ZT_INDEX iWidth, ZT_INDEX iHeight);
void SGG_Loop(void);
void SGG_Draw(void);
void SGG_CameraBounds(void);
void SGG_CameraReset(void);
void SGG_CameraMove(ZT_I iX, ZT_I iY);
void SGG_CameraZoom(ZT_I iAmount);
void SGG_CameraZoomMouse(ZT_I iAmount, ZT_I iMouseX, ZT_I iMouseY);
void SGG_TogglePauseUser(void);
void SGG_PauseUser(ZT_BOOL iPause);
void SGG_PauseSystem(ZT_BOOL iPause);
void SGG_ToggleSpeed(ZT_I iAmount);
void SGG_Flip(ZT_I iMouseX, ZT_I iMouseY);
ZT_INDEX SGG_MouseX(ZT_I iMouseX);
ZT_INDEX SGG_MouseY(ZT_I iMouseY);
void SGG_Save(void);
void SGG_Load(void);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SEAGULL_GAME_H_INCLUDED
