/*** Copyright (C) 2020 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#ifndef SEAGULL_GAME_C_INCLUDED
#define SEAGULL_GAME_C_INCLUDED

#include "Seagull_Game.h"

GAME_HIVE* gGame = NULL;

void SGG_Exit(void) {
    if (gGame != NULL) {
        ZTM8_Free(gGame->cache);
        ZTM8_Free(gGame->gfx.background.pixels);
        SGC_Free();
        ZTM8_Free(gGame);
        gGame = NULL;
    }
}
void SGG_ViewUpdate(void) {
    if (gGame != NULL) {
        SGG_CameraBounds();
        gGame->gfx.view.w = gGame->game->dimension.x << gGame->gfx.zoom;
        gGame->gfx.view.h = gGame->game->dimension.y << gGame->gfx.zoom;
        gGame->gfx.view.x = ((ZTK_GetWidth() - gGame->gfx.view.w) >> 1) - gGame->gfx.camera.x;
        gGame->gfx.view.y = ((ZTK_GetHeight() - gGame->gfx.view.h) >> 1) - gGame->gfx.camera.y;
    }
}
void SGG_InitGFX(void) {
    if (gGame != NULL) {
        gGame->gfx.background.block.x = gGame->game->dimension.x;
        gGame->gfx.background.block.y = gGame->game->dimension.y;
        gGame->gfx.background.pixels = (ZT_COLOR*)ZTM8_New(sizeof(ZT_COLOR) * ZTM_PointArea(&(gGame->gfx.background.block)));
        gGame->gfx.flag = SGGAME_DEFAULT_GFX_FLAG;
        gGame->gfx.zoom = 0;
        gGame->gfx.camera.x = 0;
        gGame->gfx.camera.y = 0;
        SGG_ViewUpdate();
    }
}
void SGG_Spawn(void) {
    if (gGame != NULL) {
        for (ZT_INDEX y = 0; y < gGame->game->dimension.y; y++) {
             for (ZT_INDEX x = 0; x < gGame->game->dimension.x; x++) {
                if ((ZTM_Randomize_32(&gGame->seed, 100) + 1) <= gGame->stat.density) {SGC_SetAlive(x, y);} else {SGC_SetEmpty(x, y);}
            }
        }
        gGame->game->counter.iteration = 0;
        gGame->counter.fps = 0;
    }
}
void SGG_Wipe(void) {
    if (gGame != NULL) {
        for (ZT_INDEX y = 0; y < gGame->game->dimension.y; y++) {
             for (ZT_INDEX x = 0; x < gGame->game->dimension.x; x++) {
                SGC_SetEmpty(x, y);
            }
        }
        gGame->game->counter.iteration = 0;
        gGame->counter.fps = 0;
        gGame->flag |= SGGAME_FLAG_PAUSE_USER;
    }
}
void SGG_Init(ZT_INDEX iWidth, ZT_INDEX iHeight) {
    if (gGame == NULL) {
        if ((gGame = ZTM8_Init(sizeof(GAME_HIVE), 0x0)) != NULL) {
            if ((gGame->game = SGC_New(iWidth, iHeight)) != NULL) {
                gGame->cache = NULL;
                gGame->seed = ZTM_Time();
                gGame->flag = SGGAME_DEFAULT_FLAG;
                gGame->options = SGGAME_DEFAULT_OPTIONS;
                gGame->timeout.timer = 32;
                gGame->timeout.fps = 999;
                gGame->stat.timer = SGGAME_DEFAULT_SPEED;
                gGame->stat.density = SGGAME_DEFAULT_DENSITY;
                gGame->stat.fps = 0;
                gGame->counter.fps = 0;
                gGame->counter.timer = 0;
                SGG_InitGFX();
                SGG_Spawn();
            } else {
                SGG_Exit();
            }
        }
    }
}
void SGG_Loop(void) {
    if (gGame != NULL) {
        if (ZTK_Timeout(&(gGame->timestamp.fps), gGame->timeout.fps)) {
            ZTK_TimeoutReset(&(gGame->timestamp.fps), gGame->timeout.fps);
            gGame->stat.fps = gGame->game->counter.iteration - gGame->counter.fps;
            gGame->counter.fps = gGame->game->counter.iteration;
        }
        if (gGame->options & SGGAME_OPTION_TIMED_ITERATION) {
            if (ZTK_Timeout(&(gGame->timestamp.timer), gGame->timeout.timer)) {
                ZTK_TimeoutReset(&(gGame->timestamp.timer), gGame->timeout.timer);
                gGame->flag |= SGGAME_FLAG_ITERATE;
            }
        }
        if (gGame->flag & SGGAME_FLAG_ITERATE && !(gGame->flag & SGGAME_FLAG_PAUSE)) {
            SGC_Iterate();
            gGame->flag &= ~SGGAME_FLAG_ITERATE;
        }
    }
}
void SGG_Draw(void) {
    if (gGame != NULL) {
        ZTM32_CopyBlock(gGame->game->data.current, gGame->gfx.background.pixels, &(gGame->gfx.background.block));
        ZTM_SurfacePixelsReplaceColor(&(gGame->gfx.background), gGame->game->value.alive, ((ZUI_HostGetJuicyColor() >> 8) | 0xff000000), 0);
        ZTK_DrawSurface(&(gGame->gfx.background), &(gGame->gfx.view));
        //if (gGame->flag & SGGAME_FLAG_DRAW_GRID) {}
        if (!(gGame->options & SGGAME_OPTION_TIMED_ITERATION)) {
            if (!(++gGame->counter.timer < ((ZT_FLAG)0x1 << gGame->stat.timer))) {
                gGame->counter.timer =  0;
                gGame->flag |= SGGAME_FLAG_ITERATE;
            }
        }
    }
}
void SGG_CameraBounds(void) {
    if (gGame != NULL) {
        ZT_I lBoundX = ((ZT_I)(gGame->game->dimension.x << gGame->gfx.zoom) - (4 * ZTK_GetWidth() / 5)) / 2;
        if (lBoundX < 0) {lBoundX = 0;}
        if (gGame->gfx.camera.x > lBoundX) {
            gGame->gfx.camera.x = lBoundX;
        } else if (gGame->gfx.camera.x < -lBoundX) {
            gGame->gfx.camera.x = -lBoundX;
        }
        ZT_I lBoundY = ((ZT_I)(gGame->game->dimension.y << gGame->gfx.zoom) - (4 * ZTK_GetHeight() / 5)) / 2;
        if (lBoundY < 0) {lBoundY = 0;}
        if (gGame->gfx.camera.y > lBoundY) {
            gGame->gfx.camera.y = lBoundY;
        } else if (gGame->gfx.camera.y < -lBoundY) {
            gGame->gfx.camera.y = -lBoundY;
        }
    }
}
void SGG_CameraReset(void) {
    if (gGame != NULL) {
        ZTM_PointZero(&(gGame->gfx.camera));
        gGame->gfx.zoom = 0;
        SGG_ViewUpdate();
    }
}
void SGG_CameraMove(ZT_I iX, ZT_I iY) {
    if (gGame != NULL) {
        gGame->gfx.camera.x += iX;
        gGame->gfx.camera.y += iY;
        SGG_ViewUpdate();
    }
}
void SGG_CameraZoom(ZT_I iAmount) {
    if (gGame != NULL) {
        if (iAmount > 0) {
            if ((ZT_INDEX)iAmount > gGame->gfx.zoom) {iAmount = gGame->gfx.zoom;}
            gGame->gfx.zoom -= iAmount;
            gGame->gfx.camera.x >>= iAmount;
            gGame->gfx.camera.y >>= iAmount;
        } else {
            iAmount = -iAmount;
            if ((ZT_INDEX)iAmount > (SGGAME_GFX_MAX_ZOOM - gGame->gfx.zoom)) {iAmount = (SGGAME_GFX_MAX_ZOOM - gGame->gfx.zoom);}
            gGame->gfx.zoom += iAmount;
            gGame->gfx.camera.x <<= iAmount;
            gGame->gfx.camera.y <<= iAmount;
        }
        SGG_ViewUpdate();
    }
}
void SGG_CameraZoomMouse(ZT_I iAmount, ZT_I iMouseX, ZT_I iMouseY) {
    if (gGame != NULL) {
        gGame->gfx.camera.x = (SGG_MouseX(iMouseX) - gGame->game->dimension.x / 2) << gGame->gfx.zoom;
        gGame->gfx.camera.y = (SGG_MouseY(iMouseY) - gGame->game->dimension.y / 2) << gGame->gfx.zoom;
        if (iAmount > 0) {
            if ((ZT_INDEX)iAmount > gGame->gfx.zoom) {iAmount = gGame->gfx.zoom;}
            gGame->gfx.zoom -= iAmount;
            gGame->gfx.camera.x >>= iAmount;
            gGame->gfx.camera.y >>= iAmount;
        } else {
            iAmount = -iAmount;
            if ((ZT_INDEX)iAmount > (SGGAME_GFX_MAX_ZOOM - gGame->gfx.zoom)) {iAmount = (SGGAME_GFX_MAX_ZOOM - gGame->gfx.zoom);}
            gGame->gfx.zoom += iAmount;
            gGame->gfx.camera.x <<= iAmount;
            gGame->gfx.camera.y <<= iAmount;
        }
        gGame->gfx.camera.x -= (iMouseX - ZTK_GetWidth() / 2);
        gGame->gfx.camera.y -= (iMouseY - ZTK_GetHeight() / 2);
        SGG_ViewUpdate();
    }
}
void SGG_TogglePauseUser(void) {
    if (gGame != NULL) {
        gGame->flag ^= SGGAME_FLAG_PAUSE_USER;
    }
}
void SGG_PauseUser(ZT_BOOL iPause) {
    if (gGame != NULL) {
        if (iPause) {
            gGame->flag |= SGGAME_FLAG_PAUSE_USER;
        } else {
            gGame->flag &= ~SGGAME_FLAG_PAUSE_USER;
        }
    }
}
void SGG_PauseSystem(ZT_BOOL iPause) {
    if (gGame != NULL) {
        if (iPause) {
            gGame->flag |= SGGAME_FLAG_PAUSE_SYSTEM;
        } else {
            gGame->flag &= ~SGGAME_FLAG_PAUSE_SYSTEM;
        }
    }
}
void SGG_ToggleSpeed(ZT_I iAmount) {
    if (gGame != NULL) {
        if (iAmount > 0) {
            if ((ZT_INDEX)iAmount > gGame->stat.timer) {iAmount = gGame->stat.timer;}
            gGame->stat.timer -= iAmount;
            gGame->counter.timer >>= iAmount;
        } else {
            iAmount = -iAmount;
            if ((ZT_INDEX)iAmount > (SGGAME_MAX_SPEED - gGame->stat.timer)) {iAmount = (SGGAME_MAX_SPEED - gGame->stat.timer);}
            gGame->stat.timer += iAmount;
            gGame->counter.timer <<= iAmount;
        }
    }
}
void SGG_Flip(ZT_I iMouseX, ZT_I iMouseY){
    SGC_Flip(SGG_MouseX(iMouseX), SGG_MouseY(iMouseY));
}
ZT_INDEX SGG_MouseX(ZT_I iMouseX) {
    if (gGame != NULL) {
        return (iMouseX - ZTK_GetWidth() / 2 + gGame->gfx.camera.x + gGame->gfx.view.w / 2) >> gGame->gfx.zoom;
    }
    return 0;
}
ZT_INDEX SGG_MouseY(ZT_I iMouseY) {
    if (gGame != NULL) {
        return (iMouseY - ZTK_GetHeight() / 2 + gGame->gfx.camera.y + gGame->gfx.view.h / 2) >> gGame->gfx.zoom;
    }
    return 0;
}
void SGG_Save(void) {
    if (gGame != NULL) {
        if (gGame->cache == NULL) {gGame->cache = (ZT_U*)ZTM8_New(sizeof(ZT_U) * gGame->game->data.length);}
        if (gGame->cache != NULL) {
            ZTM8_Copy(gGame->game->data.current, gGame->cache, sizeof(ZT_U) * gGame->game->data.length);
        }
    }
}
void SGG_Load(void) {
    if (gGame != NULL) {
        if (gGame->cache != NULL) {
            ZTM8_Copy(gGame->cache, gGame->game->data.current, sizeof(ZT_U) * gGame->game->data.length);
            gGame->game->counter.iteration = 0;
            gGame->counter.fps = 0;
            SGC_Count();
        }
    }
}
#endif // SEAGULL_GAME_C_INCLUDED
