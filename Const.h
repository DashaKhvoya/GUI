#pragma once

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <unistd.h>

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

enum TextureID {
  WHITE_TEXTURE_ID,
  BLACK_TEXTURE_ID,
  GRAY_TEXTURE_ID,
  BROWN_TEXTURE_ID,
  PURPLE_TEXTURE_ID,
  SALMON_TEXTURE_ID,
  LILAC_TEXTURE_ID,
  PINK_TEXTURE_ID,
  YELLOW_TEXTURE_ID,
  TURQUOISE_TEXTURE_ID,
  GREEN_TEXTURE_ID,
  ORANGE_TEXTURE_ID,
  PEACH_TEXTURE_ID,
  BEIGE_TEXTURE_ID,
  EXAMPLE_TEXTURE_ID,
  WALL_TEXTURE_ID,
  ICON_TEXTURE_ID,
  CLOSE_TEXTURE_ID,
  MINUS_TEXTURE_ID,
  CANVAS_MANAGER_TEXTURE_ID,
  CANVAS_CLOSE_TEXTURE_ID,
  UP_TEXTURE_ID,
  DOWN_TEXTURE_ID,
  SCROLLBAR_TEXTURE_ID,
  SIZE_BUTTON_TEXTURE_ID,
  BRUSH_TEXTURE_ID,
  BRUSH_NEG_TEXTURE_ID,
  PENCIL_TEXTURE_ID,
  PENCIL_NEG_TEXTURE_ID,
  ERASER_TEXTURE_ID,
  ERASER_NEG_TEXTURE_ID,
  TOOL_TEXTURE_ID,
  PALETTE_TEXTURE_ID,
  CANVAS_ID,
  SCROLLBAR_PIXEL_ID
};

static const size_t ColorID[] = {WHITE_TEXTURE_ID,
                                 BLACK_TEXTURE_ID,
                                 GRAY_TEXTURE_ID,
                                 BROWN_TEXTURE_ID,
                                 PURPLE_TEXTURE_ID,
                                 SALMON_TEXTURE_ID,
                                 LILAC_TEXTURE_ID,
                                 PINK_TEXTURE_ID,
                                 YELLOW_TEXTURE_ID,
                                 TURQUOISE_TEXTURE_ID,
                                 GREEN_TEXTURE_ID,
                                 ORANGE_TEXTURE_ID,
                                 PEACH_TEXTURE_ID,
                                 BEIGE_TEXTURE_ID,};

static const char* TEXTURES[] = {
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/color/white.png",                 //|WHITE_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/color/black.png",                 //|BLACK_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/color/gray.png",                  //|GRAY_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/color/brown.png",                 //|BROWN_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/color/purple.png",                //|PURPLE_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/color/salmon.png",                //|SALMON_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/color/lilac.png",                 //|LILAC_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/color/pink.png",                  //|PINK_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/color/yellow.png",                //|YELLOW_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/color/turquoise.png",             //|TURQUOISE_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/color/green.png",                 //|GREEN_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/color/orange.png",                //|ORANGE_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/color/peach.png",                 //|PEACH_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/color/beige.png",                 //|BEIGE_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/example.jpg",                     //|EXAMPLE_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/wall.png",                        //|WALL_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/icon.png",                        //|ICON_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/close.png",                       //|CLOSE_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/minus.png",                       //|MINUS_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/canvas/canvas_manager.png",       //|CANVAS_MANAGER_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/canvas/canvas_close.png",         //|CANVAS_CLOSE_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/scrollbar/up.png",                //|UP_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/scrollbar/down.png",              //|DOWN_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/scrollbar/scrollbar.png",         //|SCROLLBAR_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/scrollbar/scrollbar_button.png",  //|SIZE_BUTTON_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/instrument/brush.png",            //|BRUSH_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/instrument/brush_neg.png",        //|BRUSH_NEG_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/instrument/pencil.png",           //|PENCIL_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/instrument/pencil_neg.png",       //|PENCIL_NEG_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/instrument/eraser.png",           //|ERASER_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/instrument/eraser_neg.png",       //|ERASER_NEG_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/instrument/instruments.png",      //|TOOL_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/color/palette.png",               //|PALETTE_TEXTURE_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/canvas/canvas.png",               //|CANVAS_ID
  "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/img/scrollbar/pixel.png"              //|SCROLLBAR_PIXEL_ID
};

