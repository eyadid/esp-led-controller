/**
  @Generated MPLAB® Code Configurator Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using MPLAB® Code Configurator

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC24FJ64GA006
        Driver Version    :  1.02
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

// Configuration bits: selected in the GUI

// CONFIG2
#pragma config IESO = ON    // Internal External Switch Over Mode->IESO mode (Two-Speed Start-up) enabled
#pragma config FNOSC = PRI    // Oscillator Select->Primary Oscillator (XT, HS, EC)
#pragma config POSCMOD = HS    // Primary Oscillator Select->HS Oscillator mode selected
#pragma config OSCIOFNC = OFF    // Primary Oscillator Output Function->OSC2/CLKO/RC15 functions as CLKO (FOSC/2)
#pragma config FCKSM = CSDCMD    // Clock Switching and Monitor->Clock switching and Fail-Safe Clock Monitor are disabled

// CONFIG1
#pragma config WDTPS = PS32768    // Watchdog Timer Postscaler->1:32,768
#pragma config COE = OFF    // Set Clip On Emulation Mode->Reset Into Operational Mode
#pragma config ICS = PGx1    // Comm Channel Select->Emulator/debugger uses EMUC1/EMUD1
#pragma config FWPSA = PR128    // WDT Prescaler->Prescaler ratio of 1:128
#pragma config WINDIS = OFF    // Watchdog Timer Window->Windowed Watchdog Timer enabled; FWDTEN must be 1
#pragma config GWRP = OFF    // General Code Segment Write Protect->Writes to program memory are allowed
#pragma config GCP = OFF    // General Code Segment Code Protect->Code protection is disabled
#pragma config FWDTEN = OFF    // Watchdog Timer Enable->Watchdog Timer is disabled
#pragma config BKBUG = OFF    // Background Debug->Device resets into Operational mode
#pragma config JTAGEN = OFF    // JTAG Port Enable->JTAG port is disabled

#include "mcc.h"

void SYSTEM_Initialize(void)
{
    OSCILLATOR_Initialize();
    PIN_MANAGER_Initialize();
    INTERRUPT_Initialize();
    UART1_Initialize();
    UART2_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // DOZEN disabled; DOZE 1:8; RCDIV FRC/2; ROI disabled; 
    CLKDIV = 0x3100;
    // Set the secondary oscillator
    
}

/**
 End of File
*/