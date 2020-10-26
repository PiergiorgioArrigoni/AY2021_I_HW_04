/**
 * \file InterruptRoutine.h
 * \brief Header file for Interrupt Service Routines
 * \author Piergiorgio Arrigoni
*/

#ifndef __INTERRUPT_ROUTINES_H__
    #define __INTERRUPT_ROUTINES_H__
    
    #include "project.h"
    
    #define SIGNALS_TO_SEND 2 //sampled signals to be sent to the bridge control panel
    #define BUFFER_SIZE 1 + 2*SIGNALS_TO_SEND + 3 //header byte + 2 bytes for each sampled signals + 2 bytes for light threshold value + tail byte
    #define PHOTO_THRESH 0.25 //threshold under which led is disabled (set to 25% of total range, keeping in mind that the internal LED emanates light)
    
    CY_ISR_PROTO(UART_ISR); //ISR triggered when one byte is received by the UART
    CY_ISR_PROTO(ADC_ISR); //ISR triggered when timer reaches terminal count (needed for timing of ADC sampling)
#endif

/* [] END OF FILE */