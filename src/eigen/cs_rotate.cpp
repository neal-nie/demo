#include <iostream>
#include <Eigen/Dense>
#include <cmath>

using Eigen::Matrix2f;
using Eigen::Vector2f;

namespace
{
    float Deg2Rad(float degree) {
        return degree * M_PI / 180.0F ;
    }
    Vector2f RotateCs(const Vector2f &baseVec, float angle)
    {
        Matrix2f transMaxtrix;
        transMaxtrix << std::cos(angle), std::sin(angle),
            -std::sin(angle), std::cos(angle);
        std::cout << transMaxtrix << std::endl;
        return transMaxtrix * baseVec;
    }
}

int main(void)
{
    Vector2f yUnit(0, 1);
    float spinAngle = 90; //degree
    Vector2f spinVec = RotateCs(yUnit, Deg2Rad(spinAngle));

    std::cout << "base vector: " << yUnit << std::endl;
    std::cout << "spin angle: " << spinAngle << " degree" << std::endl;
    std::cout << "new vector: " << spinVec << std::endl;


}