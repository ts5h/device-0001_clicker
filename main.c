/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F1705
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <stdio.h>

/*
                         Main application
 */

// Like Arduino map()
int map(int target_num, int in_min, int in_max, int out_min, int out_max)
{
    int input_diff = in_max - target_num;
    int input_range = in_max - in_min;
    int output_range = out_max - out_min;
    
    // Rounding
    // http://www.motorwarp.com/koizumi/round_c.html
    double percentage = (double)input_diff / (double)input_range;
    int out_diff = (int)((double)output_range * percentage + 0.5);
 
    return out_max - out_diff;
}

void main(void)
{
    TXSTAbits.TXEN = 1;
    RCSTAbits.SPEN = 1;
    
    // initialize the device
    SYSTEM_Initialize();

    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    adc_result_t val;
    unsigned int minLimit = 90;
    unsigned int maxLimit = 150;
    
    unsigned int delayMin = 50;
    unsigned int delayMax = 1000;
    unsigned int delay;

    while (1)
    {
        // Add your application code
        val = ADC_GetConversion(CDS_IN);
        if (val < minLimit) val = minLimit;
        if (val > maxLimit) val = maxLimit;
        
        delay = delayMax + delayMin - map(val, minLimit, maxLimit, delayMin, delayMax);
        printf("%d, %d\r\n", val, delay);
        
        __delay_ms(50);
    }
}
/**
 End of File
*/