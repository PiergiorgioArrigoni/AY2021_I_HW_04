/**
 * \file InterruptRoutine.c
 * \brief Source file for Interrupt Service Routines
 * \author Piergiorgio Arrigoni
*/

#include "InterruptRoutines.h"

#define PHOTO_CHANNEL 0 //only info about one channel is needed as there are 2 channels
#define PHOTO_THRESH 0.9 //threshold under which led is disabled (set to 20%)

extern uint8_t flag_uart;
extern uint8_t flag_photo;

uint8_t char_rec;
uint8_t channel = 0;
uint8_t value_photo;
uint8_t value_potentio;

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
    channel = 1-channel;
    ADC_AMux_Select(channel);
    
    if(channel == PHOTO_CHANNEL)
    {   
        value_photo = ADC_Read32();
        if(value_photo > PHOTO_THRESH*65535) 
            flag_photo = 1;
        else
            flag_photo = 0;
    }
    else
    {
        value_potentio = ADC_Read32();
        PWM_WriteCompare(value_potentio*255/65535);
    }
}
/* [] END OF FILE */