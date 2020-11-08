/*** Copyright (C) 2020 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#ifndef SEAGULL_TEXT_C_INCLUDED
#define SEAGULL_TEXT_C_INCLUDED

#include "Seagull_Text.h"

void SGTXT_Load(void) {
	if (gMain != NULL) {
		switch (gMain->user.lang) {
            case SG_TEXT_LANG_EN:
                gMain->text.window.title = (const ZT_CHAR*)(SG_TEXT_EN_WINDOW_TITLE " - " __DATE__);
                gMain->text.menu.head.title = (const ZT_CHAR*)(SG_TEXT_EN_MENU_HEAD_TITLE);
                gMain->text.menu.head.start = (const ZT_CHAR*)(SG_TEXT_EN_MENU_HEAD_START);
                gMain->text.menu.head.help = (const ZT_CHAR*)(SG_TEXT_EN_MENU_HEAD_HELP);
                gMain->text.menu.head.credits = (const ZT_CHAR*)(SG_TEXT_EN_MENU_HEAD_CREDITS);
                gMain->text.menu.head.exit = (const ZT_CHAR*)(SG_TEXT_EN_MENU_HEAD_EXIT);
                gMain->text.menu.help.title = (const ZT_CHAR*)(SG_TEXT_EN_MENU_HELP_TITLE);
                gMain->text.menu.help.desc = (const ZT_CHAR*)(SG_TEXT_EN_MENU_HELP_DESC);
                gMain->text.menu.help.exit = (const ZT_CHAR*)(SG_TEXT_EN_MENU_HELP_EXIT);
                gMain->text.menu.credits.title = (const ZT_CHAR*)(SG_TEXT_EN_MENU_CREDITS_TITLE);
                gMain->text.menu.credits.desc = (const ZT_CHAR*)(SG_TEXT_EN_MENU_CREDITS_DESC);
                gMain->text.menu.credits.exit = (const ZT_CHAR*)(SG_TEXT_EN_MENU_CREDITS_EXIT);
                gMain->text.hud.menu = (const ZT_CHAR*)(SG_TEXT_EN_HUD_MENU);
                gMain->text.hud.speed.pause = (const ZT_CHAR*)(SG_TEXT_EN_HUD_SPEED_PAUSE);
                gMain->text.hud.speed.faster = (const ZT_CHAR*)(SG_TEXT_EN_HUD_SPEED_FASTER);
                gMain->text.hud.speed.slower = (const ZT_CHAR*)(SG_TEXT_EN_HUD_SPEED_SLOWER);
                gMain->text.hud.game.spawn = (const ZT_CHAR*)(SG_TEXT_EN_HUD_GAME_SPAWN);
                gMain->text.hud.game.wipe = (const ZT_CHAR*)(SG_TEXT_EN_HUD_GAME_WIPE);
                gMain->text.hud.game.save = (const ZT_CHAR*)(SG_TEXT_EN_HUD_GAME_SAVE);
                gMain->text.hud.game.load = (const ZT_CHAR*)(SG_TEXT_EN_HUD_GAME_LOAD);
                gMain->text.hud.camera.zoomIn = (const ZT_CHAR*)(SG_TEXT_EN_HUD_CAMERA_ZOOM_IN);
                gMain->text.hud.camera.zoomOut = (const ZT_CHAR*)(SG_TEXT_EN_HUD_CAMERA_ZOOM_OUT);
                gMain->text.hud.camera.reset = (const ZT_CHAR*)(SG_TEXT_EN_HUD_CAMERA_RESET);
                break;
            default:
                break;
        }
    }
}

#endif //SEAGULL_TEXT_C_INCLUDED
