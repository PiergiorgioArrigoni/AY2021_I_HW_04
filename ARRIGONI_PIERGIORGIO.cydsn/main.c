/**
 * \file main.c
 * \brief Main source file for Homework 4
 * \author Piergiorgio Arrigoni
*/

#include "project.h"
#include "InterruptRoutines.h"

int main(void)
{
    //Initialize components
    ADC_Start();
    UART_Start();
    PWM_Start();
    
    //Enable interrupts
    CyGlobalIntEnable;
    ISR_ADC_StartEx(ADC_ISR);
    ISR_RX_StartEx(UART_ISR);
    
    for(;;)
    {
    }
}

/* [] END OF FILE */