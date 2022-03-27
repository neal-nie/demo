/*
 * Copyright (c) 2022-2022 Nie Guangze. All rights reserved.
 * Description: file to show example of use call back library functions.
 */

#include <stdio.h>
#include "edge.h"

EdgeRisingStru ErStatic;

const char *BoolMap[] = {"false", "true"};

int main()
{
    // initialize
    EdgeRisingStru *ErDynamic = EdgeRisingNew(true);
    EdgeRisingInit(true, &ErStatic);

    // periodical
    bool flgTest = true;
    bool flgSta, flgDyn;
    printf("i\tin\tErSta\tErDyn\n");
    for (size_t i = 0; i < 20; i++)
    {
        // test case
        if (i % 5 == 0)
        {
            flgTest = !flgTest;
        }
        flgSta = ErStatic.Calc(flgTest, &ErStatic);
        flgDyn = ErDynamic->Calc(flgTest, ErDynamic);
        printf("[%d]\t[%s]\t[%s]\t[%s]\n", i, BoolMap[flgTest], BoolMap[flgSta], BoolMap[flgDyn]);
    }

    return 0;
}