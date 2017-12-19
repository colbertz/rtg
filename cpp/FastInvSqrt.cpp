#include <iostream>

float FastInvSqrt(float x)
{
    float xhalf = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i>>1); //magic number
    x = *(float*)&i;

    //two times of Newton method to improve the precision
    x = x * (1.5f-(xhalf*x*x));
    x = x * (1.5f-(xhalf*x*x));
    return x;
}

int main()
{
    float ret = FastInvSqrt(2.82f);
    std::cout<<ret;
}