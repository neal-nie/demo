/*
 * Copyright (c) 2022-2022 Nie Guangze. All rights reserved.
 * Description: libray function for edge operation.
 */

#ifndef EDGE_H
#define EDGE_H

#include "types.h"

typedef struct _edge_rising_stru
{
    bool statePre;
    void (*Reset)(bool, struct _edge_rising_stru *);
    bool (*Calc)(bool, struct _edge_rising_stru *);
} EdgeRisingStru;

// static memory appliaction
// init an instance
void EdgeRisingInit(bool flgInit, EdgeRisingStru *instance);

// dynamic memory application
// create an instance
EdgeRisingStru *EdgeRisingNew(bool flgInit);

#endif // !EDGE_H
