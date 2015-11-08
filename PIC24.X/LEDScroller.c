#include "LEDScroller.h"
#include "Letters.h"
#include "string.h"




unsigned char DisplayBuffer[DISPLAY_ROWS][DISPLAY_WIDTH];

unsigned char ColorBitsGreen[DISPLAY_WIDTH * DISPLAY_ROWS];
unsigned char ColorBitsRed[DISPLAY_WIDTH * DISPLAY_ROWS];
unsigned char ColorBitsBlinkGreen[DISPLAY_WIDTH * DISPLAY_ROWS];
unsigned char ColorBitsBlinkRed[DISPLAY_WIDTH * DISPLAY_ROWS];

unsigned char   cursor_X = 0;
unsigned char   cursor_Y = 0;

unsigned char   write_letter = 0;
unsigned char   write_scan = 0;
unsigned char   write_charWidth = 0;

uint16_t    write_char = 0;

uint8_t write_currentColor = COLOR_GREEN;

uint16_t pnt_blink = 0;
uint8_t pnt_r = 0;
uint8_t pnt_mask = 0b10000000;
uint16_t pnt_address = 0;
#ifdef ROWS_COUNT_3 || ROWS_COUNT_2
uint16_t pnt_address2 = 0;
#endif
#ifdef ROWS_COUNT_3
uint16_t pnt_address3 = 0;
#endif
uint8_t pnt_index = 0;
uint8_t pnt_indexEOF = 0;

void LED_Clear(){
    
  memset(ColorBitsGreen, 0, DISPLAY_WIDTH * DISPLAY_ROWS);
  memset(ColorBitsRed, 0, DISPLAY_WIDTH * DISPLAY_ROWS);
  memset(ColorBitsBlinkGreen, 0, DISPLAY_WIDTH * DISPLAY_ROWS);
  memset(ColorBitsBlinkRed, 0, DISPLAY_WIDTH * DISPLAY_ROWS);

  cursor_X = 0;
  cursor_Y = 0;
}



void SetRow(uint8_t row){
     if(row == 0){
        ROW_A = 0;
        ROW_B = 0;
        ROW_C = 0;
    }else if(row == 1){
        ROW_A = 0;
        ROW_B = 0;
        ROW_C = 1;
    }else if(row == 2){
        ROW_A = 0;
        ROW_B = 1;
        ROW_C = 0;
    }else if(row == 3){
        ROW_A = 0;
        ROW_B = 1;
        ROW_C = 1;
    }else if(row == 4){
        ROW_A = 1;
        ROW_B = 0;
        ROW_C = 0;
    }else if(row == 5){
        ROW_A = 1;
        ROW_B = 0;
        ROW_C = 1;
    }else if(row == 6){
        ROW_A = 1;
        ROW_B = 1;
        ROW_C = 0;
    } if(row == 7) {
        ROW_A = 1;
        ROW_B = 1;
        ROW_C = 1;
    }
}


void LED_SetColor(uint8_t color){
  write_currentColor = color;
}

void LED_Paint(){
    pnt_r++;

    if(pnt_blink > BLINK_TOTAL){
        pnt_blink = 0;
    }else{
        pnt_blink ++;
    }
    
    if(pnt_r == DISPLAY_ROW_HEIGHT){
        pnt_r = 0;
    }

    SetRow(pnt_r);

    pnt_index = (pnt_r * DISPLAY_WORDS);
    pnt_indexEOF = pnt_index + DISPLAY_WORDS;

    for(pnt_address = pnt_index ; pnt_address < pnt_indexEOF; pnt_address++){

#ifdef ROWS_COUNT_3 || ROWS_COUNT_2
        pnt_address2 = pnt_address + DISPLAY_WIDTH;
#endif

#ifdef ROWS_COUNT_3
        pnt_address3 = pnt_address2 + DISPLAY_WIDTH;
#endif

        pnt_mask = 0b10000000;
        
        while(pnt_mask){

            SRCK = 0;
            if((ColorBitsGreen[pnt_address] & pnt_mask) || (ColorBitsBlinkGreen[pnt_address] & pnt_mask && pnt_blink > BLINK_SWITCH)) {
                COLOR_BIT_GREEN_1 = 1;
            }else{
                COLOR_BIT_GREEN_1 = 0;
            }
            if((ColorBitsRed[pnt_address] & pnt_mask) || (ColorBitsBlinkRed[pnt_address] & pnt_mask && pnt_blink > BLINK_SWITCH)) {
                COLOR_BIT_RED_1 = 1;
            }else{
                COLOR_BIT_RED_1 = 0;
            }
            SRCK = 1;


#ifdef ROWS_COUNT_3 || ROWS_COUNT_2

            SRCK2 = 0;
            if((ColorBitsGreen[pnt_address2] & pnt_mask) || (ColorBitsBlinkGreen[pnt_address2] & pnt_mask && pnt_blink > BLINK_SWITCH)) {
                COLOR_BIT_GREEN_2 = 1;
            }else{
                COLOR_BIT_GREEN_2 = 0;
            }
            if((ColorBitsRed[pnt_address2] & pnt_mask) || (ColorBitsBlinkRed[pnt_address2] & pnt_mask && pnt_blink > BLINK_SWITCH)) {
                COLOR_BIT_RED_2 = 1;
            }else{
                COLOR_BIT_RED_2 = 0;
            }
            SRCK2 = 1;
            
#endif


#ifdef ROWS_COUNT_3

            SRCK3 = 0;
            if((ColorBitsGreen[pnt_address3] & pnt_mask) || (ColorBitsBlinkGreen[pnt_address3] & pnt_mask && pnt_blink > BLINK_SWITCH)) {
                COLOR_BIT_GREEN_3 = 1;
            }else{
                COLOR_BIT_GREEN_3 = 0;
            }
            if((ColorBitsRed[pnt_address3] & pnt_mask) || (ColorBitsBlinkRed[pnt_address3] & pnt_mask && pnt_blink > BLINK_SWITCH)) {
                COLOR_BIT_RED_3 = 1;
            }else{
                COLOR_BIT_RED_3 = 0;
            }
            SRCK3 = 1;
#endif

            pnt_mask >>= 1;
        }
   }

   RCK = 0;
   RCK = 1;
}


