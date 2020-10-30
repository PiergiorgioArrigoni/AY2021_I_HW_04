/**
 * \file main.c
 * \brief Main source file for Homework 4
 * \author Piergiorgio Arrigoni
*/

#include "InterruptRoutines.h"

int main(void)
{
    //Initialize components
    ADC_Start();
    UART_Start();
    PWM_Start();
    Timer_Start();
    
    //Enable UART interrupt
    CyGlobalIntEnable;
    ISR_RX_StartEx(UART_ISR);
    
    flag_uart = 0; //system starts with sampling disabled
    flag_packet = 0;
    
    Data[0] = 0xA0; //header byte
    Data[BUFFER_SIZE-1] = 0xC0; //tail byte
    
    uint16 threshold = PHOTO_THRESH*65535; //light threshold value to be sent to bridge control to be displayed
    Data[5] = threshold >> 8;
    Data[6] = threshold & 0xFF;
   
    for(;;)
    {
        if(flag_uart)
        {
            LED_INT_Write(1); //internal LED turns on: system is sampling and data are continuously being sent
            ISR_ADC_StartEx(ADC_ISR); //ADC starts sampling when UART "begin" command is received
             
            while(flag_uart){
                if(flag_packet)
                {
                    UART_PutArray(Data, BUFFER_SIZE); //sending the packet to the bridge control
                    flag_packet = 0;
                }
            }
            
            ISR_ADC_Stop(); //ADC stops sampling when UART "stop" command is received
            LED_INT_Write(0); //internal LED turns off: system is not sampling anymore
            PWM_WriteCompare(0); //UART "stop" command also shuts off external LED
        } 
    }
}

/* [] END OF FILE */