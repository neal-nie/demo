/*
 * Copyright (c) 2022-2022 NealNie. All rights reserved.
 * Description: demo for cpp leanring
 */

#include "box.h"
#include <iostream>

// define of static class variable member
uint16_t Box::objCounter{0};

Box::Box()
{
    objCounter++;
    std::cout << "constructor 0 of Box is called." << std::endl;
}

Box::Box(float lv, float wv, float hv) : length{lv}, width{wv}, height{hv}
{
    objCounter++;
    std::cout << "constructor 1 of Box is called." << std::endl;
}

Box::~Box()
{
    objCounter--;
    std::cout << "destructor of Box is called." << std::endl;
}

float Box::volume() const
{
    return length * width * height;
}
