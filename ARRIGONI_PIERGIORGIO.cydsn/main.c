/**
 * \file main.c
 * \brief Main source file for Homework 4
 * \author Piergiorgio Arrigoni
*/

#include "project.h"
#include "InterruptRoutines.h"

uint8 flag_uart = 0; //system starts with sampling disabled
uint8 flag_photo;
uint8 flag_packet = 0; //at the beginning packet is not ready
uint8 Data[BUFFER_SIZE];

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
    
    Data[0] = 0xA0; //header byte
    Data[5] = 0xC0; //tail byte
    
    for(;;)
    {
        if(flag_uart)
        {
            ISR_ADC_StartEx(ADC_ISR); //ADC samples only if correct UART character is received
            while(flag_uart){
                if(flag_packet)
                {
                    UART_PutArray(Data, 6); //sending the packet to the bridge control
                    flag_packet = 0;
                }
            }
            ISR_ADC_Stop(); //ADC stop sampling
            flag_photo = 0; //this variable is set low in the main too, because ADC sampling might resume from potentiometer channel
            PWM_WriteCompare(0);
        } 
    }
}

/* [] END OF FILE */