/*
 * scheduler.c
 *
 *  Created on: Nov 28, 2022
 *      Author: program
 */

#include "scheduler.h"

static uint32_t event_scheduled;

void scheduler_open(void)
{
    uint32_t temp;
    temp = NVIC->ISER[0];
    __disable_irq();
    event_scheduled = 0;
    NVIC->ISER[0] = temp;
    __enable_irq();

}

void add_scheduled_event(uint32_t event)
{
    uint32_t temp;
    temp = NVIC->ISER[0];
    __disable_irq();
    event_scheduled |= event;
    NVIC->ISER[0] = temp;
    __enable_irq();

}

void remove_scheduled_event(uint32_t event)
{
    uint32_t temp;
    temp = NVIC->ISER[0];
    __disable_irq();
    event_scheduled &= ~event;
    NVIC->ISER[0] = temp;
    __enable_irq();

}

uint32_t get_scheduled_events(void)
{
    return event_scheduled;
}
