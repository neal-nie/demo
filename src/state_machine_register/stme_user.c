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
#define STATE_BUFF 3 // dummy state value as stateNum.

uint8 g_state;
uint16 g_onCounter;

#if STATIC_MEMORY
StmeLibTransitionCallBack g_transitionFuncArr[STATE_BUFF];
StmeLibActionCallBack g_actionFuncArr[STATE_BUFF * STATE_BUFF];
#endif

size_t currentTime;

const uint16 OnCounterMin = 500;

typedef struct
{
    bool flgSwitchOn;
    bool flgSwitchOff;
    bool flgFault;
    bool flgHeal;
} StmeUserCondStru;

uint8 StmeUserJumpOutOff(const void *condInfo)
{
    StmeUserCondStru *userCondInfo = (StmeUserCondStru *)condInfo;

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
    StmeUserCondStru *userCondInfo = (StmeUserCondStru *)condInfo;

    if (userCondInfo->flgSwitchOff && g_onCounter > OnCounterMin)
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
    StmeUserCondStru *userCondInfo = (StmeUserCondStru *)condInfo;

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
    g_onCounter = 0;
}

void StmeUserDuringOn(void)
{
    g_onCounter++;
}

void StmeUserInit(StmeLibCallBackStru *stmeCallBackHandle)
{
    g_state = STATE_OFF;
    g_onCounter = 0;
    StmeLibRegisterTransition(STATE_ON, StmeUserJumpOutOn, stmeCallBackHandle);
    StmeLibRegisterTransition(STATE_OFF, StmeUserJumpOutOff, stmeCallBackHandle);
    StmeLibRegisterTransition(STATE_FAULT, StmeUserJumpOutFault, stmeCallBackHandle);
    StmeLibRegisterAction(STATE_OFF, STATE_ON, StmeUserEnterOn, stmeCallBackHandle);
    StmeLibRegisterAction(STATE_FAULT, STATE_ON, StmeUserEnterOn, stmeCallBackHandle);
    StmeLibRegisterAction(STATE_ON, STATE_ON, StmeUserDuringOn, stmeCallBackHandle);
}

int main()
{
    // input info
    StmeUserCondStru userCondInfo = {0};

    // User State Machine Global Variable Declare
#if STATIC_MEMORY
    StmeLibCallBackStru userStmeInfo = {
        .stateNum = STATE_BUFF,
        .actionMap = g_actionFuncArr,
        .transitionList = g_transitionFuncArr,
    };
    StmeLibCallBackStru *userStmeHandle = &userStmeInfo;
#else
    StmeLibCallBackStru *userStmeHandle = StmeLibNew(STATE_BUFF);
#endif

    // User State Machine Init
    StmeUserInit(userStmeHandle);

    // Run State Machine Periodically
    for (currentTime = 0; currentTime < 1000; currentTime++)
    {
        if (currentTime > 200)
        {
            userCondInfo.flgSwitchOn = true;
        }
        if (currentTime > 400)
        {
            userCondInfo.flgSwitchOn = false;
            userCondInfo.flgSwitchOff = true;
        }
        if (currentTime > 750)
        {
            userCondInfo.flgSwitchOn = true;
            userCondInfo.flgSwitchOff = false;
        }
        if (currentTime > 800)
        {
            userCondInfo.flgFault = true;
        }
        if (currentTime > 850)
        {
            userCondInfo.flgFault = false;
            userCondInfo.flgHeal = true;
        }
        if (currentTime > 900)
        {
            userCondInfo.flgFault = true;
            userCondInfo.flgHeal = false;
        }
        if (currentTime > 950)
        {
            userCondInfo.flgSwitchOn = false;
            userCondInfo.flgSwitchOff = true;
        }
        uint8 stateCur = StmeLibRun(&userCondInfo, &g_state, userStmeHandle);
        printf("Current state is [%d] at [%d].\n", stateCur, currentTime);
    }

    return 0;
}