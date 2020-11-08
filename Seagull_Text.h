/*** Copyright (C) 2020 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#ifndef SEAGULL_TEXT_H_INCLUDED
#define SEAGULL_TEXT_H_INCLUDED

#include "Seagull.h"

#define SG_TEXT_LANG_EN 0x0
#define SG_TEXT_LANG_DE 0x1
#define SG_DEFAULT_TEXT_LANG SG_TEXT_LANG_EN

#define SG_TEXT_EN_MENU_HEAD_TITLE "Seagull"
#define SG_TEXT_EN_MENU_HEAD_START "Start"
#define SG_TEXT_EN_MENU_HEAD_HELP "Help"
#define SG_TEXT_EN_MENU_HEAD_CREDITS "Credits"
#define SG_TEXT_EN_MENU_HEAD_EXIT "Exit"
#define SG_TEXT_EN_MENU_HELP_TITLE "Help"
#define SG_TEXT_EN_MENU_HELP_DESC "L-MOUSE:\nToggle cell\n\nR-MOUSE:\nMove camera\n\nM-WHEEL:\nZoom"
#define SG_TEXT_EN_MENU_HELP_EXIT "Back"
#define SG_TEXT_EN_MENU_CREDITS_TITLE "Credits"
#define SG_TEXT_EN_MENU_CREDITS_DESC "Seagull:\nAndreas Riebesehl\n\nlibZDK:\nZaidaTek\nAndreas Riebesehl\n"
#define SG_TEXT_EN_MENU_CREDITS_EXIT "Back"
#define SG_TEXT_EN_HUD_MENU "Menu"
#define SG_TEXT_EN_HUD_SPEED_PAUSE "Run/Pause"
#define SG_TEXT_EN_HUD_SPEED_FASTER ">>"
#define SG_TEXT_EN_HUD_SPEED_SLOWER "<<"
#define SG_TEXT_EN_HUD_GAME_SPAWN "Spawn"
#define SG_TEXT_EN_HUD_GAME_WIPE "Wipe"
#define SG_TEXT_EN_HUD_GAME_SAVE "Save"
#define SG_TEXT_EN_HUD_GAME_LOAD "Load"
#define SG_TEXT_EN_HUD_CAMERA_ZOOM_IN "+"
#define SG_TEXT_EN_HUD_CAMERA_ZOOM_OUT "-"
#define SG_TEXT_EN_HUD_CAMERA_RESET "Reset"
#define SG_TEXT_EN_WINDOW_TITLE "Seagull"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void SGTXT_Load(void);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif //SEAGULL_TEXT_H_INCLUDED
