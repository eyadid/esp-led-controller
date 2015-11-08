/* 
 * File:   LEDScroller.h
 * Author: Yadid
 *
 * Created on August 12, 2015, 8:18 PM
 */

#include "SystemConfiguration.h"



#ifndef LEDSCROLLER_H
#define	LEDSCROLLER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define RCK               LATEbits.LATE2

#define SRCK              LATEbits.LATE6
#define COLOR_BIT_GREEN_1 LATEbits.LATE5
#define COLOR_BIT_RED_1   LATEbits.LATE7

#define SRCK2             LATFbits.LATF1
#define COLOR_BIT_GREEN_2 LATFbits.LATF0
#define COLOR_BIT_RED_2   LATEbits.LATE4

#define SRCK3             LATDbits.LATD6
#define COLOR_BIT_GREEN_3 LATDbits.LATD5
#define COLOR_BIT_RED_3   LATDbits.LATD7

#define ROW_A             LATEbits.LATE1
#define ROW_B             LATEbits.LATE0
#define ROW_C             LATEbits.LATE3

#define BLINK_TOTAL 600
#define BLINK_SWITCH 300

#define ROWS_COUNT_3

#define LETTERS_COUNT 250
#define LETTER_HEIGHT 10

#define COLOR_OFF           0
#define COLOR_RED           1
#define COLOR_GREEN         2
#define COLOR_ORANGE        3
#define COLOR_BLINK_RED     4
#define COLOR_BLINK_GREEN   8
#define COLOR_BLINK_ORANGE  12

#define DISPLAY_WIDTH       160
#define DISPLAY_WORDS       (DISPLAY_WIDTH / 8)
#define DISPLAY_ROWS        3
#define DISPLAY_ROW_HEIGHT  8

extern void LED_InitScroller();

extern void LED_SetColor(uint8_t color);
extern void LED_WriteText(const uint8_t *text);
extern void LED_Paint();
extern void LED_Clear();

#ifdef	__cplusplus
}
#endif

#endif	/* LEDSCROLLER_H */



/*

*/
