/**
 * \file InterruptRoutine.h
 * \brief Header file for Interrupt Service Routines
 * \author Piergiorgio Arrigoni
*/

#ifndef __INTERRUPT_ROUTINES_H__
    #define __INTERRUPT_ROUTINES_H__
    
    #include "project.h"
    
    #define VALUES_TO_SEND 2 //sampled measures to be sent to the bridge control panel
    #define BUFFER_SIZE 1+2*VALUES_TO_SEND+1 //sampled measures are 16bits long, so number is multiplied by 2 
    
    CY_ISR_PROTO(UART_ISR); //ISR triggered when one byte is received
    CY_ISR_PROTO(ADC_ISR); //ISR triggered when timer reaches terminal count (needed for timing of ADC sampling)
#endif

/* [] END OF FILE */