static const size_t NUMBER_OF_TEXTURES = 35;

static const Color BLACK_COLOR = {0, 0, 0, 255};
static const Color WHITE_COLOR = {255, 255, 255, 255};

static const int BEGIN_SIZE = 25;

static const int TOP_INDENT = 10;
static const int LEFT_INDENT = 15;
static const int BEGIN_INDENT = 5;
static const char* FONT_TTF_WAY = "/Users/dashabaranchikova/Documents/3_sem/ded/GUI_2.0/shrift.ttf";

static const int EXAMPLE_X_POS  = 0;
static const int EXAMPLE_Y_POS  = 0;
static const int EXAMPLE_WIDTH  = 1103;
static const int EXAMPLE_HEIGHT = 40;

static const int MENU_WIDTH  = 80;
static const int MENU_HEIGHT = 40;

static const int WALL_X_POS  = 0;
static const int WALL_Y_POS  = EXAMPLE_Y_POS + EXAMPLE_HEIGHT;
static const int WALL_WIDTH  = 1103;
static const int WALL_HEIGHT = 806;

static const int ICON_WIDTH  = 40;
static const int ICON_HEIGHT = 40;

static const int COLOR_X_POS  = EXAMPLE_X_POS + 150;
static const int COLOR_Y_POS  = EXAMPLE_Y_POS + 137 + 464 + 50;
static const int COLOR_WIDTH  = 43;
static const int COLOR_HEIGHT = 43;

static const int CLOSE_WIDTH  = 30;
static const int CLOSE_HEIGHT = 30;

static const int MINUS_WIDTH  = 40;
static const int MINUS_HEIGHT = 20;

static const int CANVAS_MANAGER_X_POS  = EXAMPLE_X_POS + 150;
static const int CANVAS_MANAGER_Y_POS  = EXAMPLE_Y_POS + 100;
static const int CANVAS_MANAGER_WIDTH  = 800;
static const int CANVAS_MANAGER_HEIGHT = 37;

static const int CANVAS_IMG_WIDTH  = 800;
static const int CANVAS_IMG_HEIGHT = 464;

static const int CANVAS_WIDTH  = 798;
static const int CANVAS_HEIGHT = 462;

static const int CANVAS_CLOSE_X_INDENT = 17;
static const int CANVAS_CLOSE_Y_INDENT = 8;
static const int CANVAS_CLOSE_WIDTH    = 21;
static const int CANVAS_CLOSE_HEIGHT   = 21;

static const int UP_WIDTH  = 30;
static const int UP_HEIGHT = 30;

static const int DOWN_WIDTH  = UP_WIDTH;
static const int DOWN_HEIGHT = UP_HEIGHT;

static const int SCROLLBAR_X_POS  = 15;
static const int SCROLLBAR_Y_POS  = 280;
static const int SCROLLBAR_WIDTH  = 30;
static const int SCROLLBAR_HEIGHT = 145;

static const int SIZE_BUTTON_WIDTH  = UP_WIDTH;
static const int SIZE_BUTTON_HEIGHT = UP_HEIGHT;

static const int NUMBER_OF_TOOLS = 3;
static const int TOOL_WIDTH  = 60;
static const int TOOL_HEIGHT = 50;
static const int INSTRUMENT_X_POS  = 15;
static const int INSTRUMENT_Y_POS  = 100;
static const int INSTRUMENT_WIDTH  = 120;
static const int INSTRUMENT_HEIGHT = 21;

static const int NUMBER_OF_COLOR = 14;
static const Color COLORS[] = {{255, 255, 255, 255}, {0,   0,   0,   255}, {135, 136, 137, 255}, {184, 115, 119, 255}, {192, 149, 191, 255}, {249, 152, 144, 255}, {130, 128, 254, 255},
                              {255, 181, 251, 255}, {231, 229, 143, 255}, {43,  192, 212, 255}, {151, 202, 132, 255}, {230, 149, 54,  255}, {246, 221, 212, 255}, {253, 234, 227, 255}};
static const int PALETTE_X_POS  = EXAMPLE_X_POS + 150;
static const int PALETTE_Y_POS  = EXAMPLE_Y_POS + 137 + 464 + 50;
static const int PALETTE_WIDTH  = 300;
static const int PALETTE_HEIGHT = 85;
