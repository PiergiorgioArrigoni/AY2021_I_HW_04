/**
 * \file InterruptRoutine.h
 * \brief Header file for Interrupt Service Routine
 * \author Piergiorgio Arrigoni
*/

#ifndef __INTERRUPT_ROUTINES_H__
    #define __INTERRUPT_ROUTINES_H__
    
    #include "project.h"
    
    CY_ISR_PROTO(UART_ISR);
    CY_ISR_PROTO(ADC_ISR);
#endif

/* [] END OF FILE */