/*** Copyright (C) 2020 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/

#include "Seagull.h"

APP_HIVE* gMain = NULL;

void gSG_Init(void) {
    if (gMain == NULL) {
        if ((gMain = (APP_HIVE*)ZTM8_New(sizeof(APP_HIVE))) != NULL) {
			gMain->user.lang = SG_DEFAULT_TEXT_LANG;
			gMain->user.menu = SG_FLAG_GUI_MENU_NONE;
            ZTM_Rect(&(gMain->rect.window), ZTK_HostGetScreenWidth() / 4, ZTK_HostGetScreenHeight() / 4, ZTK_HostGetScreenWidth() / 2, ZTK_HostGetScreenHeight() / 2);
			gMain->timestamp.fps = 0;
            gMain->timestamp.draw = 0;
			gMain->timeout.fps = 999;
            gMain->timeout.draw = 16;
			gMain->counter.fps = 0;
			gMain->stat.fps = 0;
			gMain->event.window = NULL;
			gMain->event.gui = NULL;
			gMain->font.window = NULL;
			gMain->font.title = NULL;
			gMain->font.desc = NULL;
			gMain->printer = NULL;
            SGTXT_Load();
            ZTK_New(gMain->text.window.title, &(gMain->rect.window), NULL);
            ZTK_Background(ZT_TRUE);
            ZTK_BackgroundAuto(ZT_TRUE);
            ZTK_Heartbeat(1);
            ZTK_IdleForbid(ZT_FALSE);
            ZTK_IdleAuto(ZT_TRUE);
            SGUI_Init();
            ZTK_Open();
        }
    }
}
void gSG_Exit(void) {
    if (gMain != NULL) {
        SGG_Exit();
        SGUI_Exit();
        ZTK_Free();
        ZTM8_Free(gMain);
        gMain = NULL;
    }
}
void SGUI_Event(void) {
    ZT_EVENT* lGUIEvent = gMain->event.gui;
    //printf("%x %x %u %u %u %u\n", lGUIEvent->id.device, lGUIEvent->id.event, lGUIEvent->data.d0, lGUIEvent->data.d1, lGUIEvent->data.d2, lGUIEvent->data.d3);
    if (lGUIEvent->id.E == ZTK_EID_GUI_RELEASE) {
        switch (lGUIEvent->id.S) {
            case SG_ID_GUI_MENU_HEAD_START: gMain->user.menu = SG_FLAG_GUI_MENU_NONE; SGUI_Menu(); break;
            case SG_ID_GUI_MENU_HEAD_HELP: gMain->user.menu = SG_FLAG_GUI_MENU_HELP; SGUI_Menu(); break;
            case SG_ID_GUI_MENU_HEAD_CREDITS: gMain->user.menu = SG_FLAG_GUI_MENU_CREDITS; SGUI_Menu();  break;
            case SG_ID_GUI_MENU_HEAD_EXIT: ZTK_Quit(); break;
            case SG_ID_GUI_MENU_HELP_EXIT: gMain->user.menu = SG_FLAG_GUI_MENU_HEAD; SGUI_Menu(); break;
            case SG_ID_GUI_MENU_CREDITS_EXIT: gMain->user.menu = SG_FLAG_GUI_MENU_HEAD; SGUI_Menu(); break;
            case SG_ID_GUI_HUD_MENU: gMain->user.menu = SG_FLAG_GUI_MENU_HEAD; SGUI_Menu(); break;
            case SG_ID_GUI_HUD_SPEED_SLOWER: SGG_ToggleSpeed(-1); break;
            case SG_ID_GUI_HUD_SPEED_PAUSE: SGG_TogglePauseUser(); break;
            case SG_ID_GUI_HUD_SPEED_FASTER: SGG_ToggleSpeed(1); break;
            case SG_ID_GUI_HUD_GAME_SPAWN: SGG_Spawn(); break;
            case SG_ID_GUI_HUD_GAME_WIPE: SGG_Wipe(); break;
            case SG_ID_GUI_HUD_GAME_SAVE: SGG_Save(); break;
            case SG_ID_GUI_HUD_GAME_LOAD: SGG_Load(); break;
            case SG_ID_GUI_HUD_CAMERA_ZOOM_IN: SGG_CameraZoom(-1); break;
            case SG_ID_GUI_HUD_CAMERA_RESET: SGG_CameraReset(); break;
            case SG_ID_GUI_HUD_CAMERA_ZOOM_OUT: SGG_CameraZoom(1); break;
            default: break;
        }
    }
}
void gSG_Event(void) {
    ZT_EVENT* lEvent = gMain->event.window;
    //printf("%x %x %u %u %u %u\n", lEvent->id.device, lEvent->id.event, lEvent->data.d0, lEvent->data.d1, lEvent->data.d2, lEvent->data.d3);
    ZT_BOOL lGUI_Event = ZT_FALSE;
    while (ZUI_HostPoll(lEvent, &(gMain->event.gui))) {SGUI_Event(); lGUI_Event = ZT_TRUE;}
    if (lGUI_Event || gMain->user.menu) {
    } else {
        switch (lEvent->id.H) {
            case ZTK_HID_MOUSE:
                switch (lEvent->id.E) {
                    case ZTK_EID_MOUSE_BUTTON_L_UP: SGG_Flip((ZT_I)lEvent->data.d0, (ZT_I)lEvent->data.d1); break;
                    case ZTK_EID_MOUSE_MOVE: if (ZTK_GetMouseState() & ZTK_SID_MOUSE_RBUTTON) {SGG_CameraMove((ZT_I)lEvent->data.d2 - (ZT_I)lEvent->data.d0, (ZT_I)lEvent->data.d3 - (ZT_I)lEvent->data.d1);} break;
                    case ZTK_EID_MOUSE_WHEEL_UP: case ZTK_EID_MOUSE_WHEEL_DOWN: SGG_CameraZoomMouse(((ZT_I)lEvent->data.d3) / 120, (ZT_I)lEvent->data.d0, (ZT_I)lEvent->data.d1); break;
                    default: break;
                }
                break;
            case ZTK_HID_KEY:
                if (lEvent->id.E == ZTK_EID_KEYBOARD_KEY_UP) {
                    switch (lEvent->id.S) {
                        case ZTK_SID_KEY_SPACE: case ZTK_SID_KEY_PAUSE: SGG_TogglePauseUser(); break;
                        case ZTK_SID_KEY_L: SGG_ToggleSpeed(1); break;
                        case ZTK_SID_KEY_K: SGG_ToggleSpeed(-1); break;
                        default: break;
                    }
                } else if (lEvent->id.E == ZTK_EID_KEYBOARD_KEY_DOWN) {
                    switch (lEvent->id.S) {
                        case ZTK_SID_KEY_UP: SGG_CameraMove(0, -2); break;
                        case ZTK_SID_KEY_DOWN: SGG_CameraMove(0, 2); break;
                        case ZTK_SID_KEY_LEFT: SGG_CameraMove(-2, 0); break;
                        case ZTK_SID_KEY_RIGHT: SGG_CameraMove(2, 0); break;
                        default: break;
                    }
                }
                break;
            default:
                break;
        }
    }
    switch (lEvent->id.H) {
        case ZTK_HID_KEY:
            if (lEvent->id.E == ZTK_EID_KEYBOARD_KEY_UP) {
                switch (lEvent->id.S) {
                    case ZTK_SID_KEY_ESC:
                        if (gMain->user.menu & SG_FLAG_GUI_MENU_HEAD) {gMain->user.menu = SG_FLAG_GUI_MENU_NONE;} else {gMain->user.menu = SG_FLAG_GUI_MENU_HEAD;}
                        SGUI_Menu();
                        break;
                    default: break;
                }
            }
            break;
        case ZTK_HID_WINDOW:
            switch (lEvent->id.E) {
                case ZTK_EID_WINDOW_RESIZE: SGG_ViewUpdate(); SGUI_Size(); break;
                default: break;
            }
            break;
        default:
            break;
    }
}
void gSG_Draw(void) {
    ZT_COLOR lColorCurrent = ZUI_HostGetJuicyColor();
    ZT_FLAG lPalette = ZTK_GetPalette();
    ZT_COLOR lBackground = ((ZTM_ColorRed(lColorCurrent, lPalette) >> 3) << ZTM_ColorRedShift(lPalette)) |
    ((ZTM_ColorGreen(lColorCurrent, lPalette) >> 3) << ZTM_ColorGreenShift(lPalette)) |
    ((ZTM_ColorBlue(lColorCurrent, lPalette) >> 3) << ZTM_ColorBlueShift(lPalette));
    ZTK_BackgroundColor(lBackground);
    ZTK_DrawClear();
    SGG_Draw();
	ZUI_HostDraw();
	if (!(gMain->user.menu)) {
        ZTK_PrintPos(&(gMain->pos.fps));
        ZTK_Print("FPS: %3u\n", gMain->stat.fps);
        if (gGame!= NULL) {
            ZTK_PrintPos(&(gMain->pos.tick));
            ZTK_Print("TPS: %3u (%u)", gGame->stat.fps, gGame->game->counter.iteration);
            ZTK_PrintPos(&(gMain->pos.pop));
            ZT_DBL lPercent = 100.0 * gGame->game->counter.alive / (ZT_DBL)(gGame->game->dimension.x * gGame->game->dimension.y);
            ZTK_Print("Pop: %6u (%3.2f%%)", gGame->game->counter.alive, lPercent);
        }
	}
    ZTK_DrawPresent();
    gMain->counter.fps++;
}
void gSG_Main(void) {
    if (ZTK_Timeout(&(gMain->timestamp.fps), gMain->timeout.fps)) {
        ZTK_TimeoutReset(&(gMain->timestamp.fps), gMain->timeout.fps);
        gMain->stat.fps = gMain->counter.fps;
        gMain->counter.fps = 0;
    }
    while (ZTK_PollMessages(&(gMain->event.window))) {gSG_Event();}
    SGG_Loop();
    if (ZTK_Timeout(&(gMain->timestamp.draw), gMain->timeout.draw)) {
        ZTK_TimeoutReset(&(gMain->timestamp.draw), gMain->timeout.draw);
        gSG_Draw();
    }
}
int main(void) {
	gSG_Init();
	SGG_Init(512, 256);
    while (ZTK_Main(&gSG_Main));
    gSG_Exit();
    return 0;
}
