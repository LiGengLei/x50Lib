#include <iostream>
#include <xCCore/xCValue.h>
#include <yarp/os/all.h>

int main()
{
    xcr::xvalue vdouble,vstring;
    vdouble = 123.0;
    vstring = xstring("123.0");

    double vd = vdouble;
    xstring vs = vstring;
    std::cout << "vdouble = " << vd << std::endl;
    std::cout << "vstring = " << vs << std::endl;
}
