/*
 * scheduler.h
 *
 *  Created on: Nov 28, 2022
 *      Author: program
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "msp.h"

void scheduler_open(void);
void add_scheduled_event(uint32_t event);
void remove_scheduled_event(uint32_t event);
uint32_t get_scheduled_events(void);

#endif /* SCHEDULER_H_ */
