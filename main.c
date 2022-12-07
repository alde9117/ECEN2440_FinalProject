#include "msp.h"
#include "scheduler.h"
#include <stdio.h>

#include <stdlib.h>
/**
 * main.c
 */

#define LIGHT_SENSOR_CB 0x10 //arbitrary value that won't match another CB

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    P4 -> OUT = 0x00;

    volatile uint32_t i;

    //Initialize pins (1 input and 1 output that will be high or low)

    //Put the following in pwm.c
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //For the input (P4.0):
    P4-> SEL0 &= ~BIT0;//set to zero
    P4-> SEL1 &= ~BIT0;//set to zero

    P4 -> DIR &= ~BIT0;//set as an input, set to 0 using &= ~ syntax
    //P4 -> REN |= BIT0;//set as an REN, set to 1 using &= ~ syntax  //check if this should be zero if we don't need a pulldown resistor
    //P4 -> OUT |= BIT0;//set as an out, set to 1 using &= ~ syntax  //check if this should be deleted if we don't need a pull down resistor

    P4 -> IFG &= ~BIT1;
    P4 ->IES &= ~BIT0;
    P4 ->IE |=BIT0;

    //For the output (P6.1):
    P6 -> DIR |= BIT1;
    P6 -> DS |= BIT1;
    //test led
    P1 -> DIR |= BIT0;
    P1 -> DS |= BIT0;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    scheduler_open();

    //__NVIC_EnableIRQ(...) treat like a button. So we will need to do (PORT4_IRQn) and have a void PORT4_IRQHandler(void)
    __NVIC_EnableIRQ(PORT4_IRQn);


    __enable_irq();

    while(1)
    {
        //if an event was scheduled (use get scheduled) then turn on the LED, else turn it off
        if(get_scheduled_events()==LIGHT_SENSOR_CB)
        {
            //turn on LED
            __disable_irq();
            P6 ->OUT |= BIT1;
            P1 ->OUT |= BIT0;
            for (i = 10000; i > 0; i --);
            remove_scheduled_event(LIGHT_SENSOR_CB);

            __enable_irq();

        }
        else
        {
            //turn off LED
            __disable_irq();
            P6 -> OUT &= ~BIT1;
            P1 ->OUT &= ~BIT0;
            for (i = 10000; i > 0; i --);
            remove_scheduled_event(LIGHT_SENSOR_CB);

            __enable_irq();

        }
    }
}
    void PORT4_IRQHandler(void)
    {
        volatile uint32_t i;
        for (i = 100; i > 0; i --);
        //if P4.0 is high, send an event to be scheduled
        if(((P4->IFG & BIT0) == BIT0) )
        {
            P4 -> IFG &= ~BIT0;
            add_scheduled_event(LIGHT_SENSOR_CB);


            for (i = 100; i > 0; i --);
        }
        //if P4.0 is low, send a remove event
        else
        {
            //ifphoto1 == 0){
                P4 -> IFG &= ~BIT0;
                remove_scheduled_event(LIGHT_SENSOR_CB);


               for (i = 100; i > 0; i --);
            //}

        }

    }
