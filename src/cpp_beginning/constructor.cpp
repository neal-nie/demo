/*
 * Copyright (c) 2022-2022 NealNie. All rights reserved.
 * Description: demo for constructure functions
 */

#include <iostream>

class Box
{
private:
    double length{1.};
    double width{1.};
    double height{1.};
    static int objCounter;

public:
    // declaration of function
    Box(double lv, double wv, double hv);

    // definition of function
    Box(double side) : Box(side, side, side)
    {
        std::cout << "call constructor 2" << std::endl;
    }
    Box()
    {
        std::cout << "call constructor default" << std::endl;
    }

    double volume() const;

    double getLength() { return length; }
    double getWidth() { return width; }
    double getHeight() { return height; }

    static int getObjCounter() { return objCounter; }
};

// Necessary! used to initalize static variable. Define it!
int Box::objCounter{3};

double Box::volume() const
{
    return length * width * height;
}

Box::Box(double lv, double wv, double hv) : length{lv}, width{wv}, height{hv}
{
    std::cout << "call constructor 1" << std::endl;
}

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
