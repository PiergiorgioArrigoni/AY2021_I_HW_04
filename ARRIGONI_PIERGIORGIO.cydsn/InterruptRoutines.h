/**
 * \file InterruptRoutine.h
 * \brief Header file for Interrupt Service Routines
 * \author Piergiorgio Arrigoni
*/

#ifndef __INTERRUPT_ROUTINES_H__
    #define __INTERRUPT_ROUTINES_H__
    
    #include "project.h"
    
    #define VALUES_TO_SEND 3 //potentiometer sampling, photoresistor sempling and light threshold (constant)
    #define BUFFER_SIZE 1 + 2*VALUES_TO_SEND + 1
    #define PHOTO_THRESH 0.25 //threshold under which led is disabled (set to 25% of total range, keeping in mind that the internal LED emanates dim light)
    
    volatile uint8 flag_uart; //flag signaling UART instructions for enabling or disabling the sampling
    volatile uint8 flag_packet; //flag signaling if packet is ready to be sent
    uint8 Data[BUFFER_SIZE]; //array of the packet to be sent
    
    CY_ISR_PROTO(UART_ISR); //ISR triggered when one byte is received by the UART
    CY_ISR_PROTO(ADC_ISR); //ISR triggered when timer reaches terminal count (needed for timing of ADC sampling)
#endif

/* [] END OF FILE */