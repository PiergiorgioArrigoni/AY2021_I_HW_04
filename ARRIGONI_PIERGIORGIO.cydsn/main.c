/**
 * \file main.c
 * \brief Main source file for Homework 4
 * \author Piergiorgio Arrigoni
*/

#include "project.h"
#include "InterruptRoutines.h"

uint8 flag_uart = 1;
uint8 flag_photo;
uint8 flag_packet = 0;
uint8 Data[BUFFER_SIZE];

int main(void)
{
    //Initialize components
    ADC_Start();
    UART_Start();
    PWM_Start();
    Timer_Start();
    
    //Enable interrupts
    CyGlobalIntEnable;
    ISR_RX_StartEx(UART_ISR);
    
    Data[0] = 0xA0;
    Data[5] = 0xC0;
    
    for(;;)
    {
        if(flag_uart)
        {
            ISR_ADC_StartEx(ADC_ISR);
            while(flag_uart){
                if(flag_packet)
                {
                    UART_PutArray(Data, 6);
                    flag_packet = 0;
                }
            }
            ISR_ADC_Stop();
            flag_photo = 0;
            PWM_WriteCompare(0);
        } 
    }
}

/* [] END OF FILE */