void LED_WriteText(const uint8_t *message){

  int messageLen = strlen((const char *)message);

  uint16_t x8 = 0;
  uint16_t y8 = 0;
  uint16_t xpo = 0;
  uint8_t shft = 0;
  uint8_t mask = 0;

  for(write_char = 0 ; write_char < messageLen ; write_char++){

    if(message[write_char] == '\n'){
        cursor_Y += 8;
        cursor_X = 0;
        continue;
    }else if(message[write_char] == 0x0D){
        cursor_X ++;
        continue;
    }else if(message[write_char] == '\t'){
        x8 = cursor_X / 8;
        cursor_X = (x8 * 8) + 16;
        continue;
    }else if(message[write_char] == ' '){
        cursor_X += 4;
        continue;
    }

    /***********************************************
     Write letter
     ************************************************/

    //Find letter loop
    for(write_letter = 0 ; write_letter < LETTERS_COUNT; write_letter++){

      if(message[write_char] != LetterCodes[write_letter][0]){
        continue;
      }

      if(cursor_X + LetterCodes[write_letter][1] > DISPLAY_WIDTH){
        cursor_Y += 8;
        cursor_X = 0;
      }

      for(write_scan = 2 ; write_scan < LETTER_HEIGHT ; write_scan++){

        write_charWidth = LetterCodes[write_letter][1];
        x8 =  cursor_X / 8;
        y8 = (x8 / DISPLAY_WORDS) * 8;
        xpo = (cursor_Y * DISPLAY_WORDS) + (y8 * DISPLAY_WORDS) + (x8 + ((write_scan-2) * DISPLAY_WORDS));

        if(xpo >= DISPLAY_ROWS * DISPLAY_WIDTH){
          break;
        }

        shft = 128 >> (cursor_X-(x8*8));
        mask = 128;

        while(mask && write_charWidth){

          write_charWidth--;

          if(mask & LetterCodes[write_letter][write_scan]){

            if(write_currentColor & COLOR_GREEN){
              ColorBitsGreen[xpo] |= shft;
            }
            if(write_currentColor & COLOR_RED){
              ColorBitsRed[xpo] |= shft;
            }
            if(write_currentColor & COLOR_BLINK_GREEN){
              ColorBitsBlinkGreen[xpo] |= shft;
            }
            if(write_currentColor & COLOR_BLINK_RED){
              ColorBitsBlinkRed[xpo] |= shft;
            }
          }

          shft >>= 1;

          if(!shft){
            shft = 128;
            xpo++;
          }
          mask >>= 1;
        }
      }
      cursor_X += LetterCodes[write_letter][1];
    }
  }
}



void LED_InitScroller(){
    RCK = 0;

    SRCK = 0;
    COLOR_BIT_RED_1 = 0;
    COLOR_BIT_GREEN_1 = 0;

#ifdef ROWS_COUNT_3 || ROWS_COUNT_2
    SRCK2 = 0;
    COLOR_BIT_RED_2 = 0;
    COLOR_BIT_GREEN_2 = 0;
#endif
#ifdef ROWS_COUNT_3
    SRCK3 = 0;
    COLOR_BIT_RED_3 = 0;
    COLOR_BIT_GREEN_3 = 0;
#endif
}
