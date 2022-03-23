/*
 * Copyright (c) 2022-2022 Nie Guangze. All rights reserved.
 * Description: reuse state machine entry
 */

#ifndef STME_LIB_H
#define STME_LIB_H

#include "types.h"

typedef void (*StmeLibActionCallBack)(void);
typedef uint8 (*StmeLibTransitionCallBack)(const void *); // arg: condInfo

typedef struct
{
    // Number of states in state machine.
    // Valid State value in [0, stateNum - 1].
    // Dummy state value is stateNum.
    uint8 stateNum;
    // 2D Table in array, row first. Length: stateNum^2.
    // Row index is statePre. Col index is value of stateCur.
    StmeLibActionCallBack *actionMap;
    // Length: stateNum.
    // Index value of stateCur.
    StmeLibTransitionCallBack *transitionList;
} StmeLibCallBackStru;

// Create CallBack handle for new instance of state machine.
StmeLibCallBackStru *StmeLibNew(uint8 stateNum);

// Add jumpOutFunc into CallBack handle.
// jumpOutFunc return next state value. If preState is not feasible, return dummy state value.
// arg of jumpOutFunc is trainsition condition info of stata machine.
void StmeLibRegisterTransition(uint8 stateValue, StmeLibTransitionCallBack jumpOutFunc, StmeLibCallBackStru *callBackInfo);

// Add actionFunc into CallBack handle.
// actionFunc define behaviour from previous state to current state.
void StmeLibRegisterAction(uint8 statePre, uint8 stateCur, StmeLibActionCallBack actionFunc, StmeLibCallBackStru *callBackInfo);

// Run State machine to generate current state and update previous state memory.
uint8 StmeLibRun(const void *condInfo, uint8 *statePre, StmeLibCallBackStru *callBackInfo);

#endif // !STME_LIB_H
