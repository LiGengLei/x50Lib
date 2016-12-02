/*
* License:The MIT License (MIT)
*
* Copyright (c) 2013,2014 Yanyu Su
* State Key Laboratory of Robotics and System, Harbin Institute of Technology
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/regex.hpp>
#include <boost/shared_ptr.hpp>
#include "engine.h"

int main(int argc, char* argv[])
{
    std::string szFileName = "test";
    std::string szStrIn =
            "FUNCTION F1 \n"
            " DEFAULT_FRAME = {TCP} \n"
            " INIT_POSITION = {TCP} 100.0 120.0 -200.0 0.0 0.0 0.0 {N} ;\n"
            "INT   COUNT = 0; \n"
            "FLOAT POS = 0.0; \n"
            "POINT POS1[3] = 102.0 103.0 104.0 {N}; \n"
            "POINT POS2[3] = 110.0 110.0 110.0 {N}; \n"
            "POINT POS3[6] = 0.0 0.0 0.0 30.0 45.0 60.0 {TCP}; \n"
            "MOVL {TCP} 100.0 120.0 -200.0 {N}; /// move tool to the position of 100.0 120.0 -200.0 in the world frame {N} \n"
            "MOVL {TCP} 100.0 120.0 -200.0 {N}; /// move tool to the position of 100.0 120.0 -200.0 in the world frame {N} \n"
            "MOVC {TCP} 100.0 120.0 -200.0 {N}; /// move tool to the position of 100.0 120.0 -200.0 in the world frame {N} \n"
            "MOVC {TCP} 100.0 120.0 -200.0 {N}; /// move tool to the position of 100.0 120.0 -200.0 in the world frame {N} \n"
            "MOVC {TCP} 100.0 120.0 -200.0 {N}; /// move tool to the position of 100.0 120.0 -200.0 in the world frame {N} \n"
            "MOVS {TCP} POS1 ;                  /// move tool to the position of 100.0 120.0 -200.0 in the world frame {N} \n"
            "MOVS {TCP} POS2 ;                  /// move tool to the position of 100.0 120.0 -200.0 in the world frame {N} \n"
            "MOVJ {TCP} 150.0;                  /// move joint 1 to the position of 150.0 deg \n"
            "\n"
            "WHILE COUNT < 15;                 /// move joint 1 to the position of 150.0 deg \n"
            "COUNT = COUNT + 1;                /// change the value of POS\n"
            "POS = POS + 0.5;                  /// change the value of POS\n"
            "MOVJ [J1] [J2] POS;                     /// move joint 2 to the position of POS \n"
            "MOVJ [J1] [J2] [J3] POS;                     /// move joint 2 to the position of POS \n"
            "MOVJ [J2] POS;                     /// move joint 2 to the position of POS \n"
            "END WHILE COUNT < 15;              /// end of the while loop"
            "\n"
            "\n"
            "COUNT = 0;\n"
            "WHILE COUNT < 15;                 /// move joint 1 to the position of 150.0 deg \n"
            "COUNT = COUNT + 1;                /// change the value of POS\n"
            "POS = POS + 0.5;                  /// change the value of POS\n"
            "MOVL [J2] POS;                     /// move joint 2 to the position of POS \n"
            "END WHILE COUNT < 15;              /// end of the while loop"
            "\n"
            "END FUNCTION F1; \n"
            "\n"
            "\n"
            "\n"
            "FUNCTION F2; \n"
            "INT   COUNT = 0; \n"
            "WHILE COUNT < 15;                 /// move joint 1 to the position of 150.0 deg \n"
            "COUNT = COUNT + 1;                /// change the value of POS\n"
            "MOV J2  15.0;                     /// move joint 2 to the position of POS \n"
            "END WHILE COUNT < 15;              /// end of the while loop"
            "\n"
            "END FUNCTION F2;";

    std::ifstream myfile;
    myfile.open("testPro.txt");
    if(myfile.good())
    {
        std::string strtmp((std::istreambuf_iterator<char>(myfile)),
                         std::istreambuf_iterator<char>());
        szStrIn = strtmp;
    }
    else
    {
        std::cout << "can not open the file" << std::endl;
    }

    std::cout << "A example of the program" << std::endl
              << "-------------------------------------------" << std::endl
              << szStrIn << std::endl
              << "-------------------------------------------" << std::endl;

    std::string szStr; xPreProcess(szStrIn, szStr);
    std::stringstream stm(szStr);
    xptrWorkspace pWorkspace = xLoadWorkspace(stm,szFileName);
    std::string prefix = " ";
    std::cout << pWorkspace->toString(prefix) << std::endl;
    return 0;
}
