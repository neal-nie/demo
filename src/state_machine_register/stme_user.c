/*
 * Copyright (c) 2022-2022 Nie Guangze. All rights reserved.
 * Description: example of state machine application.
 *      states: OFF, ON, FAULT
 */

#include <string.h>
#include <stdio.h>
#include "types.h"
#include "stme_lib.h"

#define STATIC_MEMORY 1

#define STATE_OFF 0
#define STATE_ON 1
#define STATE_FAULT 2
#define STATE_NUM 3 // dummy state value as stateNum.

typedef struct
{
    bool flgSwitchOn;
    bool flgSwitchOff;
    bool flgFault;
    bool flgHeal;
} StmeUserCondStru;

typedef struct
{
    uint8 state;
    uint16 onCounter;
#if STATIC_MEMORY
    StmeLibTransitionCallBack transitionFuncArr[STATE_NUM];
    StmeLibActionCallBack actionFuncArr[STATE_NUM * STATE_NUM];
#endif
} StmeUserHistoryStru;

StmeUserHistoryStru g_stmeUserHistoryInfo;
const uint16 OnCounterMin = 500;
size_t currentTime;

uint8 StmeUserJumpOutOff(const void *condInfo)
{
    const StmeUserCondStru *userCondInfo = (const StmeUserCondStru *)condInfo;

    if (userCondInfo->flgSwitchOn)
    {
        return STATE_ON;
    }
    else
    {
        // keep in OFF
        return STATE_OFF;
    }
}

uint8 StmeUserJumpOutOn(const void *condInfo)
{
    const StmeUserCondStru *userCondInfo = (const StmeUserCondStru *)condInfo;

    if (userCondInfo->flgSwitchOff && g_stmeUserHistoryInfo.onCounter > OnCounterMin)
    {
        // ON to OFF, on at least last time of OnCounterMin
        return STATE_OFF;
    }
    else if (userCondInfo->flgFault)
    {
        return STATE_FAULT;
    }
    else
    {
        // keep in OFF
        return STATE_ON;
    }
}

uint8 StmeUserJumpOutFault(const void *condInfo)
{
    const StmeUserCondStru *userCondInfo = (const StmeUserCondStru *)condInfo;

    if (userCondInfo->flgSwitchOff)
    {
        return STATE_OFF;
    }
    else if (userCondInfo->flgHeal)
    {
        return STATE_ON;
    }
    else
    {
        // keep in FAULT
        return STATE_FAULT;
    }
}

void StmeUserEnterOn(void)
{
    g_stmeUserHistoryInfo.onCounter = 0;
}

void StmeUserDuringOn(void)
{
    g_stmeUserHistoryInfo.onCounter++;
}

void StmeUserInit(StmeLibCallBackStru *stmeCallBackHandle)
{
    memset(&g_stmeUserHistoryInfo, 0, sizeof(StmeUserHistoryStru));
    g_stmeUserHistoryInfo.state = STATE_OFF;
    g_stmeUserHistoryInfo.onCounter = 0;
    StmeLibRegisterTransition(STATE_ON, StmeUserJumpOutOn, stmeCallBackHandle);
    StmeLibRegisterTransition(STATE_OFF, StmeUserJumpOutOff, stmeCallBackHandle);
    StmeLibRegisterTransition(STATE_FAULT, StmeUserJumpOutFault, stmeCallBackHandle);
    StmeLibRegisterAction(STATE_OFF, STATE_ON, StmeUserEnterOn, stmeCallBackHandle);
    StmeLibRegisterAction(STATE_FAULT, STATE_ON, StmeUserEnterOn, stmeCallBackHandle);
    StmeLibRegisterAction(STATE_ON, STATE_ON, StmeUserDuringOn, stmeCallBackHandle);
}

void StmeUserSetTestCase(StmeUserCondStru *userCondInfo)
{
    memset(userCondInfo, 0, sizeof(StmeUserCondStru));
    if (currentTime > 950)
    {
        userCondInfo->flgSwitchOff = true;
        return;
    }
    if (currentTime > 900)
    {
        userCondInfo->flgSwitchOn = true;
        userCondInfo->flgFault = true;
        return;
    }
    if (currentTime > 850)
    {
        userCondInfo->flgSwitchOn = true;
        userCondInfo->flgHeal = true;
        return;
    }
    if (currentTime > 800)
    {
        userCondInfo->flgSwitchOn = true;
        userCondInfo->flgFault = true;
        return;
    }
    if (currentTime > 750)
    {
        userCondInfo->flgSwitchOn = true;
        return;
    }
    if (currentTime > 400)
    {
        userCondInfo->flgSwitchOff = true;
        return;
    }
    if (currentTime > 200)
    {
        userCondInfo->flgSwitchOn = true;
        return;
    }
}

int main()
{
    const char *stateNames[] = {"OFF", "ON", "FAULT"};
    // input info
    StmeUserCondStru userCondInfo = {0};

    // User State Machine Global Variable Declare
#if STATIC_MEMORY
    StmeLibCallBackStru userStmeInfo = {
        .stateNum = STATE_NUM,
        .actionMap = g_stmeUserHistoryInfo.actionFuncArr,
        .transitionList = g_stmeUserHistoryInfo.transitionFuncArr,
    };
    StmeLibCallBackStru *userStmeHandle = &userStmeInfo;
#else
    StmeLibCallBackStru *userStmeHandle = StmeLibNew(STATE_NUM);
#endif

    // User State Machine Init
    StmeUserInit(userStmeHandle);

    // Run State Machine Periodically
    for (currentTime = 0; currentTime < 1000; currentTime++)
    {
        StmeUserSetTestCase(&userCondInfo);
        uint8 stateCur = StmeLibRun(&userCondInfo, &g_stmeUserHistoryInfo.state, userStmeHandle);
        printf("Current state is [%s] at [%d].\n", stateNames[stateCur], currentTime);
    }

    return 0;
}