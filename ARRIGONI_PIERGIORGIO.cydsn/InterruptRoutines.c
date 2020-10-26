/**
 * \file InterruptRoutine.c
 * \brief Source file for Interrupt Service Routine
 * \author Piergiorgio Arrigoni
*/

#include "InterruptRoutines.h"

extern uint8_t flag_uart;

CY_ISR(UART_ISR)
{
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
        flag_uart = 1;
}

CY_ISR(ADC_ISR)
{
    
}
/* [] END OF FILE */