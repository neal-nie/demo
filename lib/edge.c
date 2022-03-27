/*
 * Copyright (c) 2022-2022 Nie Guangze. All rights reserved.
 * Description: libray function for edge operation.
 */

#include "edge.h"
#include <stdlib.h>
#include <stdio.h>

static void EdgeRisingLibReset(bool flgIn, EdgeRisingStru *self)
{
    self->statePre = flgIn;
}

static bool EdgeRisingLibCalc(bool flgIn, EdgeRisingStru *self)
{
    bool flgRet = !self->statePre && flgIn;
    self->statePre = flgIn;
    return flgRet;
}

void EdgeRisingInit(bool flgInit, EdgeRisingStru *instance)
{
    instance->Reset = EdgeRisingLibReset;
    instance->Calc = EdgeRisingLibCalc;
    instance->Reset(flgInit, instance);
}

EdgeRisingStru *EdgeRisingNew(bool flgInit)
{
    EdgeRisingStru *instance = (EdgeRisingStru *)malloc(sizeof(EdgeRisingStru));
    if (!instance)
    {
        printf("ERROR! fail to apply memory for instance.");
        return NULL;
    }
    instance->Reset = EdgeRisingLibReset;
    instance->Calc = EdgeRisingLibCalc;
    instance->Reset(flgInit, instance);
    return instance;
}
