/*
 * Copyright (c) 2022-2022 Nie Guangze. All rights reserved.
 * Description: define state machine periodic. Notice: init task should do by user.
 * NOTICE! Invalid stateValue = stateNum!
 */

#include "stme_lib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// convert table(row first) index into array index
static size_t StmeLibConvertIndexTable2Array(size_t idxRow, size_t idxCol, size_t sizeCol)
{
    /*
     * Table Index to Array Index (idxRow, idxCol, idxArr)
     * (0, 0, 0) | (0, 1, 1) | (0, 2, 2) | (0, 3, 3) | (0, 4, 4)
     * (1, 0, 5) | (1, 1, 6) | (1, 2, 7) | (1, 3, 8) | (1, 4, 9)
     * (2, 0, 10)| (2, 1, 11)| (2, 2, 12)| (2, 3, 13)| (2, 4, 14)
     * ...(idxRow, idxCol, idxRow*sizeCol + idxCol)
     */
    if (idxRow > UINT8_MAX)
    {
        printf("ERROR! idxRow [%d] out of range [0, 255].\n", idxRow);
        return 0;
    }
    if (idxCol > UINT8_MAX)
    {
        printf("ERROR! idxCol [%d] out of range [0, 255].\n", idxCol);
        return 0;
    }
    if (sizeCol > UINT8_MAX)
    {
        printf("ERROR! sizeCol [%d] out of range [0, 255].\n", sizeCol);
        return 0;
    }

    return idxRow * sizeCol + idxCol;
}

// reset Call Back Function Pointers to Null
static void StmeLibResetCallBack(StmeLibCallBackStru *callBackInfo)
{
    memset(callBackInfo->actionMap, 0, sizeof(StmeLibActionCallBack) * callBackInfo->stateNum * callBackInfo->stateNum);
    memset(callBackInfo->transitionList, 0, sizeof(StmeLibTransitionCallBack) * callBackInfo->stateNum);
}

// create New Stme handle. For dummpy state, stateValue = stateNum
StmeLibCallBackStru *StmeLibNew(uint8 stateNum)
{
    if (stateNum < 2)
    {
        printf("ERROR! stateNum [%d] out of range [3, 255]\n", stateNum);
        return NULL;
    }
    StmeLibCallBackStru *handle = (StmeLibCallBackStru *)malloc(sizeof(StmeLibCallBackStru));
    if (handle == NULL)
    {
        printf("ERROR! Fail to apply memory for CallBack!");
        return NULL;
    }
    handle->stateNum = stateNum;
    handle->transitionList = (StmeLibTransitionCallBack *)malloc(sizeof(StmeLibTransitionCallBack) * stateNum);
    if (handle->transitionList == NULL)
    {
        printf("ERROR! Fail to apply memory for transitionList!");
        free(handle);
        return NULL;
    }
    handle->actionMap = (StmeLibActionCallBack *)malloc(sizeof(StmeLibActionCallBack) * stateNum * stateNum);
    if (handle->actionMap == NULL)
    {
        printf("ERROR! Fail to apply memory for actionMap!");
        free(handle->transitionList);
        free(handle);
        return NULL;
    }
    StmeLibResetCallBack(handle);
    return handle;
}

// add jumpOutFunc for state of stateValue in callBackInfo
void StmeLibRegisterTransition(uint8 stateValue, StmeLibTransitionCallBack jumpOutFunc, StmeLibCallBackStru *callBackInfo)
{
    if (stateValue >= callBackInfo->stateNum)
    {
        printf("ERROR! stateValue [%d] out of range [0\n", stateValue);
        return;
    }
    *(callBackInfo->transitionList + stateValue) = jumpOutFunc;
}

// add action between states in callBackInfo
void StmeLibRegisterAction(uint8 statePre, uint8 stateCur, StmeLibActionCallBack actionFunc, StmeLibCallBackStru *callBackInfo)
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
    size_t index = StmeLibConvertIndexTable2Array(statePre, stateCur, callBackInfo->stateNum);
    *(callBackInfo->actionMap + index) = actionFunc;
}

// calc current state of state machine
uint8 StmeLibRun(const void *condInfo, uint8 *statePre, StmeLibCallBackStru *callBackInfo)
{
    if (*statePre >= callBackInfo->stateNum) {
        printf("ERROR! statePre out of range [0, %d)", callBackInfo->stateNum);
        return callBackInfo->stateNum;
    }
    uint8 stateCur;
    // Do State Transition
    StmeLibTransitionCallBack transitionFunc = *(callBackInfo->transitionList + *statePre);
    if (transitionFunc)
    {
        stateCur = transitionFunc(condInfo);
    }
    else
    {
        // for Not transition state, return dummy state value.
        return callBackInfo->stateNum;
    }
    if (stateCur >= callBackInfo->stateNum) {
        printf("ERROR! stateCur out of range [0, %d)", callBackInfo->stateNum);
        return callBackInfo->stateNum;
    }
    // Do Action between States.
    size_t index = StmeLibConvertIndexTable2Array(*statePre, stateCur, callBackInfo->stateNum);
    StmeLibActionCallBack actionFunc = *(callBackInfo->actionMap + index);
    if (actionFunc)
    {
        actionFunc();
    }
    // update state memory
    *statePre = stateCur;

    return stateCur;
}
