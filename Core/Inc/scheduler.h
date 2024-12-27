/*
 * scheduler.h
 *
 *  Created on: Nov 25, 2024
 *      Author: HP
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#include "main.h"

#define MAX_TASKS 10
#define TICK 10 // ms
/*	ERROR CODE: 1xy
 * 1: error
 * x: class <1: scheduler>
 * y: method
*/
#define ADD_TASK_ERROR 110
#define NOT_VALID_TASK_ID 111

typedef struct TaskNode {
    void (*pTask)(void);
    struct TaskNode *next;
    uint32_t delay;
    uint32_t period;
    uint8_t runMe;
    uint32_t TaskID;
} TaskNode;

typedef struct {
    TaskNode *head;
    uint32_t nTasks;
} Tasks_t;

void Scheduler_Init(void);
void Scheduler_Update(void);
void Scheduler_Dispatch_Tasks(void);
uint32_t Scheduler_Add_Task(void (*pF)(void), uint32_t DELAY, const uint32_t PERIOD);
uint8_t Scheduler_Remove_Task(uint32_t TaskID);


#endif /* INC_SCHEDULER_H_ */
