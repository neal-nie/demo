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
    uint8 stateNum;
    StmeLibActionCallBack **actionMap;      // length: stateNum; length of actionMap[i] = stateNum;
    StmeLibTransitionCallBack *transitList; // length: stateNum
} StmeLibCallBackStru;

StmeLibCallBackStru *StmeLibNew(uint8 stateNum);

void StmeLibRegistTransition(uint8 stateValue, StmeLibTransitionCallBack jumpOutFunc, StmeLibCallBackStru *callBackInfo);

void StmeLibRegistAction(uint8 statePre, uint8 stateCur, StmeLibActionCallBack actionFunc, StmeLibCallBackStru *callBackInfo);

uint8 StmeLibProc(const void *condInfo, uint8 *statePre, StmeLibCallBackStru *callBackInfo);

#endif // !STME_LIB_H
