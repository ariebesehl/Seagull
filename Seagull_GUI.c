/*** Copyright (C) 2020 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#ifndef SEAGULL_GUI_C_INCLUDED
#define SEAGULL_GUI_C_INCLUDED

#include "Seagull_GUI.h"

void SGUI_Init(void) {
    gMain.font.window = ZTK_FontNew(NULL, (ZT_CHAR*)SG_FONT_WINDOW, ZTK_DEFAULT_FONT_SIZE, ZTK_FONT_STYLE_NORMAL, ZTK_DEFAULT_FONT_COLOR);
    gMain.font.title = ZTK_FontNew(NULL, (ZT_CHAR*)SG_FONT_TITLE, ZTK_DEFAULT_FONT_SIZE, ZTK_FONT_STYLE_NORMAL | ZTK_FONT_STYLE_ALIGN_CENTER, ZTK_DEFAULT_FONT_COLOR);
    gMain.font.desc = ZTK_FontNew(NULL, (ZT_CHAR*)SG_FONT_TITLE, ZTK_DEFAULT_FONT_SIZE, ZTK_FONT_STYLE_NORMAL | ZTK_FONT_STYLE_ALIGN_CENTER, ZTK_DEFAULT_FONT_COLOR);
    ZTK_FontSet(gMain.font.window);
    ZTK_PrinterInit(gMain.font.window);
    ZUI_HostNew();
    gMain.user.menu = SG_DEFAULT_FLAG_GUI_MENU;
    gMain.gui.menu.box = ZUI_BoxNew(SG_ID_GUI_MENU_HEAD_BOX, NULL, 0x101010bf, 0xffffffff);
    gMain.gui.menu.head.title = ZUI_LabelNewFromFont(SG_ID_GUI_MENU_HEAD_TITLE, NULL, gMain.text.menu.head.title, gMain.font.title);
    gMain.gui.menu.head.start = ZUI_ButtonNew(SG_ID_GUI_MENU_HEAD_START, NULL, gMain.text.menu.head.start);
    gMain.gui.menu.head.help = ZUI_ButtonNew(SG_ID_GUI_MENU_HEAD_HELP, NULL, gMain.text.menu.head.help);
    gMain.gui.menu.head.credits = ZUI_ButtonNew(SG_ID_GUI_MENU_HEAD_CREDITS, NULL, gMain.text.menu.head.credits);
    gMain.gui.menu.head.exit = ZUI_ButtonNew(SG_ID_GUI_MENU_HEAD_EXIT, NULL, gMain.text.menu.head.exit);
    gMain.gui.menu.help.title = ZUI_LabelNewFromFont(SG_ID_GUI_MENU_HELP_TITLE, NULL, gMain.text.menu.help.title, gMain.font.title);
    gMain.gui.menu.help.desc = ZUI_LabelNewFromFont(SG_ID_GUI_MENU_HELP_DESC, NULL, gMain.text.menu.help.desc, gMain.font.desc);
    gMain.gui.menu.help.exit = ZUI_ButtonNew(SG_ID_GUI_MENU_HELP_EXIT, NULL, gMain.text.menu.help.exit);
    gMain.gui.menu.credits.title = ZUI_LabelNewFromFont(SG_ID_GUI_MENU_CREDITS_TITLE, NULL, gMain.text.menu.credits.title, gMain.font.title);
    gMain.gui.menu.credits.desc = ZUI_LabelNewFromFont(SG_ID_GUI_MENU_CREDITS_DESC, NULL, gMain.text.menu.credits.desc, gMain.font.desc);
    gMain.gui.menu.credits.exit = ZUI_ButtonNew(SG_ID_GUI_MENU_CREDITS_EXIT, NULL, gMain.text.menu.credits.exit);
    gMain.gui.hud.box.top = ZUI_BoxNew(SG_ID_GUI_HUD_BOX_TOP, NULL, 0x101010bf, 0xffffffff);
    //ZUI_BorderSize(gMain.gui.hud.box.top, 0);
    gMain.gui.hud.box.bottom = ZUI_BoxNew(SG_ID_GUI_HUD_BOX_BOTTOM, NULL, 0x101010bf, 0xffffffff);
    gMain.gui.hud.menu = ZUI_ButtonNew(SG_ID_GUI_HUD_MENU, NULL, gMain.text.hud.menu);
    gMain.gui.hud.speed.pause = ZUI_ButtonNew(SG_ID_GUI_HUD_SPEED_PAUSE, NULL, gMain.text.hud.speed.pause);
    gMain.gui.hud.speed.faster = ZUI_ButtonNew(SG_ID_GUI_HUD_SPEED_FASTER, NULL, gMain.text.hud.speed.faster);
    gMain.gui.hud.speed.slower = ZUI_ButtonNew(SG_ID_GUI_HUD_SPEED_SLOWER, NULL, gMain.text.hud.speed.slower);
    gMain.gui.hud.game.spawn = ZUI_ButtonNew(SG_ID_GUI_HUD_GAME_SPAWN, NULL, gMain.text.hud.game.spawn);
    gMain.gui.hud.game.wipe = ZUI_ButtonNew(SG_ID_GUI_HUD_GAME_WIPE, NULL, gMain.text.hud.game.wipe);
    gMain.gui.hud.game.save = ZUI_ButtonNew(SG_ID_GUI_HUD_GAME_SAVE, NULL, gMain.text.hud.game.save);
    gMain.gui.hud.game.load = ZUI_ButtonNew(SG_ID_GUI_HUD_GAME_LOAD, NULL, gMain.text.hud.game.load);
    gMain.gui.hud.camera.zoomIn = ZUI_ButtonNew(SG_ID_GUI_HUD_CAMERA_ZOOM_IN, NULL, gMain.text.hud.camera.zoomIn);
    gMain.gui.hud.camera.zoomOut = ZUI_ButtonNew(SG_ID_GUI_HUD_CAMERA_ZOOM_OUT, NULL, gMain.text.hud.camera.zoomOut);
    gMain.gui.hud.camera.reset = ZUI_ButtonNew(SG_ID_GUI_HUD_CAMERA_RESET, NULL, gMain.text.hud.camera.reset);
    SGUI_Size();
    SGUI_Menu();
}
void SGUI_Size(void){
    // CALC SIZES
    gMain.dim.font = ZTK_GetHeight() * SG_HEIGHT_GUI_FONT;
    if (gMain.dim.font > 24) {gMain.dim.font = 24;}
    gMain.dim.fontBig = ZTK_GetHeight() * SG_HEIGHT_GUI_FONT_BIG;
    if (gMain.dim.fontBig > 36) {gMain.dim.fontBig = 36;}
    ZTM_Point(&(gMain.dim.buttonMenu), ZTK_GetWidth() * SG_WIDTH_GUI_MENU_BUTTON, ZTK_GetHeight() * SG_HEIGHT_GUI_MENU_BUTTON);
    ZTM_Point(&(gMain.dim.buttonHUD), ZTK_GetWidth() * SG_WIDTH_GUI_HUD_BUTTON, ZTK_GetHeight() * SG_HEIGHT_GUI_HUD_BUTTON);
    if (gMain.dim.buttonHUD.y > 32) {gMain.dim.buttonHUD.y = 32;}
    ZTM_Point(&(gMain.dim.buttonHUDHalf), ZTK_GetWidth() * SG_WIDTH_GUI_HUD_BUTTON / 2, gMain.dim.buttonHUD.y);
    // FONTS
    ZTK_FontSize(gMain.font.window, gMain.dim.font);
    ZTK_FontSize(gMain.font.title, gMain.dim.fontBig);
    ZTK_FontSize(gMain.font.desc, gMain.dim.font);
    // MENU SIZE
	ZUI_SizeRelative(gMain.gui.menu.box, 0.25, 0.75);
	ZUI_Size(gMain.gui.menu.head.title, NULL);
	ZUI_Size(gMain.gui.menu.help.title, NULL);
	ZUI_Size(gMain.gui.menu.credits.title, NULL);
	ZUI_Size(gMain.gui.menu.help.desc, NULL);
	ZUI_Size(gMain.gui.menu.credits.desc, NULL);
	ZUI_Size(gMain.gui.menu.head.start, (const ZT_POINT*)&(gMain.dim.buttonMenu));
	ZUI_Size(gMain.gui.menu.head.help, (const ZT_POINT*)&(gMain.dim.buttonMenu));
	ZUI_Size(gMain.gui.menu.head.credits, (const ZT_POINT*)&(gMain.dim.buttonMenu));
	ZUI_Size(gMain.gui.menu.head.exit, (const ZT_POINT*)&(gMain.dim.buttonMenu));
	ZUI_Size(gMain.gui.menu.help.exit, (const ZT_POINT*)&(gMain.dim.buttonMenu));
	ZUI_Size(gMain.gui.menu.credits.exit, (const ZT_POINT*)&(gMain.dim.buttonMenu));
	// MENU POS
	ZUI_PosCenterRelative(gMain.gui.menu.box, 0.5, 0.5);
	ZUI_PosCenterRelative(gMain.gui.menu.head.title, 0.5, 0.25);
	ZUI_PosCenterRelative(gMain.gui.menu.help.title, 0.5, 0.25);
	ZUI_PosCenterRelative(gMain.gui.menu.credits.title, 0.5, 0.25);
	ZUI_PosCenterRelative(gMain.gui.menu.help.desc, 0.5, 0.5);
	ZUI_PosCenterRelative(gMain.gui.menu.credits.desc, 0.5, 0.5);
	ZUI_PosCenterRelative(gMain.gui.menu.head.start, 0.5, 0.375);
	ZUI_PosCenterRelative(gMain.gui.menu.head.help, 0.5, 0.5);
	ZUI_PosCenterRelative(gMain.gui.menu.head.credits, 0.5, 0.625);
	ZUI_PosCenterRelative(gMain.gui.menu.head.exit, 0.5, 0.75);
	ZUI_PosCenterRelative(gMain.gui.menu.help.exit, 0.5, 0.75);
	ZUI_PosCenterRelative(gMain.gui.menu.credits.exit, 0.5, 0.75);
    // HUD SIZE
	ZUI_SizeFromInteger(gMain.gui.hud.box.top, ZTK_GetWidth() + 2 * ZUI_GetBorderSize(gMain.gui.hud.box.top), gMain.dim.buttonHUD.y + 2 * ZUI_GetBorderSize(gMain.gui.hud.box.top));
	ZUI_SizeFromInteger(gMain.gui.hud.box.bottom, ZTK_GetWidth() + 2 * ZUI_GetBorderSize(gMain.gui.hud.box.bottom), gMain.dim.buttonHUD.y + 2 * ZUI_GetBorderSize(gMain.gui.hud.box.bottom));
	ZUI_Size(gMain.gui.hud.menu, (const ZT_POINT*)&(gMain.dim.buttonHUD));
	ZUI_Size(gMain.gui.hud.speed.slower, (const ZT_POINT*)&(gMain.dim.buttonHUDHalf));
	ZUI_Size(gMain.gui.hud.speed.pause, (const ZT_POINT*)&(gMain.dim.buttonHUD));
	ZUI_Size(gMain.gui.hud.speed.faster, (const ZT_POINT*)&(gMain.dim.buttonHUDHalf));
	ZUI_Size(gMain.gui.hud.game.spawn, (const ZT_POINT*)&(gMain.dim.buttonHUD));
	ZUI_Size(gMain.gui.hud.game.wipe, (const ZT_POINT*)&(gMain.dim.buttonHUD));
	ZUI_Size(gMain.gui.hud.game.save, (const ZT_POINT*)&(gMain.dim.buttonHUD));
	ZUI_Size(gMain.gui.hud.game.load, (const ZT_POINT*)&(gMain.dim.buttonHUD));
	ZUI_Size(gMain.gui.hud.camera.zoomOut, (const ZT_POINT*)&(gMain.dim.buttonHUDHalf));
	ZUI_Size(gMain.gui.hud.camera.reset, (const ZT_POINT*)&(gMain.dim.buttonHUD));
	ZUI_Size(gMain.gui.hud.camera.zoomIn, (const ZT_POINT*)&(gMain.dim.buttonHUDHalf));
    // HUD POS
    ZUI_PosFromInteger(gMain.gui.hud.box.top, -ZUI_GetBorderSize(gMain.gui.hud.box.top), -ZUI_GetBorderSize(gMain.gui.hud.box.top));
    ZUI_PosFromInteger(gMain.gui.hud.box.bottom, -ZUI_GetBorderSize(gMain.gui.hud.box.bottom), ZTK_GetHeight() - gMain.dim.buttonHUD.y - ZUI_GetBorderSize(gMain.gui.hud.box.bottom));
    ZUI_PosFromInteger(gMain.gui.hud.menu, ZTK_GetWidth() - gMain.dim.buttonHUD.x, 0);
    ZUI_XRelative(gMain.gui.hud.speed.slower, 0.0);
    ZUI_XRelative(gMain.gui.hud.speed.pause, SG_WIDTH_GUI_HUD_BUTTON / 2);
    ZUI_XRelative(gMain.gui.hud.speed.faster, 3 * SG_WIDTH_GUI_HUD_BUTTON / 2);
    ZUI_XRelative(gMain.gui.hud.game.spawn, 0.5 - 2 * SG_WIDTH_GUI_HUD_BUTTON);
    ZUI_XRelative(gMain.gui.hud.game.wipe, 0.5 - SG_WIDTH_GUI_HUD_BUTTON);
    ZUI_XRelative(gMain.gui.hud.game.save, 0.5);
    ZUI_XRelative(gMain.gui.hud.game.load, 0.5 + SG_WIDTH_GUI_HUD_BUTTON);
    ZUI_XRelative(gMain.gui.hud.camera.zoomOut, 1.0 - 2 * SG_WIDTH_GUI_HUD_BUTTON);
    ZUI_XRelative(gMain.gui.hud.camera.reset, 1.0 - 3 * SG_WIDTH_GUI_HUD_BUTTON / 2);
    ZUI_XRelative(gMain.gui.hud.camera.zoomIn, 1.0 - SG_WIDTH_GUI_HUD_BUTTON / 2);
    ZUI_Y(gMain.gui.hud.speed.slower, ZTK_GetHeight() - gMain.dim.buttonHUD.y);
    ZUI_Y(gMain.gui.hud.speed.pause, ZTK_GetHeight() - gMain.dim.buttonHUD.y);
    ZUI_Y(gMain.gui.hud.speed.faster, ZTK_GetHeight() - gMain.dim.buttonHUD.y);
    ZUI_Y(gMain.gui.hud.game.spawn, ZTK_GetHeight() - gMain.dim.buttonHUD.y);
    ZUI_Y(gMain.gui.hud.game.wipe, ZTK_GetHeight() - gMain.dim.buttonHUD.y);
    ZUI_Y(gMain.gui.hud.game.save, ZTK_GetHeight() - gMain.dim.buttonHUD.y);
    ZUI_Y(gMain.gui.hud.game.load, ZTK_GetHeight() - gMain.dim.buttonHUD.y);
    ZUI_Y(gMain.gui.hud.camera.zoomOut, ZTK_GetHeight() - gMain.dim.buttonHUD.y);
    ZUI_Y(gMain.gui.hud.camera.reset, ZTK_GetHeight() - gMain.dim.buttonHUD.y);
    ZUI_Y(gMain.gui.hud.camera.zoomIn, ZTK_GetHeight() - gMain.dim.buttonHUD.y);

    ZT_I lYPrinter = (gMain.dim.buttonHUD.y - gMain.dim.font) / 2;
    ZTM_Point(&(gMain.pos.fps), ZTK_GetWidth() * (SG_WIDTH_GUI_HUD_BUTTON / 8), lYPrinter);
    ZTM_Point(&(gMain.pos.tick), ZTK_GetWidth() * (0.5 - SG_WIDTH_GUI_HUD_BUTTON), lYPrinter);
    ZTM_Point(&(gMain.pos.pop), ZTK_GetWidth() * 0.5, lYPrinter);
}
void SGUI_Menu(void) {
    for (ZT_INDEX i = 0; i < (sizeof(gMain.gui.menu) / sizeof(ZUI_ELEMENT*)); i++) {
        ZUI_ELEMENT* lElement = *((ZUI_ELEMENT**)&(gMain.gui.menu) + i);
        ZUI_Bury(lElement);
    }
    void* lMenu = NULL;
    ZT_INDEX lLength = 0;
    switch (gMain.user.menu) {
        case SG_FLAG_GUI_MENU_HEAD:
            lMenu = &(gMain.gui.menu.head);
            lLength = (sizeof(gMain.gui.menu.head) / sizeof(ZUI_ELEMENT*));
            break;
        case SG_FLAG_GUI_MENU_HELP:
            lMenu = &(gMain.gui.menu.help);
            lLength = (sizeof(gMain.gui.menu.help) / sizeof(ZUI_ELEMENT*));
            break;
        case SG_FLAG_GUI_MENU_CREDITS:
            lMenu = &(gMain.gui.menu.credits);
            lLength = (sizeof(gMain.gui.menu.credits) / sizeof(ZUI_ELEMENT*));
            break;
        default:
            break;
    }
    if (lMenu != NULL) {
        SGG_PauseSystem(ZT_TRUE);
        for (ZT_INDEX i = 0; i < (sizeof(gMain.gui.hud) / sizeof(ZUI_ELEMENT*)); i++) {
            ZUI_ELEMENT* lElement = *((ZUI_ELEMENT**)&(gMain.gui.hud) + i);
            ZUI_Bury(lElement);
        }
        ZUI_Restore(gMain.gui.menu.box);
        for (ZT_INDEX i = 0; i < lLength; i++) {
            ZUI_ELEMENT* lElement = *((ZUI_ELEMENT**)lMenu + i);
            ZUI_Restore(lElement);
        }
    } else {
        SGG_PauseSystem(ZT_FALSE);
        for (ZT_INDEX i = 0; i < (sizeof(gMain.gui.hud) / sizeof(ZUI_ELEMENT*)); i++) {
            ZUI_ELEMENT* lElement = *((ZUI_ELEMENT**)&(gMain.gui.hud) + i);
            ZUI_Restore(lElement);
        }
    }
}
void SGUI_Exit(void) {
    ZUI_HostFree();
    ZTK_PrinterQuit();
    ZTK_FontFree(gMain.font.window);
    ZTK_FontFree(gMain.font.title);
    ZTK_FontFree(gMain.font.desc);
}

#endif //SEAGULL_GUI_C_INCLUDED
