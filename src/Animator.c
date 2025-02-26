//------------------------------------------------
// Copyright (C) 2025 杨锦熠 - All Rights Reserved
// Author: 杨锦熠
// Date: Fuburary 2025
//------------------------------------------------
#include <stdio.h>
#include "Animator.h"

static FILE* frame;
static fpos_t line[31];
static int frame_cnt = 0, gmvHeight = 0, gmvWidth = 0;
static char frame_name[22] = "./frames/frame000.ppm";
static gmvAttrib att;

// hardcode for all single digits, one at a line
// nums[d][] stands for digit d
static char nums[10][35] = {
    "@\0\0@@\0@@\0@\0@@\0@\0@@\0@\0@@\0@\0@@\0@@\0\0@@",
    "@@\0@@\0\0\0@@@@\0@@@@\0@@@@\0@@@@\0@@\0\0\0\0@",
    "@\0\0@@\0@@\0@@@@\0@@@\0@@@\0@@@\0@@@@\0\0\0\0@",
    "@\0\0@@\0@@\0@@@@\0@@\0\0@@@@@\0@\0@@\0@@\0\0@@",
    "@@@\0@@@\0\0@@\0@\0@\0@@\0@\0\0\0\0@@@@\0@@@@\0@",
    "\0\0\0\0@\0@@@@\0@@@@\0\0\0@@@@@\0@\0@@\0@@\0\0@@",
    "@\0\0@@\0@@\0@\0@@@@\0\0\0@@\0@@\0@\0@@\0@@\0\0@@",
    "\0\0\0\0@@@@\0@@@\0@@@@\0@@@\0@@@@\0@@@@\0@@@",
    "@\0\0@@\0@@\0@\0@@\0@@\0\0@@\0@@\0@\0@@\0@@\0\0@@",
    "@\0\0@@\0@@\0@\0@@\0@@\0\0\0@@@@\0@\0@@\0@@\0\0@@"
}, letters[2][216] = {
    "333000003303330000000003300333330003"
    "000333333003000033333003000003333303"
    "300000333333330000033333333000003333"
    "333300000333033330000033003333000003"
    "003333300000000333330000000333330000"
    "000333300003000000000033033300000333",
    "000000000000000000000000003330033300"
    "033330033330333330033333333330033333"
    "333330033333333330033333333330033333"
    "333330033333333330033333333330033333"
    "333330033333333330033333333330033333"
    "333330033333333330033333330000000033"
};

#define TOP_X            0  //  2, 2, 2, 2, 3, 4, 5
#define BOTTOM_X         1  // 28,28,28,28,27,26,25
#define LEFT_Y           3  //  2, 3, 4, 5, 2, 2, 2
#define RIGHT_Y          4  // 28,27,26,25,28,28,28
#define TOP_X_LEFT_Y     5  //  1, 2, 2, 3, 3, 0, 0
#define BOTTOM_X_RIGHT_Y 6  // 29,28,28,27,27, 0, 0
#define TOP_Y_LEFT_X     7  // 15,16,14,13,17, 0, 0
#define BOTTOM_Y_RIGHT_X 8  // 15,14,16,13,17, 0, 0

// hardcode for all coordinates of arrows
/*
static char arrows_x[][7] = { {2,2,2,2,3,4,5}, { 1, 2, 2, 3, 3,0,0},  }
static char arrows_y[][7] = { {2,3,4,5,2,2,2}, {15,14,16,13,17,0,0} }
*/

void gmvInit(int height, int width)
{
    gmvHeight = height, gmvWidth = width;
}

static void put_color(gmvColor color)
{
    for (int i = 1; i < 30; i++)
        for (int j = 1; j < 30; j++)  tcell[i][j] = color;
}

static void put_arrow(gmvArrow arrow)
{
    switch (arrow) {
        case GMV_NAARROW:       break;
        case GMV_TOP_LEFT:      tcell[2][2]   = tcell[2][3]   = tcell[2][4]   = tcell[2][5]   = tcell[3][2]   = tcell[4][2]   = tcell[5][2]   = '\0'; break;
        case GMV_TOP:           tcell[1][15]  = tcell[2][14]  = tcell[2][16]  = tcell[3][13]  = tcell[3][17]  = '\0';  break;
        case GMV_TOP_RIGHT:     tcell[2][27]  = tcell[2][26]  = tcell[2][25]  = tcell[2][24]  = tcell[3][27]  = tcell[4][27]  = tcell[5][27]  = '\0'; break;
        case GMV_LEFT:          tcell[15][1]  = tcell[14][2]  = tcell[16][2]  = tcell[13][3]  = tcell[17][3]  = '\0';  break;
        case GMV_RIGHT:         tcell[15][29] = tcell[14][28] = tcell[16][28] = tcell[13][27] = tcell[17][27] = '\0';  break;
        case GMV_BOTTOM_LEFT:   tcell[28][2]  = tcell[28][3]  = tcell[28][4]  = tcell[28][5]  = tcell[27][2]  = tcell[26][2]  = tcell[25][2]  = '\0'; break;
        case GMV_BOTTOM:        tcell[29][15] = tcell[28][14] = tcell[28][16] = tcell[27][13] = tcell[27][17] = '\0';  break;
        case GMV_BOTTOM_RIGHT:  tcell[28][28] = tcell[28][27] = tcell[28][26] = tcell[28][25] = tcell[27][28] = tcell[26][28] = tcell[25][28] = '\0'; break;
    }
}

static void put_num(int num)
{
    if (num == GMV_NAN)  return;
    for (int offs = 20; num; num /= 10, offs -= 5)
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 5; j++)
                if (!nums[num % 10][i * 5 + j])
                    tcell[12 + i][offs + j] = nums[num % 10][i * 5 + j];
}

void writeFrame()
{
    if (!(gmvHeight || gmvWidth)) {
        printf("Call gmvInit(int heighg, int width) first!\n");
        return;
    }
    int cnt = frame_cnt;
    for (int i = 0; cnt; i++, cnt /= 10)
        frame_name[16 - i] = cnt % 10 + '0';
    frame_cnt++;
    printf("writing %s\n", frame_name + 9);
    frame = fopen(frame_name, "w");
    // print the ppm file header
    fprintf(frame, "P3\n%d %d\n3", 31 * gmvWidth, 31 * gmvHeight);
    // set the black border for tcell[][]
    for (int i = 0; i < 31; i++)  tcell[0][i] = tcell[i][0] = tcell[30][i] = tcell[i][30] = 0;
    // write the yth line
    for (int y = 0; y < gmvHeight; y++) {
        // preserve writing space for this line of BLOCKS
        for (int i = 0; i < 31; i++) {
            fprintf(frame, "\n");
            fgetpos(frame, line + i);
            for (int j = 0; j < gmvWidth; j++)
                fprintf(frame, ".............................................................."
                    ".............................................................."
                    "..............................................................");
        }
        // iterate through each cell in the line
        for (int x = 0; x < gmvWidth; x++) {
            gmvConfig(x, y, &att);
            put_color(att.color);
            put_arrow(att.arrow);
            put_num(att.num);
            for (int i = 0; i < 31; i++) {
                fsetpos(frame, line + i);
                for (int j = 0; j < 31; j++)
                    fprintf(frame, "%d %d %d ", (tcell[i][j] & GMV_RED) >> 4, (tcell[i][j] & GMV_GREEN) >> 2, tcell[i][j] & GMV_BLUE);
                fgetpos(frame, line + i);
            }
        }
    }
    fclose(frame);
}