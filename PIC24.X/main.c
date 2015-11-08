/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC24FJ64GA006
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.24
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#include "SystemConfiguration.h"
#include "LEDScroller.h"

/*
Main application
 */

#define CMD_CLEAR                   1
#define CMD_SET_COLOR_RED           2
#define CMD_SET_COLOR_GREEN         3
#define CMD_SET_COLOR_ORANGE        4
#define CMD_SET_COLOR_BLINK_RED     5
#define CMD_SET_COLOR_BLINK_GREEN   6
#define CMD_SET_COLOR_BLINK_ORANGE  7
#define CMD_ALIGN_LEFT              8
#define CMD_ALIGN_CENTER            11
#define CMD_ALIGN_RIGHT             12

int main(void) {
    // initialize the device
    SYSTEM_Initialize();

    uint8_t read = 0;
    uint8_t* buf[1];

    LED_InitScroller();

    LED_Clear();

    while (1) {
        LED_Paint();

        while((UART1_TransferStatusGet() & UART1_TRANSFER_STATUS_RX_DATA_PRESENT) == UART1_TRANSFER_STATUS_RX_DATA_PRESENT){
            read = UART1_Read();

            if(read == CMD_CLEAR){
                LED_Clear();

            }else if(read == CMD_SET_COLOR_GREEN){
                LED_SetColor(COLOR_GREEN);
            }else if(read == CMD_SET_COLOR_RED){
                LED_SetColor(COLOR_RED);
            }else if(read == CMD_SET_COLOR_ORANGE){
                LED_SetColor(COLOR_ORANGE);
            }else if(read == CMD_SET_COLOR_BLINK_GREEN){
                LED_SetColor(COLOR_BLINK_GREEN);
            }else if(read == CMD_SET_COLOR_BLINK_RED){
                LED_SetColor(COLOR_BLINK_RED);
            }else if(read == CMD_SET_COLOR_BLINK_ORANGE){
                LED_SetColor(COLOR_BLINK_ORANGE);
            }else{
                buf[0] = read;
                LED_WriteText((const uint8_t*)buf);
            }
        }
    }

    return -1;
}
/**
 End of File
 */