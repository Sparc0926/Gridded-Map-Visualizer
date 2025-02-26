//------------------------------------------------
// Copyright (C) 2025 杨锦熠 - All Rights Reserved
// Author: 杨锦熠
// Date: Fuburary 2025
//------------------------------------------------
#ifndef GMV_H
#define GMV_H

#define GMV_NAN ((int)0x80000000)

typedef enum gmvColor gmvColor;
typedef enum gmvArrow gmvArrow;
typedef struct gmvAttrib gmvAttrib;

// temperory cell for editing
char tcell[31][31];

enum gmvColor {  // RGB with saturation 3
    GMV_WHITE         = 63,  // (333)_{4}
    GMV_GRAY          = 42,  // (222)_{4}
    GMV_GRAYER        = 21,  // (111)_{4}
    GMV_BLACK         =  0,  // (000)_{4}
    GMV_RED           = 48,  // (300)_{4}
    GMV_DARK_RED      = 32,  // (200)_{4}
    GMV_DARKER_RED    = 16,  // (100)_{4}
    GMV_GREEN         = 12,  // (030)_{4}
    GMV_DARK_GREEN    =  8,  // (020)_{4}
    GMV_DARKER_GREEN  =  4,  // (010)_{4}
    GMV_BLUE          =  3,  // (003)_{4}
    GMV_DARK_BLUE     =  2,  // (002)_{4}
    GMV_DARKER_BLUE   =  1,  // (001)_{4}
    GMV_YELLOW        = 60,  // (330)_{4}
    GMV_DARK_YELLOW   = 40,  // (220)_{4}
    GMV_DARKER_YELLOW = 20,  // (110)_{4}
    GMV_PURPLE        = 51,  // (303)_{4}
    GMV_DARK_PURPLE   = 34,  // (202)_{4}
    GMV_DARKER_PURPLE = 17   // (101)_{4}
};

enum gmvArrow {  // 3 * dx + dy
    GMV_TOP_LEFT, GMV_LEFT, GMV_BOTTOM_LEFT, GMV_TOP, GMV_NAARROW,
    GMV_BOTTOM, GMV_TOP_RIGHT, GMV_RIGHT, GMV_BOTTOM_RIGHT
};

struct gmvAttrib {
    gmvArrow arrow;
    gmvColor color;
    int num, letter;
};

// tell gmv the graph dimension, TODO: call it once before using any gmv functions
void gmvInit(int height, int width);
// user configuration, TODO: define it
void gmvConfig(int x, int y, gmvAttrib* att);
// write the tcell to a new frame
void writeFrame();

#endif//GMV_H