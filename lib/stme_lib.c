/*
 * Copyright (c) 2022-2022 Nie Guangze. All rights reserved.
 * Description: define state machine periodic. Notice: init task should do by user.
 * NOTICE! Invalid stateValue = stateNum!
 */

#include "stme_lib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// reset Call Back Function Pointers to Null
static void StmeLibReset(StmeLibCallBackStru *callBackInfo)
{
    StmeLibActionCallBack **actionPtr = callBackInfo->actionMap;
    for (size_t i = 0; i < callBackInfo->stateNum; i++)
    {
        memset(*actionPtr, 0, sizeof(StmeLibActionCallBack) * callBackInfo->stateNum);
    }
    memset(callBackInfo->transitList, 0, sizeof(StmeLibTransitionCallBack) * callBackInfo->stateNum);
}

// create New Stme instance. For dummpy state, stateValue = stateNum
StmeLibCallBackStru *StmeLibNew(uint8 stateNum)
{
    if (stateNum < 2)
    {
        printf("ERROR! Invalid stateNum [%d]\n", stateNum);
        return NULL;
    }
    StmeLibCallBackStru *instance = (StmeLibCallBackStru *)malloc(sizeof(StmeLibCallBackStru));
    if (instance == NULL)
    {
        printf("ERROR! Fail to apply memory!");
        return NULL;
    }
    instance->stateNum = stateNum;
    instance->transitList = (StmeLibTransitionCallBack *)malloc(sizeof(StmeLibTransitionCallBack) * stateNum);
    if (instance->transitList == NULL)
    {
        printf("ERROR! Fail to apply memory!");
        free(instance);
        return NULL;
    }
    instance->actionMap = (StmeLibActionCallBack **)malloc(sizeof(StmeLibActionCallBack *) * stateNum);
    if (instance->actionMap == NULL)
    {
        printf("ERROR! Fail to apply memory!");
        free(instance->transitList);
        free(instance);
        return NULL;
    }
    for (size_t i = 0; i < stateNum; i++)
    {
        StmeLibActionCallBack *ptr = (StmeLibActionCallBack *)malloc(sizeof(StmeLibActionCallBack) * stateNum);
        if (ptr == NULL)
        {
            printf("ERROR! Fail to apply memory!");
            for (size_t j = 0; j < i; j++)
            {
                free(*(instance->actionMap + j));
            }
            free(instance->transitList);
            free(instance);
            return NULL;
        }
        *(instance->actionMap + i) = ptr;
    }
    StmeLibReset(instance);
    return instance;
}

// add jumpOutFunc for state of stateValue in callBackInfo
void StmeLibRegistTransition(uint8 stateValue, StmeLibTransitionCallBack jumpOutFunc, StmeLibCallBackStru *callBackInfo)
{
    if (stateValue >= callBackInfo->stateNum)
    {
        printf("ERROR! Invalid stateValue [%d]\n", stateValue);
        return;
    }
    *(callBackInfo->transitList + stateValue) = jumpOutFunc;
}

// add action between states in callBackInfo
void StmeLibRegistAction(uint8 statePre, uint8 stateCur, StmeLibActionCallBack actionFunc, StmeLibCallBackStru *callBackInfo)
{
    if (statePre >= callBackInfo->stateNum)
    {
        printf("ERROR! Invalid statePre [%d]\n", statePre);
        return;
    }
    if (stateCur >= callBackInfo->stateNum)
    {
        printf("ERROR! Invalid stateCur [%d]\n", stateCur);
        return;
    }
    *(*(callBackInfo->actionMap + statePre) + stateCur) = actionFunc;
}

// calc current state of state machine
uint8 StmeLibProc(const void *condInfo, uint8 *statePre, StmeLibCallBackStru *callBackInfo)
{
    uint8 stateCur = *statePre;
    for (size_t i = 0; i < callBackInfo->stateNum; i++)
    {
        // Do State Transition
        uint8 stateRet = (*(callBackInfo->transitList + i))(condInfo);
        if (stateRet != callBackInfo->stateNum)
        {
            stateCur = stateRet;
            break;
        }
    }
    // Do Action between States
    StmeLibActionCallBack actionFunc = *(*(callBackInfo->actionMap + *statePre) + stateCur);
    if (actionFunc)
    {
        actionFunc();
    }
    // update state memory
    *statePre = stateCur;

    return stateCur;
}
