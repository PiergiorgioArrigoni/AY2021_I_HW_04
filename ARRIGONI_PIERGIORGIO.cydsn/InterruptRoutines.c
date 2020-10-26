/**
 * \file InterruptRoutine.c
 * \brief Source file for Interrupt Service Routines
 * \author Piergiorgio Arrigoni
*/

#include "InterruptRoutines.h"

#define PHOTO_CHANNEL 0 //only info about one channel of the mux is needed as there are only 2 channels
#define PHOTO_THRESH 0.25 //threshold under which led is disabled (set to 25%)

extern uint8 flag_uart; //flag signaling UART instructions for enabling the sampling,
extern uint8 flag_photo; //flag signaling if light is under the threshold
extern uint8 flag_packet; //flag signaling if packet is ready to be sent
extern uint8 Data[BUFFER_SIZE]; //array of the packet to be sent

uint8 char_rec; //character received from UART
uint8 channel = 1-PHOTO_CHANNEL; //in this way we start from the photoresistor channel
int32 value_photo; //sampled value from the photoresistor
int32 value_potentio; //sampled value from the potentiometer

CY_ISR(UART_ISR)
{
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {   
        char_rec = UART_ReadRxData();
        if(char_rec == 'b' || char_rec == 'B')
            flag_uart = 1;
        else if(char_rec == 's' || char_rec == 'S')
            flag_uart = 0;
    }
}

CY_ISR(ADC_ISR)
{
    Timer_ReadStatusRegister(); //bring interrupt line low
    
    channel = 1-channel; //communation of the channel (works for 2 channels only)
    AMux_Select(channel);
    
    if(channel == PHOTO_CHANNEL)
    {   
        value_photo = ADC_Read32();
        if(value_photo < 0) 
            value_photo = 0;
        else if(value_photo > 65535) 
            value_photo = 65535;
        
        Data[1] = value_photo >> 8;
        Data[2] = value_photo & 0xFF;
        
        if(value_photo < PHOTO_THRESH*65535) 
            flag_photo = 1;
        else
        {
            flag_photo = 0;
            PWM_WriteCompare(0); 
        }
    }
    else
    {
        value_potentio = ADC_Read32();
        if(value_potentio < 0) 
            value_potentio = 0;
        else if(value_potentio > 65535) 
            value_potentio = 65535;
        
        Data[3] = value_potentio >> 8;
        Data[4] = value_potentio & 0xFF;
        flag_packet = 1; //packet is ready to be sent
        
        if(flag_photo) //if photoresistor value is under threshold we can modulate the LED
            PWM_WriteCompare(value_potentio*255/65535); //ADC is 16bit but PWM of the LED is 8bit        
    }
}
/* [] END OF FILE */