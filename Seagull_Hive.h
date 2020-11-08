/*** Copyright (C) 2020 Andreas Riebesehl
**** This work is licensed under: This work is presently unlicensed.
****
***/
#ifndef SEAGULL_HIVE_H_INCLUDED
#define SEAGULL_HIVE_H_INCLUDED

#include "Seagull.h"

typedef struct {
	struct {
		struct {
			const ZT_CHAR* title;
			const ZT_CHAR* start;
			const ZT_CHAR* help;
			const ZT_CHAR* credits;
			const ZT_CHAR* exit;
		} head;
		struct {
			const ZT_CHAR* title;
			const ZT_CHAR* desc;
			const ZT_CHAR* exit;
		} help;
		struct {
			const ZT_CHAR* title;
			const ZT_CHAR* desc;
			const ZT_CHAR* exit;
		} credits;
	} menu;
	struct {
		const ZT_CHAR* menu;
		struct {
			const ZT_CHAR* pause;
			const ZT_CHAR* faster;
			const ZT_CHAR* slower;
		} speed;
		struct {
			const ZT_CHAR* spawn;
			const ZT_CHAR* wipe;
			const ZT_CHAR* save;
			const ZT_CHAR* load;
		} game;
		struct {
			const ZT_CHAR* zoomIn;
			const ZT_CHAR* zoomOut;
			const ZT_CHAR* reset;
		} camera;
	} hud;
	struct {
		const ZT_CHAR* title;
	} window;
} TEXT_HIVE;

typedef struct {
	struct {
		ZUI_BOX* box;
		struct {
			ZUI_LABEL* title;
			ZUI_BUTTON* start;
			ZUI_BUTTON* help;
			ZUI_BUTTON* credits;
			ZUI_BUTTON* exit;
		} head;
		struct {
			ZUI_LABEL* title;
			ZUI_LABEL* desc;
			ZUI_BUTTON* exit;
		} help;
		struct {
			ZUI_LABEL* title;
			ZUI_LABEL* desc;
			ZUI_BUTTON* exit;
		} credits;
	} menu;
	struct {
		ZUI_BUTTON* menu;
		struct {
			ZUI_BOX* top;
			ZUI_BOX* bottom;
		} box;
		struct {
			ZUI_BUTTON* pause;
			ZUI_BUTTON* faster;
			ZUI_BUTTON* slower;
		} speed;
		struct {
			ZUI_BUTTON* spawn;
			ZUI_BUTTON* wipe;
			ZUI_BUTTON* save;
			ZUI_BUTTON* load;
		} game;
		struct {
			ZUI_BUTTON* zoomIn;
			ZUI_BUTTON* zoomOut;
			ZUI_BUTTON* reset;
		} camera;
	} hud;
} GUI_HIVE;

typedef struct {
    struct {
        ZT_EVENT* window;
        ZT_EVENT* gui;
    } event;
    ZT_PRINTER* printer;
    struct {
        ZT_FONT* window;
        ZT_FONT* title;
        ZT_FONT* desc;
    } font;
	GUI_HIVE gui;
    struct {
        ZT_INDEX fps;
    } counter;
    struct {
        ZT_INDEX fps;
    } stat;
    struct {
        ZT_TIME fps;
        ZT_TIME draw;
    } timestamp;
    struct {
        ZT_TIME fps;
        ZT_TIME draw;
    } timeout;
	struct {
		ZT_FLAG lang;
		ZT_FLAG menu;
	} user;
    struct {
        ZT_POINT buttonMenu;
        ZT_POINT buttonHUD;
        ZT_POINT buttonHUDHalf;
        ZT_I font;
        ZT_I fontBig;
    } dim;
    struct {
        ZT_POINT fps;
        ZT_POINT tick;
        ZT_POINT pop;
    } pos;
    struct {
        ZT_RECT window;
    } rect;
    TEXT_HIVE text;
} APP_HIVE;

#endif // SEAGULL_HIVE_H_INCLUDED
