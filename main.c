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
#include <time.h>

/**
 * Like Arduino map()
 * @param targetNum
 * @param inMin
 * @param inMax
 * @param outMin
 * @param outMax
 * @return 
 */
int map(int targetNum, int inMin, int inMax, int outMin, int outMax)
{
    int inDiff = inMax - targetNum;
    int inRange = inMax - inMin;
    int outputRange = outMax - outMin;
    
    // Rounding
    // http://www.motorwarp.com/koizumi/round_c.html
    double percentage = (double)inDiff / (double)inRange;
    int outDiff = (int)((double)outputRange * percentage + 0.5);
 
    return outMax - outDiff;
}


/**
 * Variable Milliseconds Delay
 * @param milliseconds
 */
void delay_ms(unsigned int milliseconds)
{
    while(milliseconds > 0)
    {
        __delay_ms(1);
        milliseconds--;
    }
}

/**
 * Variable Microseconds Delay
 * @param microseconds
 */
void delay_us(unsigned int microseconds)
{
    while(microseconds > 0)
    {
        __delay_us(1);
        microseconds--;
    }
}


/*
                         Main application
 */
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
    
    // PWM
    int clickTime = 1;  // ms
    PWM3_LoadDutyValue(0);
    
    // Cds
    adc_result_t val;
    // 0 - 255
    int minLimit = 100;
    int maxLimit = 180;
    
    // Delay
    int delayMin = 20;
    int delayMax = 1000;
    unsigned int delay = 0;
    
    // test
    time_t toc;
    time(&toc);
    srand((int)toc);
    
    while (1)
    {
        // Add your application code
        // Get Cds Value / Set Delay
        val = ADC_GetConversion(CDS_IN);
        if (val < minLimit) val = (adc_result_t)minLimit;
        if (val > maxLimit) val = (adc_result_t)maxLimit;
        
        delay = (unsigned int)(delayMax + delayMin - map((int)val, minLimit, maxLimit, delayMin, delayMax));
        printf("%d, %d\r\n", val, delay);
        
        // PWM
        PWM3_LoadDutyValue(PWM3_INITIALIZE_DUTY_VALUE);
        delay_ms(clickTime);
        PWM3_LoadDutyValue(0);

        delay_ms(delay - clickTime);
    }
}

/**
 End of File
*/