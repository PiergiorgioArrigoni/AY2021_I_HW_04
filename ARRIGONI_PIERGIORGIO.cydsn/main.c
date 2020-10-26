/**
 * \file main.c
 * \brief Main source file for Homework 4
 * \author Piergiorgio Arrigoni
*/

#include "project.h"
#include "InterruptRoutines.h"

uint8_t flag_uart = 1;
uint8_t flag_photo = 0;

int main(void)
{
    //Initialize components
    ADC_Start();
    UART_Start();
    PWM_Start();
    
    //Enable interrupts
    CyGlobalIntEnable;
    ISR_RX_StartEx(UART_ISR);
    
    for(;;)
    {
        if(flag_uart)
        {
            ISR_ADC_StartEx(ADC_ISR);
            while(flag_uart){
                if(flag_photo)
                {
                }
            }
            ISR_ADC_Stop();
            flag_photo = 0;
        }
        
    }
}

/* [] END OF FILE */