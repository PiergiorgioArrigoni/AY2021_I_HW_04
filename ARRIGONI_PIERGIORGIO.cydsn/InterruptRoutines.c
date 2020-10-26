/**
 * \file InterruptRoutine.c
 * \brief Source file for Interrupt Service Routines
 * \author Piergiorgio Arrigoni
*/

#include "InterruptRoutines.h"

#define PHOTO_CHANNEL 0 //amux channel of the photodiode
#define POTENTIO_CHANNEL 1 //amux channel of the potentiometer

extern uint8 flag_uart; //flag signaling UART instructions for enabling or disabling the sampling
extern uint8 flag_packet; //flag signaling if packet is ready to be sent
extern uint8 Data[BUFFER_SIZE]; //array of the packet to be sent

uint8 char_rec; //character received from UART
int32 value_photo; //sampled value from the photoresistor
int32 value_potentio; //sampled value from the potentiometer

CY_ISR(UART_ISR)
{
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {   
        char_rec = UART_ReadRxData();
        if(char_rec == 'b' || char_rec == 'B') //begin
        {
            flag_uart = 1;
            LED_TX_Write(1); //internal LED turns on: system is sampling and data are continuously being sent 
        }
        else if(char_rec == 's' || char_rec == 'S') //stop
        {
            flag_uart = 0;
            LED_TX_Write(0); //internal LED turns off: system is not sampling anymore 
        }
    }
}

CY_ISR(ADC_ISR)
{
    Timer_ReadStatusRegister(); //bring interrupt line low
    
    AMux_Select(PHOTO_CHANNEL);
    value_photo = ADC_Read32();
    if(value_photo < 0) 
        value_photo = 0;
    else if(value_photo > 65535) 
        value_photo = 65535;
    
    Data[1] = value_photo >> 8;
    Data[2] = value_photo & 0xFF;

    AMux_Select(POTENTIO_CHANNEL); //potentiometer channel is sampled even if light is over the threshold
    value_potentio = ADC_Read32();
    if(value_potentio < 0) 
        value_potentio = 0;
    else if(value_potentio > 65535) 
        value_potentio = 65535;
    
    if(value_photo < PHOTO_THRESH*65535)  //if photoresistor value is under threshold we can modulate the LED
        PWM_WriteCompare(value_potentio*255/65535); //ADC is 16bit but PWM of the LED is 8bit  
    else
        PWM_WriteCompare(0);
        
    Data[3] = value_potentio >> 8;
    Data[4] = value_potentio & 0xFF;
    flag_packet = 1; //packet is ready to be sent
}
/* [] END OF FILE */