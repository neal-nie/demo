/*
 * Copyright (c) 2022-2022 NealNie. All rights reserved.
 * Description: demo for cpp leanring
 */

#ifndef BOX_H
#define BOX_H

#include <stdint.h>

class Box
{
private:
    float length{1.};
    float width{1.};
    float height{1.};
    static uint16_t objCounter;

public:
    Box(float lv, float wv, float hv);
    Box(float edge) : Box(edge, edge, edge) {}
    Box();
    ~Box();

    double getLength() { return length; }
    double getWidth() { return width; }
    double getHeight() { return height; }
    float volume() const;
    static uint16_t getObjCounter() { return objCounter; }
};

#endif // !BOX_H
