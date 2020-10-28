/**
 * \file InterruptRoutine.c
 * \brief Source file for Interrupt Service Routines
 * \author Piergiorgio Arrigoni
*/

#include "InterruptRoutines.h"

#define PHOTO_CHANNEL 0 //amux channel of the photoresistor
#define POTENTIO_CHANNEL 1 //amux channel of the potentiometer

uint8 char_rec; //character received from UART
int32 value_photo; //sampled value from the photoresistor
int32 value_potentio; //sampled value from the potentiometer

CY_ISR(UART_ISR)
{
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {   
        char_rec = UART_ReadRxData();
        if(char_rec == 'b' || char_rec == 'B') //begin
            flag_uart = 1;
        else if(char_rec == 's' || char_rec == 'S') //stop
            flag_uart = 0;
    }
}

CY_ISR(ADC_ISR)
{
    Timer_ReadStatusRegister(); //brings interrupt line low
    
    AMux_FastSelect(PHOTO_CHANNEL);
    value_photo = ADC_Read32();
    if(value_photo < 0) 
        value_photo = 0;
    else if(value_photo > 65535) 
        value_photo = 65535;
    
    Data[1] = value_photo >> 8;
    Data[2] = value_photo & 0xFF;

    AMux_FastSelect(POTENTIO_CHANNEL); //potentiometer channel is sampled even if light is over the threshold
    value_potentio = ADC_Read32();
    if(value_potentio < 0) 
        value_potentio = 0;
    else if(value_potentio > 65535) 
        value_potentio = 65535;
    
    if(value_photo < PHOTO_THRESH*65535)  //if photoresistor value is under the threshold external LED can be modulated
        PWM_WriteCompare(value_potentio*255/65535); //ADC is 16bit but PWM of the LED is 8bit  
    else 
        PWM_WriteCompare(0); //if photoresistor value is over the threshold, external LED is turned off
        
    Data[3] = value_potentio >> 8;
    Data[4] = value_potentio & 0xFF;
    flag_packet = 1; //packet is ready to be sent
}
/* [] END OF FILE */