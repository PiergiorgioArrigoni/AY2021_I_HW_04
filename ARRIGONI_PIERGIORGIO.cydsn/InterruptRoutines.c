/**
 * \file InterruptRoutine.c
 * \brief Source file for Interrupt Service Routines
 * \author Piergiorgio Arrigoni
*/

#include "InterruptRoutines.h"

extern uint8_t flag_uart;
uint8_t rec;

CY_ISR(UART_ISR)
{
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {   
        rec = UART_ReadRxData();
        if(rec == 'b' || rec == 'B')
            flag_uart = 1;
        else if(rec == 's' || rec == 'S')
            flag_uart = 0;
    }
}

CY_ISR(ADC_ISR)
{

}
/* [] END OF FILE */