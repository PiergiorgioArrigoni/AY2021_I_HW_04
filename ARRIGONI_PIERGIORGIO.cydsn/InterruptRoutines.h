/**
 * \file InterruptRoutine.h
 * \brief Header file for Interrupt Service Routines
 * \author Piergiorgio Arrigoni
*/

#ifndef __INTERRUPT_ROUTINES_H__
    #define __INTERRUPT_ROUTINES_H__
    
    #include "project.h"
    
    #define VALUES_TO_SEND 2
    #define BUFFER_SIZE 1+2*VALUES_TO_SEND+1
    
    CY_ISR_PROTO(UART_ISR);
    CY_ISR_PROTO(ADC_ISR);
#endif

/* [] END OF FILE */