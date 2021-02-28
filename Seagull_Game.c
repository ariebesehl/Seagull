/*** Copyright (C) 2020 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#ifndef SEAGULL_GAME_C_INCLUDED
#define SEAGULL_GAME_C_INCLUDED

#include "Seagull_Game.h"

void SGG_Exit(void) {
    ZTM8_Free(gGame.cache);
    ZTM8_Free(gGame.gfx.background.pixels);
    SGC_Free();
}
void SGG_ViewUpdate(void) {
    SGG_CameraBounds();
    gGame.gfx.view.w = gCore.dimension.x << gGame.gfx.zoom;
    gGame.gfx.view.h = gCore.dimension.y << gGame.gfx.zoom;
    gGame.gfx.view.x = ((ZTK_GetWidth() - gGame.gfx.view.w) >> 1) - gGame.gfx.camera.x;
    gGame.gfx.view.y = ((ZTK_GetHeight() - gGame.gfx.view.h) >> 1) - gGame.gfx.camera.y;
}
void SGG_InitGFX(void) {
    gGame.gfx.background.block.x = gCore.dimension.x;
    gGame.gfx.background.block.y = gCore.dimension.y;
    gGame.gfx.background.pixels = (ZT_COLOR*)ZTM8_New(sizeof(ZT_COLOR) * ZTM_PointArea(&(gGame.gfx.background.block)));
    gGame.gfx.flag = SGGAME_DEFAULT_GFX_FLAG;
    gGame.gfx.zoom = 0;
    gGame.gfx.camera.x = 0;
    gGame.gfx.camera.y = 0;
    SGG_ViewUpdate();
}
void SGG_Spawn(void) {
    for (ZT_INDEX y = 0; y < gCore.dimension.y; y++) {
         for (ZT_INDEX x = 0; x < gCore.dimension.x; x++) {
            if ((ZTM_Randomize_32(&gGame.seed, 100) + 1) <= gGame.stat.density) {SGC_SetAlive(x, y);} else {SGC_SetEmpty(x, y);}
        }
    }
    gCore.counter.iteration = 0;
    gGame.counter.fps = 0;
}
void SGG_Wipe(void) {
    for (ZT_INDEX y = 0; y < gCore.dimension.y; y++) {
         for (ZT_INDEX x = 0; x < gCore.dimension.x; x++) {
            SGC_SetEmpty(x, y);
        }
    }
    gCore.counter.iteration = 0;
    gGame.counter.fps = 0;
    gGame.flag |= SGGAME_FLAG_PAUSE_USER;
}
void SGG_Init(ZT_INDEX iWidth, ZT_INDEX iHeight) {
    SGC_New(iWidth, iHeight);
    ZTM8_Zero(&gGame, sizeof(gGame));
    gGame.cache = NULL;
    gGame.seed = ZTM_Time();
    gGame.flag = SGGAME_DEFAULT_FLAG;
    gGame.options = SGGAME_DEFAULT_OPTIONS;
    gGame.timeout.timer = 32;
    gGame.stat.timer = SGGAME_DEFAULT_SPEED;
    gGame.stat.density = SGGAME_DEFAULT_DENSITY;
    gGame.stat.fps = 0;
    gGame.counter.fps = 0;
    gGame.counter.timer = 0;
    SGG_InitGFX();
    SGG_Spawn();
}
void SGG_Loop(void) {
    if (ZTK_TimeoutReset(&(gGame.timestamp.fps), 1000)) {
        gGame.stat.fps = gCore.counter.iteration - gGame.counter.fps;
        gGame.counter.fps = gCore.counter.iteration;
    }
    if (gGame.options & SGGAME_OPTION_TIMED_ITERATION) {
        if (ZTK_TimeoutReset(&(gGame.timestamp.timer), gGame.timeout.timer)) {
            gGame.flag |= SGGAME_FLAG_ITERATE;
        }
    }
    if (gGame.flag & SGGAME_FLAG_ITERATE && !(gGame.flag & SGGAME_FLAG_PAUSE)) {
        SGC_Iterate();
        gGame.flag &= ~SGGAME_FLAG_ITERATE;
    }
}
void SGG_Draw(ZT_COLOR iColor) {
    if (ZTK_GetRendererType() == ZTK_RENDERER_OPENGL) {
        ZTM_PixelsFlipVertical(gCore.data.current, gGame.gfx.background.pixels, &gGame.gfx.background.block);
    } else {
        ZTM32_CopyBlock(gCore.data.current, gGame.gfx.background.pixels, &(gGame.gfx.background.block));
    }
    ZT_COLOR lColor = ZTM_ColorConvert(iColor, ZTK_GetPalette(), ZTK_GetPaletteSystem());
    ZTM_SurfaceReplaceColor(&(gGame.gfx.background), gCore.value.alive, lColor);
    ZTK_DrawSurface(&(gGame.gfx.background), &(gGame.gfx.view));
    //if (gGame.flag & SGGAME_FLAG_DRAW_GRID) {}
    if (!(gGame.options & SGGAME_OPTION_TIMED_ITERATION)) {
        if (!(++gGame.counter.timer < ((ZT_FLAG)0x1 << gGame.stat.timer))) {
            gGame.counter.timer =  0;
            gGame.flag |= SGGAME_FLAG_ITERATE;
        }
    }
}
void SGG_CameraBounds(void) {
    ZT_I lBoundX = ((ZT_I)(gCore.dimension.x << gGame.gfx.zoom) - (4 * ZTK_GetWidth() / 5)) / 2;
    if (lBoundX < 0) {lBoundX = 0;}
    if (gGame.gfx.camera.x > lBoundX) {
        gGame.gfx.camera.x = lBoundX;
    } else if (gGame.gfx.camera.x < -lBoundX) {
        gGame.gfx.camera.x = -lBoundX;
    }
    ZT_I lBoundY = ((ZT_I)(gCore.dimension.y << gGame.gfx.zoom) - (4 * ZTK_GetHeight() / 5)) / 2;
    if (lBoundY < 0) {lBoundY = 0;}
    if (gGame.gfx.camera.y > lBoundY) {
        gGame.gfx.camera.y = lBoundY;
    } else if (gGame.gfx.camera.y < -lBoundY) {
        gGame.gfx.camera.y = -lBoundY;
    }
}
void SGG_CameraReset(void) {
    ZTM_PointZero(&(gGame.gfx.camera));
    gGame.gfx.zoom = 0;
    SGG_ViewUpdate();
}
void SGG_CameraMove(ZT_I iX, ZT_I iY) {
    gGame.gfx.camera.x += iX;
    gGame.gfx.camera.y += iY;
    SGG_ViewUpdate();
}
void SGG_CameraZoom(ZT_I iAmount) {
    if (iAmount > 0) {
        if ((ZT_INDEX)iAmount > gGame.gfx.zoom) {iAmount = gGame.gfx.zoom;}
        gGame.gfx.zoom -= iAmount;
        gGame.gfx.camera.x >>= iAmount;
        gGame.gfx.camera.y >>= iAmount;
    } else {
        iAmount = -iAmount;
        if ((ZT_INDEX)iAmount > (SGGAME_GFX_MAX_ZOOM - gGame.gfx.zoom)) {iAmount = (SGGAME_GFX_MAX_ZOOM - gGame.gfx.zoom);}
        gGame.gfx.zoom += iAmount;
        gGame.gfx.camera.x <<= iAmount;
        gGame.gfx.camera.y <<= iAmount;
    }
    SGG_ViewUpdate();
}
void SGG_CameraZoomMouse(ZT_I iAmount, ZT_I iMouseX, ZT_I iMouseY) {
    gGame.gfx.camera.x = (SGG_MouseX(iMouseX) - gCore.dimension.x / 2) << gGame.gfx.zoom;
    gGame.gfx.camera.y = (SGG_MouseY(iMouseY) - gCore.dimension.y / 2) << gGame.gfx.zoom;
    if (iAmount > 0) {
        if ((ZT_INDEX)iAmount > gGame.gfx.zoom) {iAmount = gGame.gfx.zoom;}
        gGame.gfx.zoom -= iAmount;
        gGame.gfx.camera.x >>= iAmount;
        gGame.gfx.camera.y >>= iAmount;
    } else {
        iAmount = -iAmount;
        if ((ZT_INDEX)iAmount > (SGGAME_GFX_MAX_ZOOM - gGame.gfx.zoom)) {iAmount = (SGGAME_GFX_MAX_ZOOM - gGame.gfx.zoom);}
        gGame.gfx.zoom += iAmount;
        gGame.gfx.camera.x <<= iAmount;
        gGame.gfx.camera.y <<= iAmount;
    }
    gGame.gfx.camera.x -= (iMouseX - ZTK_GetWidth() / 2);
    gGame.gfx.camera.y -= (iMouseY - ZTK_GetHeight() / 2);
    SGG_ViewUpdate();
}
void SGG_TogglePauseUser(void) {
    gGame.flag ^= SGGAME_FLAG_PAUSE_USER;
}
void SGG_PauseUser(ZT_BOOL iPause) {
    if (iPause) {
        gGame.flag |= SGGAME_FLAG_PAUSE_USER;
    } else {
        gGame.flag &= ~SGGAME_FLAG_PAUSE_USER;
    }
}
void SGG_PauseSystem(ZT_BOOL iPause) {
    if (iPause) {
        gGame.flag |= SGGAME_FLAG_PAUSE_SYSTEM;
    } else {
        gGame.flag &= ~SGGAME_FLAG_PAUSE_SYSTEM;
    }
}
void SGG_ToggleSpeed(ZT_I iAmount) {
    if (iAmount > 0) {
        if ((ZT_INDEX)iAmount > gGame.stat.timer) {iAmount = gGame.stat.timer;}
        gGame.stat.timer -= iAmount;
        gGame.counter.timer >>= iAmount;
    } else {
        iAmount = -iAmount;
        if ((ZT_INDEX)iAmount > (SGGAME_MAX_SPEED - gGame.stat.timer)) {iAmount = (SGGAME_MAX_SPEED - gGame.stat.timer);}
        gGame.stat.timer += iAmount;
        gGame.counter.timer <<= iAmount;
    }
}
void SGG_Flip(ZT_I iMouseX, ZT_I iMouseY){
    SGC_Flip(SGG_MouseX(iMouseX), SGG_MouseY(iMouseY));
}
ZT_INDEX SGG_MouseX(ZT_I iMouseX) {
    return (iMouseX - ZTK_GetWidth() / 2 + gGame.gfx.camera.x + gGame.gfx.view.w / 2) >> gGame.gfx.zoom;
}
ZT_INDEX SGG_MouseY(ZT_I iMouseY) {
    return (iMouseY - ZTK_GetHeight() / 2 + gGame.gfx.camera.y + gGame.gfx.view.h / 2) >> gGame.gfx.zoom;
}
void SGG_Save(void) {
    if (gGame.cache == NULL) {gGame.cache = (ZT_U*)ZTM8_New(sizeof(ZT_U) * gCore.data.length);}
    if (gGame.cache != NULL) {
        ZTM8_Copy(gCore.data.current, gGame.cache, sizeof(ZT_U) * gCore.data.length);
    }
}
void SGG_Load(void) {
    if (gGame.cache != NULL) {
        ZTM8_Copy(gGame.cache, gCore.data.current, sizeof(ZT_U) * gCore.data.length);
        gCore.counter.iteration = 0;
        gGame.counter.fps = 0;
        SGC_Count();
    }
}
#endif // SEAGULL_GAME_C_INCLUDED
