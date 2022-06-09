/*
 * Copyright (c) 2022-2022 NealNie. All rights reserved.
 * Description: demo for constructure functions
 */

#include <iostream>
#include "box.h"


int main()
{
    std::cout << "Box number is " << Box::getObjCounter() << std::endl;
    const Box cube{2., 2., 2};

    double cubeVolume = cube.volume();
    std::cout << "Volumne of Box Object [cube] is " << cubeVolume << std::endl;
    Box foo{3.};
    std::cout << "Volumne of Box Object [foo] is " << foo.volume() << std::endl;

    Box dummy{};
    std::cout << "Volumne of Box Object [dummy] is " << dummy.volume() << std::endl;

    std::cout << "length of Box Object [foo] is " << foo.getHeight() << std::endl;
    std::cout << "width of Box Object [foo] is " << foo.getWidth() << std::endl;

    Box boxes[6];
    return 0;
}
